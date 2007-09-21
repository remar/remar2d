#ifndef TILESET_H
#define TILESET_H

#include "SDL.h"

class TileSet
{
 public:
  TileSet(char *file);
  ~TileSet();

  char *getName();
  SDL_Rect *getRect(int x, int y);
  SDL_Surface *getImage();

 private:
  char *name;
  SDL_Surface *image;
  SDL_Rect rect;
  int size_x, size_y;
};
#endif
