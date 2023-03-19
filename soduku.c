// INCLUSAO DOS LISBS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TAB2 printf("\t\t\t\t") // PARA DAR TAB EM PRINTS
#define BR2 printf("\n\n") // BRAKE 2 ROWS
#define L 3
#define C 3

// DEFINIÇÃO DE ESTRUTURAS
typedef struct{
    int **Matrix; 
}Dtype;




void index_checker(int section, int *col_start, int *lin_start){
    switch(section){
        case 1:{

            *lin_start = 1;
            *col_start = 1;
            break;
        }

        case 2:{

            *lin_start = 1;
            *col_start = 4;
            break;
        }

        case 3:{

            *lin_start = 1;
            *col_start = 7;
            break;
        }

        case 4:{

            *lin_start = 4;
            *col_start = 1;
            break;
        }
        case 5:{

            *lin_start = 4;
            *col_start = 4;
            break;
        }
        case 6:{

            *lin_start = 4;
            *col_start = 7;
            break;
        }
        case 7:{

            *lin_start = 7;
            *col_start = 1;
            break;
        }

        case 8:{

            *lin_start = 7;
            *col_start = 4;
            break;
        }
        case 9:{

            *lin_start = 7;
            *col_start = 7;
            break;
        }
        

    }
}



void geradorDeDadosFake(Dtype* Dados){// GERADOR DE DADOS FAKE PARA FINS DE TESTE
    time_t t;
     srand((unsigned) time(&t));;
    for(int i=0; i<9;i++){
        for(int j=0; j<9;j++){
             Dados->Matrix[i][j] = -1;
        }

    }

    
}


Dtype* alocadorDeDados(){ // ALOCA MATRIX 9X9 DINAMICAMENTE E O RETORNA
    
    Dtype* Dados = (Dtype*)malloc(sizeof(Dtype));
    Dados->Matrix = (int**)malloc(sizeof(int*)*9);
    for(int i=0; i<9;i++){
        Dados->Matrix[i] = (int*)malloc(sizeof(int)*9);
    } 



    // for(int i=0; i<9;i++){
    //     for(int j=0; j<9;j++){
    //          Dados->Matrix[i][j] = rand()%9;
    //     }

    // }


    return Dados;
}



void desalocadorDeDados(Dtype *Dados){

    for(int i=0; i<9; i++){
        free(Dados->Matrix[i]);
    }
    free(Dados->Matrix);
    free(Dados);

}



void matrix_3_3_printer(int section, Dtype *Dados){

    int col;
    int lin;
    index_checker(section, &col, &lin);

    for(int i=lin-1; i <lin+2; i++){
        for(int j = col-1; j<col+2; j++){
            printf("%d ", Dados->Matrix[i][j]);
        }
        printf("\n");
    }
}

int geradorAleatorio(int min, int max){
     time_t t;
     srand((unsigned) time(&t));;
    int numero_aleatorio = (rand() % (max - min + 1)) + min;

    return numero_aleatorio;
}


int verificaLinha(int col, Dtype *Dados, int value){ // VERIFICA COLISAO NA LINHA
    // printf("\n\nlinha\n\n");
    
    
    for(int i=0; i<9;i++){
        // printf("%d ", Dados->Matrix[i][col]);
        if(value == Dados->Matrix[i][col]){
            return 0;
        }
    }
    return 1;
}

int verificaColuna(int linha, Dtype *Dados, int value){ // VERIFICA COLISAO NA COLUNA
    // printf("\n\ncoluna\n\n");
    for(int i=0; i<9;i++){
        // printf("%d ", Dados->Matrix[linha][i]);

        if(value == Dados->Matrix[linha][i]){
            return 0;
        }
    }

    return 1;
}






void preenchedor_matrix_3_3(int qunt, int section, Dtype *Dados){

    int col;
    int lin;
    index_checker(section, &col, &lin);

    // for(int i=lin-1; i <lin+2; i++){
    //     for(int j = col-1; j<col+2; j++){
    //         printf("%d ", Dados->Matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    int counter=0;

    while(counter < qunt){
        int value = geradorAleatorio(0, 9);
        int newCol = geradorAleatorio(col-1, col+1);
        int newLin = geradorAleatorio(lin-1, lin+1);

        if(Dados->Matrix[newLin][newCol] == -1 && verificaColuna(newLin, Dados, value) && verificaLinha(newCol, Dados, value)){
            Dados->Matrix[newLin][newCol] =value;
            counter++; 
        }

        // sleep(1);
    }
}



