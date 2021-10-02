
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27,16,2);

int buzzer = 5;               //buzzer to pin 5
int Ledred = 12;              // led red to pin12
int Ledgreen = 13;            // led green to pin13
double temp_obj;

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();                  // initialize lcd backlight
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(Ledred, OUTPUT);
  pinMode(Ledgreen, OUTPUT);
  while (!Serial);


  Serial.println("Temperature Check");

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };

  Serial.print("Emissivity = "); Serial.println(mlx.readEmissivity());
  Serial.println("================================================");

  
  lcd.setCursor(3, 0);
  lcd.print("B-SAFE");
  lcd.setCursor(0, 1);
  lcd.print("TEMP CHECKER");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GROUP 22");
  lcd.setCursor(0, 1);
  lcd.print("SIT312");
  delay(2000);
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  digitalWrite(Ledgreen, HIGH);
  Serial.println();
}

void loop() {
 
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  lcd.setCursor(0, 0);
  lcd.print("Temp.   :");
  lcd.print(mlx.readObjectTempC());
  lcd.println("*C");
  lcd.setCursor(0, 1);
  lcd.print("Safe to go in");
  
  temp_obj = mlx.readObjectTempC();
  if (temp_obj > 25) {
    digitalWrite(Ledgreen, LOW);
    Serial.print("Warning...HIGH TEMP...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp.   :");
    lcd.print(mlx.readObjectTempC());
    lcd.println("*C");
    lcd.setCursor(0, 1);
    lcd.print("STOP");
    digitalWrite(buzzer, HIGH);
    digitalWrite(Ledred, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(Ledred, LOW);
    digitalWrite(Ledgreen, HIGH);
  }
  Serial.println();
  delay(500);
}
