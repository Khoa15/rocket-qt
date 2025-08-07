#include "Bullet.h"
#include "Controller.h"

Bullet::Bullet(Controller* controller, QObject* parent): m_x(1462/2), m_y(922 - 50), ySpeed(-10)
{
    connect(&time, &QTimer::timeout, this, &Bullet::updateBullet);
    time.start(16);

    connect(this, &Bullet::bulletDestroyed, controller, &Controller::deleteBullet);
}

void Bullet::updateBullet()
{
    setY(m_y + ySpeed);
    if(m_y < 0)
    {
        emit bulletDestroyed(this);
    }
}
