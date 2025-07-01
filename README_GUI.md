# Sistema de Inventario Médico - Clínica Vida Plena

## Versión con Interfaz Gráfica

### 📋 Descripción

Sistema mejorado de inventario médico con interfaz gráfica nativa de Windows que implementa todas las funcionalidades requeridas (a-g) con visualización profesional.

### 🚀 Características Principales

#### ✅ **Funcionalidades Core (Requisitos a-g):**

- **a)** Ingresar nuevos artículos (Equipos médicos y Mobiliario clínico)
- **b)** Mostrar equipos médicos agrupados por marca y área
- **c)** Mostrar artículos dañados por tipo
- **d)** Calcular costo total por categoría
- **e)** Calcular costo más alto y más bajo
- **f)** Mostrar técnico con más equipos asignados
- **g)** Calcular valor con plus para mobiliario

#### 🎨 **Mejoras Visuales:**

- Interfaz gráfica nativa con Windows API
- Menús organizados y fáciles de usar
- Tablas interactivas con columnas ordenables
- Barra de estado con información contextual
- Ventana redimensionable y profesional

### 🛠️ Compilación y Ejecución

#### **Opción 1: Versión GUI (Recomendada)**

```batch
# Compilar la versión con interfaz gráfica
compilar_gui.bat

# Ejecutar
inventario_medico_gui.exe
```

#### **Opción 2: Versión Consola (Original)**

```batch
# Compilar la versión de consola original
compilar.bat

# Ejecutar
inventario_gui.exe
```

### 📁 Estructura del Proyecto

```text
proyecto/
├── src/                     # Código fuente
│   ├── articulo.cpp         # Clase base Artículo
│   ├── equipo_medico.cpp    # Clase EquipoMedico
│   ├── mobiliario_clinico.cpp # Clase MobiliarioClinico
│   ├── inventario.cpp       # Lógica de inventario
│   ├── main.cpp            # Main consola (original)
│   ├── main_gui.cpp        # Main GUI (nuevo)
│   └── GuiMainFrame.cpp    # Interfaz gráfica (nuevo)
├── include/                 # Headers
│   ├── articulo.hpp
│   ├── equipo_medico.hpp
│   ├── mobiliario_clinico.hpp
│   ├── inventario.hpp
│   └── GuiMainFrame.hpp    # Header GUI (nuevo)
├── obj/                    # Archivos objeto (auto-generado)
├── libs/                   # Librerías (preparado para expansión)
├── gui/                    # Interfaz consola original
├── compilar.bat           # Script consola
├── compilar_gui.bat       # Script GUI (nuevo)
└── README_GUI.md          # Esta documentación
```

### 🎯 Cómo Usar la Aplicación GUI

#### **1. Inicio Rápido:**

1. Ejecute `compilar_gui.bat`
2. Cuando aparezca la ventana, vaya a **Archivo → Cargar Datos de Prueba**
3. Explore las diferentes opciones del menú

#### **2. Navegación por Menús:**

**📂 Menú Archivo:**

- **Agregar Artículo**: Formulario para nuevos artículos
- **Cargar Datos de Prueba**: Carga ejemplos predefinidos
- **Salir**: Cerrar aplicación

**👁️ Menú Ver:**

- **Equipos por Marca y Área**: Agrupación visual de equipos
- **Artículos Dañados**: Lista filtrada por estado dañado
- **Técnicos**: Ranking de técnicos por equipos asignados

**📊 Menú Reportes:**

- **Costos por Categoría**: Análisis financiero con porcentajes
- **Costos Mín/Máx**: Comparativa de artículos extremos
- **Valores con Plus**: Cálculo de plus para mobiliario

#### **3. Funcionalidades de la Tabla:**

- **Redimensionar columnas**: Arrastre los bordes
- **Ordenar**: Click en los headers de columna
- **Información contextual**: Vea la barra de estado

### 💡 Datos de Prueba Incluidos

El sistema incluye datos de ejemplo:

**Equipos Médicos:**

- EQ001: Philips - Emergencia ($15,000) - Dr. García
- EQ002: GE - Quirófano ($8,500) - Dr. García  
- EQ003: Mindray - Pediatría ($12,000) - Téc. López
- EQ004: Philips - Quirófano ($25,000) - Dr. García
- EQ005: Otros - Emergencia ($9,800) - Téc. Martínez

**Mobiliario Clínico:**

- MOB001: Acero inoxidable - Quirófano ($1,500 + $500 plus)
- MOB002: Aluminio - Consulta ($800 + $200 plus)
- MOB003: Fibra carbono - Emergencia ($2,200 + $300 plus)
- MOB004: Plástico médico - Consulta ($1,200 + $200 plus)

### 🔧 Requisitos del Sistema

- **SO**: Windows 7/8/10/11
- **Compilador**: MinGW-w64 o similar con soporte C++17
- **Librerías**: Windows API (incluidas en el sistema)
- **RAM**: Mínimo 512MB
- **Espacio**: ~50MB para código fuente y ejecutables

### 📈 Ventajas de la Versión GUI

1. **✅ Sin dependencias externas**: Solo usa Windows API nativa
2. **⚡ Rendimiento**: Compilación rápida sin librerías pesadas
3. **🎨 Profesional**: Interfaz moderna y fácil de usar
4. **📊 Visual**: Datos presentados en tablas organizadas
5. **🔍 Interactivo**: Ordenamiento y filtrado de información
6. **💾 Portable**: Un solo ejecutable independiente

### 🚨 Solución de Problemas

**Error de compilación:**

- Verifique que g++ esté instalado y en el PATH
- Asegúrese de tener todos los archivos fuente

**La aplicación no inicia:**

- Verifique que sea compatible con su versión de Windows
- Ejecute desde la línea de comandos para ver errores

**Faltan datos:**

- Use "Cargar Datos de Prueba" desde el menú Archivo

### 📞 Información del Proyecto

- **Desarrollado para**: Trabajo Final Programación I
- **Equipos**: #5, #6, #7, #8
- **Cliente**: Clínica Vida Plena
- **Versión**: 2.0 (GUI)
- **Fecha**: 2025
