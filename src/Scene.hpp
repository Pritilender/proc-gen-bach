#ifndef GLAMOUR_SCENE_HPP
#define GLAMOUR_SCENE_HPP


#include <Camera.hpp>
#include <random>

class Scene {
public:
    Scene(int w, int h): width(w), height(h), rd(), gen(rd()) {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }
    virtual ~Scene() = default;
    virtual void render() = 0;

    void setFreq(float f) {
        freq += f;
        redraw();
    }

    void setLacunarity(float l) {
        lacunarity += l;
        redraw();
    }

    void setPersistence(float p) {
        persistence += p;
        redraw();
    }

    void setOctaves(int o) {
        octaves += o;
        redraw();
    }

    void setXMax(float xm) {
        xMax += xm;
        redraw();
    }
    void generateSeed() {
        std::uniform_int_distribution<> dis(0, 10000);
        seed = dis(gen);
        redraw();
    }
    Camera camera;
protected:
    virtual void redraw() = 0;
    virtual void setupProgram() = 0;
    virtual void setupTexture() = 0;
    void printInfo() {
        std::cout << "==========" << std::endl;
        std::cout << "Seed: " << seed << std::endl;
        std::cout << "Noise frequency: " << freq << std::endl;
        std::cout << "Noise lacunarity: " << lacunarity << std::endl;
        std::cout << "Noise persistence: " << persistence << std::endl;
        std::cout << "Number of octaves: " << octaves << std::endl;
        std::cout << "==========" << std::endl;
    }

    int width;
    int height;
    std::random_device rd;
    std::mt19937 gen;
    float freq = 0.01f;
    float lacunarity = 1.7f;
    float persistence = 0.5f; // gain
    int octaves = 5;
    int seed = 1337;
    float xMax = 500.0f;
    int resolution = 2000;
};


#endif //GLAMOUR_SCENE_HPP
