#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct{
    int x, y;
}Ponto;
typedef struct{
    Ponto posicao;
    int distancia;
}NoFila;
typedef struct{
    char mapa[MAX][MAX];
    int linhas;
    int colunas;
    Ponto joao;
    Ponto pedro;
    Ponto tesouro;
    bool achou_joao;
    bool achou_pedro;
    bool achou_tesouro;
}Mapa;

void inicializarMapa(Mapa *m){
    m->linhas = 0;
    m->colunas = 0;
    m->achou_joao = false;
    m->achou_pedro = false;
    m->achou_tesouro = false;
}
bool Valido(const Mapa *m, int x, int y){
    return x >= 0 && x < m->linhas && y >= 0 && y < m->colunas;
}
bool Transitavel(const Mapa *m, int x, int y){
    return m->mapa[x][y] == ' ' || m->mapa[x][y] == '*' || 
           m->mapa[x][y] == '+' || m->mapa[x][y] == '$';
}
int bfs(const Mapa *m, Ponto inicio){
    bool visitado[MAX][MAX] = {false};
    NoFila fila[MAX * MAX];
    int frente = 0, tras = 0;

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    fila[tras].posicao = inicio;
    fila[tras].distancia = 0;
    tras++;
    visitado[inicio.x][inicio.y] = true;

    while(frente < tras){
        NoFila atual = fila[frente];
        frente++;

        if(m->mapa[atual.posicao.x][atual.posicao.y] == '$'){
            return atual.distancia;
        }

        for(int i = 0; i < 4; i++){
            int novoX = atual.posicao.x + dx[i];
            int novoY = atual.posicao.y + dy[i];

            if(Valido(m, novoX, novoY)){
                if(Transitavel(m, novoX, novoY)){
                    if(!visitado[novoX][novoY]){
                        visitado[novoX][novoY] = true;
                        fila[tras].posicao.x = novoX;
                        fila[tras].posicao.y = novoY;
                        fila[tras].distancia = atual.distancia + 1;
                        tras++;
                    }
                }
            }
        }
    }
    return -1;
}
void lerMapa(Mapa *m){
    scanf("%d", &m->linhas);
    getchar();

    for(int i = 0; i < m->linhas; i++){
        fgets(m->mapa[i], MAX, stdin);
        
        for(int j = 0; j < MAX; j++){
            if(m->mapa[i][j] == '\n'){
                m->mapa[i][j] = '\0';
                m->colunas = (j > m->colunas) ? j : m->colunas;
                break;
            }
        }

        for(int j = 0; m->mapa[i][j] != '\0'; j++){
            if(m->mapa[i][j] == '*'){
                m->joao.x = i;
                m->joao.y = j;
                m->achou_joao = true;
            }else if(m->mapa[i][j] == '+'){
                m->pedro.x = i;
                m->pedro.y = j;
                m->achou_pedro = true;
            }else if(m->mapa[i][j] == '$'){
                m->tesouro.x = i;
                m->tesouro.y = j;
                m->achou_tesouro = true;
            }
        }
    }
}

int main(){
    Mapa mapa;
    inicializarMapa(&mapa);
    lerMapa(&mapa);

    if(!mapa.achou_tesouro){
        printf("-1\n");
        return 0;
    }

    int dist_joao = -1, dist_pedro = -1;

    if(mapa.achou_joao){
        dist_joao = bfs(&mapa, mapa.joao);
    }

    if(mapa.achou_pedro){
        dist_pedro = bfs(&mapa, mapa.pedro);
    }

    if(dist_joao == -1 && dist_pedro == -1){
        printf("-1\n");
    }else if(dist_joao == -1){
        printf("2\n");
    }else if(dist_pedro == -1){
        printf("1\n");
    }else if(dist_joao < dist_pedro){
        printf("1\n");
    }else if(dist_pedro < dist_joao){
        printf("2\n");
    }else{
        printf("0\n");
    }

    return 0;
}