#include "Ninja.h"
#include "TextureManager.h"
#include "Input.h"


Ninja::Ninja(Properties* props) : Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    // m_HitBox = new hitBox();
    m_Animation->setProps(m_TextureId, 0, 4, 150);
    printf("Created character success!\n");
}

void Ninja::Draw(){
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height);
    Vector2d cam = Camera::GetInstance()->getPosition();
    SDL_Rect box = m_HitBox;
    box.x -= cam.x;
    box.y -= cam.y;

    if (m_Transform == nullptr) {
        printf("m_transform error!\n");
    } else {
        // m_Transform->log();
    }
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(Game::renderer, &box);
    printf("%d, %d\n", box.x, box.y);
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}

void Ninja::Clean() {
    TextureManager::GetInstance()->clean();
}

void Ninja::Update(float dt) {
    // current states
    switch (curDirection)
    {
    case DOWN:
        m_Animation->setProps("character_idle", 0, 4, 150);
        break;
    case LEFT:
        m_Animation->setProps("character_idle", 1, 4, 150);
        break;
    case UP:
        m_Animation->setProps("character_idle", 2, 4, 150);
        break;
    case RIGHT:
        m_Animation->setProps("character_idle", 3, 4, 150);
        break;
    }
    // unset force
    m_RigidBody->UnSetForce();

    //Movement
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        curDirection = DOWN;
        m_Animation->setProps("character_walk", 0, 4, 150);
        m_RigidBody->ApplyForceY(100);
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        curDirection = LEFT;
        m_Animation->setProps("character_walk", 1, 4, 150);
        m_RigidBody->ApplyForceX(-100);

    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        curDirection = UP;
        m_Animation->setProps("character_walk", 2, 4, 150);
        m_RigidBody->ApplyForceY(-100);

    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        curDirection = RIGHT;
        m_Animation->setProps("character_walk", 3, 4, 150);
        m_RigidBody->ApplyForceX(100);
    }


    // Roll
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
        switch (curDirection)
        {
        case DOWN:
            m_Animation->setProps("character_roll", 0, 4, 150);
            m_RigidBody->ApplyForceY(300);
            break;
        case LEFT:
            m_Animation->setProps("character_roll", 1, 4, 150);
            m_RigidBody->ApplyForceX(-300);
            break;
        case UP:
            m_Animation->setProps("character_roll", 2, 4, 150);
            m_RigidBody->ApplyForceY(-300);
            break;
        case RIGHT:
            m_Animation->setProps("character_roll", 3, 4, 150);
            m_RigidBody->ApplyForceX(300);
            break;
        }
    }
    //attack
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_J)) {
        switch (curDirection)
        {
        case DOWN:
            m_Animation->setProps("character_attack", 0, 4, 150);
            break;
        case LEFT:
            m_Animation->setProps("character_attack", 1, 4, 150);
            break;
        case UP:
            m_Animation->setProps("character_attack", 2, 4, 150);
            break;
        case RIGHT:
            m_Animation->setProps("character_attack", 3, 4, 150);
            break;
        }
    }

    // Block
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_K)) {
        switch (curDirection)
        {
        case DOWN:
            m_Animation->setProps("character_block", 0, 1, 150);
            break;
        case LEFT:
            m_Animation->setProps("character_block", 1, 1, 150);
            break;
        case UP:
            m_Animation->setProps("character_block", 2, 1, 150);
            break;
        case RIGHT:
            m_Animation->setProps("character_block", 3, 1, 50);
            break;
        }
    }
    



    m_RigidBody->Update(dt);

    m_HitBox.x = m_Transform->x;
    m_HitBox.y = m_Transform->y;

    m_Transform->translateX(m_RigidBody->getPosition().x);
    m_Transform->translateY(m_RigidBody->getPosition().y);

    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Height/2;

    

    m_Animation->Update();
}