#include "Camera2D.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"

int main(void) {

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1076;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Tower Defence");

    Texture2D mapImg = LoadTexture("resources/map.png");

    int frameWidth = mapImg.width;
    int frameHeight = mapImg.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = {0.0f, 0.0f, (float)frameWidth, (float)frameHeight};

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = {screenWidth * 1.0f, screenHeight * 1.0f,
                         frameWidth * 1.0f, frameHeight * 1.0f};

    Vector2 origin = {(float)frameWidth, (float)frameHeight};

    int rotation = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
                                   // Update

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        DrawTexturePro(mapImg, sourceRec, destRec, origin, (float)rotation,
                       WHITE);

        EndDrawing();
        //---------------------------------------------------------------------------------
    }
    return 0;
}