/*  Config file 
*   Here we define global variables, defines, and constants etc
*   This probably needs some rework and clean up.
*/

// fastar sem eru bundnir við þetta tiltekna tæki.
//#define SERIALNUMBER "003" 
#define VERSION "hw1.7.0-swV1.3.2"
#define BUILDDATE "2021-06-24"
#define CALIBRATE ON // Ef calibrate er ON þá keyrir bara calibrate lúppan.

// Hér skilgreinum við fasta sem breytast ekki.
// Fastar tafir.
#define AIR_DELAY 1000 // Hve lengi við hinkrum meðan verið er að dæla í eða úr kistu. 1s er nægur tími.
#define TIMERTIRE 10
// Pressure Timer for inflate/deflate
#define PTLONG 30000 // 30s fyrir langa
#define PTMEDIUM 12000
#define PTSHORT 3000 


// EEPROM memory banks
#define ESERIALNUMBER 0 // Skilgreinum hvar seríal númer er geymt.
#define EBACKLIGHT 10 // Skilgreinum minnishólf fyrir baklýsingu
#define EPRESSURE 15 // Skilgreinum minnishólf fyrir þrýsting
#define EPRESSURE_LRT 20 // Skilgreinum minnishólf fyrir dekkjaþrýsting
#define EPRESSURE_LFT 25
#define EPRESSURE_RFT 30
#define EPRESSURE_RRT 35
#define EDEBUG 40

// In case we want to use P-Mosfets at some point.
#define OFF LOW
#define ON HIGH

// Define output pins for solenoids
// Mightycore pinout, not the physical pins on the ATmega
// They are in parenthesis behind followed by wire number in the harness
// Numbers of each wire in the cable then follow
#define AIR_OUT 21   // Loft út af kistu (27) (6)
#define TIRE_LR 20   // vinstra afturdekk (26) (5)
#define TIRE_LF 19   // vinstra framdekk (25) (4)
#define TIRE_RF 18   // hægra  framdekk (24) (3)
#define TIRE_RR 17   // hægra afturdekk (23) (2)
#define AIR_IN 16  // Loft inn á kistu. (22) (1)

// Secondary Solenoids, either for 4 extra tires, or 4 air bags
#define AIRBAG_OUT 25
#define AIRBAG_LR 26
#define AIRBAG_LF 27
#define AIRBAG_RF 28
#define AIRBAG_RR 2
#define AIRBAG_IN 3


// Skilgreinum pinna fyrir skynjara.
// Define pins for inputs
#define P_SENSOR A0 // Þrýstingsnemi MPX5700 (40)
#define LIGHT_SENSE A5 // (35)

// Skilgreinum pinna fyrir PWM
//#define BACKLIGHT 4 
// Það þarf að finna þetta í kóðanum, og lagfæra, þessi breyta er týnd.


// Global variables
// Skilgreinum global breytur
static bool debug = false;

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

unsigned long timer_measure = 0;  // Timer between measurements of tire pressure 
unsigned long interval_measure = 600000; // interval1 er hugsað fyrir athugun á dekkjaþrýstingi, er 10mínútur.
unsigned long timer_inflate = 0; // timer for inflation
unsigned long interval_inflate = 3000; // interval for inflation, this should be measured every now and then but default is 2s
unsigned long timer_deflate = 0;
unsigned long interval_deflate = 3000; 

unsigned long interval_inflate_LRT = 2000;
unsigned long interval_inflate_LFT = 2000;
unsigned long interval_inflate_RFT = 2000;
unsigned long interval_inflate_RRT = 2000;

unsigned long interval_deflate_LRT = 2000;
unsigned long interval_deflate_LFT = 2000;
unsigned long interval_deflate_RFT = 2000;
unsigned long interval_deflate_RRT = 2000;

unsigned long timer_inflate_LRT = 0;
unsigned long timer_inflate_LFT = 0;
unsigned long timer_inflate_RFT = 0;
unsigned long timer_inflate_RRT = 0;

unsigned long timer_deflate_LRT = 0;
unsigned long timer_deflate_LFT = 0;
unsigned long timer_deflate_RFT = 0;
unsigned long timer_deflate_RRT = 0;

// Þessir mega væntanlega fara bráðlega?
unsigned long previousMillis2 = 0; // Teljari 3
uint16_t previousMillis3 = 0; 

static uint8_t menuval = 0; // Is main menu selected or not?
static uint8_t selectedTire = 0; // Which tyre is selected
static bool adjust = false; // To adjust, or not to adjust? That is the question.
static bool manual = false; // When in manual selectedpressure is selected for each tyre
static uint8_t tiretoken = 0; // The tyre that has the token rules
static uint8_t tireval = 0; // Selected tyre 
char tirecolour_status[4];

uint8_t backlight_selected = 255; // Backlight
bool backlight_auto = false;


// Define all functions
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
void timerSelector();
float timerSelector2(float Pt, float Pv, float Pd, float time);
void bootMessage();
void menu(); // Fall sem opnar Menu
int backlightAdjust(int);
void read_ALL();
void drawSettings();
void drawBacklight();
void test();
void tireMonitor();
void boot();