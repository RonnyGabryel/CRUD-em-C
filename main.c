#include <stdio.h>  //Biblioteca padrão de entrada e saída
#include <string.h> //Biblioteca para manipular string
#include <stdlib.h> //Biblioteca para limpar o terminal
#include <locale.h> //Biiblioteca para acentuação
#include <ctype.h> //Biblioteca para função toupper
#define tam 12
// tam é a variavel para declaração do tamanho do vetor da struct

typedef struct
{                         // Struct para armazenar os dados do produto
    int codigo, estoque;  // codigo e estoque do produto
    char tipo, nome[156]; // tipo e descrição do produto
} produto;                // Produto é a nomenclatura do tipo da struct

int printar_menu(); // Referenciamento da função, para utilização na main
produto cadastroProduto(produto produt[], int x); // Referenciamento da função, para utilização na main
void MostrarRegistro(produto produt[],int x); // Referenciamento da função, para utilização na main
void ordenar(produto produt[], int x); // Referenciamento da função, para utilização na main
void BuscaConsulta(produto produt[], int x); // Referenciamento da função, para utilização na main
int RemoveFilme(produto produt[], int x); // Referenciamento da função, para utilização na main
void CorrecaoCadastro(produto produt[], int x); // Referenciamento da função, para utilização na main
void AtualizaEstoque(produto produt[], int x); // Referenciamento da função, para utilização na main

int main() //Inicia a Função Main, com retorno vazio
{
    setlocale(LC_ALL, "Portuguese"); // Define acentuação para a acentuação do português
    produto prod[12]; //Vetor do tipo produto onde será armazenado os cadastros
    int cont=0; //Quantidade de cadastros feitos
    int menu; //Variavel que define qual a opção selecionada no menu
     int confirma; //variavel de retorno do RemoveFilme, para verificar se for removido o filme ou não
    do{ //Faz com que o Menu se repita até que seja informado a saída
        menu = printar_menu();
        switch(menu){
            case 1: //Opção de cadastro
                if(cont<12){ //Verifica se ja foi cadastrado o máximo de filmes
                    //Chama a função de cadastro, recebe o retorno, aumenta o contator e ordena
                    prod[cont] = cadastroProduto(prod, cont);
                    cont++;
                    ordenar(prod, cont);
                }else{
                    printf("Quantidade máxima de 12 filmes cadastrados atingida");
                }
            break;

            case 2:
                if(cont==0){ //Verifica se há cadastro
                        printf("Não é possível realizar a busca, pois não há filme cadastrado.\n");
                    }else{
                        BuscaConsulta(prod, cont); //Chama a função de busca e consulta, onde é feito a busca com cógigo ou gênero
                    }
                break;

            case 3:
                if(cont==0){ //Verifica se há cadastro
                    printf("\nNão é possível excluir um cadastro, pois não há filme cadastrado.\n");
                }else{
                    confirma = RemoveFilme(prod, cont); //Chama função de remover filme e recebe o retorno
                    if(confirma==1){
                        ordenar(prod, cont); //Ordena todo o vetor jogando o cadastro excluído pro fim e depois diminui o contador
                        cont--;
                    }
                }
            break;

            case 4:
                if(cont==0){ //Verifica se há cadastro
                    printf("\nNão é possível corrigir um cadastro, pois não há filme cadastrado.\n");
                }else{
                    CorrecaoCadastro(prod, cont); //Chama função de correção, corrigi e ordena
                    ordenar(prod, cont);
                }
            break;
            
            case 5:
                if(cont==0){ //Verifica se há cadastro
                    printf("\nNão é possível atualizar um estoque, pois não há filme cadastrado.\n");
                }else{
                    AtualizaEstoque(prod, cont); //Chama função de atualizar estoque
                }
            break;
            case 6:
                if(cont==0){ //Verifica se há cadastro
                    printf("\nNão é possível mostrar todos os cadastros, pois não há filme cadastrado.\n");
                }else{
                    MostrarRegistro(prod, cont); //Chama a função para mostrar todos os registros
                }
            break;

            default: //Caso não seja nenhuma das opções acima é a opção 7, no caso a saída do programa
                printf("\nOpção de encerramento do programa selecionada\n");
                printf("\nEncerrando programa...\n");
        }
    }while(menu!=7); //Repete o programa enquanto não for digitado a opção 7

    return 0;
}

