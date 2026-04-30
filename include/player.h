#include "raylib.h"
//header guard
#ifndef PLAYER_H
#define Player_h

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
void UpdatePlayer(Player *player, Rectangle ground);
void DrawPlayer(Player player);
Rectangle GetPlayerRect(Player *player);

#endif