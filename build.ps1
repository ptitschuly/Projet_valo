# Script de build simplifié pour la bibliothèque de valorisation financière

param(
    [string]$Action = "build"
)

Write-Host "=== Build Script Bibliothèque Valorisation Financière ===" -ForegroundColor Cyan

# Vérifier les prérequis
$cmake = Get-Command cmake -ErrorAction SilentlyContinue
$gpp = Get-Command g++ -ErrorAction SilentlyContinue

if (-not $cmake) {
    Write-Error "CMake n'est pas installé"
    exit 1
}

if (-not $gpp) {
    Write-Error "g++ n'est pas installé"
    exit 1
}

Write-Host "Prérequis OK ✓" -ForegroundColor Green

switch ($Action) {
    "clean" {
        Write-Host "Nettoyage..." -ForegroundColor Yellow
        if (Test-Path "build") {
            Remove-Item -Recurse -Force "build"
        }
        Write-Host "Nettoyage terminé ✓" -ForegroundColor Green
    }

    "build" {
        Write-Host "Configuration du projet..." -ForegroundColor Yellow
        if (-not (Test-Path "build")) {
            New-Item -ItemType Directory -Path "build" | Out-Null
        }

        Push-Location build
        & cmake .. -G "MinGW Makefiles"
        if ($LASTEXITCODE -ne 0) {
            Write-Error "Erreur CMake"
            Pop-Location
            exit 1
        }

        Write-Host "Compilation..." -ForegroundColor Yellow
        & mingw32-make
        if ($LASTEXITCODE -ne 0) {
            Write-Error "Erreur compilation"
            Pop-Location
            exit 1
        }

        Write-Host "Build terminé ✓" -ForegroundColor Green
        Pop-Location
    }

    "test" {
        if (-not (Test-Path "build")) {
            Write-Error "Compilez d'abord avec: .\build.ps1 build"
            exit 1
        }

        Push-Location build
        Write-Host "Tests..." -ForegroundColor Yellow
        & mingw32-make test
        Pop-Location
    }

    "example" {
        if (-not (Test-Path "build")) {
            Write-Error "Compilez d'abord avec: .\build.ps1 build"
            exit 1
        }

        Push-Location build
        Write-Host "Compilation exemple..." -ForegroundColor Yellow
        & mingw32-make example
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Exécution..." -ForegroundColor Yellow
            Write-Host "----------------------------------------" -ForegroundColor Cyan
            & .\example.exe
            Write-Host "----------------------------------------" -ForegroundColor Cyan
        }
        Pop-Location
    }

    default {
        Write-Host "Usage: .\build.ps1 [build|clean|test|example]" -ForegroundColor Yellow
    }
}

Write-Host "Terminé." -ForegroundColor Green