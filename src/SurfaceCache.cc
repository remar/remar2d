#include "SurfaceCache.h"

SurfaceCache::SurfaceCache()
{

}

SurfaceCache::~SurfaceCache()
{
  std::map<std::string, SDL_Surface *>::iterator it = cache.begin();
  for(;it != cache.end();it++)
    {
      SDL_FreeSurface((*it).second);
    }
}

SDL_Surface *
SurfaceCache::get(const char *path)
{
  SDL_Surface *surface;

  if((surface = cache[std::string(path)]))
    return surface;

  surface = SDL_LoadBMP(path);

  cache[std::string(path)] = surface;

  return surface;
}
