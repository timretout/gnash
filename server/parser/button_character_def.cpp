// button_character_def.cpp:  Mouse-sensitive SWF buttons, for Gnash.
//
//   Copyright (C) 2006, 2007, 2008 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

/* $Id: button_character_def.cpp,v 1.26 2008/01/21 20:56:00 rsavoye Exp $ */

// Based on the public domain work of Thatcher Ulrich <tu@tulrich.com> 2003

#include "button_character_def.h"
#include "button_character_instance.h" // for create_character_instance()

#include "stream.h" // for read()
#include "movie_definition.h"
#include "action_buffer.h"


namespace gnash {

//
// button_action
//


button_action::button_action(stream& in, int tag_type, unsigned long endPos, movie_definition& mdef)
	:
	m_actions(mdef)
{
	// Read condition flags.
	if (tag_type == SWF::DEFINEBUTTON) // 7
	{
		m_conditions = OVER_DOWN_TO_OVER_UP;
	}
	else
	{
		assert(tag_type == SWF::DEFINEBUTTON2); // 34

		if ( in.get_position()+2 > endPos ) 
		{
			IF_VERBOSE_MALFORMED_SWF(
			log_swferror(_("Premature end of button action input: can't read conditions"));
			);
			return;
		}
		m_conditions = in.read_u16();
	}

	IF_VERBOSE_PARSE (
	log_parse(_("-- actions in button")); // @@ need more info about which actions
	);

	// Read actions.
	m_actions.read(in, endPos);
}

//
// button_record
//

bool
button_record::is_valid()
{
	return (m_character_def != NULL);
}

bool
button_record::read(stream* in, int tag_type,
		movie_definition* m, unsigned long endPos)
{
	// caller should check this
	assert(in->get_position() < endPos);
	int	flags = in->read_u8();
	if (flags == 0)
	{
		return false;
	}

	// Upper 4 bits are:
	//
	//   ButtonReserved = readBits (f, 2);
	//   ButtonHasBlendMode = readBits(f, 1);
	//   ButtonHasFilterList = readBits(f, 1);
	//
	m_hit_test = flags & (1<<3); // 8 ? true : false;
	m_down     = flags & (1<<2); // 4 ? true : false;
	m_over     = flags & (1<<1); // 2 ? true : false;
	m_up       = flags & (1<<0); // 1 ? true : false;

	if (in->get_position()+2 > endPos)
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("   premature end of button record input stream, can't read character id"));
		);
		return false;
	}
	m_character_id = in->read_u16();

	// Get character definition now (safer)
	m_character_def = m->get_character_def(m_character_id);

	// If no character with given ID is found in the movie
	// definition, we print an error, but keep parsing.
	if ( ! m_character_def )
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("   button record refer to "
			"character with id %d, which is not found "
			"in the chars dictionary"), m_character_id);
		);
	}
	else
	{
		IF_VERBOSE_PARSE(
		log_parse(_("   button record for states %x contain "
			"character %d (%s)"), (m_hit_test<<4)+(m_down<<2)+(m_over<<1)+(m_up), m_character_id,
		        typeName(*m_character_def).c_str());
		);
	}

	if (in->get_position()+2 > endPos)
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("   premature end of button record input stream, can't read button layer (depth?)"));
		);
		return false;
	}
	m_button_layer = in->read_u16();

	// TODO: pass available range to button matrix read
	m_button_matrix.read(in);

	if (tag_type == SWF::DEFINEBUTTON2)
	{
		// TODO: pass available range to button cxform read
		m_button_cxform.read_rgba(in);
	}

	return true;
}


//
// button_character_definition
//

button_character_definition::button_character_definition(movie_definition* m)
	:
	m_min_layer(0),
	m_max_layer(0),
	m_sound(NULL),
	_movieDef(m)

// Constructor.
{
}

button_character_definition::~button_character_definition()
{
	for (ButtonActVect::iterator i=m_button_actions.begin(),
			ie=m_button_actions.end();
			i != ie; ++i )
	{
		delete *i;
	}
}


