#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <GL/gl.h>
#include <GL/glut.h>

void initLights();
void initMaterial();

void onDisplay(void);
void onKeyboard(unsigned char key, int x, int y);
void onKeyboardSpecial(int key, int x, int y); 
void onReshape(int width, int height);

#endif