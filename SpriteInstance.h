/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
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
