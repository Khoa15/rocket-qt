#include "Controller.h"
#include "Bullet.h"
Controller::Controller(QObject* parent): m_x(1462/2), m_y(922 - 50), xSpeed(10), minX(0), maxX(1512 - 50), bottomY(922-50)
{
    // if(m_start)
    // {
    //     connect(&time, &QTimer::timeout, this, &Controller::updateState);
    //     time.start(16); //60FPS

    //     connect(&move, &QTimer::timeout, this, &Controller::updateMovement);
    //     move.start(16);

    //     connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    //     startE.start(1000 + rand() % 2000); // 1 - 3 seconds
    // }
}

void Controller::startGame()
{
    setStartGame(true);
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16); //60FPS

    connect(&move, &QTimer::timeout, this, &Controller::updateMovement);
    move.start(16);

    connect(&startE, &QTimer::timeout, this, &Controller::createEnemy);
    startE.start(1000 + rand() % 2000); // 1 - 3 seconds
}

void Controller::moveLeft()
{
    moveDirection = -1;
    if(!move.isActive())
    {
        move.start();
    }
}

void Controller::moveRight()
{
    moveDirection = 1;
    if(!move.isActive())
    {
        move.start();
    }
}

void Controller::stopMovement()
{
    moveDirection = 0;
    move.stop();
}

QString Controller::showScore()
{
    return QString::number(score());
}

void Controller::restartGame()
{
    for(Enemy* enemy: enemyList)
    {
        delete enemy;
    }
    enemyList.clear();

    for(Bullet* bullet: bulletList)
    {
        delete bullet;
    }
    bulletList.clear();

    emit enemyChanged();
    emit bulletChanged();

    setX(1462/2);
    setY(922-50);

    emit xChanged();
    emit yChanged();
}

void Controller::applyThrust()
{
    ySpeed = maxThrust;
    if(m_y < bottomY / 2){
        ySpeed = 0;
    }
}

void Controller::fireBullet()
{
    Bullet* newBullet = new Bullet(this, this);
    newBullet->setX(m_x + 20);
    newBullet->setY(m_y);
    bulletList.append(newBullet);
    emit bulletChanged();

}

void Controller::createEnemy()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX(rand() % 1512);
    //newEnemy->setY(0);
    enemyList.append(newEnemy);
    startE.start(1000 + rand() % 2000); // 1 - 3 seconds
    emit enemyChanged();

}


// slots
void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y > bottomY)
    {
        m_y = bottomY;
    }
    checkCollision();
    emit yChanged();
}

void Controller::deleteBullet(Bullet *bullet)
{
    int index = bulletList.indexOf(bullet);
    if(index != -1)
    {
        // delete the memory
        delete bulletList[index];

        // delete the place inside list of the instance
        bulletList.removeAt(index);
        emit bulletChanged();
    }
}

void Controller::deleteEnemy(Enemy* enemy)
{
    int index = enemyList.indexOf(enemy);
    if(index != -1)
    {
        // delete the memory
        delete enemyList[index];

        // delete the place inside list of the instance
        enemyList.removeAt(index);
        emit enemyChanged();
    }
}

void Controller::updateMovement()
{
    if(moveDirection == -1 && m_x > minX)
    {
        setX(m_x - xSpeed);
    }
    if(moveDirection == 1 && m_x < maxX)
    {
        setX(m_x + xSpeed);
    }
    if(moveDirection == 0)
    {
        //setX(m_x);
    }
}



void Controller::checkCollision()
{
    for(int i = bulletList.size() - 1; i >= 0; i--)
    {
        Bullet* bullet = bulletList[i];

        double bulletLeft = bullet->x();
        double bulletRight = bullet->x() + 10;
        double bulletTop = bullet->y();
        double bulletBottom = bullet->y() + 30;
        for(int j = enemyList.size() - 1; j >= 0; j--)
        {
            Enemy* enemy = enemyList[j];



            double enemyLeft = enemy->x();
            double enemyRight = enemy->x() + 50;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y() + 50;


            if(
                bulletRight > enemyLeft && bulletLeft < enemyRight &&
                bulletTop < enemyBottom && bulletBottom > enemyTop
                )
            {
                deleteEnemy(enemy);
                deleteBullet(bullet);

                setScore(score() + 10);
                emit scoreChanged();

                break;
            }
        }
    }


    for(Enemy* enemy: enemyList)
    {
        if(enemy->y() > bottomY)
        {
            emit gameOver();
            return;
        }

        double enemyLeft = enemy->x();
        double enemyRight = enemy->x() + 50;
        double enemyTop = enemy->y();
        double enemyBottom = enemy->y() + 50;

        double playerLeft = m_x;
        double playerRight = m_x + 50;
        double playerTop = m_y;
        double playerBottom = m_y + 50;

        if(
            playerRight > enemyLeft && playerLeft < enemyRight &&
            playerTop < enemyBottom && playerBottom > enemyTop
            )
        {
            emit gameOver();

            break;
        }
    }
}




