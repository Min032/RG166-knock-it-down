#ifndef IMG_HPP
#define IMG_HPP

/*
 * Dve strukture koje opisuju strukturu dva zaglavlja
 * kojima pocinje svaka slika u bmp formatu.
 */
using BITMAPFILEHEADER = struct {
  unsigned short type;
  unsigned int size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned int offsetbits;
};

using BITMAPINFOHEADER = struct {
  unsigned int size;
  unsigned int width;
  unsigned int height;
  unsigned short planes;
  unsigned short bitcount;
  unsigned int compression;
  unsigned int sizeimage;
  int xpelspermeter;
  int ypelspermeter;
  unsigned int colorsused;
  unsigned int colorsimportant;
};

using Image = struct Image {
  int width, height; 
  char *pixels; 
};

auto image_init(int width, int height) -> Image *;

void image_done(Image *image);

void image_read(Image *image, char *filename);

#endif