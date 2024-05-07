#include "Camera.h"

Camera* Camera::s_Instance = nullptr;

void Camera::Update() {
    if (m_Target != nullptr) {
        int y = (m_Target->y / HEIGHT);
        m_ViewBox.y = y * HEIGHT;
        m_ViewBox.x = 0;
        // check offset

        if (m_ViewBox.x < 0) m_ViewBox.x = 0; 
        if (m_ViewBox.y < 0) m_ViewBox.y = 0;
        
        if (m_ViewBox.x > WIDTH) {
            m_ViewBox.x = WIDTH;
        }

        if (m_ViewBox.y > 5*HEIGHT) {
            m_ViewBox.y = 5*HEIGHT;
        }

        m_Position = Vector2d(m_ViewBox.x, m_ViewBox.y);
        // m_Position.log();
    }
}

