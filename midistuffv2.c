#include <stdio.h>
#include <stdlib.h>

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

struct Chunk {
    char type[4];
    unsigned int length;
};

unsigned createMask(unsigned a, unsigned b) {
   unsigned r = 0;
   for (unsigned i=a; i<=b; i++)
       r |= 1 << i;

   return r;
}

int bitExtracted(int number, int k, int p) {
    return (((1 << k) - 1) & (number >> (p - 1)));
}

unsigned char varlen(int value) {
    unsigned char *output = calloc(1, sizeof(char));
    output[0] = (value >> 21) & 0x7f;
    if((value >> 14) & 0x7f != 0x00) {
        output = realloc(output, sizeof(output) + sizeof(char));
        output[1] = ((value >> 14) & 0x7f) + 0b10000000;
    }
    if((value >> 7) & 0x7f != 0x00) {
        output = realloc(output, sizeof(output) + sizeof(char));
        output[2] = ((value >> 7) & 0x7f) + 0b10000000;
    }
    if(value & 0x7F != 0x00) {
        output = realloc(output, sizeof(output) + sizeof(char));
        output[3] = (value & 0x7F) + 0b10000000;
    }
    return output;
}

void addtoend(int arr[], int size, int value) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == 128) {
            arr[i] = value;
            return;
        }
    }
}

int valueinarray(int val, int arr[], int size) {
    int i;
    for(i = 0; i < size; i++)
    {
        if(arr[i] == val)
            return 1;
    }
    return 0;
}

void seekanddelete(int val, int arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == val) {
            arr[i] = 128;
        }
    }
}

char note(int arr[], int pressed, int totaltime) {
    int time = rand() % 1024;
    totaltime += time;
    int note = rand() % 128;
    int velocity = rand() % 128;
    if(pressed < 4 && !valueinarray(note, arr, 4)) {
        addtoend(arr, 4, note);
    }
    unsigned char *timemod = varlen(time);
    char temp[5] = {timemod, 0x90, note, velocity}; // TODO: Return the actual note event
	printf("Added note %d\n", note);
    return temp;
}

char removee(int arr[], int pressed, int totaltime) {
	while(1) {
    	int time = rand() % 1024;
    	totaltime += time;
    	int note = rand() % 128;
    	int velocity = rand() % 128;
		//printf("Trying note %d\n", note);
    	if(valueinarray(note, arr, 4)) {
			seekanddelete(note, arr, 4);
    	    if(time > 127) {
    	        unsigned char *timemod = varlen(time);
    	        char temp[5] = {timemod, 0x80, note, velocity}; // TODO: Return the actual note event
				printf("Lifted note %d\n", note);
    	        return temp;
    	    }
    	    else {
    	        char temp[4] = {time, 0x80, note, velocity};
				printf("Lifted note %d\n", note);
    	        return temp;
    	    }
    	}
	}
}

int main() {
	//unsigned int seed;
	//printf("Seed: ");
	//scanf("%d", seed);
	//printf("\n");
	//srand(seed);
    FILE *f = fopen("output.mid", "wb");
    unsigned char header[14] = {'M', 'T', 'h', 'd', 0, 0, 0, 6, 0, 1, 0, 2, 0, 0x60};
    fwrite(header, sizeof(char), 14, f);
    unsigned char track1[20] = {'M', 'T', 'r', 'k', 0, 0, 0, 0x0C, 0, 0xFF, 0x51, 0x03, 0x07, 0xA1, 0x20, 0b10000011, 0b00000000, 0xFF, 0x2F, 0x00};
    fwrite(track1, sizeof(char), 20, f);
    //unsigned char track2[25] = {'M', 'T', 'r', 'k', 0, 0, 0, 0x11, 0, 0xC0, 0x7F, 0, 0x90, 0x3C, 0x40, 0b10000011, 0b00000000, 0x80, 0x3C, 0x40, 0b10000011, 0b00000000, 0xFF, 0x2F, 0x00};
    //fwrite(track2, sizeof(char), 25, f);
    int length = 300;
    Node *node = calloc(1, sizeof(Node));
    LinkedList *list = calloc(1, sizeof(LinkedList));
    list->headNode = node;
	int time = 0;
	int pressedKeys[4] = {128, 128, 128, 128};
	int pressed = 0;
    for(int i = 0; i < length; i++) {
		printf("Iteration %d\nNumber of notes pressed: %d\n", i, pressed);
		if((rand() % 2 || pressed == 0) && pressed < 4) {
			append(node, note(pressedKeys, pressed, time));
			pressed++;
		}
		else {
			append(node, removee(pressedKeys, pressed, time));
			pressed--;
		}
    }
	printf("Done with generating instructions! Begin writing.\n");
	Node* temp = node->next;
	int totalsize = 0;
	char endtrack[3] = {0xFF, 0x2F, 0x00};
	append(node, endtrack);
	while(1) {
		totalsize += sizeof(temp->data);
		temp = temp->next;
		if(temp->next == NULL) {
			break;
		}
	}
	printf("Done calculating total size: %d\n", totalsize);
	char finalheader[8] = {'M', 'T', 'r', 'k', totalsize >> 24, totalsize >> 16, totalsize >> 8, totalsize};
	fwrite(finalheader, sizeof(char), 8, f);
	printf("Finished writing final header\n");
	Node* nextnode = node->next;
	while(nextnode->next != NULL) {
		printf("Writing stuff! Data: %s\n", nextnode->data);
		fwrite(nextnode->data, sizeof(char), sizeof(nextnode->data) / sizeof(char), f);
		nextnode = nextnode->next;
	}
	char endoftrack[3] = {0xFF, 0x2F, 0x00};
	fwrite(endoftrack, sizeof(char), 3, f);
	printf("Done!");
    fclose(f);
}