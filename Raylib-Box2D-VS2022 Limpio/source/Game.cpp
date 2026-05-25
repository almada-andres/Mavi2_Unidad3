#include "Game.h"

Game::Game() 
{
    InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 2");
    SetTargetFPS(60);

    // Mundo físico
    b2Vec2 gravity(0.0f, 500.0f);
    world = new b2World(gravity);

    InitPhysics();

}

Game::~Game() 
{
    // Limpieza de punteros estaticos

    delete caja1;
    delete caja2;
    delete caja3;
    delete mecanismo;
    delete world;
    CloseWindow();
}

void Game::InitPhysics() 
{
    // -----------------------------
    // Suelo estático
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
    groundBody = world->CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
    groundBody->CreateFixture(&groundShape, 0.0f);

    // Instanciar el mecanismo compuesto
    mecanismo = new MecanismoCompuesto(world, groundBody);

    // Cajas individuales en posiciones fijas apiladas
    float cajaX = 680.0f;
    caja1 = new Caja(world, cajaX, 515.0f, 45.0f, 45.0f);
    caja2 = new Caja(world, cajaX, 470.0f, 45.0f, 45.0f);
    caja3 = new Caja(world, cajaX, 425.0f, 45.0f, 45.0f);
}

void Game::Update() 
{
    mecanismo->Update();

    // Avanzar simulación
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    world->Step(timeStep, velocityIterations, positionIterations);
}

void Game::Draw() 
{
    BeginDrawing();
    ClearBackground(fondo);

    // Suelo visual
    DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);

    // Dibujar mecanismo, lineas, joints, cuerpos
    mecanismo->Draw();

    // Cajas
    caja1->Draw();
    caja2->Draw();
    caja3->Draw();

    // Panel superior
    DrawRectangle(90, 40, 820, 60, Fade(BLACK, 0.2f));
    DrawText("Unidad 3 - Modelos y Algoritmos para Videojuegos II", 150, 55, 25, RAYWHITE);

    // Cuadro Izquierdo: Como operar la simulacion
    DrawRectangle(20, 130, 290, 110, Fade(BLACK, 0.6f));
    DrawRectangleLines(20, 130, 290, 110, RAYWHITE);

    DrawText("INSTRUCCIONES DE USO:", 35, 140, 12, GREEN);
    DrawText("Presione las teclas de flechas para iniciar.", 35, 160, 11, LIGHTGRAY);
    DrawText("[<-] FLECHA IZQUIERDA : Mover a la izquierda", 35, 185, 11, RAYWHITE);
    DrawText("[->] FLECHA DERECHA   : Mover a la derecha", 35, 205, 11, RAYWHITE);

    // Cuadro Derecho: Joints utilizados
    DrawRectangle(690, 130, 290, 110, Fade(BLACK, 0.6f));
    DrawRectangleLines(690, 130, 290, 110, RAYWHITE);

    DrawText("IDENTIFICACION DE JOINTS:", 705, 140, 12, ORANGE);
    DrawText("- Linea Gris: Prismatic Joint (Guia de riel)", 705, 165, 11, RAYWHITE);
    DrawText("- Punto Verde: Revolute Joint (Bisagra soga)", 705, 185, 11, RAYWHITE);
    DrawText("Objetivo: Balancear la soga y tirar las cajas.", 705, 210, 11, LIGHTGRAY);

    EndDrawing();
}

void Game::Run() 
{
    while (!WindowShouldClose()) 
    {
        Update();
        Draw();
    }
}