#include "Tile.h"
#include <algorithm>

Tile::Tile(char *tileSet, int x, int y)
{
  this->tileSet = tileSet;
  this->x = x;
  this->y = y;
}

void
Tile::addSpriteInstance(SpriteInstance *spriteInstance)
{
  sprites.push_back(spriteInstance);
}

void
Tile::removeSpriteInstance(SpriteInstance *spriteInstance)
{
  sprites.remove(spriteInstance);
}

/* This should have been a lambda... */
template<class T> struct setRedraw : public unary_function<T, void>
{
  void operator() (T x) {x->setRedraw(true);}
};

void
Tile::markSpritesDirty()
{
  for_each(sprites.begin(), sprites.end(), setRedraw<SpriteInstance *>());
}
