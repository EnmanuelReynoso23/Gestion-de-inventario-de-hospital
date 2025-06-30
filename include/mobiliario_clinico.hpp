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
    // Constructor
    MobiliarioClinico(const std::string& codigo, const std::string& fechaIngreso,
                      EstadoArticulo estado, double costoUnitario, 
                      const std::string& material, AreaUbicacion area);
    
    // Getters específicos
    std::string getMaterial() const { return material; }
    AreaUbicacion getAreaUbicacion() const { return areaUbicacion; }
    
    // Setters específicos
    void setMaterial(const std::string& nuevoMaterial) { material = nuevoMaterial; }
    void setAreaUbicacion(AreaUbicacion area) { areaUbicacion = area; }
    
    // Métodos heredados
    std::string getInformacion() const override;
    double calcularCostoTotal() const override;
    
    // Métodos específicos
    double calcularPlusPorArea() const;
    double calcularValorConPlus() const;
    
    // Funciones auxiliares estáticas
    static std::string areaUbicacionToString(AreaUbicacion area);
    static AreaUbicacion stringToAreaUbicacion(const std::string& str);
    static double getPlusPorArea(AreaUbicacion area);
};

#endif // MOBILIARIO_CLINICO_HPP
