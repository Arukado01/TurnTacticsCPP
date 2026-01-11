# Text-Based RPG - Dungeon Crawler

Un juego de rol basado en texto escrito en C++. Explora un calabozo, recolecta objetos, lucha contra enemigos y encuentra la salida.

## 📋 Descripción

Este es un juego de exploración de calabozos con mecánicas de combate por turnos. Tu objetivo es navegar a través de varias habitaciones, recolectar loot para mejorar tus estadísticas y derrotar enemigos en tu camino hacia la salida.

## ✨ Características

- **Exploración dinámica**: Navega a través de múltiples habitaciones interconectadas
- **Sistema de combate por turnos**: Lucha contra enemigos con mecánicas realistas de ataque y defensa
- **Recolección de loot**: Encuentra objetos para mejorar tu HP, ATK y DEF
- **Tres niveles de dificultad**: Easy, Normal y Hard con diferentes estadísticas iniciales
- **Sistema de retroceso**: Puedes retirarte a la habitación anterior durante una pelea (si existe)
- **Estadísticas progresivas**: Gana recompensas por derrotar enemigos

## 🎮 Cómo Jugar

### Objetivo
Encuentra la habitación de **SALIDA** y escapa del calabozo sin morir.

### Mecánicas
- **Exploración**: Elige hacia dónde moverte (Norte, Sur, Este, Oeste)
- **Combate**: Cuando encuentres un enemigo, puedes:
  - Atacar: Inflige daño basado en tu ATK (reducido por la DEF del enemigo)
  - Retirarte: Vuelve a la habitación anterior (si existe)
- **Defensa**: Tu DEF reduce el daño que recibes
- **Loot**: Algunos cuartos contienen objetos que mejoran tus estadísticas

### Consejos
- La defensa es importante para sobrevivir combates prolongados
- Recolecta todo el loot que encuentres antes de luchar
- El ataque más alto te ayuda a terminar combates más rápido

## 🛠️ Requisitos

- C++17 o superior
- CMake 3.10+
- Un compilador compatible (g++, clang, MSVC)

## 📦 Compilación y Ejecución

### Usando CMake

```bash
# Crear directorio de compilación
mkdir build
cd build

# Configurar y compilar
cmake ..
cmake --build .

# Ejecutar
./textBasedRPG
```

### Compilación manual

```bash
g++ -std=c++17 -o textBasedRPG \
    main.cpp Dungeon.cpp GameCharacter.cpp Item.cpp Player.cpp Room.cpp
./textBasedRPG
```

## 📁 Estructura del Proyecto

```
.
├── main.cpp                 # Punto de entrada y menú principal
├── Player.cpp/hpp          # Clase del jugador (extiende GameCharacter)
├── GameCharacter.cpp/hpp   # Clase base para jugador y enemigos
├── Dungeon.cpp/hpp         # Lógica principal del juego
├── Room.cpp/hpp            # Representación de habitaciones
├── Item.cpp/hpp            # Sistema de objetos
├── CMakeLists.txt          # Configuración de CMake
└── README.md               # Este archivo
```

## 🎯 Clases Principales

- **Player**: El personaje del jugador con inventario y seguimiento de habitaciones
- **GameCharacter**: Clase base con estadísticas (HP, ATK, DEF)
- **Room**: Representa una habitación con salidas, enemigos y loot
- **Dungeon**: Controla la lógica principal del juego y la interfaz de usuario
- **Item**: Objetos que mejoran estadísticas del jugador

## 🏗️ Arquitectura del Proyecto

```
+-------------------+
|      main.cpp     |
|-------------------|
| - Menú principal  |
| - Nombre jugador  |
| - Dificultad      |
| - Crea Player     |
| - Crea Dungeon    |
| - runDungeon()    |
+---------+---------+
          |
          v
+-------------------+
|     Dungeon       |  ← MOTOR DEL JUEGO
|-------------------|
| Player player     |
| array<Room> rooms |
|-------------------|
| runDungeon()      |
| enterRoom()       |
| fight()           |
| movement()        |
| readChoice()      |
+---------+---------+
          |
          | controla
          v
+-------------------+        +-------------------+
|       Room        |<------>|   GameCharacter  |
|-------------------|        |-------------------|
| id                |        | name              |
| isExit             |        | maxHealth         |
| items              |        | currentHealth     |
| enemies            |        | attack            |
| exits[N,E,S,W]     |        | defense           |
+---------+---------+        |-------------------|
          |                  | takeDamage()      |
          |                  | isDead()          |
          v                  +---------+---------+
+-------------------+                    ^
|      Item         |                    |
|-------------------|                    |
| name              |                    |
| +hp +atk +def     |                    |
+-------------------+                    |
                                         |
                              +----------+----------+
                              |       Player         |
                              |---------------------|
                              | inherits GameChar   |
                              | currentRoomId       |
                              | previousRoomId      |
                              | inventory           |
                              |---------------------|
                              | moveToRoom()        |
                              | grantReward()       |
                              +---------------------+
```

## 🔄 Flujo de Ejecución

```
Mostrar menú
 ├─ Help
 ├─ Quit
 └─ Start Game
       ├─ Leer nombre
       ├─ Elegir dificultad
       ├─ Crear Player
       └─ Crear Dungeon(player)
             └─ dungeon.runDungeon()
                   ├─ enterRoom()
                   │  ├─ handleRoomWithEnemies()
                   │  │  └─ fight()
                   │  ├─ handleRoomWithChest()
                   │  └─ handleMovement()
                   └─ (repite hasta EXIT o Game Over)
```

## 🎲 Dificultades

| Dificultad | HP Inicial | ATK | DEF |
|-----------|-----------|-----|-----|
| Easy      | 40        | 10  | 3   |
| Normal    | 30        | 8   | 2   |
| Hard      | 24        | 7   | 1   |

## � Recursos de Aprendizaje

- [Crear un Text-Based RPG con C++ - Alison.com](https://alison.com/course/build-a-text-based-rpg-with-c-plus-plus)

## 📝 Licencia

Proyecto de práctica personal.

## 👨‍💻 Autor

Creado como proyecto de aprendizaje en C++ desde el curso de Building a Game With C++ de la plataforma [Alison.com](https://alison.com/course/build-a-text-based-rpg-with-c-plus-plus).
