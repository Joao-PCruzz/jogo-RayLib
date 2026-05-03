#include "raylib.h"
#include "map.h"

//Definido como enum pois um typedef enum permite definir um conjunto de constantes inteiras
typedef enum{
    TILE_EMPTY = 0,
    TILE_GROUND = 1,
    TILE_SPIKE = 2,
    TILE_PLATFORM = 3
} TileTypes;

//Definição do mapa
int mapa[MAPA_ALTURA][MAPA_LARGURA] = {
    // teto (vazio)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    // sala esquerda (plataformas)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    // chão contínuo
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

    // sala do meio (plataformas + espinhos)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0},
    {0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0},

    // sala direita (plataformas altas)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},

    // base final
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

    // resto vazio
    {0},{0},{0},{0} 
};

//desenhar o mapa
void DrawMapa(){
    for(int y=0; y < MAPA_ALTURA; y++){
        for(int x=0; x < MAPA_LARGURA; x++){
            switch (mapa[y][x]) {

            case TILE_GROUND:
                DrawRectangleRec(GetTileRect(x,y), BROWN);
                break;

            case TILE_SPIKE:
                DrawRectangleRec(GetTileRect(x,y), RED);
                break;

            case TILE_PLATFORM:
                DrawRectangleRec(GetTileRect(x,y), GREEN);
                break;
            }
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