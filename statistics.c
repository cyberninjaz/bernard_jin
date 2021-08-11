#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    char input[100];
    double *nums = calloc(10, sizeof(double));
    int amount = 0;
    while(1) {
        printf("\nPlease put in a number (type anything else but a number to exit): ");
        scanf("%s", &input);
        if((input[0] > '9' || input[0] < '0') && input[0] != '-') {
            break;
        }
        if(amount == sizeof(nums) / sizeof(double)) {
            nums = realloc(nums, sizeof(nums) + (sizeof(double)* 10));
        }
        nums[amount] = atof(input);
        amount++;
        printf("Numbers put in: %d", amount);
    }
    printf("Your numbers: ");
    for(int i = 0; i < amount; i++) {
        printf("%.2f ", nums[i]);
    }
    double sum = 0;
    for(int i = 0; i < amount; i++) {
        sum += nums[i];
    }
    double mean = sum / (double) amount ;
    printf("\nMean of values: %lf", mean);
    double *temp = malloc(sizeof(double) * amount);
    for(int i = 0; i < amount; i++) {
        temp[i] = (nums[i] - mean) * (nums[i] - mean);
    }
    sum = 0.0;
    for(int i = 0; i < amount; i++) {
        sum += temp[i];
    }
    sum /= amount;
    double stdev = sqrt(sum);
    printf("\nStandard Deviation of values: %lf", stdev);
    double small = nums[0], large = nums[0];
    for(int i = 1; i < amount; i++) {
        if(nums[i] > large) {
            large = nums[i];
        }
        else if(nums[i] < small) {
            small = nums[i];
        }
    }
    printf("\nMin: %lf\nMax: %lf\nRange: %lf", small, large, large - small);
    free(nums);
    free(temp);
}