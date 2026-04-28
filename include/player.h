#include "raylib.h"
//header guard
#ifndef PLAYER_H
#define Player_h

typedef struct{
    Vector2 posicao;
    Vector2 velocidade;
    float rapidez;
} Player;

//funções do player
void InitPlayer(Player *player);
void UpdatePlayer(Player *player);
void DrawPlayer(Player player);

#endif