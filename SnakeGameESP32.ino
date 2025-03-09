#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define I2C_SDA       21  // ESP32 Default SDA
#define I2C_SCL       22  // ESP32 Default SCL
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int VRX = 34;  // X-axis (ESP32 ADC1_CH6)
const int VRY = 35;  // Y-axis (ESP32 ADC1_CH7)
const int SW  = 15;  // Joystick button

int snakeX[100], snakeY[100];
int snakeLength = 5;
int foodX, foodY;
int direction = 1;  // 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
bool gameOver = false;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  randomSeed(analogRead(VRX));  

  Wire.begin(I2C_SDA, I2C_SCL);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);

  spawnFood();
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 10 - i;
    snakeY[i] = 5;
  }
}

void loop() {
  if (!gameOver) {
    handleJoystick();
    moveSnake();
    checkCollision();
    drawGame();
    delay(150);
  } else {
    displayGameOver();
    delay(3000);
    resetGame();
  }
}

void handleJoystick() {
  int xValue = analogRead(VRX);
  int yValue = analogRead(VRY);

  if (yValue < 1000 && direction != 2) direction = 0;  // UP
  if (yValue > 3000 && direction != 0) direction = 2;  // DOWN
  if (xValue > 3000 && direction != 3) direction = 1;  // RIGHT
  if (xValue < 1000 && direction != 1) direction = 3;  // LEFT
}

void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  if (direction == 0) snakeY[0]--;
  else if (direction == 1) snakeX[0]++;
  else if (direction == 2) snakeY[0]++;
  else if (direction == 3) snakeX[0]--;

  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    spawnFood();
  }
}

void checkCollision() {
  if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH / 4 || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT / 4) {
    gameOver = true;
  }

  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
    }
  }
}

void drawGame() {
  display.clearDisplay();

  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i] * 4, snakeY[i] * 4, 4, 4, SSD1306_WHITE);
  }

  // Draw food
  display.fillRect(foodX * 4, foodY * 4, 4, 4, SSD1306_WHITE);

  display.display();
}

void spawnFood() {
  foodX = random(0, SCREEN_WIDTH / 4);
  foodY = random(0, SCREEN_HEIGHT / 4);
}

void displayGameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("GAME OVER");
  display.display();
}

void resetGame() {
  snakeLength = 5;
  for (int i = 0; i < snakeLength; i++) {
    snakeX[i] = 10 - i;
    snakeY[i] = 5;
  }
  gameOver = false;
  spawnFood();
}
