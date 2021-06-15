#pragma once

extern float distance(int x1, int y1, int x2, int y2);
extern float getRotation(int towerX, int towerY, int enemyX, int enemyY);
bool IsBuildingPossible(int mouseX, int mouseY, int PlatformPositionX,
                        int PlatformPositionY, int coins);
