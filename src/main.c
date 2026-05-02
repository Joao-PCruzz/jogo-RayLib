#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "map.h"

//função para atualizar câmera
    // Alterados os nomes dos parâmetros para minúsculo para evitar conflito com os #define em map.h
void UpdateCameraBounds(Camera2D *camera, Player player, int larguraTela, int alturaTela){
    //Camera seguindo o jogador
    camera->target.x = player.posicao.x;
    camera->target.y = player.posicao.y;

    //Definindo os limites permitidos pelo target/alvo
    float minX = 0;
    float minY = 0;
    //Largura total da tela, menos a largura da imagem dividido pelo zoom da câmera
    //Isso foi feito para garantir que câmera pare quando sua borda encostar na borda da tela, para não esperar o centro da câmera 
    float maxX = larguraTela * TILE_SIZE - (GetScreenWidth() /  camera->zoom);
    float maxY = alturaTela * TILE_SIZE - (GetScreenHeight() / camera->zoom);

    //Aplicar a função Clamp no alvo da câmera
    //A função clamp serve para retornar um valor entre 3, o valor passado, seu mínimo permitido ou seu máximo permitido
    //Retorna mínimo ou máximo quando o target da câmera excede os mínimos ou máximos
    camera->target.x = Clamp(camera->target.x, minX, maxX);
    camera->target.y = Clamp(camera->target.y, minY, maxY);
}   

int main(){
    //Tela em "HD"
    const int altura_tela = 720;
    const int largura_tela = 1280;

    InitWindow(largura_tela, altura_tela, "Primeiro jogo");
    SetTargetFPS(60);

    Player player; 
    InitPlayer(&player); // Inicializa o player antes de qualquer lógica

    //Câmera
    Camera2D camera = { 0 };
    camera.target = player.posicao;
    camera.offset = (Vector2){ largura_tela / 2.0f, altura_tela / 2.0f }; // Centraliza a câmera
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //Game Loop, parte mais importante do jogo
    while(!WindowShouldClose()){
        float dt = GetFrameTime(); // dt atualizado a cada frame

        UpdatePlayer(&player); //logica do player

        // Atualização da posição da câmera (suavização)
        UpdateCameraBounds(&camera, player, largura_tela, altura_tela);

        BeginDrawing(); //começa a desenhar
        ClearBackground(RAYWHITE);
        BeginMode2D(camera); //ativação da câmera

        DrawMapa(); //desenha o mapa
        DrawPlayer(player);  //renderização

        EndMode2D(); //desativação da câmera
        EndDrawing(); //fim do desenho
    };
    CloseWindow();
    return 0;
}