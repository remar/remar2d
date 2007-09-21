#ifndef TILE_H
#define TILE_H

#include "SpriteInstance.h"
#include <list>

using namespace std;

class Tile
{
 public:
  Tile(char *tileSet, int x, int y);

  /** Add sprite instance to tile to indicate that this sprite should
      be redrawn if this tile is redrawn. */
  void addSpriteInstance(SpriteInstance *spriteInstance);

  /** Remove sprite instance from tile to indicate that this sprite
      has left the tile so redraw isn't needed when tile is redrawn. */
  void removeSpriteInstance(SpriteInstance *spriteInstance);

  void markSpritesDirty();

  char *tileSet;
  int x, y;
  bool redraw;
  list<SpriteInstance *> sprites;
};

#endif
