#pragma once

using Radians = float;
using Degrees = float;

const Radians kPi = 3.1415926f;

inline Degrees GetDegrees(const Radians radians)
{
    return radians * 180 / kPi;
}

inline sf::Vector2f GetUnitVector(Radians heading)
{
    return sf::Vector2f(cos(heading), sin(heading));
}

inline Radians GetAngle(const sf::Vector2f& vector)
{
    float x = vector.x == 0 ? 0.00000001f : vector.x;
    Radians angle = atan(vector.y / x);
    angle += vector.x >= 0 ? 0 : kPi;
    return angle;
}

inline float GetMagnitude(const sf::Vector2f& vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}