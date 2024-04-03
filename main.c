#include <stdio.h>
#include <string.h>

#include "include/LogUtils.h"
#include "include/AccountManager.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        print_error("Command usage: lov [login/register] [surname] [name]");
        return 1;
    }

    if (strcmp(argv[1], "register") == 0)
    {
        if (create_account(argv[2], argv[3]))
        {
            print_error("Failed to create account.");
            return 1;
        }
        print_info("Account created succesfully!");
        return 0;
    }
}