void button_character_definition::sound_info::read(stream* in)
{
	m_in_point = m_out_point = m_loop_count = 0;
	in->read_uint(2);	// skip reserved bits.
	m_stop_playback = in->read_bit(); 
	m_no_multiple = in->read_bit(); 
	m_has_envelope = in->read_bit();
	m_has_loops = in->read_bit(); 
	m_has_out_point = in->read_bit();
	m_has_in_point = in->read_bit(); 
	if (m_has_in_point) m_in_point = in->read_u32();
	if (m_has_out_point) m_out_point = in->read_u32();
	if (m_has_loops) m_loop_count = in->read_u16();

	if (m_has_envelope)
	{
		int nPoints = in->read_u8();
		m_envelopes.resize(nPoints);
		for (int i=0; i < nPoints; i++)
		{
			m_envelopes[i].m_mark44 = in->read_u32();
			m_envelopes[i].m_level0 = in->read_u16();
			m_envelopes[i].m_level1 = in->read_u16();
		}
	}
	else
	{
		m_envelopes.resize(0);
	}


	IF_VERBOSE_PARSE(
	log_parse("	has_envelope = %d", m_has_envelope);
	log_parse("	has_loops = %d", m_has_loops);
	log_parse("	has_out_point = %d", m_has_out_point);
	log_parse("	has_in_point = %d", m_has_in_point);
	log_parse("	in_point = %d", m_in_point);
	log_parse("	out_point = %d", m_out_point);
	log_parse("	loop_count = %d", m_loop_count);
	log_parse("	envelope size = " SIZET_FMT , m_envelopes.size());
	);
}

void
button_character_definition::readDefineButton(stream* in, movie_definition* m)
{
	assert(m);
	assert(in);

	// Character ID has been read already

	// Old button tag.

	unsigned long endTagPos = in->get_tag_end_position();

	// Read button character records.
	for (;;)
	{
		button_record	r;
		if (r.read(in, SWF::DEFINEBUTTON, m, endTagPos) == false)
		{
			// Null record; marks the end of button records.
			break;
		}

		// SAFETY CHECK:
		// if the button_record is corrupted, discard it
		if ( r.is_valid() )
		{
			m_button_records.push_back(r);
		}
	}

	if ( in->get_position() >= endTagPos )
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("Premature end of DEFINEBUTTON tag, won't read actions"));
		);
		return;
	}

	// Read actions.
	m_button_actions.push_back(new button_action(*in, SWF::DEFINEBUTTON, endTagPos, *m));

	// detect min/max layer number
	m_min_layer=0;
	m_max_layer=0;
	for (unsigned int i=0; i<m_button_records.size(); i++)
	{
	  int this_layer = m_button_records[i].m_button_layer;

	  if ((i==0) || (this_layer < m_min_layer))  m_min_layer=this_layer;
	  if ((i==0) || (this_layer > m_max_layer))  m_max_layer=this_layer;
	}
}

