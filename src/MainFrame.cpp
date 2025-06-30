
#include "MainFrame.hpp"
#include <locale>

MainFrame::MainFrame() {
    // Constructor vacío o inicialización si es necesario
}

void MainFrame::ejecutar() {
    // Configurar locale para soporte de caracteres latinos
    setlocale(LC_ALL, "");
    std::cout << "Bienvenido al Inventario Medico de la Clinica Vida Plena" << std::endl;
    int opcion = 0;
    do {
        std::cout << "\n===== MENU PRINCIPAL =====" << std::endl;
        std::cout << "1. Ingresar nuevo articulo" << std::endl;
        std::cout << "2. Mostrar equipos medicos agrupados" << std::endl;
        std::cout << "3. Mostrar articulos danados por tipo" << std::endl;
        std::cout << "4. Calcular costo total por categoria" << std::endl;
        std::cout << "5. Calcular costo mas alto y mas bajo" << std::endl;
        std::cout << "6. Mostrar tecnico con mas equipos asignados" << std::endl;
        std::cout << "7. Calcular valor con plus para mobiliario" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1:
                std::cout << "[Funcion no implementada] Ingresar nuevo articulo" << std::endl;
                break;
            case 2:
                std::cout << "[Funcion no implementada] Mostrar equipos medicos agrupados" << std::endl;
                break;
            case 3:
                std::cout << "[Funcion no implementada] Mostrar articulos danados por tipo" << std::endl;
                break;
            case 4:
                std::cout << "[Funcion no implementada] Calcular costo total por categoria" << std::endl;
                break;
            case 5:
                std::cout << "[Funcion no implementada] Calcular costo mas alto y mas bajo" << std::endl;
                break;
            case 6:
                std::cout << "[Funcion no implementada] Mostrar tecnico con mas equipos asignados" << std::endl;
                break;
            case 7:
                std::cout << "[Funcion no implementada] Calcular valor con plus para mobiliario" << std::endl;
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
    } while(opcion != 0);
    std::cout << "\nPresione ENTER para salir..." << std::endl;
    std::cin.get();
}
