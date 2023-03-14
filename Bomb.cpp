#include "Bomb.h"

long int sqrD(int x1, int y1, int x2, int y2)
{
  return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

Bomb::Bomb()
{
  this->posX = SCREEN_WIDTH * 0.5;
  this->posY = 666 * 0.5;
  this->velocityX = this->velocityY = 0;
  this->radius = BALLSIZE;
  this->explosionRadius = 70;
  this->existFrame = BALLEXISTFRAME;
  this->travelFrame = 0;
  isHolding = 0;
}

void Bomb::setPos(int posX, int posY)
{
  this->posX = posX;
  this->posY = posY;
}

void Bomb::setVelocity(int velX, int velY)
{
  if (existFrame <= 0)
    return;
  this->velocityX = velX;
  this->velocityY = velY;
  this->travelFrame = 120;
}

bool Bomb::isFree()
{
  if (existFrame > 0)
    return true;
  else
    return false;
}

void Bomb::renderCircle(SDL_Renderer *screen)
{
  if (radius <= 0)
  {
    return;
  }
  const int32_t diameter = (radius * 2);
  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);
  // set ball color
  SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
  while (x >= y)
  {
    SDL_RenderDrawPoint(screen, posX + x, posY - y);
    SDL_RenderDrawPoint(screen, posX + x, posY + y);
    SDL_RenderDrawPoint(screen, posX - x, posY - y);
    SDL_RenderDrawPoint(screen, posX - x, posY + y);
    SDL_RenderDrawPoint(screen, posX + y, posY - x);
    SDL_RenderDrawPoint(screen, posX + y, posY + x);
    SDL_RenderDrawPoint(screen, posX - y, posY - x);
    SDL_RenderDrawPoint(screen, posX - y, posY + x);
    rect.x = posX - BALLSIZE;
    rect.y = posY - BALLSIZE;
    if (error <= 0)
    {
      ++y;
      error += ty;
      ty += 2;
    }
    if (error > 0)
    {
      --x;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void Bomb::exist()
{
  // timer 7 secs
  if (existFrame <= 0)
    return;
  existFrame--;
  travelFrame--;
  // reset velocity when exploding
  if (existFrame == 0)
    travelFrame = 0;
  if (travelFrame == 0)
    velocityX = velocityY = 0;
  // ball's traveling
  if ((velocityX == 0) && (velocityY == 0))
    return;
  posX += velocityX;
  posY += velocityY;
}

void Bomb::explode(TeamObject &team1, TeamObject &team2, SDL_Renderer *screen)
{
  if (existFrame != 0)
    return;
  radius += 4;
  isHolding = 0;
  if (radius > explosionRadius)
  {
    existFrame = -1;
    radius = 0;
    damage(team1, team2, screen);
  }
}

void Bomb::respawnBall()
{
  // timer 1 sec
  if (existFrame >= 0)
    return;
  existFrame--;
  // spawn the ball but can't be controled
  if (-existFrame == BALLSPAWNFRAME / 2)
  {
    posX = SCREEN_WIDTH / 2; // random in range 101 - 400
    posY = 666 / 2 - 150 + rand() % 300;
  }
  if (-existFrame > BALLSPAWNFRAME / 2)
  {
    radius = BALLSIZE + (BALLSPAWNFRAME + existFrame) / 3;
  }
  // free the ball, increase explosion radius
  if (-existFrame > BALLSPAWNFRAME)
  {
    radius = BALLSIZE;
    explosionRadius = (int)(1.3 * explosionRadius);
    existFrame = BALLEXISTFRAME;
  }
}

void Bomb::damage(TeamObject &team1, TeamObject &team2, SDL_Renderer *screen)
{
  if (explosionRadius > 800)
  {
    team1.point += 4;
    team2.point += 4;
    return;
  }
  // squared distance
  long int d;
  // Big tower
  for (int i = 0; i < 2; i++)
  {
    if (sqrD(posX, posY, team1.bigTurret[i].getRect().x + 30, team1.bigTurret[i].getRect().y + 30) < explosionRadius * explosionRadius)
      team2.point += 1;
    if (sqrD(posX, posY, team2.bigTurret[i].getRect().x + 30, team2.bigTurret[i].getRect().y + 30) < explosionRadius * explosionRadius)
      team1.point += 1;
  }

  for (int i = 0; i < team1.soldierList.size(); i++)
  {
    if (sqrD(posX, posY, team1.soldierList[i].getRect().x + 30, team1.soldierList[i].getRect().y + 30) < explosionRadius * explosionRadius)
    {
      team1.removeSoldier(i, screen);
      i--;
    }
  }
  for (int i = 0; i < team2.soldierList.size(); i++)
  {
    if (sqrD(posX, posY, team2.soldierList[i].getRect().x + 30, team2.soldierList[i].getRect().y + 30) < explosionRadius * explosionRadius)
    {
      team2.removeSoldier(i, screen);
      i--;
    }
  }

  // Small tower
  if (sqrD(posX, posY, team1.smallTurret.getRect().x + 20, team1.smallTurret.getRect().y + 20) < explosionRadius * explosionRadius)
    team2.point += 2;
  if (sqrD(posX, posY, team2.smallTurret.getRect().x + 20, team2.smallTurret.getRect().y + 20) < explosionRadius * explosionRadius)
    team1.point += 2;
}

void Bomb::collision(TeamObject &team)
{
  if (velocityX == 0 && velocityY == 0)
  {
    return;
  }
  int nextX = posX + velocityX;
  int nextY = posY + velocityY;
  SDL_Rect screenRect = {5, 5, SCREEN_WIDTH - 15, 666 - 10};
  // top & left edges of inner yard collision
  if (isInside(posX, nextY, screenRect) == false)
    velocityY = -velocityY;
  if (team.side == 1)
  {
    // with towers
    if (posX < SCREEN_WIDTH * 0.15)
    {
      // left edge of inner yard collision
      if (isInside(nextX, posY, screenRect) == false)
        velocityX = -velocityX;
      // towerA2 collision
      if (isInside(posX, nextY, team.smallTurret.getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.smallTurret.getRect()) == true)
        velocityX = -velocityX;
      return;
    }
    if (posX >= SCREEN_WIDTH * 0.15 && posX < SCREEN_WIDTH * 0.25)
    {
      // towerA1 collision
      if (isInside(posX, nextY, team.bigTurret[0].getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.bigTurret[0].getRect()) == true)
        velocityX = -velocityX;
      // towerA3 collision
      if (isInside(posX, nextY, team.bigTurret[1].getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.bigTurret[1].getRect()) == true)
        velocityX = -velocityX;
    }
  }

  if (team.side == 2)
  {
    if (posX >= SCREEN_WIDTH * 0.65 && posX < SCREEN_WIDTH * 0.9)
    {
      // towerB1 collision
      if (isInside(posX, nextY, team.bigTurret[0].getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.bigTurret[0].getRect()) == true)
        velocityX = -velocityX;
      // towerB3 collision
      if (isInside(posX, nextY, team.bigTurret[1].getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.bigTurret[1].getRect()) == true)
        velocityX = -velocityX;
    }
    if (posX >= SCREEN_WIDTH * 0.9)
    {
      // right edge of inner yard collision
      if (isInside(nextX, posY, screenRect) == false)
        velocityX = -velocityX;
      // towerB2 collision
      if (isInside(posX, nextY, team.smallTurret.getRect()) == true)
        velocityY = -velocityY;
      if (isInside(nextX, posY, team.smallTurret.getRect()) == true)
        velocityX = -velocityX;
      return;
    }
  }
}

bool Bomb::isInside(int posX, int posY, SDL_Rect rect)
{
  if ((posX < rect.x) || (posX > rect.x + rect.w))
    return false;
  if ((posY < rect.y) || (posY > rect.y + rect.h))
    return false;
  return true;
}

void Bomb::renderIndicator(SDL_Renderer *screen, int vx, int vy)
{
  if (vx == 0 && vy == 0)
    return;
  int x = posX, y = posY;
  //    SDL_RenderDrawPoint(renderer, x + 2 * vx, y + 2 * vy);
  thickLineRGBA(screen, x + vx, y + vy, x + 6 * vx, y + 6 * vy, 5, 255, 0, 0, 255);
}