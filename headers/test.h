/**
 * @brief Defines data for test implementation
 *
 * @file test.h
 * @author Alejandro González
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
/** @brief Assigns color red */
#define KRED  "\x1B[31m" 
 /** @brief Assigns color green */
#define KGRN  "\x1B[32m"
/** @brief Assigns color yellow */
#define KYEL  "\x1B[33m" 
/** @brief Assigns color cyan */
#define KCYN  "\x1B[36m" 
/** @brief Assigns reset code */
#define RESET "\033[0m"
#else
#define KRED
#define KGRN
#define KYEL
#define KCYN
#define RESET
#endif

/** @brief Defines print_test_result */
#define PRINT_TEST_RESULT(x) do{					\
    __test_counter++;							\
    __pass = (x);							\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;	\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n",	\
	   __FILE__, __LINE__ , __FUNCTION__,				\
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

/** @brief Defines passed_percentage for printing data */
#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))
      
static int __test_counter = 0;
static int __test_passed  = 0;
static int __pass = 0;

#endif