void
button_character_definition::readDefineButton2(stream* in, movie_definition* m)
{
	// Character ID has been read already

	// Read the menu flag
	// (this is a single bit, the other 7 bits are reserved)
	m_menu = in->read_u8() != 0;

	unsigned button_2_action_offset = in->read_u16();
	unsigned long tagEndPosition = in->get_tag_end_position();
	unsigned next_action_pos = in->get_position() + button_2_action_offset - 2;

	if ( next_action_pos > tagEndPosition )
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("Next Button2 actionOffset (%u) points past the end of tag (%lu)"),
			button_2_action_offset, tagEndPosition);
		);
		return;
	}

	unsigned long endOfButtonRecords = tagEndPosition;
	if ( ! button_2_action_offset  ) endOfButtonRecords = tagEndPosition;

	// Read button records.
	// takes at least 1 byte for the end mark button record, so 
	// we don't attempt to parse at all unless we have at least 1 byte left
	while ( in->get_position() < endOfButtonRecords )
	{
		button_record	r;
		if (r.read(in, SWF::DEFINEBUTTON2, m, endOfButtonRecords) == false)
		{
			// Null record; marks the end of button records.
			break;
		}

		// SAFETY CHECK:
		// if the button_record is corrupted, discard it
		if ( r.is_valid() )
		{
			m_button_records.push_back(r);
		}
	}

	if ( button_2_action_offset )
	{
		in->set_position(next_action_pos);

		// Read Button2ActionConditions
		// Don't read past tag end
		while ( in->get_position() < tagEndPosition ) 
		{
			unsigned next_action_offset = in->read_u16();
			next_action_pos = in->get_position() + next_action_offset - 2;

			unsigned long endActionPos = next_action_offset ? next_action_pos : tagEndPosition;

			m_button_actions.push_back(new button_action(*in, SWF::DEFINEBUTTON2, endActionPos, *m));

			if (next_action_offset == 0 )
			{
				// done.
				break;
			}

			//was: in->get_position() >= in->get_tag_end_position()
			if ( next_action_pos >= in->get_tag_end_position() )
			{
				IF_VERBOSE_MALFORMED_SWF(
				log_swferror(_("Next action offset (%u) in Button2ActionConditions points past the end of tag"),
					next_action_offset);
				);
				break;
			}

			// seek to next action.
			in->set_position(next_action_pos);
		}
	}

	// detect min/max layer number
	m_min_layer=0;
	m_max_layer=0;
	for (unsigned int i=0; i<m_button_records.size(); i++)
	{
		int this_layer = m_button_records[i].m_button_layer;

		if ((i==0) || (this_layer < m_min_layer))  m_min_layer=this_layer;
		if ((i==0) || (this_layer > m_max_layer))  m_max_layer=this_layer;
	}
}

void
button_character_definition::readDefineButtonSound(stream* in, movie_definition* m)
{
	// Character ID has been read already

	if ( m_sound )
	{
		IF_VERBOSE_MALFORMED_SWF(
		log_swferror(_("Attempt to redefine button sound ignored"));
		);
		return;
	}

	m_sound.reset( new button_sound_def() );

	IF_VERBOSE_PARSE(
	log_parse(_("button sound options: "));
	);

	for (int i = 0; i < 4; i++)
	{
		button_sound_info& bs = m_sound->m_button_sounds[i];
		bs.m_sound_id = in->read_u16();
		if (bs.m_sound_id)
		{
			bs.m_sam = m->get_sound_sample(bs.m_sound_id);
			if ( ! bs.m_sam )
			{
				IF_VERBOSE_MALFORMED_SWF(
				log_swferror(_("sound tag not found, sound_id=%d, button state #=%i"), bs.m_sound_id, i);
				);
			}
			IF_VERBOSE_PARSE(
			log_parse("\n	sound_id = %d", bs.m_sound_id);
			);
			bs.m_sound_style.read(in);
		}
	}
}


void
button_character_definition::read(stream* in, int tag_type, movie_definition* m)
// Initialize from the given stream.
{
	// Character ID has been read already

	switch (tag_type)
	{
		case SWF::DEFINEBUTTON:
			readDefineButton(in, m);
			break;
		case SWF::DEFINEBUTTONSOUND:
			readDefineButtonSound(in, m);
			break;
		case SWF::DEFINEBUTTON2:
			readDefineButton2(in, m);
			break;
		default:
			abort();
	}
}


character*
button_character_definition::create_character_instance(
		character* parent, int id)
{
	character* ch = new button_character_instance(this, parent, id);
	return ch;
}

#ifdef GNASH_USE_GC
void
button_character_definition::button_sound_info::markReachableResources() const
{
	if ( m_sam ) m_sam->setReachable();
}
#endif // GNASH_USE_GC

int
button_character_definition::getSWFVersion() const
{
	return _movieDef->get_version();
}

} // namespace gnash

// Local Variables:
// mode: C++
// c-basic-offset: 8
// tab-width: 8
// indent-tabs-mode: t
// End:
