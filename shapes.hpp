#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <GL/gl.h>
#include <GL/glut.h>

extern double front_legs_angle_param;
extern double back_legs_angle_param;
extern double jump_param;
extern double floor_param;
extern double character_z_param;

void draw_axis(int n);

void makeLegAndPaw();
void clipTailBody();
void clipTailBall();
void clipSmile();

void drawBottomPolygon();
void drawSidePolygon();
void drawMainPolygon();

void generateMenu();

void generateTexturedPlatform();
void generateWholePlatform();
void generateCatto();
void generateMovingCatto();

void initTextures();

#endif