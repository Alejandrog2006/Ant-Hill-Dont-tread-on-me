/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"
#include "character.h"
#include "time.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Game {
  Id player_location;       /**< Current location of the player. */
  Player *player;           /**< Pointer to the player. */
  Space *spaces[MAX_SPACES];/**< Array of spaces in the game. */
  Object *objects[MAX_OBJECTS];/**< Array of objects in the game. */
  Character *characters[MAX_CHARACTERS];/**< Array of characters in the game. */
  int n_spaces;             /**< Number of spaces in the game. */
  int n_objects;            /**< Number of objects in the game. */
  int n_characters;         /**< Number of characters in the game. */
  Command *last_cmd;        /**< Last command executed. */
  Bool finished;            /**< Whether the game is finished or not. */
  char last_message[MESSAGE_SIZE + 1]; /**< Last message received from a character. */
  /*TEMPORAL*/
  char temporal_feedback[MESSAGE_SIZE + 1];
};

Status game_create(Game **game) {
  int i;

  if (*game == NULL) {
    *game = (Game *)malloc(sizeof(Game));
    if (!*game) {
      return ERROR;
    }
  }

  /*Initialize seed for random numbers*/
  srand(time(NULL));

  /*Initialize character array*/
  (*game)->n_characters = 0;
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    (*game)->characters[i] = NULL;
  }

  strcpy((*game)->last_message, "\0");

  /*Designed especially for I2 to test character functionality*/
  (*game)->characters[0] = character_create(1);
  character_set_message((*game)->characters[0], "Hello, I am the wizard, don't disturb me!");
  character_set_friendly((*game)->characters[0], TRUE);
  character_set_location((*game)->characters[0], 122);
  character_set_name((*game)->characters[0], "Magnus");

  (*game)->characters[1] = character_create(2);
  character_set_friendly((*game)->characters[1], FALSE);
  character_set_location((*game)->characters[1], 13);
  character_set_name((*game)->characters[1], "Teacher");

  (*game)->n_characters = 2;
  /*End temp for I2*/

  for (i = 0; i < MAX_SPACES; i++) {
    (*game)->spaces[i] = NULL;
  }

  (*game)->n_spaces = 0;
  (*game)->n_objects = 0;
  (*game)->player = player_create(NO_ID);
  if ((*game)->player == NULL) {
    return ERROR;
  }
  /*(*game)->object[0] = object_create(NO_ID);
  if ((*game)->object[0] == NULL) {
    return ERROR;
  }
  (*game)->n_objects++;*/
  (*game)->last_cmd = command_create();
  if ((*game)->last_cmd == NULL) {
    return ERROR;
  }
  (*game)->finished = FALSE;

  return OK;
}

Status game_create_from_file(Game **game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(*game, filename) == ERROR) {
    return ERROR;
  }
  
  if (game_load_objects(*game, filename) == ERROR) {
    return ERROR;
  }

  /* The player is located in the first space */
  game_set_player_location(*game, game_get_space_id_at(*game, 0));
  /*game_set_object_location(*game, game_get_space_id_at(*game, 0), 0);*/

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  if (!game) {
    return ERROR;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (game->spaces[i] != NULL) {
      space_destroy(game->spaces[i]);
      game->spaces[i] = NULL;
    }
  }

  /*Checks all character array and frees as needed*/
  for (i = 0; i < MAX_CHARACTERS; i++)
  {
    if (game->characters[i] != NULL)
    {
      character_destroy(game->characters[i]);
    }
    game->characters[i] = NULL;
  }
  

  if (game->player != NULL) {
    player_destroy(game->player);
    game->player = NULL;
  }

  for (i = 0; i < game->n_objects; i++) {
    if (game->objects[i] != NULL) {
      object_destroy(game->objects[i]);
    }
  }

  if (game->last_cmd != NULL) {
    command_destroy(game->last_cmd);
    game->last_cmd = NULL;
  }

  free(game);
  game = NULL;
  return OK;
}



Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Player *game_get_player(Game *game) {
  if (game == NULL) {
    return NULL;
  }

  return game->player;
}

Id game_get_player_location(Game *game) { 

  Id location =  player_get_location(game->player);

  return location; 
}

Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }
  
  *(player_get_location_pointer(game->player)) = id;

  return OK;
}

Id game_get_object_location(Game *game, int position) { 
  int i = 0;

  if (game == NULL || position < 0 || position >= MAX_OBJECTS || game->objects[position] == NULL) {
    return NO_ID;  
  }
  
  for (i = 0; i < game->n_spaces; i++)
  {
    
    if (game->spaces[i] != NULL  &&  (space_get_id(game->spaces[i]) ==  object_get_location(game->objects[position])) )
    {
      return object_get_location(game->objects[position]);
    }
  }
  
  return NO_ID;
}

Status game_set_object_location(Game *game, Id id, int position) {
  if (position < 0 || position >= MAX_OBJECTS || game == NULL) {
    return ERROR;
  }

  *(object_get_location_pointer(game->objects[position])) = id;

  if (game->n_objects == position){
    game->n_objects++;
  }

  space_set_object(game_get_space(game, id), TRUE);

  return OK;
}

Command* game_get_last_command(Game *game) { 
  return game->last_cmd; 
}

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { 
  return game->finished; 
}

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  for (i = 0; i < game->n_objects; i++)
  {
    printf("=> Object location: %d\n", (int)object_get_id(game->objects[i]));
  }
  
  printf("=> Player location: %d\n", (int)game->player_location);
}

/*ADDITIONAL FUNCTIONS*/

int *game_get_n_spaces(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return &(game->n_spaces);
}

Space** game_get_spaces(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return game->spaces;
}

int *game_get_n_objects(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return &(game->n_objects);
}

Object **game_get_objects(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return game->objects;
}

Character **game_get_character_array(Game *game) {
  if (game == NULL) {
    return NULL;
  }
  return game->characters;
}

Status game_set_last_message(Game *game, const char *message) {
  if (!game || !message) {
    return ERROR;
  }
  strncpy(game->last_message, message, MESSAGE_SIZE);
  game->last_message[MESSAGE_SIZE] = '\0';
  return OK;
}

const char *game_get_last_message(Game *game) {
  if (!game) {
    return NULL;
  }
  return game->last_message;
}

const char *game_get_temporal_feedback(Game *game) {
  if (!game) {
      return NULL;
  }
  return game->temporal_feedback;
}

Status game_set_temporal_feedback(Game *game, const char *feedback) {
  if (!game || !feedback) {
      return ERROR;
  }
  strncpy(game->temporal_feedback, feedback, MESSAGE_SIZE - 1);
  game->temporal_feedback[MESSAGE_SIZE - 1] = '\0';
  return OK;
}