#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int value;
    int weight;
    double ratio;
} Item;

int cmp(const void* a, const void* b) {
    Item* a1 = (Item*)a;
    Item* a2 = (Item*)b;
    return a2->ratio - a1->ratio;
}

int knapSackGreedy(int W, Item items[], int n) {
    int value = 0;
    int weight = 0;
    int i = 0;
    while (i < n && weight < W) {
        if (weight + items[i].weight <= W) {
            value += items[i].value;
            weight += items[i].weight;
        }
        i++;
    }
    return value;
}
