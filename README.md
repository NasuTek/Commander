NasuTek Commander
=================
A Total Commander-like application written in Qt for Windows, Linux, and Mac OS X. 
It is a continuation of Beesoft Commander.

Building Requirements
---------------------
NasuTek Commander uses CMake to automate building, check for libraries, etc. We
also use Qt 4 as the widget toolkit. This allows you to use MinGW or Visual
Studio on Windows, and any other IDE/Compiler on Linux.

How to Build?
-------------
1. Run CMake
2. On Linux type make, on Windows if using MinGW type mingw32-make.
3. You should now have a nc.exe in your output path.

Creating a Package
------------------
We use CPack to create distribution packages. To create the package, type 'make package'

Thanks and Credits
------------------
* Thanks to Piotr Pszczolkowski for creating Beesoft Commander, the basis of NasuTek Commander.
