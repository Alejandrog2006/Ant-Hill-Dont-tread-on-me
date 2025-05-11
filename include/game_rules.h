#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "game.h"
#include "game_reader.h"


/**
 * @brief Takes in the last command and excutes an event, either based on the command or the game itself
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param last_cmd A pointer to the last command
 */
Status game_rules_event(Game *game, Command *last_cmd);

/**
 * @brief Creates a new object inside the given space
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param space A pointer to the space where the object is being added to
 * @return NULL if something went wrong, a pointer to the new object otherwise
 */
Object *event_create_object(Game *game, Space *space);

/**
 * @brief Creates a space adjacent to the current one in one of the directions
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param current_id The id of the space where the player is
 * @param dir The direction where the new space will be created
 * @return NULL if something went wrong, a pointer to the new space otherwise
 */
Space *event_create_space(Game *game, Id current_id, Direction dir);

/**
 * @brief Creates a character in a given space
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param space A pointer to the space where the character is being added
 * @return NULL if something went wrong, a pointer to the new object otherwise
 */
Character *event_create_character(Game *game, Space *space);