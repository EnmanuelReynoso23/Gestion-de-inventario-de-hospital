/**
 * @file GuiMainFrame.cpp
 * @brief Implementation of the main GUI window for Medical Inventory Management System
 * @author Medical Inventory Team
 * @date 2025
 */

#include "../include/GuiMainFrame.hpp"
#include "../include/equipo_medico.hpp"
#include "../include/mobiliario_clinico.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <memory>

using namespace MedicalInventory::UI::Constants;

// Constructor por defecto
GuiMainFrame::GuiMainFrame() {
    // Inicialización se hace en Create()
}

// Constructor con instancia
GuiMainFrame::GuiMainFrame(HINSTANCE hInstance) {
    m_components.instance = hInstance;
}

// Destructor
GuiMainFrame::~GuiMainFrame() {
    Shutdown();
}

// Crear y inicializar la ventana principal
bool GuiMainFrame::Create(HINSTANCE hInstance, const char* title, int nCmdShow) {
    m_components.instance = hInstance;
    
    if (!RegisterWindowClass()) {
        return false;
    }
    
    if (!CreateMainWindow()) {
        return false;
    }
    
    if (!CreateMenuBar()) {
        return false;
    }
    
    if (!CreateControls()) {
        return false;
    }
    
    // Cargar datos de prueba automáticamente
    LoadTestData();
    SetupGeneralView();
    
    // Mostrar la ventana
    ShowWindow(m_components.mainWindow, nCmdShow);
    UpdateWindow(m_components.mainWindow);
    
    m_state.isInitialized = true;
    UpdateStatusBar("Aplicación iniciada correctamente - " + std::to_string(m_inventory.obtenerCantidadTotal()) + " artículos cargados");
    
    return true;
}

// Registrar la clase de ventana
bool GuiMainFrame::RegisterWindowClass() {
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_components.instance;
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_CLASS_NAME;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    
    return RegisterClassExW(&wcex) != 0;
}

// Crear la ventana principal
bool GuiMainFrame::CreateMainWindow() {
    m_components.mainWindow = CreateWindowExW(
        0,
        WINDOW_CLASS_NAME,
        WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
        nullptr,
        nullptr,
        m_components.instance,
        this
    );
    
    return m_components.mainWindow != nullptr;
}

// Crear la barra de menú
bool GuiMainFrame::CreateMenuBar() {
    HMENU hMenuBar = CreateMenu();
    if (!hMenuBar) return false;
    
    // Menú Archivo
    HMENU hFileMenu = CreateFileMenu();
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"&Archivo");
    
    // Menú Ver
    HMENU hViewMenu = CreateViewMenu();
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hViewMenu, L"&Ver");
    
    // Menú Reportes
    HMENU hReportsMenu = CreateReportsMenu();
    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hReportsMenu, L"&Reportes");
    
    return SetMenu(m_components.mainWindow, hMenuBar) != 0;
}

// Crear menú Archivo
HMENU GuiMainFrame::CreateFileMenu() {
    HMENU hMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING, MENU_FILE_ADD_ARTICLE, L"&Agregar Artículo...");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(hMenu, MF_STRING, MENU_FILE_LOAD_TEST_DATA, L"&Cargar Datos de Prueba");
    AppendMenuW(hMenu, MF_STRING, MENU_FILE_EXPORT, L"&Exportar Datos...");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(hMenu, MF_STRING, MENU_FILE_EXIT, L"&Salir");
    return hMenu;
}

// Crear menú Ver
HMENU GuiMainFrame::CreateViewMenu() {
    HMENU hMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING, MENU_VIEW_EQUIPMENT_BY_BRAND, L"Equipos por &Marca y Área");
    AppendMenuW(hMenu, MF_STRING, MENU_VIEW_DAMAGED_ARTICLES, L"Artículos &Dañados");
    AppendMenuW(hMenu, MF_STRING, MENU_VIEW_TECHNICIANS, L"&Técnicos con Equipos");
    return hMenu;
}

// Crear menú Reportes
HMENU GuiMainFrame::CreateReportsMenu() {
    HMENU hMenu = CreatePopupMenu();
    AppendMenuW(hMenu, MF_STRING, MENU_REPORTS_COSTS_BY_CATEGORY, L"&Costos por Categoría");
    AppendMenuW(hMenu, MF_STRING, MENU_REPORTS_MIN_MAX_COSTS, L"Costos &Mínimo y Máximo");
    AppendMenuW(hMenu, MF_STRING, MENU_REPORTS_PLUS_VALUES, L"Valores con &Plus (Mobiliario)");
    return hMenu;
}

