#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dados {
            char nome[20];
            int nascD, nascM, nascA;
            char ec[2];
            float sal;
            //elementos da estrutura ok
            };

void inclui();
void lista();
int pesquisaNome();
int pesquisaCivil();
int pesquisaMes();
int pesquisaSal();
void alterarSal();
void altera();
void exclui();

int main()
{
        struct dados info;
        struct dados *p;
        int op;
        int i;
        int tam;    //n. de bytes da estrutura

        p = & info;
        tam = sizeof(info);

        while(1){
        printf(" 1 - Incluir dados  \n");
        printf(" 2 - Listar dados  \n");
        printf(" 3 - Pesquisar registro pelo nome \n");
        printf(" 4 - Pesquisar registro por estado civil \n");
        printf(" 5 - Pesquisar registro pelo mês de aniversário \n");
        printf(" 6 - Pesquisar registro pela faixa salarial \n");
        printf(" 7 - Alterar salário  \n");
        printf(" 8 - Alterar dados  \n");
        printf(" 9 - Exclui dados  \n");
        printf(" 10 - Saida\n");
        scanf("%d", &op);
        getchar();


    switch(op)
                {
                case 1 : inclui(p, tam);   //passa como parametro o ponteiro para a estrutura e o n. de bytes da desta
                break;

                case 2: lista(p, tam);
                break;

                case 3: pesquisaNome(p, tam);
                break;

                case 4: pesquisaCivil(p, tam);
                break;

                case 5: pesquisaMes(p, tam);
                break;

                case 6: pesquisaSal(p, tam);
                break;

                case 7: alterarSal(p, tam);
                break;

                case 8: altera(p, tam);
                break;

                case 9: exclui(p, tam);
                break;

                case 10: exit(0);
                break;

                default: printf("\n opcao invalida\n");
                }
    };

}

void inclui(struct dados *ps, int tam) /*1 - ok*/
{
    FILE *p, *p1;
    int cont = 0;
    int i;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("contador antes %d\n",cont);
    fclose(p1);

    //zera os dados da estrutura
    for(i=0;i<19;i++){
        ps->nome[i]='0';
    }
    ps->ec[0]='0';
    ps->nascD=0;
    ps->nascM=0;
    ps->nascA=0;
    ps->sal=0.0;

    p = fopen("arquivo.txt", "a");

    if( p == NULL){
        printf("\nERRO");
        exit(1);
    }

    do{
    printf("\nDigite o nome do contato: ");
    gets(ps->nome);
    if(*ps->nome == '\0')
        printf("\nERRO: nome invalido\n");
    }while(*ps->nome == '\0');

    do{
    printf("\nDigite o estado civil do contato (s/c/v): ");
    gets(ps->ec);
    if(*ps->ec != 's' && *ps->ec != 'c' && *ps->ec != 'v')
        printf("\nERRO: estado civil invalido\n");
    }while(*ps->ec != 's' && *ps->ec != 'c' && *ps->ec != 'v');

    do{
    printf("\nDigite o dia do nascimento do contato: ");
    scanf("%d", &ps->nascD);
    if(ps->nascD <=0 || ps->nascD >31)
        printf("\nERRO: dia invalido\n");
    }while(ps->nascD <=0 || ps->nascD >31);

    do{
    printf("\nDigite o mes do nascimento do contato: ");
    scanf("%d", &ps->nascM);
    if(ps->nascM <=0 || ps->nascM >12)
        printf("\nERRO: mes invalido\n");
    }while(ps->nascM <=0 || ps->nascM >12);

    do{
    printf("\nDigite o ano do nascimento do contato: ");
    scanf("%d", &ps->nascA);
    if(ps->nascA <=0 || ps->nascA >9999)
        printf("\nERRO: ano invalido\n");
    }while(ps->nascA <=0 || ps->nascA >9999);

    do{
    printf("\nDigite o salario do contato: ");
    scanf("%f", &ps->sal);
    if(ps->sal <=0)
        printf("\nERRO: valor invalido\n");
    }while(ps->sal <=0);

    fwrite(ps, tam,1,p);
    fclose(p);

    cont++;

    p1 = fopen("contador.txt", "w");
    fprintf(p1,"%d",cont);
    printf("\ncontador depois %d\n",cont);
    fclose(p1);
}

