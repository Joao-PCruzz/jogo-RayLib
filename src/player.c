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
void UpdatePlayer(Player *player){
    float dt = GetFrameTime(); //linha para igualar o movimento em qualquer FPS
    Rectangle playerRect; //instanciação do retângulo do Player
    float controle = player->estaNoChao ? 1.0f : player->controleDoAr; //se o jogador está no chão, usa 1, se não, usa controle do ar
    player->estaNoChao = 1;

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

    //Para ajudar na colisao nos tiles do map
    player->estaNoChao = 0;
    if(IsKeyPressed(KEY_SPACE) && player->velocidade.y > 0){
        //Força do ar quando o player está em queda
         player->velocidade.y *= 0.5f;
    }
    //Aplicação do movimento
    player->posicao.x += player->velocidade.x * dt;
    //Atualização da colisao pelos tiles próximos do map (paredes)
    ResolveColisaoX(player);

    //atualização da velocidade em y
    player->posicao.y += player->velocidade.y * dt;
    //atualização da colisãp pelos tiles próximos o map (player)
    ResolveColisaoY(player);
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

//Pegar o tamanho do tile (telha)/ pedaço do mapa próximo
void GetTileRange(Rectangle rect, int *comecoX, int *fimX, int *comecoY, int *fimY){
    //Tamanho do tile x pela largura
    *comecoX = (int)(rect.x / TILE_SIZE);
    *fimX = (int)((rect.x + rect.width - 1) / TILE_SIZE);
    //Tamanho do tile y pela altura
    *comecoY = (int)(rect.y / TILE_SIZE);
    *fimY = (int)((rect.y + rect.height - 1) / TILE_SIZE);

    //proteção contra sair do mapa
    if(*comecoX < 0) *comecoX = 0;
    if(*comecoY < 0) *comecoY = 0;
    if(*fimX >= COLUNAS) *fimX = COLUNAS -1;
    if(*fimY >= LINHAS) *fimY = LINHAS -1;
}

void ResolveColisaoX(Player *player){
    //Pegar o retângulo do Player
    Rectangle rect = GetPlayerRect(player);

    int comecoX, fimX, comecoY, fimY;
    GetTileRange(rect, &comecoX, &fimX, &comecoY, &fimY);
    //y height e x width
    for(int y=comecoY; y <= fimY; y++){
        for(int x=comecoX; x <= fimX; x++){
            //Se o mapa tem elemento
            if(mapa[y][x] == 1){
                Rectangle tile = GetTileRect(x, y);

                if(CheckCollisionRecs(rect, tile)){
                    //Corrige a posição, ao encostar na parede volta
                    if(player->velocidade.x > 0){
                        player->posicao.x = tile.x - rect.width;
                    }
                    //Outra correção de posição, dessa vez pela esquerda
                    else if(player->velocidade.x < 0){
                        player->posicao.x = tile.x + tile.width;
                    }
                    //Reseta a velocidade
                    player->velocidade.x = 0;

                    //atuliza rect após correção 
                    rect = GetPlayerRect(player);
                }
            }
        }
    }

}
void ResolveColisaoY(Player *player){
    //Pegar o retângulo do Player
    Rectangle rect = GetPlayerRect(player);

    int comecoX, fimX, comecoY, fimY;
    GetTileRange(rect, &comecoX, &fimX, &comecoY, &fimY);
    //y height e x width
    for(int y=comecoY; y <=fimY; y++){
        for(int x=comecoX; x<=fimX; x++){

            if(mapa[y][x] == 1) {
                Rectangle tile = GetTileRect(x, y);

                if(CheckCollisionRecs(rect, tile)){
                    //colisão para o player (caindo) e parando no chão
                    if(player->velocidade.y > 0){
                        player->posicao.y = tile.y - rect.height;
                        player->velocidade.y = 0;
                        player->estaNoChao = 1;
                    }
                    //Player batendo a cabeça (subindo) e voltando para o chão
                    else if(player->velocidade.y < 0){
                        player->posicao.y = tile.y + rect.height;
                        player->velocidade.y = 0;
                    }
                    //Reseta a velocidade
                    player->velocidade.y = 0;
                    //atualiza o ratângulo do player
                    rect = GetPlayerRect(player);
                }
            }

        }
    }

}