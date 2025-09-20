# Configuration de l'environnement C++ pour Windows
# Ajoutez ces lignes à votre profil PowerShell pour un accès permanent

# Ajouter CMake au PATH
$env:Path += ";C:\Program Files\CMake\bin"

# Ajouter MinGW/LLVM au PATH (ajustez le chemin selon votre installation)
# $env:Path += ";C:\path\to\llvm-mingw\bin"

# Alias pratiques
Set-Alias -Name build -Value ".\build.ps1"
Set-Alias -Name clean -Value ".\build.ps1 -Action clean"
Set-Alias -Name test -Value ".\build.ps1 -Action test"
Set-Alias -Name example -Value ".\build.ps1 -Action example"

Write-Host "Environnement C++ configuré!" -ForegroundColor Green