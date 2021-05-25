

// fastar sem eru bundnir við þetta tiltekna tæki.
//#define SERIALNUMBER "003" // Þetta ætti að vera lesið úr EEPROM...
#define VERSION "hw1.7.0-swV1.2.0"
#define BUILDDATE "2021-05-21"
#define CALIBRATE ON // Ef calibrate er ON þá keyrir bara calibrate lúppan.

// Hér skilgreinum við fasta sem breytast ekki.
// Fastar tafir.
#define AIR_DELAY 1000 // Hve lengi við hinkrum meðan verið er að dæla í eða úr kistu. 1s er nægur tími.
#define TIMERTIRE 10
#define TIMER10PSI 45000 // 30s fyrir langa
#define TIMER5PSI 30000
#define TIMER1PSI 15000 // 7 sekúndur
#define TIMER025PSI 7000

// EEPROM minnishólf
#define ESERIALNUMBER 0 // Skilgreinum hvar seríal númer er geymt.
#define EBACKLIGHT 10 // Skilgreinum minnishólf fyrir baklýsingu
#define EPRESSURE 15 // Skilgreinum minnishólf fyrir þrýsting
#define EPRESSURE_LRT 20 // Skilgreinum minnishólf fyrir dekkjaþrýsting
#define EPRESSURE_LFT 25
#define EPRESSURE_RFT 30
#define EPRESSURE_RRT 35

// Val milli active high eða active low. Auðveldar portun á kóða fyrir aðrar útgangsstýringar.
#define OFF LOW
#define ON HIGH

// Skilgreinum pinna fyrir hvern segulloka.
// Þessi pinnaröð er miðað við Arduino digital pinnaröð samkvæmt ATmega1284, en miðast
// ekki við fýsíska pinna örtölvunnar. Þeir koma í sviga fyrir aftan athugasemd.
// Númer víra að lokum er svo aftast.
#define AIR_OUT 21   // Loft út af kistu (27) (6)
#define TIRE_LR 20   // vinstra afturdekk (26) (5)
#define TIRE_LF 19   // vinstra framdekk (25) (4)
#define TIRE_RF 18   // hægra  framdekk (24) (3)
#define TIRE_RR 17   // hægra afturdekk (23) (2)
#define AIR_IN 16  // Loft inn á kistu. (22) (1)


// Skilgreinum pinna fyrir skynjara.
#define P_SENSOR A0 // Þrýstingsnemi MPX5700 (40)

// Global variables


// Skilgreinum global breytur
bool debug = true; // breyta í true fyrir debug

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


unsigned long previousMillis = 0; // Teljari 1
unsigned long previousMillis1 = 0; // Teljari 2
unsigned long previousMillis2 = 0; // Teljari 3
unsigned long interval = 6000; // hve lengi á að bíða þar til athugað er aftur. 6s ~= 0.1psi
unsigned long interval1 = 600000; // interval1 er hugsað fyrir athugun á dekkjaþrýstingi, er 10mínútur.
unsigned long interval2 = 300000; // interval2 er hugsað fyrir athugun dekkjaþrýstings
uint16_t interval_ALL = 6000;
uint16_t interval_LRT = 6000; // Tími LRT
uint16_t interval_LFT = 6000;
uint16_t interval_RFT = 6000;
uint16_t interval_RRT = 6000;

uint8_t menuval = 0; // er menu valið eða ekki?
uint8_t selectedTire =0; // Hvaða dekk er valið.
uint16_t psi = 0; //
bool forval = false; // Er forval valið eða ekki?
bool adjust = false; // Á að stilla eða á ekki að stilla?
bool adjustall = false; // Breyta sem segir forritinu að stilla öll dekk í einu.
bool manual = false; // Ef við erum í manual, þá er selectedpressure valinn fyrir hvert dekk fyrir sig
uint8_t tiretoken = 0; // Dekk sem heldur tokeninu ræður
uint8_t tireval = 0; // Valið dekk
uint8_t backlight_selected = 255; // Styrkur á baklýsingu
uint16_t timerTire = 0; //Hve oft við athugum þrýsting í dekkjum áður en við gefumst upp í bili.

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
void calibrate(); // Calibrate lúppa sem er hugsuð fyrir upphafsstillingu, les CALIBRATE flaggið
void writeSelectedPressure(); // Skrifum þrýstingsval í EEPROM.
void toggleMenu(); // Litum menu takka grænan eða svartan eftir því hvort vöktun sé virk eður ei
//void timerSelector();
//int timerSelector2(float Pt, float Pv);
