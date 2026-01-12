#include <iostream>
#include <fstream>
using namespace std;

struct Repuesto {
    int id;
    string nombre;
    string marca;
    float precio;
    int stock;
};

// ---- VALIDAR SI ID YA EXISTE ----
bool idExiste(int idBuscar) {
    ifstream archivo("repuestos.txt");
    string linea;
    int idArchivo;

    if (!archivo) return false; // Si no existe el archivo, ningún ID existe aún

    while (getline(archivo, linea)) {
        // Extraer solo el ID hasta el primer '|'
        idArchivo = stoi(linea.substr(0, linea.find('|')));
        if (idArchivo == idBuscar) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

//CREATE
void agregarRepuesto() {
    Repuesto nuevo;
    ofstream archivo("repuestos.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo\n";
        return;
    }

    cout << "ID: ";
    cin >> nuevo.id;

    // ---- VALIDACIÓN DE ID ----
    if (idExiste(nuevo.id)) {
        cout << "Error: El ID ya existe. No se guardo el repuesto.\n";
        archivo.close();
        return;
    }

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevo.nombre);

    cout << "Marca: ";
    getline(cin, nuevo.marca);

    cout << "Precio: $";
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

    cout << "\n=== LISTA DE REPUESTOS ===\n";
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }

    archivo.close();
}

//	UPDATE
void actualizarRepuesto() {
    int idBuscado;
    bool encontrado = false;
    Repuesto producto;
    string stringTemporal; // Para leer datos numéricos temporalmente

    ifstream archivoOriginal("repuestos.txt");
    ofstream archivoTemporal("temporal.txt");

    if (!archivoOriginal) {
        cout << "Error: No se encontro el archivo de repuestos.\n";
        return;
    }

    cout << "Ingrese el ID del producto a actualizar: ";
    cin >> idBuscado;

    while (getline(archivoOriginal, stringTemporal, '|')) {
        producto.id = stoi(stringTemporal); // Convertimos el ID de texto a entero
        
        getline(archivoOriginal, producto.nombre, '|');
        getline(archivoOriginal, producto.marca, '|');
        
        getline(archivoOriginal, stringTemporal, '|');
        producto.precio = stod(stringTemporal);
        
        getline(archivoOriginal, stringTemporal, '|');
        producto.stock = stoi(stringTemporal);
        
        archivoOriginal.ignore(); // Saltamos el salto de línea (\n) al final de la fila

        if (producto.id == idBuscado) {
            encontrado = true;
            cout << "\n--- Producto Encontrado ---" << endl;
            cout << "Nombre actual: " << producto.nombre << endl;
            
            cout << "Nuevo Nombre: "; cin.ignore(); getline(cin, producto.nombre);
            cout << "Nueva Marca: "; getline(cin, producto.marca);
            cout << "Nuevo Precio: $"; cin >> producto.precio;
            cout << "Nuevo Stock: "; cin >> producto.stock;
        }

        // ESCRITURA EN EL ARCHIVO TEMPORAL
        archivoTemporal << producto.id << "|" << producto.nombre << "|" << producto.marca << "|" 
                        << producto.precio << "|" << producto.stock << "|" << endl;
    }

    archivoOriginal.close();
    archivoTemporal.close();

    // INTERCAMBIO DE NOMBRES DE ARCHIVOS
    if (encontrado) {
        remove("repuestos.txt");
        rename("temporal.txt", "repuestos.txt");
        cout << "\n¡Producto actualizado con éxito!\n";
    } else {
        remove("temporal.txt");
        cout << "\nError: El ID " << idBuscado << " no existe.\n";
    }
}

int main() {
    int opcion;

    do {
        cout << "\n1. Agregar repuesto";
        cout << "\n2. Listar repuestos";
        cout << "\n3. Actualizar repuestos";
        cout << "\n4. Salir";
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarRepuesto(); break;
            case 2: listarRepuestos(); break;
            case 3: actualizarRepuesto(); break;
            case 4: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 4);

    return 0;
}
