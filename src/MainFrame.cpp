
#include "MainFrame.hpp"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fcntl.h>
#include <locale>
#include <io.h>

MainFrame::MainFrame() {
    // Constructor vacío o inicialización si es necesario
}

void MainFrame::ejecutar() {
    // Configurar consola para UTF-8 y salida wide
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    setlocale(LC_ALL, "");
    std::wcout << L"Bienvenido al Inventario Médico de la Clínica Vida Plena" << std::endl;
    int opcion = 0;
    do {
        std::wcout << L"\n===== MENÚ PRINCIPAL =====" << std::endl;
        std::wcout << L"1. Ingresar nuevo artículo" << std::endl;
        std::wcout << L"2. Mostrar equipos médicos agrupados" << std::endl;
        std::wcout << L"3. Mostrar artículos dañados por tipo" << std::endl;
        std::wcout << L"4. Calcular costo total por categoría" << std::endl;
        std::wcout << L"5. Calcular costo más alto y más bajo" << std::endl;
        std::wcout << L"6. Mostrar técnico con más equipos asignados" << std::endl;
        std::wcout << L"7. Calcular valor con plus para mobiliario" << std::endl;
        std::wcout << L"0. Salir" << std::endl;
        std::wcout << L"Seleccione una opción: ";
        std::wcin >> opcion;
        std::wcin.ignore();

        switch(opcion) {
            case 1:
                std::wcout << L"[Función no implementada] Ingresar nuevo artículo" << std::endl;
                break;
            case 2:
                std::wcout << L"[Función no implementada] Mostrar equipos médicos agrupados" << std::endl;
                break;
            case 3:
                std::wcout << L"[Función no implementada] Mostrar artículos dañados por tipo" << std::endl;
                break;
            case 4:
                std::wcout << L"[Función no implementada] Calcular costo total por categoría" << std::endl;
                break;
            case 5:
                std::wcout << L"[Función no implementada] Calcular costo más alto y más bajo" << std::endl;
                break;
            case 6:
                std::wcout << L"[Función no implementada] Mostrar técnico con más equipos asignados" << std::endl;
                break;
            case 7:
                std::wcout << L"[Función no implementada] Calcular valor con plus para mobiliario" << std::endl;
                break;
            case 0:
                std::wcout << L"Saliendo del programa..." << std::endl;
                break;
            default:
                std::wcout << L"Opción no válida. Intente de nuevo." << std::endl;
        }
    } while(opcion != 0);
    std::wcout << L"\nPresione ENTER para salir..." << std::endl;
    std::wcin.get();
}
