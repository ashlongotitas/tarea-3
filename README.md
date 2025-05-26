GraphQuest - Explorador de Laberintos con Grafo
GraphQuest es un juego de exploración basado en grafos donde el jugador debe navegar por un laberinto, recolectar ítems estratégicamente y alcanzar la salida antes de que se agote el tiempo. Cada decisión afecta el tiempo disponible y la capacidad de movimiento.

Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje de C, recomiendo descargar Visual Studio Code para usar el sistema fácilmente (link VSC https://code.visualstudio.com). Una vez dentro de Visual necesitarás instalar una extensión de C/C++ como C/C++ Extension Pack de Microsoft.

Requisitos previos: Además de tener instalado VSC con su extensión, en necesario tener instalado un compilador gcc, recomiendo descargar MinGW (link para Windows: https://sourceforge.net/projects/mingw/)

Pasos para compilar: comienza descargando y descomprimiendo el archivo (.zip). Luego ábrelo dentro de Visual Studio Code. Una vez abierto el archivo necesitarás compilarlo antes de ejecutarlo, para esto:

1. Abre el archivo principal (en este caso tarea3.c)
2. Selecciona "Terminal" ubicada en la esquina superior izquierda y luego "Nueva Terminal".
3. Una vez dentro de la terminal seleccione la flecha que esta al lado del "+" y apretar git bash.
4. Debes ingresar el siguiente comando: gcc -o tarea3 tarea3.c tdas/list.c tdas/graph.c tdas/extra.c -I. y despúes ./tarea3

Funcionando Correctamente

Cargar laberinto desde CSV: Construye un grafo donde cada nodo es un escenario con decisiones, ítems y conexiones.

Exploración interactiva: Menú de juego con opciones para recolectar/descartar ítems, avanzar en direcciones válidas y gestionar el tiempo.

Sistema de inventario: Cada ítem tiene peso y valor. El peso total afecta al tiempo que se descuenta.


Problemas Conocidos

Tiempo de carga: Laberintos muy grandes (ej: +100 nodos) pueden tardar unos segundos en cargar.

Caracteres especiales: Algunos nombres de ítems con símbolos o idiomas no latinos pueden mostrar errores de formato.


Mejoras Futuras
- Búsqueda de caminos óptimos: Sugerir rutas para maximizar puntaje.
- Guardar/recuperar partidas: Persistencia del estado del juego.
- Combate o puzzles: Añadir mecánicas avanzadas por escenario.

EJEMPLO DE USO: 
- Paso 1) Leer escenarios: antes de comenzar a jugar debes usar la opción 1 para que el programa lea los esccenarios y almacene sus datos.
- Paso 2) Iniciar Partida: Luego de haber leido los escenarios ya estarás listo para comenzar a jugar! verás todas las opciones disponibles al empezar:

![image](https://github.com/user-attachments/assets/0efc36cf-c2d0-4348-bc9c-021723f877e9)

- Paso 3) Moverse: Como recién empieza la partida solo podrás iniciar moviendote, se te mostrarán todas las direcciones disponibles que tienes en cada escenario, además despues de cada acción el programa mostrará tu estado actual: 

![image](https://github.com/user-attachments/assets/e4064509-ddeb-4f19-b588-fa7afb6056ac)

Recuerda que cada acción te restará 1 de tiempo (si te mueves con mucho peso, perderás más)

- Paso 4) Recoger Item(s): En cada escenario se te mostrarán los items disponibles, podrás elegir cual recoger.
- 
![image](https://github.com/user-attachments/assets/250d5a69-a94f-41ce-9adc-8193eb5e2832)

- Paso 5) Descartar Item: Si deseas descartar un objeto reuerda que igual te consumirá 1 de tiempo.

![image](https://github.com/user-attachments/assets/e1093719-1e24-4bd8-86e0-c0534db4dcf0)

- Paso 6) Reiniciar Partida: Si vez que perdiste mucho tiempo y deseas volver a empezar, con esta opción se te hará muy sencillo reiniciar las veces que quieras.

![image](https://github.com/user-attachments/assets/b417073b-6b24-4ccc-90e4-5bfba5478171)

- Paso 7) Salir: Cuando ya te aburras o logres ganar el juego, selecciona esta opcion para salir.



