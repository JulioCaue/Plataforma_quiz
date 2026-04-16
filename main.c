#include <stdio.h>
#include <string.h>
#include <windows.h>

//função responsavel pelo menu do programa
int menu_programa(){
    //define variaveis e textos usados.
    char nome_usuario[30]="sem_nome_usuario";
    int escolha_menu;
    int confirmacao_nome;
    int olhando_menu=1;
    const char *texto_explicação =(
    "\n=======EXPLICAÇÃO DO JOGO=======\n"
    "texto placeholder\n"
    "================================\n");

    const char *menu_principal=
    "\n=======MENU DO JOGO=======\n"
    "1. Iniciar jogo\n"
    "2. Ajuda\n"
    "3. Sair\n";

    while (strcmp(nome_usuario,"sem_nome_usuario")==0){
        printf("Por favor digite seu nome.\n\0");
        if (fgets (nome_usuario, sizeof(nome_usuario), stdin) != NULL){
            nome_usuario [strcspn(nome_usuario, "\n")] = '\0';
            printf("Seu nome está correto? '%s'\n\0",nome_usuario);
            confirmacao_nome=getchar();
            if (confirmacao_nome=='s'){
                break;
                }
        }

        else{
            printf("Nome não pode estar vazio.\n\0");
        }
    }

    printf(menu_principal);
    escolha_menu=getchar();

    while (olhando_menu=='1'){
        if (escolha_menu==1){
            return 1;
        }
        else if (escolha_menu=='2'){
            printf(texto_explicação);
        }
        else if (escolha_menu=='3'){
            olhando_menu=0;
        }
        else{
            printf("Escolha uma das opções do menu.\n\0");
            escolha_menu=getchar();
        }
    }


    
}


//função principal do programa
void main(){
    //logica do programa fica aqui
    //usando funções menores
    SetConsoleOutputCP(65001);
    menu_programa();

    //notas:
        //confirmação de inicio de jogo será menu principal retornando 1.
}