#include "Enemy.h"

Enemy::Enemy(QObject* parent): m_x(rand() % 1512), m_y(-50), ySpeed(1)
{
    connect(&time, &QTimer::timeout, this, &Enemy::updateEnemy);
    time.start(50);
}

void Enemy::updateEnemy()
{
    setY(m_y + ySpeed);
}
