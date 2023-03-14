#ifndef SOLDIER_H
#define SOLDIER_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define PLAYER_SPEED 3

class Soldier : public BaseObject
{
public:
  Soldier();
  ~Soldier() {}

  void handleInputAction(SDL_Event event, SDL_Renderer *screen);
  void movePlayer(); // Handle việc di chuyển của player
  void checkTouchMap();
  void setTeam(int _team) { team = _team; }

  SDL_Rect getRectFrame(); // Lấy rect của frame hiện tại
  float velX, velY;        // Vận tốc di chuyển
  bool isHolding;

private:
  Input inputType;
  int team;
};
#endif