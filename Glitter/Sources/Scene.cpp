#include <Square.hpp>
#include <Triangle.hpp>
#include "Scene.hpp"

using namespace std;

Scene::Scene() {
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);

    setupProgram();
    setupTextures();

    drawables.push_back(unique_ptr<Drawable>(new Square));
//    drawables.push_back(unique_ptr<Drawable>(new Triangle));
}

void Scene::setupProgram() {
    Shader vertex("vertexShaderSquare.vert");
    Shader fragment("fragmentShaderSquare.frag");

    program.reset(new ShaderProgram());
    program->attachShader(vertex)
        ->attachShader(fragment);

    program->link();
}

void Scene::setupTextures() {
    textures.push_back(unique_ptr<Texture>(new Texture("awesomeface.png")));
    textures.push_back(unique_ptr<Texture>(new Texture("container.jpg")));

    program->use();
    program->setUniform("texture1", 0)
        ->setUniform("texture2", 1);
}

void Scene::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < textures.size(); ++i) {
        textures[i]->bindToActive(GL_TEXTURE0 + i);
    }
    program->use();

    for (auto &d : drawables) {
        d->draw();
    }
}
