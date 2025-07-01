
#include "../include/mobiliario_clinico.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Definición de constantes estáticas
const double MobiliarioClinico::PLUS_CONSULTA = 200.0;
const double MobiliarioClinico::PLUS_EMERGENCIA = 300.0;
const double MobiliarioClinico::PLUS_QUIROFANO = 500.0;

// Constructor con validación básica
MobiliarioClinico::MobiliarioClinico(const std::string& codigo, const std::string& fechaIngreso,
                                     EstadoArticulo estado, double costoUnitario, 
                                     const std::string& material, AreaUbicacion area)
    : Articulo(codigo, TipoArticulo::MOBILIARIO_CLINICO, fechaIngreso, estado, costoUnitario),
      material(material), areaUbicacion(area) {
    if (codigo.empty()) throw std::invalid_argument("El código no puede estar vacío.");
    if (fechaIngreso.empty()) throw std::invalid_argument("La fecha de ingreso no puede estar vacía.");
    if (costoUnitario < 0) throw std::invalid_argument("El costo unitario no puede ser negativo.");
    if (material.empty()) throw std::invalid_argument("El material no puede estar vacío.");
}

// Implementación del método getInformacion
std::string MobiliarioClinico::getInformacion() const {
    std::ostringstream info;
    info << std::fixed << std::setprecision(2);
    info << "=== MOBILIARIO CLÍNICO ===" << std::endl;
    info << "Código: " << codigo << std::endl;
    info << "Tipo: " << tipoToString(tipo) << std::endl;
    info << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    info << "Estado: " << estadoToString(estado) << std::endl;
    info << "Costo Unitario: $" << costoUnitario << std::endl;
    info << "Material: " << material << std::endl;
    info << "Área de Ubicación: " << areaUbicacionToString(areaUbicacion) << std::endl;
    info << "Plus por Área: $" << calcularPlusPorArea() << std::endl;
    info << "Valor Total con Plus: $" << calcularValorConPlus() << std::endl;
    return info.str();
}

// Implementación del método calcularCostoTotal
double MobiliarioClinico::calcularCostoTotal() const {
    // Siempre retorna el valor total con plus
    return calcularValorConPlus();
}

// Método para calcular el plus por área
double MobiliarioClinico::calcularPlusPorArea() const {
    return getPlusPorArea(areaUbicacion);
}

// Método para calcular el valor con plus
double MobiliarioClinico::calcularValorConPlus() const {
    return costoUnitario + calcularPlusPorArea();
}


// Funciones auxiliares estáticas
std::string MobiliarioClinico::areaUbicacionToString(AreaUbicacion area) {
    switch (area) {
        case AreaUbicacion::CONSULTA:
            return "Consulta";
        case AreaUbicacion::EMERGENCIA:
            return "Emergencia";
        case AreaUbicacion::QUIROFANO:
            return "Quirófano";
        default:
            return "Desconocido";
    }
}

AreaUbicacion MobiliarioClinico::stringToAreaUbicacion(const std::string& str) {
    if (str == "Consulta" || str == "CONSULTA") {
        return AreaUbicacion::CONSULTA;
    } else if (str == "Emergencia" || str == "EMERGENCIA") {
        return AreaUbicacion::EMERGENCIA;
    } else if (str == "Quirófano" || str == "QUIROFANO") {
        return AreaUbicacion::QUIROFANO;
    }
    throw std::invalid_argument("Área de ubicación inválida: " + str);
}

double MobiliarioClinico::getPlusPorArea(AreaUbicacion area) {
    switch (area) {
        case AreaUbicacion::CONSULTA:
            return PLUS_CONSULTA;
        case AreaUbicacion::EMERGENCIA:
            return PLUS_EMERGENCIA;
        case AreaUbicacion::QUIROFANO:
            return PLUS_QUIROFANO;
        default:
            throw std::invalid_argument("Área de ubicación inválida (enum)");
    }
}
