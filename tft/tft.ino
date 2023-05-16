#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

#define LCD_CS A3
#define LCD_RST A4
#define LCD_DC A2
#define LCD_WR A1
#define LCD_RD A0

MCUFRIEND_kbv tft;

void setup() {
  Serial.begin(9600);
  tft.reset(); // Reset the TFT screen
  tft.begin(0x9486); // Initialize the TFT screen with the appropriate controller ID
  tft.setRotation(1); // Landscape mode
}

void loop() {
  tft.fillScreen(0x0000); // Clear the screen
  int x = tft.width() / 2;
  int y = tft.height() / 2;
  int r = min(x, y) - 1; // The radius of the circle
  
  // Draw the pie chart
  drawPieChart(x, y, r, 42.9, 79.4, 100.6, 137.1);
  
  delay(5000); // Wait for 5 seconds
}

// Function to draw the pie chart
void drawPieChart(int centerX, int centerY, int radius, float angle1, float angle2, float angle3, float angle4) {
  float startAngle = 90;
  float endAngle = 90;
  
  // Draw the first portion
  endAngle = startAngle + angle1;
  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White

//  if (condition1) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0); // Red
//} else if (condition2) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626); // Green
//} else if (condition3) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7); // YELLOWGREEN
//} else if (condition4) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80); // YELLOW
//}else if (condition5) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xEFEF); // Bright Yellow
//}else {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White
//}
  
  // Draw the second portion
  startAngle = endAngle;
  endAngle = startAngle + angle2;
  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White

  //  if (condition1) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0); // Red
//} else if (condition2) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626); // Green
//} else if (condition3) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7); // YELLOWGREEN
//} else if (condition4) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80); // YELLOW
//}else if (condition5) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xEFEF); // Bright Yellow
//}else {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White
//}
  
  // Draw the third portion
  startAngle = endAngle;
  endAngle = startAngle + angle3;
  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White

  //  if (condition1) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0); // Red
//} else if (condition2) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626); // Green
//} else if (condition3) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7); // YELLOWGREEN
//} else if (condition4) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80); // YELLOW
//}else if (condition5) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xEFEF); // Bright Yellow
//}else {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White
//}
  
  // Draw the fourth portion
  startAngle = endAngle;
  endAngle = startAngle + angle4;
  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White

  //  if (condition1) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xE0E0); // Red
//} else if (condition2) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0x2626); // Green
//} else if (condition3) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xC7C7); // YELLOWGREEN
//} else if (condition4) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFF80); // YELLOW
//}else if (condition5) {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xEFEF); // Bright Yellow
//}else {
//  drawSlice(centerX, centerY, radius, startAngle, endAngle, 0xFFFF); // White
//}

}

// Function to draw a portion of the pie chart using triangles
void drawSlice(int centerX, int centerY, int radius, float startAngle, float endAngle, uint16_t color) {
  int steps = 100; // Number of steps to approximate the curve
  
  // Calculate the step angle
  float stepAngle = (endAngle - startAngle) / steps;
  
  // Calculate the triangle vertices
  int x0 = centerX;
  int y0 = centerY;
  int x1, y1, x2, y2;
  
  // Draw the triangles
  for (int i = 0; i < steps; i++) {
    // Calculate the current angle
    float currentAngle = startAngle + i * stepAngle;
    
    // Calculate the next angle
    float nextAngle = startAngle + (i + 1) * stepAngle;
    
    // Calculate the triangle vertices
    x1 = centerX + radius * cos(currentAngle * PI / 180.0);
    y1 = centerY + radius * sin(currentAngle * PI / 180.0);
    x2 = centerX + radius * cos(nextAngle * PI / 180.0);
    y2 = centerY + radius * sin(nextAngle *PI / 180.0);
// Draw the triangle
tft.fillTriangle(x0, y0, x1, y1, x2, y2, color);
}
}
