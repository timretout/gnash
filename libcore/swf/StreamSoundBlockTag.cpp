// StreamSoundBlockTag.cpp:  for Gnash.
//
//   Copyright (C) 2007, 2008 Free Software Foundation, Inc.
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


#include "StreamSoundBlockTag.h"
#include "sound_handler.h" 
#include "movie_definition.h" // for addControlTag
#include "sprite_instance.h" // for execute
#include "SoundInfo.h" // for loader
#include "SWFStream.h"
#include "log.h" 
//#include "sound_definition.h" // for sound_sample

namespace gnash {
namespace SWF {

void
StreamSoundBlockTag::execute(sprite_instance* m, DisplayList& /*dlist*/) const
{
	// Make static ?
	media::sound_handler* handler = get_sound_handler();
	if (handler)
	{
		// This makes it possible to stop only the stream when framejumping.
		m->setStreamSoundId(m_handler_id);
		handler->play_sound(m_handler_id, 0, 0, m_start, NULL);
	}
}

/* public static */
void
StreamSoundBlockTag::loader(SWFStream& in, tag_type tag, movie_definition* m)
{
    assert(tag == SWF::SOUNDSTREAMBLOCK); // 19

    media::sound_handler* handler = get_sound_handler();

    // If we don't have a sound_handler registered stop here
    if (!handler)
    {
	// log_debug ?
        return;
    }

    // Get the ID of the sound stream currently being loaded
    int handle_id = m->get_loading_sound_stream_id();

    // Get the SoundInfo object that contains info about the sound stream.
    // Ownership of the object is in the soundhandler
    media::SoundInfo* sinfo = handler->get_sound_info(handle_id);

    // If there is no SoundInfo something is wrong...
    if (!sinfo)
    {
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror(_("Found SOUNDSTREAMBLOCK tag w/out preceeding SOUNDSTREAMHEAD"));
        );
        return;
    }

    media::audioCodecType format = sinfo->getFormat();
    unsigned int sample_count = sinfo->getSampleCount();

    // MP3 format blocks have additional info
    if (format == media::AUDIO_CODEC_MP3)
    {
        in.ensureBytes(4);
	// FIXME: use these values !
        unsigned int samplesCount = in.read_u16(); UNUSED(samplesCount);
        unsigned int seekSamples = in.read_u16();
	LOG_ONCE ( if ( seekSamples ) log_unimpl("MP3 soundblock seek samples") );
    }

    const unsigned int dataLength = in.get_tag_end_position() - in.tell();
    if ( ! dataLength )
    {
        IF_VERBOSE_MALFORMED_SWF(
        LOG_ONCE( log_swferror("Empty SOUNDSTREAMBLOCK tag, seems common waste of space") );
        );
        return;
    }

    unsigned char *data = new unsigned char[dataLength];
    const unsigned int bytesRead = in.read(reinterpret_cast<char*>(data), dataLength);
    
    if (bytesRead < dataLength)
    {
        throw ParserException(_("Tag boundary reported past end of stream!"));
    }

    // Fill the data on the apropiate sound, and receives the starting point
    // for later "start playing from this frame" events.
    //
    // ownership of 'data' is transferred here
    //
    long start = handler->fill_stream_data(data, dataLength, sample_count, handle_id);

    // TODO: log_parse ?

    StreamSoundBlockTag* ssst = new StreamSoundBlockTag(handle_id, start);
    m->addControlTag(ssst); // ownership is transferred to movie_definition
}

} // namespace gnash::SWF
} // namespace gnash

// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End: