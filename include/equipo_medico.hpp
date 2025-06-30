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
    // Constructor
    EquipoMedico(const std::string& codigo, const std::string& fechaIngreso,
                 EstadoArticulo estado, double costoUnitario, MarcaEquipo marca,
                 int vidaUtil, const std::string& tecnico, AreaUso area);
    
    // Getters específicos
    MarcaEquipo getMarca() const { return marca; }
    int getVidaUtilAnios() const { return vidaUtilAnios; }
    std::string getTecnicoAsignado() const { return tecnicoAsignado; }
    AreaUso getAreaUso() const { return areaUso; }
    
    // Setters específicos
    void setTecnicoAsignado(const std::string& tecnico) { tecnicoAsignado = tecnico; }
    void setAreaUso(AreaUso area) { areaUso = area; }
    void setVidaUtilAnios(int anios) { vidaUtilAnios = anios; }
    
    // Métodos heredados
    std::string getInformacion() const override;
    double calcularCostoTotal() const override;
    
    // Funciones auxiliares estáticas
    static std::string marcaToString(MarcaEquipo marca);
    static std::string areaToString(AreaUso area);
    static MarcaEquipo stringToMarca(const std::string& str);
    static AreaUso stringToArea(const std::string& str);
    
    // Métodos específicos
    double calcularDepreciacion() const;
    bool necesitaMantenimiento() const;
};

#endif // EQUIPO_MEDICO_HPP
