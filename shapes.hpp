#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <GL/gl.h>
#include <GL/glut.h>

extern double front_legs_angle_param;
extern double back_legs_angle_param;
extern double jump_param;

void drawTriPolygon(float v1x, float v1y, float v1z, 
                    float v2x, float v2y, float v2z,
                    float v3x, float v3y, float v3z);

void draw_axis(int n);

void makeLegAndPaw();
void clipTailBody();
void clipTailBall();

void generatePlatform();
void generateCatto();
void generateMovingCatto();

void initTextures();

#endif