#ifndef GLAMOUR_CAMERA_HPP
#define GLAMOUR_CAMERA_HPP

#include "includes.hpp"
#include "helpers/Incremental.hpp"

class Camera {
public:
    explicit Camera() : positionX(0.0f, 0.5f),
                        positionY(0.0f, 0.5f),
                        positionZ(-5.0f, 0.5f),
                        angleX(45, 5),
                        angleY(45, 5), angleZ(0, 5) {}

    Camera(const Incremental<float> &positionX,
           const Incremental<float> &positionY,
           const Incremental<float> &positionZ,
           const Incremental<float> &angleX,
           const Incremental<float> &angleY,
           const Incremental<float> &angleZ) : positionX(positionX),
                                               positionY(positionY),
                                               positionZ(positionZ),
                                               angleX(angleX),
                                               angleY(angleY),
                                               angleZ(angleZ) {}

    glm::mat4 getViewMatrix() {
        glm::mat4 view(1.0f);
        auto cameraPosition =
            glm::vec3(static_cast<float>(positionX), static_cast<float>(positionY), static_cast<float>(positionZ));
        view = glm::translate(view, cameraPosition);
        view = glm::rotate(view, glm::radians(static_cast<float>(angleX)), glm::vec3(1, 0, 0));
        view = glm::rotate(view, glm::radians(static_cast<float>(angleY)), glm::vec3(0, 1, 0));
        view = glm::rotate(view, glm::radians(static_cast<float>(angleZ)), glm::vec3(0, 0, 1));
        return view;
    }

    Incremental<float> positionX, positionY, positionZ;
    Incremental<float> angleX, angleY, angleZ;
};


#endif //GLAMOUR_CAMERA_HPP
