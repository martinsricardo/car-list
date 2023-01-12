#include <stdio.h>
#include <stdlib.h>

//6
//ex1
/*
int main()
{
    FILE *fh; // apontador para o ficheiro
    char input[255];
    printf("Enter text: ");
    gets(input);
    fh = fopen("input.txt","w");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }
    //fprintf(fh,"string: %d", 10*20);
    //fprintf(fh,"....%s",input);
    fputs(input,fh);
    fclose(fh);
    return (0);
}
*/

/* 2
int main()
{
    char c;

    FILE *fh;
    fh = fopen("input.txt","r");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }
    while((c=fgetc(fh))!= EOF)
    {
        putchar(c);
    }
    fclose(fh);

    return (0);
}
*/

/*3
int main()
{
    FILE *fh; // apontador para o ficheiro
    char input[255];
    printf("Enter text: ");
    gets(input);
    fh = fopen("input.txt","a");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }
    //fprintf(fh,"string: %d", 10*20);
    //fprintf(fh,"....%s",input);
    fputs(input,fh);
    fputs("\n",fh);

    fclose(fh);
    return (0);
}
*/

//4 e 5
/*
int main()
{
    struct aluno
    {
        int numero;
        char nome[20];
        char apelido[20];
        float nota;
    };

    FILE *fh;
    struct aluno alunos[10];
    int numAlunos, i;
    do{
    printf("Quantos alunos: ");
    scanf("%d",&numAlunos);
    }while(numAlunos<0 || numAlunos >10);

    for(i = 0 ; i< numAlunos; i++){
        do{
        printf("Introduza o numero:");
        scanf("%d", &alunos[i].numero);
        }while(alunos[i].numero < 0);

        printf("Nome do aluno:");
        scanf("%s",alunos[i].nome);

        printf("Apelido do aluno:");
        scanf("%s",alunos[i].apelido);

        do{
            printf("Introduza a nota:");
            scanf("%f", &alunos[i].nota);
        }while(alunos[i].nota < 0.0 || alunos[i].nota > 20.0);

    }

    for(i=0 ; i < numAlunos; i++){
        if(alunos[i].nota >= 9.5){
            printf("O aluno %s %s foi aprovado com nota %.2f", alunos[i].nome, alunos[i].apelido, alunos[i].nota);
        }

    }

    fh = fopen("alunos.txt","a");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }
    for(i=0; i<numAlunos; i++){
        fwrite(&alunos[i],sizeof(struct aluno),1,fh);

    }
    fclose(fh);


    return (0);
}
*/


int main()
{
     struct aluno
    {
        int numero;
        char nome[20];
        char apelido[20];
        float nota;
    };

    FILE *fh;
    struct aluno alunos[10];
    int numAlunos, i=0;

    fh = fopen("alunos.txt","r");
    if(fh==NULL)
    {
        puts("Can't open that file!");
        exit(1);
    }
   /* for(i=0; i<numAlunos; i++){
        fwrite(&alunos[i],sizeof(struct aluno),1,fh);

    }*/
    numAlunos=0;
    while( fread(&alunos[numAlunos],sizeof(struct aluno),1,fh) )
    {
     printf("Aluno: %s %s\n", alunos[numAlunos].nome, alunos[numAlunos].apelido);
     numAlunos++;
    }
   for(i=0 ; i < numAlunos; i++){
        if(alunos[i].nota >= 9.5){
            printf("O aluno %s %s foi aprovado com nota %.2f\n", alunos[i].nome, alunos[i].apelido, alunos[i].nota);
        }

    }

    printf("foram encontados %d alunos\n",i);
    fclose(fh);

    return (0);


}