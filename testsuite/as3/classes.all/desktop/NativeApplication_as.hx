// NativeApplication_as.hx:  ActionScript 3 "NativeApplication" class, for Gnash.
//
// Generated by gen-as3.sh on: 20090514 by "rob". Remove this
// after any hand editing loosing changes.
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
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

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.desktop.NativeApplication;
import flash.display.MovieClip;
#else
import flash.NativeApplication;
import flash.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class NativeApplication_as {
    static function main() {
        var x1:NativeApplication = new NativeApplication();

        // Make sure we actually get a valid class        
        if (x1 != null) {
            DejaGnu.pass("NativeApplication class exists");
        } else {
            DejaGnu.fail("NativeApplication lass doesn't exist");
        }
// Tests to see if all the properties exist. All these do is test for
// existance of a property, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.activeWindow == NativeWindow) {
	    DejaGnu.pass("NativeApplication::activeWindow property exists");
	} else {
	    DejaGnu.fail("NativeApplication::activeWindow property doesn't exist");
	}
	if (x1.applicationDescriptor == XML) {
	    DejaGnu.pass("NativeApplication::applicationDescriptor property exists");
	} else {
	    DejaGnu.fail("NativeApplication::applicationDescriptor property doesn't exist");
	}
	if (x1.applicationID == null) {
	    DejaGnu.pass("NativeApplication::applicationID property exists");
	} else {
	    DejaGnu.fail("NativeApplication::applicationID property doesn't exist");
	}
	if (x1.autoExit == false) {
	    DejaGnu.pass("NativeApplication::autoExit property exists");
	} else {
	    DejaGnu.fail("NativeApplication::autoExit property doesn't exist");
	}
	if (x1.icon == InteractiveIcon) {
	    DejaGnu.pass("NativeApplication::icon property exists");
	} else {
	    DejaGnu.fail("NativeApplication::icon property doesn't exist");
	}
	if (x1.idleThreshold == 0) {
	    DejaGnu.pass("NativeApplication::idleThreshold property exists");
	} else {
	    DejaGnu.fail("NativeApplication::idleThreshold property doesn't exist");
	}
	if (x1.menu == NativeMenu) {
	    DejaGnu.pass("NativeApplication::menu property exists");
	} else {
	    DejaGnu.fail("NativeApplication::menu property doesn't exist");
	}
	if (x1.nativeApplication == NativeApplication) {
	    DejaGnu.pass("NativeApplication::nativeApplication property exists");
	} else {
	    DejaGnu.fail("NativeApplication::nativeApplication property doesn't exist");
	}
	if (x1.openedWindows == 0) {
	    DejaGnu.pass("NativeApplication::openedWindows property exists");
	} else {
	    DejaGnu.fail("NativeApplication::openedWindows property doesn't exist");
	}
	if (x1.publisherID == null) {
	    DejaGnu.pass("NativeApplication::publisherID property exists");
	} else {
	    DejaGnu.fail("NativeApplication::publisherID property doesn't exist");
	}
	if (x1.runtimePatchLevel == uint) {
	    DejaGnu.pass("NativeApplication::runtimePatchLevel property exists");
	} else {
	    DejaGnu.fail("NativeApplication::runtimePatchLevel property doesn't exist");
	}
	if (x1.runtimeVersion == null) {
	    DejaGnu.pass("NativeApplication::runtimeVersion property exists");
	} else {
	    DejaGnu.fail("NativeApplication::runtimeVersion property doesn't exist");
	}
	if (x1.startAtLogin == false) {
	    DejaGnu.pass("NativeApplication::startAtLogin property exists");
	} else {
	    DejaGnu.fail("NativeApplication::startAtLogin property doesn't exist");
	}
	if (x1.supportsDockIcon == false) {
	    DejaGnu.pass("NativeApplication::supportsDockIcon property exists");
	} else {
	    DejaGnu.fail("NativeApplication::supportsDockIcon property doesn't exist");
	}
	if (x1.supportsMenu == false) {
	    DejaGnu.pass("NativeApplication::supportsMenu property exists");
	} else {
	    DejaGnu.fail("NativeApplication::supportsMenu property doesn't exist");
	}
	if (x1.supportsSystemTrayIcon == false) {
	    DejaGnu.pass("NativeApplication::supportsSystemTrayIcon property exists");
	} else {
	    DejaGnu.fail("NativeApplication::supportsSystemTrayIcon property doesn't exist");
	}
	if (x1.timeSinceLastUserInput == 0) {
	    DejaGnu.pass("NativeApplication::timeSinceLastUserInput property exists");
	} else {
	    DejaGnu.fail("NativeApplication::timeSinceLastUserInput property doesn't exist");
	}

// Tests to see if all the methods exist. All these do is test for
// existance of a method, and don't test the functionality at all. This
// is primarily useful only to test completeness of the API implementation.
	if (x1.activate == null) {
	    DejaGnu.pass("NativeApplication::activate() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::activate() method doesn't exist");
	}
	if (x1.addEventListener == null) {
	    DejaGnu.pass("NativeApplication::addEventListener() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::addEventListener() method doesn't exist");
	}
	if (x1.clear == false) {
	    DejaGnu.pass("NativeApplication::clear() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::clear() method doesn't exist");
	}
	if (x1.copy == false) {
	    DejaGnu.pass("NativeApplication::copy() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::copy() method doesn't exist");
	}
	if (x1.cut == false) {
	    DejaGnu.pass("NativeApplication::cut() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::cut() method doesn't exist");
	}
	if (x1.dispatchEvent == false) {
	    DejaGnu.pass("NativeApplication::dispatchEvent() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::dispatchEvent() method doesn't exist");
	}
	if (x1.exit == null) {
	    DejaGnu.pass("NativeApplication::exit() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::exit() method doesn't exist");
	}
	if (x1.getDefaultApplication == null) {
	    DejaGnu.pass("NativeApplication::getDefaultApplication() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::getDefaultApplication() method doesn't exist");
	}
	if (x1.isSetAsDefaultApplication == false) {
	    DejaGnu.pass("NativeApplication::isSetAsDefaultApplication() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::isSetAsDefaultApplication() method doesn't exist");
	}
	if (x1.paste == false) {
	    DejaGnu.pass("NativeApplication::paste() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::paste() method doesn't exist");
	}
	if (x1.removeAsDefaultApplication == null) {
	    DejaGnu.pass("NativeApplication::removeAsDefaultApplication() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::removeAsDefaultApplication() method doesn't exist");
	}
	if (x1.removeEventListener == null) {
	    DejaGnu.pass("NativeApplication::removeEventListener() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::removeEventListener() method doesn't exist");
	}
	if (x1.selectAll == false) {
	    DejaGnu.pass("NativeApplication::selectAll() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::selectAll() method doesn't exist");
	}
	if (x1.setAsDefaultApplication == null) {
	    DejaGnu.pass("NativeApplication::setAsDefaultApplication() method exists");
	} else {
	    DejaGnu.fail("NativeApplication::setAsDefaultApplication() method doesn't exist");
	}

        // Call this after finishing all tests. It prints out the totals.
        DejaGnu.done();
    }
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

