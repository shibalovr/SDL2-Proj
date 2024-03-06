#include "Ninja.h"
#include "TextureManager.h"

Ninja::Ninja(Properties* props) : Character(props)
{
    // m_FrameCount = 8;
    // m_Row = 10;
    // m_aniSpeed = 40;
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->setProps(o_TextureId, 0, 6, 40);
}

void Ninja::Draw(){
    m_Animation->Draw(o_Transform->x, o_Transform->y, o_Width, o_Height);
}

void Ninja::Clean() {
    TextureManager::TM->clean();
}

void Ninja::Update() {
    m_RigidBody->Update(0.03);
    m_RigidBody->ApplyForceX(3);
    o_Transform->translateX(m_RigidBody->getPosition().x);
    o_Transform->translateY(m_RigidBody->getPosition().y);
    m_Animation->Update();

}