#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update(float dt) {
    if (m_Target != nullptr) {
        m_ViewBox.x = m_Target->x - WIDTH/2;
        m_ViewBox.y = m_Target->y - HEIGHT/2;


        // check offset

        if (m_ViewBox.x < 0) m_ViewBox.x = 0; 
        if (m_ViewBox.y < 0) m_ViewBox.y = 0;
        
        if (m_ViewBox.x > 4*WIDTH - m_ViewBox.w) {
            m_ViewBox.x = 4*WIDTH - m_ViewBox.w;
        }

        if (m_ViewBox.y > 2*HEIGHT - m_ViewBox.h) {
            m_ViewBox.y = 2*HEIGHT - m_ViewBox.h;
        }

        m_Position = Vector2d(m_ViewBox.x, m_ViewBox.y);
    }
}