#include "lib.hpp"
#include "cmath"

#define PI 3.14159265

// Считает расстояние между двумя точками
// x1 - x координата первой точки
// y1 - y координата первой точки
// x2 - x координата второй точки
// y2 - y координата второй точки
float distance(int x1, int y1, int x2, int y2) {
    return (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Считает угол, на который нужно повернуть башню
// towerX - x координата башни
// towerY - y координата башни
// enemyX - x координата противника, в которого целиться башня
// enemyY - y координата противника, в которого целиться башня
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

// Проверяет, можно ли поставить башню в данном месте
// mouseX - x координата мыши
// mouseY - y координата мыши
// PlatformPositionX - x координата платформы
// PlatformPositionY - y координата платвормы
// coins - количество монет
bool IsBuildingPossible(int mouseX, int mouseY, int PlatformPositionX,
                        int PlatformPositionY, int coins) {
    return (mouseX > PlatformPositionX - 30 &&
            mouseX < PlatformPositionX + 30) &&
           (mouseY > PlatformPositionY - 30 &&
            mouseY < PlatformPositionY + 30) &&
           coins >= 30;
}