/**
 * @file equipo_medico.cpp
 * @brief Implementation of the EquipoMedico class
 * @author Medical Inventory Team
 * @date 2025
 */

#include "../include/equipo_medico.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <ctime>

EquipoMedico::EquipoMedico(const std::string& codigo, const std::string& fechaIngreso,
                           const ArticleStatus estado, const double costoUnitario, const MarcaEquipo marca,
                           const int vidaUtil, const std::string& tecnico, const AreaUso area)
    : Articulo(codigo, ArticleType::MEDICAL_EQUIPMENT, fechaIngreso, estado, costoUnitario),
      marca(marca), vidaUtilAnios(vidaUtil), tecnicoAsignado(tecnico), areaUso(area) {
    if (codigo.empty()) throw std::invalid_argument("[EquipoMedico] Código vacío.");
    if (fechaIngreso.empty()) throw std::invalid_argument("[EquipoMedico] Fecha de ingreso vacía.");
    if (costoUnitario < 0) throw std::invalid_argument("[EquipoMedico] Costo unitario negativo.");
    if (vidaUtil <= 0) throw std::invalid_argument("[EquipoMedico] Vida útil debe ser mayor a 0.");
    if (tecnico.empty()) throw std::invalid_argument("[EquipoMedico] Técnico asignado vacío.");
}

std::string EquipoMedico::GetDetailedInfo() const {
    std::ostringstream info;
    info << std::fixed << std::setprecision(2);
    info << "=== EQUIPO MÉDICO ===\n"
         << "Código: " << GetCode() << '\n'
         << "Tipo: " << TypeToString(GetType()) << '\n'
         << "Fecha de Ingreso: " << GetEntryDate() << '\n'
         << "Estado: " << StatusToString(GetStatus()) << '\n'
         << "Costo Unitario: $" << GetUnitCost() << '\n'
         << "Marca: " << marcaToString(marca) << '\n'
         << "Vida Útil: " << vidaUtilAnios << " años\n"
         << "Técnico Asignado: " << tecnicoAsignado << '\n'
         << "Área de Uso: " << areaToString(areaUso) << '\n'
         << "Depreciación: $" << calcularDepreciacion() << '\n';
    return info.str();
}

// Implementación del método legacy para compatibilidad
std::string EquipoMedico::getInformacion() const {
    return GetDetailedInfo();
}

// Implementación del método CalculateTotalCost (nueva interfaz)
double EquipoMedico::CalculateTotalCost() const {
    return GetUnitCost() - calcularDepreciacion();
}

// Implementación del método legacy para compatibilidad
double EquipoMedico::calcularCostoTotal() const {
    return CalculateTotalCost();
}

// Método para calcular la depreciación
double EquipoMedico::calcularDepreciacion() const {
    // Calcular años transcurridos desde la fecha de ingreso
    double aniosTranscurridos = calcularAniosTranscurridos();
    
    if (vidaUtilAnios <= 0) return 0.0;
    
    double depreciacionAnual = GetUnitCost() / vidaUtilAnios;
    return std::min(depreciacionAnual * aniosTranscurridos, GetUnitCost() * 0.8); // máximo 80% de depreciación
}

// Método para calcular años transcurridos desde fecha de ingreso
double EquipoMedico::calcularAniosTranscurridos() const {
    try {
        const std::string& fechaIngreso = GetEntryDate();
        if (fechaIngreso.length() >= 10) {
            const std::string anioStr = fechaIngreso.substr(6, 4);
            const int anioIngreso = std::stoi(anioStr);
            const auto now = std::chrono::system_clock::now();
            const std::time_t t = std::chrono::system_clock::to_time_t(now);
            const struct tm* ltm = std::localtime(&t);
            const int anioActual = 1900 + ltm->tm_year;
            const double diferencia = anioActual - anioIngreso;
            return std::max(0.0, diferencia);
        }
    } catch (const std::exception&) {
        // Si hay error en el parsing, usar valor por defecto
    }
    return 2.0;
}

// Método para verificar si necesita mantenimiento
bool EquipoMedico::necesitaMantenimiento() const {
    return GetStatus() == ArticleStatus::UNDER_REVIEW || GetStatus() == ArticleStatus::DAMAGED;
}

// Funciones auxiliares estáticas
std::string EquipoMedico::marcaToString(MarcaEquipo marca) {
    switch (marca) {
        case MarcaEquipo::PHILIPS:
            return "Philips";
        case MarcaEquipo::GE:
            return "GE";
        case MarcaEquipo::MINDRAY:
            return "Mindray";
        case MarcaEquipo::OTROS:
            return "Otros";
        default:
            return "Desconocido";
    }
}

std::string EquipoMedico::areaToString(AreaUso area) {
    switch (area) {
        case AreaUso::EMERGENCIA:
            return "Emergencia";
        case AreaUso::PEDIATRIA:
            return "Pediatría";
        case AreaUso::QUIROFANO:
            return "Quirófano";
        default:
            return "Desconocido";
    }
}

MarcaEquipo EquipoMedico::stringToMarca(const std::string& str) {
    if (str == "Philips" || str == "PHILIPS") {
        return MarcaEquipo::PHILIPS;
    } else if (str == "GE") {
        return MarcaEquipo::GE;
    } else if (str == "Mindray" || str == "MINDRAY") {
        return MarcaEquipo::MINDRAY;
    } else {
        return MarcaEquipo::OTROS;
    }
}

AreaUso EquipoMedico::stringToArea(const std::string& str) {
    if (str == "Emergencia" || str == "EMERGENCIA") {
        return AreaUso::EMERGENCIA;
    } else if (str == "Pediatría" || str == "PEDIATRIA") {
        return AreaUso::PEDIATRIA;
    } else if (str == "Quirófano" || str == "QUIROFANO") {
        return AreaUso::QUIROFANO;
    }
    return AreaUso::EMERGENCIA; // valor por defecto
}

void EquipoMedico::setTecnicoAsignado(const std::string& nuevoTecnico) {
    if (nuevoTecnico.empty()) {
        throw std::invalid_argument("[EquipoMedico] Técnico asignado vacío.");
    }
    tecnicoAsignado = nuevoTecnico;
}
