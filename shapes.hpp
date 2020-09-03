#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <GL/gl.h>
#include <GL/glut.h>

void drawTriPolygon(float v1x, float v1y, float v1z, 
                    float v2x, float v2y, float v2z,
                    float v3x, float v3y, float v3z);

void draw_axis(int n);
void generatePlatform();
void generateCatto();

void initTextures();

#endif