#ifndef SURFACE_CACHE_H
#define SURFACE_CACHE_H

#include "SDL.h"
#include <map>
#include <string>

class SurfaceCache
{
 public:
  SurfaceCache();
  ~SurfaceCache();
  SDL_Surface *get(const char *path);

 private:
  std::map<std::string, SDL_Surface *> cache;
};

#endif
