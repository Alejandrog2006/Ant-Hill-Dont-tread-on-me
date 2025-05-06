/**
 * @brief It tests character module
 * @author Alejandro González
 *
 * @file character_test.c
 * @version 1.0
 * @date 27-02-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 14

/**
 * @brief It tests the creation of a character.
 *
 * This test creates a character using a valid ID and verifies that the character was successfully created.
 * It also destroys the character after the test.
 */
void test1_character_create();

/**
 * @brief It tests the creation of a character with an invalid ID.
 *
 * This test tries to create a character using an invalid ID (NO_ID) and verifies that the function returns NULL.
 * It then ensures proper cleanup by not calling the destroy function, as the character creation failed.
 */
void test2_character_create();

/**
 * @brief It tests the destruction of a character.
 *
 * This test creates a character and verifies that it can be destroyed successfully, returning the expected result (OK).
 */
void test1_character_destroy();

/**
 * @brief It tests the destruction of a NULL character.
 *
 * This test attempts to destroy a NULL character pointer and verifies that the function returns an error (ERROR).
 */
void test2_character_destroy();

/**
 * @brief It tests setting the name of a character.
 *
 * This test creates a character and sets a valid name. It verifies that the name is set correctly and then destroys the character.
 */
void test1_character_set_name();

/**
 * @brief It tests setting an invalid name for a character.
 *
 * This test creates a character and attempts to set a NULL name, verifying that the function returns an error (ERROR).
 * The character is then destroyed after the test.
 */
void test2_character_set_name();

/**
 * @brief It tests getting the name of a character.
 *
 * This test creates a character, sets a name, and then verifies that the name retrieved matches the expected value.
 * The character is destroyed after the test.
 */
void test1_character_get_name();

/**
 * @brief It tests getting the name of a character with a different name.
 *
 * This test creates a character, sets a name, and verifies that the name retrieved matches the expected value.
 * The character is destroyed after the test.
 */
void test2_character_get_name();

/**
 * @brief It tests setting the friendly status of a character.
 *
 * This test creates a character and sets its friendly status to TRUE. It verifies that the status is set correctly and then destroys the character.
 */
void test1_character_set_friendly();

/**
 * @brief It tests setting the friendly status of a NULL character.
 *
 * This test attempts to set the friendly status of a NULL character pointer and verifies that the function returns an error (ERROR).
 */
void test2_character_set_friendly();

/**
 * @brief Main function for CHARACTER unit tests.
 * @author Alejandro González
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
		printf("Running all test for module Character:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test1_character_create();
	if (all || test == 2)
		test2_character_create();
	if (all || test == 3)
		test1_character_destroy();
	if (all || test == 4)
		test2_character_destroy();
	if (all || test == 5)
		test1_character_set_name();
	if (all || test == 6)
		test2_character_set_name();
	if (all || test == 7)
		test1_character_get_name();
	if (all || test == 8)
		test2_character_get_name();
	if (all || test == 9)
		test1_character_set_friendly();
	if (all || test == 10)
		test2_character_set_friendly();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}

void test1_character_create()
{
	Character *character = character_create(1);
	PRINT_TEST_RESULT(character != NULL);
	character_destroy(character);
}

void test2_character_create()
{
	Character *character = character_create(NO_ID);
	PRINT_TEST_RESULT(character == NULL);
}

void test1_character_destroy()
{
	Character *character = character_create(1);
	PRINT_TEST_RESULT(character_destroy(character) == OK);
}

void test2_character_destroy()
{
	Character *character = NULL;
	PRINT_TEST_RESULT(character_destroy(character) == ERROR);
}

void test1_character_set_name()
{
	Character *character = character_create(1);
	PRINT_TEST_RESULT(character_set_name(character, "Izan") == OK);
	character_destroy(character);
}

void test2_character_set_name()
{
	Character *character = character_create(1);
	PRINT_TEST_RESULT(character_set_name(character, NULL) == ERROR);
	character_destroy(character);
}

void test1_character_get_name()
{
	Character *character = character_create(1);
	character_set_name(character, "Izan");
	PRINT_TEST_RESULT(strcmp(character_get_name(character), "Izan") == 0);
	character_destroy(character);
}

void test2_character_get_name()
{
	Character *character = character_create(1);
	character_set_name(character, "Alex");
	PRINT_TEST_RESULT(strcmp(character_get_name(character), "Alex") == 0);
	character_destroy(character);
}

void test1_character_set_friendly()
{
	Character *character = character_create(1);
	PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == OK);
	character_destroy(character);
}

void test2_character_set_friendly()
{
	Character *character = NULL;
	PRINT_TEST_RESULT(character_set_friendly(character, TRUE) == ERROR);
}