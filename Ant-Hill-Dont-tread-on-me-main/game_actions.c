/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Handles the "unknown" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_unknown(Game *game);

/**
 * @brief Handles the "exit" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_exit(Game *game);

/**
 * @brief Handles the "next" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_next(Game *game);

/**
 * @brief Handles the "back" command.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_actions_back(Game *game);

/**
 * @brief Handles the "take" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
void game_actions_take(Game *game);

/**
 * @brief Handles the "drop" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
void game_actions_drop(Game *game);

/**
 * @brief Handles the "attack" command.
 * @author Izan Robles
 * 
 * @param game A pointer to the game structure.
 */
void game_actions_attack(Game *game);

/**
 * @brief Handles the "left" command.
 * @author Izan Robles
 *
 * @param game A pointer to the game structure.
 */
void game_actions_left(Game *game);

/**
 * @brief Handles the "right" command.
 * @author Izan Robles
 * 
 * @param game A pointer to the game structure.
 */
void game_actions_right(Game *game);

/**
 * @brief Handles the "chat" command.
 * @author Izan Robles
 * 
 * @param game A pointer to the game structure.
 */
void game_actions_chat(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;
  Status status = OK;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      status = ERROR;
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;

    case TAKE:
      game_actions_take(game);
      break;
      
    case DROP:
      game_actions_drop(game);
      break;

    case ATTACK:
      game_actions_attack(game);
      break;
      
    case LEFT:
      game_actions_left(game);
      break;

    case RIGHT: 
      game_actions_right(game);
      break;  

    case CHAT:
      game_actions_chat(game);
      break;
    
    default:
      status = ERROR;
      break;
  }

  return status;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game) {
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  const char *obj_name = NULL;
  int i = 0;
  Command *cmd = game_get_last_command(game);

  if (!cmd) return;


  obj_name = command_get_arg(cmd);
  if (!obj_name || obj_name[0] == '\0') {
    return;
  }

  player_id = game_get_player_location(game);
  
  if (player_get_object(game_get_player(game)) == FALSE) {
    for (i = 0; i < *(game_get_n_objects(game)); i++) {
      object_id = game_get_object_location(game, i);

      if (object_id == player_id && 
          strcasecmp(object_get_name(game_get_objects(game)[i]), obj_name) == 0) {
        game_set_object_location(game, NO_ID, i);
        player_set_object(game_get_player(game), TRUE);
        break;
      }
    }    
  }
}

void game_actions_drop(Game *game) {
  Id object_id = NO_ID;
  Id player_id = NO_ID;
  int i;

  player_id = game_get_player_location(game);

  if ((player_get_object(game_get_player(game)) == TRUE)) {

    for (i = 0; i < *(game_get_n_objects(game)); i++) {
      object_id = game_get_object_location(game, i);

      if (object_id == NO_ID) {
        game_set_object_location(game, player_id, i);  
        player_set_object(game_get_player(game), FALSE); 
      }
    }      
  }
}

void game_actions_attack(Game *game)
{
  Id player_location_id = NO_ID;
  Id character_location_id = NO_ID;
  Player *player = NULL;
  Character **character_array = NULL;
  int i, random;
  char temp[WORD_SIZE];
  
  player = game_get_player(game);
  
  if (!(character_array = game_get_character_array(game)))
  {
    return;
  }

  player_location_id = game_get_player_location(game);
  if (player_location_id == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    character_location_id = character_get_location(character_array[i]);
    if (character_location_id == player_location_id)
    {
      if (character_get_friendly(character_array[i]) == FALSE)
      {
        random = rand() % 2;

        if (random == 0) {
          character_set_health(character_array[i], character_get_health(character_array[i]) - 10);
          strcpy(temp, character_get_name(character_array[i]));
          if (character_get_health(character_array[i]) > 0)
          {
            strcat(temp, " - 10");
            game_set_temporal_feedback(game, temp);
          }
          else
          {
            strcat (temp, " is dead");
            game_set_temporal_feedback(game, temp);
          }
        }
        else {
          
          if (character_get_health(character_array[i]) > 0)
          {
            player_set_health(player, player_get_health(player) - 10 );
            game_set_temporal_feedback(game, "Player - 10");
          }
          else
          {
            strcpy(temp, character_get_name(character_array[i]));
            strcat(temp, " is dead");
            game_set_temporal_feedback(game, temp);
          }
        }
      }
    }
  }
}

void game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_west(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_east(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_chat(Game *game){
  Id player_location_id = NO_ID;
  Id character_location_id = NO_ID;
  Character **character_array = NULL;
  int i;
  const char *message = NULL;
  
  if (!(character_array = game_get_character_array(game)))
  {
    return;
  }

  player_location_id = game_get_player_location(game);
  if (player_location_id == NO_ID)
  {
    return;
  }

  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    character_location_id = character_get_location(character_array[i]);
    if (character_location_id == player_location_id)
    {
      if (character_get_friendly(character_array[i]) == TRUE)
      {
        message = character_get_message(character_array[i]);
        if (message) {
          game_set_last_message(game, message);
        }
      }
    }
  }
}