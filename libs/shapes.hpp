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
extern int		score;
extern int		game_ongoing;
extern int		current_level;
extern int		game_finished;

// Axis of n length
void drawAxis (int n);

// Parts of cat
void makeLegAndPaw ();
void clipTailBody ();
void clipTailBall ();
void clipSmile ();

// Parts of floor
void drawBottomPolygon ();
void drawSidePolygon ();
void drawMainPolygon ();

// Misc stuff
void generateMenu ();
void generateScore ();
void generateLevelResolve ();
void generateFinisher ();

void generateTexturedPlatform ();
void generateWholePlatform ();
void generateCatto ();
void generateMovingCatto ();
void generateObjects ();

void initTextures ();
void initGlobalIndicator ();

#endif