#ifndef MENU_H
#define MENU_H

#include "CommonFunc.h"
#include "TextObject.h"

struct Menu
{
  void initMenu(SDL_Renderer *screen, SDL_Event event, TextObject textObject);
  bool initState;
};

#endif