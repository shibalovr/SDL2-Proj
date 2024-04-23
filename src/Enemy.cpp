#include "Enemy.h"

Enemy::Enemy(Properties* props) : GameObject(props)
{
    x = 0;
    m_isDead = false;
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_HitBox = new HitBox();
    m_HitBox->SetBuffer(-24 * m_scalar,-24 * m_scalar, 48 * m_scalar, 48 * m_scalar);
    m_Animation->setProps(m_TextureId, 0, 4, 150);
}

void Enemy::Draw() {
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    TextureManager::GetInstance()->drawHitBox(m_HitBox);

}

void Enemy::Clean() {
    TextureManager::GetInstance()->clean();
}

void Enemy::Update(float dt) {
    m_RigidBody->UnSetForce();
    m_LastSafePosition.x = m_Transform->x;
    m_LastSafePosition.y = m_Transform->y;

    srand(time(nullptr));
    if (x >= m_MoveRangeX) {
        m_speedX = -m_speedX;
        x = 0;
        m_Animation->m_Flip = SDL_FLIP_HORIZONTAL;
    } else if (x <= -m_MoveRangeX) {
        m_speedX = -m_speedX;
        x = 0;
        m_Animation->m_Flip = SDL_FLIP_NONE;
    } 
    x += m_speedX;  
    int y = rand() % 10 - 5;
    m_RigidBody->ApplyForceX(m_speedX);
    m_RigidBody->ApplyForceY(y);
    m_RigidBody->Update(dt);

    m_Transform->translate(m_RigidBody->getPosition());
    m_HitBox->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);

    if (ColHandler::GetInstance()->CheckCollideMap(m_HitBox->Get(), 40, 40)) {
        m_Transform->x = m_LastSafePosition.x;
        m_Transform->y = m_LastSafePosition.y;
        if (m_Animation->m_Flip == SDL_FLIP_HORIZONTAL) {
            m_Animation->m_Flip = SDL_FLIP_NONE;
        } else {
            m_Animation->m_Flip = SDL_FLIP_HORIZONTAL;
        }
        m_speedX = -m_speedX;
        printf("Touched\n");
    }  
    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->x + m_Height/2;

    m_Animation->Update();
}