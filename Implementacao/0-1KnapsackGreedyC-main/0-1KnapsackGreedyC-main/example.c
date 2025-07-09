#include "0-1knapsack_greedy.c"

int main()
{
    int W = 50;
    Item items[] = {{60, 10, 6.0}, {100, 20, 5.0}, {120, 30, 4.0}};
    int n = sizeof(items)/sizeof(items[0]);
    
    qsort(items, n, sizeof(items[0]), cmp);

    printf("%d", knapSackGreedy(W, items, n));

    return 0;
}
