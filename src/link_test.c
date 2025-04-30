/**
 * @brief It tests the link module
 *
 * @file link_test.c
 * @author
 * @version 1.0
 * @date 01-04-2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_l.h"
#include "test.h"

/**
 * @brief Defines maximum number of tests per execution
 */
#define MAX_TESTS 16

/**
 * @brief It tests the creation of a Link.
 *
 * This test creates a Link with a valid ID (1) and verifies that the Link is successfully created
 * by checking if the returned pointer is not NULL. The Link is then destroyed after the test.
 */
void test1_link_create();

/**
 * @brief It tests the creation of a Link with an invalid ID.
 *
 * This test tries to create a Link with an invalid ID (`NO_ID`) and verifies that the function returns NULL,
 * indicating that the Link creation has failed. No destruction is needed since the Link creation is unsuccessful.
 */
void test2_link_create();

/**
 * @brief It tests the destruction of a Link.
 *
 * This test creates a Link with a valid ID (1) and verifies that the Link can be successfully destroyed
 * by checking if the return value is `OK`. The test confirms that the link destruction works as expected.
 */
void test1_link_destroy();

/**
 * @brief It tests the destruction of a NULL Link.
 *
 * This test verifies that trying to destroy a NULL Link returns an error (`ERROR`), which helps confirm
 * the correct handling of invalid input when attempting to destroy a Link.
 */
void test2_link_destroy();

/**
 * @brief It tests setting the name of a Link.
 *
 * This test creates a Link with a valid ID (1), sets a name for the Link, and verifies that the operation
 * was successful by checking that the return value is `OK`. The Link is then destroyed after the test.
 */
void test1_link_set_name();

/**
 * @brief It tests setting the name of a Link to NULL.
 *
 * This test creates a Link with a valid ID (1), attempts to set its name to `NULL`, and verifies that
 * the operation fails by returning an error (`ERROR`). The Link is then destroyed after the test.
 */
void test2_link_set_name();

/**
 * @brief It tests getting the name of a Link.
 *
 * This test creates a Link with a valid ID (1), sets its name to "Test Link", and verifies that the
 * function `link_get_name()` returns the correct name. It checks if the returned name is "Test Link".
 * The Link is then destroyed after the test.
 */
void test1_link_get_name();

/**
 * @brief It tests getting the name of a NULL Link.
 *
 * This test checks the behavior of `link_get_name()` when called on a NULL Link. It verifies that
 * the function returns `NULL`, indicating that the name cannot be retrieved for an invalid Link.
 */
void test2_link_get_name();

/**
 * @brief It tests setting the origin of a Link.
 *
 * This test creates a Link with a valid ID (1), sets its origin to ID 2, and verifies that the operation
 * was successful by checking that the return value is `OK`. The Link is then destroyed after the test.
 */
void test1_link_set_origin();

/**
 * @brief It tests setting the origin of a NULL Link.
 *
 * This test tries to set the origin of a NULL Link and verifies that the operation fails, returning
 * an error (`ERROR`). This ensures that the system handles invalid input correctly.
 */
void test2_link_set_origin();

/**
 * @brief It tests getting the origin of a Link.
 *
 * This test creates a Link with a valid ID (1), sets its origin to ID 2, and verifies that the
 * `link_get_origin()` function correctly retrieves the origin ID (2). The Link is then destroyed after the test.
 */
void test1_link_get_origin();

/**
 * @brief It tests getting the origin of a NULL Link.
 *
 * This test checks the behavior of `link_get_origin()` when called on a NULL Link. It verifies that
 * the function returns `NO_ID`, indicating that the origin cannot be retrieved for an invalid Link.
 */
void test2_link_get_origin();

/**
 * @brief It tests setting the destination of a Link.
 *
 * This test creates a Link with a valid ID (1), sets its destination to ID 3, and verifies that the
 * operation was successful by checking that the return value is `OK`. The Link is then destroyed after the test.
 */
void test1_link_set_destination();

