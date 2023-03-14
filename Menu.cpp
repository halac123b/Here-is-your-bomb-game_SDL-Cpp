#include "Menu.h"

void Menu::initMenu(SDL_Renderer *screen, SDL_Event event)
{
  initState = true;

  font = TTF_OpenFont("font/FreeSans.ttf", 120);
  SDL_Rect backRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  loadImg("img/start.png", screen);

  while (initState)
  {
    // SDL_RenderFillRect(screen, &backRect);
    render(screen);
    SDL_RenderPresent(screen);

    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
      SDL_Quit();
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
      int mouseX, mouseY;
      SDL_GetMouseState(&mouseX, &mouseY);
      if (mouseX >= 349 && mouseX <= 651 && mouseY >= 568 && mouseY <= 664)
      {
        initState = false;
      }
    }
  }
}
