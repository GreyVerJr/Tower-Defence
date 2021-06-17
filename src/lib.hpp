#pragma once

/*!
Считает расстояние между двумя точками
\param x1 X координата первой точки
\param y1 Y координата первой точки
\param x2 X координата второй точки
\param y2 Y координата второй точки
*/
extern float distance(int x1, int y1, int x2, int y2);

/*!
Считает угол, на который нужно повернуть башню
\param towerX X координата башни
\param towerY Y координата башни
\param enemyX X координата противника, в которого целиться башня
\param enemyY Y координата противника, в которого целиться башня
*/
extern float getRotation(int towerX, int towerY, int enemyX, int enemyY);

/*!
Возвращает true, если курсор мыши нашодиться на платформе для башни и монет не
меньше 30
\param mouseX X координата курсора мыши
\param mouseY Y координата курсора мыши
\param PlatformPositionX X координата платформы
\param PlatformPositionY Y координата платвормы
\param coins Количество монет
*/
bool IsBuildingPossible(int mouseX, int mouseY, int PlatformPositionX,
                        int PlatformPositionY, int coins);
