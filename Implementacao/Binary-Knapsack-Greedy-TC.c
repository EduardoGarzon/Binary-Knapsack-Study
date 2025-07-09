#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

//--------------------------------------------------------------------------
// QUICKSORT
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
// MOCHILA BINÁRIA
//--------------------------------------------------------------------------
typedef struct Item
{
    int value;           // valor ou beneficio.
    int weight;          // peso ou custo.
    double cost_benefit; // beneficio / custo.
} Item;

// max_knapsack_weight  : Capacidade máxima da mochila.
// items[]              : Array de itens cada um contento: valor, peso e beneficio.
// total_items          : Quantida de itens.
int knapSackGreedy(int max_knapsack_weight, Item items[], int total_items)
{
    int value = 0;
    int weight = 0;
    int i = 0;
    while (i < total_items && weight < max_knapsack_weight)
    {
        if (weight + items[i].weight <= max_knapsack_weight)
        {
            value += items[i].value;
            weight += items[i].weight;
        }
        i++;
    }
    return value;
}

//--------------------------------------------------------------------------

// ARGUMENTOS:
// 0. Nome do arquivo.
// 1. Options:  [1] Greedy ou [2] TC.
// 2. Arquivo de Entrada.
int main(int argc, char *argv[])
{
    CLEAR_SCREEN;

    if (argc < 3)
    {
        printf("FALHA AO EXECUTAR!, MODO DE USO DOS PARAMETROS:\n");
        printf("<MODO: [1 - GREEDY] OU [2 - TC]> <ARQUIVO DE ENTRADA>\n");
        return 1;
    }

    int modo = atoi(argv[1]);
    char *arquivo_entrada = argv[2];

    if (modo == "1") // GREEDY
    {
    }
    else if (modo == "2") // TC
    {
    }
    else
    {
        printf("MODO INVALIDO!\n");
        return 1;
    }

    return 0;
}