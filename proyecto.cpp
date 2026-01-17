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

//Menu de actualizacion de Producto
void menuActualizacion(){
    cout<<"OPCIONES PARA ACTUALIZAR PRODUCTO\n";
    cout<<"1. Actualizar Nombre\n";
    cout<<"2. Actualizar Marca\n";
    cout<<"3. Actualizar Precio\n";
    cout<<"4. Actualizar Stock\n";
    cout<<"5. Salir\n";
    cout<<"Seleccione opcion para actualizar producto: ";
}


// Verifica si un ID ya existe
bool idExiste(int idBuscar) {
    ifstream archivo("repuestos.txt");
    string linea;
    int idArchivo;

    if (!archivo) return false;

    while (getline(archivo, linea)) {
        idArchivo = stoi(linea.substr(0, linea.find('|')));
        if (idArchivo == idBuscar) {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// CREATE
void agregarRepuesto() {
    Repuesto nuevo;
    ofstream archivo("repuestos.txt", ios::app);

    if (!archivo) {
        cout << "Error al abrir el archivo\n";
        return;
    }

    cout << "ID: ";
    cin >> nuevo.id;

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

// READ
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

// UPDATE
void actualizarRepuesto() {
    int idBuscado;
    bool encontrado = false;
    Repuesto producto;
    string temp;

    ifstream archivoOriginal("repuestos.txt");
    ofstream archivoTemporal("temporal.txt");

    if (!archivoOriginal) {
        cout << "Error: No se encontro el archivo de repuestos.\n";
        return;
    }

    cout << "Ingrese el ID del producto a actualizar: ";
    cin >> idBuscado;

    while (getline(archivoOriginal, temp, '|')) {
        producto.id = stoi(temp);

        getline(archivoOriginal, producto.nombre, '|');
        getline(archivoOriginal, producto.marca, '|');

        getline(archivoOriginal, temp, '|');
        producto.precio = stof(temp);

        getline(archivoOriginal, temp);
        producto.stock = stoi(temp);

        if (producto.id == idBuscado) {
            encontrado = true;
            cout << "\n--- Producto Encontrado ---\n";
            cout << "Nombre actual: " << producto.nombre << endl;
            cout << "Marca actual: "<< producto.marca <<endl;
            cout << "Precio Actual: $"<< producto.precio << endl;
            cout << "Stock Actual: "<< producto.stock <<endl;
            
            int opcionActualizar;
            //MENU INTERACTIVO PARA ACTUALIZAR
            do
            {
                menuActualizacion();
                cin>>opcionActualizar;
                cin.ignore();
                if (opcionActualizar == 1)
                {
                    string nuevoNombre;
                    cout<<"Ingrese nuevo nombre: ";
                    getline(cin, nuevoNombre);
                    cout<<"Se a actualizado el nombre "<<producto.nombre<<" a "<<nuevoNombre<<".\nVolviendo al menu.\n";
                    producto.nombre = nuevoNombre;
                } else if (opcionActualizar == 2)
                {
                    string nuevaMarca;
                    cout<<"Ingrese nueva marca: ";
                    getline(cin, nuevaMarca);
                    cout<<"Se a actualizado la marca "<<producto.marca<<" a "<<nuevaMarca<<".\nVolviendo al menu.\n";
                    producto.marca = nuevaMarca;
                } else if (opcionActualizar == 3)
                {
                    float nuevoPrecio;
                    cout<<"Ingrese el nuevo Precio: ";
                    cin>>nuevoPrecio;
                    cout<<"Se a actualizado el precio "<<producto.precio<<" a "<<nuevoPrecio<<".\nVolviendo al menu.\n";
                    producto.precio = nuevoPrecio;
                    cin.ignore();
                } else if (opcionActualizar == 4)
                {
                    int nuevoStock;
                    cout<<"Ingrese el nuevo Stock: ";
                    cin>>nuevoStock;
                    cout<<"Se a actualizado el stock "<<producto.stock<<" a "<<nuevoStock<<".\nVolviendo al menu.\n";
                    producto.stock = nuevoStock;
                    cin.ignore();
                } else if (opcionActualizar == 5)
                {
                    cout<<"SALIENDO DEL MENU DE ACTUALIZACION DE PRODUCTOS. VOLVIENDO AL MENU PRINCIPAL.\n";
                } else {
                    cout<<"Opcion Invalida. Ingresar la opcion requerida\n";
                }
            } while (opcionActualizar != 5);
            
            
            cin.ignore();
        }

        archivoTemporal << producto.id << "|"
                        << producto.nombre << "|"
                        << producto.marca << "|"
                        << producto.precio << "|"
                        << producto.stock << endl;
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (encontrado) {
        remove("repuestos.txt");
        rename("temporal.txt", "repuestos.txt");
        cout << "\n¡Producto actualizado con éxito!\n";
    } else {
        remove("temporal.txt");
        cout << "\nError: El ID no existe.\n";
    }
}

// DELETE -> nueva función
void eliminarRepuesto() {
    int idEliminar;
    bool eliminado = false;
    Repuesto producto;
    string temp;

    ifstream archivoOriginal("repuestos.txt");
    ofstream archivoTemporal("temporal.txt");

    if (!archivoOriginal) {
        cout << "Error: No se encontro el archivo de repuestos.\n";
        return;
    }

    cout << "Ingrese el ID del repuesto a eliminar: ";
    cin >> idEliminar;

    while (getline(archivoOriginal, temp, '|')) {
        producto.id = stoi(temp);

        getline(archivoOriginal, producto.nombre, '|');
        getline(archivoOriginal, producto.marca, '|');

        getline(archivoOriginal, temp, '|');
        producto.precio = stof(temp);

        getline(archivoOriginal, temp);
        producto.stock = stoi(temp);

        if (producto.id == idEliminar) {
            eliminado = true;
        } else {
            archivoTemporal << producto.id << "|"
                            << producto.nombre << "|"
                            << producto.marca << "|"
                            << producto.precio << "|"
                            << producto.stock << endl;
        }
    }

    archivoOriginal.close();
    archivoTemporal.close();

    if (eliminado) {
        remove("repuestos.txt");
        rename("temporal.txt", "repuestos.txt");
        cout << "\n¡Repuesto eliminado correctamente!\n";
    } else {
        remove("temporal.txt");
        cout << "\nError: El ID no existe.\n";
    }
}

int main() {
    system("chcp 65001 > nul");
    int opcion;

    do {
        cout << "\n1. Agregar repuesto";
        cout << "\n2. Listar repuestos";
        cout << "\n3. Actualizar repuesto";
        cout << "\n4. Eliminar repuesto";
        cout << "\n5. Salir";
        cout << "\nOpcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarRepuesto(); break;
            case 2: listarRepuestos(); break;
            case 3: actualizarRepuesto(); break;
            case 4: eliminarRepuesto(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida\n";
        }
    } while (opcion != 5);

    return 0;
}