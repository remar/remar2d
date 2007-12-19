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

#ifndef SPRITE_INSTANCE_H
#define SPRITE_INSTANCE_H

#include "Sprite.h"

class SpriteInstance
{
 public:
  SpriteInstance(Sprite *sprite);
  void setAnimation(char *animation);
  void setVisible(bool visible);
  Sprite *getSprite();
  char *getCurrentAnimation();
  void animate(int delta);
  bool getVisible();
  void setRedraw(bool redraw);
  bool getRedraw();
  void moveRel(int x, int y);
  void moveAbs(int x, int y);
  void setLastRect(int x, int y, int w, int h);
  SDL_Rect *getLastRect();
  int x, y;
  int currentFrame;
  int old_x, old_y;

 private:
  Sprite *sprite;
  char *currentAnimation;
  int timeSpentInFrame;
  bool visible;
  bool redraw;
  SDL_Rect lastRect;
};

#endif // SPRITE_INSTANCE_H
