#include "mainframe.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

#ifdef _WIN32
    #include <cstdlib>
    #define CLEAR_SCREEN "cls"
    #define PAUSE_COMMAND "pause"
#else
    #include <cstdlib>
    #define CLEAR_SCREEN "clear"
    #define PAUSE_COMMAND "read -p 'Presione Enter para continuar...' dummy"
#endif

MainFrame::MainFrame() : ejecutando(true) {
    // Constructor
}

void MainFrame::ejecutar() {
    limpiarPantalla();
    mostrarTitulo();
    
    std::cout << "\n¡Bienvenido al Sistema de Inventario de Clínica Vida Plena!\n\n";
    std::cout << "¿Desea cargar datos de prueba? (s/n): ";
    
    std::string respuesta;
    std::getline(std::cin, respuesta);
    
    if (respuesta == "s" || respuesta == "S" || respuesta == "si" || respuesta == "SI") {
        cargarDatosDePrueba();
        std::cout << "\nDatos de prueba cargados exitosamente!\n";
        pausar();
    }
    
    while (ejecutando) {
        limpiarPantalla();
        mostrarMenu();
        
        int opcion = obtenerEnteroValido("Seleccione una opción: ", 0, 12);
        procesarOpcion(opcion);
    }
}

void MainFrame::mostrarTitulo() {
    std::cout << "===============================================\n";
    std::cout << "    CLÍNICA VIDA PLENA - INVENTARIO MÉDICO    \n";
    std::cout << "===============================================\n";
}

void MainFrame::mostrarSeparador() {
    std::cout << "-----------------------------------------------\n";
}

void MainFrame::mostrarMenu() {
    mostrarTitulo();
    std::cout << "\n📋 MENÚ PRINCIPAL:\n\n";
    std::cout << "1️⃣  Ingresar nuevo artículo\n";
    std::cout << "2️⃣  Mostrar equipos médicos por marca y área\n";
    std::cout << "3️⃣  Mostrar artículos dañados por tipo\n";
    std::cout << "4️⃣  Calcular costos por categoría\n";
    std::cout << "5️⃣  Mostrar costos más alto y más bajo\n";
    std::cout << "6️⃣  Técnico con más equipos asignados\n";
    std::cout << "7️⃣  Valores con plus para mobiliario\n";
    std::cout << "8️⃣  Mostrar todos los artículos\n";
    std::cout << "9️⃣  Buscar artículo por código\n";
    std::cout << "🔟  Mostrar estadísticas generales\n";
    std::cout << "1️⃣1️⃣ Cargar datos de prueba\n";
    std::cout << "0️⃣  Salir\n";
    mostrarSeparador();
}

void MainFrame::procesarOpcion(int opcion) {
    limpiarPantalla();
    
    switch (opcion) {
        case 1:
            ingresarNuevoArticulo();
            break;
        case 2:
            mostrarEquiposPorMarcaYArea();
            break;
        case 3:
            mostrarArticulosDanados();
            break;
        case 4:
            mostrarCostosPorCategoria();
            break;
        case 5:
            mostrarCostosMinMax();
            break;
        case 6:
            mostrarTecnicoConMasEquipos();
            break;
        case 7:
            mostrarValoresConPlus();
            break;
        case 8:
            mostrarTodosLosArticulos();
            break;
        case 9:
            buscarArticuloPorCodigo();
            break;
        case 10:
            mostrarEstadisticas();
            break;
        case 11:
            cargarDatosDePrueba();
            std::cout << "\n✅ Datos de prueba cargados exitosamente!\n";
            break;
        case 0:
            std::cout << "¡Gracias por usar el Sistema de Inventario de Clínica Vida Plena!\n";
            std::cout << "¡Hasta pronto! 👋\n";
            ejecutando = false;
            return;
        default:
            std::cout << "❌ Opción inválida. Por favor, seleccione una opción válida.\n";
            break;
    }
    
    if (ejecutando) {
        pausar();
    }
}

void MainFrame::ingresarNuevoArticulo() {
    mostrarTitulo();
    std::cout << "\n📝 INGRESAR NUEVO ARTÍCULO\n\n";
    
    std::cout << "Seleccione el tipo de artículo:\n";
    std::cout << "1. Equipo Médico\n";
    std::cout << "2. Mobiliario Clínico\n";
    
    int tipo = obtenerEnteroValido("Opción: ", 1, 2);
    
    if (tipo == 1) {
        ingresarEquipoMedico();
    } else {
        ingresarMobiliarioClinico();
    }
}

