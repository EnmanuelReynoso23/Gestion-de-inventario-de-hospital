#include "../include/inventario.hpp"
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>

// Agrega un nuevo artículo al inventario si el código no existe
void Inventario::agregarArticulo(std::unique_ptr<Articulo> articulo) {
    if (articulo && !existeCodigo(articulo->getCodigo())) {
        articulos.push_back(std::move(articulo));
    }
}

// Agrupa equipos médicos por marca y área
std::map<std::pair<MarcaEquipo, AreaUso>, std::vector<EquipoMedico*>> 
Inventario::agruparEquiposPorMarcaYArea() const {
    std::map<std::pair<MarcaEquipo, AreaUso>, std::vector<EquipoMedico*>> agrupados;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == MedicalInventory::Domain::ArticleType::MEDICAL_EQUIPMENT) {
            auto* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
            if (equipo) {
                agrupados[{equipo->getMarca(), equipo->getAreaUso()}].push_back(equipo);
            }
        }
    }
    return agrupados;
}

// Devuelve todos los artículos dañados
std::vector<Articulo*> Inventario::obtenerArticulosDanados() const {
    std::vector<Articulo*> danados;
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == MedicalInventory::Domain::ArticleStatus::DAMAGED) {
            danados.push_back(articulo.get());
        }
    }
    return danados;
}

std::map<MedicalInventory::Domain::ArticleType, std::vector<Articulo*>> Inventario::agruparDanadosPorTipo() const {
    std::map<MedicalInventory::Domain::ArticleType, std::vector<Articulo*>> danadosPorTipo;
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == MedicalInventory::Domain::ArticleStatus::DAMAGED) {
            danadosPorTipo[articulo->getTipo()].push_back(articulo.get());
        }
    }
    return danadosPorTipo;
}

// Calcula el costo total de una categoría
double Inventario::calcularCostoTotalPorCategoria(const MedicalInventory::Domain::ArticleType tipo) const {
    double total = 0.0;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == tipo) {
            total += articulo->calcularCostoTotal();
        }
    }
    return total;
}

std::map<MedicalInventory::Domain::ArticleType, double> Inventario::calcularCostosPorCategoria() const {
    std::map<MedicalInventory::Domain::ArticleType, double> costos;
    costos[MedicalInventory::Domain::ArticleType::MEDICAL_EQUIPMENT] = calcularCostoTotalPorCategoria(MedicalInventory::Domain::ArticleType::MEDICAL_EQUIPMENT);
    costos[MedicalInventory::Domain::ArticleType::CLINICAL_FURNITURE] = calcularCostoTotalPorCategoria(MedicalInventory::Domain::ArticleType::CLINICAL_FURNITURE);
    return costos;
}

// Devuelve el costo mínimo y máximo de los artículos
std::pair<double, double> Inventario::obtenerCostosMinMax() const {
    if (articulos.empty()) return {0.0, 0.0};
    double minCosto = std::numeric_limits<double>::max();
    double maxCosto = std::numeric_limits<double>::min();
    for (const auto& articulo : articulos) {
        const double costo = articulo->getCostoUnitario();
        minCosto = std::min(minCosto, costo);
        maxCosto = std::max(maxCosto, costo);
    }
    return {minCosto, maxCosto};
}

Articulo* Inventario::obtenerArticuloMasCaro() const {
    if (articulos.empty()) return nullptr;
    const auto it = std::max_element(articulos.begin(), articulos.end(),
        [](const std::unique_ptr<Articulo>& a, const std::unique_ptr<Articulo>& b) {
            return a->getCostoUnitario() < b->getCostoUnitario();
        });
    return it->get();
}

Articulo* Inventario::obtenerArticuloMasBarato() const {
    if (articulos.empty()) return nullptr;
    const auto it = std::min_element(articulos.begin(), articulos.end(),
        [](const std::unique_ptr<Articulo>& a, const std::unique_ptr<Articulo>& b) {
            return a->getCostoUnitario() < b->getCostoUnitario();
        });
    return it->get();
}

// Devuelve el técnico con más equipos asignados
std::string Inventario::obtenerTecnicoConMasEquipos() const {
    const auto conteo = contarEquiposPorTecnico();
    if (conteo.empty()) return "";
    const auto it = std::max_element(conteo.begin(), conteo.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
    return it->first;
}

std::map<std::string, int> Inventario::contarEquiposPorTecnico() const {
    std::map<std::string, int> conteo;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == MedicalInventory::Domain::ArticleType::MEDICAL_EQUIPMENT) {
            auto* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
            if (equipo) {
                conteo[equipo->getTecnicoAsignado()]++;
            }
        }
    }
    return conteo;
}

// Calcula el valor con plus para cada mobiliario clínico
std::vector<std::pair<MobiliarioClinico*, double>> Inventario::calcularValoresConPlus() const {
    std::vector<std::pair<MobiliarioClinico*, double>> valoresConPlus;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == MedicalInventory::Domain::ArticleType::CLINICAL_FURNITURE) {
            auto* mobiliario = dynamic_cast<MobiliarioClinico*>(articulo.get());
            if (mobiliario) {
                valoresConPlus.emplace_back(mobiliario, mobiliario->calcularValorConPlus());
            }
        }
    }
    return valoresConPlus;
}

// Devuelve todos los artículos del inventario
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
        if (articulo->getTipo() == MedicalInventory::Domain::ArticleType::MEDICAL_EQUIPMENT) {
            auto* equipo = dynamic_cast<EquipoMedico*>(articulo.get());
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
        if (articulo->getTipo() == MedicalInventory::Domain::ArticleType::CLINICAL_FURNITURE) {
            auto* mob = dynamic_cast<MobiliarioClinico*>(articulo.get());
            if (mob) {
                mobiliario.push_back(mob);
            }
        }
    }
    return mobiliario;
}

// Busca un artículo por su código
Articulo* Inventario::buscarPorCodigo(const std::string& codigo) const {
    const auto it = std::find_if(articulos.begin(), articulos.end(),
        [&codigo](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getCodigo() == codigo;
        });
    return (it != articulos.end()) ? it->get() : nullptr;
}

std::vector<Articulo*> Inventario::filtrarPorEstado(const EstadoArticulo estado) const {
    std::vector<Articulo*> filtrados;
    for (const auto& articulo : articulos) {
        if (articulo->getEstado() == estado) {
            filtrados.push_back(articulo.get());
        }
    }
    return filtrados;
}

std::vector<Articulo*> Inventario::filtrarPorTipo(const MedicalInventory::Domain::ArticleType tipo) const {
    std::vector<Articulo*> filtrados;
    for (const auto& articulo : articulos) {
        if (articulo->getTipo() == tipo) {
            filtrados.push_back(articulo.get());
        }
    }
    return filtrados;
}

size_t Inventario::obtenerCantidadPorTipo(const MedicalInventory::Domain::ArticleType tipo) const {
    return std::count_if(articulos.begin(), articulos.end(),
        [tipo](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getTipo() == tipo;
        });
}

size_t Inventario::obtenerCantidadPorEstado(const EstadoArticulo estado) const {
    return std::count_if(articulos.begin(), articulos.end(),
        [estado](const std::unique_ptr<Articulo>& articulo) {
            return articulo->getEstado() == estado;
        });
}

bool Inventario::existeCodigo(const std::string& codigo) const {
    return buscarPorCodigo(codigo) != nullptr;
}

// Guarda el inventario en un archivo (implementación básica)
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
