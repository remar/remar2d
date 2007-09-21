/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
 */

#include "SpriteInstance.h"

SpriteInstance::SpriteInstance(Sprite *sprite)
  : currentAnimation(0), x(0), y(0), currentFrame(0), timeSpentInFrame(0),
    redraw(false)
{
  this->sprite = sprite;
}

void
SpriteInstance::setAnimation(char *animation)
{
  currentAnimation = animation;
  currentFrame = 0;
  timeSpentInFrame = 0;

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
  return currentAnimation;
}

void
SpriteInstance::animate(int delta)
{
  if(!currentAnimation)
    return;

  Animation *animation = sprite->getAnimation(currentAnimation);

  int oldFrame = currentFrame;
  animation->getNextFrame(&currentFrame, &timeSpentInFrame, delta);

  if(currentFrame != oldFrame)
    redraw = true;
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
