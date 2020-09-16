#ifndef HELPER_HPP
#define HELPER_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include <string>
#include <vector>

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

// Drawing a string on a certain coordinates
void drawRomanString(char *str, double x, double y, double z);

// 15 randomly generated numbers in a range  
std::vector<double> generateRangedNumbers(double min, double max);

// 1 randomly generated number in (0, 1)
double generateRNZO();

// Collision detection for cat and object
bool isCollision(double catZ, double objX, double objZ);

#endif