#include "CommonFunc.h"
#include "BaseObject.h"
#include "Menu.h"
#include "TextObject.h"
#include "TeamObject.h"
#include "Timer.h"
#include "Bomb.h"
#include "ExplosionObject.h"
#include "Sound.h"

#define FPS 60

BaseObject g_background;
int velX = 0, velY = 0;

bool initData()
{
  bool success = true;
  int ret = SDL_Init(SDL_INIT_VIDEO);
  if (ret < 0)
  {
    return false;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  g_window = SDL_CreateWindow("Here is your Bomb",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  if (g_window == NULL)
  {
    success = false;
  }
  else
  {
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if (g_screen == NULL)
    {
      success = false;
    }
    else
    {
      SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
      int imgFlag = IMG_INIT_PNG;
      if (IMG_Init(imgFlag) && imgFlag == false)
      {
        success = false;
      }
    }
    if (TTF_Init() == -1)
    {
      success = false;
    }
    font = TTF_OpenFont("font/FreeSans.ttf", 120);
    if (font == NULL)
    {
      success = false;
    }
  }
  return success;
}

void initSoldier(TeamObject &team)
{
  if (team.side == 1)
  {
    Soldier soldier;
    soldier.setTeam(1);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.2);
    team.soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.5);
    team.soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.25, 666 * 0.8);
    team.soldierList.push_back(soldier);

    for (int i = 0; i < 3; i++)
    {
      team.soldierList[i].loadImg("img/g" + to_string(i) + ".png", g_screen);
    }
  }
  else if (team.side == 2)
  {
    Soldier soldier;
    soldier.setTeam(2);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.2);
    team.soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.5);
    team.soldierList.push_back(soldier);
    soldier.setRect(SCREEN_WIDTH * 0.65, 666 * 0.8);
    team.soldierList.push_back(soldier);

    for (int i = 0; i < 3; i++)
    {
      team.soldierList[i].loadImg("img/r" + to_string(i) + ".png", g_screen);
    }
  }
  team.point = 0;
  team.setIndexControl(0);
  team.special = 1;
}

bool loadBackground()
{
  bool ret = g_background.loadImg("img/playground.png", g_screen);
  if (ret == false)
    return false;
  return true;
}