void MainFrame::ingresarEquipoMedico() {
    limpiarPantalla();
    mostrarTitulo();
    std::cout << "\n🏥 INGRESAR EQUIPO MÉDICO\n\n";
    
    std::string codigo, fecha, tecnico;
    EstadoArticulo estado;
    double costo;
    MarcaEquipo marca;
    AreaUso area;
    int vidaUtil;
    
    // Obtener datos básicos
    do {
        codigo = obtenerEntrada("Código único: ");
        if (inventario.existeCodigo(codigo)) {
            std::cout << "❌ El código ya existe. Ingrese uno diferente.\n";
        }
    } while (inventario.existeCodigo(codigo));
    
    fecha = obtenerEntrada("Fecha de ingreso (DD/MM/AAAA): ");
    
    // Estado
    std::cout << "\nEstado del equipo:\n";
    std::cout << "1. Operativo\n2. En Revisión\n3. Dañado\n";
    int estadoOp = obtenerEnteroValido("Seleccione estado: ", 1, 3);
    switch (estadoOp) {
        case 1: estado = EstadoArticulo::OPERATIVO; break;
        case 2: estado = EstadoArticulo::EN_REVISION; break;
        case 3: estado = EstadoArticulo::DANADO; break;
    }
    
    costo = obtenerDoubleValido("Costo unitario ($): ");
    
    // Marca
    std::cout << "\nMarca del equipo:\n";
    std::cout << "1. Philips\n2. GE\n3. Mindray\n4. Otros\n";
    int marcaOp = obtenerEnteroValido("Seleccione marca: ", 1, 4);
    switch (marcaOp) {
        case 1: marca = MarcaEquipo::PHILIPS; break;
        case 2: marca = MarcaEquipo::GE; break;
        case 3: marca = MarcaEquipo::MINDRAY; break;
        case 4: marca = MarcaEquipo::OTROS; break;
    }
    
    vidaUtil = obtenerEnteroValido("Vida útil en años: ", 1, 50);
    tecnico = obtenerEntrada("Técnico asignado: ");
    
    // Área de uso
    std::cout << "\nÁrea de uso:\n";
    std::cout << "1. Emergencia\n2. Pediatría\n3. Quirófano\n";
    int areaOp = obtenerEnteroValido("Seleccione área: ", 1, 3);
    switch (areaOp) {
        case 1: area = AreaUso::EMERGENCIA; break;
        case 2: area = AreaUso::PEDIATRIA; break;
        case 3: area = AreaUso::QUIROFANO; break;
    }
    
    // Crear y agregar el equipo
    auto equipo = std::make_unique<EquipoMedico>(codigo, fecha, estado, costo, marca, vidaUtil, tecnico, area);
    inventario.agregarArticulo(std::move(equipo));
    
    std::cout << "\n✅ Equipo médico agregado exitosamente!\n";
}

void MainFrame::ingresarMobiliarioClinico() {
    limpiarPantalla();
    mostrarTitulo();
    std::cout << "\n🪑 INGRESAR MOBILIARIO CLÍNICO\n\n";
    
    std::string codigo, fecha, material;
    EstadoArticulo estado;
    double costo;
    AreaUbicacion area;
    
    // Obtener datos básicos
    do {
        codigo = obtenerEntrada("Código único: ");
        if (inventario.existeCodigo(codigo)) {
            std::cout << "❌ El código ya existe. Ingrese uno diferente.\n";
        }
    } while (inventario.existeCodigo(codigo));
    
    fecha = obtenerEntrada("Fecha de ingreso (DD/MM/AAAA): ");
    
    // Estado
    std::cout << "\nEstado del mobiliario:\n";
    std::cout << "1. Operativo\n2. En Revisión\n3. Dañado\n";
    int estadoOp = obtenerEnteroValido("Seleccione estado: ", 1, 3);
    switch (estadoOp) {
        case 1: estado = EstadoArticulo::OPERATIVO; break;
        case 2: estado = EstadoArticulo::EN_REVISION; break;
        case 3: estado = EstadoArticulo::DANADO; break;
    }
    
    costo = obtenerDoubleValido("Costo unitario ($): ");
    material = obtenerEntrada("Material: ");
    
    // Área de ubicación
    std::cout << "\nÁrea de ubicación:\n";
    std::cout << "1. Consulta (+$200)\n2. Emergencia (+$300)\n3. Quirófano (+$500)\n";
    int areaOp = obtenerEnteroValido("Seleccione área: ", 1, 3);
    switch (areaOp) {
        case 1: area = AreaUbicacion::CONSULTA; break;
        case 2: area = AreaUbicacion::EMERGENCIA; break;
        case 3: area = AreaUbicacion::QUIROFANO; break;
    }
    
    // Crear y agregar el mobiliario
    auto mobiliario = std::make_unique<MobiliarioClinico>(codigo, fecha, estado, costo, material, area);
    inventario.agregarArticulo(std::move(mobiliario));
    
    std::cout << "\n✅ Mobiliario clínico agregado exitosamente!\n";
}

