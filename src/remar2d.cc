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

#include "remar2d.h"
#include "Sprite.h"

#include <string.h>

remar2d::remar2d(int width, int height, int bpp, int fullscreen)
  : errorCode(NO_ERROR), nextSpriteInstance(1), lastTime(0), frameCounter(0),
    frameTimer(0), backgroundSetup(false)
{
  /* SDL_RESIZABLE makes it possible to switch between window/fullscreen */
  int flags = SDL_DOUBLEBUF | SDL_RESIZABLE;

  if(fullscreen)
    {
      flags |= SDL_FULLSCREEN;
    }

  screenWidth = width;
  screenHeight = height;

  screen = SDL_SetVideoMode(width, height, bpp, flags);

  if(screen == 0)
    {
      errorCode = FAILED_SET_VIDEO_MODE;
    }

  setBackgroundColor(0, 0, 0);
}

remar2d::ErrorCode
remar2d::getError()
{
  return errorCode;
}

char *
remar2d::getErrorMessage()
{
  char *errorToString[] = { "No error",
			    "Failed to set video mode",
			    "Failed to load sprite"};

  if(errorCode >= NO_ERROR && errorCode <= FAILED_LOAD_TILESET)
    {
      return errorToString[errorCode];
    }
  else
    {
      return "BUG! Error code has no matching string";
    }
}

int
remar2d::redraw()
{
  int delta;

  if(lastTime == 0)
    {
      delta = 0;
      lastTime = SDL_GetTicks();
    }
  else
    {
      delta = SDL_GetTicks() - lastTime;
      lastTime = SDL_GetTicks();
    }

  /* Animate sprites to see where we need to redraw */
  for(int i = 1;i < nextSpriteInstance;i++)
    {
      SpriteInstance *spriteInstance = spriteInstances[i];

      if(spriteInstance && spriteInstance->getVisible())
	{
	  spriteInstance->animate(delta);

	  if(spriteInstance->getRedraw() == true)
	    {
	      SDL_Rect *rect = spriteInstance->getLastRect();

	      markBackgroundDirty(rect);
	    }
	}
    }

  /* Redraw background tiles */
  SDL_Rect *source;
  SDL_Rect dest;
  SDL_Surface *image;
  for(int i = 0;i < mapWidth*mapHeight;i++)
    {
      if(dirty[i])
	{
	  dest.x = (i%mapWidth)*tileWidth;
	  dest.y = (i/mapWidth)*tileHeight;
	  dest.w = tileWidth;
	  dest.h = tileHeight;

	  SDL_FillRect(screen, &dest, backgroundColor);

	  if(tiles[i] != 0)
	    {
	      tiles[i]->markSpritesDirty();

	      TileSet *set = tileSets[tiles[i]->tileSet];
	  
	      source = set->getRect(tiles[i]->x, tiles[i]->y);
	      image = set->getImage();

	      SDL_BlitSurface(image, source, screen, &dest);
	    }
	}
      /* Clear dirty flags */
      dirty[i] = 0;
    }

  for(int i = 1;i < nextSpriteInstance;i++)
    {
      SpriteInstance *spriteInstance = spriteInstances[i];

      if(spriteInstance
	 && spriteInstance->getVisible()
	 && spriteInstance->getRedraw())
	{
	  spriteInstance->setRedraw(false);

	  Sprite *sprite = spriteInstance->getSprite();
	  SDL_Rect *source;
	  SDL_Rect dest;

	  char *anim = spriteInstance->getCurrentAnimation();
	  if(!anim)
	    {
	      /* If animation isn't set, just continue */
	      continue;
	    }

	  Animation *animation = sprite->getAnimation(anim);
	  int currentFrame = spriteInstance->currentFrame;

	  SDL_Surface *animSurface = animation->getImage();
	  source = animation->getRect(currentFrame);

	  dest.x = spriteInstance->x - animation->orig_x;
	  dest.y = spriteInstance->y - animation->orig_y;

	  SDL_BlitSurface(animSurface,
			  source,
			  screen,
			  &dest);

	  /* Save where we painted so we can paint over later */
	  spriteInstance->setLastRect(dest.x, dest.y, source->w, source->h);

	  delete source;
	}
    }

  SDL_Flip(screen);

  frameCounter++;
  if(frameTimer == 0)
    {
      frameTimer = SDL_GetTicks();
    }

  if(SDL_GetTicks() - frameTimer > 1000)
    {
      //printf("FPS: %d\n", frameCounter);
      frameTimer = SDL_GetTicks();
      frameCounter = 0;
    }
}

