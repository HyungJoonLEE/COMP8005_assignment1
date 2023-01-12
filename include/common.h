#ifndef COMP8005_ASSIGNMENT1_COMMON_H
#define COMP8005_ASSIGNMENT1_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <string.h>
#include "linkedList.h"

#define BUF_SIZE 4096

void parse_command(int argc, char *argv[], char* file_directory, LinkedList* user_list);
int readFromShadow(char* file_directory, char* file_list);

#endif //COMP8005_ASSIGNMENT1_COMMON_H
