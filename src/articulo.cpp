#include "../include/articulo.hpp"
#include <sstream>

// Constructor
Articulo::Articulo(const std::string& cod, TipoArticulo tip, const std::string& fecha, 
                   EstadoArticulo est, double costo)
    : codigo(cod), tipo(tip), fechaIngreso(fecha), estado(est), costoUnitario(costo) {
}

// Implementación del método virtual calcularCostoTotal
double Articulo::calcularCostoTotal() const {
    return costoUnitario;
}

// Funciones auxiliares para conversión de enums
std::string Articulo::tipoToString(TipoArticulo tipo) {
    switch (tipo) {
        case TipoArticulo::EQUIPO_MEDICO:
            return "Equipo Médico";
        case TipoArticulo::MOBILIARIO_CLINICO:
            return "Mobiliario Clínico";
        default:
            return "Desconocido";
    }
}

std::string Articulo::estadoToString(EstadoArticulo estado) {
    switch (estado) {
        case EstadoArticulo::OPERATIVO:
            return "Operativo";
        case EstadoArticulo::EN_REVISION:
            return "En Revisión";
        case EstadoArticulo::DANADO:
            return "Dañado";
        default:
            return "Desconocido";
    }
}

TipoArticulo Articulo::stringToTipo(const std::string& str) {
    if (str == "Equipo Médico" || str == "EQUIPO_MEDICO") {
        return TipoArticulo::EQUIPO_MEDICO;
    } else if (str == "Mobiliario Clínico" || str == "MOBILIARIO_CLINICO") {
        return TipoArticulo::MOBILIARIO_CLINICO;
    }
    return TipoArticulo::EQUIPO_MEDICO; // valor por defecto
}

EstadoArticulo Articulo::stringToEstado(const std::string& str) {
    if (str == "Operativo" || str == "OPERATIVO") {
        return EstadoArticulo::OPERATIVO;
    } else if (str == "En Revisión" || str == "EN_REVISION") {
        return EstadoArticulo::EN_REVISION;
    } else if (str == "Dañado" || str == "DANADO") {
        return EstadoArticulo::DANADO;
    }
    return EstadoArticulo::OPERATIVO; // valor por defecto
}
