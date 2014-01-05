/**
 * \mainpage libtest
 *
 * \section intro_sec oFono telephony client APIs.
 *
 * This library provides easy to use APIs to use by hiding all details.
 *
 * \section install_sec Installation
 *
 * \subsection Download the RPM package
 *
 * Go to download page to download the RPM package.
 *
 * \subsection Install
 *
 * Run the following command in terminal to install:
 * \code
 * $rpm -ivh libtest-api.rpm
 * \endcode
 *
 * \section usage_sec How to use this library
 *
 * \subsection source Include in file
 *
 * To use this library, you must include the headers in your source file:
 * \code
 * #include <test.h>
 * \endcode
 * If you use other interfaces, you must include it too, like message:
 * \code
 * #include <test.h>
 * #include <test-helper.h>
 * \endcode
 *
 * \subsection compile How to compile
 *
 * To build with this library you can use pkg-config to get link options:
 * \code
 * $pkg-config --cflags --libs test-api
 * \endcode
 */
/**
 * \file test.h
 * \brief API interface test is in charge of path management
 *
 * It provides APIs to query path list and to query properties for a specific path.
 *
 * \note
 * This interface requirs to run in main loop thread because some GLib dependency.
 *
 * Besides, you should keep main loop idle for most of times in order to get callbacks and make sure
 * libtest-api process signals successfully. This means you should put business logic into a separate
 * thread.
 */
#ifndef _TEST_H
#define _TEST_H

/**
 * \enum API_RESULT_CODE Indicating whether API operation succeed or fail.
 */
enum API_RESULT_CODE {
    API_SUCCESS, /**< API call is successfully */
    API_FAILED, /**< API call is failed */
};

/**
 * \brief Initialize libtest-api.
 *
 * This function should be the first one to call when using libtest-api. It does essential initializations.
 * This function is synchronous.
 *
 * \return #API_RESULT_CODE indicating whether this call success or failed.
 *
 * \see test_deinit
 *
 * \par Sample code:
 * \code
 * if (test_init() != OFONO_API_SUCCESS) {
 *     printf("error occurred, failed to init test\n");
 *     return;
 * }
 * // operations goes here
 * if (test_deinit() != OFONO_API_SUCCESS) {
 *     printf("failed to deinit \n");
 *     return;
 * }
 * \endcode
 */
int test_init();

/**
 * \brief Finalize libtest-api
 *
 * This function is designated to be called when no longer needs libtest-api to release resources in libtest
 * and do some finalization.
 *
 * \note
 * It is an error to call any APIs after calling test_deinit()
 *
 * \return #API_RESULT_CODE indicating whether this call success or failed.
 *
 * \see test_init
 */
int test_deinit();

/**
 * \brief Obtain current list of path 
 *
 * \param [out] paths a pointer to an array of strings
 * \param [out] count indicating the count of path.
 *
 * \note
 * This function will allocate memory for path array. So caller must free the array, but should not free each item.
 *
 * \return #API_RESULT_CODE indicating whether this call success or failed.
 *
 * \par Sample code:
 * \code
 *    char **path = NULL;
 *    int count = 0;
 *    test_get_paths(&path, &count);
 *    // use the path
 *    free(path);
 *    path = NULL;
 * \endcode
 */
int test_get_paths(char ***paths, int *count);

#endif
