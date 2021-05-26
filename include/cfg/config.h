/*  Config file 
*   Here we define global variables, defines, and constants etc
*   This probably needs some rework and clean up.
*/

// fastar sem eru bundnir við þetta tiltekna tæki.
//#define SERIALNUMBER "003" // Þetta ætti að vera lesið úr EEPROM...
#define VERSION "hw1.7.0-swV1.2.0"
#define BUILDDATE "2021-05-26"
#define CALIBRATE ON // Ef calibrate er ON þá keyrir bara calibrate lúppan.

// Hér skilgreinum við fasta sem breytast ekki.
// Fastar tafir.
#define AIR_DELAY 1000 // Hve lengi við hinkrum meðan verið er að dæla í eða úr kistu. 1s er nægur tími.
#define TIMERTIRE 10
// These timers can probably be removed soon.
#define TIMER10PSI 45000 // 30s fyrir langa
#define TIMER5PSI 30000
#define TIMER1PSI 15000 // 7 sekúndur
#define TIMER025PSI 7000

// EEPROM memory banks
#define ESERIALNUMBER 0 // Skilgreinum hvar seríal númer er geymt.
#define EBACKLIGHT 10 // Skilgreinum minnishólf fyrir baklýsingu
#define EPRESSURE 15 // Skilgreinum minnishólf fyrir þrýsting
#define EPRESSURE_LRT 20 // Skilgreinum minnishólf fyrir dekkjaþrýsting
#define EPRESSURE_LFT 25
#define EPRESSURE_RFT 30
#define EPRESSURE_RRT 35

// In case we want to use P-Mosfets at some point.
#define OFF LOW
#define ON HIGH

// Define output pins for solenoids
// Mightycore pinout, not the physical pins on the ATmega
// They are in parenthesis behind followed by wire number in the harness
// Númer víra í víralúmi eru aftast
#define AIR_OUT 21   // Loft út af kistu (27) (6)
#define TIRE_LR 20   // vinstra afturdekk (26) (5)
#define TIRE_LF 19   // vinstra framdekk (25) (4)
#define TIRE_RF 18   // hægra  framdekk (24) (3)
#define TIRE_RR 17   // hægra afturdekk (23) (2)
#define AIR_IN 16  // Loft inn á kistu. (22) (1)


// Skilgreinum pinna fyrir skynjara.
// Define pins for inputs
#define P_SENSOR A0 // Þrýstingsnemi MPX5700 (40)

// Skilgreinum pinna fyrir PWM
//#define BACKLIGHT 4 
// Það þarf að finna þetta í kóðanum, og lagfæra, þessi breyta er týnd.


// Global variables
// Skilgreinum global breytur
bool debug = true; // true for debug

static float selectedPressure = 0.00f; // Valinn þrýstingur.
static float selectedPressure_LRT = 0.00f;
static float selectedPressure_LFT = 0.00f;
static float selectedPressure_RFT = 0.00f;
static float selectedPressure_RRT = 0.00f;
static float pressure_ALL = 0.00f; // Þrýstingur í kistu með öll dekk opin.
static float pressure_LFT = 0.00f; //Breyta sem geymir þrýsting vinstra framdekks.
static float pressure_RFT = 0.00f; // Breyta sem geymir þrýsting Hægra framdekks
static float pressure_LRT = 0.00f; // Breyta sem geymir vinstra afturdekks
static float pressure_RRT = 0.00f; // Breyta sem geymir hægra afturdekks.

// Þessa teljara þarf eitthvað að endurhanna... Þetta er algjör steik eins og er.
unsigned long timer_measure = 0;  // Timer between measurements of tire pressure 
unsigned long interval_measure = 600000; // interval1 er hugsað fyrir athugun á dekkjaþrýstingi, er 10mínútur.
unsigned long timer_inflate = 0; // timer for inflation
unsigned long interval_inflate = 2000; // interval for inflation, this should be measured every now and then but default is 2s
unsigned long timer_deflate = 0;
unsigned long interval_deflate = 2000; 

// Þessir mega væntanlega fara bráðlega?
unsigned long previousMillis = 0; // Teljari 1
unsigned long previousMillis1 = 0; // Teljari 2
unsigned long previousMillis2 = 0; // Teljari 3
unsigned long interval = 6000; // hve lengi á að bíða þar til athugað er aftur. 6s ~= 0.1psi

unsigned long interval2 = 300000; // interval2 er hugsað fyrir athugun dekkjaþrýstings
static uint16_t interval_ALL = 6000;
static uint16_t interval_LRT = 6000; // Tími LRT
static uint16_t interval_LFT = 6000;
static uint16_t interval_RFT = 6000;
static uint16_t interval_RRT = 6000;

static uint8_t menuval = 0; // er menu valið eða ekki?
static uint8_t selectedTire =0; // Hvaða dekk er valið.
static uint16_t psi = 0; //
static bool adjust = false; // Á að stilla eða á ekki að stilla?
static bool manual = false; // Ef við erum í manual, þá er selectedpressure valinn fyrir hvert dekk fyrir sig
static uint8_t tiretoken = 0; // Dekk sem heldur tokeninu ræður
static uint8_t tireval = 0; // Valið dekk
uint8_t backlight_selected = 255; // Styrkur á baklýsingu
static uint16_t timerTire = 0; //Hve oft við athugum þrýsting í dekkjum áður en við gefumst upp í bili.

// Skilgreinum öll föll
void updateValues(); // Við uppfærum öll gildi.
void drawTireSelection(); // Við teiknum valmynd fyrir dekkjaval
void drawMain(); // Við teiknum aðal útlit
void drawMenu(); // Við teiknum menu útlit
void drawForval(); // Við teiknum Forvals útlit
void warningCheck(); // Þegar eitthvað bilar.
void air_base_close(); // Lokum öllum lokum
void updateBaseValue(); // Lesum þrýsting af kistu
float readPressure(); // Skilgreinum fall til að lesa þrýsting
void readTires(); // Skilgreinum fall til að lesa þrýsting.
int tirePaint(int tire_colour, int tire); // til að teikna og lita dekk.
void read_RRT(); //Lesum þrýsting í hægra afturhjóli
void read_RFT(); // lesum þrýsting í hægra framhjóli
void read_LFT(); // Lesum þrýsting í vinstra framhjóli
void read_LRT(); // Lesum þrýsting í vinstra afturhjóli
float readTemp(); // Lesum hitanema
void adjustLRT(); // Jöfnum þrýsting í vinstra afturdekki
void adjustLFT(); // Jöfnum þrýsting í Vinstra framdekki
void adjustRFT(); // Jöfnum þrýsting í hægra Framdekki
void adjustRRT(); // Jöfnum þrýsting í hægra afturdekki
void adjustAllTires(); // Við stillum öll dekk í einu.
void air_base_inflate();
void air_base_deflate();
void calibrate(); // Calibrate lúppa sem er hugsuð fyrir upphafsstillingu, les CALIBRATE flaggið
void writeSelectedPressure(); // Skrifum þrýstingsval í EEPROM.
void toggleMenu(); // Litum menu takka grænan eða svartan eftir því hvort vöktun sé virk eður ei
//void timerSelector();
float timerSelector2(float Pt, float Pv, float Pd, float time);
void bootMessage();
void menu(); // Fall sem opnar Menu
int backlightAdjust(int);