/**
 * @brief It tests setting the destination of a NULL Link.
 *
 * This test tries to set the destination of a NULL Link and verifies that the operation fails, returning
 * an error (`ERROR`). This ensures that the system handles invalid input correctly.
 */
void test2_link_set_destination();

/**
 * @brief It tests getting the destination of a Link.
 *
 * This test creates a Link with a valid ID (1), sets its destination to ID 3, and verifies that the
 * `link_get_destination()` function correctly retrieves the destination ID (3). The Link is then destroyed after the test.
 */
void test1_link_get_destination();

/**
 * @brief It tests getting the destination of a NULL Link.
 *
 * This test checks the behavior of `link_get_destination()` when called on a NULL Link. It verifies that
 * the function returns `NO_ID`, indicating that the destination cannot be retrieved for an invalid Link.
 */
void test2_link_get_destination();

/**
 * @brief Main function for LINK unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL tests are executed
 *   2.- A number means a particular test (the one identified by that number)
 */
int main(int argc, char **argv)
{
	int test = 0;
	int all = 1;

	if (argc < 2)
	{
		printf("Running all tests for module Link:\n");
	}
	else
	{
		test = atoi(argv[1]);
		all = 0;
		printf("Running test %d:\t", test);
	}

	if (all || test == 1)
		test1_link_create();
	if (all || test == 2)
		test2_link_create();
	if (all || test == 3)
		test1_link_destroy();
	if (all || test == 4)
		test2_link_destroy();
	if (all || test == 5)
		test1_link_set_name();
	if (all || test == 6)
		test2_link_set_name();
	if (all || test == 7)
		test1_link_get_name();
	if (all || test == 8)
		test2_link_get_name();
	if (all || test == 9)
		test1_link_set_origin();
	if (all || test == 10)
		test2_link_set_origin();
	if (all || test == 11)
		test1_link_get_origin();
	if (all || test == 12)
		test2_link_get_origin();
	if (all || test == 13)
		test1_link_set_destination();
	if (all || test == 14)
		test2_link_set_destination();
	if (all || test == 15)
		test1_link_get_destination();
	if (all || test == 16)
		test2_link_get_destination();

	PRINT_PASSED_PERCENTAGE;

	return 0;
}

void test1_link_create()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link != NULL);
	link_destroy(link);
}

void test2_link_create()
{
	Link *link = link_create(NO_ID);
	PRINT_TEST_RESULT(link == NULL);
}

void test1_link_destroy()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_destroy(link) == OK);
}

void test2_link_destroy()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_destroy(link) == ERROR);
}

void test1_link_set_name()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_name(link, "Test Link") == OK);
	link_destroy(link);
}

void test2_link_set_name()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
	link_destroy(link);
}

void test1_link_get_name()
{
	Link *link = link_create(1);
	link_set_name(link, "Test Link");
	PRINT_TEST_RESULT(strcmp(link_get_name(link), "Test Link") == 0);
	link_destroy(link);
}

void test2_link_get_name()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_set_origin()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_origin(link, 2) == OK);
	link_destroy(link);
}

void test2_link_set_origin()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_origin(link, 2) == ERROR);
}

void test1_link_get_origin()
{
	Link *link = link_create(1);
	link_set_origin(link, 2);
	PRINT_TEST_RESULT(link_get_origin(link) == 2);
	link_destroy(link);
}

void test2_link_get_origin()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_origin(link) == NO_ID);
}

void test1_link_set_destination()
{
	Link *link = link_create(1);
	PRINT_TEST_RESULT(link_set_destination(link, 3) == OK);
	link_destroy(link);
}

void test2_link_set_destination()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_set_destination(link, 3) == ERROR);
}

void test1_link_get_destination()
{
	Link *link = link_create(1);
	link_set_destination(link, 3);
	PRINT_TEST_RESULT(link_get_destination(link) == 3);
	link_destroy(link);
}

void test2_link_get_destination()
{
	Link *link = NULL;
	PRINT_TEST_RESULT(link_get_destination(link) == NO_ID);
}
