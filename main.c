#include "raylib.h"

int main(){
    InitWindow(800, 600, "Primeiro Jogo");

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Primeiro", 190, 200, 20, BLACK);
        EndDrawing();
    };
    CloseWindow();
    return 0;
}