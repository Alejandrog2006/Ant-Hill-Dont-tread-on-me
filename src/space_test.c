/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Profesores Pprog
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"

/**
 * @brief Defines maximum number of test per execution
 */
#define MAX_TESTS 30

/**
 * @brief Main function for SPACE unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 *
 */
int main(int argc, char **argv)
{

	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all test for module Space:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
		if (test < 1 && test > MAX_TESTS)
		{
			printf("Error: unknown test %d\t", test);
			exit(EXIT_SUCCESS);
		}
	}

	if (all || test == 1)
		test1_space_create();
	if (all || test == 2)
		test2_space_create();
	if (all || test == 3)
		test1_space_set_name();
	if (all || test == 4)
		test2_space_set_name();
	if (all || test == 5)
		test3_space_set_name();
	if (all || test == 6)
		test1_space_set_object();
	if (all || test == 7)
		test2_space_set_object();
	if (all || test == 8)
		test1_space_get_id();
	if (all || test == 9)
		test2_space_get_id();
	if (all || test == 10)
		test1_space_get_name();
	if (all || test == 11)
		test2_space_get_name();
	if (all || test == 12)
		test1_space_get_object();
	if (all || test == 13)
		test2_space_get_object();
	if (all || test == 14)
		test3_space_get_object();
	if (all || test == 14)
		test1_space_get_characters();
	if (all || test == 15)
		test2_space_get_characters();
	if (all || test == 16)
		test1_space_del_character();
	if (all || test == 17)
		test2_space_del_character();
	if (all || test == 18)
		test3_space_del_character();
	if (all || test == 19)
		test1_space_add_character();
	if (all || test == 20)
		test2_space_add_character();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}

void test1_space_create()
{
	int result;
	Space *s;
	s = space_create(5);
	result = s != NULL;
	PRINT_TEST_RESULT(result);
	space_destroy(s);
}

void test2_space_create()
{
	Space *s;
	s = space_create(4);
	PRINT_TEST_RESULT(space_get_id(s) == 4);
	space_destroy(s);
}

void test1_space_set_name()
{
	Space *s;
	s = space_create(5);
	PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
	space_destroy(s);
}

void test2_space_set_name()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name()
{
	Space *s;
	s = space_create(5);
	PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
	space_destroy(s);
}

void test1_space_set_object()
{
	Space *s;
	s = space_create(1);
	PRINT_TEST_RESULT(space_set_object(s, TRUE) == OK);
	space_destroy(s);
}

void test2_space_set_object()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_set_object(s, TRUE) == ERROR);
}

void test1_space_get_name()
{
	Space *s;
	s = space_create(1);
	space_set_name(s, "adios");
	PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
	space_destroy(s);
}

void test2_space_get_name()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_object()
{
	Space *s;
	s = space_create(1);
	PRINT_TEST_RESULT(space_get_object(s, 1) == FALSE);
	space_destroy(s);
}

void test2_space_get_object()
{
	Space *s;
	s = space_create(1);
	set_add(space_get_object_locations(s), 1);
	PRINT_TEST_RESULT(space_get_object(s, 1) == TRUE);
	space_destroy(s);
}

void test3_space_get_object()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_get_object(s, 1) == FALSE);
}

void test1_space_get_id()
{
	Space *s;
	s = space_create(25);
	PRINT_TEST_RESULT(space_get_id(s) == 25);
	space_destroy(s);
}

void test2_space_get_id()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/** */
void test1_space_get_characters()
{
	Space *s = NULL;
	PRINT_TEST_RESULT(space_get_characters(s) == NULL);
}

void test2_space_get_characters()
{
	Space *s = NULL;
	s = space_create(1);
	PRINT_TEST_RESULT(space_get_characters(s) != NULL);
	space_destroy(s);
}

void test1_space_del_character()
{
	Space *s = NULL;
	Character *c = NULL;

	c = character_create(25);
	PRINT_TEST_RESULT(space_del_character(s, c) == ERROR);
	character_destroy(c);
}

void test2_space_del_character()
{
	Space *s = NULL;
	Character *c = NULL;

	s = space_create(1);
	PRINT_TEST_RESULT(space_del_character(s, c) == ERROR);
	space_destroy(s);
}

void test3_space_del_character()
{
	Space *s = NULL;
	Character *c = NULL;

	s = space_create(1);
	c = character_create(2);
	PRINT_TEST_RESULT(space_del_character(s, c) == OK);
	space_destroy(s);
	character_destroy(c);
}

void test1_space_add_character()
{
	Space *s = NULL;
	Character *c = NULL;

	s = space_create(1);
	c = character_create(2);
	PRINT_TEST_RESULT(space_add_character(s, c) == OK);
	space_destroy(s);
	character_destroy(c);
}

void test2_space_add_character()
{
	Space *s = NULL;
	Character *c = NULL;

	s = space_create(1);
	PRINT_TEST_RESULT(space_del_character(s, c) == ERROR);
	space_destroy(s);
}