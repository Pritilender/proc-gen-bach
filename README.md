# Glamour

This is a template for OpenGL projects, forked from [Glitter](https://github.com/polytonic/Glitter) with improvements.

## Improvements

* Added [Freetype2](https://www.freetype.org/).
* Added [Boxer](https://github.com/aaronmjacobs/Boxer) for cross-platform messageboxes.
* Generated an OpenGL 4.6 function loader using the [glad](http://glad.dav1d.de/) web service instead of the outdated c-branch on the original repo.
* All submodules have been pointed toward their latest stable release.
* Output goes to a `bin` directory at the project root.
* A `resources` folder has been added that will be copied to the `bin` folder along with the executable project output as a post build event. This is a good place to store shader source files, art assets, or any other files that will need to be loaded by your program.
* The console window will now be hidden by default for Visual Studio projects.
* The startup project will now be the main executable project by default for Visual Studio projects.
* `C++14` is set with [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/v3.1/variable/CMAKE_CXX_STANDARD.html) in the `CMakeLists.txt` file. This can be changed to whichever standard your project requires.
* Added a default [`.editorconfig`](http://editorconfig.org/) file.
* [`USE_FOLDERS`](https://cmake.org/cmake/help/v3.0/prop_gbl/USE_FOLDERS.html) is now on by default in the `CMakeLists.txt` so that CMake targets will be placed in their own folder.



## Instructions

```bash
git clone --recursive https://github.com/matthewjberger/opengl_template
cd opengl_template
mkdir build
cd build

# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 14" ..
cmake -G "Visual Studio 14 Win64" ..
```
