#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define BUTTON_PIN 2

LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

bool lastButtonState = HIGH;
bool buttonPressed = false;

unsigned long fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    randomSeed(analogRead(0));
    
    lcd.init();
    lcd.backlight();
    
    lcd.setCursor(0, 0);
    lcd.print("Press button");
    lcd.setCursor(0, 1);
    lcd.print("to start");
}

void loop() {
    bool currentState = digitalRead(BUTTON_PIN);
    
    if (lastButtonState == HIGH && currentState == LOW) {
        buttonPressed = true;
        delay(50); 
    }
    lastButtonState = currentState;
    
    if (buttonPressed) {
        buttonPressed = false;
        
        int randNum = random(5, 31);
        
        lcd.clear();
        
        lcd.setCursor(0, 0);
        lcd.print("Num: ");
        lcd.print(randNum);
        
        unsigned long startTime = micros();
        unsigned long fibResult = fibonacci(randNum);
        unsigned long endTime = micros();
        
        float elapsedSec = (endTime - startTime) / 1000000.0;
        
        lcd.setCursor(0, 1);
        lcd.print("Time: ");
        lcd.print(elapsedSec, 5);
        lcd.print(" sec");
        
        lcd.setCursor(0, 2);
        lcd.print("Fib: ");
        lcd.print(fibResult);
    }
}