int printar_menu() //Função que exibe o menu e retorna um int com qual a opção selecionada
{
    int option; //Variavel local que recebe a opção

    //Exibe o menu
    printf("\n\n--- MENU ---\n");
    printf("1 - Cadastro de filme\n");
    printf("2 - Busca/Consulta\n");
    printf("3 - Remoção de filme\n");
    printf("4 - Correção de cadastro\n");
    printf("5 - Atualização de estoque\n");
    printf("6 - Mostrar todos os registros\n");
    printf("7 - Sair\n");

    printf("\nSelecione uma opção do menu: "); // Solicitar a escolha do usuário
    fflush(stdin); 
    scanf("%d", &option); //Lê a escolha do usuário

    if (option > 0 && option < 8){ //Verifica se o int digitado é uma opção válida do menu
        return option;
    }
    else //Se o int digitado não for uma das opções do menu, ele solicita novamente
    {
        do{
            option = 0; //Zera a variavel, pois em casos especificos pode ser que gere algum bug
            printf("\nOpção inválida, essa opção não existe no menu\n");

            printf("\n--- MENU ---\n");
            printf("1 - Cadastro de filme\n");
            printf("2 - Busca/Consulta\n");
            printf("3 - Remoção de filme\n");
            printf("4 - Correção de dados\n");
            printf("5 - Atualização de estoque\n");
            printf("6 - Mostrar todos os registros\n");
            printf("7 - Sair\n");

            printf("\nEscolha uma opção do menu");
            printf("\nDigite uma opção válida: ");
            fflush(stdin);
            scanf("%d", &option);
        } while (option < 1 || option > 7); //Repete até que seja digitado uma opção valida
        return option;
    }
}

produto cadastroProduto(produto produt[], int x) //Função que faz a solicitação e armazenamento das informações dos produtos
{
    produto p;
    int existe=0;
    int flag=0;
    printf("\nOpção de cadastro selecionada.\n");
    printf("\nIniciando cadastro de filme\n");
    do{ //Repete até que seja digitado um código válido que não exista cadastro
        flag=0;
        printf("\nO código do filme deve conter 4 digitos inteiros");
        printf("\nDigite o código do filme: ");
        fflush(stdin);
        scanf("%d",&p.codigo); 
        if(p.codigo>999 && p.codigo<10000){ //Verifica se é um código válido
            for(int i=0;i<x;i++){
                if(p.codigo==produt[i].codigo){ //Verifica se o código ja existe
                    printf("\nEsse código ja existe, escolha outro código");
                    flag=1;
                }
            }
            if(flag==0){
                existe=1;
            }
        }else{
            printf("\nCódigo inválido, não inserido");
        }
    }while(existe!=1);
    printf("\nCódigo armazenado com sucesso");

    do{
        printf("\nO estoque do filme deve ser um numero inteiro de até 10.000");
        printf("\nDigite o estoque do filme informado: ");
        fflush(stdin);
        scanf("%d",&p.estoque);
    }while(p.estoque>1000);
    
    if(p.estoque<10001){
        printf("\nEstoque armazenado com sucesso\n");
    }else{
        do{
            p.estoque=0;
            printf("\nO estoque informado é inválido, o estoque deve ser um inteiro de até 10.000");
            printf("\nDigite o estoque disponível do filme: ");
            fflush(stdin);
            scanf("%d",&p.estoque);
        }while(p.estoque>10000);
        printf("\nEstoque armazenado com sucesso\n");
    }

    printf("\nO nome do filme deve ser de até 150 caracteres");
    printf("\nDigite o nome do filme: ");
    fflush(stdin);
    fgets(p.nome, 156, stdin);
    printf("\nNome do filme armazenado com sucesso\n");

    printf("\nGêneros disponíveis\n");
    printf("A - Ação e Aventura\n");
    printf("C - Comédia\n");
    printf("D - Drama\n");
    printf("F - Ficção Científica\n");
    printf("T - Terror\n");

    printf("\nEscolha apenas um dos gêneros disponíveis");
    printf("\nDigite o gênero: ");
    fflush(stdin);
    scanf("%c",&p.tipo);
    p.tipo=toupper(p.tipo);
    if(p.tipo=='A' || p.tipo=='C' || p.tipo=='D' || p.tipo=='F' || p.tipo=='T'){
        printf("\nGênero armazenado com sucesso\n");
    }else{
        do{
            printf("\nO gênero escolhido não é um gênero disponível");
            printf("\nGêneros disponíveis\n");
            printf("A - Ação e Aventura\n");
            printf("C - Comédia\n");
            printf("D - Drama\n");
            printf("F - Ficção Científica\n");
            printf("T - Terror\n");
            printf("Digite um dos gêneros disponíveis: ");
            fflush(stdin);
            scanf("%c",&p.tipo);
            p.tipo=toupper(p.tipo);
        }while(p.tipo!='A' && p.tipo!='C' && p.tipo!='D' && p.tipo!='F' && p.tipo!='T');
        printf("\nGênero armazenado com sucesso");
    }
    return p;

}

