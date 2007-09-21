/*
 *
 * remar2d Graphics Engine
 * TODO: Proper header
 *
 */

#ifndef FRAME_H
#define FRAME_H

class Frame
{
 public:
  int x, y;
  int duration;

  Frame(int x, int y, int duration)
    {
      this->x = x;
      this->y = y;
      this->duration = duration;
    }
};

#endif
