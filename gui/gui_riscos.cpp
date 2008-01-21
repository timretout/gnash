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

/* $Id: gui_riscos.cpp,v 1.2 2008/01/21 20:55:41 rsavoye Exp $ */

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "gui.h"
#include "GnashException.h"

#ifdef GUI_RISCOS
#include "riscossup.h"
#endif

namespace gnash {

#ifdef GUI_RISCOS
std::auto_ptr<Gui> createRISCOSGui(unsigned long windowid, float scale, bool do_loop, unsigned int bit_depth)
{
	return std::auto_ptr<Gui>(new RiscosGui(windowid, scale, do_loop, bit_depth));
}
#else // ! GUI_RISCOS
std::auto_ptr<Gui> createRISCOSGui(unsigned long , float , bool , unsigned int )
{
	throw GnashException("Support for RISCOS gui was not compiled in");
}
#endif // ! GUI_RISCOS

} // namespace gnash

