# Vergleich verschiedener Prüfsummenalgorithmen

Im diesem Projekt sind verschiedene Prüfsummenalgorithmen implementiert.
Das Programm ermittelt zusätzlich die jeweiligen Laufzeiten, der Algorithmen, jewils für einen Speicherbereich von 8 kByte.

Die Algorithmen sind sowohl in C als auch in Assembler (ASM) umgesetzt. Damit werden die Laufzeitunterschiede zwischen den Programmiersprachen sichtbar.


## Prüfsummenalgorithmen
- CRC16 (nach CCITT)  
- Fletcher-16 mit M = 255  
- Fletcher-16 mit M = 256  
- Fletcher-16 mit M = 256 (modifizierter Startwert)  
- SUM16  

### CRC16
CRC steht für _cyclic redundancy check_, einem Prüfsummenverfahren, welches sich gut in Hardware (Logikschaltkreise) abbilden lässt.
Hier kommt das Verfahren mit dem Polynom  0x1021 (x<sup>16</sup> + x<sup>12</sup> + x<sup>5</sup> + 1) nach CCITT zum Einsatz [^2].

Eine Kontrolle kann mit jacksum [^1] erfolgen:
```
jacksum -a crc:16,1021,ffff,false,false,0 -X  <Datei>
```

### Fletcher-16 mit M = 255

Die Prüfsumme nach Fletcher [^3] folgt einem relativ einfachen Algorithmus, der sich gut in Software abbilden läßt:
```
for i = 1, 2, ... , L
    c0 = (c0 + b[i]) mod M
    c1 = (c1 + c0) mod M

fletcher16 = c1 << 8 | c0
```

Legende:

| Symbol | Bedeutung                           |
| :---   | :---                                |
| L      | Länge der Daten                     |
| i      | Index                               |
| b      | Daten, byteweise                    |
| M      | ganzzahliger Divisionsrest (modulo) |
| c0     | einfache Prüfsumme                  |
| c1     | Prüfsumme der Prüfsummen            |

Neben der einfachen Prüfsumme der einezlnen Bytes wird noch eine Prüfsumme der einzelnen Prüfsummen gebildet.


### Fletcher-16 mit M = 256
Um die Berechnug - gerade auf 8-Bit-Systemen - zu vereinfachen, wird statt Modulo 255 mit Modulo 256 gerechnet.
Dieser Algorithmus eignet sich nicht als eindeutige Signatur für Speicherbereich mit der Größe von 512 Byte (und ganzzahligen Vielfachen davon).
Sobald ein zu prüfender Speicherbereich mit identischen Bytes gefüllt ist und die Länge von 512 Bytes (oder Vielfache) hat, beträgt die Prüfsumme 0.


### Fletcher-16 mit M = 256 (modifizierter Startwert)
Um den Nachteil zu Umgehen und doch eine Unterscheidung machen zu können, kann als Startwert für c0, der erste Wert aus dem Speicherbereich verwendet werden.
Damit ist eine Nutzung als Signaturalgorithmus möglich.


## Laufzeiten

Die Lauzeitmessung erfolgt mit Hilfe der CTC, Kanal 2. Es wir alle 20 ms ein Interupt ausgelöst und eine Zählvariable inkrementiert.
Damit ergibt sich eine Ungenauigkeit von &#x00B1; 20 ms.
Mit einer 16-Bit Zählvariable läßt sich ein Messbereich bis 5:27 min:s abdecken.

| Algorithmus  | Laufzeit C | Laufzeit ASM
| :---         | :--------: | :----------:
| CRC16        | 7940 ms    | 840 ms
| Fletcher 255 | 7760 ms    | 280 ms
| Fletcher 256 | 1020 ms    | 200 ms
| Fletcher KC  | 1020 ms    | 200 ms
| SUM16        |  960 ms    | 180 ms


[^1]: https://de.wikipedia.org/wiki/Zyklische_Redundanzpr%C2%BCfung#Berechnung_einer_CRC-Pr%C3%BCfsumme_in_C_und_Pascal_bzw._Delphi
[^2]: https://jacksum.net/en/index.html
[^3]: https://de.wikipedia.org/wiki/Fletcher%E2%80%99s_Checksum
