#include "Menu.h"

void Menu::initMenu(SDL_Renderer *screen, SDL_Event event, TextObject textObject)
{
  initState = true;

  font = TTF_OpenFont("font/FreeSans.ttf", 120);
  SDL_Rect backRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  textObject.setTextColor(255, 255, 255);

  while (initState)
  {
    // SDL_RenderFillRect(screen, &backRect);
    textObject.setContent("Start game");
    textObject.loadFromRenderText(font, screen);
    textObject.renderText(screen, SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.5);
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
      if (mouseX >= SCREEN_WIDTH * 0.3 && mouseX <= SCREEN_WIDTH * 0.3 + textObject.getWidth() && mouseY >= SCREEN_HEIGHT * 0.5 && mouseY <= SCREEN_HEIGHT * 0.5 + textObject.getHeight())
      {
        initState = false;
      }
    }
  }
}
