@echo off
cd /d %~dp0

set "deleted=false"

echo Lösche Ordner "bin"...
if exist "bin\*" (
    rd /s /q "bin"
    set "deleted=true"
)

echo Lösche Ordner "out"...
if exist "out\*" (
    rd /s /q "out"
    set "deleted=true"
)

echo Lösche Ordner ".vs"...
if exist ".vs\*" (
    rd /s /q ".vs"
    set "deleted=true"
)

if %deleted%==true (
    echo Die angegebenen Ordner wurden gelöscht.
) else (
    echo Es wurden keine Ordner gelöscht, da sie entweder nicht existieren oder Dateien enthalten.
)
pause
