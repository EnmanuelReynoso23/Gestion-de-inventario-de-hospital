/**
 * @file articulo.cpp
 * @brief Implementation of the base Article class
 * @author Medical Inventory Team
 * @date 2025
 */

#include "../include/articulo.hpp"
#include <sstream>
#include <algorithm>
#include <regex>
#include <cctype>

using namespace MedicalInventory::Domain;

// Constructor con validación
Articulo::Articulo(const std::string& code, 
                   const ArticleType type, 
                   const std::string& entryDate,
                   const ArticleStatus status, 
                   const double unitCost)
    : m_code(code), m_type(type), m_entryDate(entryDate), 
      m_status(status), m_unitCost(unitCost) {
    ValidateParameters(code, entryDate, unitCost);
}

void Articulo::SetUnitCost(const double newCost) {
    if (!IsValidCost(newCost)) {
        throw std::invalid_argument("[Articulo] Costo inválido: debe estar entre " + 
                                  std::to_string(Validation::MIN_COST) + 
                                  " y " + std::to_string(Validation::MAX_COST));
    }
    m_unitCost = newCost;
}

double Articulo::CalculateTotalCost() const {
    return m_unitCost;
}

std::string Articulo::TypeToString(const ArticleType type) {
    switch (type) {
        case ArticleType::MEDICAL_EQUIPMENT:   return "Medical Equipment";
        case ArticleType::CLINICAL_FURNITURE:  return "Clinical Furniture";
        default:                               return "Unknown Type";
    }
}

std::string Articulo::StatusToString(const ArticleStatus status) {
    switch (status) {
        case ArticleStatus::OPERATIONAL:   return "Operational";
        case ArticleStatus::UNDER_REVIEW:  return "Under Review";
        case ArticleStatus::DAMAGED:       return "Damaged";
        default:                           return "Unknown Status";
    }
}

Articulo::ArticleType Articulo::StringToType(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    if (lowerStr == "medical equipment" || lowerStr == "equipo_medico" || 
        lowerStr == "equipo médico" || lowerStr == "equipment") {
        return ArticleType::MEDICAL_EQUIPMENT;
    }
    if (lowerStr == "clinical furniture" || lowerStr == "mobiliario_clinico" || 
        lowerStr == "mobiliario clínico" || lowerStr == "furniture") {
        return ArticleType::CLINICAL_FURNITURE;
    }
    throw std::invalid_argument("[Articulo] Tipo de artículo inválido: " + str);
}

Articulo::ArticleStatus Articulo::StringToStatus(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    if (lowerStr == "operational" || lowerStr == "operativo") {
        return ArticleStatus::OPERATIONAL;
    }
    if (lowerStr == "under review" || lowerStr == "en revisión" || 
        lowerStr == "en revision" || lowerStr == "en_revision") {
        return ArticleStatus::UNDER_REVIEW;
    }
    if (lowerStr == "damaged" || lowerStr == "dañado" || lowerStr == "danado") {
        return ArticleStatus::DAMAGED;
    }
    throw std::invalid_argument("[Articulo] Estado de artículo inválido: " + str);
}

// Validation methods
bool Articulo::IsValidCode(const std::string& code) {
    if (code.empty() || 
        code.length() < Validation::MIN_CODE_LENGTH || 
        code.length() > Validation::MAX_CODE_LENGTH) {
        return false;
    }
    const std::regex codePattern("^[A-Za-z0-9_-]+$");
    return std::regex_match(code, codePattern);
}

bool Articulo::IsValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    const std::regex datePattern("^([0-2][0-9]|3[01])/(0[1-9]|1[0-2])/([12][0-9]{3})$");
    if (!std::regex_match(date, datePattern)) return false;
    const int day = std::stoi(date.substr(0, 2));
    const int month = std::stoi(date.substr(3, 2));
    const int year = std::stoi(date.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12) return false;
    if (year < 2000 || year > 2099) return false;
    if (month == 2) {
        const bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) return false;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }
    return true;
}

bool Articulo::IsValidCost(const double cost) {
    return cost >= Validation::MIN_COST && 
           cost <= Validation::MAX_COST && 
           !std::isnan(cost) && 
           std::isfinite(cost);
}

// Comparison operators
bool Articulo::operator==(const Articulo& other) const {
    return m_code == other.m_code;
}

bool Articulo::operator!=(const Articulo& other) const {
    return !(*this == other);
}

bool Articulo::operator<(const Articulo& other) const {
    return m_code < other.m_code;
}

void Articulo::ValidateParameters(const std::string& code, 
                                 const std::string& entryDate, 
                                 const double unitCost) const {
    if (!IsValidCode(code)) {
        throw std::invalid_argument("[Articulo] Código inválido: '" + code +
                                  "'. Debe tener entre " + std::to_string(Validation::MIN_CODE_LENGTH) +
                                  " y " + std::to_string(Validation::MAX_CODE_LENGTH) +
                                  " caracteres y solo contener alfanuméricos, guiones y guiones bajos.");
    }
    if (!IsValidDate(entryDate)) {
        throw std::invalid_argument("[Articulo] Fecha inválida: '" + entryDate +
                                  "'. Formato esperado: DD/MM/YYYY");
    }
    if (!IsValidCost(unitCost)) {
        throw std::invalid_argument("[Articulo] Costo inválido: " + std::to_string(unitCost) +
                                  ". Debe estar entre " + std::to_string(Validation::MIN_COST) +
                                  " y " + std::to_string(Validation::MAX_COST));
    }
}
