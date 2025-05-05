/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "game.h"

/**
 * @brief Defines map width
 */
#define WIDTH_MAP 80
/**
 * @brief Defines description width
 */
#define WIDTH_DES 40
/**
 * @brief Defines banner width
 */
#define WIDTH_BAN 30
/**
 * @brief Defines map heigh
 */
#define HEIGHT_MAP 30
/**
 * @brief Defines banner heigh
 */
#define HEIGHT_BAN 1
/**
 * @brief Defines hlp height
 */
#define HEIGHT_HLP 2
/**
 * @brief Defines fdb height
 */
#define HEIGHT_FDB 5
/**
 * @brief Defines cell height
 */
#define HEIGHT_CELL 9

/**
 * @brief Private implementation of graphic engine datatype
 */
struct _Graphic_engine
{
	Area *map;		/*!< Map for graphic engine */
	Area *descript; /*!< Description for gengine*/
	Area *banner;	/*!< Banner for gengine*/
	Area *help;		/*!< Help for gengine*/
	Area *feedback; /*!< Feedback for gengine*/
};

Graphic_engine *graphic_engine_create()
{
	static Graphic_engine *ge = NULL;

	if (ge)
	{
		return ge;
	}

	screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
	ge = (Graphic_engine *)malloc(sizeof(Graphic_engine));
	if (ge == NULL)
	{
		return NULL;
	}

	ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
	ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
	ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
	ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
	ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

	return ge;
}

