/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/**
 * @brief Graphic engine structure.
 *
 * This struct stores the areas used for rendering the game, including the map,
 * descriptions, banners, help, and feedback.
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Creates a new graphic engine.
 * @author Profesores PPROG
 *
 * This function initializes the graphic engine and its display areas.
 *
 * @return A pointer to the newly created graphic engine, or NULL if an error occurs.
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Destroys the graphic engine, freeing the allocated memory.
 * @author Profesores PPROG
 *
 * This function frees all resources associated with the graphic engine.
 *
 * @param ge A pointer to the graphic engine to be destroyed.
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Renders the game state.
 * @author Profesores PPROG
 *
 * This function paints the current state of the game, including the map, descriptions,
 * banners, help, and feedback.
 *
 * @param ge A pointer to the graphic engine.
 * @param game A pointer to the game structure.
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

/**
 * @brief Displays an image using SDL2.
 * @author Alejandro Gonzalez
 *
 * This function loads and displays an image using SDL2.
 *
 * @param image_path Path to the image file.
 */
void graphic_engine_show_image(const char *image_path);

/**
 * @brief Displays the intro screen of the game.
 * @author Alejandro Gonzalez
 *
 * This function displays the intro screen of the game using SDL2. 
 */
void graphic_engine_show_intro();

/**
 * @brief Displays the end screen of the game.
 * @author Alejandro Gonzalez
 *
 * This function displays the end screen of the game using SDL2.
 */
void graphic_engine_show_end();

#endif
