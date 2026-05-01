#include "raylib.h"
//header guard
#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
    Vector2 posicao;
    Vector2 velocidade;
    float rapidez;
    float gravidade;
    //Para o pulo
    float forcaPulo;
    float controleDoAr;
    float multiQueda;
    float multiPuloBaixo;
    int estaNoChao; //evita que o player pule infinitamente
} Player;

//funções do player
void InitPlayer(Player *player);
void UpdatePlayer(Player *player);
void DrawPlayer(Player player);
Rectangle GetPlayerRect(Player *player);
void GetTileRange(Rectangle rect, int *comecoX, int *fimX, int *comecoY, int *fimY);
void ResolveColisaoX(Player *player);
void ResolveColisaoY(Player *player);

#endif