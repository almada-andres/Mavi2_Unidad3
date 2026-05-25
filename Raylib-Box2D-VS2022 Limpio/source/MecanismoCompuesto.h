#pragma once
#include <box2d.h>
#include "raylib.h"

class MecanismoCompuesto 
{
    private:
            // Cuerpos
            b2Body* m_plataforma;
            b2Body* m_pendulo;

            // Joints utilizados
            b2PrismaticJoint* m_prismaticJoint;
            b2RevoluteJoint* m_revoluteJoint;

            // Dimensiones visuales (en píxeles para Raylib)
            const float m_anchoPlataforma = 80.0f;
            const float m_altoPlataforma = 20.0f;
            const float m_radioPendulo = 25.0f;

    public:
            MecanismoCompuesto(b2World* world, b2Body* groundBody);
            ~MecanismoCompuesto();

            void Update();
            void Draw();
};