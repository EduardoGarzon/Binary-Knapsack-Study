#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

LARGE_INTEGER frequency, start, end;
double elapsed = 0;

//-----------------------------------------------------------------------------------
// Funcao responsável por simular a Mochila Binária utilizando Greedy ou TC.
//-----------------------------------------------------------------------------------
typedef struct Item
{
    int value;           // valor ou beneficio.
    int weight;          // peso ou custo.
    double cost_benefit; // beneficio / custo.
    int is_selected;     // Item foi selecionado?
    int is_discarded;    // Item foi descartado?
} Item;

int knapSackGTC(int max_knapsack_weight, Item items[], int total_items, int modo);

//-----------------------------------------------------------------------------------
// QUICKSORT
//-----------------------------------------------------------------------------------
void troca(Item *vet, int i, int j);
int particiona(Item *vet, int inicio, int fim);
int particiona_random(Item *vet, int inicio, int fim);
void quick_sort(Item *vet, int inicio, int fim);

//-----------------------------------------------------------------------------------
// Funcao responsável por carregar o arquivo de entrada e definir o array de itens.
//-----------------------------------------------------------------------------------
Item *load_entrie(const char *input_file, int *max_knapsack_weight, int total_items);

int main(int argc, char *argv[])
{
    // CLEAR_SCREEN;

    if (argc < 4)
    {
        printf("FALHA AO EXECUTAR!, MODO DE USO DOS PARAMETROS:\n");
        printf("<modo: 1 para GREEDY ou 2 para TC> <total de itens> <arquivo de entrada>\n");
        return 1;
    }

    // modo Greddy ou TC | total de itens | peso máximo da mochila.
    int modo = atoi(argv[1]), total_items = atoi(argv[2]), max_knapsack_weight = 0;
    // Array de structs para os itens.
    Item *items = load_entrie(argv[3], &max_knapsack_weight, total_items);

    printf("\nCAPACIDADE DA MOCHILA: %d\n", max_knapsack_weight);

    // for (int i = 0; i < total_items; i++)
    // {
    //     printf("ITEM %d: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
    //            i + 1, items[i].value, items[i].weight, items[i].cost_benefit, items[i].is_selected, items[i].is_discarded);
    // }
    // printf("\n");

    int final_weight = knapSackGTC(max_knapsack_weight, items, total_items, modo);
    printf("PESO FINAL DA MOCHILA: %d\n", final_weight);

    printf("TEMPO DE EXECUCAO: %.8f segundos\n", elapsed);

    free(items);

    return 0;
}

