#include "raylib.h"
#include "player.h"

int main(){
    SetTargetFPS(60);
    const int altura_tela = 600;
    const int largura_tela = 1200;

    InitWindow(largura_tela, altura_tela, "Primeiro jogo");
    //Game Loop
    while(!WindowShouldClose()){
        Player player;
        InitPlayer(&player);
        BeginDrawing();
        DrawPlayer(player);
        ClearBackground(RAYWHITE);
        DrawText("Primeiro", 190, 200, 20, BLACK);
        EndDrawing();
    };
    CloseWindow();
    return 0;
}