#ifndef LOG_UTILS_HEADER
#define LOG_UTILS_HEADER

/**
 * @brief Prints to stdout in green, prepending [INFO].
 *
 * @param fmt - Format
 * @param ... - Variables used in fmt
 */
void print_info(const char *fmt, ...);

/**
 * @brief Prints to stdout in red, prepending [ERRORs].
 *
 * @param fmt - Format
 * @param ... - Variables used in fmt
 */
void print_error(const char *fmt, ...);

/**
 * @brief Prints to stdout in cyan, prepending [DEBUG].
 *
 * @param fmt - Format
 * @param ... - Variables used in fmt
 */
void print_debug(const char *fmt, ...);

#endif