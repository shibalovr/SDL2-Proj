#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Vector2d.h>

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody {
    public:
        RigidBody(){
            m_Mass = UNI_MASS;
            m_Gravity = GRAVITY; 
        }
        inline void SetMass(float mass) {m_Mass = mass;};
        inline void SetGravity(float gravity) {
            m_Gravity = gravity;
        }

        // Force
        inline void ApplyForce(Vector2d F) {m_Force = F;}
        inline void ApplyForceX(float Fx) {m_Force.x = Fx;}
        inline void ApplyForceY(float Fy) {m_Force.y = Fy;}
        inline void UnSetForce() {m_Force = Vector2d(0,0);}

        void Update(float dt) {
            m_Acceleration.x = m_Force.x / m_Mass; // horizontal
            m_Acceleration.y = m_Gravity + m_Force.y/m_Mass; // vertical
            m_Velocity = m_Acceleration*dt;
            m_Position = m_Velocity*dt;
        } 

        inline Vector2d getPosition(){return m_Position;}
        inline Vector2d getVelocity(){return m_Velocity;}
        inline Vector2d getAcceleration(){return m_Acceleration;}
    private:
        float m_Mass;
        float m_Gravity;
        Vector2d m_Force;

        Vector2d m_Position;
        Vector2d m_Velocity;
        Vector2d m_Acceleration;
};

#endif