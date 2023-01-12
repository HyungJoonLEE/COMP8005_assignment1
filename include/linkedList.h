#ifndef PROJECT_LINKEDLIST_H
#define PROJECT_LINKEDLIST_H

typedef struct ListNodeType {
    char id[32];
    char hash_value[8];
    char salt[32];
    char hashed_password[67];
    struct ListNodeType *pLink;
}ListNode;


typedef struct LinkedListType {
    int currentElementCount;
    ListNode headerNode;
}LinkedList;


LinkedList* createLinkedList();
int addLLElement(LinkedList *pList, int position, ListNode element);
int removeLLElement (LinkedList *pList, int position);
ListNode* getLLElement(LinkedList *pList, int position);

void clearLinkedList(LinkedList *pList);
int getLinkedListLength(LinkedList *pList);
void deleteLinkedList(LinkedList *pList);
void displayLinkedList(LinkedList* pList);

#define FALSE 0
#define TRUE 1

#endif //PROJECT_LINKEDLIST_H
