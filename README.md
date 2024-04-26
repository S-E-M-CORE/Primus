# Primus - Der glühende Colt

<div align="center">
    <img src="ProjectAssets/General/Logo - Der glühende Colt 512x512.jpg" alt="Logo" width="300" height="300">
</div>

[![License](https://img.shields.io/badge/license-GPLv3-blue.svg)](https://github.com/S-E-M-CORE/Primus/blob/main/LICENSE)

<hr>

## Über das Projekt

Primus ist ein Mitgliederverwaltungssystem für einen Schützenverein.
Es ermöglicht das Verwalten von Mitgliedern. Folgende Daten lassen sich erfassen:
- Vor(Name)
- Geburtsdatum
- Email
- Telefonnummer
- Adresse
- Anewesenheit zu Trainingseinheiten (Schießübungen)
- Erlaubnis zum Erwerb von Waffen (Auftrag entsprechend, nicht nach echten Waffenregulierungen!)

Dieses Projekt wurde in einem schulischen Rahmen gestartet. Die Software bietet keinerlei Authentifizierung/Autorisierung. Entsprechend empfehlen wir nicht die Anwendung in öffentlichen Netzwerken zu verwenden.

[Projektdokumentation »](https://S-E-M-CORE.github.io/Primus/index.html)

[Einen Fehler gefunden?](https://github.com/S-E-M-CORE/Primus/issues)

<hr>

### Erstellt mit

#### Backend
- [C++](https://www.cplusplus.com/)
- [oatpp](https://oatpp.io/)
- [oatpp-swagger](https://github.com/oatpp/oatpp-swagger)
- [oatpp-sqlite](https://github.com/oatpp/oatpp-sqlite)
- [SQLite](https://www.sqlite.org/)

#### Frontend
- [HTML](https://developer.mozilla.org/de/docs/Web/HTML)
- [CSS](https://developer.mozilla.org/de/docs/Web/CSS)
- [Bootstrap](https://getbootstrap.com/)
- [JavaScript](https://developer.mozilla.org/de/docs/Web/JavaScript)
- [jQuery](https://jquery.com/)
- [Fetch API](https://developer.mozilla.org/de/docs/Web/API/Fetch_API)
- [Popper.js](https://popper.js.org/)

### Installation

Die Installation wurde bisher ausschließlich unter Windows getestet. Im Folgenden finden Sie eine Anleitung für die Windows-Installation.
Theoretisch ist der Code jedoch plattformunabhängig und sollte auf allen bekannten Platformen funktionieren, die auch von [oatpp](https://oatpp.io/supported-platforms/) unterstützt werden.

#### Anforderungen
- Microsoft Visual Studio (getestet mit Visual Studio 2022 Community)
- CMake
- Git

Ort zum Runterladen/Installieren auswählen

```bash
git clone https://github.com/oatpp/oatpp.git
cd oatpp\
mkdir build
cd build\

cmake ..
cmake --build . --target INSTALL

cd ..
cd ..

git clone https://github.com/oatpp/oatpp-swagger.git
cd oatpp-swagger
mkdir build
cd build\

cmake ..
cmake --build . --target INSTALL

cd ..
cd ..

git clone https://github.com/oatpp/oatpp-sqlite.git
cd oatpp-sqlite
mkdir build
cd build\

cmake .. -DOATPP_SQLITE_AMALGAMATION=ON
cmake --build . --target INSTALL

git clone https://github.com/S-E-M-CORE/Primus.git
cd Primus
cd PrimusSvr
mkdir build
cd build\

cmake ..
cmake --build . 
```

Die ausführbare Datei (Exe-Datei) befindet sich nun im Verzeichnis Primus\PrimusSvr\bin\Debug. Da die CMake-Konfiguration bisher noch unvollständig ist, müssen die Dateien manuell in das übergeordnete Verzeichnis verschoben werden. Kopieren Sie dazu alle Dateien aus Primus\PrimusSvr\bin\Debug in Primus\PrimusSvr\bin. Anschließend kann der Ordner "Debug" gelöscht werden.

Nachdem dies erledigt ist, kann die PrimusSvr.exe ausgeführt werden. Öffnen Sie dazu einen Webbrowser und geben Sie http://localhost:8000 ein. Sie werden automatisch zur Weboberfläche weitergeleitet. Die Endpunkt-Dokumentation, die mit Swagger erstellt wurde, ist unter http://localhost:8000/swagger/ui/ verfügbar.

Bitte beachten Sie, dass wir keine Authentifizierungssysteme in diese Implementierung einer Mitgliederverwaltung integriert haben. Aus diesem Grund empfehlen wir dringend, diese Version nicht auf einem öffentlichen Server zu hosten.

