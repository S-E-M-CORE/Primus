<br />
<div align="center">
  <a href="https://github.com/theSaschaM/BSFI22D_Primus/">
    <img src="ProjectAssets/General/Logo - Der glühende Colt 512x512.jpg" alt="Logo" width="150" height="150">
  </a>

  <h3 align="center">Primus - Der glühende Colt</h3>
  
[![License]([https://img.shields.io/badge/license-GPLv3-blue.svg)](https://github.com/theSaschaM/Primus/blob/main/LICENSE.txt)

  <p align="center">
Primus ist ein modernes Mitgliederverwaltungssystem, das im Rahmen eines Schulprojekts entwickelt wurde. Es soll die veraltete Excel-97-Version für den fiktiven Schützenverein "Der glühende Colt" ersetzen. Mit einer benutzerfreundlichen Oberfläche vereinfacht Primus die Mitgliederverwaltungsaufgaben mühelos.

Hinweis: Primus ist ein Projekt im Aufbau und wurde ausschließlich zu Bildungszwecken erstellt. Das beschriebene Szenario ist fiktiv.
    <br />
    <a href="https://thesascham.github.io/BSFI22D_Primus/index.html"><strong>Projektdokumentation »</strong></a>
    <br />
    <br />
		<a href="https://github.com/theSaschaM/BSFI22D_Primus/issues">Einen Fehler gefunden?</a>
  </p>
</div>

<details>
  <summary>Inhaltsverzeichnis</summary>
  <ol>
    <li>
      <a href="#about-the-project">Über das Projekt</a>
      <ul>
        <li><a href="#built-with">Erstellt mit</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Erste Schritte</a>
      <ul>
        <li><a href="#prerequisites">Voraussetzungen</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Mitwirken</a></li>
    <li><a href="#license">Lizenz</a></li>
  </ol>
</details>

## Über das Projekt

"Primus" ist der Codename für unser erstes umfassendes Full-Stack-Projekt im Rahmen des Lernfelds 8 (Datenbanken) an der Berufsschule. Alle relevanten Informationen, einschließlich Projektklarstellungen und aller verwendeten Ressourcen, sind in dieser Datei dokumentiert.

### Erstellt mit

* [HTML](https://developer.mozilla.org/de/docs/Web/HTML)
* [CSS](https://developer.mozilla.org/de/docs/Web/CSS)
* [Bootstrap](https://getbootstrap.com/) - Frontend-Framework
* [JavaScript](https://developer.mozilla.org/de/docs/Web/JavaScript)
* [jQuery](https://jquery.com/) - JavaScript-Bibliothek
* [Fetch API](https://developer.mozilla.org/de/docs/Web/API/Fetch_API) - Zum Senden von HTTP-Anfragen
* [Popper.js](https://popper.js.org/) - Zur Erstellung von Popovers und Tooltips

#### Backend

* [C++](https://www.cplusplus.com/) - Programmiersprache für das Backend
* [oatpp](https://oatpp.io/) - C++ Web Framework
* [oatpp-swagger](https://github.com/oatpp/oatpp-swagger) - Werkzeug zur API-Dokumentation
* [oatpp-sqlite](https://github.com/oatpp/oatpp-sqlite) - SQLite-Erweiterung für oatpp
* [SQLite](https://www.sqlite.org/) - Datenbank für das Backend

## Erste Schritte

Da es noch keine richtige Version der Anwendung gibt, wird dieser Abschnitt in späteren Versionen aktualisiert.

### Voraussetzungen


### Installation
Die Installation wurde bisher ausschließlich unter Windows getestet. Im Folgenden finden Sie eine Anleitung für die Windows-Installation. Theoretisch ist der Code jedoch plattformunabhängig und sollte auch unter Linux-Distributionen problemlos funktionieren.

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

git clone https://github.com/theSaschaM/BSFI22D_Primus.git
cd BSFI22D_Primus
cd PrimusSvr
mkdir build
cd build\

cmake ..
cmake --build . 

```

Die ausführbare Datei (Exe-Datei) befindet sich nun im Verzeichnis BSFI22D_Primus\PrimusSvr\bin\Debug. Da die CMake-Konfiguration bisher noch unvollständig ist, müssen die Dateien manuell in das übergeordnete Verzeichnis verschoben werden. Kopieren Sie dazu alle Dateien aus BSFI22D_Primus\PrimusSvr\bin\Debug in BSFI22D_Primus\PrimusSvr\bin\. Anschließend kann der Ordner "Debug" gelöscht werden.

Nachdem dies erledigt ist, kann die PrimusSvr.exe ausgeführt werden. Öffnen Sie dazu einen Webbrowser und geben Sie http://localhost:8000 ein. Sie werden automatisch zur Weboberfläche weitergeleitet. Die Endpunkt-Dokumentation, die mit Swagger erstellt wurde, ist unter http://localhost:8000/swagger/ui/ verfügbar.

Bitte beachten Sie, dass wir keine Authentifizierungssysteme in diese Implementierung einer Mitgliederverwaltung integriert haben. Aus diesem Grund empfehlen wir dringend, diese Version nicht auf einem öffentlichen Server zu hosten.

### Dokumentation

Wie bereits erwähnt, finden Sie eine Dokumentation der REST-API-Endpunkte bei laufendem Serverbetrieb unter der Adresse http://localhost:8000/swagger/ui/. In dem Verzeichnis BSFI22D_Primus\Documentation sind weitere Dokumente verfügbar, darunter eine Doxygen-generierte Dokumentation der Backend-Klassen (PrimusSrv-Dokumentation.pdf). Da es sich um ein Schulprojekt handelt, finden Sie dort auch die Datei "Projekt-Dokumentation.pdf", die alle Antworten und Anforderungen enthält, die im Rahmen des Schulprojekts erhalten wurden.

Veröffentlicht unter der Apache 2.0 Lizenz. Weitere Informationen finden Sie in der Datei `LICENSE.txt`.
```
