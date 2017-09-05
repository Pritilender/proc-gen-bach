#pragma once

// System Headers
#include <glad/glad.h>

// GLM
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// More System Headers
#include <GLFW/glfw3.h>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// Freetype 2
#include <ft2build.h>
#include FT_FREETYPE_H "freetype/freetype.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
