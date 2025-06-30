#include "../include/inventario.hpp"
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>

// Agregar un nuevo artículo al inventario
void Inventario::agregarArticulo(std::unique_ptr<Articulo> articulo) {
    if (articulo && !existeCodigo(articulo->getCodigo())) {
        articulos.push_back(std::move(articulo));
    }
}

// b) Agrupar equipos médicos por marca y área
std::map<std::pair<MarcaEquipo, AreaUso>, std::vector<EquipoMedico*>> 
Inventario::agruparEquiposPorMarcaYArea() const {
    std::map<std::pair<MarcaEquipo, AreaUso>, std::vector<EquipoMedico*>> agrupados;
    
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == TipoArticulo::EQUIPO_MEDICO) {
            EquipoMedico* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
            if (equipo) {
                std::pair<MarcaEquipo, AreaUso> clave = {equipo->getMarca(), equipo->getAreaUso()};
                agrupados[clave].push_back(equipo);
            }
        }
    }
    
    return agrupados;
}

// c) Obtener artículos dañados y agruparlos por tipo
std::vector<Articulo*> Inventario::obtenerArticulosDanados() const {
    std::vector<Articulo*> danados;
    
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == EstadoArticulo::DANADO) {
            danados.push_back(articulo.get());
        }
    }
    
    return danados;
}

std::map<TipoArticulo, std::vector<Articulo*>> Inventario::agruparDanadosPorTipo() const {
    std::map<TipoArticulo, std::vector<Articulo*>> danadosPorTipo;
    
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == EstadoArticulo::DANADO) {
            danadosPorTipo[articulo->getTipo()].push_back(articulo.get());
        }
    }
    
    return danadosPorTipo;
}

// d) Calcular costo total por categoría
double Inventario::calcularCostoTotalPorCategoria(TipoArticulo tipo) const {
    double total = 0.0;
    
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == tipo) {
            total += articulo->calcularCostoTotal();
        }
    }
    
    return total;
}

std::map<TipoArticulo, double> Inventario::calcularCostosPorCategoria() const {
    std::map<TipoArticulo, double> costos;
    costos[TipoArticulo::EQUIPO_MEDICO] = calcularCostoTotalPorCategoria(TipoArticulo::EQUIPO_MEDICO);
    costos[TipoArticulo::MOBILIARIO_CLINICO] = calcularCostoTotalPorCategoria(TipoArticulo::MOBILIARIO_CLINICO);
    return costos;
}

// e) Obtener costos mínimo y máximo
std::pair<double, double> Inventario::obtenerCostosMinMax() const {
    if (articulos.empty()) {
        return {0.0, 0.0};
    }
    
    double minCosto = std::numeric_limits<double>::max();
    double maxCosto = std::numeric_limits<double>::min();
    
    for (const auto& articulo : articulos) {
        double costo = articulo->getCostoUnitario();
        minCosto = std::min(minCosto, costo);
        maxCosto = std::max(maxCosto, costo);
    }
    
    return {minCosto, maxCosto};
}

Articulo* Inventario::obtenerArticuloMasCaro() const {
    if (articulos.empty()) return nullptr;
    
    auto it = std::max_element(articulos.begin(), articulos.end(),
        [](const std::unique_ptr<Articulo>& a, const std::unique_ptr<Articulo>& b) {
            return a->getCostoUnitario() < b->getCostoUnitario();
        });
    
    return it->get();
}

Articulo* Inventario::obtenerArticuloMasBarato() const {
    if (articulos.empty()) return nullptr;
    
    auto it = std::min_element(articulos.begin(), articulos.end(),
        [](const std::unique_ptr<Articulo>& a, const std::unique_ptr<Articulo>& b) {
            return a->getCostoUnitario() < b->getCostoUnitario();
        });
    
    return it->get();
}

