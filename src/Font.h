#ifndef FONT_H
#define FONT_H

#include "SDL.h"
#include "tinyxml.h"
#include <string>
#include <map>
#include "Character.h"

class Font
{
 public:
  Font(char *file);
  ~Font();

  char *getName();
  
 private:
  char *addImageToFont(TiXmlElement *element, char *pathToXml);
  void addCharToFont(TiXmlElement *element, char *currentImage);

  char *name;
  int size_x, size_y;

  /* The character set of this font */
  std::map<char, Character *> characters;

  /* The images that this font consists of */
  std::map<std::string, SDL_Surface *> images;
};

#endif
