#include <unistd.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LogUtils.h"

char *read_password(char *prompt)
{
    // TODO: don't use getpass, it's deprecated
    char *pass_buff = getpass(prompt);
    char *pass = malloc(strlen(pass_buff));
    strcpy(pass, pass_buff);
    return pass;
}

char *hash_password(char *pass)
{
    // https://stackoverflow.com/a/919375
    unsigned char *hashed_bytes = malloc(SHA256_DIGEST_LENGTH);
    char *hashed_pass = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    hashed_pass[0] = 0; // necesary for the first strlen

    SHA256(pass, strlen(pass), hashed_bytes);

    for (int i = 0; i < SHA256_192_DIGEST_LENGTH; i++)
    {
        sprintf(hashed_pass + strlen(hashed_pass), "%02x", hashed_bytes[i]);
    }

    free(hashed_bytes);

    return hashed_pass;
}

char create_account(char *surname, char *name)
{
    // read password without echoing
    char *pass = read_password("Password: ");
    char *confirm_pass = read_password("Confirm password: ");

    if (strcmp(pass, confirm_pass) != 0 || strlen(pass) != strlen(confirm_pass))
    {
        print_error("Passwords don't match.");
        free(pass);
        free(confirm_pass);
        return 1;
    }
    free(confirm_pass);

    char *hashed_pass = hash_password(pass);
    free(pass);

    return 0;
}