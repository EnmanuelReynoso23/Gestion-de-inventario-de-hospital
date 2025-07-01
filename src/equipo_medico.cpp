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

// Constructor
EquipoMedico::EquipoMedico(const std::string& codigo, const std::string& fechaIngreso,
                           ArticleStatus estado, double costoUnitario, MarcaEquipo marca,
                           int vidaUtil, const std::string& tecnico, AreaUso area)
    : Articulo(codigo, ArticleType::MEDICAL_EQUIPMENT, fechaIngreso, estado, costoUnitario),
      marca(marca), vidaUtilAnios(vidaUtil), tecnicoAsignado(tecnico), areaUso(area) {
    
    // Validaciones en el constructor
    if (codigo.empty()) throw std::invalid_argument("El código no puede estar vacío.");
    if (fechaIngreso.empty()) throw std::invalid_argument("La fecha de ingreso no puede estar vacía.");
    if (costoUnitario < 0) throw std::invalid_argument("El costo unitario no puede ser negativo.");
    if (vidaUtil <= 0) throw std::invalid_argument("La vida útil debe ser mayor a 0.");
    if (tecnico.empty()) throw std::invalid_argument("El técnico asignado no puede estar vacío.");
}

// Implementación del método GetDetailedInfo (nueva interfaz)
std::string EquipoMedico::GetDetailedInfo() const {
    std::ostringstream info;
    info << std::fixed << std::setprecision(2);
    info << "=== EQUIPO MÉDICO ===" << std::endl;
    info << "Código: " << GetCode() << std::endl;
    info << "Tipo: " << TypeToString(GetType()) << std::endl;
    info << "Fecha de Ingreso: " << GetEntryDate() << std::endl;
    info << "Estado: " << StatusToString(GetStatus()) << std::endl;
    info << "Costo Unitario: $" << GetUnitCost() << std::endl;
    info << "Marca: " << marcaToString(marca) << std::endl;
    info << "Vida Útil: " << vidaUtilAnios << " años" << std::endl;
    info << "Técnico Asignado: " << tecnicoAsignado << std::endl;
    info << "Área de Uso: " << areaToString(areaUso) << std::endl;
    info << "Depreciación: $" << calcularDepreciacion() << std::endl;
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
    // Para una implementación simple, asumimos 2 años
    // En una implementación real, se calcularía la diferencia entre fecha actual y GetEntryDate()
    try {
        // Simplificado: extraer año de la fecha (formato esperado: DD/MM/AAAA)
        const std::string& fechaIngreso = GetEntryDate();
        if (fechaIngreso.length() >= 10) {
            std::string anioStr = fechaIngreso.substr(6, 4);
            int anioIngreso = std::stoi(anioStr);
            
            // Obtener año actual
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            struct tm* ltm = std::localtime(&t);
            int anioActual = 1900 + ltm->tm_year;
            
            double diferencia = anioActual - anioIngreso;
            return std::max(0.0, diferencia); // No puede ser negativo
        }
    } catch (const std::exception&) {
        // Si hay error en el parsing, usar valor por defecto
    }
    
    return 2.0; // Valor por defecto si no se puede calcular
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

// Setter con validación
void EquipoMedico::setTecnicoAsignado(const std::string& nuevoTecnico) {
    if (nuevoTecnico.empty()) {
        throw std::invalid_argument("El técnico asignado no puede estar vacío.");
    }
    tecnicoAsignado = nuevoTecnico;
}
