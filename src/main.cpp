#include "Camera2D.hpp"
#include "array"
#include "raylib-cpp.hpp"
#include "raylib.h"

struct Img {
    Vector2 position;
    Vector2 origin;
    Rectangle sourceRec;
    Rectangle destRec;
    Texture2D texture;
    float rotation = 0;
};

int main(void) {

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1076;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Tower Defence");

    Img map;
    Img tower;

    map.texture = LoadTexture("resources/map.png");
    tower.texture = LoadTexture("resources/tower.png");

    int frameWidth = map.texture.width;
    int frameHeight = map.texture.height;

    map.rotation = 0;
    tower.rotation = 0;

    // Source rectangle (part of the texture to use for drawing)
    tower.sourceRec = {0.0f, 0.0f, (float)tower.texture.width,
                       (float)tower.texture.height};
    // Destination rectangle (screen rectangle where drawing part of texture)
    tower.destRec = {40, 500, (float)tower.texture.width * 2.0f,
                     (float)tower.texture.height * 2.0f};
    tower.origin = {(float)tower.texture.width, (float)tower.texture.height};

    std::array<float, 10> PlatformPositionX = {40,  270, 270,  420,  500,
                                               730, 885, 1040, 1040, 805};
    std::array<float, 10> PlatformPositionY = {500, 580, 345, 115, 115,
                                               425, 650, 270, 190, 115};

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
                                   // Update

        tower.rotation++;
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        DrawTexture(map.texture, 0, 0, WHITE);

        tower.destRec = {PlatformPositionX[0], PlatformPositionY[0],
                         (float)tower.texture.width * 2.0f,
                         (float)tower.texture.height * 2.0f};

        DrawTexturePro(tower.texture, tower.sourceRec, tower.destRec,
                       tower.origin, (float)tower.rotation, WHITE);

        EndDrawing();
        //---------------------------------------------------------------------------------
    }
    return 0;
}