void MostrarRegistro(produto produt[],int x){
    printf("\nOpção de mostrar todos os cadastros selecionado.");
    for(int i=0; i<x; i++){
            printf("\nInformações do %dº filme\n",i+1);
            printf("\nCódigo: %d",produt[i].codigo);
            printf("\nEstoque: %d",produt[i].estoque);
            printf("\nNome: %s",produt[i].nome);
            printf("Gênero: %c\n",produt[i].tipo);
        }
}

void ordenar(produto produt[], int x) //Metódo de ordenação bubllesort(Metódo da bolha)
{
    int i, j;
    for(i = x - 1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(produt[j].codigo > produt[j+1].codigo) /* compara elementos adjacentes */
            {
            produto temp;
            temp = produt[j]; /* troca elementos em v[j] e v[j+1] */
            produt[j] = produt[j+1];
            produt[j+1] = temp;
            }
        }
    }
}

void BuscaConsulta(produto produt[], int x){
    int codigo, flag, posicao,opcao;
    char genero;
 
    printf("\nOpção de busca/consulta selecionada.\n");
    do {
        printf("\nPara realizar a busca/consulta, selecione uma das opções");
        printf("\n1 - Código do filme");
        printf("\n2 - Gênero do filme");
        printf("\nDigite a opção que deseja fazer a busca: ");
        fflush(stdin);
        scanf("%d", &opcao);
        if(opcao!=1 && opcao!=2){
            printf("\nO código inserido não é uma opção válida.");
        }
    }while(opcao !=1 && opcao!=2);
    if(opcao==1){
        printf("\nSelecionado busca pelo código do filme.");
        printf("\nDigite o código do filme(um inteiro de 4 dígitos): ");
        fflush(stdin);
        scanf("%d",&codigo);
        for(int i=0; i<x; i++){
            if(codigo==produt[i].codigo){
                flag=1;
                posicao=i;
            }
        }
        if(flag==1){
            printf("\nFilme encontrado: ");
            printf("\nCódigo: %d", produt[posicao].codigo);
            printf("\nEstoque: %d", produt[posicao].estoque);
            printf("\nNome: %s", produt[posicao].nome);
            printf("Gênero: %c", produt[posicao].tipo); 
        }else{
            printf("\nFilme não encontrado, verifique o código e tente novamente.");
        }
    }else{
        printf("\nSelecionado busca pelo gênero do filme.");
        printf("\nDigite o gênero do filme(A, C, D, F OU T): ");
        fflush(stdin);
        scanf("%c",&genero);
        genero=toupper(genero);
        for(int i=0;i<x;i++){
            if(genero==produt[i].tipo){
                printf("\nFilme encontrado: ");
                printf("\nCódigo: %d", produt[i].codigo);
                printf("\nEstoque: %d", produt[i].estoque);
                printf("\nNome: %s", produt[i].nome);
                printf("Gênero: %c\n", produt[i].tipo);
                flag=1;
            }
        }
        if(flag==0){
            printf("\nNão existe filme cadastrado com esse gênero.");
        }
    }

}

