#include "raylib.h"
#include "player.h"

int main(){
    SetTargetFPS(60);
    //Tela em "HD"
    const int altura_tela = 720;
    const int largura_tela = 1280;
    
    Rectangle ground = {0, 400, 800, 50}; //criação da primeira plataforma do chão

    InitWindow(largura_tela, altura_tela, "Primeiro jogo");
    Player player; //inicialização do player
    InitPlayer(&player);

    //Game Loop, parte mais importante do jogo
    while(!WindowShouldClose()){
        UpdatePlayer(&player, ground); //logica do player

        BeginDrawing(); //começa a desenhar
        ClearBackground(RAYWHITE);

        DrawRectangleRec(ground, BROWN); //desenha o chão
        DrawPlayer(player);  //renderização

        EndDrawing();
    };
    CloseWindow();
    return 0;
}