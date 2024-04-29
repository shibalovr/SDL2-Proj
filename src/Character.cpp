#include "Character.h"
#include "TextureManager.h"
#include "Input.h"


Character::Character(Properties* props) : GameObject(props)
{
    m_JumpTime = 0;
    m_isJumping = false;
    m_isCrouching = false;
    m_Flip = SDL_FLIP_NONE;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_HitBox = new HitBox();
    m_HitBox->SetBuffer(0,0,0,0); // wall hit box
    m_Animation->setProps(m_TextureId, 0, 1, 150);
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
    // current states
    m_lastSafePosition.x = m_Transform->x;
    m_lastSafePosition.y = m_Transform->y;
    
    // unset force
    m_RigidBody->UnSetForce();
    m_Animation->setProps("idle", 0, 1, 150, m_Flip);

    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_isGrounded) {
        m_isCrouching = true;
        m_isJumping = true;
        m_Animation->setProps("crouch", 0, 1, 150, m_Flip);
        m_JumpTime += dt;
    } else {
        m_isCrouching = false;
    }
    if (m_isGrounded && !m_isJumping) {
        curDirection = NONE;
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A) && m_isCrouching) {
        m_Flip = SDL_FLIP_HORIZONTAL;
        curDirection = LEFT;
    } else if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D) && m_isCrouching) {
        m_Flip = SDL_FLIP_NONE;
        curDirection = RIGHT;
    }

    //Movement
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A) && m_isGrounded && !m_isCrouching) {
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_Animation->setProps("walk", 0, 3, 150, m_Flip);
        m_RigidBody->ApplyForceX(-100);
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D) && m_isGrounded && !m_isCrouching) {
        m_Flip = SDL_FLIP_NONE;
        m_Animation->setProps("walk", 0, 3, 150, m_Flip);
        m_RigidBody->ApplyForceX(100);
    }

    // jump
    if (m_isJumping && m_JumpTime > 0 && !m_isCrouching) {
        if (curDirection == LEFT) {
            m_RigidBody->ApplyForceX(-30);
        } else if (curDirection == RIGHT) {
            m_RigidBody->ApplyForceX(30);
        }
        m_isGrounded = false;
        m_RigidBody->ApplyForceY(-50);
        m_Animation->setProps("jump_up", 0, 1, 150, m_Flip);
        m_JumpTime -= dt;
    }

    if (m_JumpTime <= 0) {
        m_JumpTime = 0;
        m_isJumping = false;
    }
    


    // mov on X
    m_RigidBody->Update(dt);    
    m_Transform->translateX(m_RigidBody->getPosition().x);
    m_HitBox->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    if (ColHandler::GetInstance()->CheckCollideMap(m_HitBox->Get(), 40, 40)) {
        m_Transform->x = m_lastSafePosition.x;
    }

    // mov on Y
    m_RigidBody->Update(dt);    
    m_Transform->translateY(m_RigidBody->getPosition().y);
    m_HitBox->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    if (ColHandler::GetInstance()->CheckCollideMap(m_HitBox->Get(), 40, 40)) {
        m_Transform->y = m_lastSafePosition.y;
        m_isGrounded = true;
    } else {
        m_isGrounded = false;
    }
    // m_Origin->Log();
    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Height/2;  

    m_Animation->Update();
}