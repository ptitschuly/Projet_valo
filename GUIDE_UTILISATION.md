# Guide d'utilisation - Bibliothèque de Valorisation Financière

## Installation de l'environnement C++

### Prérequis installés automatiquement :
- ✅ CMake 4.1.1
- ✅ Compilateur C++ (LLVM MinGW g++ 14.2.0)

## Utilisation rapide

### 1. Compiler la bibliothèque
```cmd
.\build.bat
```

### 2. Exécuter l'exemple
```cmd
.\build.bat example
```

### 3. Lancer les tests
```cmd
.\build.bat test
```

### 4. Nettoyer le projet
```cmd
.\build.bat clean
```

## Scripts disponibles

- `build.bat` : Script de build principal (Windows)
- `build.ps1` : Script PowerShell alternatif
- `setup_environment.ps1` : Configuration de l'environnement

## Structure du projet

```
Projet_valo/
├── include/           # En-têtes de la bibliothèque
├── src/              # Code source
├── tests/            # Tests unitaires
├── example.cpp       # Exemple d'utilisation
├── CMakeLists.txt    # Configuration CMake
└── README.md         # Documentation complète
```

## Intégration dans votre projet

1. Copiez les dossiers `include/` et `src/`
2. Ajoutez les fichiers à votre système de build
3. Liez avec la bibliothèque `financial_valuation`

## Support

La bibliothèque est maintenant prête à être utilisée pour valoriser des produits financiers en C++ !