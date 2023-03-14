#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "CommonFunc.h"

struct TextObject
{
  TextObject();
  ~TextObject();
  void setTextColor(Uint8 red, Uint8 green, Uint8 blue);
  void setContent(string text) { content = text; }
  string getContent() { return content; }
  void loadFromRenderText(TTF_Font *font, SDL_Renderer *screen);
  void renderText(SDL_Renderer *screen, int posX, int posY);
  void free();
  int getWidth() { return width; }
  int getHeight() { return height; }

  SDL_Texture *texture;
  SDL_Color textColor;
  string content;
  int width;
  int height;
};

#endif