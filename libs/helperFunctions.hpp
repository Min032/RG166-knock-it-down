#ifndef HELPER_HPP
#define HELPER_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include <string>
#include <vector>

void setMaterialColor (GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

// Drawing a string on a certain coordinates
void drawRomanString (char *str, double x, double y, double z);

// 15 randomly generated numbers in a range
auto generateRangedNumbers (double min, double max) -> std::vector<double>;

// 1 randomly generated number in (0, 1)
auto generateRNZO () -> double;

// Collision detection for cat and object
auto isCollision (double catZ, double objX, double objZ) -> bool;

#endif