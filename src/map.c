#include "raylib.h"
#include "map.h"

//Definição do mapa
int mapa[LINHAS][COLUNAS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 é para nada
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // 1 é para chão, e 2 é para parede (não criada ainda?)
};

//desenhar o mapa
void DrawMapa(){
    for(int y=0; y < LINHAS; y++){
        for(int x=0; x < COLUNAS; x++){
            //desenhar o retângulo a cada interação na cor azul escuro
            DrawRectangleRec(GetTileRect(y,x), DARKBLUE);
        }
    }
}

//desenhar o retângulo
Rectangle GetTileRect(int x, int y){
    return(Rectangle){
        x * TILE_SIZE,
        y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE
    };
};