void MainFrame::mostrarEquiposPorMarcaYArea() {
    mostrarTitulo();
    std::cout << "\n🏥 EQUIPOS MÉDICOS AGRUPADOS POR MARCA Y ÁREA\n\n";
    
    auto agrupados = inventario.agruparEquiposPorMarcaYArea();
    
    if (agrupados.empty()) {
        std::cout << "📭 No hay equipos médicos registrados.\n";
        return;
    }
    
    for (const auto& [clave, equipos] : agrupados) {
        std::cout << "🔹 " << EquipoMedico::marcaToString(clave.first) 
                  << " - " << EquipoMedico::areaToString(clave.second) 
                  << " (" << equipos.size() << " equipos):\n";
        
        for (const auto& equipo : equipos) {
            std::cout << "   • " << equipo->getCodigo() 
                      << " - " << Articulo::estadoToString(equipo->getEstado())
                      << " - $" << std::fixed << std::setprecision(2) << equipo->getCostoUnitario()
                      << " - Técnico: " << equipo->getTecnicoAsignado() << "\n";
        }
        std::cout << "\n";
    }
}

void MainFrame::mostrarArticulosDanados() {
    mostrarTitulo();
    std::cout << "\n🔧 ARTÍCULOS DAÑADOS POR TIPO\n\n";
    
    auto danadosPorTipo = inventario.agruparDanadosPorTipo();
    
    if (danadosPorTipo.empty()) {
        std::cout << "✅ No hay artículos dañados registrados.\n";
        return;
    }
    
    for (const auto& [tipo, articulos] : danadosPorTipo) {
        std::cout << "🔹 " << Articulo::tipoToString(tipo) 
                  << " (" << articulos.size() << " artículos dañados):\n";
        
        for (const auto& articulo : articulos) {
            std::cout << "   • " << articulo->getCodigo() 
                      << " - $" << std::fixed << std::setprecision(2) << articulo->getCostoUnitario()
                      << " - Fecha: " << articulo->getFechaIngreso() << "\n";
        }
        std::cout << "\n";
    }
}

void MainFrame::mostrarCostosPorCategoria() {
    mostrarTitulo();
    std::cout << "\n💰 COSTOS TOTALES POR CATEGORÍA\n\n";
    
    auto costos = inventario.calcularCostosPorCategoria();
    double total = 0.0;
    
    for (const auto& [tipo, costo] : costos) {
        std::cout << "🔹 " << Articulo::tipoToString(tipo) 
                  << ": $" << std::fixed << std::setprecision(2) << costo << "\n";
        total += costo;
    }
    
    mostrarSeparador();
    std::cout << "💵 TOTAL GENERAL: $" << std::fixed << std::setprecision(2) << total << "\n";
}

void MainFrame::limpiarPantalla() {
    system(CLEAR_SCREEN);
}

void MainFrame::pausar() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::string MainFrame::obtenerEntrada(const std::string& prompt) {
    std::string entrada;
    std::cout << prompt;
    std::getline(std::cin, entrada);
    return entrada;
}

int MainFrame::obtenerEnteroValido(const std::string& prompt, int min, int max) {
    int valor;
    std::string entrada;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entrada);
        
        std::stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor >= min && valor <= max) {
            return valor;
        }
        
        std::cout << "❌ Por favor, ingrese un número válido entre " << min << " y " << max << ".\n";
    }
}

