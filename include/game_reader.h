/**
 * @brief Implements the game reader from datafile
 * @file game_reader.h
 * @author Daniel Martin Jaen
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Loads spaces for a Map inside a game structure.
 * @author Profesores PPROG
 * 
 * @param game A pointer to the game structure to be updated.
 * @param filename A string with the name of the file containing space data.
 * @return OK if the spaces were loaded successfully, ERROR otherwise.
 */
Status game_load_spaces(Game *game, char *filename);

/**
 * @brief Adds a space to the Game structure
 * @author Profesores PPROG
 * 
 * @param game A pointer to the game structure to be updated.
 * @param space A pointer to the space to be added.
 * @return OK if the space was added successfully, ERROR otherwise.
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Gets the Id of the Space in the "position" its list 
 * @author Profesores PPROG
 * 
 * @param game A pointer to the game structure to be updated.
 * @param position The position of the space in the game's space list.
 * @return Id of the Space within the "position" of the array, NO_ID if there was an error.
 */
Id game_get_space_id_at(Game *game, int position);

/**
 * @brief Loads objects for a Map inside a game structure.
 * @author Alejandro Gonzalez
 * 
 * @param game A pointer to the game structure to be updated.
 * @param filename A string with the name of the file containing object data.
 * @return OK if the objects were loaded successfully, ERROR otherwise.
 */
Status game_load_objects(Game *game, char *filename);

/**
 * @brief Adds an object to the Game structure
 * @author Alejandro Gonzalez
 * 
 * @param game A pointer to the game structure to be updated.
 * @param object A pointer to the object to be added.
 * @return OK if the object was added successfully, ERROR otherwise.
 */
Status game_add_objects(Game *game, Object *object);

/**
 * @brief Adds a link to the Game structure
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game structure
 * @param link A pointer to the link that's being added
 * @return OK if everything went correctly, ERROR if something went wrong
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief Loads the links into the game structure from a given file
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param filename A pointer to the name string of the file
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status game_load_links(Game *game, char *filename);

/**
 * @brief Loads the players into the game structure from a given file (currently only works with one player)
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param filename A pointer to the name string of the file
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status game_load_players(Game *game, char *filename);

/**
 * @brief Returns the value of n_characters from the game struct
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @return A pointer to the n_characters value stored into the game struct NULL if there was an error
 */
int *game_get_n_characters(Game *game);

/**
 * @brief Adds a character to the game struct
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param char_p A pointer to the new charcter that's being added
 * @return OK if everything went correctly, ERROR if something went wrong
 */
Status game_add_character(Game *game, Character *char_p);

/**
 * @brief Loads the characters into the game struct from a given file
 * @author Daniel Martín Jaén
 * 
 * @param game A pointer to the game struct
 * @param filename A pointer to the name string
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status game_load_characters(Game *game, char *filename);

/**
 * @brief Adds a player to the game struct
 * @author Daniel Martín Jaén
 *  
 * @param game A pointer to the game struct
 * @param player A pointer to the struct of the player that's being added
 * @return OK if everything went correctly ERROR if something went wrong
 */
Status game_add_player(Game *game, Player *player);

#endif
