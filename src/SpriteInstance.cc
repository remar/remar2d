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

#include "SpriteInstance.h"

SpriteInstance::SpriteInstance(Sprite *sprite)
  : currentAnimationName(0), x(0), y(0), currentFrame(0), timeSpentInFrame(0),
    redraw(false), currentAnimation(0), paused(false)
{
  this->sprite = sprite;
}

void
SpriteInstance::setAnimation(char *animation)
{
  currentAnimationName = animation;
  currentFrame = 0;
  timeSpentInFrame = 0;

  currentAnimation = sprite->getAnimation(currentAnimationName);
  currentAnimRect = currentAnimation->getRect(0);

  redraw = true;
}

void
SpriteInstance::setVisible(bool visible)
{
  this->visible = visible;
}

Sprite *
SpriteInstance::getSprite()
{
  return sprite;
}

char *
SpriteInstance::getCurrentAnimation()
{
  return currentAnimationName;
}

void
SpriteInstance::animate(int delta)
{
  if(!currentAnimationName || paused)
    return;

  // Animation *animation = sprite->getAnimation(currentAnimationName);

  int oldFrame = currentFrame;
  currentAnimation->getNextFrame(&currentFrame, &timeSpentInFrame, delta);

  if(currentFrame != oldFrame)
    redraw = true;
}

void
SpriteInstance::pauseAnimation(bool yes)
{
  paused = yes;
}

bool
SpriteInstance::getVisible()
{
  return visible;
}

void
SpriteInstance::setRedraw(bool redraw)
{
  this->redraw = redraw;
}

bool
SpriteInstance::getRedraw()
{
  return redraw;
}

void
SpriteInstance::moveRel(int x, int y)
{
  old_x = this->x;
  old_y = this->y;
  this->x += x;
  this->y += y;

  redraw = true;
}

void
SpriteInstance::moveAbs(int x, int y)
{
  old_x = this->x;
  old_y = this->y;
  this->x = x;
  this->y = y;
  
  redraw = true;
}

void
SpriteInstance::setLastRect(int x, int y, int w, int h)
{
  lastRect.x = x;
  lastRect.y = y;
  lastRect.w = w;
  lastRect.h = h;
}

SDL_Rect *
SpriteInstance::getLastRect()
{
  return &lastRect;
}

SDL_Rect *
SpriteInstance::getCurrentRect()
{
  // Animation *animation = sprite->getAnimation(currentAnimationName);
  currentRect.x = x;
  currentRect.y = y;
  currentRect.w = currentAnimRect->w;
  currentRect.h = currentAnimRect->h;

  return &currentRect;
}
