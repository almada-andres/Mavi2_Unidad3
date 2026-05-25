#include "Caja.h"

Caja::Caja(b2World* world, float x, float y, float ancho, float alto) 
{
    m_ancho = ancho;
    m_alto = alto;

    m_color = 
    {
        (unsigned char)GetRandomValue(180, 240),
        (unsigned char)GetRandomValue(100, 150),
        30,
        255
    };

    // Definicion del cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    // Creacion del cuerpo
    m_body = world->CreateBody(&bodyDef);

    // Definicion de forma geometrica
    b2PolygonShape shape;
    shape.SetAsBox(ancho / 2.0f, alto / 2.0f);

    // Propiedades fisicas
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;

    // Vinculacion al cuerpo fisico
    m_body->CreateFixture(&fixtureDef);
}

void Caja::Draw() 
{
    // Posicion actual calculada por la fisica
    b2Vec2 pos = m_body->GetPosition();

    // Dibujar el rectangulo dinamico
    DrawRectanglePro({ pos.x, pos.y, m_ancho, m_alto },{ m_ancho / 2.0f, m_alto / 2.0f },
                       m_body->GetAngle() * RAD2DEG,m_color);

    // Dibujar el borde de la caja
    DrawRectangleLinesEx({ pos.x - m_ancho / 2.0f, pos.y - m_alto / 2.0f, m_ancho, m_alto },1,DARKBROWN);

}