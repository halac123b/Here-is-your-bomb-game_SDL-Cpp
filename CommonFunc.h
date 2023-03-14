#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

using namespace std;

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_screen = NULL;
static SDL_Event g_event;
static TTF_Font *font = NULL;

// Screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 733;
const int SCREEN_BPP = 32; // Bit by pixel

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

struct Input
{
  int up;
  int down;
  int left;
  int right;
};

namespace SDLCommonFunc
{
  bool checkCollison(const SDL_Rect &object1, const SDL_Rect &object2);
}

#endif