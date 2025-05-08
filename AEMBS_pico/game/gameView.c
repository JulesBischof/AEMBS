/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "game_config.h"
#include "gameController.h"
#include "gameView.h"
#include "gameModel.h"
#include "sprite.h"
#include "McuUtility.h"
#include "McuGDisplaySSD1306.h"
#include "McuFontDisplay.h"
#include "McuFontHelv08Normal.h"
#include "McuFontHelv10Normal.h"
#include "McuFontHelv12Normal.h"
#include "McuFontHelv18Bold.h"

/*!
 * \brief Shows one line of text centered on the display, with a border around it
 * \param text0 Line one of text
 */
static void Show1Liner(const unsigned char *text0)
{
  /*! \todo Make sure things are reentrant! */
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text0, font, NULL) / 2;
  y = McuGDisplaySSD1306_GetHeight() / 2 - charHeight / 2; /* 1 line */
  McuFontDisplay_WriteString((unsigned char *)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1, McuGDisplaySSD1306_GetHeight() - 1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth() - 1 - 4, McuGDisplaySSD1306_GetHeight() - 1 - 4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_UpdateFull();
}

/*!
 * \brief Shows two lines of text centered on the display, with a border around it
 * \param text0 Line one of text
 * \param text1 Line two of text
 */
static void Show2Liner(const unsigned char *text0, const unsigned char *text1)
{
  /*! \todo Make sure things are reentrant! */
  PGFONT_Callbacks font = McuFontHelv12Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text0, font, NULL) / 2;
  y = McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2; /* 2 lines */
  McuFontDisplay_WriteString((unsigned char *)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text1, font, NULL) / 2;
  y += McuGDisplaySSD1306_GetHeight() / 2 - (2 * charHeight) / 2;
  McuFontDisplay_WriteString((unsigned char *)text1, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1, McuGDisplaySSD1306_GetHeight() - 1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth() - 1 - 4, McuGDisplaySSD1306_GetHeight() - 1 - 4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_UpdateFull();
}

static void Show4Liner(const unsigned char *text0, const unsigned char *text1, const unsigned char *text2, const unsigned char *text3)
{
  PGFONT_Callbacks font = McuFontHelv08Normal_GetFont();
  McuFontDisplay_PixelDim x, y;
  McuFontDisplay_PixelDim charHeight, totalHeight;

  McuGDisplaySSD1306_Clear();
  McuFontDisplay_GetFontHeight(font, &charHeight, &totalHeight);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text0, font, NULL) / 2;
  y = McuGDisplaySSD1306_GetHeight() / 2 - (4 * charHeight) / 2; /* 4 lines */
  McuFontDisplay_WriteString((unsigned char *)text0, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text1, font, NULL) / 2;
  y += McuGDisplaySSD1306_GetHeight() / 2 - (4 * charHeight) / 2;
  McuFontDisplay_WriteString((unsigned char *)text1, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text2, font, NULL) / 2;
  y += McuGDisplaySSD1306_GetHeight() / 2 - (4 * charHeight) / 2;
  McuFontDisplay_WriteString((unsigned char *)text2, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  x = McuGDisplaySSD1306_GetWidth() / 2 - McuFontDisplay_GetStringWidth((unsigned char *)text3, font, NULL) / 2;
  y += McuGDisplaySSD1306_GetHeight() / 2 - (4 * charHeight) / 2;
  McuFontDisplay_WriteString((unsigned char *)text3, McuGDisplaySSD1306_COLOR_BLUE, &x, &y, font);

  McuGDisplaySSD1306_DrawBox(0, 0, McuGDisplaySSD1306_GetWidth() - 1, McuGDisplaySSD1306_GetHeight() - 1, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_DrawBox(2, 2, McuGDisplaySSD1306_GetWidth() - 1 - 4, McuGDisplaySSD1306_GetHeight() - 1 - 4, 1, McuGDisplaySSD1306_COLOR_BLUE);
  McuGDisplaySSD1306_UpdateFull();
}

static void showTestScreen(void)
{
  McuGDisplaySSD1306_Clear();

  // McuGDisplaySSD1306_DrawBox(0,
  //                            0,
  //                            McuDisplaySSD1306_GetWidth() - 1,
  //                            McuGDisplaySSD1306_GetHeight() - 1,
  //                            1,
  //                            McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawCircle(20, 30,
                                5,
                                McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawCircle(10, 20,
                                7,
                                McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawLine(0, 0,
                              McuGDisplaySSD1306_GetWidth() - 1,
                              McuGDisplaySSD1306_GetHeight() - 1,
                              McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawLine(30, 30,
                              60, 30,
                              McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawLine(60, 30,
                              45, 45,
                              McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_DrawLine(45, 45,
                              30, 30,
                              McuGDisplaySSD1306_COLOR_WHITE);
  McuGDisplaySSD1306_DrawBox(60, 30,
                             30, 30,
                             5,
                             McuGDisplaySSD1306_COLOR_WHITE);

  McuGDisplaySSD1306_UpdateFull();
}

static void PaintGamePlayScreen(void)
{
  /*! \todo Make sure things are reentrant! */
  McuGDisplaySSD1306_Clear();
  int cntr = 0;
  Sprite_t **sprites;

  do
  {
    sprites = Game_IteratorGetSpriteLists(&cntr);
    if (sprites != NULL)
    {
      Sprite_PaintList(*sprites);
    }
  } while (cntr != 0);
  McuGDisplaySSD1306_UpdateFull();
}

void Game_ShowScreen(Game_Screen_e screen)
{
  switch (screen)
  {
  case GAME_SCREEN_INTRO:
    Show1Liner((const unsigned char *)"AEMBS");
    break;
  case GAME_SCREEN_GAMEPLAY:
    PaintGamePlayScreen();
    break;
  case GAME_SCREEN_GAME_WON:
    Show2Liner((const unsigned char *)"You won!", (const unsigned char *)":-)");
    break;
  case GAME_SCREEN_GAME_LOST:
    Show2Liner((const unsigned char *)"You lost!", (const unsigned char *)":-(");
    break;
  case GAME_SCREEN_SHOW_HELP:
    // showTestScreen();
    Show4Liner((const unsigned char *)"HOW TO NAVIGATE",
               (const unsigned char *)"Joystick up/down",
               (const unsigned char *)"HOW TO SHOOT",
               (const unsigned char *)"press Button");
    break;
  case GAME_SCREEN_SHOW_POINTS:
    char buff[8] = {0};
    int32_t score = Game_GetScore();
    sprintf(buff, "%d", score);

    Show2Liner((const unsigned char *)"Score:", (const unsigned char *)buff);
    break;
  default:
    break;
  }
}

void Game_ViewInit(void)
{
  /* nothing needed */
}

void Game_ViewDeinit(void)
{
  /* nothing needed */
}
