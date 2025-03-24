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

#endif
