@echo off
REM Script de build pour la bibliothèque de valorisation financière
REM Utilisation: build.bat [clean|test|example]

if "%1"=="clean" goto clean
if "%1"=="test" goto test
if "%1"=="example" goto example

REM Build normale
echo Configuration du projet...
if not exist build mkdir build
cd build
cmake .. -G "MinGW Makefiles"
if errorlevel 1 goto error

echo Compilation...
mingw32-make
if errorlevel 1 goto error

echo Build terminé avec succès!
goto end

:test
cd build
mingw32-make test
goto end

:example
cd build
mingw32-make example
echo.
echo Exécution de l'exemple...
example.exe
goto end

:clean
echo Nettoyage...
if exist build rmdir /s /q build
echo Nettoyage terminé.
goto end

:error
echo Erreur lors du build!
exit /b 1

:end