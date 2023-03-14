#ifndef BOMB_H
#define BOMB_H

#include "CommonFunc.h"
#include "TeamObject.h"
#include "Sound.h"

#define BALLEXISTFRAME 600
#define BALLSPAWNFRAME 60
#define BALLSIZE 8

class Bomb : public BaseObject
{
private:
  int posX, posY;
  int radius, explosionRadius;
  int travelFrame;

public:
  Sound sound;
  int velocityX, velocityY;
  int existFrame;
  int isHolding;
  int getPosX() { return posX; }
  int getPosY() { return posY; }
  Bomb();
  void setPos(int posX, int posY);
  void setVelocity(int velX, int velY);
  bool isFree();
  int getFrame()
  {
    return existFrame;
  }
  void renderCircle(SDL_Renderer *screen);
  void exist();
  void explode(TeamObject &team1, TeamObject &team2, SDL_Renderer *screen);
  void respawnBall();
  void damage(TeamObject &team1, TeamObject &team2, SDL_Renderer *screen);
  void collision(TeamObject &team);
  bool isInside(int posX, int posY, SDL_Rect rect);
  void renderIndicator(SDL_Renderer *screen, int vx, int vy);
  void setExplodeRadius(int radius) { explosionRadius = radius; }
};

#endif