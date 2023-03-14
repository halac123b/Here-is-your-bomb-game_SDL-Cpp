#include "TeamObject.h"

TeamObject::TeamObject(int index)
{
  side = index;
  if (index == 1)
  {
    Soldier soldier;
    soldier.setTeam(1);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.2);
    soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.5);
    soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.8);
    soldierList.push_back(soldier);

    SmallTurret sTurret;
    smallTurret = sTurret;
    smallTurret.setRect(SCREEN_WIDTH * 0.05, 666 * 0.6);

    BigTurret tTurret;
    bigTurret.push_back(tTurret);
    bigTurret[0].setRect(SCREEN_WIDTH * 0.15, 666 * 0.2);
    bigTurret.push_back(tTurret);
    bigTurret[1].setRect(SCREEN_WIDTH * 0.15, 666 * 0.7);
  }
  else if (index == 2)
  {
    Soldier soldier;
    soldier.setTeam(2);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.2);
    soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.5);
    soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.8);
    soldierList.push_back(soldier);

    SmallTurret sTurret;
    smallTurret = sTurret;
    smallTurret.setRect(SCREEN_WIDTH * 0.9, 666 * 0.4);

    BigTurret tTurret;
    bigTurret.push_back(tTurret);
    bigTurret[0].setRect(SCREEN_WIDTH * 0.8, 666 * 0.2);
    bigTurret.push_back(tTurret);
    bigTurret[1].setRect(SCREEN_WIDTH * 0.8, 666 * 0.7);
  }
  indexControl = 0;
  point = 0;
}

void TeamObject::removeSoldier()
{
  soldierList[soldierList.size() - 1].free();
  soldierList.erase(soldierList.end());
}

void TeamObject::removeSoldier(int index, SDL_Renderer *screen)
{
  while (index > soldierList.size() - 1)
  {
    index--;
  }
  soldierList[index].free();
  soldierList.erase(soldierList.begin() + index);
  if (soldierList.size() > 0)
  {
    if (side == 1)
    {
      soldierList[soldierList.size() - 1].loadImg("img/soldier1.png", screen);
    }
    else if (side == 2)
    {
      soldierList[soldierList.size() - 1].loadImg("img/soldier2.png", screen);
    }
  }
  if (getIndexControl() >= soldierList.size())
  {
    setIndexControl(0);
  }
}

void TeamObject::switchPlayer()
{
  if (soldierList.size() <= 0)
  {
    return;
  }
  indexControl++;
  if (indexControl >= soldierList.size())
  {
    indexControl = 0;
  }
}

bool TeamObject::checkIsLose()
{
  if (soldierList.size() == 0)
  {
    return true;
  }
  return false;
}