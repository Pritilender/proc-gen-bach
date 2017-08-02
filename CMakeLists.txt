cmake_minimum_required(VERSION 3.0)
project(OpenGL_Demos)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Ensure C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

# GLFW build options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

# Assimp build options
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(vendor/assimp)

# Bullet build options
option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory(vendor/bullet)

if(MSVC)
	# Set warning level 4 when using Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	# Set compiler flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    if(NOT WIN32)
		# GLAD requires libdl on Unix systems
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(core/Headers/
                    vendor/assimp/include/
                    vendor/bullet/src/
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

file(GLOB GLAD_SOURCE vendor/glad/src/glad.c)
file(GLOB_RECURSE PROJECT_HEADERS core/*.h)
file(GLOB_RECURSE PROJECT_SOURCES core/*.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("GLAD"	   FILES ${GLAD_SOURCE})

# GLFW_INCLUDE_NONE tells GLFW not to include OpenGL headers.
# This flag is used when using GLFW with an extension loading library.
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

# Create the executable
add_executable(${PROJECT_NAME}  ${PROJECT_SOURCES}
								${PROJECT_HEADERS}
								${PROJECT_CONFIGS}
								${GLAD_SOURCE})
# Link dependencies
target_link_libraries(${PROJECT_NAME}   assimp
										glfw
										${GLFW_LIBRARIES}
										${GLAD_LIBRARIES}
										BulletDynamics
										BulletCollision
										LinearMath)

set_target_properties(${PROJECT_NAME} PROPERTIES

	# Output to lib directory
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib

	# Output to bin directory
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin

	# Disable all warnings
	CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w"
)

