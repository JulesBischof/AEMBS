/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "platform.h"
#include "game_config.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef enum Game_Screen_e
  {
    GAME_SCREEN_INTRO,     /* show introduction screen */
    GAME_SCREEN_GAMEPLAY,  /* update gameplay screen with all game elements */
    GAME_SCREEN_GAME_LOST, /* game lost */
    GAME_SCREEN_GAME_WON,  /* game won */
    GAME_SCREEN_SHOW_HELP,   /* show help right after startup */
    GAME_SCREEN_SHOW_POINTS, /* show status after game is won */
  }
  Game_Screen_e;

  /*!
   * \brief Show a screen on the display
   * \param screen Game screen to be shown
   */
  void Game_ShowScreen(Game_Screen_e screen);

  /*!
   * \brief View de-initialization
   */
  void Game_ViewDeinit(void);

  /*!
   * \brief View initialization
   */
  void Game_ViewInit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* GAMEVIEW_H_ */