double MainFrame::obtenerDoubleValido(const std::string& prompt) {
    double valor;
    std::string entrada;
    
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entrada);
        
        std::stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor >= 0.0) {
            return valor;
        }
        
        std::cout << "❌ Por favor, ingrese un número válido mayor o igual a 0.\n";
    }
}

void MainFrame::mostrarCostosMinMax() {
    mostrarTitulo();
    std::cout << "\n📊 COSTOS MÁS ALTO Y MÁS BAJO\n\n";
    
    if (inventario.obtenerCantidadTotal() == 0) {
        std::cout << "📭 No hay artículos registrados.\n";
        return;
    }
    
    auto [minCosto, maxCosto] = inventario.obtenerCostosMinMax();
    auto* articuloMasCaro = inventario.obtenerArticuloMasCaro();
    auto* articuloMasBarato = inventario.obtenerArticuloMasBarato();
    
    std::cout << "💰 ARTÍCULO MÁS CARO:\n";
    if (articuloMasCaro) {
        std::cout << "   • Código: " << articuloMasCaro->getCodigo() << "\n";
        std::cout << "   • Tipo: " << Articulo::tipoToString(articuloMasCaro->getTipo()) << "\n";
        std::cout << "   • Costo: $" << std::fixed << std::setprecision(2) << maxCosto << "\n";
    }
    
    std::cout << "\n💸 ARTÍCULO MÁS BARATO:\n";
    if (articuloMasBarato) {
        std::cout << "   • Código: " << articuloMasBarato->getCodigo() << "\n";
        std::cout << "   • Tipo: " << Articulo::tipoToString(articuloMasBarato->getTipo()) << "\n";
        std::cout << "   • Costo: $" << std::fixed << std::setprecision(2) << minCosto << "\n";
    }
    
    std::cout << "\n📈 DIFERENCIA: $" << std::fixed << std::setprecision(2) << (maxCosto - minCosto) << "\n";
}

void MainFrame::mostrarTecnicoConMasEquipos() {
    mostrarTitulo();
    std::cout << "\n👨‍🔧 TÉCNICO CON MÁS EQUIPOS ASIGNADOS\n\n";
    
    auto conteo = inventario.contarEquiposPorTecnico();
    
    if (conteo.empty()) {
        std::cout << "📭 No hay equipos médicos con técnicos asignados.\n";
        return;
    }
    
    std::string tecnicoTop = inventario.obtenerTecnicoConMasEquipos();
    
    std::cout << "🏆 TÉCNICO LÍDER: " << tecnicoTop << "\n";
    std::cout << "📊 EQUIPOS ASIGNADOS: " << conteo[tecnicoTop] << "\n\n";
    
    std::cout << "📋 TODOS LOS TÉCNICOS:\n";
    for (const auto& [tecnico, cantidad] : conteo) {
        std::cout << "   • " << tecnico << ": " << cantidad << " equipos\n";
    }
}

void MainFrame::mostrarValoresConPlus() {
    mostrarTitulo();
    std::cout << "\n💰 VALORES CON PLUS PARA MOBILIARIO CLÍNICO\n\n";
    
    auto valoresConPlus = inventario.calcularValoresConPlus();
    
    if (valoresConPlus.empty()) {
        std::cout << "📭 No hay mobiliario clínico registrado.\n";
        return;
    }
    
    double totalMobiliario = 0.0;
    
    for (const auto& [mobiliario, valorConPlus] : valoresConPlus) {
        std::cout << "🔹 " << mobiliario->getCodigo() << " (" 
                  << MobiliarioClinico::areaUbicacionToString(mobiliario->getAreaUbicacion()) << ")\n";
        std::cout << "   • Costo base: $" << std::fixed << std::setprecision(2) 
                  << mobiliario->getCostoUnitario() << "\n";
        std::cout << "   • Plus área: $" << std::fixed << std::setprecision(2) 
                  << mobiliario->calcularPlusPorArea() << "\n";
        std::cout << "   • Valor total: $" << std::fixed << std::setprecision(2) 
                  << valorConPlus << "\n";
        std::cout << "   • Material: " << mobiliario->getMaterial() << "\n\n";
        
        totalMobiliario += valorConPlus;
    }
    
    mostrarSeparador();
    std::cout << "💵 VALOR TOTAL DEL MOBILIARIO: $" << std::fixed << std::setprecision(2) 
              << totalMobiliario << "\n";
}