int RemoveFilme(produto produt[], int x){
    int codigo;
    printf("\nOpção de remoção de filme selecionada.\n");
    printf("\nPara realizar a remoção do cadastro de um filme, informe o codigo do filme");
    printf("\nDigite o código do filme: ");
    fflush(stdin);
    scanf("%d",&codigo);
    for(int i=0;i<x;i++){
        if(codigo==produt[i].codigo){
            printf("\nFilme encontrado, filme a ser excluido: ");
            printf("\nCódigo: %d", produt[i].codigo);
            printf("\nEstoque: %d", produt[i].estoque);
            printf("\nNome: %s", produt[i].nome);
            printf("Gênero: %c", produt[i].tipo);
            produt[i].codigo+=10000;
            printf("\nFilme excluído.");
            return 1;
        }
    }
    printf("\nNão foi possível excluir pois não existe cadastro com esse código.");
    return 0;
}

void CorrecaoCadastro(produto produt[], int x){
    int codigo, flag=0, posicao;
    printf("\nOpção de correção de cadastro selecionado.\n");
    printf("\nPara realizar a correção de cadastro informe o código do filme: ");
    fflush(stdin);
    scanf("%d",&codigo);
    for(int i=0; i<x; i++){
        if(codigo==produt[i].codigo){
            flag=1;
            posicao=i;
            printf("\nCadastro encontrado.\n");
        }
    }

    if(flag==1){
        int opcao;
        int VerificaEstoque;
        char VerificaNome[156];
        char VerificaGenero;
        printf("\nInformações do cadastro selecionado:");
        printf("\nCódigo: %d", produt[posicao].codigo);
        printf("\nEstoque: %d", produt[posicao].estoque);
        printf("\nNome: %s", produt[posicao].nome);
        printf("Gênero: %c", produt[posicao].tipo);

        do{
            printf("\n\nSelecione uma das opções para mudar:");
            printf("\n1 - Código");
            printf("\n2 - Estoque");
            printf("\n3 - Nome");
            printf("\n4 - Gênero");
            printf("\n5 - Retornar ao menu");
            printf("\nDigite a operação desejada(Em números): ");
            fflush(stdin);
            scanf("%d",&opcao);
            switch(opcao){
                case 1:
                    printf("\nAlteração de código selecionado.");
                    int verificacodigo, existe=0, flag1=0;
                    do{
                        verificacodigo=0;
                        flag1=0;
                        printf("\nO código do filme deve conter 4 digitos inteiros");
                        printf("\nDigite o código do filme: ");
                        fflush(stdin);
                        scanf("%d",&verificacodigo); 
                        if(verificacodigo>999 && verificacodigo<10000){
                            for(int i=0;i<x;i++){
                                if(verificacodigo==produt[i].codigo){
                                    printf("\nEsse código ja existe, escolha outro código");
                                    flag1=1;
                                }
                            }
                            if(flag1==0){
                                existe=1;
                            }
                        }else{
                            printf("\nCódigo inválido, não inserido");
                        }
                    }while(existe!=1);
                    produt[posicao].codigo=verificacodigo;
                    printf("\nCódigo alterado com sucesso");
                break;
                case 2:
                    printf("\nAlteração de estoque selecionado.");
                    printf("\nO estoque informado é inválido, o estoque deve ser um inteiro de até 10.000");
                    printf("\nDigite o estoque disponível do filme: ");
                    fflush(stdin);
                    scanf("%d",&VerificaEstoque);
                    if(VerificaEstoque<10001){
                        produt[posicao].estoque=VerificaEstoque;
                        printf("\nEstoque armazenado com sucesso\n");
                    }else{
                        do{
                            VerificaEstoque=0;
                            printf("\nO estoque informado é inválido, o estoque deve ser um inteiro de até 10.000");
                            printf("\nDigite o estoque disponível do filme: ");
                            fflush(stdin);
                            scanf("%d",&VerificaEstoque);
                        }while(VerificaEstoque>10000);
                        produt[posicao].estoque=VerificaEstoque;
                        printf("\nEstoque armazenado com sucesso\n");
                    }
                break;
                case 3:
                    printf("\nAlteração de nome selecionado.");
                    printf("\nO nome do filme deve ser de até 150 caracteres");
                    printf("\nDigite o nome do filme: ");
                    fflush(stdin);
                    fgets(VerificaNome, 156, stdin);
                    strcpy(produt[posicao].nome, VerificaNome);
                    printf("\nNome do filme armazenado com sucesso\n");
                break;
                case 4:
                    printf("\nAlteração de Gênero selecionado.");
                    printf("\nEscolha apenas um dos gêneros disponíveis");
                    printf("\nDigite o gênero: ");
                    fflush(stdin);
                    scanf("%c",&VerificaGenero);
                    VerificaGenero=toupper(VerificaGenero);
                    if(VerificaGenero=='A' || VerificaGenero=='C' || VerificaGenero=='D' || VerificaGenero=='F' || VerificaGenero=='T'){
                        produt[posicao].tipo=VerificaGenero;
                        printf("\nGênero armazenado com sucesso\n");
                    }else{
                        do{
                            printf("\nO gênero escolhido não é um gênero disponível");
                            printf("\nGêneros disponíveis\n");
                            printf("A - Ação e Aventura\n");
                            printf("C - Comédia\n");
                            printf("D - Drama\n");
                            printf("F - Ficção Científica\n");
                            printf("T - Terror\n");
                            printf("Digite um dos gêneros disponíveis: ");
                            fflush(stdin);
                            scanf("%c",&VerificaGenero);
                            VerificaGenero=toupper(VerificaGenero);
                        }while(VerificaGenero!='A' && VerificaGenero!='C' && VerificaGenero!='D' && VerificaGenero!='F' && VerificaGenero!='T');
                        produt[posicao].tipo=VerificaGenero;
                        printf("\nGênero armazenado com sucesso");
                    }
                break;
                case 5:
                    printf("\nCadastro atualizado do filme selecionado");
                    printf("\nCódigo: %d",produt[posicao].codigo);
                    printf("\nEstoque: %d",produt[posicao].estoque);
                    printf("\nNome: %s",produt[posicao].nome);
                    printf("Gênero: %c\n",produt[posicao].tipo);
                break;
                
                case 6:
                    printf("\nRetornando ao menu.");
                break;

                default:
                    printf("\n\nOpção inválida, digite uma opção do menu\n");
            }
        }while(opcao!=5);
    }else{
        printf("\nCadastro não encontrao, verifique o código e tente novamente.\n");
    }
}

