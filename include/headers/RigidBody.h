#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <Vector2d.h>

class RigidBody {
    public:
        RigidBody(){}

        // Force
        inline void ApplyForce(Vector2d F) {m_Force = F;}
        inline void ApplyForceX(float Fx) {m_Force.x = Fx;}
        inline void ApplyForceY(float Fy) {m_Force.y = Fy;}
        inline void UnSetForce() {m_Force = Vector2d(0,0);}

        // Friction
        inline void ApplyFriction(Vector2d Fr) {m_Friction = Fr;} 
        inline void UnSetFriction(){m_Friction = Vector2d(0,0);}

        void Update(float dt) {
            m_Acceleration.x = m_Force.x; // horizontal
            m_Acceleration.y = m_Force.y; // vertical
            m_Velocity = m_Acceleration*dt;
            m_Position = m_Velocity*dt;
        } 

        inline float getMass(){return m_Mass;}
        inline Vector2d getPosition(){return m_Position;}
        inline Vector2d getVelocity(){return m_Velocity;}
        inline Vector2d getAcceleration(){return m_Acceleration;}

    private:
        float m_Mass;
        float m_Gravity;

        Vector2d m_Force;
        Vector2d m_Friction;

        Vector2d m_Position;
        Vector2d m_Velocity;
        Vector2d m_Acceleration;
};

#endif