void MainFrame::mostrarTodosLosArticulos() {
    mostrarTitulo();
    std::cout << "\n📋 TODOS LOS ARTÍCULOS DEL INVENTARIO\n\n";
    
    auto articulos = inventario.obtenerTodosLosArticulos();
    
    if (articulos.empty()) {
        std::cout << "📭 No hay artículos registrados en el inventario.\n";
        return;
    }
    
    int contador = 1;
    for (const auto& articulo : articulos) {
        std::cout << "[" << contador++ << "] ";
        std::cout << articulo->getCodigo() << " - "
                  << Articulo::tipoToString(articulo->getTipo()) << " - "
                  << Articulo::estadoToString(articulo->getEstado()) << " - $"
                  << std::fixed << std::setprecision(2) << articulo->getCostoUnitario() << "\n";
    }
    
    std::cout << "\n📊 Total de artículos: " << articulos.size() << "\n";
}

void MainFrame::buscarArticuloPorCodigo() {
    mostrarTitulo();
    std::cout << "\n🔍 BUSCAR ARTÍCULO POR CÓDIGO\n\n";
    
    std::string codigo = obtenerEntrada("Ingrese el código a buscar: ");
    
    auto* articulo = inventario.buscarPorCodigo(codigo);
    
    if (articulo == nullptr) {
        std::cout << "❌ No se encontró ningún artículo con el código: " << codigo << "\n";
        return;
    }
    
    std::cout << "✅ Artículo encontrado:\n\n";
    std::cout << articulo->getInformacion() << "\n";
}

void MainFrame::mostrarEstadisticas() {
    mostrarTitulo();
    std::cout << "\n📊 ESTADÍSTICAS GENERALES DEL INVENTARIO\n\n";
    
    size_t totalArticulos = inventario.obtenerCantidadTotal();
    
    if (totalArticulos == 0) {
        std::cout << "📭 No hay artículos registrados.\n";
        return;
    }
    
    // Estadísticas por tipo
    size_t equiposMedicos = inventario.obtenerCantidadPorTipo(TipoArticulo::EQUIPO_MEDICO);
    size_t mobiliario = inventario.obtenerCantidadPorTipo(TipoArticulo::MOBILIARIO_CLINICO);
    
    // Estadísticas por estado
    size_t operativos = inventario.obtenerCantidadPorEstado(EstadoArticulo::OPERATIVO);
    size_t enRevision = inventario.obtenerCantidadPorEstado(EstadoArticulo::EN_REVISION);
    size_t danados = inventario.obtenerCantidadPorEstado(EstadoArticulo::DANADO);
    
    // Costos
    auto costos = inventario.calcularCostosPorCategoria();
    auto [minCosto, maxCosto] = inventario.obtenerCostosMinMax();
    
    std::cout << "📈 RESUMEN GENERAL:\n";
    std::cout << "   • Total de artículos: " << totalArticulos << "\n\n";
    
    std::cout << "📦 POR TIPO:\n";
    std::cout << "   • Equipos médicos: " << equiposMedicos 
              << " (" << std::fixed << std::setprecision(1) 
              << (100.0 * equiposMedicos / totalArticulos) << "%)\n";
    std::cout << "   • Mobiliario clínico: " << mobiliario 
              << " (" << std::fixed << std::setprecision(1) 
              << (100.0 * mobiliario / totalArticulos) << "%)\n\n";
    
    std::cout << "🔧 POR ESTADO:\n";
    std::cout << "   • Operativos: " << operativos 
              << " (" << std::fixed << std::setprecision(1) 
              << (100.0 * operativos / totalArticulos) << "%)\n";
    std::cout << "   • En revisión: " << enRevision 
              << " (" << std::fixed << std::setprecision(1) 
              << (100.0 * enRevision / totalArticulos) << "%)\n";
    std::cout << "   • Dañados: " << danados 
              << " (" << std::fixed << std::setprecision(1) 
              << (100.0 * danados / totalArticulos) << "%)\n\n";
    
    std::cout << "💰 COSTOS:\n";
    for (const auto& [tipo, costo] : costos) {
        std::cout << "   • " << Articulo::tipoToString(tipo) 
                  << ": $" << std::fixed << std::setprecision(2) << costo << "\n";
    }
    
    double totalCostos = costos[TipoArticulo::EQUIPO_MEDICO] + costos[TipoArticulo::MOBILIARIO_CLINICO];
    std::cout << "   • Total general: $" << std::fixed << std::setprecision(2) << totalCostos << "\n";
    std::cout << "   • Costo promedio: $" << std::fixed << std::setprecision(2) 
              << (totalCostos / totalArticulos) << "\n";
    std::cout << "   • Rango: $" << std::fixed << std::setprecision(2) << minCosto 
              << " - $" << maxCosto << "\n";
}

