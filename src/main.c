#include "raylib.h"
#include "player.h"

int main(){
    SetTargetFPS(60);
    //Tela em "HD"
    const int altura_tela = 720;
    const int largura_tela = 1280;

    InitWindow(largura_tela, altura_tela, "Primeiro jogo");
    Player player;
    InitPlayer(&player);
    //Game Loop
    while(!WindowShouldClose()){
        UpdatePlayer(&player); //logica do player
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawPlayer(player);  //renderização
        EndDrawing();
    };
    CloseWindow();
    return 0;
}