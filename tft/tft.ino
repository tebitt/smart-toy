#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

#define LCD_CS A3
#define LCD_RST A4
#define LCD_DC A2
#define LCD_WR A1
#define LCD_RD A0

MCUFRIEND_kbv tft;

int x = tft.width() / 2;
int y = tft.height() / 2;
int r = min(x, y) - 1; // The radius of the circle

void setup() {
  Serial.begin(9600);
  tft.reset(); // Reset the TFT screen
  tft.begin(0x9486); // Initialize the TFT screen with the appropriate controller ID
  tft.setRotation(1); // Landscape mode
  tft.fillScreen(0x0000); // Clear the screen
  delay(100);
  drawSlice(x, y, r, 90, 132.9, 0xFFFF);
  drawSlice(x, y, r, 132.9, 212.3, 0xFFFF);
  drawSlice(x, y, r, 212.3, 312.9, 0xFFFF);
  drawSlice(x, y, r, 312.9, 450, 0xFFFF);
}

void loop() {
  while(!Serial.available());
  int data = Serial.readString().toInt();
  drawPieChart(x, y, r, 42.9, 79.4, 100.6, 137.1, data);
}

// Function to draw the pie chart
void drawPieChart(int centerX, int centerY, int radius, float angle1, float angle2, float angle3, float angle4, int data) {
  if(data <= 3){
    float startAngle = 90;
    float endAngle = 132.9;
    if(data == 1){//Fat / White
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF);}
    else if(data == 2){//Fat / Green
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626);}
    else if(data == 3){// Fat / Red
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0);}
    }
  else if(data > 3 && data <= 7){
    float startAngle = 132.9;
    float endAngle = 212.3;
    if(data == 4){//Pro / White
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF);}
    else if(data == 5){// Pro / Yellow
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80);}
    else if(data == 6){// Pro / Green
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626);}
    else if(data == 7){// Pro / Red
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0);}
    }
  else if(data > 7 && data <= 12){
    float startAngle = 212.3;
    float endAngle = 312.9;
    if(data == 8){//Vit / White
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF);}
    else if(data == 9){// Vit / Yellow
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80);}
    else if(data == 10){// Vit / YellowGreen
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7);}
    else if(data == 11){// Vit / Green
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626);}
    else if(data == 12){// Vit / Red
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0);}
    }
  else if(data > 12 && data <= 18){
    float startAngle = 312.9;
    float endAngle = 450;
    if(data == 13){//Carb / White
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF);}
    else if(data == 14){// Cab / BrightYellow
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xEFEF);}
    else if(data == 15){// Cab / Yellow
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80);}
    else if(data == 16){// Carb / YellowGreen
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7);}
    else if(data == 17){// Carb / Green
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626);}
    else if(data == 18){// Carb / Red
      drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0);}
    }
  else{
    drawSlice(centerX, centerY, radius, 90, 132.9, 0xFFFF);
    drawSlice(centerX, centerY, radius, 132.9, 212.3, 0xFFFF);
    drawSlice(centerX, centerY, radius, 212.3, 312.9, 0xFFFF);
    drawSlice(centerX, centerY, radius, 312.9, 450, 0xFFFF);}

}

void drawSlice(int centerX, int centerY, int radius, float startAngle, float endAngle, uint16_t color) {
  int steps = 100;
  float stepAngle = (endAngle - startAngle) / steps;
  int x0 = centerX;
  int y0 = centerY;
  int x1, y1, x2, y2;
  for (int i = 0; i < steps; i++) {
    float currentAngle = startAngle + i * stepAngle;
    float nextAngle = startAngle + (i + 1) * stepAngle;
    
    // Calculate the triangle vertices
    x1 = centerX + radius * cos(currentAngle * PI / 180.0);
    y1 = centerY + radius * sin(currentAngle * PI / 180.0);
    x2 = centerX + radius * cos(nextAngle * PI / 180.0);
    y2 = centerY + radius * sin(nextAngle *PI / 180.0);
tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);}
}
