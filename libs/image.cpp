#include <cassert>
#include <cstdlib>
#include <iostream>
#include "image.hpp"

auto image_init(int width, int height) -> Image * {

  Image *image = nullptr;

  assert(width >= 0 && height >= 0);

  image = static_cast<Image *>(malloc(sizeof(Image)));
  assert(image != nullptr);

  image->width = width;
  image->height = height;
  if (width == 0 || height == 0) {
    image->pixels = nullptr;
  } else {
    image->pixels = static_cast<char *>(malloc(3 * width * height * sizeof(char)));
    assert(image->pixels != nullptr);
  }

  return image;
}

void image_done(Image *image) {
  free(image->pixels);
  free(image);
}

void image_read(Image *image, char *filename) {

  FILE *file = nullptr;
  BITMAPFILEHEADER bfh;
  BITMAPINFOHEADER bih;
  unsigned int i = 0;
  unsigned char r = 0, g = 0, b = 0, a = 0;

  free(image->pixels);
  image->pixels = nullptr;

  assert((file = fopen(filename, "rb")) != nullptr);

  fread(&bfh.type, 2, 1, file);
  fread(&bfh.size, 4, 1, file);
  fread(&bfh.reserved1, 2, 1, file);
  fread(&bfh.reserved2, 2, 1, file);
  fread(&bfh.offsetbits, 4, 1, file);

  fread(&bih.size, 4, 1, file);
  fread(&bih.width, 4, 1, file);
  fread(&bih.height, 4, 1, file);
  fread(&bih.planes, 2, 1, file);
  fread(&bih.bitcount, 2, 1, file);
  fread(&bih.compression, 4, 1, file);
  fread(&bih.sizeimage, 4, 1, file);
  fread(&bih.xpelspermeter, 4, 1, file);
  fread(&bih.ypelspermeter, 4, 1, file);
  fread(&bih.colorsused, 4, 1, file);
  fread(&bih.colorsimportant, 4, 1, file);

  image->width = bih.width;
  image->height = bih.height;

  if (bih.bitcount == 24) {
    image->pixels = static_cast<char *>(malloc(3 * bih.width * bih.height * sizeof(char)));
  } else if (bih.bitcount == 32) {
    image->pixels = static_cast<char *>(malloc(4 * bih.width * bih.height * sizeof(char)));
  } else {
    fprintf(stderr, "image_read(): Podrzane su samo slike koje po pikselu cuvaju 24 ili 32 bita podataka.\n");
    exit(1);
  }
  assert(image->pixels != nullptr);

  if (bih.bitcount == 24) {
    for (i = 0; i < bih.width * bih.height; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);

      image->pixels[3 * i] = r;
      image->pixels[3 * i + 1] = g;
      image->pixels[3 * i + 2] = b;
    }
  } else if (bih.bitcount == 32) {
    for (i = 0; i < bih.width * bih.height; i++) {
      fread(&b, sizeof(char), 1, file);
      fread(&g, sizeof(char), 1, file);
      fread(&r, sizeof(char), 1, file);
      fread(&a, sizeof(char), 1, file);

      image->pixels[4 * i] = r;
      image->pixels[4 * i + 1] = g;
      image->pixels[4 * i + 2] = b;
      image->pixels[4 * i + 3] = a;
    }
}

  fclose(file);
}
