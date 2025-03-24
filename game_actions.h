/**
 * @brief It defines the game actions
 *
 * @file game_actions.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"
#include "character.h"
#include "player.h"

/**
 * @brief Updates the game state based on the given command.
 * @author Profesores PPROG
 * 
 * @param game A pointer to the game structure to be updated.
 * @param cmd A pointer to the command to be processed.
 * @return OK if the update was successful, ERROR otherwise.
 */
Status game_actions_update(Game *game, Command *cmd);

#endif

