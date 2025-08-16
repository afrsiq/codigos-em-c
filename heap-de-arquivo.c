#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MAX 1001

void trocar(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int heap[], int i){
    while (i > 0 && heap[i] < heap[(i - 1) / 2]){
        trocar(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void descer(int heap[], int tam, int i){
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tam && heap[esquerda] < heap[menor])
        menor = esquerda;
    if (direita < tam && heap[direita] < heap[menor])
        menor = direita;

    if (menor != i){
        trocar(&heap[i], &heap[menor]);
        descer(heap, tam, menor);
    }
}

void inserir(int heap[], int *tam, int valor){
    if (*tam >= MAX){
        printf("Heap cheio.\n");
        return;
    }
    heap[*tam] = valor;
    heapify(heap, *tam);
    (*tam)++;
}

int remover(int heap[], int *tam){
    if (*tam == 0){
        printf("Heap vazio.\n");
        return -1;
    }
    int raiz = heap[0];
    heap[0] = heap[--(*tam)];
    descer(heap, *tam, 0);
    return raiz;
}

bool buscar(int heap[], int tam, int valor){
    for (int i = 0; i < tam; i++){
        if (heap[i] == valor)
            return true;
    }
    return false;
}

double medir_tempo(clock_t inicio, clock_t fim){
    return ((double)(fim - inicio)) * 1000.0 / CLOCKS_PER_SEC;
}

void mostrar_heap(int heap[], int tam){
    printf("Heap: ");
    for (int i = 0; i < tam; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

void menu(){
    printf("MENU\n");
    printf("1. Inserir número\n");
    printf("2. Remover menor número\n");
    printf("3. Buscar número\n");
    printf("4. Mostrar heap atual\n");
    printf("5. Sair\n");
    printf("Escolha: ");
}

int main(){
    int heap[MAX];
    int tam = 0;
    int N;
    char nome_arquivo[300];
    FILE *arquivo;

    printf("Digite o caminho do arquivo: ");
    scanf(" %[^\n]", nome_arquivo);

    printf("Digite o número de elementos (máximo %d): ", MAX);
    scanf("%d", &N);

    if (N > MAX){
        printf("Erro: número máximo excedido.\n");
        return 1;
    }

    arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("Inserindo elementos do arquivo no heap\n");
    for (int i = 0; i < N; i++){
        int valor;
        if (fscanf(arquivo, "%d", &valor) != 1){
            printf("Erro ao ler o número no arquivo.");
            return 1;
        }
        clock_t ini = clock();
        inserir(heap, &tam, valor);
        clock_t fim = clock();
        printf("Inserido %d em %.4f ms\n", valor, medir_tempo(ini, fim));
    }
    fclose(arquivo);

    int opcao;
    do {
        menu();
        scanf("%d", &opcao);

        if (opcao == 1){
            int valor;
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            clock_t ini = clock();
            inserir(heap, &tam, valor);
            clock_t fim = clock();
            printf("Inserido %d em %.4f ms\n", valor, medir_tempo(ini, fim));

        } else if (opcao == 2){
            clock_t ini = clock();
            int removido = remover(heap, &tam);
            clock_t fim = clock();
            if (removido != -1)
                printf("Removido %d em %.4f ms\n", removido, medir_tempo(ini, fim));

        } else if (opcao == 3){
            int valor;
            printf("Digite o valor a buscar: ");
            scanf("%d", &valor);
            clock_t ini = clock();
            bool achou = buscar(heap, tam, valor);
            clock_t fim = clock();
            printf("Busca por %d: %s (%.4f ms)\n", valor, achou ? "Encontrado" : "Não encontrado", medir_tempo(ini, fim));

        } else if (opcao == 4){
            mostrar_heap(heap, tam);

        } else if (opcao == 5){
            printf("Encerrando.\n");

        } else {
            printf("Opção inválida.\n");
        }

    } while (opcao != 5);

    return 0;
}
