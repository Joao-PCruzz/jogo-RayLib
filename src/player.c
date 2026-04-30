#include "raylib.h"
#include "player.h"

//Iniciando o player com suas características
void InitPlayer(Player *player){
    player->posicao = (Vector2){100, 100};
    player->velocidade = (Vector2){0, 0};
    player->rapidez = 200.0f;
    player->gravidade = 800.0f;
    player->forcaPulo = -1000.0f;
    player->controleDoAr = 0.5f; //50% de controle do ar
    player-> multiQueda = 2.0f;
    player-> multiPuloBaixo = 2.0f;
    player->estaNoChao = 0; //1 para quando pode pular, 0 para quanndo não pode
}

//Atualizar o Frame
//GetFrameTime garante que o jogo funcione igual em qualquer FPS
//IsKeyDown checa se a tecla está sendo pressionada
void UpdatePlayer(Player *player, Rectangle ground){
    //Cria o retângulo do player a todo movimento
    Rectangle playerRect = {
        player->posicao.y,
        player->posicao.x,
        50, 
        50
    };


    float dt = GetFrameTime(); //linha para igualar o movimento em qualquer FPS
    float controle = player->estaNoChao ? 1.0f : player->controleDoAr; //se o jogador está no chão, usa 1, se não, usa controle do ar

    //Movimento vertical
    if(IsKeyDown(KEY_D)) player->posicao.x += player->rapidez * controle * GetFrameTime(); //KeyDown é se a tecla está sendo pressionada
    if(IsKeyDown(KEY_A)) player->posicao.x -= player->rapidez * controle * GetFrameTime();

    //Gravidade
    player->velocidade.y += player->gravidade * dt;

    //Para dar uma sensação de queda mais rápida, mais pesada
    if (player->velocidade.y > 0) {
        player->velocidade.y += player->gravidade * player->multiQueda * dt;
    }
    //Para cortar o pulo no meio e permitir controlar a altura do pulo, tornando o pulo mais curto se soltar o botao
    else if (player->velocidade.y < 0 && !IsKeyDown(KEY_SPACE)) {
        player->velocidade.y += player->gravidade * player->multiPuloBaixo * dt;
    }

    //Pulo
    if(IsKeyPressed(KEY_SPACE) && player->estaNoChao) { //KeyPressed é quando a tecla foi pressionada uma vez
        player->velocidade.y = player->forcaPulo;
        player->estaNoChao = 0;
    }
    if(IsKeyPressed(KEY_SPACE) && player->velocidade.y < 0){
        player->velocidade.y *= 0.5f;
    }
    //Aplicação de velocidade ao pulo
    player->posicao.y += player->velocidade.y * dt;

    if(CheckCollisionRecs(playerRect, ground)){
        player->posicao.y = ground.y - 50;
        player->velocidade.y = 0;
        player->estaNoChao = 1;

    }

    //Chão temporário
    if(player->posicao.y >= 400){
        player->posicao.y = 400;
        player->velocidade.y = 0;
        player->estaNoChao = 1;
    }
}

//Desenhar o jogador
void DrawPlayer(Player player){
    DrawRectangle(player.posicao.x, player.posicao.y, 50, 50, RED);
}