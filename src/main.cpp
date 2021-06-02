#include "Camera2D.hpp"
#include "array"
#include "cmath"
#include "raylib-cpp.hpp"
#include "raylib.h"

#define PI 3.14159265

struct EnemyStruct {
    Vector2 origin = {0, 0};
    Rectangle sourceRec;
    Rectangle destRec;
    Texture2D texture;
    float rotation = 0;
    int health = 100;
};

struct TowerStruct {
    Vector2 origin = {0, 0};
    Rectangle sourceRec;
    Rectangle destRec;
    Texture2D texture;
    float rotation = 0;
    const int radius = 300;
};

float distance(int x1, int y1, int x2, int y2) {
    return (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool IsBuildingPossible(int PlatformPositionX, int PlatformPositionY,
                        int coins) {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true &&
           (GetMouseX() > PlatformPositionX - 30 &&
            GetMouseX() < PlatformPositionX + 30) &&
           (GetMouseY() > PlatformPositionY - 30 &&
            GetMouseY() < PlatformPositionY + 30) &&
           coins >= 100;
}

float getRotation(int towerX, int towerY, int enemyX, int enemyY) {
    float tg = (float)(enemyY - towerY) / (float)(enemyX - towerX);
    float angle = atan(tg) * 180.0 / PI;
    if ((enemyY - towerY) < 0 && (enemyX - towerX) < 0)
        return angle - 180;
    if ((enemyY - towerY) > 0 && (enemyX - towerX) < 0)
        return angle + 180;
    return angle;
}

int main(void) {

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1076;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Tower Defence");

    TowerStruct tower;
    EnemyStruct enemy;

    Texture2D mapTexture = LoadTexture("resources/map.png");
    tower.texture = (LoadTexture("resources/tower.png"));
    enemy.texture = (LoadTexture("resources/enemy.png"));

    std::vector<int> PlatformPositionX = {40,  270, 270,  420,  500,
                                          730, 885, 1040, 1040, 805};
    std::vector<int> PlatformPositionY = {500, 580, 345, 115, 115,
                                          425, 650, 270, 190, 115};
    tower.rotation = -90;
    // Source rectangle (part of the texture to use for drawing)
    tower.sourceRec = {0.0F, 0.0F, (float)tower.texture.width,
                       (float)tower.texture.height};
    // Destination rectangle (screen rectangle where drawing part of
    // texture)
    tower.destRec = {(float)PlatformPositionX[0], (float)PlatformPositionY[0],
                     (float)tower.texture.width * 2.0F,
                     (float)tower.texture.height * 2.0F};
    tower.origin = {(float)tower.texture.width, (float)tower.texture.height};

    enemy.rotation = 90;
    enemy.sourceRec = {0.0F, 0.0F, (float)enemy.texture.width,
                       (float)enemy.texture.height};
    enemy.destRec = {920, -20, (float)enemy.texture.width * 2.0F,
                     (float)enemy.texture.height * 2.0F};
    enemy.origin = {(float)enemy.texture.width, (float)enemy.texture.height};

    std::vector<int> waypointsX = {920, 615, 615, 155, 155, -20};
    std::vector<int> waypointsY = {540, 540, 235, 235, 605, 605};
    std::vector<int> enemyRotation = {90, 180, -90, 180, 90, 180};

    std::vector<int> waypointsCounter;
    std::vector<TowerStruct> Towers;
    for (int i = 0; i < 10; i++) {
        Towers.push_back(tower);
        waypointsCounter.push_back(0);
    }

    std::vector<EnemyStruct> Enemies;
    for (int i = 0; i < 5; i++) {
        enemy.destRec = {920, (-60) * (float)(i + 1),
                         (float)enemy.texture.width * 2.0F,
                         (float)enemy.texture.height * 2.0F};
        Enemies.push_back(enemy);
    }

    std::vector<bool> IsPlatformFree;
    for (int i = 0; i < 10; i++)
        IsPlatformFree.push_back(true);

    int coins = 0;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
                                   // Update

        coins++;
        // Передвижене противников
        //---------------------------------------------------------------------------------
        for (int i = 0; i < Enemies.size(); i++) {
            if (Enemies[i].destRec.x == waypointsX[waypointsCounter[i]] &&
                Enemies[i].destRec.y == waypointsY[waypointsCounter[i]] &&
                waypointsCounter[i] < waypointsX.size() - 1) {
                waypointsCounter[i]++;
                Enemies[i].rotation = enemyRotation[waypointsCounter[i]];
            }
            if (Enemies[i].destRec.x < waypointsX[waypointsCounter[i]])
                Enemies[i].destRec.x++;
            if (Enemies[i].destRec.x > waypointsX[waypointsCounter[i]])
                Enemies[i].destRec.x--;
            if (Enemies[i].destRec.y < waypointsY[waypointsCounter[i]])
                Enemies[i].destRec.y++;
            if (Enemies[i].destRec.y > waypointsY[waypointsCounter[i]])
                Enemies[i].destRec.y--;
        }
        //---------------------------------------------------------------------------------

        // Вращение башни
        //---------------------------------------------------------------------------------
        for (int i = 0; i < Towers.size(); i++) {
            for (int j = 0; j < Enemies.size(); j++) {
                if (distance((int)Towers[i].destRec.x, (int)Towers[i].destRec.y,
                             (int)Enemies[j].destRec.x,
                             (int)Enemies[j].destRec.y) <
                    (float)Towers[0].radius) {
                    Towers[i].rotation = getRotation(
                        (int)Towers[i].destRec.x, (int)Towers[i].destRec.y,
                        (int)Enemies[j].destRec.x, (int)Enemies[j].destRec.y);
                    break;
                }
            }
        }
        //---------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        DrawTexture(mapTexture, 0, 0, WHITE);

        for (int i = 0; i < Towers.size(); i++) {

            if (IsBuildingPossible(PlatformPositionX[i], PlatformPositionY[i],
                                   coins)) {
                coins -= 100;
                IsPlatformFree[i] = false;
            }

            if (!IsPlatformFree[i]) {
                Towers[i].destRec = {(float)PlatformPositionX[i],
                                     (float)PlatformPositionY[i],
                                     (float)Towers[i].texture.width * 2.0F,
                                     (float)Towers[i].texture.height * 2.0F};

                DrawTexturePro(Towers[i].texture, Towers[i].sourceRec,
                               Towers[i].destRec, Towers[i].origin,
                               (float)Towers[i].rotation, WHITE);
            }
        }

        for (int i = 0; i < Enemies.size(); i++)
            if (Enemies[i].destRec.x != -20)
                DrawTexturePro(Enemies[i].texture, enemy.sourceRec,
                               Enemies[i].destRec, Enemies[i].origin,
                               Enemies[i].rotation, WHITE);

        DrawText(TextFormat("Box position X: %03i", GetMouseX()), 10, 40, 20,
                 LIGHTGRAY);
        DrawText(TextFormat("Box position Y: %03i", GetMouseY()), 10, 80, 20,
                 LIGHTGRAY);

        EndDrawing();
        //---------------------------------------------------------------------------------
    }
    return 0;
}