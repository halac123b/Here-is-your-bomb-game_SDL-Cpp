#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "BaseObject.h"

class Menu : public BaseObject
{
public:
  void initMenu(SDL_Renderer *screen, SDL_Event event);
  bool initState;
};

#endif