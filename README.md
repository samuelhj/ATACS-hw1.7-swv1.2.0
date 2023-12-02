# ATACS-hw1.7-swv1.2.0
English below

Uppfærslur má nálgast hér: https://ulfraf.space/files/ATACS-V1.7.x-updater-current.7z

Til að opna 7z skránna gæti þurft p7zip forritið. Það má nálgast hér: https://www.7-zip.org/download.html

Leiðbeiningar: https://ulfraf.space/files/ATACS-Manual-V1.pdf


### Eiginleikar:

Forritið stýrir 6rása mosfet útgangsrás, snertiskjá og les frá þrýstinema. Gildin birtir það svo á skjánum.
Frá skjánum tekur það valin gildi á hvaða þrýstingur á að vera í dekkjum og stillir þrýstingin í dekkjunum eftir því. Einnig fylgist það af og til með
að réttur þrýstingur sé í dekkjum og ef það er ekki til staðar leiðréttir forritið
þrýstingin í því dekki eða dekkjum sem um ræðir.

Hjartað í kerfinu er annarsvegar ATmega1284P með Mightycore bootloader ásamt II9341 skjá frá Adafruit. Sjálfsagt er lítið mál að porta kóðann fyrir á einhverja aðra ATmega rás, t.d. 2560 eða ARM. ATmega328P rásirnar hafa einfaldlega ekki nægilegt minni til að keyra kóðann, en hugsanlega er það hægt með einhverjum brögðum (fækka valmöguleikum t.d.)

Þetta forrit miðast við 2+4 kistu og með skynjarann á prentplötu
Líklega er ekki mikið mál að breyta forritinu svo það lesi aðrar
tegundir af skynjurum. Ef ekki er ætlunin að nota loftút eða auka úrtak frá
loftkerfi má sleppa AIR_IN loka og tengja þann útgang frá MOSFET stýringu beint
á segulrofa fyrir loftdælu og spara þannig bæði einn loftloka og aflestunarloka
fyrir loftdælu. Athugið að EKKI er mælst til þess að nota kerfið með loftkút, það gerir lítið gagn
annað en að rugla kerfið. Ef einhverra hluta vegna er algjört möst að eyða pening í loftkút þá er best
að einangra loftkútinn frá kerfinu með segulrofa, sem lokar á kútinn á meðan ATACS er virkt.

    Útgangar eru eftirfarandi:
    * 6 til að stýra loftlokum með MOSFET stýringu (Gefur jörð)
    * RS232 útgangur fyrir t.d. RS232 skjá eða samskipti við hvað annað sem mönnum
      gæti dottið í hug að bæta við seinna meir.
    * 15 pinna tengi fyrir SPI skjá.

### Kóðasöfn í notkun:
* TouchScreen.h  Við þurfum library til að lesa snertingu af skjá.
* Adafruit_GFX.h  Við þurfum library til að teikna á skjá.
* Adafruit_ILI9341.h  Við þurfum library til að tala við ILI9341 stýringu á skjá.


Ath breyta þarf línu í kóðasafninu Touchscreen.h fyrir ATmega1284P

"TouchScreen.h: Lína 12 í TouchScreen.h bæta þarf við:
>||defined(__AVR_ATmega1284P__)"

# ATACS-hw1.7-swv1.2.0 English
 
Latest updates: https://ulfraf.space/files/ATACS-V1.7.x-updater-current.7z

If you can't open 7zip you can get the program here: https://www.7-zip.org/download.html

Manual: https://ulfraf.space/files/ATACS-Manual-V1.pdf


### Function:

The program controls 6 channel MOSFET outputs to a pneumatic valve base, touch screen and reads a pressure sensor. 
The values are then reported on the TFT. On the TFT pressure is selected and which mode the program is in.
If set to auto the program will periodically measure all the tyres (one at a time) and adjust the pressure if needed.

The core of the system is ATmega1284P with mightycore bootloader along with ILI9341 display from Adafruit. Since the 
ecosystem is Arduino it shouldn't be too difficult to port the code to a different arduino compatible MCU, or any other MCU.
The ATmega328P does not have enough memory to control both the TFT and the system, but could be split up if there's desire to do so.

The program works with a 2+4 valve base (2 valves for in/out and one valve per tyre).
The pressure sensor is located on the PCB but modifications to run on different setup is probably not too difficult.
The system is intended to be used only with an air compressor, and not with an extra air pressure tank. If you absolutely want
to use such a thing, please add a solenoid to cut off the tank while the system is active. If the air compressor is only used for the
ATACS the solenoid for AIR_IN can be omitted and that output can be used to drive a relay for the air compressor.

    Outputs are as following:
    * 6 N-channel MOSFET
    * RS232 port for addons and debugging.
    * 15 pin connector for display
    * HwV1.8 has CAN BUS module (Tbd)

### Libraries:
* TouchScreen.h  For touchscreen
* Adafruit_GFX.h  For drawing graphics.
* Adafruit_ILI9341.h  For communication to ILI9341 on the TFT.


Modifications for the touchscreen library so it works with ATmega1284P

"TouchScreen.h: Line 12 in TouchScreen.h add:
>||defined(__AVR_ATmega1284P__)"
