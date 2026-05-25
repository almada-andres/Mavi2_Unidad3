#pragma once
#include "raylib.h"
#include <box2d.h>
#include "MecanismoCompuesto.h"
#include "Caja.h"

class Game 
{
    private:
            const int screenWidth = 1000;
            const int screenHeight = 600;

            b2World* world;

            b2Body* groundBody;
            MecanismoCompuesto* mecanismo;

            Caja* caja1;
            Caja* caja2;
            Caja* caja3;

            Color fondo = { 110, 100, 215, 255 };
            Color sueloColor = Fade(DARKGREEN, 0.7f);

            void InitPhysics();
            void Update();
            void Draw();

    public:
            Game();
            ~Game();
            void Run();
};