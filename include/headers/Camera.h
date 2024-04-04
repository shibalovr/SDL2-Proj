#ifndef CAMERA_H
#define CAMERA_H

#include "Game.h"
#include "Point.h"

class Camera {
    public:
        void Update(float dt);
        inline static Camera* GetInstance() {
            if (s_Instance == nullptr) {
                s_Instance = new Camera();
            }
            return s_Instance;
        }

        inline SDL_Rect getViewBox() {return m_ViewBox;}
        inline Vector2d getPosition() {return m_Position;}
        inline void setTarget(Point* target) {m_Target = target;}

    private:
        Camera() {
            m_ViewBox = {0, 0, 1200, 800};
        };
        Point* m_Target; // the middle point of the frame
        Vector2d m_Position; // current start point of the camera;

        SDL_Rect m_ViewBox;

        static Camera* s_Instance;
};



#endif