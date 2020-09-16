#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <GL/gl.h>
#include <GL/glut.h>

extern double front_legs_angle_param;
extern double back_legs_angle_param;
extern double jump_param;
extern double floor_param;
extern double character_z_param;
extern double objects_rotation_param;
extern int score;
extern int game_ongoing;
extern int current_level;

void drawAxis(int n);

void makeLegAndPaw();
void clipTailBody();
void clipTailBall();
void clipSmile();

void drawBottomPolygon();
void drawSidePolygon();
void drawMainPolygon();

void generateMenu();
void generateScore();
void generateLevelResolve();

void generateTexturedPlatform();
void generateWholePlatform();
void generateCatto();
void generateMovingCatto();
void generateObjects();

void initTextures();
void initGlobalIndicator();

#endif