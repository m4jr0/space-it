@rem Copyright 2024 m4jr0. All Rights Reserved.
@rem Use of this source code is governed by the MIT
@rem license that can be found in the LICENSE file.

@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    set "BUILD_TYPE=debug"
) else (
    set "BUILD_TYPE=%~1"
)

if /I not "%BUILD_TYPE%"=="debug" if /I not "%BUILD_TYPE%"=="release" (
    echo Invalid argument. Defaulting to debug.
    set "BUILD_TYPE=debug"
)

if "%~2"=="" (
    set "CLEAR_BUILD=false"
) else (
    set "CLEAR_BUILD=%~2
)

if not "%CLEAR_BUILD%"=="true" if not "%CLEAR_BUILD%"=="false" (
    echo Invalid clear flag argument. Defaulting to false.
    set "CLEAR_BUILD=false"
)

echo Build type is: %BUILD_TYPE%

set SCRIPT_DIR=%~dp0
set REPO_URL=https://github.com/m4jr0/space-it-tools/
set COMMIT_HASH=cc2e6b673dc067c7304bd72012fa63ea9cef8d90

if "%SCRIPT_DIR:~-1%" == "\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_DIR=%%~fI"

set TOOLS_DIR=%PROJECT_DIR%\tools
set BUILD_DIR=%TOOLS_DIR%\lib_build

if "%CLEAR_BUILD%"=="true" (
    echo Clearing directories:
    echo - %BUILD_DIR%
    echo - %TOOLS_DIR%
    
    if exist "%BUILD_DIR%" (
        rmdir /s /q "%BUILD_DIR%"
    )
    
    if exist "%TOOLS_DIR%" (
        rmdir /s /q "%TOOLS_DIR%"
    )
)

echo Setting up tools...

git --version >nul 2>&1

if %ERRORLEVEL% neq 0 (
    echo Git is not installed! Please install Git and try again.
    exit /b 1
)

if not exist %TOOLS_DIR% (
    git clone --no-checkout %REPO_URL% %TOOLS_DIR%

    if %ERRORLEVEL% neq 0 (
        echo Failed to clone the project.
        exit /b 1
    )

    cd %TOOLS_DIR%
    git checkout %COMMIT_HASH%

    if %ERRORLEVEL% neq 0 (
        echo Failed to checkout the specified commit: %COMMIT_HAS%
        exit /b 1
    )
)

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%

    if %ERRORLEVEL% neq 0 (
        echo Failed to create build directory: %BUILD_DIR%
        exit /b 1
    )
)

cmake --version >nul 2>&1

if %ERRORLEVEL% neq 0 (
    echo CMake is not installed! Please install CMake and try again.
    exit /b 1
)

cd %BUILD_DIR%

echo Configuring build...

cmake %PROJECT_DIR% -DVCPKG_ROOT="%PROJECT_DIR%\vcpkg" -DIS_VCPKG_CLONE=TRUE -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DSID_IS_LIB_BUILD_ONLY=TRUE

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed.
    exit /b 1
)

echo Building...

cmake --build %BUILD_DIR%

if %ERRORLEVEL% neq 0 (
    echo Build failed.
    exit /b 1
)

set GENERATED_LIB=%BUILD_DIR%\sid_lib.Lib
set DEST_LIB_DIR=%TOOLS_DIR%\lib

if not exist %DEST_LIB_DIR% (
    mkdir %DEST_LIB_DIR%

    if %ERRORLEVEL% neq 0 (
        echo Failed to create destination lib directory!
        exit /b 1
    )
)

copy %GENERATED_LIB% %DEST_LIB_DIR%

if %ERRORLEVEL% neq 0 (
    echo Failed to copy sid_lib.Lib.
    exit /b 1
)

cd %TOOLS_DIR%
cargo --version >nul 2>&1

if %ERRORLEVEL% neq 0 (
    echo Cargo is not installed or not in the PATH!
    exit /b 1
)

if /I "%BUILD_TYPE%"=="release" (
    cargo build --release
) else (
    cargo build
)

if %ERRORLEVEL% neq 0 (
    echo Something wrong happened while building the tool binaries!
    exit /b 1
)

%TOOLS_DIR%\target\%BUILD_TYPE%\sid_aseprite_converter.exe %PROJECT_DIR%\raw_assets\ %PROJECT_DIR%\assets\

if %ERRORLEVEL% neq 0 (
    echo Something wrong happened while converting the Aseprite files to assets!
    exit /b 1
)

%TOOLS_DIR%\target\%BUILD_TYPE%\sid_asset_packer.exe %PROJECT_DIR%\assets\ %PROJECT_DIR%\build\resources\

if %ERRORLEVEL% neq 0 (
    echo Something wrong happened while exporting the resources!
    exit /b 1
)

exit /b 0
endlocal
