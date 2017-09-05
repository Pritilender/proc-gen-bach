cmake_minimum_required(VERSION 3.0)
project(glamour)

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Create the compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

# GLFW build options
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

# Freetype2 build options
add_subdirectory(vendor/freetype2)

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

include_directories(src/headers
					vendor/freetype2/include/
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

# Create file globs
file(GLOB GLAD_SOURCE vendor/glad/src/glad.c)
file(GLOB_RECURSE PROJECT_HEADERS src/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

# Use file globs to create filters for Visual Studio
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Configs" FILES ${PROJECT_CONFIGS})
source_group("Glad"	   FILES ${GLAD_SOURCE})

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
target_link_libraries(${PROJECT_NAME}   glfw
										freetype
                                        ${GLFW_LIBRARIES}
                                        ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    # Output to bin directory
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Visual Studio specific settings
# Requires CMake 3.8+
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # Hide the console in Visual Studio projects in debug and release
    set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
		LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

    # Copy resources folder to output folder
	# This would be a good place to store shader source files and art assets
    add_custom_command(TARGET   ${PROJECT_NAME} POST_BUILD
                                COMMAND ${CMAKE_COMMAND} -E copy_directory
                                ${CMAKE_SOURCE_DIR}/src/resources
                                $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)
endif(MSVC)
