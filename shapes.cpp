#include "shapes.hpp"
#include "helperFunctions.hpp"
#include "image.hpp"
#include <cmath>
#include <iostream>

// Texture IDs
static GLuint names[2];

// Textures files names
#define FILENAME0 "resources/orr.bmp"
#define FILENAME1 "resources/floor.bmp"

static float matrix[16];

void initTextures()
{
  Image *image;

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

  glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

  glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 4.0f);
  glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE, 4.0f);


  glGenTextures(2, names);

  image = image_init(0, 0);

  // 1 Texture - Fur
  image_read(image, FILENAME0);

  glBindTexture(GL_TEXTURE_2D, names[0]);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                image->width, image->height, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);

  // 2 Texture - Neon
  image_read(image, FILENAME1);

  glBindTexture(GL_TEXTURE_2D, names[1]);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                image->width, image->height, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

  // Turning off active texture
  glBindTexture(GL_TEXTURE_2D, 0);

  // Destroy the image object
  image_done(image);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

}

void draw_axis(int n)
{
  glPushMatrix();
    glDisable(GL_LIGHTING);  
    glPushMatrix();
      
      glColor3f(1, 0, 0);
      glBegin(GL_LINES);
      glVertex3f(n, 0, 0);
      glVertex3f(0, 0, 0);
      glEnd();

      glColor3f(0, 1, 0);
      glBegin(GL_LINES);
      glVertex3f(0, n, 0);
      glVertex3f(0, 0, 0);
      glEnd();

      glColor3f(0, 0, 1);
      glBegin(GL_LINES);
      glVertex3f(0, 0, n);
      glVertex3f(0, 0, 0);
      glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
  glPopMatrix();
}

void generateMenu() {

  drawHelveticaString("Welcome to Knock it down!", 3.7, 4.3, 3.7);
  drawHelveticaString("[A/S] for movement", 4, 4.1, 4);
  drawHelveticaString("[SPACE] for start", 4, 3.9, 4);
  drawHelveticaString("[P] for pause", 4, 3.7, 4);
  drawHelveticaString("[R] for reset", 4, 3.5, 4);
  drawHelveticaString("[ESC] for exit", 4, 3.3, 4);

  glEnable(GL_BLEND);
  
  setMaterialColor(0.1, 0.1, 0.1, 0.8);
  glPushMatrix();
    glTranslatef(0, 3.5, 0);
    glTranslatef(2.5, 0, 0);
    glTranslatef(0, 0, 2);
    glRotatef(-40, 0, 1, 0);
    glRotatef(50, 0, 0, 1);
    glScalef(0.2, 7, 15);
    glutSolidCube(1);
  glPopMatrix();
  glDisable(GL_BLEND);
    
}

void drawMainPolygon() {

  glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);

    glTexCoord2f(-4, 8);
    glVertex3f(-2, 4, 0);

    glTexCoord2f(6000, 8);
    glVertex3f(3000, 4, 0);

    glTexCoord2f(6000, -8);
    glVertex3f(3000, -4, 0);

    glTexCoord2f(-4, -8);
    glVertex3f(-2, -4, 0);
  glEnd();

}

void drawSidePolygon() {

  glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(-4, 0.6);
    glVertex3f(-2, 0.3, 0);

    glTexCoord2f(6000, 0.6);
    glVertex3f(3000, 0.3, 0);

    glTexCoord2f(6000, -0.6);
    glVertex3f(3000, -0.3, 0);

    glTexCoord2f(-4, -0.6);
    glVertex3f(-2, -0.3, 0);
  glEnd();

}

void drawBottomPolygon() {

  glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);

    glTexCoord2f(-8, 0.6);
    glVertex3f(-4, 0.3, 0);

    glTexCoord2f(8, 0.6);
    glVertex3f(4, 0.3, 0);

    glTexCoord2f(8, -0.6);
    glVertex3f(4, -0.3, 0);

    glTexCoord2f(-8, -0.6);
    glVertex3f(-4, -0.3, 0);
  glEnd();

}

void generateTexturedPlatform()
{
  
  setMaterialColor(0.2, 0.2, 0.2, 1);
  
  glBindTexture(GL_TEXTURE_2D, names[1]);
  
  // Main plats
  glPushMatrix();
    
    glTranslatef(0, 0.3, 0);
    glRotatef(90, 1, 0, 0);
    drawMainPolygon();  
  glPopMatrix();

  glPushMatrix();
    
    glTranslatef(0, -0.3, 0);
    glRotatef(270, 1, 0, 0);
    drawMainPolygon();  
  glPopMatrix();

  // Sides
  glPushMatrix();
    glTranslatef(0, 0, 4);
    drawSidePolygon();  
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0, 0, -4);
    glRotatef(180, 1, 0, 0);
    drawSidePolygon();  
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);

}

void generateWholePlatform() {

  setMaterialColor(0, 0, 0, 0);
  double clip_plane0[] = {1, 0, 0, 3};
  glClipPlane(GL_CLIP_PLANE0, clip_plane0);

  glEnable(GL_CLIP_PLANE0);

  glPushMatrix();
    glTranslatef(-2-floor_param, 0, 0);
    generateTexturedPlatform();
  glPopMatrix();

  glDisable(GL_CLIP_PLANE0);

  glPushMatrix();
    glTranslatef(-3.5, 0, 0);
    glScalef(1, 1, 8);
    glutSolidCube(1);

  glPopMatrix();

}

