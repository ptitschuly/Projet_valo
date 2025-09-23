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
- **Collateralized Products**: CDO valuation with tranche pricing and risk analysis
- **Total Return Swaps**: TRS valuation with periodic cash flows and total return calculations
- **Basket Total Return Forwards**: Basket TRF valuation for diversified asset portfolios
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
    std::cout << "Prix total du CDO: " << totalPrice << std::endl;
}

#### Total Return Swap (TRS)

```cpp
#include "total_return_swap.h"

// Créer un actif sous-jacent
UnderlyingTRSAsset asset{120.0, 0.025, 0.22, "Tech Stock"};

// Créer un TRS : nom, actif, notionnel, maturité, taux swap, taux sans risque
TotalReturnSwap trs("Tech Stock TRS", asset, 5000000.0, 3.0, 0.045, 0.03);

double price = trs.getPrice();
double expectedReturn = trs.getExpectedTotalReturn();
std::vector<double> cashFlows = trs.getCashFlows();
```

#### Basket Total Return Forward

```cpp
#include "basket_total_return_forward.h"

// Créer un panier d'actifs
std::vector<BasketAsset> basket = {
    {100.0, 0.4, 0.02, 0.25, "Action Tech"},     // prix, poids, dividendes, volatilité, nom
    {200.0, 0.35, 0.035, 0.18, "Action Finance"},
    {50.0, 0.25, 0.015, 0.30, "Action Energie"}
};

// Créer un Basket TRF : nom, panier, notionnel, maturité, taux forward, taux sans risque
BasketTotalReturnForward basketTrf("Diversified Basket TRF", basket, 10000000.0, 2.0, 0.04, 0.028);

double price = basketTrf.getPrice();
double basketReturn = basketTrf.getBasketTotalReturn();
double basketValue = basketTrf.getBasketValue();
```

## Paramètres des options
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

#### Produits Collatéralisés (CDO)

```cpp
#include "collateralized_product.h"

// Créer un portefeuille d'actifs sous-jacents
std::vector<UnderlyingAsset> assets = {
    {1000000.0, 0.05, 0.15},  // notional, spread, default_prob
    {1000000.0, 0.06, 0.12},
    {1000000.0, 0.04, 0.18},
    {1000000.0, 0.07, 0.10},
    {1000000.0, 0.05, 0.20}
};

// Définir les tranches
std::vector<Tranche> tranches = {
    {0.0, 0.05, 0.08},     // tranche equity: 0-5%, coupon 8%
    {0.05, 0.15, 0.06},    // tranche mezzanine: 5-15%, coupon 6%
    {0.15, 1.0, 0.04}      // tranche senior: 15-100%, coupon 4%
};

// Créer le CDO
CollateralizedProduct cdo("My CDO", assets, tranches, 5.0, 0.03);

// Calculer le prix et les métriques de risque
double price = cdo.getPrice();
double var = cdo.getVaR(0.95);
double expectedLoss = cdo.getExpectedLoss();
```

## Paramètres des options

- **Spot Price (S)**: Prix actuel de l'actif sous-jacent
- **Strike Price (K)**: Prix d'exercice
- **Time to Maturity (T)**: Temps restant en années
- **Risk-free Rate (r)**: Taux sans risque
- **Volatility (σ)**: Volatilité de l'actif

## Paramètres des produits collatéralisés

- **Underlying Assets**: Portefeuille d'actifs sous-jacents avec leur notionnel, spread et probabilité de défaut
- **Tranches**: Structure de tranching avec points d'attachement/détachement et coupons
- **Maturity**: Maturité du CDO en années
- **Risk-free Rate**: Taux sans risque pour l'actualisation
- **Correlation**: Corrélation entre les défauts des actifs (implémentée via copule gaussienne)
- **Recovery Rate**: Taux de récupération en cas de défaut (par défaut 40%)

## Paramètres des Total Return Instruments

### Total Return Swap (TRS)
- **Underlying Asset**: Actif sous-jacent avec prix spot, rendement des dividendes et volatilité
- **Notional**: Montant notionnel du swap
- **Maturity**: Maturité du swap en années
- **Swap Rate**: Taux de swap fixe payé par le receveur du rendement total
- **Risk-free Rate**: Taux sans risque pour l'actualisation
- **Payment Frequency**: Fréquence des paiements (par défaut trimestriel)

### Basket Total Return Forward
- **Basket Assets**: Panier d'actifs avec prix, poids, dividendes et volatilité
- **Notional**: Montant notionnel du forward
- **Maturity**: Maturité du forward en années
- **Forward Rate**: Taux forward de référence
- **Risk-free Rate**: Taux sans risque pour l'actualisation
- **Asset Weights**: Poids des actifs dans le panier (automatiquement normalisés)

## API Reference

### Classes principales

- `Instrument`: Classe de base pour tous les instruments financiers
- `Option`: Classe de base pour les options
- `EuropeanOption`: Implémentation des options européennes
- `AmericanOption`: Implémentation des options américaines
- `CollateralizedProduct`: Implémentation des produits collatéralisés (CDO)
- `TotalReturnSwap`: Implémentation des swaps de rendement total
- `BasketTotalReturnForward`: Implémentation des forwards de rendement total sur panier

### Moteurs de valorisation

- `BlackScholes`: Valorisation analytique des options européennes
- `BinomialTree`: Méthode d'arbre binomial pour options américaines
- `MonteCarlo`: Simulation Monte Carlo

### Métriques de risque

- `GreeksCalculator`: Calcul des Greeks pour les options européennes
- `CollateralizedProduct`: Calcul du VaR, perte attendue et distribution des pertes

### Méthodes de CollateralizedProduct

- `getPrice()`: Prix total du CDO (somme des prix des tranches)
- `getVaR(double confidence)`: Value at Risk à un niveau de confiance donné
- `getExpectedLoss()`: Perte attendue sur le portefeuille
- `getTranchePrices()`: Prix de chaque tranche individuellement
- `getLossDistribution(int numSimulations)`: Distribution des pertes via Monte Carlo

### Méthodes de TotalReturnSwap

- `getPrice()`: Valeur présente nette du swap (flux reçus - flux payés)
- `getExpectedTotalReturn()`: Rendement total attendu de l'actif sous-jacent
- `getSwapRate()`: Taux de swap fixe
- `getNotional()`: Montant notionnel du swap
- `getMaturity()`: Maturité du swap
- `getCashFlows()`: Vecteur des flux de trésorerie nets périodiques

### Méthodes de BasketTotalReturnForward

- `getPrice()`: Valeur présente du forward
- `getBasketTotalReturn()`: Rendement total attendu du panier
- `getForwardRate()`: Taux forward de référence
- `getNotional()`: Montant notionnel du forward
- `getMaturity()`: Maturité du forward
- `getBasketValue()`: Valeur actuelle du panier d'actifs
- `getAssetWeights()`: Poids normalisés des actifs dans le panier

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

- **Tabbed Interface**: Separate tabs for European options, American options, Monte Carlo, Collateralized Products, Total Return Swaps, and Basket Forwards
- **Real-time Calculations**: Instant pricing, Greeks computation, CDO valuation, TRS pricing, and basket forward valuation
- **Input Validation**: Automatic validation of numerical inputs
- **Professional UI**: Modern interface with proper styling and error handling
- **Advanced Instruments**: Support for complex derivatives including collateralized products and total return instruments

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