// Skilgreinum minnsta og mesta gildi sem snertingin má vera.
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// Skilgreinum mesta og minnsta þrýsting á snertiskjáinn
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// X+ X- Y+ Y- pinnar fyrir snertiskjá og mæla X/Y ás
#define YP A6  // Y+ (35)
#define XM A7  // X- (34)
#define YM 15  // Y- (21)
#define XP 12  // X+ (18)

// Við þurfum að þekkja viðnámið yfir snertiskjáinn
// milli  X+ and X-
// Má nota hefðbundin DMM til að mæla.
// Þessi mælist 291 Ohm
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 291); // Skilgreinum breytur fyrir snertiskjá.

#define TFT_CS 14 // CS er á pinna 14 (20)
#define TFT_DC 13 // D/C er á pinna 13 (19)
#define BACKLIGHT 4 // Baklýsing er á pinna 4 (3)
#define RESET 3 // Reset er á pinna 1 (4)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); // Skilgreining fyrir ILI9341 kóðasafn

// Svo skilgreinum við kassa og önnur form á skjánum.
#define FRAME_RFT_X 260
#define FRAME_RFT_Y 20
#define FRAME_RFT_W 60
#define FRAME_RFT_H 40

#define FRAME_LFT_X 20
#define FRAME_LFT_Y 20
#define FRAME_LFT_W 60
#define FRAME_LFT_H 40

#define FRAME_LRT_X 20
#define FRAME_LRT_Y 180
#define FRAME_LRT_W 60
#define FRAME_LRT_H 40

#define FRAME_RRT_X 240
#define FRAME_RRT_Y 180
#define FRAME_RRT_W 60
#define FRAME_RRT_H 40
// eða allavegana hingað.

// Skilgreinum MENU takka
#define MENU_X 110
#define MENU_Y 10
#define MENU_W 130
#define MENU_H 38

// Skilgreinum útlínur bíls.
#define FRAME_CAR_X 125
#define FRAME_CAR_Y 80
#define FRAME_CAR_W 80
#define FRAME_CAR_H 150

// dekk vinstra framan
#define LFT_X 110
#define LFT_Y 100
#define TIRE_W 30
#define TIRE_H 35

// dekk hægra framan
#define RFT_X LFT_X+FRAME_CAR_W
#define RFT_Y LFT_Y

// Dekk Vinstra megin aftan
#define LRT_X LFT_X
#define LRT_Y 180

// Dekk hægra megin aftan
#define RRT_X RFT_X
#define RRT_Y LRT_Y

// Skilgreinum hækka takka sem er þríhyrningur
#define INCREMENT_PRESSURE_X0 270
#define INCREMENT_PRESSURE_Y0 90
#define INCREMENT_PRESSURE_X1 240
#define INCREMENT_PRESSURE_Y1 130
#define INCREMENT_PRESSURE_X2 300
#define INCREMENT_PRESSURE_Y2 130

// Skilgreinum lækka takka sem er einnig þríhyrningur.
#define DECREMENT_PRESSURE_X0 50
#define DECREMENT_PRESSURE_Y0 130
#define DECREMENT_PRESSURE_X1 20
#define DECREMENT_PRESSURE_Y1 90
#define DECREMENT_PRESSURE_X2 80
#define DECREMENT_PRESSURE_Y2 90

// Skilgreinum liti
#define BLACK       0x0000        // Bakgrunnur
#define DARKGREEN   0x04E0        // Vöktun - var 0x3E0
#define C_INNDAELING        0x001F      // Inndæling (BLUE)
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define C_WARNING   0xF800      // RED
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define C_URHLEYPING      0xFFE0      // úRHLEYPIING (YELLOW)
#define WHITE       0xFFFF      // Valið dekk
#define C_MAELING   0xFD20      // Mæling (ORANGE)
#define PINK        0xF81F