#pragma once

/**
 * Считает расстояние между двумя точками
 * x1 - x координата первой точки
 * y1 - y координата первой точки
 * x2 - x координата второй точки
 * y2 - y координата второй точки
 */
extern float distance(int x1, int y1, int x2, int y2);

/**
 * Считает угол, на который нужно повернуть башню
 * towerX - x координата башни
 * towerY - y координата башни
 * enemyX - x координата противника, в которого целиться башня
 * enemyY - y координата противника, в которого целиться башня
 */
extern float getRotation(int towerX, int towerY, int enemyX, int enemyY);

/**
 * Возвращает true, если курсор мыши нашодиться на платформе для башни
 * и монет не меньше 30
 * mouseX - x координата курсора мыши
 * mouseY - y координата курсора мыши
 * PlatformPositionX - x координата платформы
 * PlatformPositionY - y координата платвормы
 * coins - количество монет
 */
bool IsBuildingPossible(int mouseX, int mouseY, int PlatformPositionX,
                        int PlatformPositionY, int coins);