// Crear controles
bool GuiMainFrame::CreateControls() {
    if (!CreateListView()) return false;
    if (!CreateStatusBar()) return false;
    return true;
}

// Crear ListView
bool GuiMainFrame::CreateListView() {
    m_components.listView = CreateWindowExW(
        0,
        WC_LISTVIEWW,
        L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
        10, 10, DEFAULT_WINDOW_WIDTH - 40, DEFAULT_WINDOW_HEIGHT - 100,
        m_components.mainWindow,
        (HMENU)CONTROL_LISTVIEW,
        m_components.instance,
        nullptr
    );
    
    if (!m_components.listView) return false;
    
    // Establecer estilo extendido
    ListView_SetExtendedListViewStyle(m_components.listView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    
    return true;
}

// Crear StatusBar
bool GuiMainFrame::CreateStatusBar() {
    m_components.statusBar = CreateWindowExW(
        0,
        STATUSCLASSNAMEW,
        L"",
        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
        0, 0, 0, 0,
        m_components.mainWindow,
        (HMENU)CONTROL_STATUS_BAR,
        m_components.instance,
        nullptr
    );
    
    return m_components.statusBar != nullptr;
}

// Procedimiento de ventana estático
LRESULT CALLBACK GuiMainFrame::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    GuiMainFrame* pThis = nullptr;
    
    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (GuiMainFrame*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->m_components.mainWindow = hwnd;
    } else {
        pThis = (GuiMainFrame*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    
    if (pThis) {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

// Manejar mensajes de ventana
LRESULT GuiMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            return HandleCommand(wParam, lParam);
        case WM_SIZE:
            return HandleSize(wParam, lParam);
        case WM_DESTROY:
            return HandleDestroy();
        default:
            return DefWindowProcW(m_components.mainWindow, uMsg, wParam, lParam);
    }
}

// Manejar comandos de menú
LRESULT GuiMainFrame::HandleCommand(WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    
    switch (LOWORD(wParam)) {
        case MENU_FILE_ADD_ARTICLE:
            OnAddArticle();
            break;
        case MENU_FILE_LOAD_TEST_DATA:
            OnLoadTestData();
            break;
        case MENU_FILE_EXPORT:
            OnExportData();
            break;
        case MENU_FILE_EXIT:
            OnExit();
            break;
        case MENU_VIEW_EQUIPMENT_BY_BRAND:
            OnShowEquipmentByBrand();
            break;
        case MENU_VIEW_DAMAGED_ARTICLES:
            OnShowDamagedArticles();
            break;
        case MENU_VIEW_TECHNICIANS:
            OnShowTechnicians();
            break;
        case MENU_REPORTS_COSTS_BY_CATEGORY:
            OnShowCostsByCategory();
            break;
        case MENU_REPORTS_MIN_MAX_COSTS:
            OnShowMinMaxCosts();
            break;
        case MENU_REPORTS_PLUS_VALUES:
            OnShowPlusValues();
            break;
        default:
            return DefWindowProcW(m_components.mainWindow, WM_COMMAND, wParam, lParam);
    }
    
    return 0;
}

// Manejar redimensionamiento
LRESULT GuiMainFrame::HandleSize(WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(wParam);
    
    int width = LOWORD(lParam);
    int height = HIWORD(lParam);
    
    // Redimensionar ListView
    if (m_components.listView) {
        SetWindowPos(m_components.listView, nullptr, 
                    10, 10, 
                    width - 20, height - 60, 
                    SWP_NOZORDER);
    }
    
    // Redimensionar StatusBar
    if (m_components.statusBar) {
        SendMessage(m_components.statusBar, WM_SIZE, 0, 0);
    }
    
    return 0;
}

// Manejar destrucción de ventana
LRESULT GuiMainFrame::HandleDestroy() {
    PostQuitMessage(0);
    return 0;
}

// Configurar vista general
void GuiMainFrame::SetupGeneralView() {
    ClearListView();
    
    // Agregar columnas
    AddListViewColumn("Código", COLUMN_WIDTH_CODE);
    AddListViewColumn("Tipo", COLUMN_WIDTH_TYPE);
    AddListViewColumn("Estado", COLUMN_WIDTH_STATUS);
    AddListViewColumn("Costo", COLUMN_WIDTH_COST);
    AddListViewColumn("Fecha", COLUMN_WIDTH_DATE);
    AddListViewColumn("Detalles", COLUMN_WIDTH_DETAILS);
    
    // Agregar datos
    auto articulos = m_inventory.obtenerTodosLosArticulos();
    for (const auto& articulo : articulos) {
        std::vector<std::string> rowData = {
            articulo->GetCode(),
            Articulo::TypeToString(articulo->GetType()),
            Articulo::StatusToString(articulo->GetStatus()),
            FormatCurrency(articulo->GetUnitCost()),
            articulo->GetEntryDate(),
            "Ver detalles..."
        };
        AddListViewRow(rowData);
    }
    
    m_state.currentView = "General";
    UpdateStatusBarWithStats();
}

// Limpiar ListView
void GuiMainFrame::ClearListView() {
    ListView_DeleteAllItems(m_components.listView);
    
    // Eliminar columnas
    while (ListView_DeleteColumn(m_components.listView, 0)) {
        // Continuar eliminando
    }
}

// Agregar columna al ListView
void GuiMainFrame::AddListViewColumn(const std::string& text, int width) {
    LVCOLUMNW lvc = {};
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.cx = width;
    
    std::wstring wtext = StringToWString(text);
    lvc.pszText = const_cast<wchar_t*>(wtext.c_str());
    
    int columnCount = Header_GetItemCount(ListView_GetHeader(m_components.listView));
    lvc.iSubItem = columnCount;
    
    ListView_InsertColumn(m_components.listView, columnCount, &lvc);
}

// Agregar fila al ListView
void GuiMainFrame::AddListViewRow(const std::vector<std::string>& data) {
    if (data.empty()) return;
    
    LVITEMW lvi = {};
    lvi.mask = LVIF_TEXT;
    lvi.iItem = ListView_GetItemCount(m_components.listView);
    lvi.iSubItem = 0;
    
    std::wstring wtext = StringToWString(data[0]);
    lvi.pszText = const_cast<wchar_t*>(wtext.c_str());
    
    int index = ListView_InsertItem(m_components.listView, &lvi);
    
    // Agregar subitems
    for (size_t i = 1; i < data.size(); ++i) {
        std::wstring wsubtext = StringToWString(data[i]);
        ListView_SetItemText(m_components.listView, index, static_cast<int>(i), 
                           const_cast<wchar_t*>(wsubtext.c_str()));
    }
}

// Handlers de menú
void GuiMainFrame::OnAddArticle() {
    ShowInfoMessage("Función de agregar artículo en desarrollo", "Información");
}

void GuiMainFrame::OnLoadTestData() {
    LoadTestData();
    SetupGeneralView();
    UpdateStatusBar("Datos de prueba cargados - " + std::to_string(m_inventory.obtenerCantidadTotal()) + " artículos");
}

void GuiMainFrame::OnExportData() {
    ShowInfoMessage("Función de exportar datos en desarrollo", "Información");
}

void GuiMainFrame::OnExit() {
    PostMessage(m_components.mainWindow, WM_CLOSE, 0, 0);
}

void GuiMainFrame::OnShowEquipmentByBrand() {
    ShowEquipmentByBrandView();
}

void GuiMainFrame::OnShowDamagedArticles() {
    ShowDamagedArticlesView();
}

void GuiMainFrame::OnShowTechnicians() {
    ShowTechniciansView();
}

void GuiMainFrame::OnShowCostsByCategory() {
    ShowCostsByCategoryView();
}

void GuiMainFrame::OnShowMinMaxCosts() {
    ShowMinMaxCostsView();
}

void GuiMainFrame::OnShowPlusValues() {
    ShowPlusValuesView();
}

// Vistas específicas
void GuiMainFrame::ShowEquipmentByBrandView() {
    ClearListView();
    
    AddListViewColumn("Marca", COLUMN_WIDTH_BRAND);
    AddListViewColumn("Área", COLUMN_WIDTH_AREA);
    AddListViewColumn("Código", COLUMN_WIDTH_CODE);
    AddListViewColumn("Estado", COLUMN_WIDTH_STATUS);
    AddListViewColumn("Costo", COLUMN_WIDTH_COST);
    AddListViewColumn("Técnico", COLUMN_WIDTH_TECHNICIAN);
    
    auto agrupados = m_inventory.agruparEquiposPorMarcaYArea();
    for (const auto& [clave, equipos] : agrupados) {
        for (const auto& equipo : equipos) {
            std::vector<std::string> rowData = {
                EquipoMedico::marcaToString(clave.first),
                EquipoMedico::areaToString(clave.second),
                equipo->GetCode(),
                Articulo::StatusToString(equipo->GetStatus()),
                FormatCurrency(equipo->GetUnitCost()),
                equipo->getTecnicoAsignado()
            };
            AddListViewRow(rowData);
        }
    }
    
    m_state.currentView = "Equipos por Marca";
    UpdateStatusBar("Vista: Equipos agrupados por marca y área");
}

void GuiMainFrame::ShowDamagedArticlesView() {
    ClearListView();
    
    AddListViewColumn("Tipo", COLUMN_WIDTH_TYPE);
    AddListViewColumn("Código", COLUMN_WIDTH_CODE);
    AddListViewColumn("Costo", COLUMN_WIDTH_COST);
    AddListViewColumn("Fecha", COLUMN_WIDTH_DATE);
    
    auto danadosPorTipo = m_inventory.agruparDanadosPorTipo();
    int totalDanados = 0;
    
    for (const auto& [tipo, articulos] : danadosPorTipo) {
        for (const auto& articulo : articulos) {
            std::vector<std::string> rowData = {
                Articulo::TypeToString(tipo),
                articulo->GetCode(),
                FormatCurrency(articulo->GetUnitCost()),
                articulo->GetEntryDate()
            };
            AddListViewRow(rowData);
            totalDanados++;
        }
    }
    
    m_state.currentView = "Artículos Dañados";
    UpdateStatusBar("Vista: Artículos dañados - Total: " + std::to_string(totalDanados));
}

void GuiMainFrame::ShowTechniciansView() {
    ClearListView();
    
    AddListViewColumn("Técnico", COLUMN_WIDTH_TECHNICIAN);
    AddListViewColumn("Equipos Asignados", 150);
    
    auto conteo = m_inventory.contarEquiposPorTecnico();
    for (const auto& [tecnico, cantidad] : conteo) {
        std::vector<std::string> rowData = {
            tecnico,
            std::to_string(cantidad)
        };
        AddListViewRow(rowData);
    }
    
    m_state.currentView = "Técnicos";
    UpdateStatusBar("Vista: Técnicos con equipos asignados");
}

void GuiMainFrame::ShowCostsByCategoryView() {
    ClearListView();
    
    AddListViewColumn("Categoría", 200);
    AddListViewColumn("Costo Total", COLUMN_WIDTH_COST);
    AddListViewColumn("Porcentaje", 100);
    
    auto costos = m_inventory.calcularCostosPorCategoria();
    double total = 0.0;
    for (const auto& [tipo, costo] : costos) {
        total += costo;
    }
    
    for (const auto& [tipo, costo] : costos) {
        double porcentaje = (total > 0) ? (costo / total) * 100.0 : 0.0;
        std::vector<std::string> rowData = {
            Articulo::TypeToString(tipo),
            FormatCurrency(costo),
            FormatPercentage(porcentaje)
        };
        AddListViewRow(rowData);
    }
    
    // Agregar total
    std::vector<std::string> totalRow = {
        "TOTAL",
        FormatCurrency(total),
        "100.00%"
    };
    AddListViewRow(totalRow);
    
    m_state.currentView = "Costos por Categoría";
    UpdateStatusBar("Vista: Costos por categoría - Total: " + FormatCurrency(total));
}

void GuiMainFrame::ShowMinMaxCostsView() {
    ClearListView();
    
    AddListViewColumn("Descripción", 200);
    AddListViewColumn("Código", COLUMN_WIDTH_CODE);
    AddListViewColumn("Tipo", COLUMN_WIDTH_TYPE);
    AddListViewColumn("Costo", COLUMN_WIDTH_COST);
    
    if (m_inventory.obtenerCantidadTotal() > 0) {
        auto [minCosto, maxCosto] = m_inventory.obtenerCostosMinMax();
        auto* articuloMasCaro = m_inventory.obtenerArticuloMasCaro();
        auto* articuloMasBarato = m_inventory.obtenerArticuloMasBarato();
        
        if (articuloMasCaro) {
            std::vector<std::string> maxRow = {
                "Más Caro",
                articuloMasCaro->GetCode(),
                Articulo::TypeToString(articuloMasCaro->GetType()),
                FormatCurrency(maxCosto)
            };
            AddListViewRow(maxRow);
        }
        
        if (articuloMasBarato) {
            std::vector<std::string> minRow = {
                "Más Barato",
                articuloMasBarato->GetCode(),
                Articulo::TypeToString(articuloMasBarato->GetType()),
                FormatCurrency(minCosto)
            };
            AddListViewRow(minRow);
        }
        
        std::vector<std::string> diffRow = {
            "Diferencia",
            "-",
            "-",
            FormatCurrency(maxCosto - minCosto)
        };
        AddListViewRow(diffRow);
    }
    
    m_state.currentView = "Costos Min/Max";
    UpdateStatusBar("Vista: Costos mínimo y máximo");
}

void GuiMainFrame::ShowPlusValuesView() {
    ClearListView();
    
    AddListViewColumn("Código", COLUMN_WIDTH_CODE);
    AddListViewColumn("Área", COLUMN_WIDTH_AREA);
    AddListViewColumn("Costo Base", COLUMN_WIDTH_COST);
    AddListViewColumn("Plus", COLUMN_WIDTH_COST);
    AddListViewColumn("Total", COLUMN_WIDTH_COST);
    AddListViewColumn("Material", 150);
    
    auto valoresConPlus = m_inventory.calcularValoresConPlus();
    double totalMobiliario = 0.0;
    
    for (const auto& [mobiliario, valorConPlus] : valoresConPlus) {
        std::vector<std::string> rowData = {
            mobiliario->GetCode(),
            MobiliarioClinico::areaUbicacionToString(mobiliario->getAreaUbicacion()),
            FormatCurrency(mobiliario->GetUnitCost()),
            FormatCurrency(mobiliario->calcularPlusPorArea()),
            FormatCurrency(valorConPlus),
            mobiliario->getMaterial()
        };
        AddListViewRow(rowData);
        totalMobiliario += valorConPlus;
    }
    
    m_state.currentView = "Valores con Plus";
    UpdateStatusBar("Vista: Mobiliario con plus - Total: " + FormatCurrency(totalMobiliario));
}

// Cargar datos de prueba
void GuiMainFrame::LoadTestData() {
    // Limpiar inventario actual
    m_inventory = Inventario();
    
    // Equipos médicos (usando typedef para compatibilidad)
    auto equipo1 = std::make_unique<EquipoMedico>(
        "EQ001", "15/01/2023", Articulo::ArticleStatus::OPERATIONAL, 15000.0,
        MarcaEquipo::PHILIPS, 10, "Dr. García", AreaUso::EMERGENCIA
    );
    
    auto equipo2 = std::make_unique<EquipoMedico>(
        "EQ002", "20/02/2023", Articulo::ArticleStatus::UNDER_REVIEW, 8500.0,
        MarcaEquipo::GE, 8, "Dr. García", AreaUso::QUIROFANO
    );
    
    auto equipo3 = std::make_unique<EquipoMedico>(
        "EQ003", "10/03/2023", Articulo::ArticleStatus::DAMAGED, 12000.0,
        MarcaEquipo::MINDRAY, 12, "Téc. López", AreaUso::PEDIATRIA
    );
    
    auto equipo4 = std::make_unique<EquipoMedico>(
        "EQ004", "05/04/2023", Articulo::ArticleStatus::OPERATIONAL, 25000.0,
        MarcaEquipo::PHILIPS, 15, "Dr. García", AreaUso::QUIROFANO
    );
    
    auto equipo5 = std::make_unique<EquipoMedico>(
        "EQ005", "12/05/2023", Articulo::ArticleStatus::OPERATIONAL, 9800.0,
        MarcaEquipo::OTROS, 6, "Téc. Martínez", AreaUso::EMERGENCIA
    );
    
    // Mobiliario clínico
    auto mobiliario1 = std::make_unique<MobiliarioClinico>(
        "MOB001", "08/01/2023", Articulo::ArticleStatus::OPERATIONAL, 1500.0,
        "Acero inoxidable", AreaUbicacion::QUIROFANO
    );
    
    auto mobiliario2 = std::make_unique<MobiliarioClinico>(
        "MOB002", "15/02/2023", Articulo::ArticleStatus::DAMAGED, 800.0,
        "Aluminio", AreaUbicacion::CONSULTA
    );
    
    auto mobiliario3 = std::make_unique<MobiliarioClinico>(
        "MOB003", "22/03/2023", Articulo::ArticleStatus::OPERATIONAL, 2200.0,
        "Fibra de carbono", AreaUbicacion::EMERGENCIA
    );
    
    auto mobiliario4 = std::make_unique<MobiliarioClinico>(
        "MOB004", "30/04/2023", Articulo::ArticleStatus::UNDER_REVIEW, 1200.0,
        "Plástico médico", AreaUbicacion::CONSULTA
    );
    
    // Agregar todos los artículos al inventario
    m_inventory.agregarArticulo(std::move(equipo1));
    m_inventory.agregarArticulo(std::move(equipo2));
    m_inventory.agregarArticulo(std::move(equipo3));
    m_inventory.agregarArticulo(std::move(equipo4));
    m_inventory.agregarArticulo(std::move(equipo5));
    m_inventory.agregarArticulo(std::move(mobiliario1));
    m_inventory.agregarArticulo(std::move(mobiliario2));
    m_inventory.agregarArticulo(std::move(mobiliario3));
    m_inventory.agregarArticulo(std::move(mobiliario4));
}

// Funciones de utilidad
std::string GuiMainFrame::FormatCurrency(double amount) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << "$" << amount;
    return oss.str();
}

std::string GuiMainFrame::FormatPercentage(double percentage) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << percentage << "%";
    return oss.str();
}

