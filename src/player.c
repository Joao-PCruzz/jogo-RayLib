#include "raylib.h"
#include "player.h"

//Iniciando o player com suas características
void InitPlayer(Player *player){
    player->posicao = (Vector2){100, 100};
    player->velocidade = (Vector2){0, 0};
    player->rapidez = 200.0f;
}

//Atualizar o Frame
//GetFrameTime garante que o jogo funcione igual em qualquer FPS
//IsKeyDown checa se a tecla está sendo pressionada
void UpdatePlayer(Player *player){
    if(IsKeyDown(KEY_D)) player->posicao.x += player->rapidez * GetFrameTime();
    if(IsKeyDown(KEY_A)) player->posicao.x -= player->rapidez* GetFrameTime();
}

//Desenhar o jogador
void DrawPlayer(Player player){
    DrawRectangle(player.posicao.x, player.posicao.y, 50, 50, RED);
}