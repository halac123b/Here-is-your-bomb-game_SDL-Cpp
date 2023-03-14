#include "TextObject.h"

TextObject::TextObject()
{
  textColor.r = 255;
  textColor.g = 255;
  textColor.b = 255;
  textColor.a = 255;
}

TextObject::~TextObject()
{
  free();
}

void TextObject::loadFromRenderText(TTF_Font *font, SDL_Renderer *screen)
{
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, content.c_str(), textColor);
  if (textSurface)
  {
    texture = SDL_CreateTextureFromSurface(screen, textSurface);
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);
  }
}

void TextObject::renderText(SDL_Renderer *screen, int posX, int posY)
{
  SDL_Rect renderQuad = {posX, posY, width, height};
  SDL_RenderCopy(screen, texture, NULL, &renderQuad);
}

void TextObject::free()
{
  if (texture != NULL)
  {
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}

void TextObject::setTextColor(Uint8 red, Uint8 green, Uint8 blue)
{
  textColor.r = red;
  textColor.g = green;
  textColor.b = blue;
}