#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h> 

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 11  // MUST be on PORTB! (Use pin truetrue on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
#define ARRAY_SIZE 32
#define small_letter_width 4
#define small_letter_height 5
#define thick_letter_width 7
#define thick_letter_height 9
#define bullet_drawing_width 6
#define bullet_drawing_height 8
#define y_block_1 0
#define y_block_2 8
#define y_block_3 16
#define y_block_4 24

#define BULLET 0
#define HAPPY_MOUTH 1

#define c letter_c_thin
#define a letter_a_thin
#define r letter_r_thin
#define l letter_l_thin
#define i letter_i_thin
#define t letter_t_thin
#define o letter_o_thin
#define s letter_s_thin
#define L letter_L_thick
#define A_letter letter_A_thick
#define B_letter letter_B_thick

#define bullet bullet_drawing
#define happy_mouth happyFace_mouth

boolean letter_c_thin[small_letter_height][small_letter_width] = {{true,true,true,true},{true,false,false,false},{true,false,false,false},{true,false,false,false},{true,true,true,true}};
boolean letter_a_thin[small_letter_height][small_letter_width] = {{false,true,true,false},{true,false,false,true},{true,true,true,true},{true,false,false,true},{true,false,false,true}};
boolean letter_r_thin[small_letter_height][small_letter_width] = {{true,true,true,true},{true,false,false,true},{true,true,true,true},{true,false,true,false},{true,false,false,true}};
boolean letter_l_thin[small_letter_height][small_letter_width] = {{true,false,false,false},{true,false,false,false},{true,false,false,false},{true,false,false,false},{true,true,true,true}};
boolean letter_i_thin[small_letter_height][1] = {{true},{false},{true},{true},{true}};
boolean letter_t_thin[small_letter_height][small_letter_height] = {{true,true,true,true,true},{false,false,true,false,false},{false,false,true,false,false},{false,false,true,false,false},{false,false,true,false,false}};
boolean letter_o_thin[small_letter_height][small_letter_width] = {{true,true,true,true},{true,false,false,true},{true,false,false,true},{true,false,false,true},{true,true,true,true}};
boolean letter_s_thin[small_letter_height][small_letter_width] = {{true,true,true,true},{true,false,false,false},{true,true,true,true},{false,false,false,true},{true,true,true,true}};
boolean letter_A_thick[thick_letter_height][thick_letter_width] = {{true,true,true,true,true,true,true},{true,true,true,true,true,true,true},{true,true,false,false,false,true,true},{true,true,false,false,false,true,true},{true,true,true,true,true,true,true},{true,true,true,true,true,true,true},{true,true,false,false,false,true,true},{true,true,false,false,false,true,true},{true,true,false,false,false,true,true}};
boolean letter_L_thick[thick_letter_height][thick_letter_width] = {{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,false,false,false,false,false},{true,true,true,true,true,true,true},{true,true,true,true,true,true,true}};
boolean letter_B_thick[thick_letter_height][thick_letter_width] = {{true,true,true,true,true,false,false},{true,true,true,true,true,true,false},{true,true,false,false,false,true,true},{true,true,false,false,false,true,true},{true,true,true,true,true,true,true},{true,true,false,false,false,true,true},{true,true,false,false,false,true,true},{true,true,true,true,true,true,false},{true,true,true,true,true,false,false}};
boolean bullet_drawing[bullet_drawing_height][bullet_drawing_width] = {{false,false,false,true,true,true},{false,false,true,false,false,true},{false,true,false,false,false,true},{true,false,true,false,true,false},{false,true,false,true,false,false},{false,false,true,false,false,false},{false,true,false,false,false,false},{true,false,false,false,false,false},};
boolean happyFace_mouth[6][24] = {
  {false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false},
  {false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false},
  {false,false,false,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false,false,false},
  {false,false,false,false,false,true,true,false,false,false,false,false,false,false,false,false,false,true,true,false,false,false,false,false},
  {false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false},
  {false,false,false,false,false,false,false,true,true,true,true,true,true,true,true,true,true,false,false,false,false,false,false,false}
};


const char str[] PROGMEM = "CLASS OF 2015!";
int    textX   = matrix.width(),
       textMin = sizeof(str) * -23,
       hue     = 0;
