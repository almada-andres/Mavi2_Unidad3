#include "MecanismoCompuesto.h"

MecanismoCompuesto::MecanismoCompuesto (b2World* world, b2Body* groundBody) 
{
    // -------------------------------------------------------------
    // Crear Cuerpo: Plataforma desplazable

    b2BodyDef platDef;
    platDef.type = b2_dynamicBody;
    
    platDef.position.Set(500.0f, 300.0f);
    m_plataforma = world->CreateBody(&platDef);

    b2PolygonShape platShape;
    platShape.SetAsBox(m_anchoPlataforma / 2.0f, m_altoPlataforma / 2.0f);

    b2FixtureDef platFixture;
    platFixture.shape = &platShape;
    platFixture.density = 3.0f;                             
    m_plataforma->CreateFixture(&platFixture);

    // -------------------------------------------------------------
    // Crear Cuerpo: Pendulo/Bola

    b2BodyDef pendDef;
    pendDef.type = b2_dynamicBody;
    pendDef.position.Set(500.0f, 480.0f); 
    m_pendulo = world->CreateBody(&pendDef);

    m_pendulo->SetAngularDamping(0.1f);

    b2CircleShape pendShape;
    pendShape.m_radius = m_radioPendulo;

    b2FixtureDef pendFixture;
    pendFixture.shape = &pendShape;
    pendFixture.density = 30.0f;
    pendFixture.restitution = 0.5f;
    pendFixture.friction = 0.2f;
    m_pendulo->CreateFixture(&pendFixture);

    // -------------------------------------------------------------
    // JOINT 1: Prismatic Joint
    // Restringe el movimiento a un solo eje horizontal.

    b2PrismaticJointDef prismaticDef;
    b2Vec2 axis(1.0f, 0.0f); // En eje X (Movimiento horizontal)

    prismaticDef.Initialize(groundBody, m_plataforma, m_plataforma->GetPosition(), axis);

    // Limites para que la plataforma no se salga de los bordes de la pantalla
    prismaticDef.enableLimit = true;
    prismaticDef.lowerTranslation = -350.0f; 
    prismaticDef.upperTranslation = 350.0f;  

    m_prismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&prismaticDef);

    // -------------------------------------------------------------
    // JOINT 2: Revolute Joint
    // Actua como una bisagra libre en el centro de la plataforma.

    b2RevoluteJointDef revoluteDef;
    // El punto de anclaje de la bisagra sera el centro de la plataforma movil
    revoluteDef.Initialize(m_plataforma, m_pendulo, m_plataforma->GetPosition());

    m_revoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&revoluteDef);
}

MecanismoCompuesto::~MecanismoCompuesto() 
{

}

void MecanismoCompuesto::Update() 
{
    float velocidadDestino = 0.0f;

    if (IsKeyDown(KEY_LEFT)) 
    {
        velocidadDestino = -450.0f;
    }
    else if (IsKeyDown(KEY_RIGHT)) 
    {
        velocidadDestino = 450.0f;
    }

    m_plataforma->SetLinearVelocity(b2Vec2(velocidadDestino, m_plataforma->GetLinearVelocity().y));
}

void MecanismoCompuesto::Draw() 
{
    // Obtener posiciones de los cuerpos
    b2Vec2 posPlat = m_plataforma->GetPosition();
    b2Vec2 posPend = m_pendulo->GetPosition();

    // Visualizacion del Prismatic Joint (Eje de riel guia)
    DrawLine(150, 300, 850, 300, GRAY);
    DrawText("Eje de Traslacion del Prismatic Joint", 160, 280, 10, GRAY);

    // Linea de conexion de la estructura
    DrawLine((int)posPlat.x, (int)posPlat.y, (int)posPend.x, (int)posPend.y, BLACK);
    // Punto de anclaje
    DrawCircle((int)posPlat.x, (int)posPlat.y, 5, RED);   

    // Plataforma
    DrawRectanglePro({ posPlat.x, posPlat.y, m_anchoPlataforma, m_altoPlataforma },
        { m_anchoPlataforma / 2.0f, m_altoPlataforma / 2.0f },m_plataforma->GetAngle() * RAD2DEG,DARKBLUE);

    // Visualizacion del Revolute Joint
    DrawCircle((int)posPlat.x, (int)posPlat.y, 6, GREEN);
    DrawCircleLines((int)posPlat.x, (int)posPlat.y, 10, LIME);

    // Pendulo
    DrawCircle((int)posPend.x, (int)posPend.y, m_radioPendulo, MAROON);
}