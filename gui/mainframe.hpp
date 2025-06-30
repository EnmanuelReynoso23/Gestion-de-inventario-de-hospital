#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "../include/inventario.hpp"
#include <iostream>
#include <string>
#include <memory>

class MainFrame {
private:
    Inventario inventario;
    bool ejecutando;
    
    // Métodos privados para la interfaz
    void mostrarMenu();
    void procesarOpcion(int opcion);
    void limpiarPantalla();
    void pausar();
    
    // Métodos para cada funcionalidad
    void ingresarNuevoArticulo();
    void ingresarEquipoMedico();
    void ingresarMobiliarioClinico();
    
    void mostrarEquiposPorMarcaYArea();
    void mostrarArticulosDanados();
    void mostrarCostosPorCategoria();
    void mostrarCostosMinMax();
    void mostrarTecnicoConMasEquipos();
    void mostrarValoresConPlus();
    
    void mostrarTodosLosArticulos();
    void buscarArticuloPorCodigo();
    void mostrarEstadisticas();
    
    // Métodos auxiliares
    void mostrarTitulo();
    void mostrarSeparador();
    std::string obtenerEntrada(const std::string& prompt);
    int obtenerEnteroValido(const std::string& prompt, int min = 0, int max = 100);
    double obtenerDoubleValido(const std::string& prompt);
    
    // Validaciones
    bool validarCodigo(const std::string& codigo);
    bool validarFecha(const std::string& fecha);
    
public:
    MainFrame();
    ~MainFrame() = default;
    
    void ejecutar();
    void cargarDatosDePrueba(); // Para demostrar el funcionamiento
};

#endif // MAINFRAME_HPP
