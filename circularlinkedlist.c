#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node Node;

struct LinkedList {
    Node *sentinelNode;
};
typedef struct LinkedList LinkedList;

void push(LinkedList* list, int data) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    if(list->sentinelNode->prev == NULL && list->sentinelNode->next == NULL) {
        list->sentinelNode->prev = n;
        list->sentinelNode->next = n;
        n->prev = list->sentinelNode;
        n->next = list->sentinelNode;
        return;
    }
    n->next = list->sentinelNode->next;
    n->prev = list->sentinelNode;
    list->sentinelNode->next = n;
    n->next->prev = n;
    return;
}

void insert(Node* prevnode, int data) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->next = prevnode->next;
    n->prev = prevnode;
    n->next->prev = n;
    prevnode->next = n;
    return;
}

void append(LinkedList* list, int data) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    if(list->sentinelNode->prev == NULL && list->sentinelNode->next == NULL) {
        list->sentinelNode->prev = n;
        list->sentinelNode->next = n;
        n->prev = list->sentinelNode;
        n->next = list->sentinelNode;
        return;
    }
    n->prev = list->sentinelNode->prev;
    list->sentinelNode->prev = n;
    n->prev->next = n;
}

int delete(Node* node, LinkedList* list) {
    Node* temp = list->sentinelNode;
    while(temp->next != node) {
        temp = temp->next;
    }
    int tempdata = temp->next->data;
    temp->next = temp->next->next;
    temp->next->prev = temp;
    return tempdata;
}

int pop(LinkedList* list) {
    Node* popnode = list->sentinelNode->next;
    list->sentinelNode->next = popnode->next;
    list->sentinelNode->next->prev = list->sentinelNode;
    return popnode->data;
}

int cut(LinkedList* list) {
    Node* temp = list->sentinelNode->prev;
    int info = temp->data;
    temp->prev->next = list->sentinelNode;
    list->sentinelNode->prev = temp->prev;
    return info;
}

int main() {
    Node* n = (Node*) calloc(1, sizeof(Node));
    LinkedList* list = (LinkedList*) calloc(1, sizeof(LinkedList));
    list->sentinelNode = (Node*) calloc(1, sizeof(Node));
    append(list, 101);
    push(list, 100);
    push(list, 99);
    Node* temp = list->sentinelNode->next;
    while(1) {
        printf("%d ", temp->data);
        temp = temp->next;
        if(temp == list->sentinelNode) {
            break;
        }
    }
    printf("\n%d", pop(list));
    printf("\n%d\n", cut(list));
    Node* alsotemp = list->sentinelNode->next;
    while(1) {
        printf("%d ", alsotemp->data);
        alsotemp = alsotemp->next;
        if(alsotemp == list->sentinelNode) {
            break;
        }
    }
}