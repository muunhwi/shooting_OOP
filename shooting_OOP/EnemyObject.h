#pragma once
#include "BaseObject.h"
#include "EnemyType.h"

class EnemyObject : public BaseObject
{
public:
    EnemyObject(int x, int y, const EnemyType& type);
    void update() override;
    void render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) override;
    void onCollision(BaseObject* obj) override;

private:
    void enemyMove();
    void createBullet();

private:
    EnemyType _type;
};