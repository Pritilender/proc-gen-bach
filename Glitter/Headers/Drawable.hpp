#ifndef GLITTER_DRAWABLE_HPP
#define GLITTER_DRAWABLE_HPP

/**
 * Abstract class for all drawable elements of the scene.
 */
class Drawable {
public:
    /**
     * Figure should release all buffers that it holds in its destructor.
     */
    virtual ~Drawable() {};
    /**
     * Bind all buffers and draw elements.
     */
    virtual void draw() = 0;
};


#endif //GLITTER_DRAWABLE_HPP