void AtualizaEstoque(produto produt[], int x){
    int codigo, flag=0, posicao, VerificaEstoque;
    printf("\nOpção de Atualização de estoque selecionado.\n");
    printf("\nPara realizar a atualização de estoque informe o código do filme cadastrado: ");
    fflush(stdin);
    scanf("%d",&codigo);
    for(int i=0; i<x; i++){
        if(codigo==produt[i].codigo){
            flag=1;
            posicao=i;
            printf("\nCadastro encontrado.\n");
        }
    }
    if(flag==1){
        printf("\nInformações do cadastro selecionado:");
        printf("\nCódigo: %d", produt[posicao].codigo);
        printf("\nEstoque: %d", produt[posicao].estoque);
        printf("\nNome: %s", produt[posicao].nome);
        printf("Gênero: %c", produt[posicao].tipo);

        printf("\nInforme o novo estoque, valor máximo de 10.000: ");
        fflush(stdin);
        scanf("%d",&VerificaEstoque);
        if(VerificaEstoque<10001){
                        produt[posicao].estoque=VerificaEstoque;
                        printf("\nEstoque alterado com sucesso\n");
                    }else{
                        do{
                            VerificaEstoque=0;
                            printf("\nO estoque informado é inválido, o estoque deve ser um inteiro de até 10.000");
                            printf("\nDigite o estoque disponível do filme: ");
                            fflush(stdin);
                            scanf("%d",&VerificaEstoque);
                        }while(VerificaEstoque>10000);
                        produt[posicao].estoque=VerificaEstoque;
                        printf("\nEstoque alterado com sucesso\n");
                    }
    }else{
        printf("\nNão existe filme com o código informado, verifique o código e tente novamente.");
    }
}
