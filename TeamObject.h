#ifndef TEAM_OBJECT_H
#define TEAM_OBJECT_H

#include "CommonFunc.h"
#include "Soldier.h"
#include "BigTurret.h"
#include "SmallTurret.h"

class TeamObject
{
public:
  TeamObject(int index);
  void removeSoldier();
  void removeSoldier(int index, SDL_Renderer *screen);
  void switchPlayer();
  bool checkIsLose();
  // SmallTurret getSmallTurret() { return smallTurret; }
  // vector<BigTurret> getBigturret() { return bigTurret; }
  int getIndexControl() { return indexControl; }
  void setIndexControl(int idx) { indexControl = idx; }
  vector<Soldier> soldierList;
  SmallTurret smallTurret;
  vector<BigTurret> bigTurret;
  int point;
  int side;
  int special;

private:
  int indexControl;
};

#endif