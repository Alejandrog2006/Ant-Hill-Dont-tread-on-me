/**
 * @brief It defines the character module interface
 *
 * @file character.h
 * @author Izan Robles
 * @version 1.0
 * @date 03-03-2024
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

#define GDESC_SIZE 7
#define MESSAGE_SIZE 1024

typedef struct _Character Character;

/**
 * @brief Creates a new character
 * @author Izan Robles
 *
 * @param id The identifier for the new character
 * @return A pointer to the new character, NULL if error
 */
Character *character_create(Id id);

/**
 * @brief Destroys a character, freeing allocated memory
 * @author Izan Robles
 *
 * @param character A pointer to the character to destroy
 * @return OK if successful, ERROR if there was a problem
 */
Status character_destroy(Character *character);

/**
 * @brief Gets the character's id
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's id
 */
Id character_get_id(Character *character);

/**
 * @brief Sets the character's name
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param name The name to set
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_name(Character *character, char *name);

/**
 * @brief Gets the character's name
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's name
 */
const char *character_get_name(Character *character);

/**
 * @brief Sets the character's graphic description
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param gdesc The graphic description to set (6 characters)
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_gdesc(Character *character, char *gdesc);

/**
 * @brief Gets the character's graphic description
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's graphic description
 */
const char *character_get_gdesc(Character *character);

/**
 * @brief Sets the character's health
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param health The health points to set
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_health(Character *character, int health);

/**
 * @brief Gets the character's health
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's health points
 */
int character_get_health(Character *character);

/**
 * @brief Sets whether the character is friendly
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param friendly TRUE if friendly, FALSE if not
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_friendly(Character *character, Bool friendly);

/**
 * @brief Gets whether the character is friendly
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return TRUE if friendly, FALSE if not
 */
Bool character_get_friendly(Character *character);

/**
 * @brief Sets the character's message
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param message The message to set
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_message(Character *character, char *message);

/**
 * @brief Gets the character's message
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's message
 */
const char *character_get_message(Character *character);

/**
 * @brief Sets the character's location id
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @param location The location id to set
 * @return OK if successful, ERROR if there was a problem
 */
Status character_set_location(Character* character, Id location);

/**
 * @brief Gets the character's location
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return The character's location id
 */
Id character_get_location(Character *character);

/**
 * @brief Gets a pointer to the character's location
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return A pointer to the character's location
 */
Id *character_get_location_pointer(Character *character);

/**
 * @brief Prints the character information
 * @author Izan Robles
 *
 * @param character A pointer to the character
 * @return OK if successful, ERROR if there was a problem
 */
Status character_print(Character *character);

#endif
