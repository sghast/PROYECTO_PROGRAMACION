#include <iostream>
#include <fstream>
using namespace std;

/*
- CRUD REPUESTOS DE AUTOS
- Se trabaja solo con archivos, sin vincular QT, para comprobar que funcione correctamente
*/

struct Repuesto {
    int id;
    string nombre;
    string marca;
    float precio;
    int stock;
};

void agregarRepuesto() {
    Repuesto nuevo;
    ofstream archivo("repuestos.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo\n";
        return;
    }

    cout << "ID: ";
    cin >> nuevo.id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Marca: ";
    getline(cin, nuevo.marca);

    cout << "Precio: ";
    cin >> nuevo.precio;

    cout << "Stock: ";
    cin >> nuevo.stock;

    archivo << nuevo.id << "|"
            << nuevo.nombre << "|"
            << nuevo.marca << "|"
            << nuevo.precio << "|"
            << nuevo.stock << endl;

    archivo.close();
    cout << "Repuesto guardado correctamente\n";
}

void listarRepuestos() {
    ifstream archivo("repuestos.txt");
    string linea;

    if (!archivo) {
        cout << "No existe el archivo\n";
        return;
    }

    cout << "\n  === LISTA DE REPUESTOS ===\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

int main() {
    int opcion;

    do {
        cout << "\n1. Agregar repuesto";
        cout << "\n2. Listar repuestos";
        cout << "\n3. Salir";
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarRepuesto(); break;
            case 2: listarRepuestos(); break;
            case 3: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 3);

    return 0;
}
