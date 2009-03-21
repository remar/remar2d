#include "Font.h"

#include "SurfaceCache.h"
extern SurfaceCache *surfaceCache;

Font::Font(char *file)
  : name(""), size_x(0), size_y(0)
{
  TiXmlDocument doc(file);

  if(!doc.LoadFile())
    {
      return;
    }

  TiXmlNode *font = 0, *charset = 0, *character = 0;
  TiXmlElement *element = 0;

  font = doc.FirstChild("font");
  if(font)
    {
      element = font->ToElement();
      char *n = (char *)element->Attribute("name");
      if(n)
	{
	  name = new char[strlen(n) + 1];
	  strncpy(name, n, strlen(n) + 1);
	}

      size_x = atoi(element->Attribute("size_x"));
      size_y = atoi(element->Attribute("size_y"));

      char *currentImage = 0;

      while((charset = font->IterateChildren("charset", charset)))
	{
	  while((character = charset->IterateChildren(character)))
	    {
	      element = character->ToElement();
	      if(strcmp(element->Value(), "image") == 0)
		{
		  currentImage = addImageToFont(element, file);
		}
	      else if(strcmp(element->Value(), "char") == 0)
		{
		  addCharToFont(element, currentImage);
		}
	    }	  
	}
    }
}

Font::~Font()
{

}

char *
Font::getName()
{
  return name;
}

int
Font::getWidth()
{
  return size_x;
}

int
Font::getHeight()
{
  return size_y;
}

Character *
Font::getCharacter(char ch)
{
  return characters[ch];
}

char *
Font::addImageToFont(TiXmlElement *element, char *pathToXml)
{
  int pathLen;
  for(int i = strlen(pathToXml);i >= 0;i--)
    {
      if(pathToXml[i] == '/')
	{
	  pathLen = i + 1;
	  break;
	}
    }

  const char *n = element->Attribute("name");
  char *name = 0;
  if(n)
    {
      name = new char[strlen(n) + 1];
      strncpy(name, n, strlen(n) + 1);
    }

  const char *path = element->Attribute("path");
  const char *key = element->Attribute("key");

  if(!name)
    {
      printf("Missing name for charset image in %s\n", pathToXml);
      return 0;
    }
  else if(!path)
    {
      printf("Missing path for charset image in %s\n", pathToXml);
      return 0;
    }

  char *pathToImage = new char[strlen(path) + pathLen + 1];
  strncpy(pathToImage, pathToXml, pathLen);
  strncpy(&pathToImage[pathLen], path, strlen(path));
  pathToImage[strlen(path) + pathLen] = '\0';

  SDL_Surface *image = surfaceCache->get(pathToImage);
  if(image == 0)
    {
      printf("FAILED TO LOAD IMAGE \"%s\"\n", path);
    }
  else
    {
      if(key && strlen(key) == 6)
	{
	  int r, g, b;
	  sscanf(key, "%2x", &r);
	  sscanf(&key[2], "%2x", &g);
	  sscanf(&key[4], "%2x", &b);
	  
	  SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL,
			  SDL_MapRGB(image->format, r, g, b));
	}

      images[std::string(name)] = image;
    }

  delete[] pathToImage;

  return name;
}

void
Font::addCharToFont(TiXmlElement *element, char *currentImage)
{
  char *id = (char *)element->Attribute("id");
  char ch = id[0];

  SDL_Rect rect;

  rect.w = size_x;
  rect.h = size_y;
  rect.x = atoi(element->Attribute("x")) * size_x;
  rect.y = atoi(element->Attribute("y")) * size_y;

  Character *character = new Character(images[std::string(currentImage)],
				       &rect);

  characters[ch] = character;
}
