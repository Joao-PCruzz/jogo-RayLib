#include "raylib.h"
#ifndef MAP_H
#define MAP_H

#define LINHAS 10
#define COLUNAS 20
#define TILE_SIZE 40

//Criando o vetor do mapa
//O extern serve para definir o mapa para ser usado no mapa.c ]
//ele diz ao compilador que o mapa existe, mas ainda não guarda memória para ele neste arquivo
extern int mapa[LINHAS][COLUNAS];

//funções 
void DrawMapa();
Rectangle GetTileRect(int x, int y);


#endif