#include <stdio.h>

int main() {
    char name[100];
    printf("File name: ");
    scanf("%s", name);
    FILE *f = fopen(name, "rb");
    /*
    fseek(f, 0L, SEEK_END);
    int length = ftell(f);
    rewind(f);
    int count = length / sizeof(char);
    char *buf = calloc(length/sizeof(char), sizeof(char));
    fread(buf, length, 1, f);

    char *temp = calloc(16, sizeof(char));
    printf("Data: \n");
    for(int i = 0; i < count; i++) {
        printf("%02x ", buf[i]);
        temp[i % 16] = buf[i];
        if((i + 1) % 16 == 0) {
            for(int x = 0; x < 16; x++) {
                if(temp[x] == (int) '\n' || temp[x] == (int) '\t') {
                    printf(".");
                }
                else printf("%c", temp[x]);
            }
            printf("\n");
        }
    }
    free(buf);
    free(temp);
    */
    char *buf = calloc(16, sizeof(char));
    int n;
    int printed;
    while((n = fread(buf, sizeof(char), 16, f)) > 0) {
        printed = 0;
        for(int i = 0; i < n; i++) {
            printf("%02x ", buf[i]);
            printed++;
        }
        if(printed != 16) {
            for(int i = 0; i < 16 - printed; i++) {
                printf("   ");
            }
        }
        printf("  ");
        for(int i = 0; i < n; i++) {
            if((int) buf[i] > 126 || (int) buf[i] < 32) {
                printf(".");
            }
            else {
                printf("%c", buf[i]);
            }
        }
        printf("\n");
    }
    free(buf);
}