#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <string>
#include <iostream>

enum class TipoArticulo {
    EQUIPO_MEDICO,
    MOBILIARIO_CLINICO
};

enum class EstadoArticulo {
    OPERATIVO,
    EN_REVISION,
    DANADO
};

class Articulo {
protected:
    std::string codigo;
    TipoArticulo tipo;
    std::string fechaIngreso;
    EstadoArticulo estado;
    double costoUnitario;

public:
    // Constructor
    Articulo(const std::string& cod, TipoArticulo tip, const std::string& fecha, 
             EstadoArticulo est, double costo);
    
    // Destructor virtual para herencia
    virtual ~Articulo() = default;
    
    // Getters
    std::string getCodigo() const { return codigo; }
    TipoArticulo getTipo() const { return tipo; }
    std::string getFechaIngreso() const { return fechaIngreso; }
    EstadoArticulo getEstado() const { return estado; }
    double getCostoUnitario() const { return costoUnitario; }
    
    // Setters
    void setEstado(EstadoArticulo nuevoEstado) { estado = nuevoEstado; }
    void setCostoUnitario(double nuevoCosto) { costoUnitario = nuevoCosto; }
    
    // Métodos virtuales
    virtual std::string getInformacion() const = 0;
    virtual double calcularCostoTotal() const;
    
    // Funciones auxiliares
    static std::string tipoToString(TipoArticulo tipo);
    static std::string estadoToString(EstadoArticulo estado);
    static TipoArticulo stringToTipo(const std::string& str);
    static EstadoArticulo stringToEstado(const std::string& str);
};

#endif // ARTICULO_HPP
