#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <GL/gl.h>
#include <GL/glut.h>

void initLights ();
void initMaterial ();
// Reset the game to starting state
void initParams ();

void onDisplay ();
void onKeyboard (unsigned char key, int x, int y);
void onKeyboardSpecial (int key, int x, int y);
void onReshape (int width, int height);

// Timer for game ongoing parameters
void on_timer0 (int id);
// Timer for menu state
void on_timer1 (int id);

#endif