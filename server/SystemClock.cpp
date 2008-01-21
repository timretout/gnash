// SystemClock.cpp -- system-time based VirtualClock for gnash core lib
// 
//   Copyright (C) 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "SystemClock.h"

#include "tu_timer.h" // for fetchSystemTime

#include <boost/cstdint.hpp> // for boost::uint64_t typedef

namespace gnash
{

/* static private */
boost::uint64_t
SystemClock::fetchSystemTime() 
{
    // TODO: review tu_timer implementation to make sure it
    //       always return milliseconds
    return tu_timer::get_ticks();
}

/* public */
SystemClock::SystemClock() 
	:
	_startTime(fetchSystemTime())
{
}

/* public */
unsigned long int
SystemClock::elapsed() const
{
    return fetchSystemTime() - _startTime;
}

/* public */
void
SystemClock::restart()
{
    _startTime = fetchSystemTime();
}

} // namespace gnash

