#include "Reproductor.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

Reproductor::Reproductor(string ruta) {
    rutaArchivo = ruta;
    nodoActual = nullptr;
    estadoActual = 0;
    modoRepeticion = 0;
    modoAleatorio = false;
    srand(time(0));
}

Reproductor::~Reproductor() {}

void Reproductor::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string Reproductor::obtenerTextoEstado() const {
    string estadoTxt;
    if (estadoActual == 1) estadoTxt = "Reproduciendo";
    else if (estadoActual == 2) estadoTxt = "En pausa";
    else estadoTxt = "Reproduccion Detenida";

    string mods = "";
    if (modoAleatorio) mods += "S";
    if (modoRepeticion == 1) mods += (mods.empty() ? "R1" : "-R1");
    if (modoRepeticion == 2) mods += (mods.empty() ? "RA" : "-RA");

    if (!mods.empty()) {
        estadoTxt += " (" + mods + ")";
    }
    return estadoTxt;
}

void Reproductor::iniciar() {
    FileManager::loadSongs(rutaArchivo, fonoteca);

    if (!fonoteca.isEmpty()) {
        nodoActual = fonoteca.getHead();
    }

    bool ejecutando = true;
    string entrada;

    while (ejecutando) {
        limpiarPantalla();
        mostrarMenuPrincipal();

        cout << "Ingrese Opcion: ";
        getline(cin, entrada);

        if (entrada.empty()) continue;

        char comando = toupper(entrada[0]);
        if (comando == 'X') {
            ejecutando = false;
        } else {
            procesarEntradaPrincipal(entrada);
        }
    }
}

void Reproductor::mostrarMenuPrincipal() {
    if (nodoActual != nullptr) {
        Song actual = nodoActual->data;
        cout << obtenerTextoEstado() << ": " << actual.getTitle() << "\n";
        cout << "Artista: " << actual.getArtist() << "\n";
        cout << "Album: " << actual.getAlbum() << " [" << actual.getYear() << "]\n\n";
    } else {
        cout << obtenerTextoEstado() << "\n\n";
    }

    cout << "Opciones:\n";
    cout << "W - Reproducir/Pausar\n";
    cout << "Q - Pista Anterior\n";
    cout << "E - Pista Siguiente\n";
    cout << "S - Activar/Desactivar modo aleatorio\n";
    cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    cout << "A - Ver lista de reproduccion actual\n";
    cout << "L - Listado de canciones\n";
    cout << "X - Salir\n";
}

void Reproductor::procesarEntradaPrincipal(const string& entrada) {
    char comando = toupper(entrada[0]);

    switch (comando) {
        case 'W': alternarPlayPausa(); break;
        case 'E': siguienteCancion(); break;
        case 'Q': anteriorCancion(); break;
        case 'R': cambiarRepeticion(); break;
        case 'S': modoAleatorio = !modoAleatorio; break;
        case 'A': mostrarSubmenuA(); break;
        case 'L': mostrarSubmenuL(); break;
    }
}

void Reproductor::mostrarSubmenuA() {
    bool enSubmenu = true;
    string entrada;

    while (enSubmenu) {
        limpiarPantalla();

        string tagActual = "Actual";
        string mods = "";
        if (modoAleatorio) mods += "S";
        if (modoRepeticion == 1) mods += (mods.empty() ? "R1" : "-R1");
        if (modoRepeticion == 2) mods += (mods.empty() ? "RA" : "-RA");
        if (!mods.empty()) tagActual += " (" + mods + ")";

        if (nodoActual != nullptr) {
            cout << tagActual << ": " << nodoActual->data.getTitle() << " - " << nodoActual->data.getArtist() << "\n\n";
        } else {
            cout << tagActual << ": Ninguna\n\n";
        }

        cout << "Lista de reproduccion actual:\n";


        if (nodoActual != nullptr && nodoActual->next != nullptr) {
            auto temp = nodoActual->next;
            int pos = 1;
            while (temp != nullptr) {
                cout << pos << ". " << temp->data.getTitle() << " - " << temp->data.getArtist() << "\n";
                temp = temp->next;
                pos++;
            }
        } else {
            cout << "Vacia\n";
        }

        cout << "\nOpciones:\n";
        cout << "S<num> - Saltar a la cancion seleccionada\n";
        cout << "V - Volver al menu principal\n";
        cout << "> ";
        getline(cin, entrada);

        if (entrada.empty()) continue;
        if (toupper(entrada[0]) == 'V') enSubmenu = false;

    }
}

