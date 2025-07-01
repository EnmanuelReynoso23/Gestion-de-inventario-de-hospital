/**
 * @file main.cpp
 * @brief Main entry point for Medical Inventory GUI Application
 * @author Medical Inventory Team
 * @date 2025
 * 
 * Punto de entrada único para la aplicación de Inventario Médico
 * con interfaz gráfica moderna usando Windows API nativa.
 */

#include "../include/GuiMainFrame.hpp"
#include <windows.h>
#include <commctrl.h>
#include <iostream>
#include <stdexcept>

// Constantes de la aplicación
namespace MedicalInventory::App {
    constexpr const char* APP_NAME = "Clínica Vida Plena - Inventario Médico";
    constexpr const char* APP_VERSION = "v2.0";
    constexpr const char* APP_CLASS = "MedicalInventoryApp";
}

/**
 * @brief Función principal de la aplicación
 * @param hInstance Handle de la instancia de la aplicación
 * @param hPrevInstance Handle de la instancia anterior (obsoleto)
 * @param lpCmdLine Línea de comandos
 * @param nCmdShow Modo de visualización de la ventana
 * @return Código de salida de la aplicación
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Suprimir warnings de parámetros no utilizados
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    try {
        // Inicializar controles comunes de Windows
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES | ICC_STANDARD_CLASSES;
        
        if (!InitCommonControlsEx(&icex)) {
            throw std::runtime_error("Error al inicializar controles comunes de Windows");
        }

        // Crear y mostrar la ventana principal
        GuiMainFrame mainFrame;
        
        if (!mainFrame.Create(hInstance, MedicalInventory::App::APP_NAME, nCmdShow)) {
            throw std::runtime_error("Error al crear la ventana principal");
        }

        // Mostrar mensaje de bienvenida en la consola (solo para debug)
        #ifdef _DEBUG
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "=== " << MedicalInventory::App::APP_NAME << " " 
                  << MedicalInventory::App::APP_VERSION << " ===" << std::endl;
        std::cout << "Aplicación GUI inicializada correctamente." << std::endl;
        std::cout << "Interfaz gráfica cargada." << std::endl;
        #endif

        // Bucle principal de mensajes
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        #ifdef _DEBUG
        FreeConsole();
        #endif

        return static_cast<int>(msg.wParam);

    } catch (const std::exception& e) {
        // Mostrar error en ventana de mensaje
        std::string errorMsg = "Error fatal en la aplicación:\n\n";
        errorMsg += e.what();
        errorMsg += "\n\nLa aplicación se cerrará.";
        
        MessageBoxA(nullptr, errorMsg.c_str(), 
                   "Error - Inventario Médico", 
                   MB_ICONERROR | MB_OK);
        
        return -1;
    } catch (...) {
        // Error desconocido
        MessageBoxA(nullptr, 
                   "Error desconocido en la aplicación.\n\nLa aplicación se cerrará.", 
                   "Error Fatal - Inventario Médico", 
                   MB_ICONERROR | MB_OK);
        
        return -1;
    }
}

/**
 * @brief Función main alternativa para compatibilidad con compiladores
 * que esperan un main() estándar
 */
int main() {
    // Redirigir a WinMain con parámetros por defecto
    return WinMain(GetModuleHandle(nullptr), nullptr, GetCommandLineA(), SW_SHOWDEFAULT);
}
