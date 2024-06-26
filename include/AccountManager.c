#include <unistd.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "Structs.h"
#include "LogUtils.h"
#include "AccountManager.h"

char *get_filepath(Account *acc, char *datapath)
{
    char *prefix = "accounts/";
    char *filepath = malloc(strlen(acc->surname) + strlen(acc->name) + strlen(prefix) + strlen(datapath));
    strcpy(filepath, datapath);
    strcat(filepath, prefix);
    strcat(filepath, acc->surname);
    strcat(filepath, acc->name);
    return filepath;
}

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

    // converting to hex string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(hashed_pass + strlen(hashed_pass), "%02x", hashed_bytes[i]);
    }

    free(hashed_bytes);

    return hashed_pass;
}

char create_account(Account *acc, char *datapath)
{
    // check if account already exists
    char *filepath = get_filepath(acc, datapath);
    if (fopen(filepath, "r") != NULL)
    {
        print_error("Account already exists.");
        free(filepath);
        return 1;
    }

    // read and confirm password
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

    // hash password
    char *hashed_pass = hash_password(pass);
    free(pass);

    // store data
    FILE *account_file = fopen(filepath, "w");
    fprintf(account_file, "%s", hashed_pass);
    fclose(account_file);
    free(hashed_pass);

    // create account
    char *folder = "loans/";
    char *folderPath = malloc(strlen(datapath) + strlen(folder) + strlen(acc->surname) + strlen(acc->name) + 2);
    sprintf(folderPath, "%s%s%s%s/", datapath, folder, acc->surname, acc->name);
    mkdir(folderPath, 0777);

    return 0;
}

char login(Account *acc, char *datapath)
{
    // open account file
    char *filepath = get_filepath(acc, datapath);
    FILE *account_file = fopen(filepath, "r");
    free(filepath);

    // check that account exists
    if (account_file == NULL)
    {
        print_error("Account does not exist.");
        return 1;
    }

    // read hash from file
    char *target_hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    fgets(target_hash, SHA256_DIGEST_LENGTH * 2 + 1, account_file);

    // read password from usr
    char *pass = read_password("Password: ");

    // hash password
    char *pass_hash = hash_password(pass);
    free(pass);

    if (strcmp(pass_hash, target_hash) != 0)
    {
        print_error("Wrong password.");
        return 1;
    }

    return 0;
}