void lista(struct dados *ps, int tam) /*2 - ok porem não*/
{
    FILE *p, *p1;
    int i;
    int cont,comp;

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    printf("%d\n",cont);
    fclose(p1);

    p = fopen("arquivo.txt", "r"); /*r" --> Abre o arquivo apenas para leitura.*/

    if(p == NULL){
        puts("\nERRO\n");
        exit(1);
    }

    for(i=0;i<cont; i++){
    comp = i*tam;   /*calcula o n. de bytes para posicionar o ponteiro do arquivo*/

    fseek(p,comp,0);    /*posiciona o ponteiro no inicio do registro dentro do arquivo*/
    fread(ps,tam,1,p);   /*le o registro*/
    if(ps -> nome[0] != '*'){ /*verifica se esta apagado*/
        /*imprimi registro na tela*/
        printf("\nNome: %s", ps->nome);
        printf("\nData de nasc: %d/%d/%d", ps->nascD, ps->nascM, ps->nascA);
        printf("\nEstado civil: %s", ps->ec);
        printf("\nSalario: %.2f\n\n", ps->sal);
        }
    }
        fclose(p);
}

int pesquisaNome(struct dados *ps, int tam) /*3 - ok*/
{
    FILE *p;
    FILE *p1;

    char nome1[20];
    int i=0,y, x;
    int cont;

    printf("Informe um nome para pesquisa: ");
    gets(nome1);

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    printf("%d\n",cont);

    p = fopen("arquivo.txt", "r");

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; nome1[x] != '\0';x++){
            if(nome1[x] != ps -> nome[x]){
                break;
            }
        }

    if(nome1[x] == '\0' && ps -> nome[x] == '\0')
    {
        printf("n. do reg.: %d\n\n",y);
        return y;
    }
    }
    printf("reg. nao existe\n\n");
    return -1;
}

int pesquisaCivil(struct dados *ps, int tam) /*4 - ok*/
{
    FILE *p;
    FILE *p1;

    char civil1[20];
    int i=0,y, x;
    int cont;

    printf("Informe o estado civil (c/s/v) para pesquisa: ");
    gets(civil1);

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    printf("%d\n",cont);

    p = fopen("arquivo.txt", "r");

    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);
        for(x = 0; civil1[x] != '\0';x++){
            if(civil1[x] != ps -> ec[x]){
                break;
            }
        }

    if(civil1[x] == '\0' && ps -> ec[x] == '\0')
    {
        printf("n. do reg.: %d\n\n",y);
        return y;
    }
    }
    printf("reg. nao existe\n\n");
    return -1;
}

int pesquisaMes(struct dados *ps, int tam)/*5 - ok*/
{
    FILE *p;
    FILE *p1;

    int mes1;
    int i=0,y, x=0;
    int cont;

    printf("Informe o mes para pesquisa: ");
    scanf("%d", &mes1);

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    printf("%d\n",cont);

    p = fopen("arquivo.txt", "r");

    printf("\nLista de registro com aniversário no mês solicitado:\n");
    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);

        if(mes1 == ps -> nascM)
        {
            printf("n. do reg.: %d\n", y);
            x=+1;
        }
    }
    if(x==0){
        printf("nao ha' reg.\n");
        return -1;
    }
        return y;
}

int pesquisaSal(struct dados *ps, int tam) /*6 - ok*/
{
    FILE *p;
    FILE *p1;

    int sal1, sal2;
    int i=0,y, x=0;
    int cont;

    printf("\nInforme o inicio da faixa salarial para pesquisa: ");
    scanf("%d", &sal1);

    printf("\nInforme o fim da faixa salarial para pesquisa: ");
    scanf("%d", &sal2);

    p1 = fopen("contador.txt", "r");
    fscanf(p1,"%d",&cont);
    fclose(p1);
    printf("%d\n",cont);

    p = fopen("arquivo.txt", "r");

    printf("\nLista de registros com salario na faixa solicitada:\n");
    for(y=0;y<cont;y++)
    {
        fread(ps,tam,1,p);

        if((ps -> sal) >= sal1 && (ps -> sal) <= sal2)
        {
            printf("n. do reg.: %d\n", y);
            x=+1;
        }
    }
    if(x==0){
        printf("nao ha' reg.\n");
        return -1;
    }
        return y;
}

