/**
 * \file test-helper.h
 * \brief Interface provide general utilities for libtest
 *
 * This class provide general utilities for libtest
 */
#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H

/**
 * \struct String
 *
 * A general purpose string.
 */
struct String {
    char *data; /**< string content */
    int count; /**< current length of string */
};

/**
 * \brief Fetch content of the #String
 *
 * \param [out] data the content of the string
 * Caller should not do any modifications or release the memory.
 *
 * \return #API_RESULT_CODE indicating whether this call success or failed.
 *
 * \par Code Sample:
 * \code
 * char *data = NULL;
 * if (string_get_content(&data) == API_SUCCESS) {
 *     //use data
 * }
 * \endcode
 */
int string_get_content(char **data);

/**
 * \brief Change property content of string
 *
 * \param [in] data the content to change into
 * libtest will deeply copy the parameters and make no changes to parameter.
 * So caller can free the memory after calling this function.
 *
 * \return #API_RESULT_CODE indicating whether this call success or failed.
 *
 * \see string_get_content
 */
int string_set_content(const char *data);

#endif
