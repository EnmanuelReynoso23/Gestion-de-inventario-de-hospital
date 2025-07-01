/**
 * @file mobiliario_clinico.hpp
 * @brief Clinical furniture class declaration
 * @author Medical Inventory Team
 * @date 2025
 */

#ifndef MOBILIARIO_CLINICO_HPP
#define MOBILIARIO_CLINICO_HPP

#include "articulo.hpp"
#include <string>

enum class AreaUbicacion {
    CONSULTA,
    EMERGENCIA,
    QUIROFANO
};

class MobiliarioClinico : public Articulo {
private:
    std::string material;
    AreaUbicacion areaUbicacion;
    static const double PLUS_CONSULTA;
    static const double PLUS_EMERGENCIA;
    static const double PLUS_QUIROFANO;

public:
    // Type aliases for new interface
    using ArticleStatus = Articulo::ArticleStatus;
    using ArticleType = Articulo::ArticleType;

    // Constructor - updated to use new enum names
    MobiliarioClinico(const std::string& codigo, const std::string& fechaIngreso,
                      ArticleStatus estado, double costoUnitario, 
                      const std::string& material, AreaUbicacion area);
    
    // Getters específicos
    const std::string& getMaterial() const { return material; }
    AreaUbicacion getAreaUbicacion() const { return areaUbicacion; }
    
    // Setters específicos
    void setMaterial(const std::string& nuevoMaterial);
    void setAreaUbicacion(AreaUbicacion area) { areaUbicacion = area; }
    
    // New interface methods (override virtual methods from base)
    std::string GetDetailedInfo() const override;
    double CalculateTotalCost() const override;
    
    // Legacy methods for compatibility (deprecated)
    [[deprecated("Use GetDetailedInfo() instead")]]
    std::string getInformacion() const;
    
    [[deprecated("Use CalculateTotalCost() instead")]]
    double calcularCostoTotal() const;
    
    // Métodos específicos
    double calcularPlusPorArea() const;
    double calcularValorConPlus() const;
    
    // Funciones auxiliares estáticas
    static std::string areaUbicacionToString(AreaUbicacion area);
    static AreaUbicacion stringToAreaUbicacion(const std::string& str);
    static double getPlusPorArea(AreaUbicacion area);
};

#endif // MOBILIARIO_CLINICO_HPP
