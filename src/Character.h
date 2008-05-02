#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL.h"

class Character
{
 public:
  Character(SDL_Surface *img, SDL_Rect *rect);
  ~Character();
  SDL_Surface *getImage();
  SDL_Rect *getRect();

 private:
  SDL_Surface *image;
  SDL_Rect character;
};

#endif