std::wstring GuiMainFrame::StringToWString(const std::string& str) const {
    if (str.empty()) return std::wstring();
    
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring result(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &result[0], size);
    return result;
}

std::string GuiMainFrame::WStringToString(const std::wstring& wstr) const {
    if (wstr.empty()) return std::string();
    
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &result[0], size, nullptr, nullptr);
    return result;
}

void GuiMainFrame::UpdateStatusBar(const std::string& text) {
    if (m_components.statusBar) {
        std::wstring wtext = StringToWString(text);
        SendMessageW(m_components.statusBar, SB_SETTEXTW, 0, (LPARAM)wtext.c_str());
    }
}

void GuiMainFrame::UpdateStatusBarWithStats() {
    size_t total = m_inventory.obtenerCantidadTotal();
    size_t equipos = m_inventory.obtenerCantidadPorTipo(Articulo::ArticleType::MEDICAL_EQUIPMENT);
    size_t mobiliario = m_inventory.obtenerCantidadPorTipo(Articulo::ArticleType::CLINICAL_FURNITURE);
    
    auto costos = m_inventory.calcularCostosPorCategoria();
    double totalCosto = 0.0;
    for (const auto& [tipo, costo] : costos) {
        totalCosto += costo;
    }
    
    std::string status = "Total: " + std::to_string(total) + 
                        " | Equipos: " + std::to_string(equipos) + 
                        " | Mobiliario: " + std::to_string(mobiliario) + 
                        " | Valor: " + FormatCurrency(totalCosto);
    
    UpdateStatusBar(status);
}

