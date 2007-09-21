/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
 */

#ifndef REMAR2D_H
#define REMAR2D_H

#include "SDL.h"
#include "Sprite.h"
#include "SpriteInstance.h"
#include "TileSet.h"
#include "Tile.h"

class remar2d
{
 public:
  
  enum ErrorCode
    {
      NO_ERROR,
      FAILED_SET_VIDEO_MODE,
      FAILED_LOAD_SPRITE,
      FAILED_LOAD_TILESET
    };

  remar2d(int width, int height, int bpp, int fullscreen);

  ErrorCode getError();
  char *getErrorMessage();

  int redraw();

  void setBackgroundColor(int r, int g, int b);

  char *loadTileSet(char *file);
  int   removeTileSet(char *tileset);
  bool  loadTileMap(char *file);

  void setupTileBackground(int size_x, int size_y);
  void setTile(int x, int y, char *tileSet, int t_x, int t_y);

  char *loadSprite(char *file);
  void  removeSprite(char *sprite);
  int   inFrontOf(int sprite1, int sprite2);

  int  createSpriteInstance(char *sprite);
  void setAnimation(int sprite, char *animation);
  void moveSpriteRel(int sprite, int x, int y);
  void moveSpriteAbs(int sprite, int x, int y);
  void showSprite(int sprite, bool show);
  void removeSpriteInstance(int sprite);

 private:
  /* The screen that remar2d renders to. */
  SDL_Surface *screen;

  Uint32 backgroundColor;

  int screenWidth, screenHeight;

  int mapWidth, mapHeight;
  int tileWidth, tileHeight;

  map<string, Sprite *> sprites;
  map<int, SpriteInstance *> spriteInstances;
  map<string, TileSet *> tileSets;

  /* TODO: Class for tilemap. */

  Tile **tiles;
  int *dirty;

  /* When creating a sprite instance, this variable holds the id
     number for that instance. */
  int nextSpriteInstance;

  /* Keep track of time to perform animation. */
  int lastTime;

  ErrorCode errorCode;

  int frameCounter;
  int frameTimer;

  /* Background has been set up */
  bool backgroundSetup;

  void markBackgroundDirty(SDL_Rect *rect);

  int ALTERNATE;
};

#endif
