# Taller-1-Estructura-de-Datos


**Integrantes del equipo:**
* [Diego Seco]
* [David Rodriguez]

## Descripción del Proyecto
es un reproductor de música interactivo ejecutado mediante la consola de comandos, programado íntegramente en C++. Este proyecto aplica conceptos de Estructuras de Datos mediante la implementación manual de una Lista Doblemente Enlazada Genérica (Templates). El sistema gestiona estados de reproducción, carga persistente de pistas desde archivos de texto y cuenta con algoritmos personalizados para modos de reproducción aleatoria y repetición cíclica.

## Instrucciones de compilacion y ejecucion 

El código fuente está modularizado en carpetas (data_structures, classes, core). Para compilar el proyecto correctamente, se deben enlazar todos los archivos .cpp correspondientes.

Opción 1: Compilación manual por Consola (G++)

1. Abre una terminal de comandos en la carpeta raíz del proyecto.
2. Ejecuta el siguiente comando para compilar:
g++ main.cpp classes/Song.cpp classes/FileManager.cpp core/Reproductor.cpp -o reproductor.exe
   Ejecuta el programa:
   ```bash
   ./reproductor.exe

Opción 2: Compilación con CMake (CLion o otros IDES)

1. Abre la carpeta del proyecto en tu IDE.
2. Asegúrate de que el archivo CMakeLists.txt incluya todos los ejecutables.
3. Presiona el botón Build o Run.
4. Asegúrate de colocar el archivo music_source.txt en la misma carpeta donde se genera el ejecutable (ej. cmake-build-debug), o configura el Working Directory de tu IDE a la carpeta raíz del proyecto.

# Funcionamiento de la Aplicación

Al iniciar el programa, el sistema cargará automáticamente el archivo music_source.txt y presentará un menú interactivo en consola. La navegación se realiza ingresando la letra correspondiente a la acción deseada y presionando Enter.

Controles Principales:

W (Reproducir/Pausar): Alterna el estado de la pista actual.

E (Pista Siguiente): Avanza en la lista. Si el modo aleatorio está activo, salta a un nodo al azar de la lista enlazada.

Q (Pista Anterior): Retrocede al nodo previo en el historial de la lista doble.

S (Modo Aleatorio): Activa o desactiva la selección de saltos aleatorios (indicado con una S en pantalla).

R (Modo Repetición): Alterna cíclicamente entre Desactivado, Repetir Una (R1) y Repetir Todas (RA).

A (Ver Lista Actual): Abre un submenú que muestra las pistas restantes en cola, permitiendo realizar saltos específicos.

L (Listado de Canciones): Abre un submenú con el catálogo total, permitiendo agregar nuevas canciones al sistema y guardarlas en el archivo de texto.

X (Salir): Termina la ejecución de manera segura.

## Diagrama de Clases

```mermaid
classDiagram
    class LinkedList~T~ {
        -Node* head
        -Node* tail
        -int size
        +pushBack(T value)
        +pushFront(T value)
        +popFront() T
        +get(int index) T
        +getSize() int
        +isEmpty() bool
    }
    
    class Song {
        -int id
        -string title
        -string artist
        -string album
        -int year
        -int durationSeconds
        -string filePath
        +getFormattedDuration() string
        +toFileString(char) string
        +operator==(Song) bool
    }
    
    class FileManager {
        +detectDelimiter(string)$ char
        +parseSongLine(string, char, Song)$ bool
        +loadSongs(string, LinkedList~Song~)$ bool
        +appendSong(string, Song, char)$ bool
    }
    
    class Reproductor {
        -LinkedList~Song~ fonoteca
        -Node* nodoActual
        -int estadoActual
        -int modoRepeticion
        -bool modoAleatorio
        -string rutaArchivo
        +iniciar()
        -mostrarMenuPrincipal()
        -procesarEntradaPrincipal()
    }

    Reproductor *-- LinkedList : "Usa (Fonoteca)"
    LinkedList o-- Song : "Contiene datos de"
    Reproductor ..> FileManager : "Delega I/O a"
    FileManager ..> Song : "Instancia"