void Reproductor::mostrarSubmenuL() {
    bool enSubmenu = true;
    string entrada;

    while (enSubmenu) {
        limpiarPantalla();

        string tagActual = "Actual";
        string mods = "";
        if (modoAleatorio) mods += "S";
        if (modoRepeticion == 1) mods += (mods.empty() ? "R1" : "-R1");
        if (modoRepeticion == 2) mods += (mods.empty() ? "RA" : "-RA");
        if (!mods.empty()) tagActual += " (" + mods + ")";

        if (nodoActual != nullptr) {
            cout << tagActual << ": " << nodoActual->data.getTitle() << " - " << nodoActual->data.getArtist() << "\n\n";
        } else {
            cout << tagActual << ": Ninguna\n\n";
        }

        cout << "Canciones registradas:\n";
        if (!fonoteca.isEmpty()) {
            auto temp = fonoteca.getHead();
            while (temp != nullptr) {
                cout << temp->data.getId() << ". " << temp->data.getTitle() << " - " << temp->data.getArtist() << "\n";
                temp = temp->next;
            }
        } else {
            cout << "No hay canciones registradas.\n";
        }

        cout << "\nOpciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion seleccionada al final de la lista de reproduccion actual\n";
        cout << "N - Agregar cancion al registro de canciones\n";
        cout << "D<num> - Eliminar cancion seleccionada\n";
        cout << "V - Volver al menu principal\n";
        cout << "> ";

        getline(cin, entrada);
        if (entrada.empty()) continue;

        char comando = toupper(entrada[0]);
        if (comando == 'V') enSubmenu = false;
        else if (comando == 'N') {
            agregarNuevaCancion();
        }
        
    }
}

void Reproductor::alternarPlayPausa() {
    if (fonoteca.isEmpty()) return;
    if (estadoActual == 1) estadoActual = 2; 
    else estadoActual = 1;
}

void Reproductor::siguienteCancion() {
    if (nodoActual == nullptr) return;

    if (modoRepeticion == 1) {
        estadoActual = 1;
        return;
    }

    if (modoAleatorio && fonoteca.getSize() > 1) {
        int saltoRandom = rand() % fonoteca.getSize();
        nodoActual = fonoteca.getHead();
        for (int i = 0; i < saltoRandom; i++) nodoActual = nodoActual->next;
        estadoActual = 1;
        return;
    }

    if (nodoActual->next != nullptr) {
        nodoActual = nodoActual->next;
        estadoActual = 1;
    } else {
        if (modoRepeticion == 2) {
            nodoActual = fonoteca.getHead();
            estadoActual = 1;
        } else {
            estadoActual = 0;
        }
    }
}

void Reproductor::anteriorCancion() {
    if (nodoActual != nullptr && nodoActual->prev != nullptr) {
        nodoActual = nodoActual->prev;
        estadoActual = 1;
    }
}

void Reproductor::cambiarRepeticion() {
    modoRepeticion++;
    if (modoRepeticion > 2) modoRepeticion = 0;
}

void Reproductor::agregarNuevaCancion() {
    limpiarPantalla();
    string titulo, artista, album, ruta;
    int anio, duracion, idNuevo;

    cout << "--- Agregar Cancion al Registro ---\n";
    idNuevo = fonoteca.getSize() + 1;

    cout << "Titulo: "; getline(cin, titulo);
    cout << "Artista: "; getline(cin, artista);
    cout << "Album: "; getline(cin, album);
    cout << "Anio: "; cin >> anio;
    cout << "Duracion (segundos): "; cin >> duracion;
    cin.ignore();
    cout << "Ruta del archivo (.mp3/.wav): "; getline(cin, ruta);

    Song nueva(idNuevo, titulo, artista, album, anio, duracion, ruta);
    fonoteca.pushBack(nueva);
    FileManager::appendSong(rutaArchivo, nueva, ',');

    if (nodoActual == nullptr) nodoActual = fonoteca.getHead();
}
