#ifndef REPRODUCTOR_HPP
#define REPRODUCTOR_HPP

#include "../Classes/Song.h"
#include "../Data_structure/Linkedlist.h"
#include "../Classes/Filemanager.h"
#include <string>

class Reproductor {
private:
    LinkedList<Song> fonoteca;
    LinkedList<Song>::Node* nodoActual;

    int estadoActual;     // 0 = Detenida, 1 = Reproduciendo, 2 = Pausada
    int modoRepeticion;   // 0 = Desactivado, 1 = Repetir una, 2 = Repetir todas
    bool modoAleatorio;

    std::string rutaArchivo;

    void limpiarPantalla();
    std::string obtenerTextoEstado() const; 

    void mostrarMenuPrincipal();
    void procesarEntradaPrincipal(const std::string& entrada);

    void mostrarSubmenuL();
    void mostrarSubmenuA();


    void alternarPlayPausa();
    void siguienteCancion();
    void anteriorCancion();
    void cambiarRepeticion();
    void agregarNuevaCancion();

public:
    Reproductor(std::string ruta);
    ~Reproductor();

    void iniciar();
};

#endif
