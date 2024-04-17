#include "Enemy.h"

Enemy::Enemy(Properties* props) : GameObject(props)
{
    m_isDead = false;
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_HitBox = new HitBox();
    m_HitBox->SetBuffer(-24 * m_scalar,-24 * m_scalar, 48 * m_scalar, 48 * m_scalar);
    m_Animation->setProps(m_TextureId, 0, 2, 150);
}

void Enemy::Draw() {
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    Vector2d cam = Camera::GetInstance()->getPosition();
    SDL_Rect box = m_HitBox->Get();
    box.x -= cam.x;
    box.y -= cam.y;
    printf("%d, %d, %d, %d\n", box.x, box.y, box.w, box.h);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &box);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

}

void Enemy::Clean() {
    TextureManager::GetInstance()->clean();
}

void Enemy::Update(float dt) {
    m_RigidBody->UnSetForce();
    m_LastSafePosition.x = m_Transform->x;
    m_LastSafePosition.y = m_Transform->y;

    srand(time(nullptr));

    int x = rand() % 10 - 5;
    int y = rand() % 10 - 5;
    // m_RigidBody->ApplyForceX(x);
    // m_RigidBody->ApplyForceY(y);
    // m_RigidBody->Update(dt);

    // m_Transform->translate(m_RigidBody->getPosition());
    m_HitBox->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);

    if (ColHandler::GetInstance()->CheckCollideMap(m_HitBox->Get(), 40, 40)) {
        m_Transform->x = m_LastSafePosition.x;
        m_Transform->y = m_LastSafePosition.y;
        printf("Touched\n");
    }  
    // printf("%d, %d, %d, %d\n", m_MovingArea.x, m_MovingArea.y, m_MovingArea.w, m_MovingArea.h);
    // printf("%d, %d, %d, %d\n", m_HitBox->Get().x, m_HitBox->Get().y, m_HitBox->Get().w, m_HitBox->Get().h);
    // if (ColHandler::GetInstance()->CheckCollide(m_MovingArea, m_HitBox->Get())) {
    //     m_Transform->x = m_LastSafePosition.x;
    //     m_Transform->y = m_LastSafePosition.y;
    //     printf("Out moving area\n");
    // }
    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->x + m_Height/2;

    m_Animation->Update();
}