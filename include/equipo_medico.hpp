/**
 * @file equipo_medico.hpp
 * @brief Medical equipment class declaration
 * @author Medical Inventory Team
 * @date 2025
 */

#ifndef EQUIPO_MEDICO_HPP
#define EQUIPO_MEDICO_HPP

#include "articulo.hpp"
#include <string>

enum class MarcaEquipo {
    PHILIPS,
    GE,
    MINDRAY,
    OTROS
};

enum class AreaUso {
    EMERGENCIA,
    PEDIATRIA,
    QUIROFANO
};

class EquipoMedico : public Articulo {
private:
    MarcaEquipo marca;
    int vidaUtilAnios;
    std::string tecnicoAsignado;
    AreaUso areaUso;

public:
    // Type aliases for new interface
    using ArticleStatus = Articulo::ArticleStatus;
    using ArticleType = Articulo::ArticleType;

    // Constructor - updated to use new enum names
    EquipoMedico(const std::string& codigo, const std::string& fechaIngreso,
                 ArticleStatus estado, double costoUnitario, MarcaEquipo marca,
                 int vidaUtil, const std::string& tecnico, AreaUso area);
    
    // Getters específicos
    MarcaEquipo getMarca() const { return marca; }
    int getVidaUtilAnios() const { return vidaUtilAnios; }
    const std::string& getTecnicoAsignado() const { return tecnicoAsignado; }
    AreaUso getAreaUso() const { return areaUso; }
    
    // Setters específicos
    void setTecnicoAsignado(const std::string& tecnico);
    void setAreaUso(AreaUso area) { areaUso = area; }
    void setVidaUtilAnios(int anios) { vidaUtilAnios = anios; }
    
    // New interface methods (override virtual methods from base)
    std::string GetDetailedInfo() const override;
    double CalculateTotalCost() const override;
    
    // Legacy methods for compatibility (deprecated)
    [[deprecated("Use GetDetailedInfo() instead")]]
    std::string getInformacion() const;
    
    [[deprecated("Use CalculateTotalCost() instead")]]
    double calcularCostoTotal() const;
    
    // Funciones auxiliares estáticas
    static std::string marcaToString(MarcaEquipo marca);
    static std::string areaToString(AreaUso area);
    static MarcaEquipo stringToMarca(const std::string& str);
    static AreaUso stringToArea(const std::string& str);
    
    // Métodos específicos
    double calcularDepreciacion() const;
    double calcularAniosTranscurridos() const;
    bool necesitaMantenimiento() const;
};

#endif // EQUIPO_MEDICO_HPP
