#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

//função responsavel pelo menu do programa
int menu_programa(){
    //define variaveis e textos usados.
    char nome_usuario[30]="sem_nome_usuario";
    char escolha_menu[5];
    int confirmacao_nome;
    int olhando_menu=1;
    const char *texto_explicação =(
    "\n=======EXPLICAÇÃO DO JOGO=======\n"
    "texto placeholder\n"
    "================================\n\n");

    const char *texto_menu_principal=(
    "\n=======MENU DO JOGO=======\n"
    "1. Iniciar jogo\n"
    "2. Ajuda\n"
    "3. Sair\n\n"
    "Escolha uma das opções do menu: \0");

    while (strcmp(nome_usuario,"sem_nome_usuario")==0){
        printf("Por favor digite seu nome.\n\0");
        if (fgets (nome_usuario, sizeof(nome_usuario), stdin) != NULL){
            nome_usuario [strcspn(nome_usuario, "\n")] = '\0';
        }

        else{
            printf("Nome não pode estar vazio.\n\0");
        }
    }

    printf(texto_menu_principal);
    if (fgets (escolha_menu, sizeof(escolha_menu),stdin) != NULL){
        escolha_menu[strcspn(escolha_menu,"\n")]='\0';
    }

    while (olhando_menu==1){
        if (strcspn(escolha_menu,"1")==0){
            system("cls");
            olhando_menu=0;
            return 1;
        }
        else if (strcspn(escolha_menu,"2")==0){
            system("cls");
            printf(texto_explicação);
            printf("aperte qualquer botão para sair. ");
            getchar();
            system("cls");
            printf(texto_menu_principal);
            if (fgets (escolha_menu, sizeof(escolha_menu),stdin) != NULL){
                escolha_menu[strcspn(escolha_menu,"\n")]='\0';
    }
        }
        else if (strcspn(escolha_menu,"3")==0){
            olhando_menu=0;
        }
        else{
            system("cls");
            printf(texto_menu_principal);
            printf("tela limpa por else");
        }
    }


    
}


//função principal do programa
void main(){
    //logica do programa fica aqui
    //usando funções menores
    //faz terminal usar utf-8
    SetConsoleOutputCP(65001);
    if (menu_programa()==1){
        //chamada da função do jogo fica aqui
    }

    //notas:
        //confirmação de inicio de jogo será menu principal retornando 1.
}