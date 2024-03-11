#include "Ninja.h"
#include "TextureManager.h"
#include "Input.h"


Ninja::Ninja(Properties* props) : Character(props)
{
    // m_FrameCount = 8;
    // m_Row = 10;
    // m_aniSpeed = 40;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->setProps(o_TextureId, 0, 4, 150);
}

void Ninja::Draw(){
    m_Animation->Draw(o_Transform->x, o_Transform->y, o_Width, o_Height);
}

void Ninja::Clean() {
    TextureManager::GetInstance()->clean();
}

void Ninja::Update() {

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
    m_RigidBody->UnSetForce();

    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        curDirection = DOWN;
        m_Animation->setProps("character_walk", 0, 4, 150);
        m_RigidBody->ApplyForceY(3);
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        curDirection = LEFT;
        m_Animation->setProps("character_walk", 1, 4, 150);
        m_RigidBody->ApplyForceX(-3);

    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        curDirection = UP;
        m_Animation->setProps("character_walk", 2, 4, 150);
        m_RigidBody->ApplyForceY(-3);

    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        curDirection = RIGHT;
        m_Animation->setProps("character_walk", 3, 4, 150);
        m_RigidBody->ApplyForceX(3);
    }

    m_RigidBody->Update(0.03);
    // m_RigidBody->ApplyForceX(3);
    o_Transform->translateX(m_RigidBody->getPosition().x);
    o_Transform->translateY(m_RigidBody->getPosition().y);
    m_Animation->Update();
}