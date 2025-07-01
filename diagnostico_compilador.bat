@echo off
echo ===============================================
echo     DIAGNOSTICO DE COMPILADOR C++
echo ===============================================
echo.

echo Buscando compiladores C++ instalados...
echo.

REM Verificar g++ en PATH
echo [1] Verificando g++ en PATH...
g++ --version >nul 2>&1
if %errorlevel%==0 (
    echo ✅ g++ encontrado en PATH
    g++ --version
    echo.
    goto :found_gcc
) else (
    echo ❌ g++ no encontrado en PATH
)

REM Buscar en ubicaciones comunes de MinGW
echo.
echo [2] Buscando en ubicaciones comunes de MinGW...
set MINGW_PATHS=C:\MinGW\bin C:\mingw64\bin C:\msys64\mingw64\bin "C:\Program Files\mingw-w64\mingw64\bin" C:\TDM-GCC-64\bin

for %%P in (%MINGW_PATHS%) do (
    if exist "%%P\g++.exe" (
        echo ✅ g++ encontrado en: %%P
        "%%P\g++.exe" --version
        echo.
        echo Para usar este compilador, agregue esta ruta al PATH:
        echo %%P
        echo.
        goto :found_gcc_path
    )
)

REM Buscar Visual Studio
echo [3] Verificando Visual Studio...
where cl >nul 2>&1
if %errorlevel%==0 (
    echo ✅ Visual Studio C++ encontrado
    cl 2>&1 | findstr "Microsoft"
    echo.
    goto :found_vs
) else (
    echo ❌ Visual Studio C++ no encontrado en PATH
)

REM Buscar Dev-C++ / Code::Blocks
echo.
echo [4] Buscando IDEs con compilador incluido...
if exist "C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\g++.exe" (
    echo ✅ Dev-C++ encontrado
    echo Ruta: C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\
)
if exist "C:\Program Files\CodeBlocks\MinGW\bin\g++.exe" (
    echo ✅ Code::Blocks encontrado
    echo Ruta: C:\Program Files\CodeBlocks\MinGW\bin\
)

echo.
echo ===============================================
echo     RESULTADO DEL DIAGNOSTICO
echo ===============================================

:found_gcc
echo.
echo ✅ SOLUCION: Use el comando normal de compilacion:
echo    .\compilar.bat
echo    .\compilar_gui.bat
echo.
goto :end

:found_gcc_path
echo.
echo ⚠️  SOLUCION: Agregue la ruta encontrada al PATH del sistema
echo    O use el script: compilar_manual.bat
echo.
goto :end

:found_vs
echo.
echo ✅ SOLUCION: Use el script de Visual Studio:
echo    compilar_vs.bat
echo.
goto :end

echo.
echo ❌ NO SE ENCONTRO NINGUN COMPILADOR
echo.
echo RECOMENDACIONES:
echo 1. Instalar MinGW-w64: https://www.mingw-w64.org/
echo 2. Instalar Visual Studio Community
echo 3. Instalar Code::Blocks con MinGW incluido
echo.

:end
echo.
echo Presione cualquier tecla para continuar...
pause >nul
