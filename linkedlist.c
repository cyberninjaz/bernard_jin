#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

struct LinkedList {
    struct Node* headNode;
};
typedef struct Node Node;
typedef struct LinkedList LinkedList;

void push(Node* headnode, int data, LinkedList* list) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->next = headnode;
    list->headNode = n;
    headnode = n;
    return;
}

void insert(Node* prevnode, int data) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    n->next = prevnode->next;
    prevnode->next = n;
    return;
}

void append(Node* headnode, int data) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->data = data;
    Node* last = headnode;
    n->next = NULL;
    if(headnode == NULL) {
        headnode = n;
        return;
    }
    while(last->next != NULL) {
        last = last->next;
    }
    last->next = n;
    return;
}

int delete(Node* node, Node* headnode) {
    Node* temp = headnode;
    while(temp->next != node) {
        temp = temp->next;
    }
    int tempdata = temp->next->data;
    temp->next = temp->next->next;
    return tempdata;
}

int pop(Node* headnode, LinkedList* list) {
    int temp = headnode->data;
    headnode = headnode->next;
    list->headNode = headnode;
    return temp;
}

int cut(Node* headnode) {
    Node* temp = headnode;
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    int info = temp->next->data;
    temp->next = NULL;
    return info;
}

int main() {
    Node* n = (Node*) calloc(1, sizeof(Node));
    LinkedList* list = (LinkedList*) calloc(1, sizeof(LinkedList));
    n->data = 100;
    Node** loc = n;
    append(n, 101);
    push(n, 99, list);
    Node* temp = list->headNode;
    while(1) {
        printf("%d ", temp->data);
        temp = temp->next;
        if(temp == NULL) {
            break;
        }
    }
    printf("\n%d", pop(list->headNode, list));
    printf("\n%d\n", cut(list->headNode));
    Node* alsotemp = list->headNode;
    while(1) {
        printf("%d ", alsotemp->data);
        alsotemp = alsotemp->next;
        if(alsotemp == NULL) {
            break;
        }
    }
}