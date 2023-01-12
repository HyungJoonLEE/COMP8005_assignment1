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

    printf("%s", file_list);
    return 0;
}



