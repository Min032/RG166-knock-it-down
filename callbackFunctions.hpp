#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <GL/gl.h>
#include <GL/glut.h>

void initLights();
void initMaterial();
void initParams();

void onDisplay(void);
void onKeyboard(unsigned char key, int x, int y);
void onKeyboardSpecial(int key, int x, int y); 
void onReshape(int width, int height);
void on_timer0(int id);
void on_timer1(int id);


#endif