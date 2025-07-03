
#include "../include/mobiliario_clinico.hpp"
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Plus por área para mobiliario clínico
const double MobiliarioClinico::PLUS_CONSULTA = 200.0;
const double MobiliarioClinico::PLUS_EMERGENCIA = 300.0;
const double MobiliarioClinico::PLUS_QUIROFANO = 500.0;

MobiliarioClinico::MobiliarioClinico(const std::string& codigo, const std::string& fechaIngreso,
                                     const EstadoArticulo estado, const double costoUnitario, 
                                     const std::string& material, const AreaUbicacion area)
    : Articulo(codigo, MedicalInventory::Domain::ArticleType::CLINICAL_FURNITURE, fechaIngreso, estado, costoUnitario),
      material(material), areaUbicacion(area) {
    if (codigo.empty()) throw std::invalid_argument("[MobiliarioClinico] Código vacío.");
    if (fechaIngreso.empty()) throw std::invalid_argument("[MobiliarioClinico] Fecha de ingreso vacía.");
    if (costoUnitario < 0) throw std::invalid_argument("[MobiliarioClinico] Costo unitario negativo.");
    if (material.empty()) throw std::invalid_argument("[MobiliarioClinico] Material vacío.");
}

std::string MobiliarioClinico::getInformacion() const {
    std::ostringstream info;
    info << std::fixed << std::setprecision(2);
    info << "=== MOBILIARIO CLÍNICO ===\n"
         << "Código: " << GetCode() << '\n'
         << "Tipo: " << tipoToString(GetType()) << '\n'
         << "Fecha de Ingreso: " << GetEntryDate() << '\n'
         << "Estado: " << estadoToString(GetStatus()) << '\n'
         << "Costo Unitario: $" << GetUnitCost() << '\n'
         << "Material: " << material << '\n'
         << "Área de Ubicación: " << areaUbicacionToString(areaUbicacion) << '\n'
         << "Plus por Área: $" << calcularPlusPorArea() << '\n'
         << "Valor Total con Plus: $" << calcularValorConPlus() << '\n';
    return info.str();
}

double MobiliarioClinico::calcularCostoTotal() const {
    return calcularValorConPlus();
}

double MobiliarioClinico::calcularPlusPorArea() const {
    return getPlusPorArea(areaUbicacion);
}

double MobiliarioClinico::calcularValorConPlus() const {
    return GetUnitCost() + calcularPlusPorArea();
}


std::string MobiliarioClinico::areaUbicacionToString(const AreaUbicacion area) {
    switch (area) {
        case AreaUbicacion::CONSULTA:   return "Consulta";
        case AreaUbicacion::EMERGENCIA: return "Emergencia";
        case AreaUbicacion::QUIROFANO:  return "Quirófano";
        default:                        return "Desconocido";
    }
}

AreaUbicacion MobiliarioClinico::stringToAreaUbicacion(const std::string& str) {
    if (str == "Consulta" || str == "CONSULTA") return AreaUbicacion::CONSULTA;
    if (str == "Emergencia" || str == "EMERGENCIA") return AreaUbicacion::EMERGENCIA;
    if (str == "Quirófano" || str == "QUIROFANO") return AreaUbicacion::QUIROFANO;
    throw std::invalid_argument("[MobiliarioClinico] Área de ubicación inválida: " + str);
}

double MobiliarioClinico::getPlusPorArea(const AreaUbicacion area) {
    switch (area) {
        case AreaUbicacion::CONSULTA:   return PLUS_CONSULTA;
        case AreaUbicacion::EMERGENCIA: return PLUS_EMERGENCIA;
        case AreaUbicacion::QUIROFANO:  return PLUS_QUIROFANO;
        default:
            throw std::invalid_argument("[MobiliarioClinico] Área de ubicación inválida (enum)");
    }
}
