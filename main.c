#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Structs.h"
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
    if (argc != 4)
    {
        print_error("Command usage: lov [login/register] [surname] [name]");
        return 1;
    }

    Account acc = account_constructor(argv[2], argv[3]);

    char *datapath = get_datapath(argv[0]);

    if (strcmp(argv[1], "register") == 0)
    {
        if (create_account(&acc, datapath))
        {
            print_error("Failed to create account.");
            return 1;
        }
        print_info("Account created succesfully!");
        return 0;
    }

    else if (strcmp(argv[1], "login") != 0)
    {
        print_error("Invalid operation. Valid operations are login or register.");
        return 1;
    }

    // login user
    if (login(&acc, datapath) != 0)
    {
        print_error("Login failed.");
        return 1;
    }

    print_info("Login success! Welcome %s %s.", acc.surname, acc.name);

    return 0;
}