/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @version 0
 * @date 27-01-2025
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"
#include "game_reader.h"

/**
 * @brief Initializes the game loop.
 *
 * @param game A pointer to the game structure to be initialized.
 * @param gengine A pointer to the graphic engine to be initialized.
 * @param file_name The name of the file containing the game data.
 * @return 0 if initialization is successful, 1 otherwise.
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief Runs the main game loop.
 *
 * @param game The game structure.
 * @param gengine The graphic engine used to render the game.
 * @return 0 if the game loop runs successfully, 1 otherwise.
 */
int game_loop_run(Game *game, Graphic_engine *gengine, char *log);

/**
 * @brief Cleans up resources used by the game loop.
 *
 * @param game The game structure.
 * @param gengine The graphic engine.
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief Main function of the game.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return 0 if the game runs successfully, 1 otherwise.
 */
int main(int argc, char *argv[])
{
    Game *game = NULL;
    Graphic_engine *gengine = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
        return 1;
    }

    if (game_loop_init(&game, &gengine, argv[1]) != 0)
    {
        game_loop_cleanup(game, gengine);
        return 1;
    }

    if (game_loop_run(game, gengine, argv[2]) != 0)
    {
        game_loop_cleanup(game, gengine);
        return 1;
    }

    game_loop_cleanup(game, gengine);
    return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name)
{
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        if (*game)
        {
            game_destroy(*game);
            *game = NULL;
        }
        return 1;
    }

    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        if (*game)
        {
            game_destroy(*game);
            *game = NULL;
        }
        return 1;
    }

    return 0;
}

int game_loop_run(Game *game, Graphic_engine *gengine, char *log)
{
    Command *last_cmd = NULL;
    Status cmd_status;
    int turn;
    FILE *f = NULL;

    if (!gengine)
    {
        return 1;
    }

    game_set_turn(game, 0);
    last_cmd = game_get_last_command(game);

    if (log != NULL)
    {
        if (strcmp(log, "-l") == 0)
        {
            if (!(f = fopen("log.txt", "w")))
            {
                return -1;
            }
        }
    }

    while ((command_get_code(game_get_last_command(game)) != EXIT) && (game_get_finished(game) == FALSE))
    {
        for (turn = 0; turn < game_get_n_players(game); turn++)
        {
            game_set_turn(game, turn);
            last_cmd = game_get_last_command(game);
            graphic_engine_paint_game(gengine, game);
            command_get_user_input(last_cmd);
            if (f != NULL)
            {
                switch (command_get_code(last_cmd))
                {
                case UNKNOWN:
                    fprintf(f, "Player %d: UNKNOWN\n", game_get_turn(game) + 1);
                    break;

                case EXIT:
                    fprintf(f, "Player %d: EXIT\n", game_get_turn(game) + 1);
                    break;

                case TAKE:
                    fprintf(f, "Player %d: TAKE\n", game_get_turn(game) + 1);
                    break;

                case DROP:
                    fprintf(f, "Player %d: DROP\n", game_get_turn(game) + 1);
                    break;

                case ATTACK:
                    fprintf(f, "Player %d: ATTACK\n", game_get_turn(game) + 1);
                    break;

                case CHAT:
                    fprintf(f, "Player %d: CHAT\n", game_get_turn(game) + 1);
                    break;

                case MOVE:
                    fprintf(f, "Player %d: MOVE\n", game_get_turn(game) + 1);
                    break;

                case INSPECT:
                    fprintf(f, "Player %d: INSPECT\n", game_get_turn(game) + 1);
                    break;

                default:
                    break;
                }
            }

            game_set_last_command(game, last_cmd);
            if (command_get_code(last_cmd) == EXIT)
            {
                break;
            }
            cmd_status = game_actions_update(game, game_get_last_command(game));
            command_set_status(game_get_last_command(game), cmd_status);
            if (player_get_health(game_get_player_at(game, game_get_turn(game))) <= 0)
            {
                game_set_finished(game, TRUE);
            }
        }
    }
    if (f != NULL)
    {
        fclose(f);
    }

    return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
    if (game)
    {
        game_destroy(game);
        game = NULL;
    }
    if (gengine)
    {
        graphic_engine_destroy(gengine);
        gengine = NULL;
    }
}