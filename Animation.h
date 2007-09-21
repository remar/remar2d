/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Frame.h"
#include "SDL.h"
#include <list>

using namespace std;

class Animation
{
 public:
  Animation(const char *name);
  ~Animation();
  void addImage(const char *path, int size_x, int size_y,
		int orig_x, int orig_y, const char *key);
  void addFrame(Frame *frame);
  void framesAdded();
  SDL_Surface *getImage();
  SDL_Rect *getRect(int frame);
  void getNextFrame(int *currentFrame, int *timeSpentInTime, int delta);
  void setLooping(bool loop);

  /* Centre point of animation */
  int orig_x, orig_y;

 private:
  const char *name;
  SDL_Surface *image;

  /* Size of frames */
  int size_x, size_y;

  bool looping;

  Frame **frames;
  int numFrames;
  list<Frame *> temp_frames;
};

#endif
