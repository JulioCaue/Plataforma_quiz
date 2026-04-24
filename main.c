#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "bibliotecas_locais/cJSON.h"

//função responsavel pelo menu do programa
//define variaveis e textos que são usados no menu
// além da logica do mesmo, como a movimentação entre os menus
int menu_programa(){
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

cJSON* ler_arquivo(){
    //abrir arquivo
    FILE *arquivo = fopen("perguntas.json","r");
    if (arquivo == NULL){
        printf("Erro: Não foi possivel abrir o arquivo\n");
        return NULL;
    }
    //transformar o conteudo do arquivo em uma string
    fseek(arquivo,0,SEEK_END);
    long tamanho = ftell(arquivo);
    rewind(arquivo);

    char *buffer = malloc(tamanho + 1);
    int len = fread(buffer,1,tamanho,arquivo);
    buffer[len]='\0';

    //parsear a data do arquivo json 
    cJSON *json_parseado = cJSON_Parse(buffer);
    fclose(arquivo);
    if (json_parseado == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
            printf("Erro: %s\n", error_ptr);
        }
    }
    return json_parseado;
}

int logica_pergunta(int id_pergunta, cJSON* json_parseado){
    cJSON *data_pergunta = cJSON_GetArrayItem(json_parseado,id_pergunta);
    
    cJSON *pergunta = cJSON_GetObjectItem (data_pergunta,"pergunta");

    cJSON *respostas = cJSON_GetObjectItem (data_pergunta,"respostas");

    cJSON *resposta_correta = cJSON_GetObjectItem (data_pergunta,"resposta_correta");
    
    int i = 1;
    cJSON *resposta = NULL;
    printf("Pergunta: %s\n\n",pergunta -> valuestring);
    cJSON_ArrayForEach(resposta,respostas){
        if (cJSON_IsString(resposta)){
            printf("Opção %d: %s\n", i++, resposta -> valuestring);
        }
    }
    return (resposta_correta->valueint);
}

//função principal do programa
void main(){
    int resposta_correta;
    int pontuação_jogador = 0;
    int tentativas_restantes = 3;
    int perguntas_acertadas = 0;
    int id_pergunta = 0;
    char resposta_jogador[100];
    system("cls");
    //faz terminal usar utf-8
    SetConsoleOutputCP(65001);

    //logica do programa fica aqui
    //usando funções separadas
    cJSON* json_parseado=ler_arquivo();
    if (json_parseado == NULL){
        printf("Erro: falha ao carregar dados\n");
        getchar();
    }
    int total_perguntas = cJSON_GetArraySize(json_parseado);
    while (1){
        if (menu_programa()==1){
            // entrei no jogo
            for (int i = 0; i < total_perguntas; ++i){
                //chamada da função do jogo fica aqui
                resposta_correta = (logica_pergunta(id_pergunta, json_parseado));
                resposta_correta++;
                scanf(" %s",&resposta_jogador);

                int resposta_jogador_int = atoi(resposta_jogador);
                int resposta_valida=1;
                for (int j = 0; resposta_jogador[j] != '\0'; j++){
                    if (resposta_jogador[j] <= '0' || resposta_jogador[j] > '9'){
                        resposta_valida = 0;
                        break;
                    }
                }

                if (resposta_jogador[0] != '\0' && resposta_jogador[0] != '\n'){
                    if ((resposta_jogador_int) == resposta_correta && resposta_valida){
                        pontuação_jogador++;
                        perguntas_acertadas++;
                        system("cls");
                        printf("Certa Resposta!\nPontuação atual: %d\n",pontuação_jogador);
                        getchar();
                    }

                    else{
                        if (pontuação_jogador>0){pontuação_jogador--;}
                        tentativas_restantes--;
                        system("cls");
                        printf("Resposta errada!\n");
                        printf("Opção correta era a opção numero %d!\n\n",--resposta_correta);
                        getchar();
                    }
                    if (tentativas_restantes==0){break;}
                    id_pergunta++;
                }
                else{
                    printf("Erro: mensagem_correta está nula.");
                    break;
                }
            }
            system("cls");
            printf("Fim de jogo!\n");
            printf("Pontuação final: %d\n",pontuação_jogador);
            printf("Você acertou %d/%d perguntas!\n",perguntas_acertadas,total_perguntas);
            getchar();
        }
    }
    cJSON_Delete(json_parseado);
}