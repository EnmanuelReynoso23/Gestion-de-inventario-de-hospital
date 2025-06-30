#include "../include/equipo_medico.hpp"
#include <sstream>
#include <iomanip>

// Constructor
EquipoMedico::EquipoMedico(const std::string& codigo, const std::string& fechaIngreso,
                           EstadoArticulo estado, double costoUnitario, MarcaEquipo marca,
                           int vidaUtil, const std::string& tecnico, AreaUso area)
    : Articulo(codigo, TipoArticulo::EQUIPO_MEDICO, fechaIngreso, estado, costoUnitario),
      marca(marca), vidaUtilAnios(vidaUtil), tecnicoAsignado(tecnico), areaUso(area) {
}

// Implementación del método getInformacion
std::string EquipoMedico::getInformacion() const {
    std::ostringstream info;
    info << std::fixed << std::setprecision(2);
    info << "=== EQUIPO MÉDICO ===" << std::endl;
    info << "Código: " << codigo << std::endl;
    info << "Tipo: " << tipoToString(tipo) << std::endl;
    info << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    info << "Estado: " << estadoToString(estado) << std::endl;
    info << "Costo Unitario: $" << costoUnitario << std::endl;
    info << "Marca: " << marcaToString(marca) << std::endl;
    info << "Vida Útil: " << vidaUtilAnios << " años" << std::endl;
    info << "Técnico Asignado: " << tecnicoAsignado << std::endl;
    info << "Área de Uso: " << areaToString(areaUso) << std::endl;
    info << "Depreciación: $" << calcularDepreciacion() << std::endl;
    return info.str();
}

// Implementación del método calcularCostoTotal
double EquipoMedico::calcularCostoTotal() const {
    return costoUnitario - calcularDepreciacion();
}

// Método para calcular la depreciación
double EquipoMedico::calcularDepreciacion() const {
    // Depreciación lineal basada en la vida útil (simulamos que han pasado 2 años)
    double aniosTranscurridos = 2.0; // Esto podría calcularse con la fecha actual
    if (vidaUtilAnios <= 0) return 0.0;
    
    double depreciacionAnual = costoUnitario / vidaUtilAnios;
    return std::min(depreciacionAnual * aniosTranscurridos, costoUnitario * 0.8); // máximo 80% de depreciación
}

// Método para verificar si necesita mantenimiento
bool EquipoMedico::necesitaMantenimiento() const {
    return estado == EstadoArticulo::EN_REVISION || estado == EstadoArticulo::DANADO;
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
