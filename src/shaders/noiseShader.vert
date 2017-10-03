/* https://github.com/ashima/webgl-noise/blob/master/src/classicnoise2D.glsl */
/* https://github.com/ashima/webgl-noise/issues/9 */

#version 440 core

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;

uniform int Resolution;
uniform float XMax;

uniform float Frequency;
uniform float Lacunarity;
uniform float Persistence;
uniform int Octaves;
uniform int Seed;

out vec3 Position;
out vec2 UV;
out vec3 Normal;

float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//
// GLSL textureless classic 2D noise "cnoise",
// with an RSL-style periodic variant "pnoise".
// Author:  Stefan Gustavson (stefan.gustavson@liu.se)
// Version: 2011-08-22
//
// Many thanks to Ian McEwan of Ashima Arts for the
// ideas for permutation and gradient selection.
//
// Copyright (c) 2011 Stefan Gustavson. All rights reserved.
// Distributed under the MIT license. See LICENSE file.
// https://github.com/stegu/webgl-noise
//

vec4 mod289(vec4 x)
{
  return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec4 permute(vec4 x)
{
  return mod289(((x*34.0)+1.0)*x);
}

vec4 taylorInvSqrt(vec4 r)
{
  return 1.79284291400159 - 0.85373472095314 * r;
}

vec2 fade(vec2 t) {
  return t*t*t*(t*(t*6.0-15.0)+10.0);
}

// Classic Perlin noise
float cnoise(vec2 P, int seed)
{
  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
  Pi = mod289(Pi); // To avoid truncation effects in permutation
  vec4 ix = Pi.xzxz;
  vec4 iy = Pi.yyww;
  vec4 fx = Pf.xzxz;
  vec4 fy = Pf.yyww;

  vec4 i = permute(permute(ix) + iy);
  i = permute(i + vec4(rand(vec2(seed))));

  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
  vec4 gy = abs(gx) - 0.5 ;
  vec4 tx = floor(gx + 0.5);
  gx = gx - tx;

  vec2 g00 = vec2(gx.x,gy.x);
  vec2 g10 = vec2(gx.y,gy.y);
  vec2 g01 = vec2(gx.z,gy.z);
  vec2 g11 = vec2(gx.w,gy.w);

  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
  g00 *= norm.x;
  g01 *= norm.y;
  g10 *= norm.z;
  g11 *= norm.w;

  float n00 = dot(g00, vec2(fx.x, fy.x));
  float n10 = dot(g10, vec2(fx.y, fy.y));
  float n01 = dot(g01, vec2(fx.z, fy.z));
  float n11 = dot(g11, vec2(fx.w, fy.w));

  vec2 fade_xy = fade(Pf.xy);
  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
  return 2.3 * n_xy;
}

// Classic Perlin noise, periodic variant
float pnoise(vec2 P, vec2 rep, float seed)
{
  vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
  vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
  Pi = mod(Pi, rep.xyxy); // To create noise with explicit period
  Pi = mod289(Pi);        // To avoid truncation effects in permutation
  vec4 ix = Pi.xzxz;
  vec4 iy = Pi.yyww;
  vec4 fx = Pf.xzxz;
  vec4 fy = Pf.yyww;

  vec4 i = permute(permute(ix) + iy);
  i = permute(mod289(i + vec4(seed)));

  vec4 gx = fract(i * (1.0 / 41.0)) * 2.0 - 1.0 ;
  vec4 gy = abs(gx) - 0.5 ;
  vec4 tx = floor(gx + 0.5);
  gx = gx - tx;

  vec2 g00 = vec2(gx.x,gy.x);
  vec2 g10 = vec2(gx.y,gy.y);
  vec2 g01 = vec2(gx.z,gy.z);
  vec2 g11 = vec2(gx.w,gy.w);

  vec4 norm = taylorInvSqrt(vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11)));
  g00 *= norm.x;
  g01 *= norm.y;
  g10 *= norm.z;
  g11 *= norm.w;

  float n00 = dot(g00, vec2(fx.x, fy.x));
  float n10 = dot(g10, vec2(fx.y, fy.y));
  float n01 = dot(g01, vec2(fx.z, fy.z));
  float n11 = dot(g11, vec2(fx.w, fy.w));

  vec2 fade_xy = fade(Pf.xy);
  vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
  float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
  return 2.3 * n_xy;
}

// Fractal Perlin noise implementation

float fractalNoise(vec2 p, float freq, float lac, float pers, float oct, int seed) {
    p *= freq;
    float sum = cnoise(p, seed);
    float amp = 1;
    int i = 0;
    for (i; i < oct; i++) {
        p *= lac;
        amp *= pers;
        sum += cnoise(p, seed) * amp;
    }
    return sum > 0 ?  sum * 15.0 : sum * 5.0;
}

vec3 calculateNormal(vec3 p, float freq, float lac, float pers, float oct, int seed) {
    float offset = 0.0001; // small displacement
    vec2 xOff = p.xz + vec2(offset, 0.0);
    vec2 zOff = p.xz + vec2(0.0, offset);
    float xY = fractalNoise(xOff, freq, lac, pers, oct, seed);
    float zY = fractalNoise(zOff, freq, lac, pers, oct, seed);
    vec3 xTan = vec3(xOff.x, xY, xOff.y);
    vec3 zTan = vec3(zOff.x, zY, zOff.y);
    vec3 xTanVec = xTan - p;
    vec3 zTanVec = zTan - p;
    return normalize(cross(xTanVec, zTanVec));
}

void main() {
    int id = gl_VertexID;
    vec3 position;
    float step = XMax / (Resolution - 1);
    float x = (id % Resolution) * step;
    float z = (id / Resolution) * step;
    float y = fractalNoise(vec2(x, z), Frequency, Lacunarity, Persistence, Octaves, Seed);
    Position = vec3(x, y, z);
//    UV = vec2((id << 1) & 2, id & 2);
    UV = vec2(Position.x / XMax * (Resolution - 1), Position.z / XMax * (Resolution - 1));
    Normal = NormalMatrix * calculateNormal(Position, Frequency, Lacunarity, Persistence, Octaves, Seed);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0);
}
