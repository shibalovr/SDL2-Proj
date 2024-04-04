#ifndef vector2d_h
#define vector2d_h

#include <Game.h>

class Vector2d {
    public:
        float x, y;
        Vector2d(float X = 0, float Y = 0) {
            x = X;
            y = Y;
        }
        inline Vector2d operator+(const Vector2d& other) {
            return Vector2d(x + other.x, y+other.y);
        }

        inline Vector2d operator-(const Vector2d& other) {
            return Vector2d(x - other.x, y - other.y);
        }

        inline Vector2d operator*(const float scalar) {
            return Vector2d(x * scalar, y * scalar);
        }

        void log(std::string msg) {
            printf("%s (X Y): %f %f\n", msg, x, y);
        }

        inline Vector2d operator/(const float divider) {
            return Vector2d(x /divider , y * divider);
        }
    private:
};

#endif