int8_t ball[6][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 },
  { 8,  20, -1,  -1 },
  { 15,  10, -1,  1 },
  { 30,  25, -1,  -1 }
};
static const uint16_t PROGMEM ballcolor[6] = {
  0x0080, // Green=1
  0x0102, // Blue=1
  0x1000,  // Red=1
  0x2100,
  0x3445,
  0x0050
};
//main method..
void setup(){
  int x, y;
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
}
void print_string(String text, int start_x, int start_y, int x_spacing)
{
   int x, next_letter_x_position = start_x;
   for(x=0; x < text.length(); x++){
      next_letter_x_position += (x_spacing + getLetterandPrint(text.charAt(x), next_letter_x_position, start_y, matrix.Color444(randomINT(), randomINT(), randomINT())));
      delay(100);
   }
}
void getDrawingandPrint(int drawing, int start_x_position, int start_y, int color){
  int col=0, rows=0;
  switch(drawing){
    case BULLET:
      col = sizeof(bullet[0]);
      rows = sizeof(bullet)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)bullet, start_y, color);
      break;
    case HAPPY_MOUTH:
      col = sizeof(happy_mouth[0]);
      rows = sizeof(happy_mouth)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)happy_mouth, start_y, color);
      break;
  }
}
int getLetterandPrint(char letter, int start_x_position, int start_y, int color){
  int col=0, rows=0;
  switch(letter){
    case 'c':
      col = sizeof(c[0]);
      rows = sizeof(c)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)c, start_y, color);
      break;
    case 'a':
      col = sizeof(a[0]);
      rows = sizeof(a)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)a, start_y, color);
      break;
    case 'r':
      col = sizeof(r[0]);
      rows = sizeof(r)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)r, start_y, color);
      break;
    case 'l':
      col = sizeof(l[0]);
      rows = sizeof(l)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)l, start_y, color);
      break;
    case 'i':
      col = sizeof(i[0]);
      rows = sizeof(i)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)i, start_y, color);
      break;
    case 't':
      col = sizeof(t[0]);
      rows = sizeof(t)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)t, start_y, color);
      break;
    case 'o':
      col = sizeof(o[0]);
      rows = sizeof(o)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)o, start_y, color);
      break;
    case 's':
      col = sizeof(s[0]);
      rows = sizeof(s)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)s, start_y, color);
      break;
    case 'A':
      col = sizeof(A_letter[0]);
      rows = sizeof(A_letter)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)A_letter, start_y, color);
      break;
    case 'L':
      col = sizeof(L[0]);
      rows = sizeof(L)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)L, start_y, color);
      break;
    case 'B':
      col = sizeof(B_letter[0]);
      rows = sizeof(B_letter)/col;
      printBLOCK(start_x_position, col, rows, (boolean *)B_letter, start_y, color);
      break;
     default:
      break;
  }
  return col;
}
void printBLOCK(int start_x, int col, int rows, boolean *letter, int y_offset, int color){
   int y,x;
   for(y=0; y < rows; y++) {
      for(x=0; x < col; x++){
        if(letter[(y*col)+x]){
          matrix.drawPixel(start_x+x,y_offset+y, color);
        }
      }
   } 
}
int randomINT(){
  return random(0,8);
}
void drawHappyFace(int color){
  // draw a blue circle
  matrix.fillCircle(matrix.width()/2, matrix.height()/2, 12, color);
  matrix.fillRect(matrix.width()/3, matrix.height()/3, 2, 5, matrix.Color444(0, 0, 0));
  matrix.fillRect(matrix.width()/1.5, matrix.height()/3, 2, 5, matrix.Color444(0, 0, 0));
  getDrawingandPrint(HAPPY_MOUTH, matrix.width()- 28, matrix.width()- 13, matrix.Color444(0, 0, 0));
}
void cleanDisplay(){
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.swapBuffers(false);
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.swapBuffers(false);
}
bool scrollText(){
  matrix.setTextSize(4);
  cleanDisplay();
    // Draw big scrolly text on top
    matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
    matrix.setCursor(textX, 1);
    matrix.print(F2(str));
  
    // Move text left (w/wrap), increase hue
    if((--textX) < textMin){
      textX = matrix.width();
      return true;
    }
    hue += 7;
    if(hue >= 1536) hue -= 1536;
    // Update display
    matrix.swapBuffers(false);
    return false;
}
void jumping_ballss(){
  byte i;
   // Bounce three balls around
  for(i=0; i<6; i++) {
    // Draw 'ball'
    matrix.fillCircle(ball[i][0], ball[i][1], 5, pgm_read_word(&ballcolor[i]));
    // Update X, Y position
    ball[i][0] += ball[i][2];
    ball[i][1] += ball[i][3];
    // Bounce off edges
    if((ball[i][0] == 0) || (ball[i][0] == (matrix.width() - 1)))
      ball[i][2] *= -1;
    if((ball[i][1] == 0) || (ball[i][1] == (matrix.height() - 1)))
      ball[i][3] *= -1;
  }
  matrix.swapBuffers(false);
}
void count_to_three(){
  //count to three top/left
  matrix.setCursor(1, 0);
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color444((randomINT()==0)?1:randomINT(), randomINT(), randomINT()));
  matrix.print('1');
  delay(1500);
  matrix.fillRect(0, 0, 8, 8, matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0);
  matrix.setTextColor(matrix.Color444((randomINT()==0)?1:randomINT(), randomINT(), randomINT()));
  matrix.print('2');
  delay(1500);
  matrix.fillRect(0, 0, 8, 8, matrix.Color333(0, 0, 0));
  matrix.setCursor(1, 0);
  matrix.setTextColor(matrix.Color444((randomINT()==0)?1:randomINT(), randomINT(), randomINT()));
  matrix.print('3');
  delay(1500);
  matrix.fillRect(0, 0, 8, 8, matrix.Color333(0, 0, 0));
}
void loop() {
  byte scroll_rep = 0;
  while(scroll_rep < 5){
    if(scrollText()) scroll_rep++;
  }
  
  drawHappyFace(matrix.Color444(2, 5, 2));
  delay(5000);
  count_to_three();
  
  //change happy face colors really fast
  int break_at_100 = 0;
  bool keepLoop = true;
  while(keepLoop){
    drawHappyFace(matrix.Color444((randomINT()==0)?1:randomINT(), randomINT(), randomINT()));
    delay(100);
    if(break_at_100 == 100){
      keepLoop = false;
    }
    break_at_100++;
  }
  
  cleanDisplay();
  
  //prints carlitos LA BALA message
  print_string("carlitos", 0, y_block_1, 0);
  print_string("LA", 0, y_block_3-4, 1);
  print_string("BALA", 0, y_block_4-1, 1);
  getDrawingandPrint(BULLET, (matrix.width()/2)+(thick_letter_height/2), y_block_4 - (thick_letter_height/2), matrix.Color444((randomINT()==0)?1:randomINT(), randomINT(), randomINT()));
  delay(90000);
  
  int balls_bounce = 0;
  for(balls_bounce = 0; balls_bounce < 300; balls_bounce++){
    cleanDisplay();
    jumping_ballss();
  }
}
