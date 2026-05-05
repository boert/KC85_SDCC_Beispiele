# PC-Programm

Mit diesem Programm können die Prüfsummen auf dem PC (C++-Compiler erforderlich) evaluiert werden.

```
./fletcher
zero    Länge 8192    crc16 CF9F    fletcher 255 0000    fletcher 256 0000    fletcher KC 0000    sum16 0000
ones    Länge 8192    crc16 F9AF    fletcher 255 1220    fletcher 256 0000    fletcher KC 0001    sum16 2000
55h     Länge 8192    crc16 2FA1    fletcher 255 00AA    fletcher 256 0000    fletcher KC 0055    sum16 A000
FFs     Länge 8192    crc16 FFFC    fletcher 255 0000    fletcher 256 0000    fletcher KC 00FF    sum16 E000
```
