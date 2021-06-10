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
    Texture2D texture = (LoadTexture("resources/enemy.png"));
    float rotation = 90;
    int health = 100;
};

struct TowerStruct {
    Vector2 origin = {0, 0};
    Rectangle sourceRec;
    Rectangle destRec;
    Texture2D texture = (LoadTexture("resources/tower.png"));
    float rotation = 0;
    const int radius = 300;
    bool canShoot = false;
};

struct BulletStruct {
    Vector2 origin = {0, 0};
    Rectangle sourceRec;
    Rectangle destRec;
    Texture2D texture = (LoadTexture("resources/bullet.png"));
    float rotation = 0;
    float speed = 5;
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
    BulletStruct bullet;

    Texture2D mapTexture = LoadTexture("resources/map.png");

    std::vector<int> PlatformPositionX = {40,  270, 270,  420,  500,
                                          730, 885, 1040, 1040, 805};
    std::vector<int> PlatformPositionY = {500, 580, 345, 115, 115,
                                          425, 650, 270, 190, 115};
    // Source rectangle (part of the texture to use for drawing)
    tower.sourceRec = {0.0F, 0.0F, (float)tower.texture.width,
                       (float)tower.texture.height};
    // Destination rectangle (screen rectangle where drawing part of
    // texture)
    tower.destRec = {(float)PlatformPositionX[0], (float)PlatformPositionY[0],
                     (float)tower.texture.width * 2.0F,
                     (float)tower.texture.height * 2.0F};
    tower.origin = {(float)tower.texture.width, (float)tower.texture.height};

    enemy.sourceRec = {0.0F, 0.0F, (float)enemy.texture.width,
                       (float)enemy.texture.height};
    enemy.destRec = {920, -20, (float)enemy.texture.width * 2.0F,
                     (float)enemy.texture.height * 2.0F};
    enemy.origin = {(float)enemy.texture.width, (float)enemy.texture.height};

    bullet.sourceRec = {0.0F, 0.0F, (float)bullet.texture.width,
                        (float)bullet.texture.height};
    bullet.destRec = {0, 0, (float)bullet.texture.width * 2.0F,
                      (float)bullet.texture.height * 2.0F};
    bullet.origin = {(float)bullet.texture.width, (float)bullet.texture.height};

    std::vector<int> waypointsX = {920, 615, 615, 155, 155, -20};
    std::vector<int> waypointsY = {540, 540, 235, 235, 605, 605};
    std::vector<int> enemyRotation = {90, 180, -90, 180, 90, 180};

    std::vector<int> waypointsCounter;
    std::vector<TowerStruct> Towers;
    std::vector<BulletStruct> Bullets;
    std::vector<float> BulletSpeedX;
    std::vector<float> BulletSpeedY;
    std::vector<int> shootTimer;
    std::vector<int> EnemieNumber;
    for (int i = 0; i < 10; i++) {
        EnemieNumber.push_back(0);
        Bullets.push_back(bullet);
        Bullets.at(i).destRec.x = PlatformPositionX.at(i);
        Bullets.at(i).destRec.y = PlatformPositionY.at(i);
        Towers.push_back(tower);
        BulletSpeedX.push_back(0);
        BulletSpeedY.push_back(0);
        shootTimer.push_back(120);
    }

    std::vector<EnemyStruct> Enemies;
    for (int i = 0; i < 5; i++) {
        enemy.destRec = {920, (-60) * (float)(i + 1),
                         (float)enemy.texture.width * 2.0F,
                         (float)enemy.texture.height * 2.0F};
        Enemies.push_back(enemy);
        waypointsCounter.push_back(0);
    }

    std::vector<bool> IsPlatformFree;
    for (int i = 0; i < Towers.size(); i++)
        IsPlatformFree.push_back(true);

    int coins = 1000;

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
                                   // Update

        coins++;

        // Передвижене противников
        //---------------------------------------------------------------------------------
        for (int i = 0; i < Enemies.size(); i++) {
            if (Enemies.at(i).destRec.x == waypointsX[waypointsCounter.at(i)] &&
                Enemies.at(i).destRec.y == waypointsY[waypointsCounter.at(i)] &&
                waypointsCounter.at(i) < waypointsX.size() - 1) {
                waypointsCounter.at(i)++;
                Enemies.at(i).rotation = enemyRotation[waypointsCounter.at(i)];
            }
            if (Enemies.at(i).destRec.x < waypointsX[waypointsCounter.at(i)])
                Enemies.at(i).destRec.x++;
            if (Enemies.at(i).destRec.x > waypointsX[waypointsCounter.at(i)])
                Enemies.at(i).destRec.x--;
            if (Enemies.at(i).destRec.y < waypointsY[waypointsCounter.at(i)])
                Enemies.at(i).destRec.y++;
            if (Enemies.at(i).destRec.y > waypointsY[waypointsCounter.at(i)])
                Enemies.at(i).destRec.y--;
        }
        //---------------------------------------------------------------------------------

