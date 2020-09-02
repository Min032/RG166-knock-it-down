#include "helperFunctions.hpp"
/*
#include "libraries/assimp-5.0.1/include/assimp/Importer.hpp"
#include "libraries/assimp-5.0.1/include/assimp/scene.h"
#include "libraries/assimp-5.0.1/include/assimp/postprocess.h"
*/

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b)
{
  GLfloat diffuse_coeffs[] = { r, g, b, 1 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_coeffs);
} 
