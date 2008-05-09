#include "Character.h"

Character::Character(SDL_Surface *img, SDL_Rect *rect)
{
  image = img;
  character.w = rect->w;
  character.h = rect->h;
  character.x = rect->x;
  character.y = rect->y;
}

Character::~Character()
{

}

SDL_Surface *
Character::getImage()
{
  return image;
}

SDL_Rect *
Character::getRect()
{
  return &character;
}
