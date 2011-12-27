Copyright (c) 2011 Chris Westin.   See ./LICENSE.txt for licensing.

This is the source to the phoenix4c library, which is based on experiments
in The Book of Brilliant Things (https://www.bookofbrilliantthings.com).

In an attempt to keep this as simple as possible, the makemake python script
in this directory will create a Makefile, which can then be used to build
the library.  It has been tested against contemporary GNU tools under cygwin.
The build options are fairly vanilla, so this should work on any linux system.

To build the library, cd to the root directory of the library project and issue:
# ./makemake
# make

To use, the include/ directory contains the header files for the library.
After building, the lib/ directory contains phoenix4c.a, which can be linked
in to your executable.

In order to avoid name collisions, library elements are prefixed with "px" or
"PX".
