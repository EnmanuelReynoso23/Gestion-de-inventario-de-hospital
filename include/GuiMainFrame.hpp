/**
 * @file GuiMainFrame.hpp
 * @brief Main GUI window class for Medical Inventory Management System
 * @author Medical Inventory Team
 * @date 2025
 */

#ifndef GUI_MAINFRAME_HPP
#define GUI_MAINFRAME_HPP

#include "inventario.hpp"
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace MedicalInventory {
    namespace UI {
        namespace Constants {
            // Window dimensions
            constexpr int DEFAULT_WINDOW_WIDTH = 1200;
            constexpr int DEFAULT_WINDOW_HEIGHT = 800;
            constexpr int STATUS_BAR_HEIGHT = 25;
            
            // Menu item IDs
            constexpr int MENU_FILE_ADD_ARTICLE = 1001;
            constexpr int MENU_FILE_LOAD_TEST_DATA = 1002;
            constexpr int MENU_FILE_EXPORT = 1003;
            constexpr int MENU_FILE_EXIT = 1099;
            
            constexpr int MENU_VIEW_EQUIPMENT_BY_BRAND = 2001;
            constexpr int MENU_VIEW_DAMAGED_ARTICLES = 2002;
            constexpr int MENU_VIEW_TECHNICIANS = 2003;
            
            constexpr int MENU_REPORTS_COSTS_BY_CATEGORY = 3001;
            constexpr int MENU_REPORTS_MIN_MAX_COSTS = 3002;
            constexpr int MENU_REPORTS_PLUS_VALUES = 3003;
            
            // Control IDs
            constexpr int CONTROL_LISTVIEW = 4001;
            constexpr int CONTROL_STATUS_BAR = 4002;
            
            // Column widths
            constexpr int COLUMN_WIDTH_CODE = 100;
            constexpr int COLUMN_WIDTH_TYPE = 120;
            constexpr int COLUMN_WIDTH_STATUS = 100;
            constexpr int COLUMN_WIDTH_COST = 100;
            constexpr int COLUMN_WIDTH_DATE = 100;
            constexpr int COLUMN_WIDTH_DETAILS = 200;
            constexpr int COLUMN_WIDTH_BRAND = 100;
            constexpr int COLUMN_WIDTH_AREA = 100;
            constexpr int COLUMN_WIDTH_TECHNICIAN = 150;
        }
    }
}

/**
 * @brief Main application window class
 * Handles the primary GUI interface for the Medical Inventory System
 */
class GuiMainFrame {
public:
    /**
     * @brief Default constructor
     */
    GuiMainFrame();
    
    /**
     * @brief Constructor with instance handle
     * @param hInstance Application instance handle
     */
    explicit GuiMainFrame(HINSTANCE hInstance);
    
    /**
     * @brief Destructor
     */
    ~GuiMainFrame();
    
    // Disable copy constructor and assignment operator
    GuiMainFrame(const GuiMainFrame&) = delete;
    GuiMainFrame& operator=(const GuiMainFrame&) = delete;
    
    /**
     * @brief Create and initialize the main window
     * @param hInstance Application instance handle
     * @param title Window title
     * @param nCmdShow Window show state
     * @return true if creation successful, false otherwise
     */
    bool Create(HINSTANCE hInstance, const char* title, int nCmdShow);
    
    /**
     * @brief Initialize the application window and controls
     * @return true if initialization successful, false otherwise
     */
    bool Initialize();
    
    /**
     * @brief Run the main message loop
     * @return Application exit code
     */
    int Run();
    
    /**
     * @brief Clean up resources and shutdown
     */
    void Shutdown();

private:
    // Core window components
    struct WindowComponents {
        HWND mainWindow;
        HWND listView;
        HWND statusBar;
        HINSTANCE instance;
        
        WindowComponents() : mainWindow(nullptr), listView(nullptr), 
                           statusBar(nullptr), instance(nullptr) {}
    };
    
    // Application state
    struct ApplicationState {
        bool isInitialized;
        bool isShuttingDown;
        std::string currentView;
        
        ApplicationState() : isInitialized(false), isShuttingDown(false), 
                           currentView("General") {}
    };
    
    WindowComponents m_components;
    ApplicationState m_state;
    Inventario m_inventory;
    
    // Window procedure and message handling
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    
    /**
     * @brief Handle window messages
     */
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleCommand(WPARAM wParam, LPARAM lParam);
    LRESULT HandleSize(WPARAM wParam, LPARAM lParam);
    LRESULT HandleDestroy();
    
    // Window initialization
    bool RegisterWindowClass();
    bool CreateMainWindow();
    bool CreateMenuBar();
    bool CreateControls();
    bool CreateListView();
    bool CreateStatusBar();
    
    // Menu creation helpers
    HMENU CreateFileMenu();
    HMENU CreateViewMenu();
    HMENU CreateReportsMenu();
    
    // ListView management
    void ClearListView();
    void AddListViewColumn(const std::string& text, int width);
    void AddListViewRow(const std::vector<std::string>& data);
    void UpdateListView();
    void SetupGeneralView();
    
    // Status bar management
    void UpdateStatusBar(const std::string& text);
    void UpdateStatusBarWithStats();
    
    // Menu command handlers
    void OnAddArticle();
    void OnLoadTestData();
    void OnExportData();
    void OnExit();
    
    void OnShowEquipmentByBrand();
    void OnShowDamagedArticles();
    void OnShowTechnicians();
    
    void OnShowCostsByCategory();
    void OnShowMinMaxCosts();
    void OnShowPlusValues();
    
    // View management
    void ShowEquipmentByBrandView();
    void ShowDamagedArticlesView();
    void ShowTechniciansView();
    void ShowCostsByCategoryView();
    void ShowMinMaxCostsView();
    void ShowPlusValuesView();
    
    // Data management
    void LoadTestData();
    bool ValidateInventoryData() const;
    
    // Utility functions
    std::string FormatCurrency(double amount) const;
    std::string FormatPercentage(double percentage) const;
    std::wstring StringToWString(const std::string& str) const;
    std::string WStringToString(const std::wstring& wstr) const;
    
    // Error handling
    void ShowErrorMessage(const std::string& message, const std::string& title = "Error");
    void ShowInfoMessage(const std::string& message, const std::string& title = "Information");
    bool ShowConfirmationDialog(const std::string& message, const std::string& title = "Confirm");
    
    // Constants
    static constexpr const wchar_t* WINDOW_CLASS_NAME = L"MedicalInventoryMainWindow";
    static constexpr const wchar_t* WINDOW_TITLE = L"Medical Inventory Management - Clínica Vida Plena";
};

#endif // GUI_MAINFRAME_HPP