void clipTailBody()
{
  double clip_plane0[] = {0, -1, 0, 0};
  double clip_plane1[] = {-1, 0, 0, 0};
  glClipPlane(GL_CLIP_PLANE0, clip_plane0);
  glClipPlane(GL_CLIP_PLANE1, clip_plane1);
  
  glEnable(GL_CLIP_PLANE0);
  glEnable(GL_CLIP_PLANE1);
  glutSolidTorus(0.08, 0.4, 50, 50);
  glDisable(GL_CLIP_PLANE0);
  glDisable(GL_CLIP_PLANE1);

}

void clipTailBall()
{
  double clip_plane0[] = {-1, 0, 0, 0};
  glClipPlane(GL_CLIP_PLANE0, clip_plane0);
  
  glEnable(GL_CLIP_PLANE0);
  
  glutSolidSphere(0.08, 50, 50);
  glDisable(GL_CLIP_PLANE0);
  
}

void clipSmile() {

  double clip_plane0[] = {0, -1, 0, 0};
  glClipPlane(GL_CLIP_PLANE0, clip_plane0);
  
  glEnable(GL_CLIP_PLANE0);
  
  glutSolidTorus(0.01, 0.05, 50, 50);
  glDisable(GL_CLIP_PLANE0);

}

void makeLegAndPaw() {

  // Leg

  glPushMatrix();
    glTranslatef(0, -0.7, 0);
    glScalef(0.1, 0.7, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  // Paw

  glPushMatrix();
    glTranslatef(0.05, -1.3, 0);
    glScalef(0.12, 0.1, 0.09);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

}

void generateCatto() 
{
  //setMaterialColor(0.5, 0.5, 0.5);
  setMaterialColor(0.1, 0.1, 0.1, 1);
  
  // Enable texture coordinates generation
  glEnable(GL_TEXTURE_GEN_S); 
  glEnable(GL_TEXTURE_GEN_T);

  // Set fur texture
  glBindTexture(GL_TEXTURE_2D, names[0]);

  // Body

  glPushMatrix();
    glTranslatef(0, 1.6, 0);
    glScalef(0.8, 0.6, 0.4);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  // Back legs

  glPushMatrix();
    glTranslatef(-0.4, 1.7, 0.3);
    glRotatef(back_legs_angle_param, 0, 0, 1);
    makeLegAndPaw();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.4, 1.7, -0.3);
    glRotatef(back_legs_angle_param, 0, 0, 1);
    makeLegAndPaw();
  glPopMatrix();

  // Front legs

  glPushMatrix();
    glTranslatef(0.4, 1.7, 0.3);
    glRotatef(-front_legs_angle_param, 0, 0, 1);
    makeLegAndPaw();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.4, 1.7, -0.3);
    glRotatef(-front_legs_angle_param, 0, 0, 1);
    makeLegAndPaw();
  glPopMatrix();

  // Head
  glPushMatrix();
    glTranslatef(0.8, 2, 0);
    glScalef(0.25, 0.4, 0.3);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  // Ears
  glPushMatrix();
    glTranslatef(0.8, 2.3, -0.15);
    glRotatef(-30, 1, 0, 0);
    glScalef(0.3, 1.3, 1);
    glRotatef(90, 0, 0, 1);
    glScalef(0.2, 0.7, 0.2);
    glutSolidTetrahedron();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.8, 2.3, 0.15);
    glRotatef(30, 1, 0, 0);
    glScalef(0.3, 1.3, 1);
    glRotatef(90, 0, 0, 1);
    glScalef(0.2, 0.7, 0.2);
    glutSolidTetrahedron();
  glPopMatrix();


  // Tail
  glPushMatrix();
    glTranslatef(-0.7, 2.2, 0);
    glRotatef(0, 0, 0, 1);
    clipTailBody();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-1.5, 2.2, 0);
    glRotatef(180, 0, 0, 1);
    clipTailBody();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-1.5, 2.6, 0);
    clipTailBall();
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);

  // Disable texture coordinates
  glDisable(GL_TEXTURE_GEN_S); 
  glDisable(GL_TEXTURE_GEN_T);

  // Smile
  setMaterialColor(0, 0, 0, 1);

  glPushMatrix();
    glTranslatef(1.03, 1.9, 0.05);
    glRotatef(70, 0, 1, 0);
    clipSmile();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.03, 1.9, -0.05);
    glRotatef(110, 0, 1, 0);
    clipSmile();
  glPopMatrix();

  // Eyes

  glPushMatrix();
    glTranslatef(0.99, 2.2, -0.08);
    glRotatef(30, 0, 0, 1);
    glRotatef(100, 0, 1, 0);
    glScalef(1.3, 1, 1);
    clipSmile();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(0.99, 2.2, 0.08);
    glRotatef(30, 0, 0, 1);
    glRotatef(80, 0, 1, 0);
    glScalef(1.3, 1, 1);
    clipSmile();
  glPopMatrix();


  // Eyeballs

  glPushMatrix();
    glTranslatef(1.025, 2.115, 0.095);
    glScalef(0.01, 0.035, 0.01);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.025, 2.115, -0.095);
    glScalef(0.01, 0.035, 0.01);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();


}

void generateMovingCatto() {

  glPushMatrix();
    glTranslatef(0, jump_param, character_z_param);
    generateCatto();
  glPopMatrix();

}
