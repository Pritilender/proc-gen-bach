#ifndef GLITTERING_GLAMOUR_NOISESCENE_HPP
#define GLITTERING_GLAMOUR_NOISESCENE_HPP

#include "Scene.hpp"

#include <utility>
#include "NoiseSquare.hpp"

class NoiseScene : public Scene {
public:
    NoiseScene(int w, int h, int r, float xM, std::unique_ptr<NoiseSquare> l) : Scene(w, h), landscape(std::move(l)) {
        landscape->resolution = r;
        landscape->xMax = xM;
    }

    void setFreq(float f) {
        landscape->setFreq(f);
    }

    void setLacunarity(float l) {
        landscape->setLacunarity(l);
    }

    void setPersistence(float p) {
        landscape->setPersistence(p);
    }

    void setOctaves(int o) {
        landscape->setOctaves(o);
    }

    void generateSeed() {
        landscape->generateSeed();
    }

    void forwards() {
        landscape->zOffset -= 5.f;
    };

    void backwards() {
        landscape->zOffset += 5.f;
    };

    void left() {
        landscape->xOffset -= 5.f;
    }

    void right() {
        landscape->xOffset += 5.f;
    }

    std::unique_ptr<NoiseSquare> landscape;
};

#endif //GLITTERING_GLAMOUR_NOISESCENE_HPP
