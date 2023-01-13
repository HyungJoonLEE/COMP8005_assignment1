#include <common.h>
#include <unistd.h>
#include <crypt.h>

int main(int argc, char* argv[]) {
    char file_directory[30] = {0};
    char file_list[BUF_SIZE] = {0};
    char encrypt[100] = {0};
    LinkedList *user_list = NULL;

    user_list = createLinkedList();
    parse_command(argc, argv, file_directory, user_list);
    readFromShadow(file_directory, file_list);
    find_user(file_list, user_list);
    strcpy(encrypt, crypt("1q2w3e/3Kmmp24Ym/hUx1STI/YD..", getLLElement(user_list, 1)->salt));
    printf("hash value = %s\n", encrypt);



    displayLinkedList(user_list);
    deleteLinkedList(user_list);
    return 0;
}
