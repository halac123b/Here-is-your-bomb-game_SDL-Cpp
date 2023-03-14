#include "Soldier.h"
#include <iostream>

Soldier::Soldier()
{
  velX = velY = 0;
  // Init các gt input về 0
  inputType.left = inputType.right = inputType.down = inputType.up = 0;
  team = -1;
  isHolding = 0;
}

void Soldier::handleInputAction(SDL_Event event, SDL_Renderer *screen)
{
  if (event.type == SDL_KEYDOWN)
  {
    SDL_Keycode key = event.key.keysym.sym;
    if (team == 1)
    {
      if (key == SDLK_a)
      {
        inputType.right = 0;
        inputType.left = 1; // Tránh user nhấn 2 phím cùng lúc
      }
      else if (key == SDLK_d)
      {
        inputType.left = 0;
        inputType.right = 1;
      }
      else if (key == SDLK_w)
      {
        inputType.up = 1;
        inputType.down = 0;
      }
      else if (key == SDLK_s)
      {
        inputType.down = 1;
        inputType.up = 0;
      }
    }
    else if (team == 2)
    {
      if (key == SDLK_RIGHT)
      {
        inputType.right = 1;
        inputType.left = 0; // Tránh user nhấn 2 phím cùng lúc
      }
      else if (key == SDLK_LEFT)
      {
        inputType.left = 1;
        inputType.right = 0;
      }
      else if (key == SDLK_UP)
      {
        inputType.up = 1;
        inputType.down = 0;
      }
      else if (key == SDLK_DOWN)
      {
        inputType.down = 1;
        inputType.up = 0;
      }
    }
  }
  else if (event.type == SDL_KEYUP)
  {
    SDL_Keycode key = event.key.keysym.sym;
    if (team == 1)
    {
      if (key == SDLK_a)
      {
        inputType.left = 0;
      }
      else if (key == SDLK_d)
      {
        inputType.right = 0;
      }
      else if (key == SDLK_w)
      {
        inputType.up = 0;
      }
      else if (key == SDLK_s)
      {
        inputType.down = 0;
      }
    }
    else if (team == 2)
    {
      if (key == SDLK_RIGHT)
      {
        inputType.right = 0;
      }
      else if (key == SDLK_LEFT)
      {
        inputType.left = 0;
      }
      else if (key == SDLK_UP)
      {
        inputType.up = 0;
      }
      else if (key == SDLK_DOWN)
      {
        inputType.down = 0;
      }
    }
  }
}

void Soldier::movePlayer()
{
  velX = velY = 0;
  float velPlus;
  if (!isHolding)
    velPlus = PLAYER_SPEED;
  else
    velPlus = PLAYER_SPEED * 0.8;
  if (inputType.right == 1)
  {
    velX += velPlus;
  }
  if (inputType.left == 1)
  {
    velX -= velPlus;
  }
  if (inputType.up == 1)
  {
    velY -= velPlus;
  }
  if (inputType.down == 1)
  {
    velY += velPlus;
  }
  checkTouchMap();
}

void Soldier::checkTouchMap()
{
  // Check theo chiều ngang (horizontal)
  // Check ô tiếp theo di chuyển tới là bức tường
  if (rect.x + velX <= 0 || rect.x + velX + rect.w >= SCREEN_WIDTH)
  {
    velX = 0;
  }

  if (rect.y + velY + rect.h >= 666 || rect.y + velY <= 0)
  {
    velY = 0;
  }
  rect.x += velX;
  rect.y += velY;
}