void MainFrame::cargarDatosDePrueba() {
    // Equipos médicos
    auto equipo1 = std::make_unique<EquipoMedico>(
        "EQ001", "15/01/2023", EstadoArticulo::OPERATIVO, 15000.0,
        MarcaEquipo::PHILIPS, 10, "Dr. García", AreaUso::EMERGENCIA
    );
    
    auto equipo2 = std::make_unique<EquipoMedico>(
        "EQ002", "20/02/2023", EstadoArticulo::EN_REVISION, 8500.0,
        MarcaEquipo::GE, 8, "Dr. García", AreaUso::QUIROFANO
    );
    
    auto equipo3 = std::make_unique<EquipoMedico>(
        "EQ003", "10/03/2023", EstadoArticulo::DANADO, 12000.0,
        MarcaEquipo::MINDRAY, 12, "Téc. López", AreaUso::PEDIATRIA
    );
    
    auto equipo4 = std::make_unique<EquipoMedico>(
        "EQ004", "05/04/2023", EstadoArticulo::OPERATIVO, 25000.0,
        MarcaEquipo::PHILIPS, 15, "Dr. García", AreaUso::QUIROFANO
    );
    
    auto equipo5 = std::make_unique<EquipoMedico>(
        "EQ005", "12/05/2023", EstadoArticulo::OPERATIVO, 9800.0,
        MarcaEquipo::OTROS, 6, "Téc. Martínez", AreaUso::EMERGENCIA
    );
    
    // Mobiliario clínico
    auto mobiliario1 = std::make_unique<MobiliarioClinico>(
        "MOB001", "08/01/2023", EstadoArticulo::OPERATIVO, 1500.0,
        "Acero inoxidable", AreaUbicacion::QUIROFANO
    );
    
    auto mobiliario2 = std::make_unique<MobiliarioClinico>(
        "MOB002", "15/02/2023", EstadoArticulo::DANADO, 800.0,
        "Aluminio", AreaUbicacion::CONSULTA
    );
    
    auto mobiliario3 = std::make_unique<MobiliarioClinico>(
        "MOB003", "22/03/2023", EstadoArticulo::OPERATIVO, 2200.0,
        "Fibra de carbono", AreaUbicacion::EMERGENCIA
    );
    
    auto mobiliario4 = std::make_unique<MobiliarioClinico>(
        "MOB004", "30/04/2023", EstadoArticulo::EN_REVISION, 1200.0,
        "Plástico médico", AreaUbicacion::CONSULTA
    );
    
    // Agregar todos los artículos al inventario
    inventario.agregarArticulo(std::move(equipo1));
    inventario.agregarArticulo(std::move(equipo2));
    inventario.agregarArticulo(std::move(equipo3));
    inventario.agregarArticulo(std::move(equipo4));
    inventario.agregarArticulo(std::move(equipo5));
    inventario.agregarArticulo(std::move(mobiliario1));
    inventario.agregarArticulo(std::move(mobiliario2));
    inventario.agregarArticulo(std::move(mobiliario3));
    inventario.agregarArticulo(std::move(mobiliario4));
}

bool MainFrame::validarCodigo(const std::string& codigo) {
    return !codigo.empty() && codigo.length() <= 20;
}

bool MainFrame::validarFecha(const std::string& fecha) {
    // Validación básica de formato DD/MM/AAAA
    return fecha.length() == 10 && fecha[2] == '/' && fecha[5] == '/';
}
