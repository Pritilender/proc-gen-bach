#ifndef GLAMOUR_CAMERA_HPP
#define GLAMOUR_CAMERA_HPP

#include <helpers/RangeIncremental.hpp>
#include "includes.hpp"
#include "helpers/Incremental.hpp"

class Camera {
public:
    explicit Camera() : positionX(0.0f, 0.5f),
                        positionZ(-100.0f, 0.5f),
                        positionY(-10.0f, -50.0f, -1.0f, 0.5f),
                        angleX(20, 5),
                        angleY(0, 5), angleZ(0, 5) {}

    Camera(const Incremental<float> &positionX,
           const Incremental<float> &positionY,
           const Incremental<float> &positionZ,
           const Incremental<float> &angleX,
           const Incremental<float> &angleY,
           const Incremental<float> &angleZ) : positionX(positionX),
                                               positionZ(positionZ),
                                               positionY(positionY, 1.0f, 20.0f),
                                               angleX(angleX),
                                               angleY(angleY),
                                               angleZ(angleZ) {}

    glm::mat4 getViewMatrix() {
        glm::mat4 view(1.0f);
        auto cameraPosition =
            glm::vec3(static_cast<float>(positionX), static_cast<float>(positionY), static_cast<float>(positionZ));
        view = glm::rotate(view, glm::radians(static_cast<float>(angleZ)), glm::vec3(0, 0, 1));
        view = glm::rotate(view, glm::radians(static_cast<float>(angleX)), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(static_cast<float>(angleY)), glm::vec3(0, 1, 0));
        view = glm::translate(view, cameraPosition);
        return view;
    }

    Incremental<float> positionX, positionZ;
    RangeIncremental<float> positionY;
    Incremental<float> angleX, angleY, angleZ;
};


#endif //GLAMOUR_CAMERA_HPP
