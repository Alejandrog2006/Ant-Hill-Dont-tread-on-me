/**
 * @brief It tests object module
 *
 * @author Alejandro González
 * @date 01-04-2025
 * @version 1.0
 * @file object_test.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 11

/**
 * @brief Test for the creation of an object.
 */
void test1_object_create();

/**
 * @brief Test for the destruction of an object.
 */
void test1_object_destroy();

/**
 * @brief Test for the destruction of a NULL object.
 */
void test2_object_destroy();

/**
 * @brief Test for setting the name of an object.
 */
void test1_object_set_name();

/**
 * @brief Test for setting the name of an object with NULL.
 */
void test2_object_set_name();

/**
 * @brief Test for getting the name of an object.
 */
void test1_object_get_name();

/**
 * @brief Test for getting the name of a NULL object.
 */
void test2_object_get_name();

/**
 * @brief Test for setting the location of an object.
 */
void test1_object_set_location();

/**
 * @brief Test for setting the location of a NULL object.
 */
void test2_object_set_location();

/**
 * @brief Test for getting the location of an object.
 */
void test1_object_get_location();

/**
 * @brief Test for getting the location of a NULL object.
 */
void test2_object_get_location();

/**
 * @brief Main function for OBJECT unit tests.
 */
int main(int argc, char **argv)
{
	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all tests for module Object:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test1_object_create();
	if (all || test == 2)
		test1_object_destroy();
	if (all || test == 3)
		test2_object_destroy();
	if (all || test == 4)
		test1_object_set_name();
	if (all || test == 5)
		test2_object_set_name();
	if (all || test == 6)
		test1_object_get_name();
	if (all || test == 7)
		test2_object_get_name();
	if (all || test == 8)
		test1_object_set_location();
	if (all || test == 9)
		test2_object_set_location();
	if (all || test == 10)
		test1_object_get_location();
	if (all || test == 11)
		test2_object_get_location();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_object_create()
{
	Object *object = object_create(1);
	PRINT_TEST_RESULT(object != NULL);
	object_destroy(object);
}

void test1_object_destroy()
{
	Object *object = object_create(1);
	PRINT_TEST_RESULT(object_destroy(object) == OK);
}

void test2_object_destroy()
{
	Object *object = NULL;
	PRINT_TEST_RESULT(object_destroy(object) == ERROR);
}

void test1_object_set_name()
{
	Object *object = object_create(1);
	PRINT_TEST_RESULT(object_set_name(object, "Sword") == OK);
	object_destroy(object);
}

void test2_object_set_name()
{
	Object *object = object_create(1);
	PRINT_TEST_RESULT(object_set_name(object, NULL) == ERROR);
	object_destroy(object);
}

void test1_object_get_name()
{
	Object *object = object_create(1);
	object_set_name(object, "Sword");
	PRINT_TEST_RESULT(strcmp(object_get_name(object), "Sword") == 0);
	object_destroy(object);
}

void test2_object_get_name()
{
	Object *object = NULL;
	PRINT_TEST_RESULT(object_get_name(object) == NULL);
}

void test1_object_set_location()
{
	Object *object = object_create(1);
	PRINT_TEST_RESULT(object_set_location(object, 2) == OK);
	object_destroy(object);
}

void test2_object_set_location()
{
	Object *object = NULL;
	PRINT_TEST_RESULT(object_set_location(object, 2) == ERROR);
}

void test1_object_get_location()
{
	Object *object = object_create(1);
	object_set_location(object, 2);
	PRINT_TEST_RESULT(object_get_location(object) == 2);
	object_destroy(object);
}

void test2_object_get_location()
{
	Object *object = NULL;
	PRINT_TEST_RESULT(object_get_location(object) == NO_ID);
}