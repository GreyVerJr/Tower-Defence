#include "lib.hpp"
#include "cmath"

#define PI 3.14159265

float distance(int x1, int y1, int x2, int y2) {
    return (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float getRotation(int towerX, int towerY, int enemyX, int enemyY) {
    float tg = (float)(enemyY - towerY) / (float)(enemyX - towerX);
    float angle = atan(tg) * 180.0 / PI;
    if ((enemyY - towerY) == 0 && (enemyX - towerX) < 0)
        return 180;
    if ((enemyY - towerY) < 0 && (enemyX - towerX) < 0)
        return angle - 180;
    if ((enemyY - towerY) > 0 && (enemyX - towerX) < 0)
        return angle + 180;
    return angle;
}

bool IsBuildingPossible(int mouseX, int mouseY, int PlatformPositionX,
                        int PlatformPositionY, int coins) {
    return (mouseX > PlatformPositionX - 30 &&
            mouseX < PlatformPositionX + 30) &&
           (mouseY > PlatformPositionY - 30 &&
            mouseY < PlatformPositionY + 30) &&
           coins >= 30;
}
