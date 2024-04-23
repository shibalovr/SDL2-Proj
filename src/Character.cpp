#include "Character.h"
#include "TextureManager.h"
#include "Input.h"


Character::Character(Properties* props) : GameObject(props)
{
    m_Hp = 50;
    m_Mp = 100;
    m_isAttack = false;
    m_isRoll = false;
    m_RollTime = ROLL_TIME;
    m_AttackTime = ATTACK_TIME;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_HitBox = new HitBox();
    m_AttackHitBox = new HitBox();
    m_AttackHitBox->SetBuffer(0,0,0,0);
    m_HitBox->SetBuffer(-32 * m_scalar,-24 * m_scalar, 64 * m_scalar, 48 * m_scalar); // wall hit box
    m_Animation->setProps(m_TextureId, 0, 4, 150);
    printf("Created character success!\n");
}

void Character::Draw(){
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    TextureManager::GetInstance()->drawHitBox(m_HitBox);
}

void Character::Clean() {
    TextureManager::GetInstance()->clean();
}

void Character::Update(float dt) {
    m_isWalk = false;

    m_RigidBody->UnSetForce();
    // current states
    m_lastSafePosition.x = m_Transform->x;
    m_lastSafePosition.y = m_Transform->y;
    
    switch (curDirection)
    {
    case DOWN:
        m_Animation->setProps("idle", 0, 4, 150);
        break;
    case LEFT:
        m_Animation->setProps("idle", 1, 4, 150);
        break;
    case UP:
        m_Animation->setProps("idle", 2, 4, 150);
        break;
    case RIGHT:
        m_Animation->setProps("idle", 3, 4, 150);
        break;
    }
    // unset force

    //Movement
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_S)) {
        curDirection = DOWN;
        m_Animation->setProps("walk", 0, 4, 150);
        m_RigidBody->ApplyForceY(dt*WALKFORCE);
        m_isWalk = true;
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        curDirection = LEFT;
        m_Animation->setProps("walk", 1, 4, 150);
        m_RigidBody->ApplyForceX(-dt*WALKFORCE);
        m_isWalk = true;
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_W)) {
        curDirection = UP;
        m_Animation->setProps("walk", 2, 4, 150);
        m_RigidBody->ApplyForceY(-dt*WALKFORCE);
        m_isWalk = true;
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        curDirection = RIGHT;
        m_Animation->setProps("walk", 3, 4, 150);
        m_RigidBody->ApplyForceX(dt*WALKFORCE);
        m_isWalk = true;
    }


    // Roll
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_SPACE)|| (m_isRoll && m_RollTime > 0)) {
        switch (curDirection)
        {
        case DOWN:
            m_Animation->setProps("roll", 0, 4, 150);
            m_RigidBody->ApplyForceY(dt*ROLLFORCE);
            break;
        case LEFT:
            m_Animation->setProps("roll", 1, 4, 150);
            m_RigidBody->ApplyForceX(-dt*ROLLFORCE);
            break;
        case UP:
            m_Animation->setProps("roll", 2, 4, 150);
            m_RigidBody->ApplyForceY(-dt*ROLLFORCE);
            break;
        case RIGHT:
            m_Animation->setProps("roll", 3, 4, 150);
            m_RigidBody->ApplyForceX(dt*ROLLFORCE);
            break;
        }
        m_RollTime -= dt;
        m_isRoll = true;
    }
    //Attack
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_J) || (m_isAttack && m_AttackTime > 0)) {
        switch (curDirection)
        {
        case DOWN:
            m_Animation->setProps("attack", 0, 4, 150);
            break;
        case LEFT:
            m_Animation->setProps("attack", 1, 4, 150);
            break;
        case UP:
            m_Animation->setProps("attack", 2, 4, 150);
            break;
        case RIGHT:
            m_Animation->setProps("attack", 3, 4, 150);
            break;
        }
        m_isAttack = true;
        m_AttackTime -= dt;
    }

    if (!m_isAttack || m_AttackTime <= 0) {
        m_isAttack = false;
        m_AttackTime = ATTACK_TIME;
    }
    if (!m_isRoll || m_RollTime <= 0) {
        m_isRoll = false;
        m_RollTime = ROLL_TIME;
    }


    m_RigidBody->Update(dt);    
    m_Transform->translateX(m_RigidBody->getPosition().x);
    m_Transform->translateY(m_RigidBody->getPosition().y);
    m_HitBox->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    if (ColHandler::GetInstance()->CheckCollideMap(m_HitBox->Get(), 40, 40)) {
        m_Transform->x = m_lastSafePosition.x;
        m_Transform->y = m_lastSafePosition.y;
    }

    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Height/2;  

    m_Animation->Update();
}