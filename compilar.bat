@echo off
echo ===============================================
echo     COMPILADOR DE INVENTARIO MEDICO GUI
echo ===============================================
echo.

REM Crear directorio de objetos si no existe
if not exist obj mkdir obj

echo Compilando aplicacion GUI unificada...
echo.

REM Limpiar archivos anteriores
echo [Paso 1/2] Limpiando archivos anteriores...
del /q obj\*.o 2>nul
del /q InventarioMedico.exe 2>nul

echo [Paso 2/2] Compilando y enlazando aplicacion...

REM Compilar usando g++ directamente con todos los archivos
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude ^
    src/main.cpp ^
    src/articulo.cpp ^
    src/equipo_medico.cpp ^
    src/mobiliario_clinico.cpp ^
    src/inventario.cpp ^
    src/GuiMainFrame.cpp ^
    -o InventarioMedico.exe ^
    -lcomctl32 -luser32 -lgdi32 -lkernel32

if %errorlevel% neq 0 (
    echo.
    echo ===============================================
    echo     ERROR EN LA COMPILACION!
    echo ===============================================
    echo.
    echo Se produjo un error durante la compilacion.
    echo Verifique:
    echo 1. Que g++ este instalado y en el PATH
    echo 2. Que todos los archivos fuente esten presentes
    echo 3. Que no haya errores de sintaxis en el codigo
    echo.
    pause
    exit /b 1
)

echo.
echo ===============================================
echo     COMPILACION EXITOSA!
echo ===============================================
echo.
echo Archivo ejecutable: InventarioMedico.exe
echo.
echo Para ejecutar la aplicacion:
echo    InventarioMedico.exe
echo.

REM Preguntar si quiere ejecutar la aplicacion
set /p ejecutar="¿Desea ejecutar la aplicacion ahora? (s/n): "
if /i "%ejecutar%"=="s" (
    echo.
    echo Iniciando aplicacion...
    start InventarioMedico.exe
)

echo.
echo Presione cualquier tecla para continuar...
pause >nul
