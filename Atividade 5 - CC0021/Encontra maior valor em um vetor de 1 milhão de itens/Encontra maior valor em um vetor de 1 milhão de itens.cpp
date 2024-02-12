#include <iostream>
#include <omp.h>
#include <conio.h>
#include <locale.h>

constexpr auto TAM = 1000000;
int* Alocar_Vetor();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("-----------ATIVIDADE 5 - CC0021-----------\n");
    printf("-----BUSCA DO MAIOR ELEMENTO EM UM VETOR DE 1 MILHÃO DE ITENS-----\n\n");
 
    int* v = Alocar_Vetor();
    printf("Criando e preenchendo vetor de tamanho %d\n\n", TAM);
    for (int i = 0; i < TAM; i++)
        v[i] = i;
    printf("Iniciando busca do maior elemento no vetor com uso de openMP\n\n");

    int maior = v[0];
    #pragma omp parallel
    {
        for (int i = 0; i < TAM; i++)
        {
            if (v[i] > maior) maior = v[i];
        }
    }
    free(v);
    printf("Maior elemento encontrado foi %d\n", maior);
    char opt = _getch();
}

int* Alocar_Vetor()
{
    int* v = (int*)malloc(sizeof(int) * TAM);
    if (v != NULL) return v;
    else printf("Não foi possível alocar memória!\n");
    char op = _getch();
    exit(1);
}
