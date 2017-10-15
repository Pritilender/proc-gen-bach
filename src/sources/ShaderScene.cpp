#include <FragmentShader.hpp>
#include <ShaderSquare.hpp>
#include "ShaderScene.hpp"

using namespace std;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using glm::radians;

ShaderScene::ShaderScene(int w, int h) : NoiseScene(w,
                                                    h,
                                                    XMAX,
                                                    RESOLUTION,
                                                    std::make_unique<ShaderSquare>(XMAX, RESOLUTION)) { }

void ShaderScene::redraw() {
    landscape->uploadNewData();
    landscape->printInfo();
}

