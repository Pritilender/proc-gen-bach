#ifndef GLAMOUR_PERLINVERTEXGENERATOR_HPP
#define GLAMOUR_PERLINVERTEXGENERATOR_HPP

#include "includes.hpp"
#include "VertexGenerator.hpp"

class PerlinVertexGenerator: public VertexGenerator {
public:
    explicit PerlinVertexGenerator(const FastNoise& noise): VertexGenerator(noise) {};
    glm::vec3 generateVertex(const float x, const float z) override {
        float y = noise.GetNoise(x, z);
//        float y = fractalNoise(glm::vec2(x, z), 0.01f, 1.7f, 0.5f, 5, 1337);
        if (y > 0) {
            y *= 15.0f;
        } else {
            y *= 5.0f;
        }
//        float peakFactor = 1.8f;
//        float terracingFactor = 10;
//        y = powf(y, 1.2f) * 10;
        // water cut-off
//        if (y < 0) {
//            y = -0.001f;
//        } else {
            // this can be tweaked so we can force a certain type of a terrain
//            y = powf(y, peakFactor);
//            y = roundf(y * terracingFactor) / terracingFactor;
//        }
        return glm::vec3(x, y, z);
    }

//    float rand(glm::vec2 co){
//        return fract(sinf(glm::dot(glm::vec2(co.x, co.y) ,glm::vec2(12.9898f, 78.233f))) * 43758.5453f);
//    }
//
//    float fract(float x) {
//        return x - (int)x;
//    }
//
//    glm::vec4 mod289(glm::vec4 x)
//    {
//        return x - floor(x * (1.0f / 289.0f)) * 289.0f;
//    }
//
//    glm::vec4 permute(glm::vec4 x)
//    {
//        return mod289(((x*34.0f)+1.0f)*x);
//    }
//
//    glm::vec4 taylorInvSqrt(glm::vec4 r)
//    {
//        return 1.79284291400159f - 0.85373472095314f * r;
//    }
//
//    glm::vec2 fade(glm::vec2 t) {
//        return t*t*t*(t*(t*6.0f-15.0f)+10.0f);
//    }
//
//// Classic Perlin noise
//    float cnoise(glm::vec2 P, int seed)
//    {
//        glm::vec4 Pi = glm::vec4(floor(P.x), floor(P.y), floor(P.x), floor(P.y)) + glm::vec4(0.0, 0.0, 1.0, 1.0);
//        glm::vec4 Pf = glm::vec4(fract(P.x), fract(P.y), fract(P.x), fract(P.y)) - glm::vec4(0.0, 0.0, 1.0, 1.0);
//        Pi = mod289(Pi); // To avoid truncation effects in permutation
//        glm::vec4 ix = glm::vec4(Pi.x, Pi.z, Pi.x, Pi.z);
//        glm::vec4 iy = glm::vec4(Pi.y, Pi.y, Pi.w, Pi.w);
//        glm::vec4 fx = glm::vec4(Pf.x, Pf.z, Pf.x, Pf.z);
//        glm::vec4 fy = glm::vec4(Pf.y, Pf.y, Pf.w, Pf.w);
//
//        glm::vec4 i = permute(permute(ix) + iy);
//        i = permute(i + glm::vec4(rand(glm::vec2(seed))));
//
//        glm::vec4 gx = glm::vec4(fract(i.x * (1.0f / 41.0f)),
//                                 fract(i.y * (1.0f / 41.0f)),
//                                 fract(i.z * (1.0f / 41.0f)),
//                                 fract(i.w * (1.0f / 41.0f))) * 2.0f - 1.0f ;
//        glm::vec4 gy = abs(gx) - 0.5f;
//        glm::vec4 tx = floor(gx + 0.5f);
//        gx = gx - tx;
//
//        glm::vec2 g00 = glm::vec2(gx.x,gy.x);
//        glm::vec2 g10 = glm::vec2(gx.y,gy.y);
//        glm::vec2 g01 = glm::vec2(gx.z,gy.z);
//        glm::vec2 g11 = glm::vec2(gx.w,gy.w);
//
//        glm::vec4 norm = taylorInvSqrt(glm::vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
//        g00 *= norm.x;
//        g01 *= norm.y;
//        g10 *= norm.z;
//        g11 *= norm.w;
//
//        float n00 = glm::dot(glm::vec2(g00), glm::vec2(fx.x, fy.x));
//        float n10 = glm::dot(g10, glm::vec2(fx.y, fy.y));
//        float n01 = glm::dot(g01, glm::vec2(fx.z, fy.z));
//        float n11 = glm::dot(g11, glm::vec2(fx.w, fy.w));
//
//        glm::vec2 fade_xy = fade(glm::vec2(Pf.x, Pf.y));
//        glm::vec2 n_x = glm::mix(glm::vec2(n00, n01), glm::vec2(n10, n11), fade_xy.x);
//        float n_xy = glm::mix(n_x.x, n_x.y, fade_xy.y);
//        return 2.3f * n_xy;
//    }
//
//    float fractalNoise(glm::vec2 p, float freq, float lac, float pers, float oct, int seed) {
//        p *= freq;
//        float sum = cnoise(p, seed);
//        float amp = 1;
//        int i = 0;
//        for (i; i < oct; i++) {
//            p *= lac;
//            amp *= pers;
//            sum += cnoise(p, seed) * amp;
//        }
//        return sum > 0.f ?  sum * 15.0f : sum * 5.0f;
//    }
};


#endif //GLAMOUR_PERLINVERTEXGENERATOR_HPP
