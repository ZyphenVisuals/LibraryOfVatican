#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void print_info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *formatted = malloc(strlen(fmt) + 20);
    strcpy(formatted, ANSI_COLOR_GREEN);
    strcat(formatted, "[INFO] ");
    strcat(formatted, fmt);
    strcat(formatted, "\n");
    strcat(formatted, ANSI_COLOR_RESET);
    vprintf(formatted, args);
    va_end(args);
}

void print_debug(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *formatted = malloc(strlen(fmt) + 21);
    strcpy(formatted, ANSI_COLOR_CYAN);
    strcat(formatted, "[DEBUG] ");
    strcat(formatted, fmt);
    strcat(formatted, "\n");
    strcat(formatted, ANSI_COLOR_RESET);
    vprintf(formatted, args);
    va_end(args);
}

void print_error(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *formatted = malloc(strlen(fmt) + 21);
    strcpy(formatted, ANSI_COLOR_RED);
    strcat(formatted, "[ERROR] ");
    strcat(formatted, fmt);
    strcat(formatted, "\n");
    strcat(formatted, ANSI_COLOR_RESET);
    vprintf(formatted, args);
    va_end(args);
}