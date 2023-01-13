#include <assert.h>
#include "common.h"
#include "error.h"

void parse_command(int argc, char *argv[], char* file_directory, LinkedList* user_list) {
    int c;

    while((c = getopt(argc, argv, ":f:")) != -1) {
        switch(c) {
            case 'f': {
                strcpy(file_directory, optarg);
                break;
            }
            case ':': {
                fatal_message(__FILE__, __func__, __LINE__, "\"Options requires an operand\"", 5);
                break;
            }
            case '?': {
                fatal_message(__FILE__, __func__, __LINE__, "Unknown", 6);
                break;
            }
            default: {
                assert("Should not get here");
            };
        }
    }

    if (optind < argc) {
        int i = 0;
        while(argv[optind + i] != NULL) {
            ListNode user = {0,};
            strcpy(user.id, argv[optind + i]);
            addLLElement(user_list, i, user);
            i++;
        }
    }
}

int readFromShadow(char* file_directory, char* file_list) {
    char buffer[BUF_SIZE];
    char sudo_string[70] = {0};
    FILE *fp;

    sprintf(sudo_string, "sudo -S cat %s", file_directory);
    memset(buffer, 0 ,BUF_SIZE);
    fp = popen(sudo_string, "r");
    if (fp == NULL) {
        perror("popen() failed\n");
        return -1;
    }

    while (fgets(buffer, BUF_SIZE, fp)) {
        strcat(file_list, buffer);
    }
    pclose(fp);

    // printf("%s", file_list);
    return 0;
}

void find_user(char* file_list, LinkedList* user_list) {
    char temp[BUF_SIZE] = {0};

    strcpy(temp, file_list);
    memset(file_list, 0, BUF_SIZE);
    for (int i = 0; i < user_list->currentElementCount; i++) {
        strcpy(file_list, temp);
        char* line = strtok(file_list, "\n");
        while (line != NULL) {
            if (strncmp(line, getLLElement(user_list, i)->id, strlen(getLLElement(user_list, i)->id)) == 0) {
                printf("%s\n", line);
                save_user(line, user_list, i);
                break;
            }
            line = strtok(NULL, "\n");
        }
    }
}


void save_user(char* user_info, LinkedList* user_list, int i) {
    char temp[256] = {0};
    char* user_info_var = NULL;
    unsigned long yescript_flag_len = 0;

    strcpy(temp, user_info);
    user_info += strlen(getLLElement(user_list, i)->id) + 1;
    user_info_var = strtok(user_info, "$");
    if (strcmp(user_info_var, "y") == 0) {
        strcpy(getLLElement(user_list, i)->hash_id, "yescrypt");
        user_info_var = strtok(NULL, "$");
        yescript_flag_len = strlen(user_info_var);
        process_yescrypt(temp, user_list, i, yescript_flag_len);
    }
    else {
        if (strcmp(user_info_var, "1") == 0) strcpy(getLLElement(user_list, i)->hash_id, "MD5");
        if (strcmp(user_info_var, "5") == 0) strcpy(getLLElement(user_list, i)->hash_id, "SHA-256");
        if (strcmp(user_info_var, "6") == 0) strcpy(getLLElement(user_list, i)->hash_id, "SHA-512");
        process_sha(temp, user_list, i);
    }
}


void process_yescrypt(char* user_info, LinkedList* user_list, int i, unsigned long yescript_flag_len) {
    char* user_info_var;
    user_info += strlen(getLLElement(user_list, i)->id) + yescript_flag_len + 5;
    user_info_var = strtok(user_info, "$");
    strcpy(getLLElement(user_list, i)->salt, user_info_var);
    user_info_var = strtok(NULL, ":");
    strcpy(getLLElement(user_list, i)->hash_value, user_info_var);
}


void process_sha(char* user_info, LinkedList* user_list, int i) {
    char* user_info_var;

    user_info += strlen(getLLElement(user_list, i)->id) + 4;
    user_info_var = strtok(user_info, "$");
    strcpy(getLLElement(user_list, i)->salt, user_info_var);
    user_info_var = strtok(NULL, ":");
    strcpy(getLLElement(user_list, i)->hash_value, user_info_var);
}