void GuiMainFrame::ShowErrorMessage(const std::string& message, const std::string& title) {
    std::wstring wmessage = StringToWString(message);
    std::wstring wtitle = StringToWString(title);
    MessageBoxW(m_components.mainWindow, wmessage.c_str(), wtitle.c_str(), MB_ICONERROR | MB_OK);
}

void GuiMainFrame::ShowInfoMessage(const std::string& message, const std::string& title) {
    std::wstring wmessage = StringToWString(message);
    std::wstring wtitle = StringToWString(title);
    MessageBoxW(m_components.mainWindow, wmessage.c_str(), wtitle.c_str(), MB_ICONINFORMATION | MB_OK);
}

bool GuiMainFrame::ShowConfirmationDialog(const std::string& message, const std::string& title) {
    std::wstring wmessage = StringToWString(message);
    std::wstring wtitle = StringToWString(title);
    int result = MessageBoxW(m_components.mainWindow, wmessage.c_str(), wtitle.c_str(), MB_ICONQUESTION | MB_YESNO);
    return result == IDYES;
}

// Funciones no implementadas (stubs)
bool GuiMainFrame::Initialize() {
    return m_state.isInitialized;
}

int GuiMainFrame::Run() {
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

void GuiMainFrame::Shutdown() {
    if (m_state.isShuttingDown) return;
    
    m_state.isShuttingDown = true;
    m_state.isInitialized = false;
    
    if (m_components.mainWindow) {
        DestroyWindow(m_components.mainWindow);
        m_components.mainWindow = nullptr;
    }
}

bool GuiMainFrame::ValidateInventoryData() const {
    return m_inventory.obtenerCantidadTotal() > 0;
}

// Stubs para procedimientos de diálogo
INT_PTR CALLBACK GuiMainFrame::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(hDlg);
    UNREFERENCED_PARAMETER(message);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);
    return FALSE;
}
