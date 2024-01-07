#pragma once
#include <stdbool.h>

#define BUF_SIZE 255

/**
 * @file utils.h
 * @author Marcus Ray Sanderson
 * @date
 * @brief Utils for printing questions and reading answers from command line or file.
 *
 * If an invalid answer is input into the command line or from file the user will
 * have to retry until a valid answer can be returned. For example if answering with
 * a letter to ask_question_int will not return until an int is input.
 *
 * It is assumed that the user ensures proper memory management when using the ask_questions functions,
 * since the functiosn returning char * types heap allocates memory.
 *
*/

typedef union {
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

typedef bool(*check_func)(char*);
typedef answer_t(*convert_func)(char*);

/// @brief asks a question and reads the user answer from input line
/// @param question question to print for user to answer, the answer being an int
/// @return a number answer of the question
int ioopm_ask_question_int(char *question);

/// @brief asks a question and reads the user answer from input line
/// @param question question to print for user to answer, the answer being a string
/// @return a string answer of the question
char *ioopm_ask_question_string(char *question);

/// @brief asks a question and reads the user answer from input line
/// @param question question to print for user to answer, the answer being a string on format ex. "A54"
/// @return a shelf answer of the question
char *ioopm_ask_question_shelf(char *question);