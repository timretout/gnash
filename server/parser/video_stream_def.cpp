// 
//   Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
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
// $Id: video_stream_def.cpp,v 1.20 2007/10/19 09:30:24 strk Exp $

#include "video_stream_def.h"
#include "video_stream_instance.h"
#include "render.h"

#ifdef USE_FFMPEG
#include "VideoDecoderFfmpeg.h"
#elif defined(SOUND_GST)
#include "VideoDecoderGst.h"
#endif

namespace gnash {

video_stream_definition::video_stream_definition(uint16_t char_id)
	:
	m_char_id(char_id),
	_width(0),
	_height(0),
	_decoder(NULL)
{
}


video_stream_definition::~video_stream_definition()
{
	m_video_frames.clear(); // TODO: isn't this useless ?
}


void
video_stream_definition::read(stream* in, SWF::tag_type tag, movie_definition* m)
{

	// Character ID has been read already, and was loaded in the constructor

	assert(tag == SWF::DEFINEVIDEOSTREAM ||	tag == SWF::VIDEOFRAME);

	if (tag == SWF::DEFINEVIDEOSTREAM)
	{
		m_start_frame = m->get_loading_frame();

		m_num_frames = in->read_u16();

		_width = in->read_u16();
		_height = in->read_u16();
		m_bound.enclose_point(0, 0);
		m_bound.expand_to_point(PIXELS_TO_TWIPS(_width), PIXELS_TO_TWIPS(_height));

		m_reserved_flags = in->read_uint(5);
		m_deblocking_flags = in->read_uint(2);
		m_smoothing_flags = in->read_bit(); 

		m_codec_id = static_cast<videoCodecType>(in->read_u8());
#ifdef USE_FFMPEG
		_decoder.reset( new VideoDecoderFfmpeg() );
#elif defined(SOUND_GST)
		_decoder.reset( new VideoDecoderGst() );
#else
		_decoder.reset( new VideoDecoder() );
#endif
		bool ret = _decoder->setup(_width, _height, m_deblocking_flags, m_smoothing_flags, m_codec_id, gnash::render::videoFrameFormat());
		if (!ret) _decoder.reset();

	}
	else if (tag == SWF::VIDEOFRAME && _decoder)
	{
		// We don't use the videoframe number, but instead
		// each video frame is tied to the swf-frame where
		// it belongs.
		in->skip_bytes(2); //int frameNum = in->read_u16();

		// We need to make the buffer a bit bigger than the data
		// to avoid libavcodec (ffmpeg) making illegal reads.
		// The reason is a bit sketchy, but it seems that the h263
		// decoder (perhaps other decoders as well) assumes that the
		// buffer with the data is bigger than the data it contains.
		// We make the buffer 4 bytes bigger than the data, and set
		// them to 0.

		// The data size is 4 bytes smaller than this, but because of 
		// what is mentioned above we don't subtract the 4 bytes.
		int size = in->get_tag_length();
		uint8_t* data = new uint8_t[size];
		memset(data, 0, size);
		for (int i = 0; i < size-4; i++) // The size-variable 4 bytes bigger than the data
		{
			data[i] = in->read_u8();
		}

		image::image_base* img = _decoder->decodeToImage(data, size);

		if (img) {
			m_video_frames[m->get_loading_frame()] = img;
		} else {
			log_error(_("An error occured while decoding video frame in frame %d"), m->get_loading_frame());
		}
		delete [] data;
	}

}


character*
video_stream_definition::create_character_instance(character* parent, int id)
{
	character* ch = new video_stream_instance(this, parent, id);
	return ch;
}

image::image_base*
video_stream_definition::get_frame_data(int frameNum)
{
	EmbedFrameMap::iterator it = m_video_frames.find(frameNum);
	if( it != m_video_frames.end() )
	{
		return it->second;
	} else {
		log_debug(_("No video data available for frame %d."), frameNum);
		return NULL;
	}
}

} // namespace gnash

