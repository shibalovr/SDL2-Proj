#include "Character.h"
#include "TextureManager.h"
#include "Input.h"


Character::Character(Properties* props) : GameObject(props)
{
    m_JumpTime = 0;
    m_FallTime = 0;
    m_isFalling = false;    
    m_isJumping = false;
    m_DeadTime = DEAD_TIME;
    m_isDead = false;
    m_isCrouching = false;
    m_isBounce = false; 
    m_Flip = SDL_FLIP_NONE;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_RigidBody->SetGravity(30);
    m_TopHB = new HitBox();
    m_MidHB = new HitBox();
    m_BotHB = new HitBox();
    m_BotHB->SetBuffer(-10,-32,15,32); // Ground hitbox, wall hitbox
    m_TopHB->SetBuffer(-10,0,15,32); // Ceil hitbox
    m_MidHB->SetBuffer(0,-10, 0, 20);
    m_Animation->setProps(m_TextureId, 0, 1, 150);
    printf("Created character success!\n");
}

void Character::Draw(){
    m_Animation->Draw(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    TextureManager::GetInstance()->drawHitBox(m_TopHB);
    TextureManager::GetInstance()->drawHitBox(m_BotHB);
    TextureManager::GetInstance()->drawHitBox(m_MidHB);
}

void Character::Clean() {
    TextureManager::GetInstance()->clean();
}

void Character::Update(float dt) {
    // current states
    m_lastSafePosition.x = m_Transform->x;
    m_lastSafePosition.y = m_Transform->y;
    
    // unset force
    m_RigidBody->SetGravity(30);
    m_RigidBody->UnSetForce();
    m_Animation->setProps("idle", 0, 1, 150, m_Flip);


    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_isGrounded && !m_isDead) {
        m_isCrouching = true;
        m_isJumping = true;
        m_Animation->setProps("crouch", 0, 1, 150, m_Flip);
        m_JumpTime++;
        if (m_JumpTime >= MAX_JUMPTIME) {
            m_isCrouching = false;
        }
    } else {
        m_isCrouching = false;
    }

    if (m_isGrounded && !m_isJumping) {
        curDirection = NONE;
    }

    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A) && m_isCrouching && !m_isDead) {
        m_Flip = SDL_FLIP_HORIZONTAL;
        curDirection = LEFT;
    } else if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D) && m_isCrouching && !m_isDead) {
        m_Flip = SDL_FLIP_NONE;
        curDirection = RIGHT;
    }

    if (ColHandler::GetInstance()->CheckCollideMap(m_TopHB->Get(), 40, 40)) {
        m_isFalling = true;
        m_JumpTime = 0;
    }

    //Movement
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_A) && m_isGrounded && !m_isCrouching && !m_isDead) {
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_Animation->setProps("walk", 0, 3, 120, m_Flip);
        m_RigidBody->ApplyForceX(-100);
    }
    if (Input::getInstance()->GetKeyDown(SDL_SCANCODE_D) && m_isGrounded && !m_isCrouching && !m_isDead) {
        m_Flip = SDL_FLIP_NONE;
        m_Animation->setProps("walk", 0, 3, 120, m_Flip);
        m_RigidBody->ApplyForceX(100);
    }
    // fall
    if (m_isFalling) {
        if (ColHandler::GetInstance()->CheckCollideMap(m_MidHB->Get(), 40, 40)) {
            if (curDirection == LEFT) {
                curDirection = RIGHT;
            } else if (curDirection == RIGHT) {
                curDirection = LEFT;
            }
            m_isBounce = true;
        }
        m_FallTime++;
        m_FallForce = m_FallTime;
        if (m_FallTime > 30) {
            m_FallForce = MAX_FALL_FORCE;
        } 
        if (curDirection == LEFT) {
            m_RigidBody->ApplyForceX(-150);
        } else if (curDirection == RIGHT) {
            m_RigidBody->ApplyForceX(150);
        }
        m_RigidBody->ApplyForceY(FALL_FORCE*m_FallForce);
        m_Animation->setProps("jump_down", 0 , 1, 150, m_Flip);
    } else {
        m_FallTime = 0;
    }
    


    // jump
    if (m_isJumping && m_JumpTime > 0 && !m_isCrouching) {
        if (ColHandler::GetInstance()->CheckCollideMap(m_MidHB->Get(), 40, 40)) {
            if (curDirection == LEFT) {
                curDirection = RIGHT;
            } else if (curDirection == RIGHT) {
                curDirection = LEFT;
            }
            m_isBounce = true;
        }
        if (curDirection == LEFT) {
            m_RigidBody->ApplyForceX(-150);
        } else if (curDirection == RIGHT) {
            m_RigidBody->ApplyForceX(150);
        }
        
        m_RigidBody->ApplyForceY(-m_JumpTime*JUMP_FORCE);
        m_Animation->setProps("jump_up", 0, 1, 150, m_Flip);
        m_JumpTime -= 1;
    }

    if (m_isDead && m_DeadTime > 0) {
        m_Animation->setProps("dead", 0, 1, 150, m_Flip);
        m_DeadTime--;
    } else {
        m_DeadTime = DEAD_TIME;
        m_isDead = false;
    }

    if (m_JumpTime <= 0) {
        m_JumpTime = 0;
        m_isJumping = false;
        m_isFalling = true;
    }
    if (m_isBounce == true) {
        m_Animation->setProps("bounce", 0, 1, 150, m_Flip);
    }

    // mov on X
    m_RigidBody->Update(dt);    
    m_Transform->translateX(m_RigidBody->getPosition().x);
    m_TopHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    m_BotHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    m_MidHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    if (ColHandler::GetInstance()->CheckCollideMap(m_BotHB->Get(), 40, 40)) {
        m_Transform->x = m_lastSafePosition.x;
    }

    // mov on Y
    m_RigidBody->Update(dt);    
    m_Transform->translateY(m_RigidBody->getPosition().y);
    m_TopHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    m_BotHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);
    m_MidHB->Set(m_Transform->x, m_Transform->y, m_Width, m_Height, m_scalar);

    if (ColHandler::GetInstance()->CheckCollideMap(m_BotHB->Get(), 40, 40)) {
        m_Transform->y = m_lastSafePosition.y;
        m_isGrounded = true;
        m_isFalling = false;
        if (m_FallTime >= 70) {
            m_Animation->setProps("dead", 1, 1, 1, m_Flip);
            m_isDead = true;
        }
        m_isBounce = false;
    } else {
        m_isGrounded = false;
    }
    // m_Origin->Log();
    m_Origin->x = m_Transform->x + m_Width/2;
    m_Origin->y = m_Transform->y + m_Height/2;  

    m_Animation->Update();
}