void
remar2d::setBackgroundColor(int r, int g, int b)
{
  backgroundColor = SDL_MapRGB(screen->format, r, g, b);
}

char *
remar2d::loadTileSet(char *file)
{
  TileSet *tileSet = new TileSet(file);
  if(tileSet)
    {
      if(strcmp(tileSet->getName(), "") == 0)
	{
	  errorCode = FAILED_LOAD_TILESET;
	  return 0;
	}
    }
  else
    {
      errorCode = FAILED_LOAD_TILESET;
      return 0;
    }

  /* Store tileset */
  tileSets[string(tileSet->getName())] = tileSet;

  return tileSet->getName();
}

int
remar2d::removeTileSet(char *tileset)
{

}

bool
remar2d::loadTileMap(char *file)
{

}

void
remar2d::setupTileBackground(int size_x, int size_y)
{
  if(backgroundSetup)
    {
      delete [] tiles;
      delete [] dirty;
    }

  int odd_width, odd_height;

  odd_width = !!(screenWidth % size_x);
  odd_height = !!(screenHeight % size_y);

  mapWidth = screenWidth/size_x + odd_width;
  mapHeight = screenHeight/size_y + odd_height;

  tileWidth = size_x;
  tileHeight = size_y;

  tiles = new Tile*[mapWidth * mapHeight];
  dirty = new int[mapWidth * mapHeight];

  for(int i = 0;i < mapWidth * mapHeight;i++)
    {
      tiles[i] = 0;
      dirty[i] = 1;
    }

  backgroundSetup = true;
}

void
remar2d::setTile(int x, int y, char *tileSet, int t_x, int t_y)
{
  Tile *tile = new Tile(tileSet, t_x, t_y);

  tiles[y*mapWidth + x] = tile;
  dirty[y*mapWidth + x] = 1;
}

char *
remar2d::loadSprite(char *file)
{
  Sprite *sprite = new Sprite(file);
  if(sprite)
    {
      /* Store sprite somewhere */
      if(strcmp(sprite->getName(), "") == 0)
	{
	  errorCode = FAILED_LOAD_SPRITE;
	  return 0;
	}
    }
  else
    {
      errorCode = FAILED_LOAD_SPRITE;
      return 0;
    }

  /* Store sprite */
  sprites[string(sprite->getName())] = sprite;

  /* Use this name when you wan't to create instances of this sprite */
  return sprite->getName();
}

void
remar2d::removeSprite(char *sprite)
{
  Sprite *spr = sprites[string(sprite)];

  sprites.erase(string(sprite));

  delete spr;
}

int
remar2d::createSpriteInstance(char *sprite)
{
  Sprite *spr = sprites[string(sprite)];
  spriteInstances[nextSpriteInstance] = new SpriteInstance(spr);

  return nextSpriteInstance++;
}

void
remar2d::setAnimation(int sprite, char *animation)
{
  spriteInstances[sprite]->setAnimation(animation);
}

void
remar2d::moveSpriteRel(int sprite, int x, int y)
{
  spriteInstances[sprite]->moveRel(x, y);
}

void
remar2d::moveSpriteAbs(int sprite, int x, int y)
{
  spriteInstances[sprite]->moveAbs(x, y);
}

void
remar2d::showSprite(int sprite, bool show)
{
  spriteInstances[sprite]->setVisible(show);
}

void
remar2d::removeSpriteInstance(int sprite)
{
  printf("Remove sprite instance %d\n", sprite);
}

void
remar2d::markBackgroundDirty(SDL_Rect *rect)
{
  int x1 = rect->x;
  int x2 = rect->x + rect->w;
  int y1 = rect->y;
  int y2 = rect->y + rect->h;

  x1 /= tileWidth;
  x2 /= tileWidth;
  y1 /= tileHeight;
  y2 /= tileHeight;

  if(x1 < 0)
    x1 = 0;
  else if(x1 >= mapWidth)
    x1 = mapWidth - 1;
  if(x2 < 0)
    x2 = 0;
  else if(x2 >= mapWidth)
    x2 = mapWidth - 1;

  if(y1 < 0)
    y1 = 0;
  else if(y1 >= mapHeight)
    y1 = mapHeight - 1;
  if(y2 < 0)
    y2 = 0;
  else if(y2 >= mapHeight)
    y2 = mapHeight - 1;

  for(int y = y1;y <= y2;y++)
    for(int x = x1;x <= x2;x++)
      {
	dirty[x + y * mapWidth] = 1;
      }

  // printf("Mark (%d,%d)-(%d,%d) as dirty\n", x1, y1, x2, y2);
}