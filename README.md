# Financial Valuation Library

A C++ library for valuing financial products, including options, bonds, and other derivatives.

## Quick Start (Windows)

### Environment Setup
Required tools are pre-installed:
- ✅ CMake 4.1.1
- ✅ C++ Compiler (LLVM MinGW g++ 14.2.0)

### Build and Run

```cmd
# Build the library
.\build.bat

# Run the example
.\build.bat example

# Run tests
.\build.bat test

# Clean build files
.\build.bat clean
```

## Features

- **European and American Options**: Pricing using Black-Scholes, Binomial Trees, and Monte Carlo simulations
- **Risk Metrics**: Calculation of Greeks (Delta, Gamma, Theta, Vega, Rho)
- **Modular Design**: Easy to extend with new instruments and pricing models

## Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

## Building the Library

### Installation de CMake (si nécessaire)

**Sur Windows:**
- Téléchargez CMake depuis https://cmake.org/download/
- Ajoutez CMake au PATH système

**Sur Linux/Ubuntu:**
```bash
sudo apt-get install cmake
```

**Sur macOS:**
```bash
brew install cmake
```

### Build Steps

```bash
# Depuis le répertoire racine du projet
mkdir build
cd build
cmake ..
make
```

### Exécution de l'exemple

```bash
# Compiler et exécuter l'exemple
make example
./example
```

### Exécution des tests

```bash
make test
```

## Usage

### Intégration dans votre projet

1. Copiez les dossiers `include/` et `src/` dans votre projet
2. Ajoutez les fichiers source à votre build system
3. Incluez les headers nécessaires

### Exemples de code

#### Option Européenne

```cpp
#include "european_option.h"

int main() {
    // Paramètres: nom, spot, strike, maturité, taux, volatilité, type
    EuropeanOption call("My Call", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Call);
    double price = call.getPrice();
    std::cout << "Prix: " << price << std::endl;
    return 0;
}
```

#### Option Américaine

```cpp
#include "american_option.h"

AmericanOption put("My Put", 100.0, 100.0, 1.0, 0.05, 0.2, OptionType::Put);
double price = put.getPrice();
```

#### Calcul des Greeks

```cpp
#include "greeks.h"

Greeks g = GreeksCalculator::calculateEuropeanCall(100.0, 100.0, 1.0, 0.05, 0.2);
std::cout << "Delta: " << g.delta << std::endl;
std::cout << "Gamma: " << g.gamma << std::endl;
```

#### Simulation Monte Carlo

```cpp
#include "monte_carlo.h"

double price = MonteCarlo::priceOption(100.0, 100.0, 1.0, 0.05, 0.2, 100000, true);
```

## Paramètres des options

- **Spot Price (S)**: Prix actuel de l'actif sous-jacent
- **Strike Price (K)**: Prix d'exercice
- **Time to Maturity (T)**: Temps restant en années
- **Risk-free Rate (r)**: Taux sans risque
- **Volatility (σ)**: Volatilité de l'actif

## API Reference

### Classes principales

- `Instrument`: Classe de base pour tous les instruments financiers
- `Option`: Classe de base pour les options
- `EuropeanOption`: Implémentation des options européennes
- `AmericanOption`: Implémentation des options américaines

### Moteurs de valorisation

- `BlackScholes`: Valorisation analytique des options européennes
- `BinomialTree`: Méthode d'arbre binomial pour options américaines
- `MonteCarlo`: Simulation Monte Carlo

### Métriques de risque

- `GreeksCalculator`: Calcul des Greeks pour les options européennes

## Extension de la bibliothèque

Pour ajouter un nouvel instrument:

1. Héritez de `Instrument`
2. Implémentez la méthode `getPrice()` pure virtuelle
3. Ajoutez les paramètres spécifiques dans le constructeur

## Qt6 Graphical User Interface (Optional)

The project supports a Qt6-based graphical user interface for an enhanced user experience.

### Installing Qt6

**Using aqtinstall (Recommended):**
```cmd
# Install aqtinstall if not already installed
winget install miurahr.aqtinstall

# Install Qt6.5.3 for Windows desktop
aqt install-qt windows desktop 6.5.3 win64_mingw
```

**Manual Installation:**
- Download Qt6 from https://www.qt.io/download
- Install Qt Creator or Qt6 libraries
- Ensure Qt6 is in your PATH or set `CMAKE_PREFIX_PATH`

### Building the GUI

```cmd
# Build with Qt6 GUI support
.\build.bat gui
```

### GUI Features

- **Tabbed Interface**: Separate tabs for European options, American options, Monte Carlo, and About
- **Real-time Calculations**: Instant pricing and Greeks computation
- **Input Validation**: Automatic validation of numerical inputs
- **Professional UI**: Modern interface with proper styling and error handling

## Project Structure

```
Projet_valo/
├── include/           # Header files
├── src/              # Source files
├── tests/            # Unit tests
├── build/            # Build artifacts (generated)
├── CMakeLists.txt    # CMake configuration
├── build.bat         # Build script (Windows)
├── example.cpp       # Usage example
└── README.md         # Documentation
```

## License

This project is licensed under the MIT License.