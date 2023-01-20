/*
Numero: 2022116161
Nome: Ricardo Martins
Curso: EI
*/

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
struct Cars car;


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
    

    FILE *fh;
    fh = fopen("data.db", "r");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    while (fread(&car, sizeof(struct Cars), 1, fh))
    {
        printf("%s \n", car.marca);
        numCarros++;
    }
    puts("---------------------------------");
    printf("Existem %d marcas no carro \n", numCarros);
    fclose(fh);
}

void listarDadosModelos() 
{
    
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

    while (fread(&car, sizeof(struct Cars), 1, fh))
    {
        int value = strcasecmp(car.marca, marca);
        if (value == 0)
        {
            puts("------------------------------------------------------");
            printf("%s - %s \n", car.marca, car.modelo);
            printf("Preco: %.2f Eur \n", car.preco);
            printf("Autonomia: %d Km \n", car.autonomia);
            printf("Velocidade maxima: %d km/h \n", car.velmax);
            printf("Aceleracao: %.2f s \n", car.aceleracao);
            printf("CV: %d cv \n", car.cv);
            printf("Tracao: %c Integral \n", car.tracao);
            numCarros++;
        }
    }
    puts("---------------------------------");
    printf("Foram encontrados %d carros \n", numCarros);

    fclose(fh);
}

void listarIntervaloPreco()
{
    int numCarros = 0;
    float precoMinimo, precoMaximo;
    
   do {  
        printf("Introduza um preco minimo: ");
        scanf("%f", &precoMinimo);
        if(precoMinimo < 0){
        printf("Preço inválido\n");
        }
    }while (precoMinimo < 0);

    do {  
    printf("Introduza um preco maximo: ");
    scanf("%f", &precoMaximo);
       if(precoMaximo< 0){
        printf("Preço inválido\n");
        }
    }while (precoMaximo < 0);

    FILE *fh;
    fh = fopen("data.db", "r");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    while (fread(&car, sizeof(struct Cars), 1, fh))
    {
        if (car.preco > precoMinimo && car.preco < precoMaximo)
        {
            puts("------------------------------------------------------");
            printf("%s - %s : %.2f \n", car.marca, car.modelo, car.preco);
            numCarros++;
        }
    }
    puts("---------------------------------");
    printf("Foram encontrados %d no intervalo de preco indicado (%.2fEur - %.2fEur)\n", numCarros, precoMinimo, precoMaximo);

    fclose(fh);
}

void exportar()
{
   
    int numCarros = 0;
    int autonomiaMinima, autonomiaMaxima;
    do{
        printf("Introduza a autonomia minima: ");
        scanf("%d", &autonomiaMinima);
        if(autonomiaMinima <0){
            printf("Autonomia inválida\n");
        }
    }while (autonomiaMinima <0);

    do{
    printf("Introduza a autonomia maxima:");
    scanf("%d", &autonomiaMaxima);
     if(autonomiaMaxima <0){
            printf("Autonomia inválida\n");
        }
    }while (autonomiaMaxima< 0);

    FILE *fh1, *fh;
    fh1 = fopen("data.db", "r");
    if (fh1 == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    fh = fopen("export.txt", "w");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    fputs("marca,modelo,preco,autonomia,velmax,aceleracao,cv,tracao\n",fh);
    while (fread(&car, sizeof(struct Cars), 1, fh1))
    {
        if (car.autonomia > autonomiaMinima && car.autonomia < autonomiaMaxima)
        {        
            fprintf(fh,"%s,%s,%.2f,%d,%d,%.2f,%d,%c \n",car.marca,car.modelo,car.preco,car.autonomia,car.velmax,car.aceleracao,car.cv,car.tracao);
            numCarros++;
        }

    }
    puts("---------------------------------");
    printf("Foram escritos %d carros no intervalo de autonomia indicada (%dKm - %dKm)\n",numCarros, autonomiaMinima,autonomiaMaxima);
    fclose(fh);
    fclose(fh1);
}

int main()
{
    int opcao = 0;
    char continuar[1];

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
                listarIntervaloPreco();
                break;
            case 4:
                opcao = 4;
                exportar();
                break;
            default:
                printf("Opcao invalida\n");
            }
        } while (opcao >= 4 || opcao < 1);
        puts("---------------------------------");
        printf("Escolher outra opcao ? s ou n :");
        scanf(" %c", continuar);
    } while (continuar[0] == 's');

    return (0);
}