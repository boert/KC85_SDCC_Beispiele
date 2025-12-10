# KC85_SDCC_Beispiele
Programmbeispiele zur Verwendung des Small Device C Compiler (SDCC) am KC85/4

- Hello World  
- Fraktale im Textmodus  


Das Projekt zeigt den Einsatz des SDCC-Compilers um KCC-Dateien für die Kleincomputer aus Mühlhausen (KC85/3, KC85/4, KC85/5) zu erzeugen.
Dazu sind einige Anpassungen nötig (crt0.s, header.s, menuentry.s).
Außerdem gibt es eine Bibliothek, die ein angepasste printf-Funktion zur Verfügung stellt und eine Bibliothek, die Zugriff auf einige Unterprogramme des Betriebsystems CAOS erlaubt.

## Buildsystem
Um das Programm zu übersetzen werden folgende Werkzeuge benötigt:  
- make  
- sdcc  
- ggf. python3  


# Weiterführende Links

- KC85/5 Systemhandbuch  
http://www.kc85.info/index.php/download-topmenu/download/32-handbuecher/401-kc85-5-systemhandbuch.html

- SDCC - Small Device C Compiler  
https://sdcc.sourceforge.net/

- Gihub-Seite von Andreas Ziermann  
https://github.com/anchorz/sdcc-z1013-kc85

- JKCEMU, Emulator (u.a. KC85) von Jens Müller  
http://www.jens-mueller.org/jkcemu/

