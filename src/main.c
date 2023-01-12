#include <common.h>

int main(int argc, char* argv[]) {
    char file_directory[30] = {0};
    char file_list[BUF_SIZE] = {0};
    LinkedList *user_list = NULL;

    user_list = createLinkedList();
    parse_command(argc, argv, file_directory, user_list);
    readFromShadow(file_directory, file_list);

    displayLinkedList(user_list);





    return 0;
}
