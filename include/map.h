#include "raylib.h"
#ifndef MAP_H
#define MAP_H

#define MAPA_LARGURA 30
#define MAPA_ALTURA 15
#define TILE_SIZE 40

//Criando o vetor do mapa
//O extern serve para definir o mapa para ser usado no mapa.c ]
//ele diz ao compilador que o mapa existe, mas ainda não guarda memória para ele neste arquivo
extern int mapa[MAPA_ALTURA][MAPA_LARGURA];

//funções 
void DrawMapa();
Rectangle GetTileRect(int x, int y);


#endif