void close()
{
  g_background.free();
  SDL_DestroyRenderer(g_screen);
  g_screen = NULL;

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  IMG_Quit();
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (initData() == false)
    return -1;

  TextObject textObject;
  Timer timerFPS;
  Sound sound;
  sound.Load("audio/background.mp3");
  sound.Play(-1, 6);

  Menu menu;
  menu.initMenu(g_screen, g_event);

  if (loadBackground() == false)
  {
    return -1;
  }

  Bomb bomb;
  bomb.loadImg("img/bomb.png", g_screen);
  font = TTF_OpenFont("font/FreeSans.ttf", 50);
  textObject.setTextColor(0, 0, 0);

  BaseObject redArrow, greenArrow;
  redArrow.loadImg("img/rArrow.png", g_screen);
  greenArrow.loadImg("img/gArrow.png", g_screen);

  // Init and load image team Red
  TeamObject teamRed(2);
  for (int i = 0; i < 3; i++)
  {
    teamRed.soldierList[i].loadImg("img/r" + to_string(i) + ".png", g_screen);
  }
  teamRed.smallTurret.loadImg("img/smallTurret2.png", g_screen);
  for (int i = 0; i < 2; i++)
  {
    teamRed.bigTurret[i].loadImg("img/bigTurret2.png", g_screen);
  }

  // Team Green
  TeamObject teamGreen(1);
  for (int i = 0; i < 3; i++)
  {
    teamGreen.soldierList[i].loadImg("img/g" + to_string(i) + ".png", g_screen);
  }
  teamGreen.smallTurret.loadImg("img/smallTurret1.png", g_screen);
  for (int i = 0; i < 2; i++)
  {
    teamGreen.bigTurret[i].loadImg("img/bigTurret1.png", g_screen);
  }

  ExplosionObject explosion;
  explosion.loadImg("img/explosion.png", g_screen);
  explosion.clipFrame();

  int frameExpWidth = explosion.getFrameWidth();
  int frameExpHeight = explosion.getFrameHeight();

  bool isQuit = false;
  bool isPlaying = true;
  int winTeam = -1;
  int expFrame = 0;

  while (isQuit == false)
  {
    timerFPS.start();
    if (isPlaying)
    {
      SDL_Rect bombRect = {bomb.getPosX(), bomb.getPosY(), 16, 16};
      while (SDL_PollEvent(&g_event) != 0)
      {
        if (g_event.type == SDL_QUIT)
        {
          isQuit = true;
        }
        teamRed.soldierList[teamRed.getIndexControl()].handleInputAction(g_event, g_screen);
        teamGreen.soldierList[teamGreen.getIndexControl()].handleInputAction(g_event, g_screen);
        if (g_event.type == SDL_KEYDOWN)
        {
          SDL_Keycode key = g_event.key.keysym.sym;
          if (key == SDLK_q)
          {
            teamGreen.switchPlayer();
            bomb.isHolding = 0;
            velX = velY = 0;
          }
          if (key == SDLK_SLASH)
          {
            teamRed.switchPlayer();
            bomb.isHolding = 0;
            velX = velY = 0;
          }
          if (bomb.isHolding != 0)
          {
            if ((key == SDLK_f && bomb.isHolding == 1) || (key == SDLK_KP_1 && bomb.isHolding == 2))
            {
              if (velX == 0 && velY == 0)
              {
                if (bomb.isHolding == 1)
                {
                  velX = 7;
                }
                else
                {
                  velX = -7;
                }
              }
              else if (velX == 0 && velY == -7)
              {
                velX = 7;
              }
              else if (velX == 7 && velY == -7)
              {
                velY = 0;
              }
              else if (velX == 7 && velY == 0)
              {
                velY = 7;
              }
              else if (velX == 7 && velY == 7)
              {
                velX = 0;
              }
              else if (velX == 0 && velY == 7)
              {
                velX = -7;
              }
              else if (velX == -7 && velY == 7)
              {
                velY = 0;
              }
              else if (velX == -7 && velY == 0)
              {
                velY = -7;
              }
              else if (velX == -7 && velY == -7)
              {
                velX = 0;
              }
            }
            if ((key == SDLK_SPACE && bomb.isHolding == 1) || (key == SDLK_RSHIFT && bomb.isHolding == 2))
            {
              if (velX != 0)
              {
                if (velY != 0)
                  bomb.setVelocity(velX * 5 / 7, velY * 5 / 7);
                else
                  bomb.setVelocity(velX, 0);
              }
              else
                bomb.setVelocity(0, velY);
              velX = velY = 0;
              if (bomb.isHolding == 1)
              {
                teamGreen.soldierList[teamGreen.getIndexControl()].isHolding = 0;
              }
              else
              {
                teamRed.soldierList[teamRed.getIndexControl()].isHolding = 0;
              }
              bomb.isHolding = 0;
              break;
            }
            else if ((key == SDLK_SPACE && bomb.isHolding == 2) || (key == SDLK_RSHIFT && bomb.isHolding == 1))
            {
              if (SDLCommonFunc::checkCollison(teamGreen.soldierList[teamGreen.getIndexControl()].getRect(), bombRect) || SDLCommonFunc::checkCollison(teamRed.soldierList[teamRed.getIndexControl()].getRect(), bombRect))
              {
                velX = -velX;
                velY = -velY;
                if (velX != 0)
                {
                  if (velY != 0)
                    bomb.setVelocity(velX * 5 / 7, velY * 5 / 7);
                  else
                    bomb.setVelocity(velX, 0);
                }
                else
                  bomb.setVelocity(0, velY);
                velX = velY = 0;
                if (bomb.isHolding == 1)
                {
                  teamGreen.soldierList[teamGreen.getIndexControl()].isHolding = 0;
                }
                else
                {
                  teamRed.soldierList[teamRed.getIndexControl()].isHolding = 0;
                }
                bomb.isHolding = 0;
                break;
              }
            }
          }
          else
          {
            if (key == SDLK_e && teamGreen.special == 1)
            {
              velX = 10;
              velY = 0;
              if (velX != 0)
              {
                if (velY != 0)
                  bomb.setVelocity(velX * 5 / 7, velY * 5 / 7);
                else
                  bomb.setVelocity(velX, 0);
              }
              else
                bomb.setVelocity(0, velY);
              velX = velY = 0;
              teamGreen.special = 0;
            }
            if (key == SDLK_KP_0 && teamRed.special == 1)
            {
              velX = -10;
              velY = 0;
              if (velX != 0)
              {
                if (velY != 0)
                  bomb.setVelocity(velX * 5 / 7, velY * 5 / 7);
                else
                  bomb.setVelocity(velX, 0);
              }
              else
                bomb.setVelocity(0, velY);
              velX = velY = 0;
              teamRed.special = 0;
            }
            if (key == SDLK_SPACE)
            {
              if (SDLCommonFunc::checkCollison(teamGreen.soldierList[teamGreen.getIndexControl()].getRect(), bombRect))
              {
                bomb.isHolding = 1;
                teamGreen.soldierList[teamGreen.getIndexControl()].isHolding = 1;
              }
            }
            else if (key == SDLK_RSHIFT)
            {
              if (SDLCommonFunc::checkCollison(teamRed.soldierList[teamRed.getIndexControl()].getRect(), bombRect))
              {
                bomb.isHolding = 2;
                teamRed.soldierList[teamRed.getIndexControl()].isHolding = 1;
              }
            }
          }
        }
      }

      SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
      SDL_RenderClear(g_screen);
      g_background.render(g_screen, NULL);

      if (bomb.isHolding == 2)
      {
        bomb.setPos(teamRed.soldierList[teamRed.getIndexControl()].getRect().x, teamRed.soldierList[teamRed.getIndexControl()].getRect().y);
      }
      else if (bomb.isHolding == 1)
      {
        bomb.setPos(teamGreen.soldierList[teamGreen.getIndexControl()].getRect().x, teamGreen.soldierList[teamGreen.getIndexControl()].getRect().y);
      }

      teamRed.smallTurret.render(g_screen);
      for (int i = 0; i < 2; i++)
      {
        teamRed.bigTurret[i].render(g_screen);
      }

      teamGreen.smallTurret.render(g_screen);
      for (int i = 0; i < 2; i++)
      {
        teamGreen.bigTurret[i].render(g_screen);
      }
      for (int i = 0; i < teamRed.soldierList.size(); i++)
      {
        teamRed.soldierList[i].render(g_screen);
      }
      for (int i = 0; i < teamGreen.soldierList.size(); i++)
      {
        teamGreen.soldierList[i].render(g_screen);
      }

      // Render arrow
      greenArrow.setRect(teamGreen.soldierList[teamGreen.getIndexControl()].getRect().x, teamGreen.soldierList[teamGreen.getIndexControl()].getRect().y - 46);
      greenArrow.render(g_screen);

      redArrow.setRect(teamRed.soldierList[teamRed.getIndexControl()].getRect().x, teamRed.soldierList[teamRed.getIndexControl()].getRect().y - 46);
      redArrow.render(g_screen);

      bomb.renderCircle(g_screen); // Render bomb
      bomb.render(g_screen);

      if (velX != 0 || velY != 0)
        bomb.renderIndicator(g_screen, velX, velY);

      font = TTF_OpenFont("font/FreeSans.ttf", 60);
      textObject.setTextColor(0, 0, 0);
      string text;
      text = to_string(teamGreen.point);
      textObject.setContent(text);
      textObject.loadFromRenderText(font, g_screen);
      textObject.renderText(g_screen, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.9);

      text = to_string(teamRed.point);
      textObject.setContent(text);
      textObject.loadFromRenderText(font, g_screen);
      textObject.renderText(g_screen, SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.9);

      if (bomb.existFrame > 0)
      {
        int timerBall = bomb.existFrame / 60 + 1;
        // color settings
        // if (timerBall < 3)
        // {
        //     color.g = 0;
        //     color.b = 0;
        // }

        text = to_string(timerBall);
        textObject.setContent(text);
        textObject.loadFromRenderText(font, g_screen);
        textObject.renderText(g_screen, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.9);
      }

      if (teamGreen.special == 1)
      {
        textObject.setTextColor(0, 128, 0);
        textObject.setContent("S");
        textObject.loadFromRenderText(font, g_screen);
        textObject.renderText(g_screen, 28, SCREEN_HEIGHT * 0.9);
      }

      if (teamRed.special == 1)
      {
        textObject.setTextColor(255, 0, 0);
        textObject.setContent("S");
        textObject.loadFromRenderText(font, g_screen);
        textObject.renderText(g_screen, SCREEN_WIDTH - 58, SCREEN_HEIGHT * 0.9);
      }
      bomb.collision(teamRed);
      bomb.collision(teamGreen);

      int frame = bomb.getFrame();
      if (frame > 0)
        bomb.exist();
      else if (frame == 0)
      {
        bomb.explode(teamGreen, teamRed, g_screen);
        int posX = (bomb.getPosX() + BALLSIZE * 0.5) - frameExpWidth * 0.5;
        int posY = (bomb.getPosY() + BALLSIZE * 0.5) - frameExpHeight * 0.5;
        if (expFrame % 2 == 0)
        {
          explosion.setFrame(expFrame / 2);
          explosion.setRect(posX, posY);
          explosion.show(g_screen);
          if (expFrame == NUM_FRAME_EXP * 2 - 2)
          {
            expFrame = 0;
          }
        }
        expFrame++;
        velX = 0;
        velY = 0;
      }
      else
        bomb.respawnBall();

      if (teamRed.soldierList.size() > 0)
        teamRed.soldierList[teamRed.getIndexControl()].movePlayer();
      if (teamGreen.soldierList.size() > 0)
        teamGreen.soldierList[teamGreen.getIndexControl()].movePlayer();

      SDL_RenderPresent(g_screen);
      if (teamGreen.soldierList.size() == 0 || teamRed.soldierList.size() == 0)
      {
        isPlaying = false;
      }
    }
    else
    {
      SDL_RenderClear(g_screen);
      if (winTeam == -1)
      {
        if (teamGreen.soldierList.size() > 0 && teamRed.soldierList.size() == 0)
        {
          winTeam = 1;
        }
        else if (teamGreen.soldierList.size() == 0 && teamRed.soldierList.size() > 0)
        {
          winTeam = 2;
        }
        else if (teamGreen.soldierList.size() == 0 && teamRed.soldierList.size() == 0)
        {
          if (teamGreen.point > teamRed.point)
          {
            winTeam = 1;
          }
          else if (teamGreen.point < teamRed.point)
          {
            winTeam = 2;
          }
          else
          {
            winTeam = 0;
          }
        }
        while (teamGreen.soldierList.size() > 0)
        {
          teamGreen.removeSoldier();
        }
        while (teamRed.soldierList.size() > 0)
        {
          teamRed.removeSoldier();
        }
      }

      font = TTF_OpenFont("font/FreeSans.ttf", 80);
      textObject.setTextColor(255, 255, 255);
      switch (winTeam)
      {
      case (0):
        menu.loadImg("img/draw.png", g_screen);
        break;
      case (1):
        menu.loadImg("img/greenWin.png", g_screen);
        break;
      case (2):
        menu.loadImg("img/redWin.png", g_screen);
        break;
      }
      menu.render(g_screen);

      textObject.setContent(to_string(teamGreen.point));
      textObject.loadFromRenderText(font, g_screen);
      textObject.renderText(g_screen, 250, 403);

      textObject.setContent(to_string(teamRed.point));
      textObject.loadFromRenderText(font, g_screen);
      textObject.renderText(g_screen, 661, 403);

      SDL_PollEvent(&g_event);
      if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT)
      {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= 352 && mouseX <= 652 && mouseY >= 569 && mouseY <= 664)
        {
          isPlaying = true;
          initSoldier(teamGreen);
          initSoldier(teamRed);
          bomb.setExplodeRadius(70);
          winTeam = -1;
        }
      }
      SDL_RenderPresent(g_screen);
    }

    int realTime = timerFPS.getTick();
    int timePerFrame = 1000 / FPS; // ms
    // Nếu time in game chạy nhanh hơn time quy định của số frame trong 1s của game, delay chương trình để đảm bảo FPS đúng
    if (realTime < timePerFrame)
    {
      SDL_Delay(timePerFrame - realTime);
    }
  }

  return 0;
}