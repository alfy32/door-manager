Door Manager
============

Old C++ GUI program

Built with Code Blocks. To have it just work download code blocks with mingw. The required libaraies are included with the project so it should only require code blocks with mingw to work. If it doesn't work you might have to compile fltk. 

To compile FLTK:

1. download source http://www.fltk.org/index.php
    * I'm using 1.3.2

2. have code blocks with mingw installed.
    * add mingw/bin to PATH

3. download CMake - Example, if it still exists, at http://gintasdx.althirius-studios.com/2011/08/tutorial-codeblocks-with-fltk.html
    * set source and build to fltk directory
    * On first time run you need press "Configure."
    * Choose Mingw
    * Push Generate

4. open cmd go to fltk folder and type mingw32-make

5. update fltk library files in project
