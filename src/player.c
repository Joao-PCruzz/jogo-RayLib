#include "raylib.h"
#include "player.h"
#include "map.h"

//Iniciando o player com suas características
void InitPlayer(Player *player){
    player->posicao = (Vector2){100, 100};
    player->velocidade = (Vector2){0, 0};
    player->rapidez = 200.0f;
    player->gravidade = 800.0f;
    player->forcaPulo = -1000.0f;
    player->controleDoAr = 0.5f; //50% de controle do ar
    player->multiQueda = 2.0f;
    player->multiPuloBaixo = 2.0f;
    player->estaNoChao = 0; //1 para quando pode pular, 0 para quanndo não pode
}

//Atualizar o Frame
//GetFrameTime garante que o jogo funcione igual em qualquer FPS
//IsKeyDown checa se a tecla está sendo pressionada
void UpdatePlayer(Player *player, Rectangle ground){
    float dt = GetFrameTime(); //linha para igualar o movimento em qualquer FPS
    Rectangle playerRect; //instanciação do retângulo do Player
    float controle = player->estaNoChao ? 1.0f : player->controleDoAr; //se o jogador está no chão, usa 1, se não, usa controle do ar

    //Movimento vertical
    if(IsKeyDown(KEY_D)) player->posicao.x += player->rapidez * controle * dt; //KeyDown é se a tecla está sendo pressionada
    if(IsKeyDown(KEY_A)) player->posicao.x -= player->rapidez * controle * dt;

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
    if(IsKeyPressed(KEY_SPACE) && player->estaNoChao){ //KeyPressed é quando a tecla foi pressionada uma vez
        player->velocidade.y = player->forcaPulo;
        player->estaNoChao = 0;
    }
    if(IsKeyPressed(KEY_SPACE) && player->velocidade.y < 0){
        //força do ar para quando está em queda
        player->velocidade.y *= 0.5f;
    }

    //Para ajudar na colisao
    player->estaNoChao = 0;
    //Aplicação do movimento
    player->posicao.x += player->velocidade.x * dt;
    //Atualização
    playerRect = GetPlayerRect(player);

    //Checagem da colisão com os retângulos
    if(CheckCollisionRecs(playerRect, ground)){

        if(player->velocidade.x > 0){
            //vindo da esquerda e bateu na parede a direita
            player->posicao.x = ground.x - playerRect.width;
        }
        else if(player->velocidade.x < 0){
            //vindo da direita e bateu na parede da esquerda
            player->posicao.x = ground.x + playerRect.width;
        }
        player->velocidade.x = 0;
    }

    //atualização da velocidade em y
    player->posicao.y += player->velocidade.y * dt;
    //atualiza o retângulo
    playerRect = GetPlayerRect(player);

    //checagem de coilisao com os retângulos
    if(CheckCollisionRecs(playerRect, ground)){
        if(player->velocidade.y > 0){
            //caindo
            player->posicao.y = ground.y - playerRect.height;
            player->velocidade.y = 0;
            player->estaNoChao = 1;
        }
        else if(player->velocidade.y < 0){
            //batendo a cabeça
            player->posicao.y = ground.y + playerRect.height;
            player->velocidade.y = 0;
        }
    }
}

//Desenhar o jogador
void DrawPlayer(Player player){
    DrawRectangle(player.posicao.x, player.posicao.y, 50, 50, RED);
}

//Pegar o retângulo do jogador
Rectangle GetPlayerRect(Player *player){
    return(Rectangle){
        player->posicao.x,
        player->posicao.y,
        50,
        50
    };
};