// f) Técnico con más equipos asignados
std::string Inventario::obtenerTecnicoConMasEquipos() const {
    std::map<std::string, int> conteo = contarEquiposPorTecnico();
    
    if (conteo.empty()) return "";
    
    auto it = std::max_element(conteo.begin(), conteo.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    
    return it->first;
}

std::map<std::string, int> Inventario::contarEquiposPorTecnico() const {
    std::map<std::string, int> conteo;
    
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == TipoArticulo::EQUIPO_MEDICO) {
            EquipoMedico* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
            if (equipo) {
                conteo[equipo->getTecnicoAsignado()]++;
            }
        }
    }
    
    return conteo;
}

// g) Calcular valores con plus para mobiliario
std::vector<std::pair<MobiliarioClinico*, double>> Inventario::calcularValoresConPlus() const {
    std::vector<std::pair<MobiliarioClinico*, double>> valoresConPlus;
    
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == TipoArticulo::MOBILIARIO_CLINICO) {
            MobiliarioClinico* mobiliario = dynamic_cast<MobiliarioClinico*>(articulo.get());
            if (mobiliario) {
                valoresConPlus.emplace_back(mobiliario, mobiliario->calcularValorConPlus());
            }
        }
    }
    
    return valoresConPlus;
}

// Métodos auxiliares
std::vector<Articulo*> Inventario::obtenerTodosLosArticulos() const {
    std::vector<Articulo*> todos;
    for (const auto& articulo : articulos) {
        todos.push_back(articulo.get());
    }
    return todos;
}

std::vector<EquipoMedico*> Inventario::obtenerEquiposMedicos() const {
    std::vector<EquipoMedico*> equipos;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == TipoArticulo::EQUIPO_MEDICO) {
            EquipoMedico* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
            if (equipo) {
                equipos.push_back(equipo);
            }
        }
    }
    return equipos;
}

std::vector<MobiliarioClinico*> Inventario::obtenerMobiliario() const {
    std::vector<MobiliarioClinico*> mobiliario;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == TipoArticulo::MOBILIARIO_CLINICO) {
            MobiliarioClinico* mob = dynamic_cast<MobiliarioClinico*>(articulo.get());
            if (mob) {
                mobiliario.push_back(mob);
            }
        }
    }
    return mobiliario;
}

// Búsqueda y filtros
Articulo* Inventario::buscarPorCodigo(const std::string& codigo) const {
    auto it = std::find_if(articulos.begin(), articulos.end(),
        [&codigo](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getCodigo() == codigo;
        });
    
    return (it != articulos.end()) ? it->get() : nullptr;
}

std::vector<Articulo*> Inventario::filtrarPorEstado(EstadoArticulo estado) const {
    std::vector<Articulo*> filtrados;
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == estado) {
            filtrados.push_back(articulo.get());
        }
    }
    return filtrados;
}

std::vector<Articulo*> Inventario::filtrarPorTipo(TipoArticulo tipo) const {
    std::vector<Articulo*> filtrados;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == tipo) {
            filtrados.push_back(articulo.get());
        }
    }
    return filtrados;
}

// Estadísticas
size_t Inventario::obtenerCantidadPorTipo(TipoArticulo tipo) const {
    return std::count_if(articulos.begin(), articulos.end(),
        [tipo](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getTipo() == tipo;
        });
}

size_t Inventario::obtenerCantidadPorEstado(EstadoArticulo estado) const {
    return std::count_if(articulos.begin(), articulos.end(),
        [estado](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getEstado() == estado;
        });
}

// Validación
bool Inventario::existeCodigo(const std::string& codigo) const {
    return buscarPorCodigo(codigo) != nullptr;
}

// Persistencia (implementación básica)
void Inventario::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    
    for (const auto& articulo : articulos) {
        archivo << articulo->getInformacion() << "\n---\n";
    }
    
    archivo.close();
}

void Inventario::cargarDeArchivo(const std::string& nombreArchivo) {
    // Implementación básica - en un proyecto real se haría parsing completo
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) return;
    
    // Por ahora solo se implementa la estructura
    archivo.close();
}
