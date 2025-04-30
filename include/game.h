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
#include "link_l.h"

/**
 * @brief Maximum of spaces in a game
 */
#define MAX_SPACES 100

/**
 * @brief Maximum of objects per game
 */
#define MAX_OBJECTS 10

/**
 * @brief Maximum of characters per game
 */
#define MAX_CHARACTERS 5

/**
 * @brief Maximum of links per game
 */
#define MAX_LINKS 400

/**
 * @brief Maximum of player per game
 */
#define MAX_PLAYERS 8

/**
 * @brief Interface structure
 * 
 * This struct stores all of the additional information particular for each player
 */
typedef struct _InterfaceData InterfaceData;

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
 * @param position Int of the position of the object in set
 * @return The ID of the object's current location.
 */
Id game_get_object_location(Game *game, int position);

/**
 * @brief Sets the object's location.
 * @author Profesores PPROG
 *
 * @param game A pointer to the game structure.
 * @param id The ID of the new location.
 * @param position Int of the position of the objet in set
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

/**
 * @brief Gets an object by its ID from the game structure.
 * @author Alejandro Gonzalez
 * 
 * @param game A pointer to the game structure.
 * @param id The ID of the object to retrieve.
 * @return A pointer to the object if found, NULL otherwise.
 */
Object *game_get_object_by_id(Game *game, Id id);

/**
 * @brief Gets the links array of the game
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return The links array if everything went correctly NULL if something went wrong
 */
Link **game_get_links(Game *game);

/**
 * @brief Gets a pointer to the n_links value of the game struct
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return A pointer to the n_links variable if everything went correctly NULL if something went wrong
 */
int *game_get_n_links(Game *game);

/**
 * @brief Gets the destination id in a given direction of a given space
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param id_orig The id of the space where the link begins
 * @param dir The direction of that link
 * @return The destination id of the link that begins in id_orig with the direction dir NO_ID if something went wrong or there's no such link
 */
Id game_get_connection(Game *game, Id id_orig, Direction dir);

/**
 * @brief Returns a bool value, if TRUE, the connection is open between 2 spaces, if FALSE, it's closed
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param id_orig The id of the space where the link begins
 * @param dir The direction of that link
 * @return TRUE if the link between those two spaces is open FALSE if the link between those two spaces is closed or something went wrong
 */
Bool game_connection_is_open(Game *game, Id id_orig, Direction dir);

/**
 * @brief Gets the current turn of the game (the position of a player in the game array)
 * @author Daniel Martín Jaén
 * 
 * @param game The game struct
 * @return A positive integer if everything went right, a negative one if something went wrong
 */
const int game_get_turn(Game *game);

/**
 * @brief Sets the game turn to a give one
 * @author Daniel Martín Jaén
 * 
 * @param game The game struct
 * @param turn_n The new value of the turn variable
 * @return OK if everything went correctly, ERROR if something went wrong
 */
Status game_set_turn(Game *game, int turn_n);

/**
 * @brief Gets the players array from the game struct
 * @author Daniel Martín Jaén
 * 
 * @param game The game struct
 * @return NULL if something went wrong, the players array if everything went correctly
 */
Player **game_get_players(Game *game);

/**
 * @brief Creates a new interface
 * @author Daniel Martín Jaén
 * 
 * @return A pointer to the new interface if everything went correctly, NULL if something went wrong
 */
InterfaceData *game_create_interface();

/**
 * @brief Changes the number of players to a new one
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param n_players The new value of n_players
 * @return OK if everything went correctly, ERROR if something went wrong
 */
Status game_set_n_players(Game *game, int n_players);

/**
 * @brief Gets the number of players
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return A positive integer if everything went correctly, a negative one if something went wrong
 */
const int game_get_n_players(Game *game);

/**
 * @brief Gets the interfaces array from the game struct
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return The array to the interfaces in the game struct if everything went correctly, NULL otherwise
 */
InterfaceData **game_get_interfaces(Game *game);

/**
 * @brief Gets the player pointer of a given position in the players array
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param position The position of the player pointer in the players array
 * @return A pointer to the player in position if everything went well, NULL otherwise
 */
Player *game_get_player_at(Game *game, int position);

#endif