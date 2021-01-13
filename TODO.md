# TODO: BSB-lan

# TODO

## Parameter 10100
  HEIZ->ALL  INF 10100 Benutzerdefiniert -  INFO Brenner: 04 00 00 59
  Akt. Brennerstatus ??                                   ^^
  Werte: 00 04 09 0D

## Parameter 10102
  Standard: ca. alle 10 Minuten

  HEIZ->ALL  INF 10102 Benutzerdefiniert -  INFO HK1 - TBD: 01 01 1E 84 FF FF FF FF 00 21 
  HEIZ->ALL  INF 10102 Benutzerdefiniert -  INFO HK1 - TBD: 01 01 1E 84 FF FF FF FF 02 01 
  HEIZ->ALL  INF 10102 Benutzerdefiniert -  INFO HK1 - TBD: 01 02 1E 84 FF FF FF FF 00 01 
  HEIZ->ALL  INF 10102 Benutzerdefiniert -  INFO HK1 - TBD: 01 02 1E 84 FF FF FF FF 00 21 
  HEIZ->ALL  INF 10102 Benutzerdefiniert -  INFO HK1 - TBD: 01 02 1E 84 FF FF FF FF 02 01 
                                                               ^1                   ^2 ^3
  1. Werte: 01, 02   Modus     01=Nacht, 02=Tag ???
  2. Werte: 00, 02   Brenner   00=ausm 02=an ???
  3. Werte: 01, 21

  01 00 21 => Nachtabsenkung

## Brötje WGB ProEvo 15C vs BSB-lan 

Fehler 6700 Anfragen?

6700 xxx->yyy ist KEINE Okay-Meldung


### 6705 Fehler - SW Diagnosecode: 0 - not found
=> 0
	Fehler
	SW Diagnosecode
	FA Phase Störstellung    99                         <- 6706

### 6800 Fehler - Historie 1 Datum/Zeit: error 7 (parameter not supported)
=> 15
	Fehler
	Historie 1
	"Feh 169: Sitherm Pro System"                wie 6845/6846

09.01.2021 15:01:27 - LAN->HEIZ QUR 6800 Fehler -  Historie 1 Datum/Zeit: 
                      DC C2 00 0B 06 3D 05 06 D3 23 72 
09.01.2021 15:01:27 - HEIZ->LAN ERR 6800 Fehler -  Historie 1 Datum/Zeit: error 7
                      DC 80 42 0C 08 05 3D 06 D3 07 C8 20 
                      #6800: 



### 6805 Fehler - Historie 3 Fehlercode: error 7 (parameter not supported)
=> 373
	Fehler
	SW Diagnosecode 1
	FA Phase 1         17

### 6810 Fehler - Historie 6 Datum/Zeit: error 7 (parameter not supported)
=> 1
	Fehler
	Historie 2
	153: Gerät manuell verriegelt

### 6815 Fehler - Historie 8 Fehlercode: error 7 (parameter not supported)
=>	259
	Fehler
	SW Diagnosecode 2
	FA Phase 2          0
	
### 6820 Fehler - Reset Historie: error 7 (parameter not supported)
=>	7
	Fehler
	Historie 3
	Feh 169:Sitherm Pro System
	

# Malfunction

Fehler 6700

0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
DC 80 0A 17 07 05 3D 00 9A 00 A9 06 00 08 00 00 00 00 00 00 00 D2 5D  <- Error "Sitherm"
   |  |  |  |  |              |  |     |                       |----
   |  |  |  |  |              |  |     |                       Checksumme
   |  |  |  |  |              |  |     8 ?
   |  |  |  |  |              |  6 ?
   |  |  |  |  |              169 Sitherm
   |  |  |  |  |----------
   |  |  |  |  Cmd 2700
   |  |  |  ?
   |  |  Gesamtlänge 23 Bytes
   |  DISP
   HEIZ

DC 80 0A 17 07 05 3D 00 9A 00 00 00 00 00 00 00 00 00 00 00 00 E6 2F  <- no error
                              |
              							  NO ERROR!
