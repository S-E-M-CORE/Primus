@echo off
cd /d %~dp0

set "deleted=false"

echo Loesche Ordner "bin"...
if exist "bin\*" (
    rd /s /q "bin"
    set "deleted=true"
)

echo Loesche Ordner "out"...
if exist "out\*" (
    rd /s /q "out"
    set "deleted=true"
)

echo Loesche Ordner ".vs"...
if exist ".vs\*" (
    rd /s /q ".vs"
    set "deleted=true"
)

if %deleted%==true (
    echo Die angegebenen Ordner wurden geloescht.
) else (
    echo Es wurden keine Ordner geloescht.da sie entweder nicht existieren oder Dateien enthalten.
)
pause
