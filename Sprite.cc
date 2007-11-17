#include "Sprite.h"

Sprite::Sprite(char *file)
  : name("")
{
  printf("Loading sprite \"%s\"\n", file);

  TiXmlDocument doc(file);

  if(!doc.LoadFile())
    {
      return;
    }

  TiXmlNode *sprite = 0, *animation = 0, *node = 0;
  TiXmlElement *element = 0;

  /* Locate the 'sprite' node */
  sprite = doc.FirstChild("sprite");
  if(sprite)
    {
      TiXmlElement *sprite_elm = sprite->ToElement();

      char *n = (char *)sprite_elm->Attribute("name");
      name = new char[strlen(n) + 1];
      strncpy(name, n, strlen(n) + 1);

      while(animation = sprite->IterateChildren("animation", animation))
	{
	  element = animation->ToElement();

	  // startNewAnimation(element->Attribute("name"));
	  startNewAnimation(element);

	  while(node = animation->IterateChildren(node))
	    {
	      element = node->ToElement();
	      if(strcmp(element->Value(), "image") == 0)
		{
		  addImageToAnimation(element, file);
		}
	      else if(strcmp(element->Value(), "frame") == 0)
		{
		  addFrameToAnimation(element);
		}
	    }

	  animations[currentAnimation]->framesAdded();
	}
    }
}

Sprite::~Sprite()
{
  /* Delete animations */
  delete [] name;
  animations.clear();
}

char *
Sprite::getName()
{
  return name;
}

Animation *
Sprite::getAnimation(char *animName)
{
  return animations[animName];
}

void
Sprite::startNewAnimation(TiXmlElement *element)
{
  const char *name = element->Attribute("name");
  const char *loop = element->Attribute("loop");
  Animation *anim = new Animation(name);
  
  if(loop && strcmp(loop, "false") == 0)
    {
      anim->setLooping(false);
    }

  animations[string(name)] = anim;
  currentAnimation = name;
}

void
Sprite::addImageToAnimation(TiXmlElement *element, char *pathToXml)
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

  const char *path = element->Attribute("path");
  int size_x = atoi(element->Attribute("size_x"));
  int size_y = atoi(element->Attribute("size_y"));
  int orig_x = atoi(element->Attribute("orig_x"));
  int orig_y = atoi(element->Attribute("orig_y"));
  const char *key = element->Attribute("key");

  char *pathToImage = new char[strlen(path) + pathLen + 1];
  strncpy(pathToImage, pathToXml, pathLen);
  strncpy(&pathToImage[pathLen], path, strlen(path));
  pathToImage[strlen(path) + pathLen] = '\0';

  animations[currentAnimation]->addImage(pathToImage, size_x, size_y,
					 orig_x, orig_y, key);

  delete[] pathToImage;
}

void
Sprite::addFrameToAnimation(TiXmlElement *element)
{
  int x = atoi(element->Attribute("x"));
  int y = atoi(element->Attribute("y"));
  int dur = atoi(element->Attribute("dur"));

  Frame *frame = new Frame(x, y, dur);

  animations[currentAnimation]->addFrame(frame);
}
