/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "objects.h"
#include "player.h"
#include "character.h"

#define MAX_SPACES 100
#define MAX_OBJECTS 10
#define MAX_CHARACTERS 5

/**
 * @brief Game structure.
 *
 * This struct stores all the information related to the game, including the player,
 * objects, spaces, and the last command executed.
 */
typedef struct _Game Game;

/**
 * @brief Creates a new game.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure to be initialized.
 * @return OK if the game was successfully created, ERROR otherwise.
 */
Status game_create(Game **game);

/**
 * @brief Creates a new game from a file.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure to be initialized.
 * @param filename The name of the file containing the game data.
 * @return OK if the game was successfully created, ERROR otherwise.
 */
Status game_create_from_file(Game **game, char *filename);

/**
 * @brief Destroys a game, freeing the allocated memory.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure to be destroyed.
 * @return OK if the game was successfully destroyed, ERROR otherwise.
 */
Status game_destroy(Game *game);


/**
 * @brief Gets a space by its ID.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param id The ID of the space to retrieve.
 * @return A pointer to the space, or NULL if the space is not found.
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Gets a space by its ID.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param id The ID of the space to retrieve.
 * @return A pointer to the space, or NULL if the space is not found.
 */
Player *game_get_player(Game *game);

/**
 * @brief Gets the player's current location.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @return The ID of the player's current location.
 */
Id game_get_player_location(Game *game);

/**
 * @brief Sets the player's location.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param id The ID of the new location.
 * @return OK if the location was successfully set, ERROR otherwise.
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Gets the object's current location.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @return The ID of the object's current location.
 */
Id game_get_object_location(Game *game, int position);

/**
 * @brief Sets the object's location.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param id The ID of the new location.
 * @return OK if the location was successfully set, ERROR otherwise.
 */
Status game_set_object_location(Game *game, Id id, int position);

/**
 * @brief Gets the last command executed.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @return A pointer to the last command executed.
 */
Command* game_get_last_command(Game *game);

/**
 * @brief Sets the last command executed.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param command A pointer to the command to be set as the last command.
 * @return OK if the command was successfully set, ERROR otherwise.
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief Checks if the game is finished.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @return TRUE if the game is finished, FALSE otherwise.
 */
Bool game_get_finished(Game *game);

/**
 * @brief Sets the game's finished status.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param finished The new finished status.
 * @return OK if the status was successfully set, ERROR otherwise.
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Prints the game state.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 */
void game_print(Game *game);

/*ADDITIONAL FUNCTIONS*/

/**
 * @brief Gets the number of spaces in the game.
 *
 * @param game A pointer to the game structure.
 * @return The number of spaces in the game.
 */
int *game_get_n_spaces(Game *game);

/**
 * @brief Gets the spaces in the game.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 * @return The spaces in the game.
 */
Space** game_get_spaces(Game *game);

/**
 * @brief Gets the number of objects in the game.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 * @return The number of objects in the game.
 */
int *game_get_n_objects(Game *game);

/**
 * @brief Gets the objects in the game.
 * @author Alejandro Gonzalez
 *
 * @param game A pointer to the game structure.
 * @return The objects in the game.
 */
Object** game_get_objects(Game *game);

/**
 * @brief Gets the characters in the game.
 * @author Izan Robles
 * 
 * @param game A pointer to the game structure.
 * @return A pointer to the array of characters in the game
 */
Character **game_get_character_array(Game *game);

/**
 * @brief Sets the last message received from a character
 * @author Izan Robles
 *
 * @param game A pointer to the game
 * @param message The message to store
 * @return OK if successful, ERROR otherwise
 */
Status game_set_last_message(Game *game, const char *message);

/**
 * @brief Gets the last message received from a character
 * @author Izan Robles
 *
 * @param game A pointer to the game
 * @return The last message or NULL if none exists
 */
const char *game_get_last_message(Game *game);

/**
 * @brief Gets the temporal feedback of the game
 * @author Izan Robles
 * 
 * @param game A pointer to the game
 * @return The temporal feedback or NULL if none exists
 */
const char *game_get_temporal_feedback(Game *game);

/**
 * @brief Sets the temporal feedback of the game
 * @author Izan Robles
 * 
 * @param game A pointer to the game
 * @param feedback The feedback to store
 * @return OK if successful, ERROR otherwise
 */
Status game_set_temporal_feedback(Game *game, const char *feedback);


#endif