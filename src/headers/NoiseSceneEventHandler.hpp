#ifndef GLITTERING_GLAMOUR_NOISESCENEEVENTHANDLER_HPP
#define GLITTERING_GLAMOUR_NOISESCENEEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "NoiseScene.hpp"

class NoiseSceneEventHandler : public EventHandler {
public:
    explicit NoiseSceneEventHandler(const std::shared_ptr<NoiseScene> &ns) : EventHandler(ns) {};

    void handleKey(int key, int scancode, int action, int mods) override {
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            auto scene = std::static_pointer_cast<NoiseScene>(this->scene);
            switch (key) {
                case GLFW_KEY_R: {
                    ++scene->camera.positionY;
                    return; // no need for redraw
                }
                case GLFW_KEY_F: {
                    --scene->camera.positionY;
                    return; // no need for redraw
                }
                case GLFW_KEY_W: {
                    scene->forwards();
                    break;
                }
                case GLFW_KEY_S: {
                    scene->backwards();
                    break;
                }
                case GLFW_KEY_A: {
                    scene->left();
                    break;
                }
                case GLFW_KEY_D: {
                    scene->right();
                    break;
                }
                case GLFW_KEY_UP: {
                    ++scene->camera.angleX;
                    return;
                }
                case GLFW_KEY_DOWN: {
                    --scene->camera.angleX;
                    return;
                }
                case GLFW_KEY_LEFT: {
                    ++scene->camera.angleY;
                    return;
                }
                case GLFW_KEY_RIGHT: {
                    --scene->camera.angleY;
                    return;
                }
                case GLFW_KEY_T: {
                    scene->setFreq(0.002f);
                    break;
                }
                case GLFW_KEY_G: {
                    scene->setFreq(-0.002f);
                    break;
                }
                case GLFW_KEY_Y: {
                    scene->setLacunarity(0.05f);
                    break;
                }
                case GLFW_KEY_H: {
                    scene->setLacunarity(-0.05f);
                    break;
                }
                case GLFW_KEY_U: {
                    scene->setPersistence(0.02f);
                    break;
                }
                case GLFW_KEY_J: {
                    scene->setPersistence(-0.02f);
                    break;
                }
                case GLFW_KEY_I: {
                    scene->setOctaves(1);
                    break;
                }
                case GLFW_KEY_K: {
                    scene->setOctaves(-1);
                    break;
                }
                case GLFW_KEY_SPACE: {
                    scene->generateSeed();
                    break;
                }
                default:
                    return;
            }
            scene->redraw();
        }
    }
};

#endif //GLITTERING_GLAMOUR_NOISESCENEEVENTHANDLER_HPP
