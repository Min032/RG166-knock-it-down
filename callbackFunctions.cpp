#include "callbackFunctions.hpp"
#include "shapes.hpp"

float cam_param_y = 2;
float cam_param_x = -5;
float cam_param_z = 0;
float cam_increment = 0.2;

void initLights()
{

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat light_position[] = { 2, 6, 2, 0 };
  GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1 };
	GLfloat light_diffuse[] = { 0.9, 0.9, 0.9, 1 };
	GLfloat light_specular[] = { 0.7, 0.7, 0.7, 1 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void initMaterial()
{
  // Material parameters
  GLfloat ambient_coeffs[] = { 0.8, 0.8, 0.8, 1 };
	GLfloat diffuse_coeffs[] = { 1, 1, 1, 1 };
	GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
  GLfloat shininess = 30;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  glShadeModel(GL_SMOOTH);
}

void onKeyboardSpecial(int key, int x, int y) 
{
  switch(key)
  {
    case GLUT_KEY_UP:
      if(cam_param_y < 5)
      {
        cam_param_y += cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_DOWN:
      if(cam_param_y > 1.4)
      {
        cam_param_y -= cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_RIGHT:
      if(cam_param_z < 4)
      {
        cam_param_z += cam_increment;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_LEFT:
      if(cam_param_z > -4)
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
      if(cam_param_x < -1.8)
      {
        cam_param_x += cam_increment;
        glutPostRedisplay();
      }
      break;
    case '-':
      if(cam_param_x > -11.8)
      {
        cam_param_x -= cam_increment;
        glutPostRedisplay();
      }
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  gluLookAt(cam_param_x, cam_param_y, 0+cam_param_z, 0, 0, 0, 0, 1, 0);

  

  draw_axis(20);
    
  generatePlatform();


  glutSwapBuffers();
}