void atualizadorDeJogo(Dtype *Dados, char* nomeDoFicheiro){
    FILE *jogo = fopen(nomeDoFicheiro, "wb");

    if(jogo == NULL){
        printf("O jogo nao pode ser atualizado! verifique o ficheiro do jogo\n");
    }

    int temp[9*9];
    int counter=0;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            temp[counter] = Dados->Matrix[i][j];
            counter++;
        }

    }



    fwrite(temp, sizeof(int), 9*9, jogo);
    fclose(jogo);
}   


int decoder(char * instruction, int *section, int *line, int *col, int* value ){

    if(strlen(instruction) >= 6){ // VERIFICAR SE A OPÇÃO DIGITADA É "VOLTAR" OU "SALVAR", 
        if(strcmp("salvar", instruction)==0){
            return 1; // PARA SALVAR
        }else{
            return 2; // PARA VOLTAR
        }
    }else{ // SE FOR AS INSTRUÇÕES DE JOGO
        *section = instruction[0]-48;
        *line = instruction[1]-48;
        *col = instruction[2]-48;
        *value = instruction[3]-48;

        return 3;
    }

}





void tablePrinter(Dtype* Dados){ // PRINTADOR DE TABELA
    printf("\n");
    TAB2;
    for(int i =0; i<9; i++){
        for(int j=0; j<9;j++){
            if(Dados->Matrix[i][j]==-1){
                    printf("- ");
                }else{
                    printf("%d ", Dados->Matrix[i][j]);
                }

                if(j==2 || j == 5 || j == 8){
                    printf("  ");
                }
            }
            printf("\n");
            TAB2;
            if(i==2 || i == 5 || i == 8){
            printf("\n");
            TAB2;
        }
    }
    printf("\n");
}


int verificaJogo(Dtype* Dados){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(Dados->Matrix[i][j] == -1){
                return 0;
            }
        }

    }
    return 1;
    
}
 



void resolverJogo(Dtype* Dados){
    printf("\n");
    char instruction[7];
    int col, lin, value, section;
    // getchar();
    setbuf(stdin, NULL);
    while(1){

        TAB2;
        tablePrinter(Dados);
        BR2;
        
        TAB2;
        printf("Digite um comando ou indique a celula a alterar: ");
        fgets(instruction, 7, stdin);
        printf("\n");
        int decoded = decoder(instruction, &section, &lin, &col, &value);


        if(decoded==1){ // SALVAR
            char nome[15];
            // setbuf(stdin, NULL);
            getchar();
            TAB2;
            printf("Digite o nome do arquivo: ");
            fgets(nome, 15, stdin);
            atualizadorDeJogo(Dados, nome);
            printf("\n");
            TAB2;
            printf("Jogo salvo com sucesso\n");
            sleep(1);
            return;
        }else if(decoded== 2){ // SAIR
            return;
        }else{ // JOGAR
            int col_start, lin_start;
            index_checker(section, &col_start, &lin_start);

            int lin_atual = lin_start+lin-2;
            int col_atual = col_start+col-2;
            
            TAB2;
            printf("index %d %d \n", lin_atual, col_atual);
            printf("value %d \n", value);
            TAB2;


            if(Dados->Matrix[lin_atual][col_atual] == -1 && verificaColuna(lin_atual, Dados, value) && verificaLinha(col_atual, Dados, value)){
                Dados->Matrix[lin_atual][col_atual] = value;
            }else{
                BR2;
                TAB2;
                printf("Jogada invalida, tente novamente! ....\n");
            }

            if(verificaJogo(Dados)){
                BR2;
                TAB2;
                printf("Parabens,voce venceu!\n");
                sleep(1);

                return;
            }
        }
    }
}


 



void carregadorDeJogo(Dtype *Dados, char * nomeDoFicheiro){ // LÊ O ESTADO DO JOGO GUARDADO NO FICHEIRO E O COLOCA NA MATRIZ

    FILE* jogo = fopen(nomeDoFicheiro, "rb");



    if(jogo == NULL){
        TAB2;
        printf("O jogo nao pode ser carregado! verifique o ficheiro do jogo\n");
        return;
    }  

    int temp[9*9];

    // Dados = alocadorDeDados();
    fread(temp, sizeof(int), 9*9, jogo);
    fclose(jogo);


    int counter=0;
    for(int i =0; i<9; i++){
        for(int j =0; j<9; j++){
            Dados->Matrix[i][j] = temp[counter];
            counter++;
        }

    }
}







