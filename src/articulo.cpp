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

// Constructor with validation
Articulo::Articulo(const std::string& code, 
                   ArticleType type, 
                   const std::string& entryDate,
                   ArticleStatus status, 
                   double unitCost)
    : m_code(code), m_type(type), m_entryDate(entryDate), 
      m_status(status), m_unitCost(unitCost) {
    
    ValidateParameters(code, entryDate, unitCost);
}

// Mutator with validation
void Articulo::SetUnitCost(double newCost) {
    if (!IsValidCost(newCost)) {
        throw std::invalid_argument("Invalid cost: must be between " + 
                                  std::to_string(Validation::MIN_COST) + 
                                  " and " + std::to_string(Validation::MAX_COST));
    }
    m_unitCost = newCost;
}

// Virtual method implementation
double Articulo::CalculateTotalCost() const {
    return m_unitCost;
}

// Static utility methods for enum conversions
std::string Articulo::TypeToString(ArticleType type) {
    switch (type) {
        case ArticleType::MEDICAL_EQUIPMENT:
            return "Medical Equipment";
        case ArticleType::CLINICAL_FURNITURE:
            return "Clinical Furniture";
        default:
            return "Unknown Type";
    }
}

std::string Articulo::StatusToString(ArticleStatus status) {
    switch (status) {
        case ArticleStatus::OPERATIONAL:
            return "Operational";
        case ArticleStatus::UNDER_REVIEW:
            return "Under Review";
        case ArticleStatus::DAMAGED:
            return "Damaged";
        default:
            return "Unknown Status";
    }
}

Articulo::ArticleType Articulo::StringToType(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    
    if (lowerStr == "medical equipment" || lowerStr == "equipo_medico" || 
        lowerStr == "equipo médico" || lowerStr == "equipment") {
        return ArticleType::MEDICAL_EQUIPMENT;
    } else if (lowerStr == "clinical furniture" || lowerStr == "mobiliario_clinico" || 
               lowerStr == "mobiliario clínico" || lowerStr == "furniture") {
        return ArticleType::CLINICAL_FURNITURE;
    }
    
    throw std::invalid_argument("Invalid article type string: " + str);
}

Articulo::ArticleStatus Articulo::StringToStatus(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    
    if (lowerStr == "operational" || lowerStr == "operativo") {
        return ArticleStatus::OPERATIONAL;
    } else if (lowerStr == "under review" || lowerStr == "en revisión" || 
               lowerStr == "en revision" || lowerStr == "en_revision") {
        return ArticleStatus::UNDER_REVIEW;
    } else if (lowerStr == "damaged" || lowerStr == "dañado" || lowerStr == "danado") {
        return ArticleStatus::DAMAGED;
    }
    
    throw std::invalid_argument("Invalid article status string: " + str);
}

// Validation methods
bool Articulo::IsValidCode(const std::string& code) {
    if (code.empty() || 
        code.length() < Validation::MIN_CODE_LENGTH || 
        code.length() > Validation::MAX_CODE_LENGTH) {
        return false;
    }
    
    // Check if code contains only alphanumeric characters and common separators
    const std::regex codePattern("^[A-Za-z0-9_-]+$");
    return std::regex_match(code, codePattern);
}

bool Articulo::IsValidDate(const std::string& date) {
    if (date.length() != 10) {
        return false;
    }
    
    // Check DD/MM/YYYY format
    const std::regex datePattern("^([0-2][0-9]|3[01])/(0[1-9]|1[0-2])/([12][0-9]{3})$");
    if (!std::regex_match(date, datePattern)) {
        return false;
    }
    
    // Extract components for basic validation
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    
    // Basic range validation
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    
    // Check for reasonable year range (2000-2099)
    if (year < 2000 || year > 2099) {
        return false;
    }
    
    // Additional month-specific day validation
    if (month == 2) {  // February
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            return false;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {  // 30-day months
        if (day > 30) {
            return false;
        }
    }
    
    return true;
}

bool Articulo::IsValidCost(double cost) {
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

// Private validation method
void Articulo::ValidateParameters(const std::string& code, 
                                 const std::string& entryDate, 
                                 double unitCost) const {
    if (!IsValidCode(code)) {
        throw std::invalid_argument("Invalid article code: '" + code + 
                                  "'. Code must be " + std::to_string(Validation::MIN_CODE_LENGTH) + 
                                  "-" + std::to_string(Validation::MAX_CODE_LENGTH) + 
                                  " characters and contain only alphanumeric characters, hyphens, and underscores.");
    }
    
    if (!IsValidDate(entryDate)) {
        throw std::invalid_argument("Invalid date format: '" + entryDate + 
                                  "'. Expected format: DD/MM/YYYY");
    }
    
    if (!IsValidCost(unitCost)) {
        throw std::invalid_argument("Invalid unit cost: " + std::to_string(unitCost) + 
                                  ". Cost must be between " + std::to_string(Validation::MIN_COST) + 
                                  " and " + std::to_string(Validation::MAX_COST));
    }
}
