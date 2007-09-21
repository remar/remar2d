/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "Animation.h"
#include "tinyxml.h"
#include <map>
#include <string>

using namespace std;

class Sprite
{
 public:
  Sprite(char *file);
  ~Sprite();

  char *getName();
  Animation *getAnimation(char *animName);

 private:
  char *name;

  const char *currentAnimation;
  map<string, Animation *> animations;

  void startNewAnimation(TiXmlElement *element);
  void addImageToAnimation(TiXmlElement *element, char *pathToXml);
  void addFrameToAnimation(TiXmlElement *element);
};

#endif
