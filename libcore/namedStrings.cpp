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

// A file to contain all of the different strings for which we want compile time
// known string table keys.

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h"
#endif

#include "namedStrings.h"
#include "string_table.h"

namespace gnash {
namespace NSV { // Named String Values

// Load up our pre-known names
static string_table::svt preload_names[] =
{
	string_table::svt( "a", NSV::PROP_A ),
	string_table::svt( "addListener", NSV::PROP_ADD_LISTENER ),
	string_table::svt( "align", NSV::PROP_ALIGN ),
	string_table::svt( "_alpha", NSV::PROP_uALPHA ),
	string_table::svt( "b", NSV::PROP_B ),
	string_table::svt( "blockIndent", NSV::PROP_BLOCK_INDENT ),
	string_table::svt( "bold", NSV::PROP_BOLD ),
	string_table::svt( "broadcastMessage", NSV::PROP_BROADCAST_MESSAGE ),
	string_table::svt( "bullet", NSV::PROP_BULLET ),
	string_table::svt( "c", NSV::PROP_C ),
	string_table::svt( "callee", NSV::PROP_CALLEE ),
	//string_table::svt( "color", NSV::PROP_COLOR ), // clashes with CLASS_COLOR in case-insensitive mode
	string_table::svt( "constructor", NSV::PROP_CONSTRUCTOR ),
	string_table::svt( "__constructor__", NSV::PROP_uuCONSTRUCTORuu ),
	string_table::svt( "_currentframe", NSV::PROP_uCURRENTFRAME ),
	string_table::svt( "d", NSV::PROP_D ),
	string_table::svt( "_droptarget", NSV::PROP_uDROPTARGET ),
	string_table::svt( "enabled", NSV::PROP_ENABLED ),
	string_table::svt( "useHandCursor", NSV::PROP_USEHANDCURSOR ),
	string_table::svt( "_focusrect", NSV::PROP_uFOCUSRECT ),
	string_table::svt( "_framesloaded", NSV::PROP_uFRAMESLOADED ),
	string_table::svt( "_height", NSV::PROP_uHEIGHT ),
	string_table::svt( "height", NSV::PROP_HEIGHT ),
	string_table::svt( "_highquality", NSV::PROP_uHIGHQUALITY ),
	string_table::svt( "htmlText", NSV::PROP_HTML_TEXT ),
	string_table::svt( "indent", NSV::PROP_INDENT ),
	string_table::svt( "italic", NSV::PROP_ITALIC ),
	string_table::svt( "leading", NSV::PROP_LEADING ),
	string_table::svt( "left_margin", NSV::PROP_LEFT_MARGIN ),
	string_table::svt( "length", NSV::PROP_LENGTH ),
	string_table::svt( "_listeners", NSV::PROP_uLISTENERS ),
	string_table::svt( "loaded", NSV::PROP_LOADED ),
	string_table::svt( "_name", NSV::PROP_uNAME ),
	string_table::svt( "onLoad", NSV::PROP_ON_LOAD ),
	string_table::svt( "onClose", NSV::PROP_ON_CLOSE ),
	string_table::svt( "onLoadStart", NSV::PROP_ON_LOAD_START ),
	string_table::svt( "onLoadError", NSV::PROP_ON_LOAD_ERROR ),
	string_table::svt( "onLoadProgress", NSV::PROP_ON_LOAD_PROGRESS ),
	string_table::svt( "onLoadInit", NSV::PROP_ON_LOAD_INIT ),
	string_table::svt( "onUnload", NSV::PROP_ON_UNLOAD ),
	string_table::svt( "onEnterFrame", NSV::PROP_ON_ENTER_FRAME ),
	string_table::svt( "onConstruct", NSV::PROP_ON_CONSTRUCT ),
	string_table::svt( "onInitialize", NSV::PROP_ON_INITIALIZE ),
	string_table::svt( "onData", NSV::PROP_ON_DATA ),
	string_table::svt( "onResize", NSV::PROP_ON_RESIZE ),
	string_table::svt( "onFullScreen", NSV::PROP_ON_FULLSCREEN ),
	string_table::svt( "onPress", NSV::PROP_ON_PRESS ),
	string_table::svt( "onRelease", NSV::PROP_ON_RELEASE ),
	string_table::svt( "onReleaseOutside", NSV::PROP_ON_RELEASE_OUTSIDE ),
	string_table::svt( "onRollOut", NSV::PROP_ON_ROLL_OUT ),
	string_table::svt( "onRollOver", NSV::PROP_ON_ROLL_OVER ),
	string_table::svt( "onDragOver", NSV::PROP_ON_DRAG_OVER ),
	string_table::svt( "onDragOut", NSV::PROP_ON_DRAG_OUT ),
	string_table::svt( "onKeyPress", NSV::PROP_ON_KEY_PRESS ),
	string_table::svt( "onKeyDown", NSV::PROP_ON_KEY_DOWN ),
	string_table::svt( "onKeyUp", NSV::PROP_ON_KEY_UP ),
	string_table::svt( "onMouseDown", NSV::PROP_ON_MOUSE_DOWN ),
	string_table::svt( "onMouseUp", NSV::PROP_ON_MOUSE_UP ),
	string_table::svt( "onMouseMove", NSV::PROP_ON_MOUSE_MOVE ),
	string_table::svt( "onSetFocus", NSV::PROP_ON_SET_FOCUS ),
	string_table::svt( "onKillFocus", NSV::PROP_ON_KILL_FOCUS ),
	string_table::svt( "onSelect", NSV::PROP_ON_SELECT ),
	string_table::svt( "onStatus", NSV::PROP_ON_STATUS ),
	string_table::svt( "onResult", NSV::PROP_ON_RESULT ),
	string_table::svt( "onMetaData", NSV::PROP_ON_META_DATA ),
	string_table::svt( "onSockClose", NSV::PROP_ON_SOCK_CLOSE ),
	string_table::svt( "onSockConnect", NSV::PROP_ON_SOCK_CONNECT ),
	string_table::svt( "onSockData", NSV::PROP_ON_SOCK_DATA ),
	string_table::svt( "onSockXML", NSV::PROP_ON_SOCK_XML ),
	string_table::svt( "onXMLLoad", NSV::PROP_ON_XML_LOAD ),
	string_table::svt( "onXMLData", NSV::PROP_ON_XML_DATA ),
	string_table::svt( "parseXML", NSV::PROP_PARSE_XML ),
	string_table::svt( "onTimer", NSV::PROP_ON_TIMER ),
	string_table::svt( "_parent", NSV::PROP_uPARENT ),
	string_table::svt( "_root", NSV::PROP_uROOT ),
	string_table::svt( "_global", NSV::PROP_uGLOBAL ),
	string_table::svt( "__proto__", NSV::PROP_uuPROTOuu ),
	string_table::svt( "prototype", NSV::PROP_PROTOTYPE ),
	string_table::svt( "push", NSV::PROP_PUSH ),
	string_table::svt( "removeListener", NSV::PROP_REMOVE_LISTENER ),
	string_table::svt( "rightMargin", NSV::PROP_RIGHT_MARGIN ),
	string_table::svt( "_rotation", NSV::PROP_uROTATION ),
	string_table::svt( "scaleMode", NSV::PROP_SCALE_MODE ),
	string_table::svt( "size", NSV::PROP_SIZE ),
	string_table::svt( "_soundbuftime", NSV::PROP_uSOUNDBUFTIME ),
	string_table::svt( "splice", NSV::PROP_SPLICE ),
	string_table::svt( "Stage", NSV::PROP_iSTAGE ),
	string_table::svt( "status", NSV::PROP_STATUS ),
	string_table::svt( "super", NSV::PROP_SUPER ),
	string_table::svt( "_target", NSV::PROP_uTARGET ),
	string_table::svt( "text", NSV::PROP_TEXT ),
	string_table::svt( "textColor", NSV::PROP_TEXT_COLOR ),
	string_table::svt( "textWidth", NSV::PROP_TEXT_WIDTH ),
	string_table::svt( "textHeight", NSV::PROP_TEXT_HEIGHT ),
	string_table::svt( "toString", NSV::PROP_TO_STRING ),
	string_table::svt( "_totalframes", NSV::PROP_uTOTALFRAMES ),
	string_table::svt( "tx", NSV::PROP_TX ),
	string_table::svt( "ty", NSV::PROP_TY ),
	string_table::svt( "underline", NSV::PROP_UNDERLINE ),
	string_table::svt( "_url", NSV::PROP_uURL ),
	string_table::svt( "valueOf", NSV::PROP_VALUE_OF ),
	string_table::svt( "_visible", NSV::PROP_uVISIBLE ),
	string_table::svt( "_width", NSV::PROP_uWIDTH ),
	string_table::svt( "width", NSV::PROP_WIDTH ),
	string_table::svt( "x", NSV::PROP_X ),
	string_table::svt( "_x", NSV::PROP_uX ),
	string_table::svt( "_xmouse", NSV::PROP_uXMOUSE ),
	string_table::svt( "_xscale", NSV::PROP_uXSCALE ),
	string_table::svt( "y", NSV::PROP_Y ),
	string_table::svt( "_y", NSV::PROP_uY ),
	string_table::svt( "_ymouse", NSV::PROP_uYMOUSE ),
	string_table::svt( "_yscale", NSV::PROP_uYSCALE ),
	string_table::svt( "System", NSV::CLASS_SYSTEM ),
//	string_table::svt( "Stage", NSV::CLASS_STAGE ), // Identical to PROP_iSTAGE
	string_table::svt( "MovieClip", NSV::CLASS_MOVIE_CLIP ),
	string_table::svt( "TextField", NSV::CLASS_TEXT_FIELD ),
	string_table::svt( "Button", NSV::CLASS_BUTTON ),
	string_table::svt( "Math", NSV::CLASS_MATH ),
	string_table::svt( "Boolean", NSV::CLASS_BOOLEAN ),
	string_table::svt( "Color", NSV::CLASS_COLOR ),
	string_table::svt( "Selection", NSV::CLASS_SELECTION ),
	string_table::svt( "Sound", NSV::CLASS_SOUND ),
	string_table::svt( "XMLSocket", NSV::CLASS_X_M_L_SOCKET ),
	string_table::svt( "Date", NSV::CLASS_DATE ),
	string_table::svt( "XML", NSV::CLASS_X_M_L ),
	string_table::svt( "XMLNode", NSV::CLASS_X_M_L_NODE ),
	string_table::svt( "Mouse", NSV::CLASS_MOUSE ),
	string_table::svt( "Object", NSV::CLASS_OBJECT ),
	string_table::svt( "String", NSV::CLASS_STRING ),
	string_table::svt( "Number", NSV::CLASS_NUMBER ),
	string_table::svt( "Accessibility", NSV::CLASS_ACCESSIBILITY ),	
	string_table::svt( "Array", NSV::CLASS_ARRAY ),
	string_table::svt( "Key", NSV::CLASS_KEY ),
	string_table::svt( "AsBroadcaster", NSV::CLASS_AS_BROADCASTER ),
	string_table::svt( "Function", NSV::CLASS_FUNCTION ),
	string_table::svt( "TextSnapshot", NSV::CLASS_TEXT_SNAPSHOT ),
	string_table::svt( "TextFormat", NSV::CLASS_TEXT_FORMAT ),
	string_table::svt( "Video", NSV::CLASS_VIDEO ),
	string_table::svt( "Camera", NSV::CLASS_CAMERA ),
	string_table::svt( "Microphone", NSV::CLASS_MICROPHONE ),
	string_table::svt( "SharedObject", NSV::CLASS_SHARED_OBJECT ),
	string_table::svt( "LoadVars", NSV::CLASS_LOAD_VARS ),
	string_table::svt( "CustomActions", NSV::CLASS_CUSTOM_ACTIONS ),
	string_table::svt( "NetConnection", NSV::CLASS_NET_CONNECTION ),
	string_table::svt( "NetStream", NSV::CLASS_NET_STREAM ),
	string_table::svt( "ContextMenu", NSV::CLASS_CONTEXT_MENU ),
	string_table::svt( "MovieClipLoader", NSV::CLASS_MOVIE_CLIP_LOADER ),
	string_table::svt( "Error", NSV::CLASS_ERROR ),
	string_table::svt( "flash.display", NSV::NS_FLASH_DISPLAY ),
	string_table::svt( "flash.text", NSV::NS_FLASH_TEXT ),
	string_table::svt( "flash.geom", NSV::NS_FLASH_GEOM ),
	string_table::svt( "flash.net", NSV::NS_FLASH_NET ),
	string_table::svt( "flash.system", NSV::NS_FLASH_SYSTEM ),
	string_table::svt( "flash.utils", NSV::NS_FLASH_UTILS ),
	string_table::svt( "flash.events", NSV::NS_FLASH_EVENTS ),
	string_table::svt( "flash.accessibility", NSV::NS_FLASH_ACCESSIBILITY ),
	string_table::svt( "flash.media", NSV::NS_FLASH_MEDIA ),
	string_table::svt( "flash.xml", NSV::NS_FLASH_XML ),
	string_table::svt( "flash.ui", NSV::NS_FLASH_UI ),
	string_table::svt( "adobe.utils", NSV::NS_ADOBE_UTILS ),
	string_table::svt( "", NSV::INTERNAL_TYPE ),
	string_table::svt( "", NSV::INTERNAL_STACK_PARENT ),
	string_table::svt( "", NSV::INTERNAL_INTERFACES )
};

void load_strings(string_table *table, int version)
{
	if (version < 7)
	{
		//table->lower_next_group();
		table->set_insensitive();
	}

	table->insert_group(preload_names,
		sizeof (preload_names) / sizeof (string_table::svt));
}

} // namespace NSV
} // namespace gnash