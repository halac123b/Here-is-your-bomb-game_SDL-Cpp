#ifndef SMALL_TURRET_H
#define SMALL_TURRET_H

#include "CommonFunc.h"
#include "BaseObject.h"

class SmallTurret : public BaseObject
{
public:
  SmallTurret() {}

private:
  int point = 10;
};

#endif