        // Цикл проходит по башням
        //---------------------------------------------------------------------------------
        for (int i = 0; i < Towers.size() && !Enemies.empty(); i++) {
            if (!IsPlatformFree.at(i)) {
                shootTimer.at(i)--;
                if (Bullets.at(i).destRec.x != Towers.at(i).destRec.x ||
                    Bullets.at(i).destRec.y != Towers.at(i).destRec.y ||
                    Towers.at(i).canShoot) {
                    BulletSpeedX.at(i) =
                        5 *
                        (Enemies[EnemieNumber.at(i)].destRec.x -
                         Bullets.at(i).destRec.x) /
                        distance((int)Bullets.at(i).destRec.x,
                                 (int)Bullets.at(i).destRec.y,
                                 (int)Enemies[EnemieNumber.at(i)].destRec.x,
                                 (int)Enemies[EnemieNumber.at(i)].destRec.y);
                    BulletSpeedY.at(i) =
                        5 *
                        (Enemies[EnemieNumber.at(i)].destRec.y -
                         Bullets.at(i).destRec.y) /
                        distance((int)Bullets.at(i).destRec.x,
                                 (int)Bullets.at(i).destRec.y,
                                 (int)Enemies[EnemieNumber.at(i)].destRec.x,
                                 (int)Enemies[EnemieNumber.at(i)].destRec.y);
                    Bullets.at(i).destRec.x += BulletSpeedX.at(i);
                    Bullets.at(i).destRec.y += BulletSpeedY.at(i);
                    if (abs(Bullets.at(i).destRec.x -
                            Enemies[EnemieNumber.at(i)].destRec.x) <= 5 &&
                        abs(Bullets.at(i).destRec.y -
                            Enemies[EnemieNumber.at(i)].destRec.y) <= 5) {
                        Bullets.at(i).destRec.x = Towers.at(i).destRec.x;
                        Bullets.at(i).destRec.y = Towers.at(i).destRec.y;
                        Towers.at(i).canShoot = false;
                        Enemies[EnemieNumber.at(i)].health -= 20;
                        if (Enemies[EnemieNumber.at(i)].health <= 0) {
                            Enemies.erase(Enemies.begin() + EnemieNumber.at(i));
                            waypointsCounter.erase((waypointsCounter.begin() +
                                                    EnemieNumber.at(i)));
                            // if (Enemies.empty())
                            //     return 0;
                        }
                    }
                }
            }
            for (int j = 0; j < Enemies.size(); j++) {
                if (distance(
                        (int)Towers.at(i).destRec.x,
                        (int)Towers.at(i).destRec.y, (int)Enemies[j].destRec.x,
                        (int)Enemies[j].destRec.y) < (float)Towers[0].radius) {
                    Towers.at(i).rotation =
                        getRotation((int)Towers.at(i).destRec.x,
                                    (int)Towers.at(i).destRec.y,
                                    (int)Enemies[j].destRec.x,
                                    (int)Enemies[j].destRec.y) +
                        90;
                    if (Bullets.at(i).destRec.x == Towers.at(i).destRec.x &&
                        Bullets.at(i).destRec.y == Towers.at(i).destRec.y &&
                        shootTimer.at(i) <= 0) {
                        EnemieNumber.at(i) = j;
                        shootTimer.at(i) = 120;
                        Towers.at(i).canShoot = true;
                    }
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

            if (IsBuildingPossible(PlatformPositionX.at(i),
                                   PlatformPositionY.at(i), coins)) {
                coins -= 100;
                IsPlatformFree.at(i) = false;
            }

            if (!IsPlatformFree.at(i)) {
                Towers.at(i).destRec = {
                    (float)PlatformPositionX.at(i),
                    (float)PlatformPositionY.at(i),
                    (float)Towers.at(i).texture.width * 2.0F,
                    (float)Towers.at(i).texture.height * 2.0F};

                DrawTexturePro(Bullets.at(i).texture, Bullets.at(i).sourceRec,
                               Bullets.at(i).destRec, Bullets.at(i).origin,
                               (float)Bullets.at(i).rotation, WHITE);
                DrawTexturePro(Towers.at(i).texture, Towers.at(i).sourceRec,
                               Towers.at(i).destRec, Towers.at(i).origin,
                               (float)Towers.at(i).rotation, WHITE);
            }
        }

        for (int i = 0; i < Enemies.size(); i++)
            if (Enemies.at(i).destRec.x != -20)
                DrawTexturePro(Enemies.at(i).texture, enemy.sourceRec,
                               Enemies.at(i).destRec, Enemies.at(i).origin,
                               Enemies.at(i).rotation, WHITE);

        DrawText(TextFormat("Box position X: %03i", GetMouseX()), 10, 40, 20,
                 LIGHTGRAY);
        DrawText(TextFormat("Box position Y: %03i", GetMouseY()), 10, 80, 20,
                 LIGHTGRAY);

        EndDrawing();
        //---------------------------------------------------------------------------------
    }
    return 0;
}