void graphic_engine_destroy(Graphic_engine *ge)
{
	if (!ge)
		return;

	screen_area_destroy(ge->map);
	screen_area_destroy(ge->descript);
	screen_area_destroy(ge->banner);
	screen_area_destroy(ge->help);
	screen_area_destroy(ge->feedback);

	screen_destroy();
	free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game)
{
	Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID, id_right = NO_ID, id_left = NO_ID;
	Space *space_act = NULL;
	char obj[15] = "";
	char obj1[15] = "";
	char obj2[15] = "";
	char plys[MAX_PLAYERS][15], *ply_n = NULL, *ply_e = NULL, *ply_s = NULL, *ply_w = NULL, empty[4] = "   \0";
	char ch[10] = "";
	char ch1[10] = "";
	char ch2[10] = "";
	char str[255];
	const char *gdesc = NULL, *gdesc_l = NULL, *gdesc_r = NULL;
	CommandCode last_cmd = UNKNOWN;
	extern char *cmd_to_str[N_CMD][N_CMDT];
	int i;
	int game_n_objects = *(game_get_n_objects(game));
	const char *message = NULL;
	Character **characters;
	Id player_location;
	Bool same_location = FALSE;
	Object **objects = game_get_objects(game);
	const char *obj_name;
	Bool friendly;
	const char *temporal_feedback;
	Status cmd_status;
	Set *player_objects;
	int num_objects;
	Id obj_id;
	Object *current_obj;
	Space *space = NULL;

	screen_area_clear(ge->map);

	for (i = 0; i < game_get_n_players(game); i++)
	{
		strcpy(plys[i], player_get_gdesc(game_get_player_at(game, i)));
	}

	if ((id_act = game_get_player_location(game)) != NO_ID)
	{
		space_act = game_get_space(game, id_act);
		id_back = game_get_connection(game, id_act, N);
		id_next = game_get_connection(game, id_act, S);
		id_right = game_get_connection(game, id_act, E);
		id_left = game_get_connection(game, id_act, W);

		strcpy(obj, " ");

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_back)
			{
				ply_n = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_n = empty;
		}

		space = game_get_space(game, id_back);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_back)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_back);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_back)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		if (id_back != NO_ID)
		{
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      | %s %s %3d|", ply_n, ch, (int)id_back);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(game_get_space(game, id_back), i);

				sprintf(str, " ");

				if (gdesc[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, "                     |               |");
				}
				else
				{
					strcat(str, "                     |");
					strcat(str, gdesc);
					strcat(str, "      |");
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "                      |%-15s|", obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "                              ^");
			screen_area_puts(ge->map, str);
		}

		strcpy(obj, " ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_act)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		if (id_back == NO_ID)
		{
			sprintf(str, " ");

			for (i = 0; i < HEIGHT_CELL; i++)
			{
				screen_area_puts(ge->map, str);
			}
		}

		if (id_act != NO_ID && id_right == NO_ID && id_left == NO_ID)
		{
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      | %s %s %3d|", plys[game_get_turn(game)], ch, (int)id_act);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(space_act, i);

				sprintf(str, " ");

				if (gdesc[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, "                     |               |");
				}
				else
				{
					strcat(str, "                     |");
					strcat(str, gdesc);
					strcat(str, "      |");
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "                      |%-15s|", obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
		}

		strcpy(obj, " ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_act)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(obj1, " ");

		space = game_get_space(game, id_right);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_right)
				{
					if (strlen(obj1) > 1)
					{
						strcat(obj1, ", ");
					}
					strncat(obj1, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_act);

		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		strcpy(ch1, "      ");

		space = game_get_space(game, id_right);

		if (space && space_is_discovered(space) == TRUE)
		{
		for (i = 0; i < MAX_CHARACTERS; i++)
		{
			if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_right)
			{
				strcpy(ch1, character_get_gdesc(game_get_character_array(game)[i]));
				break;
			}
		}
     	}

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_right)
			{
				ply_e = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_e = empty;
		}

		if (id_act != NO_ID && id_right != NO_ID && id_left == NO_ID)
		{
			sprintf(str, "                      +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      | %s %s %3d|   | %s %s %3d|", plys[game_get_turn(game)], ch, (int)id_act, ply_e, ch1, (int)id_right);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(space_act, i);
				gdesc_r = space_get_gdesc_at(game_get_space(game, id_right), i);

				sprintf(str, " ");

				if (gdesc[0] == '\0')
				{
					if (i == 2)
					{
						strcat(str, "                     |               | > ");
					}
					else
					{
						strcat(str, "                     |               |   ");
					}
				}
				else
				{
					if (i == 2)
					{
						strcat(str, "                     |");
						strcat(str, gdesc);
						strcat(str, "      | > ");
					}
					else
					{
						strcat(str, "                     |");
						strcat(str, gdesc);
						strcat(str, "      |   ");
					}
				}

				space = game_get_space(game, id_right);
				if (gdesc_r[0] == '\0' || space_is_discovered(space = FALSE))
				{
					strcat(str, "|               |");
				}
				else
				{
					strcat(str, "|");
					strcat(str, gdesc_r);
					strcat(str, "      |");
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "                      |%-15s|   |%-15s|", obj, obj1);
			screen_area_puts(ge->map, str);
			sprintf(str, "                      +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
		}

		strcpy(obj, " ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_act)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(obj1, " ");

		space = game_get_space(game, id_left);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_left)
				{
					if (strlen(obj1) > 1)
					{
						strcat(obj1, ", ");
					}
					strncat(obj1, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(obj2, " ");

		space = game_get_space(game, id_right);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_right)
				{
					if (strlen(obj2) > 1)
					{
						strcat(obj2, ", ");
					}
					strncat(obj2, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_left);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_left)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		strcpy(ch1, "      ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act)
				{
					strcpy(ch1, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		strcpy(ch2, "      ");

		space = game_get_space(game, id_right);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_right)
				{
					strcpy(ch2, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_left)
			{
				ply_w = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_w = empty;
		}

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_right)
			{
				ply_e = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_e = empty;
		}

		if (id_act != NO_ID && id_left != NO_ID && id_right != NO_ID)
		{

			sprintf(str, "  +---------------+   +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "  | %s %s %3d|   | %s %s %3d|   | %s %s %3d|", ply_w, ch, (int)id_left, plys[game_get_turn(game)], ch1, (int)id_act, ch2, ply_e, (int)id_right);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(space_act, i);
				gdesc_l = space_get_gdesc_at(game_get_space(game, id_left), i);
				gdesc_r = space_get_gdesc_at(game_get_space(game, id_right), i);

				sprintf(str, " ");

				space = game_get_space(game, id_left);
				if (gdesc_l[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, " |               |");
				}
				else
				{
					strcat(str, " |");
					strcat(str, gdesc_l);
					strcat(str, "      |");
				}

				if (gdesc[0] == '\0')
				{
					if (i == 2)
					{
						strcat(str, " < |               | > ");
					}
					else
					{
						strcat(str, "   |               |   ");
					}
				}
				else
				{
					if (i == 2)
					{
						strcat(str, " < |");
						strcat(str, gdesc);
						strcat(str, "      | > ");
					}
					else
					{
						strcat(str, "   |");
						strcat(str, gdesc);
						strcat(str, "      |   ");
					}
				}

				space = game_get_space(game, id_right);
				if (gdesc_r[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, "|               |");
				}
				else
				{
					strcat(str, "|");
					strcat(str, gdesc_l);
					strcat(str, "      |");
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "  |%-15s|   |%-15s|   |%-15s|", obj1, obj, obj2);
			screen_area_puts(ge->map, str);
			sprintf(str, "  +---------------+   +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
		}

		strcpy(obj, " ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_act)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(obj1, " ");

		space = game_get_space(game, id_left);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_left)
				{
					if (strlen(obj1) > 1)
					{
						strcat(obj1, ", ");
					}
					strncat(obj1, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_act);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_act)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		strcpy(ch1, "      ");

		space = game_get_space(game, id_left);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_left)
				{
					strcpy(ch1, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_left)
			{
				ply_w = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_w = empty;
		}

		if (id_act != NO_ID && id_right == NO_ID && id_left != NO_ID)
		{
			sprintf(str, "  +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "  | %s %s %3d|   | %s %s %3d|", ply_w, ch1, (int)id_left, plys[game_get_turn(game)], ch, (int)id_act);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(space_act, i);
				gdesc_l = space_get_gdesc_at(game_get_space(game, id_left), i);

				sprintf(str, " ");

				space = game_get_space(game, id_left);
				if (gdesc_l[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, " |               |");
				}
				else
				{
					strcat(str, " |");
					strcat(str, gdesc_l);
					strcat(str, "      |");
				}

				if (gdesc[0] == '\0')
				{
					if (i == 2)
					{
						strcat(str, " < |               |");
					}
					else
					{
						strcat(str, "   |               |");
					}
				}
				else
				{
					if (i == 2)
					{
						strcat(str, " < |");
						strcat(str, gdesc);
						strcat(str, "      |");
					}
					else
					{
						strcat(str, "   |");
						strcat(str, gdesc);
						strcat(str, "      |");
					}
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "  |%-15s|   |%-15s|", obj1, obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "  +---------------+   +---------------+");
			screen_area_puts(ge->map, str);
		}

		strcpy(obj, " ");

		space = game_get_space(game, id_next);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < game_n_objects; i++)
			{
				if (game_get_object_location(game, i) == id_next)
				{
					if (strlen(obj) > 1)
					{
						strcat(obj, ", ");
					}
					strncat(obj, object_get_name(objects[i]), 14);
				}
			}
		}

		strcpy(ch, "      ");

		space = game_get_space(game, id_next);
		if (space && space_is_discovered(space) == TRUE)
		{
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				if (game_get_character_array(game)[i] != NULL && character_get_location(game_get_character_array(game)[i]) == id_next)
				{
					strcpy(ch, character_get_gdesc(game_get_character_array(game)[i]));
					break;
				}
			}
		}

		for (i = 0; i < game_get_n_players(game); i++)
		{
			if (player_get_location(game_get_player_at(game, i)) == id_next)
			{
				ply_s = plys[i];
				break;
			}
		}

		if (i == game_get_n_players(game))
		{
			ply_s = empty;
		}

		if (id_next != NO_ID)
		{
			sprintf(str, "                               v");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
			sprintf(str, "                      | %s %s %3d|", ply_s, ch, (int)id_next);
			screen_area_puts(ge->map, str);

			for (i = 0; i < GDESC_ROWS; i++)
			{
				gdesc = space_get_gdesc_at(game_get_space(game, id_next), i);

				sprintf(str, " ");

				if (gdesc[0] == '\0' || space_is_discovered(space) == FALSE)
				{
					strcat(str, "                     |               |");
				}
				else
				{
					strcat(str, "                     |");
					strcat(str, gdesc);
					strcat(str, "      |");
				}

				screen_area_puts(ge->map, str);
			}

			sprintf(str, "                      |%-15s|", obj);
			screen_area_puts(ge->map, str);
			sprintf(str, "                      +---------------+");
			screen_area_puts(ge->map, str);
		}
	}

	screen_area_clear(ge->descript);

	sprintf(str, "  Player: Health %d, Position %d", player_get_health(game_get_player_at(game, game_get_turn(game))), (int)game_get_player_location(game));
	screen_area_puts(ge->descript, str);

	characters = game_get_character_array(game);
	player_location = game_get_player_location(game);

	

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		if (characters[i] != NULL && character_get_location(characters[i]) == player_location)
		{
			sprintf(str, " ");
	        screen_area_puts(ge->descript, str);
			sprintf(str, "  %s:", character_get_name(characters[i]));
			screen_area_puts(ge->descript, str);
			sprintf(str, "  Health: %d", character_get_health(characters[i]));
			screen_area_puts(ge->descript, str);
			friendly = character_get_friendly(characters[i]);
			if (friendly == TRUE)
			{
				sprintf(str, "  Friend");
				screen_area_puts(ge->descript, str);
			}
			else
			{
				sprintf(str, "  Enemy");
				screen_area_puts(ge->descript, str);
			}
		}
	}

	sprintf(str, " ");
	screen_area_puts(ge->descript, str);
	sprintf(str, "  Objects:");
	screen_area_puts(ge->descript, str);

	for (i = 0; i < MAX_OBJECTS; i++)
	{

		obj_loc = game_get_object_location(game, i);
		obj_name = object_get_name(objects[i]);

		if (obj_loc != NO_ID && obj_name != NULL)
		{
			sprintf(str, "  %s --> %d", obj_name, (int)obj_loc);
			screen_area_puts(ge->descript, str);
		}
	}

	player_objects = inventory_get_objects(player_get_inventory(game_get_player_at(game, game_get_turn(game))));

	num_objects = inventory_get_count(player_get_inventory(game_get_player_at(game, game_get_turn(game))));

	if (num_objects > 0)
	{
		sprintf(str, "  Player objects:");
		screen_area_puts(ge->descript, str);

		for (i = 0; i < num_objects; i++)
		{
			obj_id = set_get_id_at(player_objects, i);
			if (obj_id != NO_ID)
			{
				current_obj = game_get_object_by_id(game, obj_id);
				if (current_obj)
				{
					sprintf(str, "  - %s", object_get_name(current_obj));
					screen_area_puts(ge->descript, str);
				}
			}
		}
	}
	else
	{
		sprintf(str, "  Player objects: None");
		screen_area_puts(ge->descript, str);
	}

	sprintf(str, "           Player %d", game_get_turn(game));

	screen_area_puts(ge->banner, str);
	screen_area_clear(ge->help);
	sprintf(str, " The commands you can use are:");
	screen_area_puts(ge->help, str);
	sprintf(str, " move or m (north or n, south or s, east or e, west or w), take or t, drop or d, attack or a, exit or e, chat or c,       inspect or i, recruit or r, abandon or ab");
	screen_area_puts(ge->help, str);

	screen_area_clear(ge->feedback);
	last_cmd = command_get_code(game_get_last_command(game));
	cmd_status = command_get_status(game_get_last_command(game));

	if (cmd_status == OK)
	{
		sprintf(str, " %s (%s) - OK", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
	}
	else
	{
		sprintf(str, " %s (%s) - ERROR", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
	}
	screen_area_puts(ge->feedback, str);

	temporal_feedback = game_get_temporal_feedback(game);
	if (temporal_feedback && last_cmd == ATTACK)
	{
		sprintf(str, " %s", temporal_feedback);
		screen_area_puts(ge->feedback, str);
	}
	else if (temporal_feedback && last_cmd == MOVE)
	{
		sprintf(str, " %s", temporal_feedback);
		screen_area_puts(ge->feedback, str);
	}

	message = game_get_last_message(game);
	if (message && last_cmd == CHAT)
	{
		characters = game_get_character_array(game);
		player_location = game_get_player_location(game);

		for (i = 0; i < MAX_CHARACTERS; i++)
		{
			if (characters[i] != NULL && character_get_location(characters[i]) == player_location)
			{
				same_location = TRUE;
				break;
			}
		}

		if (same_location)
		{
			sprintf(str, " Character says: %s", message);
			screen_area_puts(ge->feedback, str);
		}
	}
	else if (message && last_cmd == INSPECT && cmd_status == OK)
	{
		sprintf(str, " Description: %s", message);
		screen_area_puts(ge->feedback, str);
	}

	screen_paint(game_get_turn(game));
	printf("prompt:> ");
}
