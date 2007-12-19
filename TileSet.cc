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

#include "TileSet.h"
#include "tinyxml.h"

TileSet::TileSet(char *file)
  : size_x(0), size_y(0), image(0), name("")
{
  printf("Loading tileset \"%s\"\n", file);

  TiXmlDocument doc(file);

  if(!doc.LoadFile())
    {
      return;
    }

  TiXmlNode *node;

  node = doc.FirstChild("tileset");
  if(node)
    {
      TiXmlElement *element = node->ToElement();

      char *n = (char *)element->Attribute("name");
      name = new char[strlen(n) + 1];
      strncpy(name, n, strlen(n) + 1);

      node = node->FirstChild("image");

      element = node->ToElement();

      const char *path = element->Attribute("path");
      size_x = atoi(element->Attribute("size_x"));
      size_y = atoi(element->Attribute("size_y"));
      const char *key = element->Attribute("key"); // color key

      int pathLen;
      for(int i = strlen(file);i >= 0;i--)
	{
	  if(file[i] == '/')
	    {
	      pathLen = i + 1;
	      break;
	    }
	}

      char *pathToImage = new char[strlen(path) + pathLen + 1];
      strncpy(pathToImage, file, pathLen);
      strncpy(&pathToImage[pathLen], path, strlen(path));
      pathToImage[strlen(path) + pathLen] = '\0';

      image = SDL_LoadBMP(pathToImage);

      if(key)
	{
	  if(strlen(key) == 6)
	    {
	      int r, g, b;
	      sscanf(key, "%2x", &r);
	      sscanf(&key[2], "%2x", &g);
	      sscanf(&key[4], "%2x", &b);
	      
	      SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL,
			      SDL_MapRGB(image->format, r, g, b));
	    }
	}

      /* TODO: Error handling */
    }
}

TileSet::~TileSet()
{
  /* Delete allocated surface */
  SDL_FreeSurface(image);
  image = 0;
}

char *
TileSet::getName()
{
  return name;
}

SDL_Rect *
TileSet::getRect(int x, int y)
{
  rect.w = size_x;
  rect.h = size_y;
  rect.x = x * size_x;
  rect.y = y * size_y;

  return &rect;
}

SDL_Surface *
TileSet::getImage()
{
  return image;
}
