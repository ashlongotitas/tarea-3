# GraphQuest - Explorador de Laberintos con Grafo

**GraphQuest** es un juego de exploración basado en grafos donde el jugador debe navegar por un laberinto, recolectar ítems estratégicamente y alcanzar la salida antes de que se agote el tiempo. Cada decisión afecta el tiempo disponible y la capacidad de movimiento.

---

##  Cómo Compilar y Ejecutar

Este sistema ha sido desarrollado en lenguaje **C**. Se recomienda utilizar **Visual Studio Code** para facilitar su ejecución.

### Requisitos Previos

- Visual Studio Code: [Descargar VSC](https://code.visualstudio.com)
- Extensión de C/C++: C/C++ Extension Pack de Microsoft.
- Compilador `gcc`: Se recomienda instalar **MinGW**.  
   [Descargar MinGW (Windows)](https://sourceforge.net/projects/mingw/)

### Pasos para Compilar

1. Descarga y descomprime el archivo `.zip` del proyecto.
2. Ábrelo con Visual Studio Code.
3. Abre el archivo principal `tarea3.c`.
4. Abre la terminal: ve a `Terminal > Nueva Terminal`.
5. Cambia la terminal a **Git Bash** (flecha junto al `+`).
6. Compila con el siguiente comando:

```bash
gcc -o tarea3 tarea3.c tdas/list.c tdas/graph.c tdas/extra.c -I.
```

7. Ejecuta el programa:

```bash
./tarea3
```

---

##  Funcionamiento

- **Carga desde CSV:** Construye un grafo donde cada nodo representa un escenario.
- **Exploración interactiva:** Menú dinámico para moverse, recolectar/descartar ítems y gestionar tiempo.
- **Sistema de inventario:** Cada ítem tiene peso y valor; el peso influye en el tiempo que consumes.

---

##  Ejemplo de Uso

### Paso 1: Leer escenarios

Selecciona la opción **1** para cargar los escenarios desde un archivo CSV.

### Paso 2: Iniciar partida

Una vez cargado el laberinto, ¡puedes comenzar a jugar!

![image](https://github.com/user-attachments/assets/34475956-ee41-4aaf-9251-28259480a02f)

Despues de cada acción se mostrará tu estado actual:

![image](https://github.com/user-attachments/assets/54740014-fd1b-4d92-b513-2f0b1c8d2481)


### Paso 3: Moverse

Se mostrarán las **direcciones disponibles** para moverte desde tu escenario actual.  
> Cada movimiento consume 1 unidad de tiempo (más si llevas mucho peso).
![image](https://github.com/user-attachments/assets/c133ee2a-6813-43eb-bc8b-d0be3d1b9950)


### Paso 4: Recoger ítems

Se mostrarán los ítems disponibles para recoger.
![image](https://github.com/user-attachments/assets/078134a2-5485-4589-994f-a0e26f9ecd44)


### Paso 5: Descartar ítems
![image](https://github.com/user-attachments/assets/ad9a4cf5-6b8a-45cf-a244-6f3ae6359f1e)


Puedes eliminar objetos del inventario (también consume tiempo).

### Paso 6: Reiniciar partida

¿Perdiste mucho tiempo? Reinicia fácilmente desde el menú.

### Paso 7: Salir

Cuando termines o logres escapar del laberinto, selecciona esta opción.

---

##  Problemas Conocidos

- **Tiempo de carga alto:** En laberintos con más de 100 nodos.
- **Errores de formato:** Algunos caracteres especiales o idiomas no latinos pueden fallar.

---

##  Mejoras Futuras

-  Búsqueda de rutas óptimas para maximizar puntuación.
-  Guardado y recuperación de partidas.
-  Mecánicas avanzadas como combates o acertijos.

---

¡Explora, piensa estratégicamente y escapa del laberinto en **GraphQuest**!
