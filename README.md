Unidad 3 - Joints

Descripcion del Mecanismo Implementado
El proyecto consiste en una "grua" con pendulo de demolicion e interaccion con el Entorno. 
El mecanismo esta compuesto por un carro o plataforma movil que se desplaza de manera horizontal y fluida a traves de un riel guia. 
De su centro se suspende un cable tensor con una bola pesada (pendulo) que reacciona de forma dinamica a las aceleraciones y
frenados del carro por pura inercia fisica. 

El escenario incluye un entorno interactivo con una torre de cajas dinamicas apiladas sobre el suelo.
El objetivo del sistema es utilizar las fuerzas de balanceo del pendulo para impactar,
transferir energia y derribar la estructura de cajas, demostrando el comportamiento de cuerpos y la deteccion de colisiones.

Identificacion de los Joints Utilizados
Para construir este sistema articulado se utilizaron dos tipos de restricciones distintas:

1. `b2PrismaticJoint` (Joint de Traslacion): Conecta el suelo estatico del mundo con el carro movil.
    Restringe por completo la rotacion y el movimiento en el eje Y, obligando al cuerpo a desplazarse unicamente de forma lineal sobre
    el eje X. Cuenta con limites establecidos para evitar que la grua se salga de los margenes visuales de la pantalla.
2. `b2RevoluteJoint` (Joint de Rotacion): Conecta el centro de la plataforma movil con el cuerpo del pendulo.
    Funciona como una bisagra o pivote libre, permitiendo que la soga y la masa oscilen, respondiendo a la gravedad y a las fuerzas del teclado.

Controles de la Simulacion
* **Flecha Izquierda (`<-`):** Desplaza el carro de la grua hacia la izquierda.
* **Flecha Derecha (`->`):** Desplaza el carro de la grua hacia la derecha.
