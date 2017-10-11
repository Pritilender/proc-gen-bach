#ifndef GLAMOUR_SCENE_HPP
#define GLAMOUR_SCENE_HPP


#include <Camera.hpp>
#include <random>

class Scene {
public:
    Scene(int w, int h): width(w), height(h) {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.4f, 0.7f, 0.95f, 1.0f);
    }
    Scene() = delete;
    virtual ~Scene() = default;
    virtual void render() = 0;
    virtual void redraw() = 0;
    Camera camera;
protected:

    int width;
    int height;
};


#endif //GLAMOUR_SCENE_HPP
