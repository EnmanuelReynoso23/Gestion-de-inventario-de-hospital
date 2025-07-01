#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "articulo.hpp"
#include "equipo_medico.hpp"
#include "mobiliario_clinico.hpp"
#include <vector>
#include <memory>
#include <map>
#include <string>

class Inventario {
private:
    std::vector<std::unique_ptr<Articulo>> articulos;
    
public:
    // Constructor y destructor
    Inventario() = default;
    ~Inventario() = default;
    
    // Métodos principales del sistema
    void agregarArticulo(std::unique_ptr<Articulo> articulo);
    
    // a) Ingresar nuevos artículos - implementado con agregarArticulo
    
    // b) Mostrar equipos médicos agrupados por marca y área
    std::map<std::pair<MarcaEquipo, AreaUso>, std::vector<EquipoMedico*>> 
        agruparEquiposPorMarcaYArea() const;
    
    // c) Mostrar artículos dañados por tipo
    std::vector<Articulo*> obtenerArticulosDanados() const;
    std::map<TipoArticulo, std::vector<Articulo*>> agruparDanadosPorTipo() const;
    
    // d) Calcular costo total por categoría
    double calcularCostoTotalPorCategoria(TipoArticulo tipo) const;
    std::map<TipoArticulo, double> calcularCostosPorCategoria() const;
    
    // e) Calcular costo más alto y más bajo
    std::pair<double, double> obtenerCostosMinMax() const;
    Articulo* obtenerArticuloMasCaro() const;
    Articulo* obtenerArticuloMasBarato() const;
    
    // f) Mostrar técnico con más equipos asignados
    std::string obtenerTecnicoConMasEquipos() const;
    std::map<std::string, int> contarEquiposPorTecnico() const;
    
    // g) Calcular valor con plus para cada mobiliario
    std::vector<std::pair<MobiliarioClinico*, double>> calcularValoresConPlus() const;
    
    // Métodos auxiliares
    std::vector<Articulo*> obtenerTodosLosArticulos() const;
    std::vector<EquipoMedico*> obtenerEquiposMedicos() const;
    std::vector<MobiliarioClinico*> obtenerMobiliario() const;
    
    // Búsqueda y filtros
    Articulo* buscarPorCodigo(const std::string& codigo) const;
    std::vector<Articulo*> filtrarPorEstado(EstadoArticulo estado) const;
    std::vector<Articulo*> filtrarPorTipo(TipoArticulo tipo) const;
    
    // Estadísticas
    size_t obtenerCantidadTotal() const { return articulos.size(); }
    size_t obtenerCantidadPorTipo(TipoArticulo tipo) const;
    size_t obtenerCantidadPorEstado(EstadoArticulo estado) const;
    
    // Validación
    bool existeCodigo(const std::string& codigo) const;
    
    // Métodos adicionales de mejora
    std::vector<EquipoMedico*> obtenerEquiposQueNecesitanMantenimiento() const;
    std::map<std::string, double> calcularValorTotalPorTecnico() const;
    std::vector<Articulo*> obtenerArticulosRecientes(int dias = 30) const;
    double calcularDepreciacionTotal() const;
    std::map<AreaUso, int> contarEquiposPorArea() const;
    std::map<AreaUbicacion, int> contarMobiliarioPorArea() const;
    
    // Reportes avanzados
    void generarReporteCompleto(const std::string& nombreArchivo) const;
    std::string generarResumenEjecutivo() const;
    
    // Persistencia (opcional para futuras mejoras)
    void guardarEnArchivo(const std::string& nombreArchivo) const;
    void cargarDeArchivo(const std::string& nombreArchivo);
};

#endif // INVENTARIO_HPP
