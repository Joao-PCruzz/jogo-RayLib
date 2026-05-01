#include "raylib.h"
#include "player.h"
#include "map.h"

int main(){
    SetTargetFPS(60);
    //Tela em "HD"
    const int altura_tela = 720;
    const int largura_tela = 1280;

    InitWindow(largura_tela, altura_tela, "Primeiro jogo");
    Player player; //inicialização do player
    InitPlayer(&player);

    //Game Loop, parte mais importante do jogo
    while(!WindowShouldClose()){
        UpdatePlayer(&player); //logica do player

        BeginDrawing(); //começa a desenhar
        ClearBackground(RAYWHITE);

        DrawMapa(); //desenha o mapa
        DrawPlayer(player);  //renderização

        EndDrawing();
    };
    CloseWindow();
    return 0;
}