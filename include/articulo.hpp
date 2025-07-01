/**
 * @file articulo.hpp
 * @brief Base class for medical inventory articles
 * @author Medical Inventory Team
 * @date 2025
 */

#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <string>
#include <iostream>
#include <stdexcept>

namespace MedicalInventory {
    namespace Domain {
        /**
         * @brief Article type enumeration
         */
        enum class ArticleType {
            MEDICAL_EQUIPMENT,
            CLINICAL_FURNITURE
        };

        /**
         * @brief Article status enumeration
         */
        enum class ArticleStatus {
            OPERATIONAL,
            UNDER_REVIEW,
            DAMAGED
        };

        namespace Validation {
            /**
             * @brief Validation constants
             */
            constexpr double MIN_COST = 0.0;
            constexpr double MAX_COST = 1000000.0;  // $1M max reasonable cost
            constexpr size_t MAX_CODE_LENGTH = 20;
            constexpr size_t MIN_CODE_LENGTH = 3;
        }
    }
}

/**
 * @brief Base abstract class for medical inventory articles
 * 
 * This class provides the common interface and functionality for all
 * medical inventory items, including equipment and furniture.
 */
class Articulo {
public:
    using ArticleType = MedicalInventory::Domain::ArticleType;
    using ArticleStatus = MedicalInventory::Domain::ArticleStatus;

protected:
    std::string m_code;              ///< Unique article identifier
    ArticleType m_type;              ///< Type of article (equipment/furniture)
    std::string m_entryDate;         ///< Date of entry into inventory
    ArticleStatus m_status;          ///< Current operational status
    double m_unitCost;               ///< Base unit cost

public:
    /**
     * @brief Constructor
     * @param code Unique article code
     * @param type Article type
     * @param entryDate Date of entry (DD/MM/YYYY format)
     * @param status Initial status
     * @param unitCost Base unit cost
     * @throws std::invalid_argument if parameters are invalid
     */
    Articulo(const std::string& code, 
             ArticleType type, 
             const std::string& entryDate,
             ArticleStatus status, 
             double unitCost);
    
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~Articulo() = default;
    
    // Disable copy constructor and assignment for safety
    Articulo(const Articulo&) = delete;
    Articulo& operator=(const Articulo&) = delete;
    
    // Enable move semantics
    Articulo(Articulo&&) = default;
    Articulo& operator=(Articulo&&) = default;
    
    // Accessor methods (const-correct)
    /**
     * @brief Get article code
     * @return Unique article identifier
     */
    const std::string& GetCode() const noexcept { return m_code; }
    
    /**
     * @brief Get article type
     * @return Article type enumeration
     */
    ArticleType GetType() const noexcept { return m_type; }
    
    /**
     * @brief Get entry date
     * @return Date string in DD/MM/YYYY format
     */
    const std::string& GetEntryDate() const noexcept { return m_entryDate; }
    
    /**
     * @brief Get current status
     * @return Article status enumeration
     */
    ArticleStatus GetStatus() const noexcept { return m_status; }
    
    /**
     * @brief Get unit cost
     * @return Base unit cost
     */
    double GetUnitCost() const noexcept { return m_unitCost; }
    
    // Mutator methods with validation
    /**
     * @brief Set article status
     * @param newStatus New status to set
     */
    void SetStatus(ArticleStatus newStatus) noexcept { m_status = newStatus; }
    
    /**
     * @brief Set unit cost with validation
     * @param newCost New unit cost
     * @throws std::invalid_argument if cost is invalid
     */
    void SetUnitCost(double newCost);
    
    // Pure virtual methods for polymorphism
    /**
     * @brief Get detailed article information
     * @return Formatted string with article details
     */
    virtual std::string GetDetailedInfo() const = 0;
    
    /**
     * @brief Calculate total cost including any additional fees
     * @return Total cost of the article
     */
    virtual double CalculateTotalCost() const;
    
    // Static utility methods for enum conversions
    /**
     * @brief Convert article type to string representation
     * @param type Article type enumeration
     * @return String representation
     */
    static std::string TypeToString(ArticleType type);
    
    /**
     * @brief Convert article status to string representation
     * @param status Article status enumeration
     * @return String representation
     */
    static std::string StatusToString(ArticleStatus status);
    
    /**
     * @brief Convert string to article type
     * @param str String representation
     * @return Article type enumeration
     * @throws std::invalid_argument if string is invalid
     */
    static ArticleType StringToType(const std::string& str);
    
    /**
     * @brief Convert string to article status
     * @param str String representation
     * @return Article status enumeration
     * @throws std::invalid_argument if string is invalid
     */
    static ArticleStatus StringToStatus(const std::string& str);
    
    // Validation methods
    /**
     * @brief Validate article code format
     * @param code Code to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidCode(const std::string& code);
    
    /**
     * @brief Validate date format (DD/MM/YYYY)
     * @param date Date string to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidDate(const std::string& date);
    
    /**
     * @brief Validate cost value
     * @param cost Cost to validate
     * @return true if valid, false otherwise
     */
    static bool IsValidCost(double cost);

    // Comparison operators for sorting and searching
    bool operator==(const Articulo& other) const;
    bool operator!=(const Articulo& other) const;
    bool operator<(const Articulo& other) const;  // For sorting by code

    // Legacy method names for compatibility (deprecated)
    [[deprecated("Use GetCode() instead")]]
    std::string getCodigo() const { return GetCode(); }
    
    [[deprecated("Use GetType() instead")]]
    ArticleType getTipo() const { return GetType(); }
    
    [[deprecated("Use GetEntryDate() instead")]]
    std::string getFechaIngreso() const { return GetEntryDate(); }
    
    [[deprecated("Use GetStatus() instead")]]
    ArticleStatus getEstado() const { return GetStatus(); }
    
    [[deprecated("Use GetUnitCost() instead")]]
    double getCostoUnitario() const { return GetUnitCost(); }
    
    [[deprecated("Use SetStatus() instead")]]
    void setEstado(ArticleStatus nuevoEstado) { SetStatus(nuevoEstado); }
    
    [[deprecated("Use SetUnitCost() instead")]]
    void setCostoUnitario(double nuevoCosto) { SetUnitCost(nuevoCosto); }
    
    [[deprecated("Use GetDetailedInfo() instead")]]
    virtual std::string getInformacion() const { return GetDetailedInfo(); }
    
    [[deprecated("Use CalculateTotalCost() instead")]]
    virtual double calcularCostoTotal() const { return CalculateTotalCost(); }
    
    [[deprecated("Use TypeToString() instead")]]
    static std::string tipoToString(ArticleType tipo) { return TypeToString(tipo); }
    
    [[deprecated("Use StatusToString() instead")]]
    static std::string estadoToString(ArticleStatus estado) { return StatusToString(estado); }
    
    [[deprecated("Use StringToType() instead")]]
    static ArticleType stringToTipo(const std::string& str) { return StringToType(str); }
    
    [[deprecated("Use StringToStatus() instead")]]
    static ArticleStatus stringToEstado(const std::string& str) { return StringToStatus(str); }

private:
    /**
     * @brief Validate constructor parameters
     * @param code Article code
     * @param entryDate Entry date
     * @param unitCost Unit cost
     * @throws std::invalid_argument if any parameter is invalid
     */
    void ValidateParameters(const std::string& code, 
                           const std::string& entryDate, 
                           double unitCost) const;
};

// Type aliases for convenience
using TipoArticulo = Articulo::ArticleType;  // For compatibility
using EstadoArticulo = Articulo::ArticleStatus;  // For compatibility

#endif // ARTICULO_HPP
