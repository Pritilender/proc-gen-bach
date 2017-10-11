#ifndef GLITTERING_GLAMOUR_EVENTHANDLER_HPP
#define GLITTERING_GLAMOUR_EVENTHANDLER_HPP

#include <utility>

#include "includes.hpp"
#include "Scene.hpp"

class EventHandler {
public:
    EventHandler(std::shared_ptr<Scene> s): scene(std::move(s)) {}
    virtual ~EventHandler() = default;
    virtual void handleKey(int key, int scancode, int action, int mods) = 0;

protected:
    std::shared_ptr<Scene> scene;
};

#endif //GLITTERING_GLAMOUR_EVENTHANDLER_HPP
