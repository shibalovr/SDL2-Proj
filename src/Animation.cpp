#include <Animation.h>
#include <TextureManager.h>

void Animation::Draw(float x, float y, int width, int height, int scalar) {
    TextureManager::GetInstance()->drawframe(m_TextureId, x, y, width, height, m_SpriteRow, m_SpriteFrame, scalar, m_Flip);

}

void Animation::setProps(std::string TextureId, int spriteRow, int frameCount, int anim_speed, SDL_RendererFlip flip) {
    m_TextureId = TextureId;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Flip = flip;
    m_AnimSpeed = anim_speed;
}

void Animation::Update() {
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;    
}