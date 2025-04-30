/**
 * @brief It tests set module
 * @author Alejandro González
 *
 * @file set_test.c
 * @version 1.0
 * @date 27-02-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 12

/**
 * @brief Test for the creation of a set.
 *
 * This test verifies that the `set_create()` function returns a valid set
 * pointer and that the set can be successfully destroyed afterwards.
 */
void test1_set_create();

/**
 * @brief Test for the creation of a set with an empty count.
 *
 * This test verifies that the `set_create()` function initializes a set with
 * a count of 0 and that the set is successfully destroyed after the test.
 */
void test2_set_create();

/**
 * @brief Test for the destruction of a set.
 *
 * This test verifies that the `set_destroy()` function works correctly when
 * called on a valid set.
 */
void test1_set_destroy();

/**
 * @brief Test for the destruction of a NULL set.
 *
 * This test verifies that the `set_destroy()` function correctly handles
 * a NULL pointer, returning an error.
 */
void test2_set_destroy();

/**
 * @brief Test for adding an element to a set.
 *
 * This test verifies that the `set_add()` function correctly adds an element
 * to the set and returns a success status.
 */
void test1_set_add();

/**
 * @brief Test for adding a duplicate element to a set.
 *
 * This test verifies that the `set_add()` function returns an error when
 * attempting to add a duplicate element to the set.
 */
void test2_set_add();

/**
 * @brief Test for deleting an element from a set.
 *
 * This test verifies that the `set_del()` function correctly deletes an
 * existing element from the set and returns a success status.
 */
void test1_set_del();

/**
 * @brief Test for deleting a non-existing element from a set.
 *
 * This test verifies that the `set_del()` function returns an error when
 * attempting to delete an element that does not exist in the set.
 */
void test2_set_del();

/**
 * @brief Test for getting the count of elements in a set.
 *
 * This test verifies that the `set_get_count()` function returns the correct
 * count of elements in the set after adding elements.
 */
void test1_set_get_count();

/**
 * @brief Test for getting the count of elements in an empty set.
 *
 * This test verifies that the `set_get_count()` function returns 0 for an
 * empty set.
 */
void test2_set_get_count();

/**
 * @brief Test for getting an element by its index in a set.
 *
 * This test verifies that the `set_get_id_at()` function correctly returns
 * the ID of an element at a given index in the set.
 */
void test1_set_get_id_at();

/**
 * @brief Test for getting an element from an empty set.
 *
 * This test verifies that the `set_get_id_at()` function returns `NO_ID`
 * when trying to get an element from an empty set or an invalid index.
 */
void test2_set_get_id_at();

/**
 * @brief Main function for SET unit tests.
 * @author Alejandro Gonzalez
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
		printf("Running all test for module Set:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test1_set_create();
	if (all || test == 2)
		test2_set_create();
	if (all || test == 3)
		test1_set_destroy();
	if (all || test == 4)
		test2_set_destroy();
	if (all || test == 5)
		test1_set_add();
	if (all || test == 6)
		test2_set_add();
	if (all || test == 7)
		test1_set_del();
	if (all || test == 8)
		test2_set_del();
	if (all || test == 9)
		test1_set_get_count();
	if (all || test == 10)
		test2_set_get_count();
	if (all || test == 11)
		test1_set_get_id_at();
	if (all || test == 12)
		test2_set_get_id_at();

	PRINT_PASSED_PERCENTAGE;

	return 1;
}

void test1_set_create()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set != NULL);
	set_destroy(set);
}

void test2_set_create()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_get_count(set) == 0);
	set_destroy(set);
}

void test1_set_destroy()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_destroy(set) == OK);
}

void test2_set_destroy()
{
	Set *set = NULL;
	PRINT_TEST_RESULT(set_destroy(set) == ERROR);
}

void test1_set_add()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_add(set, 1) == OK);
	set_destroy(set);
}

void test2_set_add()
{
	Set *set = set_create();
	set_add(set, 1);
	PRINT_TEST_RESULT(set_add(set, 1) == ERROR);
	set_destroy(set);
}

void test1_set_del()
{
	Set *set = set_create();
	set_add(set, 1);
	PRINT_TEST_RESULT(set_del(set, 1) == OK);
	set_destroy(set);
}

void test2_set_del()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_del(set, 1) == ERROR);
	set_destroy(set);
}

void test1_set_get_count()
{
	Set *set = set_create();
	set_add(set, 1);
	set_add(set, 2);
	PRINT_TEST_RESULT(set_get_count(set) == 2);
	set_destroy(set);
}

void test2_set_get_count()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_get_count(set) == 0);
	set_destroy(set);
}

void test1_set_get_id_at()
{
	Set *set = set_create();
	set_add(set, 1);
	PRINT_TEST_RESULT(set_get_id_at(set, 0) == 1);
	set_destroy(set);
}

void test2_set_get_id_at()
{
	Set *set = set_create();
	PRINT_TEST_RESULT(set_get_id_at(set, 0) == NO_ID);
	set_destroy(set);
}