Item *load_entrie(const char *input_file, int *max_knapsack_weight, int total_items)
{
    FILE *file = fopen(input_file, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Lê a capacidade total da mochila.
    fscanf(file, "%d", max_knapsack_weight);

    int beneficios[total_items];
    int custos[total_items];
    int i = 0;

    // Lê os benefícios.
    for (int i = 0; i < total_items; i++)
    {
        if (fscanf(file, "%d", &beneficios[i]) != 1)
        {
            printf("Erro ao ler benefício %d\n", i);
            exit(1);
        }
    }

    // printf("\nBENEFICIOS:\n");
    // for (int i = 0; i < total_items; i++)
    // {
    //     printf("%d ", beneficios[i]);
    // }
    // printf("\n");

    // Lê os custos.
    for (int j = 0; j < total_items; j++)
    {
        if (fscanf(file, "%d", &custos[j]) != 1)
        {
            printf("Erro ao ler custo %d\n", j);
            exit(1);
        }
    }

    // printf("\nCUSTOS:\n");
    // for (int j = 0; j < total_items; j++)
    // {
    //     printf("%d ", custos[j]);
    // }
    // printf("\n");

    fclose(file);

    // Cria e preenche o array de itens.
    Item *itens = malloc((total_items) * sizeof(Item));
    for (int k = 0; k < total_items; k++)
    {
        itens[k].value = beneficios[k];
        itens[k].weight = custos[k];
        itens[k].cost_benefit = (double)beneficios[k] / custos[k];
        itens[k].is_selected = 0;
        itens[k].is_discarded = 0;
    }

    return itens;
}

int knapSackGTC(int max_knapsack_weight, Item items[], int total_items, int modo)
{
    int i = 0;
    double gratest_benefit = 0;  // Maior benefício encontrado.
    int current_weight = 0;      // Peso atual da mochila.
    int selected_item_index = 0; // Index do elemento selecionado.

    if (modo == 1) // GREEDY
    {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        // Enquanto o peso atual for menor que o peso máximo da mochila e algum item for selecionado...
        while ((current_weight < max_knapsack_weight) && selected_item_index != -1)
        {
            gratest_benefit = 0;
            selected_item_index = -1;

            // Percorre todos os itens...
            for (i = 0; i < total_items; i++)
            {
                // Se o item não foi selecionado, não foi discartado e tem o maior custo-benefício...
                if (!items[i].is_selected && !items[i].is_discarded && items[i].cost_benefit > gratest_benefit)
                {
                    gratest_benefit = items[i].cost_benefit; // Atualiza o novo maior custo-benefício.
                    selected_item_index = i;                 // Salva o index do item de maior custo-benefício.
                }
            }

            // Todos os itens selecionados ou descartos? Finaliza.
            if (selected_item_index == -1)
                break;

            // Se o peso atual + o peso do item de maior custo-beneficio for menor ou igual ao peso máximo da mochila...
            if (current_weight + items[selected_item_index].weight <= max_knapsack_weight)
            {
                current_weight += items[selected_item_index].weight; // Atualiza peso atual.
                items[selected_item_index].is_selected = 1;          // Marca item como selecionado.

                // printf("ITEM SELECIONADO [%d]: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
                //        selected_item_index + 1,
                //        items[selected_item_index].value,
                //        items[selected_item_index].weight,
                //        items[selected_item_index].cost_benefit,
                //        items[selected_item_index].is_selected,
                //        items[selected_item_index].is_discarded);
            }
            else
            {
                items[selected_item_index].is_discarded = 1; // Senão marca o item como descartado.

                // printf("ITEM DESCARTADO OU NAO-SELECIONADO [%d]: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
                //        selected_item_index + 1,
                //        items[selected_item_index].value,
                //        items[selected_item_index].weight,
                //        items[selected_item_index].cost_benefit,
                //        items[selected_item_index].is_selected,
                //        items[selected_item_index].is_discarded);
            }
        }

        QueryPerformanceCounter(&end);
    }
    else if (modo == 2) // TC
    {
        quick_sort(items, 0, total_items - 1);

        // printf("ITENS ORDENADOS PELO QUICKSORT:\n");
        // for (int i = 0; i < total_items; i++)
        // {
        //     printf("ITEM %d: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
        //            i + 1, items[i].value, items[i].weight, items[i].cost_benefit, items[i].is_selected, items[i].is_discarded);
        // }
        // printf("\n");

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        // Percorre todos os itens...
        for (i = 0; i < total_items; i++)
        {
            // Se o custo-beneficio do item + o peso atual da mochila for menor ou igual a capacidade máxima da mochila...
            if ((items[i].weight + current_weight <= max_knapsack_weight))
            {
                current_weight += items[i].weight; // Atualiza o peso atual da mochila.
                items[i].is_selected = 1;          // Marca o item como selecionado.

                // printf("ITEM SELECIONADO [%d]: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
                //        i + 1,
                //        items[i].value,
                //        items[i].weight,
                //        items[i].cost_benefit,
                //        items[i].is_selected,
                //        items[i].is_discarded);
            }
            else
            {
                items[i].is_discarded = 1; // Senão marca o item como descartado.

                // printf("ITEM DESCARTADO OU NAO-SELECIONADO [%d]: VALOR = %d | PESO = %d | CUSTO/BENEFICIO = %.2f | SELECAO: %d | DESCARTE: %d\n",
                //        i + 1,
                //        items[i].value,
                //        items[i].weight,
                //        items[i].cost_benefit,
                //        items[i].is_selected,
                //        items[i].is_discarded);
            }

            if (current_weight == max_knapsack_weight)
            {
                break;
            }
        }

        QueryPerformanceCounter(&end);
    }
    else
    {
        printf("MODO INVÁLIDO PARA EXECUTAR A MOCHILA BINÁRIA!\n");
        return -1;
    }

    elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;

    return current_weight;
}

void troca(Item *vet, int i, int j)
{
    Item aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particiona(Item *vet, int inicio, int fim)
{
    Item pivo = vet[fim];
    int pivo_indice = inicio;

    for (int i = inicio; i < fim; i++)
    {
        // Ordem decrescente: do maior cost_benefit para o menor.
        if (vet[i].cost_benefit > pivo.cost_benefit)
        {
            troca(vet, i, pivo_indice);
            pivo_indice++;
        }
    }

    troca(vet, pivo_indice, fim);
    return pivo_indice;
}

int particiona_random(Item *vet, int inicio, int fim)
{
    int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
    troca(vet, pivo_indice, fim);
    return particiona(vet, inicio, fim);
}

void quick_sort(Item *vet, int inicio, int fim)
{
    if (inicio < fim)
    {
        int pivo_indice = particiona_random(vet, inicio, fim);
        quick_sort(vet, inicio, pivo_indice - 1);
        quick_sort(vet, pivo_indice + 1, fim);
    }
}