void alterarSal(struct dados *ps, int tam) /*7 - ok*/
{
    FILE *p;
    int n_reg;
    int n_bytes;

    n_reg = pesquisaNome(ps, tam);     //pesquisa o registro no arquivo
    printf("altera reg n.: %d\n",n_reg);
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);    //posioiona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    do{
    printf("\nDigite o salario do contato: ");
    scanf("%f", &ps->sal);
    if(ps->sal <=0)
        printf("\nERRO: valor invalido\n");
    }while(ps->sal <=0);

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps,tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void altera(struct dados *ps, int tam) /*8 - ok*/
{
    FILE *p;
    int n_reg;;
    int n_bytes;

    n_reg = pesquisaNome(ps, tam);     //pesquisa o registro no arquivo
    printf("altera reg n.: %d\n",n_reg);
    n_bytes = tam * n_reg;

    p = fopen("arquivo.txt", "r+");

    fseek(p,n_bytes,0);   //posiciona o ponteiro do arquivo no registro a ser alterado
    fread(ps, tam, 1, p );  //le registro do arquivo

    do{
    printf("\nDigite o nome do contato: ");
    gets(ps->nome);
    if(*ps->nome == '\0')
        printf("\nERRO: nome invalido\n");
    }while(*ps->nome == '\0');

    do{
    printf("\nDigite o estado civil do contato (s/c/v): ");
    gets(ps->ec);
    if(*ps->ec != 's' && *ps->ec != 'c' && *ps->ec != 'v')
        printf("\nERRO: estado civil invalido\n");
    }while(*ps->ec != 's' && *ps->ec != 'c' && *ps->ec != 'v');

    do{
    printf("\nDigite o dia do nascimento do contato: ");
    scanf("%d", &ps->nascD);
    if(ps->nascD <=0 || ps->nascD >31)
        printf("\nERRO: dia invalido\n");
    }while(ps->nascD <=0 || ps->nascD >31);

    do{
    printf("\nDigite o mes do nascimento do contato: ");
    scanf("%d", &ps->nascM);
    if(ps->nascM <=0 || ps->nascM >12)
        printf("\nERRO: mes invalido\n");
    }while(ps->nascM <=0 || ps->nascM >12);

    do{
    printf("\nDigite o ano do nascimento do contato: ");
    scanf("%d", &ps->nascA);
    if(ps->nascA <=0 || ps->nascA >9999)
        printf("\nERRO: ano invalido\n");
    }while(ps->nascA <=0 || ps->nascA >9999);

    do{
    printf("\nDigite o salario do contato: ");
    scanf("%f", &ps->sal);
    if(ps->sal <=0)
        printf("\nERRO: valor invalido\n");
    }while(ps->sal <=0);

    fseek(p,n_bytes,0);    //posiciona o ponteiro do arquivo no inicio do regisro a ser alterado
    fwrite(ps, tam,1,p);  //escreve o registro no arquivo

    fclose(p);
}

void exclui(struct dados *ps, int tam) /*9 - ok*/
{
    FILE *p;
    p = fopen("arquivo.txt", "r+");
    int n_reg;
    int n_bytes;

    n_reg = pesquisaNome(ps, tam);  //pesquisa o registro no arquivo
    n_bytes = tam * n_reg;

    fseek(p,n_bytes,0);       //posioiona o ponteiro do arquivo no registro a ser apagado
    fread(ps, tam, 1, p);   //le o registro do arquivo
    printf("nome para apagar e' %s\n",ps -> nome);
    //apaga o registro do arquivo
    (*ps->nome) = '*';

    fseek(p,n_bytes,0);  //posiciona o ponteiro do arquivo no inicio do regisro a ser apagado
    fwrite(ps,tam,1,p);  //escreve o registro

    fclose(p);
}
