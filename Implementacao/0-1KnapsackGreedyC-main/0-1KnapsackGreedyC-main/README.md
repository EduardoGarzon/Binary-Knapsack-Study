# 0-1 Knapsack Problem in C (Greedy)

This is an implementation of the 0-1 knapsack problem in C using a greedy algorithm. The problem consists of a set of items, each with a weight and a value, and a knapsack with a maximum weight capacity. The goal is to determine the subset of items that maximizes the total value of the knapsack without exceeding its weight capacity.

## How to use

To use this implementation, include the `0-1knapsack_greedy.c` file in your project and call the `knapSackGreedy()` function with the following parameters:

- `W`: the maximum weight capacity of the knapsack
- `items[]`: an array of Item structs, each containing a value and weight property
- `n`: the number of items

The function will return the maximum value that can be put in the knapsack without exceeding its weight capacity.

```c
#include "knapsack_greedy.c"

int main()
{
    int W = 50;
    Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(items)/sizeof(items[0]);

    qsort(items, n, sizeof(items[0]), cmp);
    printf("%d", knapSackGreedy(W, items, n));

    return 0;
}
```

### Time and Space Complexity

The time complexity of this implementation is `O(nlogn)` where n is the number of items, W is the knapsack capacity. The space complexity is `O(n)` for the sorting algorithm.

### Note

This is a greedy algorithm, it guarantees that the solution is at least as good as the optimal solution, however, it doesn't guarantee that it is optimal.

I hope this implementation helps you solve the 0-1 knapsack problem in your project. If you have any questions or suggestions, feel free to reach out.

Copyright (c) 2022, Max Base
