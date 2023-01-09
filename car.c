#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>  

struct Cars
{
    char marca[50];
    char modelo[100];
    float preco;
    int autonomia;
    int velmax;
    float aceleracao;
    int cv;
    char tracao;
};

void menu()
{
    puts("Opção 1 - Listar as marcas");
    puts("Opção 2 - Listar os modelos de uma marca");
    puts("Opção 3 - Listar os modelos num intervalo de preço");
    puts("Opção 4 - Exportar");
}

void listarTodasMarcas()
{
    int numCarros = 0;
    struct Cars car[255];

    FILE *fh;
    fh = fopen("data.db", "r");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    while (fread(&car[numCarros], sizeof(struct Cars), 1, fh))
    {
        printf("%s \n", car[numCarros].marca);
        numCarros++;
    }
    printf("Existem %d marcas no carro \n", numCarros);
}

void listarDadosModelos()
{
    struct Cars car[255];
    char marca[20];
    int numCarros = 0;
    printf("Qual é a marca: ");
    scanf("%s", marca);

    FILE *fh;
    fh = fopen("data.db", "r");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    while (fread(&car[numCarros], sizeof(struct Cars), 1, fh))
    {
    int value = strcmp(car[numCarros].marca,marca);  
    if(value == 0) {
    puts("------------------------------------------------------");
    printf("%s - %s \n",car[numCarros].marca,car[numCarros].modelo );
    printf("Preco: %.2f Eur \n",car[numCarros].preco);
    printf("Autonomia: %d Km \n",car[numCarros].autonomia);
    printf("Velocidade maxima: %d Eur \n",car[numCarros].velmax);
    printf("Aceleracao: %.2f Eur \n",car[numCarros].aceleracao);
    printf("CV: %d Eur \n",car[numCarros].cv);
    printf("Tracao: %c Eur \n",car[numCarros].tracao); 
    numCarros++;
    }   
    }
    printf("Foram encontrados %d carros com a marcar %s\n", numCarros, marca);
}

int main()
{
    int opcao = 0;
    char continuar[1];

    // struct Cars car[255];
    do
    {
        do
        {
            menu();
            printf("Opcao: ");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 1:
                opcao = 1;
                listarTodasMarcas();
                break;
            case 2:
                opcao = 2;
                listarDadosModelos();
                break;
            case 3:
                opcao = 3;
                // listarIntervaloPreco();
                break;
            case 4:
                opcao = 4;
                // exportar();
            default:
                printf("Opcao invalida\n");
            }
        } while (opcao >= 4 || opcao < 1);
        printf("Escolher outra opcao ? s ou n :");
        scanf(" %c", continuar);
    } while (continuar[0] == 's');
}