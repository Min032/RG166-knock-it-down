#include "callbackFunctions.hpp"
#include "helperFunctions.hpp"
#include "shapes.hpp"
#include <iostream>
#include <cmath>

#define TIMER0_ID 0
#define TIMER0_INTERVAL 25

#define TIMER1_ID 1
#define TIMER1_INTERVAL 25

#define INITIAL_FRONT_ANGLE 5
#define INITIAL_BACK_ANGLE 0

double cam_param_y = 5;
double cam_param_x = 6;
double cam_param_z = 5;
double cam_increment = 0.2;

double rotation_y_menu_param = 0;

int game_ongoing = 0;

double front_legs_angle_param = -15;
double back_legs_angle_param = 0;

double front_legs_angle_increment = 8;
double back_legs_angle_increment = 8;

double jump_param = 0;
double jump_param_increment = 0.11;

double time_passed = 0;

double score = 0;

void initLights()
{

  glEnable(GL_LIGHTING);

  GLfloat light_position[] = { 12, 16, 10, 0 };
  GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1 };
	GLfloat light_specular[] = { 0, 0, 0, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  GLfloat light_specular1[] = { 0.2, 0.2, 0.2, 1 };

  glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);

}

void initMaterial()
{
  // Material parameters
  GLfloat ambient_coeffs[] = { 0.15, 0.15, 0.15, 1 };
	GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };
	GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
  GLfloat shininess = 30;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glShadeModel(GL_SMOOTH);
}

void initParams() {
  front_legs_angle_param = -15;
  back_legs_angle_param = 0;
  front_legs_angle_increment = 8;
  back_legs_angle_increment = 8;

  jump_param = 0;
  jump_param_increment = 0.11;

  score = 0;

  time_passed = 0;
  game_ongoing = 0;
}

void on_timer0(int id) {
  if (id != TIMER0_ID) return;

    // TODO: check if game should stop

    if(front_legs_angle_param >= 18)
      front_legs_angle_increment = -8;
    
    if(front_legs_angle_param <= -60)
      front_legs_angle_increment = 8;
    
    front_legs_angle_param += front_legs_angle_increment;

    if(back_legs_angle_param >= 18)
      back_legs_angle_increment = -8;
    
    if(back_legs_angle_param <= -60)
      back_legs_angle_increment = 8;

    back_legs_angle_param += front_legs_angle_increment;
    
    if(jump_param >= 1)
      jump_param_increment = -0.11;

    if(jump_param <= 0)
      jump_param_increment = 0.11;

    jump_param += jump_param_increment;

    glutPostRedisplay();

    if (game_ongoing) {
      glutTimerFunc(TIMER0_INTERVAL, on_timer0, TIMER0_ID);
    }
}

void on_timer1(int id) {
  if (id != TIMER1_ID) return;

  if(rotation_y_menu_param >= 360)
    rotation_y_menu_param = 0;

  rotation_y_menu_param += 0.4;

  glutPostRedisplay();

  if (!game_ongoing) {
      glutTimerFunc(TIMER1_INTERVAL, on_timer0, TIMER1_ID);
  }
}

void onKeyboardSpecial(int key, int x, int y) 
{
  switch(key)
  {
    case GLUT_KEY_UP:
      if(cam_param_y < 100)
      {
        cam_param_y += cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_DOWN:
      if(cam_param_y > -100)
      {
        cam_param_y -= cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_RIGHT:
      if(cam_param_z < 100)
      {
        cam_param_z += cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_LEFT:
      if(cam_param_z > -100)
      {
        cam_param_z -= cam_increment;
        glutPostRedisplay();
      }
      break;
    
  }

}

void onKeyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 27:
      exit(0);
      break;
    case '+':
      if(cam_param_x < 100)
      {
        cam_param_x += cam_increment;
        glutPostRedisplay();
      }
      break;
    case '-':
      if(cam_param_x > -100)
      {
        cam_param_x -= cam_increment;
        glutPostRedisplay();
      }
      break;
    case 32:
      if(!game_ongoing)
      {
        glutTimerFunc(TIMER0_INTERVAL, on_timer0, TIMER0_ID);
        game_ongoing = 1;
      }
      break;
    case 'p':
    case 'P':
      if(game_ongoing)
      {
        glutTimerFunc(TIMER1_INTERVAL, on_timer1, TIMER1_ID);
        game_ongoing = 0;
      }
      break;
    case 'r':
    case 'R':
      initParams();
      glutPostRedisplay();
      break;
  }
}

void onReshape(int width, int height)
{
  glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width/height, 1, 1000);
  
}


void onDisplay(void)
{

  initLights();
  initMaterial();  
  initTextures();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  if(!game_ongoing)
  {
    gluLookAt(6, 5, 5, 0, 0, 0, 0, 1, 0);
  }
  else 
    gluLookAt(-9, 6, 0, 0, 0, 0, 0, 1, 0);

  glEnable(GL_LIGHT1);

  glPushMatrix();
  draw_axis(50);
  glPopMatrix();


  if(!game_ongoing)
  {
    glutTimerFunc(TIMER1_INTERVAL, on_timer1, TIMER1_ID);
  }
    
  glPushMatrix();
  if(!game_ongoing)
    glRotatef(rotation_y_menu_param, 0, 1, 0);
  generatePlatform();

  glDisable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
  generateMovingCatto();
  glDisable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  glPopMatrix();

  

  glPushMatrix();
    if(!game_ongoing) {
      generateMenu();
    }
  glPopMatrix();

  glutSwapBuffers();
}