void menuInicial(){
    BR2;
    TAB2;
    printf("0 : Sair do jogo\n");
    TAB2;
    printf("1 : Gerar novo jogo\n");

    TAB2;
    printf("2 : Carregar jogo\n");

    TAB2;
    printf("3 : Resolver jogo\n");
    TAB2;
    printf("Digite sua opçao: ");

}




void geradorDeJogo(int nivel, Dtype* Dados){
    
    // int qnt;
    // for(int i=1; i<=9;i++){
    //     if(nivel == 1){ // NIVEL FACIL
    //         qnt = geradorAleatorio(4,6);
    //     }else{ // NIVEL DIFICIL
    //         qnt = geradorAleatorio(1,3);
    //     }
    //     preenchedor_matrix_3_3(qnt, i, Dados);
    // }

    
    Dtype* Dado[6];
    for(int i=0; i<6;i++){
        Dado[i] = alocadorDeDados();
    }
    FILE *file;
    if(nivel==1){ // NIVEL FACIL
        file = fopen("facil.dat", "rb");
    }else{
        file = fopen("dificil.dat", "rb");
    }

    if(file == NULL){
        TAB2;
        printf("O jogo nao pode ser gerada!, verifique se existe arquino de configuração\n");
    }

    int size = 486;
    int temp[size];

    int areaAleatoria = geradorAleatorio(0, 5);

    fread(temp, sizeof(int), size, file);
    fclose(file);

    int conta = 0;
    for (int d = 0; d < 6; d++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9 ; j++) {
                Dado[d]->Matrix[i][j] = temp[conta];
                conta++;
            }
        }
    }


    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 ; j++) {
            Dados->Matrix[i][j] = Dado[areaAleatoria]->Matrix[i][j];
            conta++;
        }
    }

     
    // for(int i=0; i<6;i++){
    //     desalocadorDeDados(Dado[i] );
    // }    

}


int verificarColuna(int col, int lin, Dtype* Dados){
    if(Dados->Matrix[lin][col]!= -1) return 0;
    return 1;
}


void gerarJogo(Dtype *Dados){
    
    printf("\n");
    int level;
    TAB2;
    printf("Escolhe nivel:\n");
    TAB2;
    printf("1 - Facil\n");
    TAB2;
    printf("2 - Dificl\n");
    TAB2;
    scanf("%d", &level);
    
    if(level ==1 || level ==2){
        TAB2;
        printf("Gerando jogo, aguarde ....\n");
        geradorDeJogo(level, Dados);
        tablePrinter(Dados);
    }else{
        TAB2;
        printf("\t\tEntre com opçao correta\n");
        gerarJogo(Dados);
    }

}





void player(Dtype * Dados){
    int section, line, col,  value;
    char option[6];
    int code;
    while(1){

        menuInicial();
        scanf("%d", &code);
        switch (code){
        case 0:{
            TAB2;
            BR2;
            printf("Tchau!......\n");
            return ;
        }

        case 1:{
            
            Dados = alocadorDeDados();
            geradorDeDadosFake(Dados);
            gerarJogo(Dados);
            break;
        }

        case 2:{
            char nome[15];
            TAB2;
            getchar();
            printf("Digite o nome do ficheiro: ");
            fgets(nome, 15, stdin);
            
            if(Dados==NULL){
                Dados = alocadorDeDados();
            }
            carregadorDeJogo(Dados, nome);
            printf("\n");
            // resolverJogo(Dados);
            tablePrinter(Dados);
            break;
        }

        case 3:{
            if(Dados == NULL){
                TAB2;
                printf("dados nulllos\n");
                Dados = alocadorDeDados();
                geradorDeDadosFake(Dados);
                geradorDeJogo(1, Dados);
                // tablePrinter(Dados);
            }
            resolverJogo(Dados);
            break;
        }
        
        default:
            break;
        }

    }
}


// int main(int argc, char const *argv[]){
   

//     Dtype* Dados = alocadorDeDados();
//     geradorDeDadosFake(Dados);
//     player(Dados);
//     desalocadorDeDados(Dados);
//     return 0;
// }


int main(int argc, char const *argv[]) {
    Dtype* Dados;// = alocadorDeDados();
    // geradorDeDadosFake(Dados);
    player(Dados);

    if(Dados != NULL){
        tablePrinter(Dados);    
        desalocadorDeDados(Dados);
    }

    return 0;
  } 