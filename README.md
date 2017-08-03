# OpenGL Template

This is a template for OpenGL projects, forked from [Glitter](https://github.com/polytonic/Glitter) with improvements.

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