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
void find_user(char* file_list, LinkedList* user_list);
void save_user(char* user_info, LinkedList* user_list, int i);
void process_yescrypt(char* user_info, LinkedList* user_list, int i, unsigned long yescript_flag_len);
void process_sha(char* user_info, LinkedList* user_list, int i);


#endif //COMP8005_ASSIGNMENT1_COMMON_H
