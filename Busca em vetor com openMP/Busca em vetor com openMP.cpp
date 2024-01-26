// Busca em vetor com openMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <time.h>
#include <conio.h>
#include <locale.h>

constexpr auto TAM = 100000000;
static int encontrado = 0, x = 80;
int* Alocar_Vetor();
double Busca_Paralela();
double Busca_Serial();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    bool menu = true;
    char opt;
    double tempo_total;
    while (menu)
    {
        printf("-----------ATIVIDADE 5 - CC0021-----------\n");
        printf("-----BUSCA DE UM ELEMENTO EM UM VETOR-----\n\n");
        printf("Digite 1 para a busca paralela ou 2 para busca serial\n");
        opt = _getch();
        system("cls");
        if (opt == '1')
        {
            tempo_total = Busca_Paralela();
            menu = false;
        }
        else if (opt == '2')
        {
            tempo_total = Busca_Serial();
            menu = false;
        }
        else
        {
            printf("A opção escolhida não corresponde a nenhum tipo de busca!\n");
            opt = _getch();
            system("cls");
        }
    }
    printf("Tempo decorrido na busca: %.2lf ms\n", tempo_total);
    printf("Número de vezes que o elemento (%d) foi encontrado: %d\n", x, encontrado);
    opt = _getch();
}

double Busca_Paralela()
{
    int* v = Alocar_Vetor();
    printf("Criando e preenchendo vetor de tamanho %d\n\n", TAM);
    time_t secs;
    for (int i = 0; i < TAM; i++)
    { //preenche o vetor com valores aleatórios
        secs = time(NULL);
        v[i] = rand() % secs;
    }
    clock_t inicio, fim;
    double tempo_total;
    printf("Iniciando busca paralela no vetor com uso de openMP\n\n");
    printf("Buscando o elemento (%d)\n\n", x);

    inicio = clock();
    #pragma omp parallel
    {
        for (int i = 0; i < TAM; i++)
        {
            if (v[i] == x) encontrado++;
        }
    }
    fim = clock();
    tempo_total = double(fim - inicio) / double(CLOCKS_PER_SEC);
    tempo_total *= 1000;
    free(v);
    return tempo_total;
}

double Busca_Serial()
{
    int* v = Alocar_Vetor();
    printf("Criando e preenchendo vetor de tamanho %d\n\n", TAM);
    time_t secs;
    for (int i = 0; i < TAM; i++)
    { //preenche o vetor com valores aleatórios
        secs = time(NULL);
        v[i] = rand() % secs;
    }
    clock_t inicio, fim;
    double tempo_total;
    printf("Iniciando busca serial no vetor\n\n");
    printf("Buscando o elemento (%d)\n\n", x);

    inicio = clock();
    for (int i = 0; i < TAM; i++)
    {
        if (v[i] == x) encontrado++;
    }
    fim = clock();
    tempo_total = double(fim - inicio) / double(CLOCKS_PER_SEC);
    tempo_total *= 1000;
    free(v);
    return tempo_total;
}

int* Alocar_Vetor()
{
    int* v = (int*)malloc(sizeof(int) * TAM);
    char b;
    if (v == NULL)
    {
        wprintf(L"Não foi possível alocar o vetor!\n");
        b = _getch();
        exit(0);
    }
    return v;
}
