/*
    remar2d - a 2D graphics engine using SDL
    Copyright (C) 2007 Andreas Remar, andreas.remar@gmail.com

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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

  remar2d(int width, int height, int bpp, int fullscreen, const char *title);

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
  void pauseAnimation(int sprite, bool on);

  void pauseAnimations(bool on);

 private:
  /* The screen that remar2d renders to. */
  SDL_Surface *screen;

  Uint32 backgroundColor;

  int screenWidth, screenHeight;

  map<string, Sprite *> sprites;
  map<int, SpriteInstance *> spriteInstances;
  map<string, TileSet *> tileSets;

  /* TODO: Class for tilemap. */

  /* Data to keep track of the background (tilemap...) */
  Tile **tiles;
  int *dirty;
  int mapWidth, mapHeight;
  int tileWidth, tileHeight;

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

  void addSpriteToTiles(SpriteInstance *spriteInstance);
  void removeSpriteFromTiles(SpriteInstance *spriteInstance);

  int ALTERNATE;

  /* Pause all animations (used for pausing in games...) */
  bool pausedAnimations;
};

#endif
