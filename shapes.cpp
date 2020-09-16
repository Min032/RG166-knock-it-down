#include "shapes.hpp"
#include "helperFunctions.hpp"
#include "image.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>

// Texture IDs
static GLuint names[2];

// Textures files names
#define FILENAME0 "resources/orr.bmp"
#define FILENAME1 "resources/floor.bmp"

std::vector<double> objects_z;
std::vector<bool> already_collided_before(0);

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

  /*
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
  */
}

void drawAxis(int n)
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

  drawRomanString("Welcome to Knock it down!", 3.7, 4.3, 3.7);
  drawRomanString("[A/S] for movement", 4, 4.1, 4);
  drawRomanString("[SPACE] for start", 4, 3.9, 4);
  drawRomanString("[P] for pause", 4, 3.7, 4);
  drawRomanString("[R] for reset", 4, 3.5, 4);
  drawRomanString("[ESC] for exit", 4, 3.3, 4);

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

void generateScore() {
  std::string score_string;

  score_string = "Score: ";
  score_string.append(std::to_string(score));

  char *tmp = (char *)score_string.c_str();

  if(!game_ongoing)
    drawRomanString(tmp, 0, 3.6, -7);
  else
    drawRomanString(tmp, 0, 6.35, 3.05);
}

void generateLevelResolve() {
  std::string level_string;

  level_string = "Current level: ";
  level_string.append(std::to_string(current_level));

  char *tmp = (char *)level_string.c_str();

  drawRomanString(tmp, 0, 6.35, -3.2);
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

void initGlobalIndicator() {
  already_collided_before.resize(0);
  already_collided_before.resize(15);
  std::fill(std::begin(already_collided_before), std::end(already_collided_before), false);
}

void generateObjects() {

  if(floor_param >= 232 || floor_param == 0) {
    initGlobalIndicator();
    objects_z = generateRangedNumbers(-4, 4);
  }
  
  generateLevelResolve();

  bool collided = false;

  double clip_plane0[] = {1, 0, 0, 3};
  double clip_plane1[] = {0, 1, 0, -1};
  glClipPlane(GL_CLIP_PLANE0, clip_plane0);

  setMaterialColor(0.7, 0.3, 0.3, 1);
  glEnable(GL_CLIP_PLANE0);
  
  glPushMatrix();
    if(!already_collided_before[0] && isCollision(character_z_param, 20 - floor_param, objects_z[0])) {
      already_collided_before[0] = true;
      score++;
    }
    glTranslatef(20-floor_param, 1, objects_z[0]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[1] && isCollision(character_z_param, 35 - floor_param, objects_z[1])) {
      already_collided_before[1] = true;
      score++;
    }
    glTranslatef(35-floor_param, 1, objects_z[1]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[2] && isCollision(character_z_param, 50 - floor_param, objects_z[2])) {
      already_collided_before[2] = true;
      score++;
    }
    glTranslatef(50-floor_param, 1, objects_z[2]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[3] && isCollision(character_z_param, 65 - floor_param, objects_z[3])) {
      already_collided_before[3] = true;
      score++;
    }
    glTranslatef(65-floor_param, 1, objects_z[3]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[4] && isCollision(character_z_param, 80 - floor_param, objects_z[4])) {
      already_collided_before[4] = true;
      score++;
    }
    glTranslatef(80-floor_param, 1, objects_z[4]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[5] && isCollision(character_z_param, 95 - floor_param, objects_z[5])) {
      already_collided_before[5] = true;
      score++;
    }
    glTranslatef(95-floor_param, 1, objects_z[5]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[6] && isCollision(character_z_param, 110 - floor_param, objects_z[6])) {
      already_collided_before[6] = true;
      score++;
    }
    glTranslatef(110-floor_param, 1, objects_z[6]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[7] && isCollision(character_z_param, 125 - floor_param, objects_z[7])) {
      already_collided_before[7] = true;
      score++;
    }
    glTranslatef(125-floor_param, 1, objects_z[7]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[8] && isCollision(character_z_param, 140 - floor_param, objects_z[8])) {
      already_collided_before[8] = true;
      score++;
    }
    glTranslatef(140-floor_param, 1, objects_z[8]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[9] && isCollision(character_z_param, 155 - floor_param, objects_z[9])) {
      already_collided_before[9] = true;
      score++;
    }
    glTranslatef(155-floor_param, 1, objects_z[9]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[10] && isCollision(character_z_param, 170 - floor_param, objects_z[10])) {
      already_collided_before[10] = true;
      score++;
    }
    glTranslatef(170-floor_param, 1, objects_z[10]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[11] && isCollision(character_z_param, 185 - floor_param, objects_z[11])) {
      already_collided_before[11] = true;
      score++;
    }
    glTranslatef(185-floor_param, 1, objects_z[11]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[12] && isCollision(character_z_param, 200 - floor_param, objects_z[12])) {
      already_collided_before[12] = true;
      score++;
    }
    glTranslatef(200-floor_param, 1, objects_z[12]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[13] && isCollision(character_z_param, 215 - floor_param, objects_z[13])) {
      already_collided_before[13] = true;
      score++;
    }
    glTranslatef(215-floor_param, 1, objects_z[13]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();

  glPushMatrix();
    if(!already_collided_before[14] && isCollision(character_z_param, 230 - floor_param, objects_z[14])) {
      already_collided_before[14] = true;
      score++;
    }
    glTranslatef(230-floor_param, 1, objects_z[14]);
    glRotatef(objects_rotation_param, 0, 1, 0);
    glScalef(0.3, 0.3, 0.3);
    glutWireDodecahedron();
  glPopMatrix();


  glDisable(GL_CLIP_PLANE0);

}