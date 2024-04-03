#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/LogUtils.h"
#include "include/AccountManager.h"

char *get_datapath(char *command)
{
    char *suffix = "data/";
    char *datapath = malloc(strlen(command) - 2 + strlen(suffix));
    strncpy(datapath, command, strlen(command) - 3);
    strcat(datapath, suffix);
}

int main(int argc, char **argv)
{
    char *datapath = get_datapath(argv[0]);

    if (argc != 4)
    {
        print_error("Command usage: lov [login/register] [surname] [name]");
        return 1;
    }

    if (strcmp(argv[1], "register") == 0)
    {
        if (create_account(argv[2], argv[3], datapath))
        {
            print_error("Failed to create account.");
            return 1;
        }
        print_info("Account created succesfully!");
        return 0;
    }
}