/**
 * @brief It tests player module
 *
 * @author Alejandro González
 * @date 01-04-2025
 * @version 1.0
 * @file player_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "inventory.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 13

/**
 * @brief Test for the creation of a player.
 */
void test1_player_create();

/**
 * @brief Test for the destruction of a player.
 */
void test1_player_destroy();

/**
 * @brief Test for the destruction of a player.
 */
void test2_player_destroy();

/**
 * @brief Test for setting the name of a player.
 */
void test1_player_set_name();

/**
 * @brief Test for setting the name of a player.
 */
void test2_player_set_name();

/**
 * @brief Test for getting the name of a player.
 */
void test1_player_get_name();

/**
 * @brief Test for getting the name of a player.
 */
void test2_player_get_name();

/**
 * @brief Test for setting the location of a player.
 */
void test1_player_set_location();

/**
 * @brief Test for setting the location of a player.
 */
void test2_player_set_location();

/**
 * @brief Test for getting the location of a player.
 */
void test1_player_get_location();

/**
 * @brief Test for getting the location of a player.
 */
void test2_player_get_location();

/**
 * @brief Test for setting the health of a player.
 */
void test1_player_set_health();

/**
 * @brief Test for setting the health of a player.
 */
void test2_player_set_health();

/**
 * @brief Test for getting the health of a player.
 */
void test1_player_get_health();

/**
 * @brief Test for getting the health of a player.
 */
void test2_player_get_health();

/**
 * @brief Main function for PLAYER unit tests.
 */
int main(int argc, char **argv)
{
	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all tests for module Player:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test1_player_create();
	if (all || test == 2)
		test1_player_destroy();
	if (all || test == 3)
		test2_player_destroy();
	if (all || test == 4)
		test1_player_set_name();
	if (all || test == 5)
		test2_player_set_name();
	if (all || test == 6)
		test1_player_get_name();
	if (all || test == 7)
		test2_player_get_name();
	if (all || test == 8)
		test1_player_set_location();
	if (all || test == 9)
		test2_player_set_location();
	if (all || test == 10)
		test1_player_get_location();
	if (all || test == 11)
		test2_player_get_location();
	if (all || test == 12)
		test1_player_set_health();
	if (all || test == 13)
		test2_player_set_health();
	if (all || test == 14)
		test1_player_get_health();
	if (all || test == 15)
		test2_player_get_health();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_player_create()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player != NULL);
	player_destroy(player);
}

void test1_player_destroy()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player_destroy(player) == OK);
}

void test2_player_destroy()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_destroy(player) == ERROR);
}

void test1_player_set_name()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player_set_name(player, "Hero") == OK);
	player_destroy(player);
}

void test2_player_set_name()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player_set_name(player, NULL) == ERROR);
	player_destroy(player);
}

void test1_player_get_name()
{
	Player *player = player_create(1);
	player_set_name(player, "Hero");
	PRINT_TEST_RESULT(strcmp(player_get_name(player), "Hero") == 0);
	player_destroy(player);
}

void test2_player_get_name()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_get_name(player) == NULL);
}

void test1_player_set_location()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player_set_location(player, 2) == OK);
	player_destroy(player);
}

void test2_player_set_location()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_set_location(player, 2) == ERROR);
}

void test1_player_get_location()
{
	Player *player = player_create(1);
	player_set_location(player, 2);
	PRINT_TEST_RESULT(player_get_location(player) == 2);
	player_destroy(player);
}

void test2_player_get_location()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_get_location(player) == NO_ID);
}

void test1_player_set_health()
{
	Player *player = player_create(1);
	PRINT_TEST_RESULT(player_set_health(player, 100) == OK);
	player_destroy(player);
}

void test2_player_set_health()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_set_health(player, 100) == ERROR);
}

void test1_player_get_health()
{
	Player *player = player_create(1);
	player_set_health(player, 100);
	PRINT_TEST_RESULT(player_get_health(player) == 100);
	player_destroy(player);
}

void test2_player_get_health()
{
	Player *player = NULL;
	PRINT_TEST_RESULT(player_get_health(player) == -1);
}