#include <unistd.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char create_account(char *surname, char *name)
{
    // read password without echoing
    char *pass = getpass("Password:");
    char *hashed_pass = malloc(SHA_DIGEST_LENGTH * 2 + 1);
    hashed_pass[0] = 0;

    // hash password: https://stackoverflow.com/a/919375
    unsigned char obuf[SHA_DIGEST_LENGTH];

    SHA256(pass, strlen(pass), obuf);

    // this segfaults
    for (int i = 0; i < 3; i++)
    {
        sprintf(hashed_pass, "%02x", obuf[i]);
    }

    // this works
    sprintf(hashed_pass, "%02x", obuf[0]);
    sprintf(hashed_pass, "%02x", obuf[1]);
    sprintf(hashed_pass, "%02x", obuf[2]);

    printf("%s\n", hashed_pass);

    return 1;
}