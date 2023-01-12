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

void listarTodasMarcas() //feito
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
    fclose(fh);
}

void listarDadosModelos() //feito
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

    int value = strcasecmp(car[numCarros].marca,marca);  
    if(value == 0) {
    puts("------------------------------------------------------");
    printf("%s - %s \n",car[numCarros].marca,car[numCarros].modelo );
    printf("Preco: %.2f Eur \n",car[numCarros].preco);
    printf("Autonomia: %d Km \n",car[numCarros].autonomia);
    printf("Velocidade maxima: %d km/h \n",car[numCarros].velmax);
    printf("Aceleracao: %.2f s \n",car[numCarros].aceleracao);
    printf("CV: %d cv \n",car[numCarros].cv);
    printf("Tracao: %c Integral \n",car[numCarros].tracao); 
    numCarros++;
    }   
    }
    printf("Foram encontrado %d carros \n", numCarros);

    fclose(fh);
}

void listarIntervaloPreco(){
    struct Cars car[255];
     int numCarros = 0;
    float precoMinimo , precoMaximo;
    printf("Introduza um preco minimo: ");
    scanf("%f", &precoMinimo);
    while (precoMinimo < 0 ){
        printf("Preço inválido\n");
        printf("Introduza um preco minimo: ");
        scanf("%f", &precoMinimo); 
    }

    printf("Introduza um preco maximo: ");
    scanf("%f", &precoMaximo);
    
    FILE *fh;
    fh = fopen("data.db", "r");
    if (fh == NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

    while (fread(&car[numCarros], sizeof(struct Cars), 1, fh))
    {

    if(car[numCarros].preco> precoMinimo && car[numCarros].preco < precoMaximo) {
    puts("------------------------------------------------------");
        printf("%s - %s : %.2f \n",car[numCarros].marca,car[numCarros].modelo,car[numCarros].preco );  
        numCarros++;
    }   
    }
    printf("Foram encontrados %d no intervalo de preco indicado (%.2fEur - %.2fEur)\n",numCarros, precoMinimo ,precoMaximo);

fclose(fh);
}

void exportar(){
    struct Cars car[255];
    int numCarros = 0;
    int autonomiaMinima , autonomiaMaxima;
    printf("Introduza a autonomia minima: ");
    scanf("%d", &autonomiaMinima);
    while (autonomiaMinima < 0 ){
        printf("Autonomia inválida\n");
        printf("Introduza a autonomia minima: ");
        scanf("%d", &autonomiaMinima); 
    }

    printf("Introduza a autonomia maxima:");
    scanf("%d", &autonomiaMaxima);

    FILE *fh;
    fh = fopen("export.txt","w");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }

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
                listarIntervaloPreco();
                break;
            case 4:
                opcao = 4;
                exportar();
            default:
                printf("Opcao invalida\n");
            }
        } while (opcao >= 4 || opcao < 1);
        puts("---------------------------------");
        printf("Escolher outra opcao ? s ou n :");
        scanf(" %c", continuar);
    } while (continuar[0] == 's');
}