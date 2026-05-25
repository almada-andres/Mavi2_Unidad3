#pragma once

#include <box2d.h>
#include "raylib.h"

class Caja 
{
    private:
            b2Body* m_body;
            float m_ancho;
            float m_alto;
            Color m_color;

    public:
            Caja(b2World* world, float x, float y, float ancho, float alto);
            ~Caja() = default;

            void Draw();
};