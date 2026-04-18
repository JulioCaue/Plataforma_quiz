#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "bibliotecas_locais/cJSON.h"

cJSON* ler_arquivo(){
    //abrir arquivo
    FILE *arquivo = fopen("perguntas.json","r");
    if (arquivo == NULL){
        printf("Erro: Não foi possivel abrir o arquivo\n");
        return NULL;

    //transformar o conteudo do arquivo em uma string
    char buffer[1024];
    int len = fread(buffer,1,sizeof(buffer),arquivo);

    //parsear a data do arquivo json 
    cJSON *json_parseado = cJSON_Parse(buffer);
    if (json_parseado == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            printf("Erro: %s\n", error_ptr);
            }
        }   
    
    return json_parseado;
    }
}

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

char* pegar_pergunta(int pergunta_atual, cJSON* json_parseado){
    char pergunta_str[10];
    sprintf(pergunta_str,"%d",pergunta_atual);
    cJSON *id_pergunta = cJSON_GetObjectItem(json_parseado,pergunta_str);
    if (cJSON_IsString(id_pergunta) && (id_pergunta -> valuestring != NULL)){
        return id_pergunta -> valuestring;
    }
}


//função principal do programa
void main(){
    //logica do programa fica aqui
    //usando funções menores
    cJSON* json_parseado=ler_arquivo();
    if (json_parseado == NULL){
        printf("Erro: falha ao carregar dados\n");
        getchar();
    }
    //faz terminal usar utf-8
    SetConsoleOutputCP(65001);
    if (menu_programa()==1){
        printf("testando");
        //chamada da função do jogo fica aqui
        printf(pegar_pergunta(0, json_parseado));
        getchar();
        getchar();
    }

    //notas:
        //confirmação de inicio de jogo será menu principal retornando 1.
}