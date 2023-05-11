// Đây là sản phẩm môn kiến trúc máy tính của Trần Anh Đức và Lê Tiến Đạt- PTIT
#include <Servo.h>                   // Khai báo thư viện sử dụng cho động cơ
#include <LiquidCrystal_I2C.h>       // Khai báo thư viện LCD sử dụng I2C
#include <Keypad.h>                  // Khai báo thư viện Keypad
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 địa chỉ LCD, 16 cột và 2 hàng
const int ROW_NUM = 4;     //four rows
const int COLUMN_NUM = 3;  //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte pin_rows[ROW_NUM] = { 9, 8, 7, 6 };    //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 5, 4, 3 };  //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
Servo myServo;

char STR[4] = { '0', '0', '0', '0' };  // Cài đặt mật khẩu mặc định
char str[4] = { ' ', ' ', ' ', ' ' };
char nwp[4] = { ' ', ' ', ' ', ' ' };
int i, j, count = 0;

void setup() {
  myServo.attach(10);  // Khai báo chân điều khiển động cơ
  myServo.write(120);  // đóng cửa
  lcd.init();  // Khai báo sử dụng LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print(" Enter Password");
}

void loop() {
  char key = keypad.getKey();  // Ký tự nhập vào sẽ gán cho biến Key
  if (key)                     // Nhập mật khẩu
  {
    if (i == 0) {
      str[0] = key;
      lcd.setCursor(1, 1);     // Đặt vị trí hiển thị trên led
      lcd.print(str[0]);
      delay(500);  // Ký tự hiển thị trên màn hình LCD trong 0.5s
      lcd.setCursor(1, 1);
      lcd.print("*");  // Ký tự được che bởi dấu *
    }
    if (i == 1) {
      str[1] = key;
      lcd.setCursor(2, 1);
      lcd.print(str[1]);
      delay(500);
      lcd.setCursor(2, 1);
      lcd.print("*");
    }
    if (i == 2) {
      str[2] = key;
      lcd.setCursor(3, 1);
      lcd.print(str[2]);
      delay(500);
      lcd.setCursor(3, 1);
      lcd.print("*");
    }
    if (i == 3) {
      str[3] = key;
      lcd.setCursor(4, 1);
      lcd.print(str[3]);
      delay(500);
      lcd.setCursor(4, 1);
      lcd.print("*");
      count = 1;
    }
    i = i + 1;
  }

  if (count == 1) {
    if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] && str[3] == STR[3]) {
      lcd.clear();
      lcd.print(" Correct!");
      delay(1500);
      myServo.write(12);  // Mở cửa
      lcd.clear();
      lcd.print(" Opened!");
      i = 0;
      count = 0;
    } else {
      lcd.clear();
      lcd.print(" Incorrect!");
      delay(1500);
      lcd.clear();
      lcd.print(" Try Again!");
      delay(1500);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      count = 0;
    }
  }

  switch (key) {
    case '#':               // trường hợp khóa cửa
      lcd.clear();
      myServo.write(120);    // đóng cửa
      lcd.print(" Closed!");
      delay(1500);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      break;
    case '*':               // trường hợp thay đổi mật khẩu
      lcd.clear();
      int state = 1;
      bool kt = true;
      while (state != 3) {
        if (kt == false) break;
        if (state == 1) {
          lcd.print(" Old Password");
          i = 0;
          count = 0;
          while (count == 0) {
            char key = keypad.getKey();  // Ký tự nhập vào sẽ gán cho biến Key
            if (key)                     // Nhập mật khẩu
            {
              if (i == 0) {
                str[0] = key;
                lcd.setCursor(1, 1);
                lcd.print(str[0]);
                delay(500);  // Ký tự hiển thị trên màn hình LCD trong 1s
                lcd.setCursor(1, 1);
                lcd.print("*");  // Ký tự được che bởi dấu *
              }
              if (i == 1) {
                str[1] = key;
                lcd.setCursor(2, 1);
                lcd.print(str[1]);
                delay(500);
                lcd.setCursor(2, 1);
                lcd.print("*");
              }
              if (i == 2) {
                str[2] = key;
                lcd.setCursor(3, 1);
                lcd.print(str[2]);
                delay(500);
                lcd.setCursor(3, 1);
                lcd.print("*");
              }
              if (i == 3) {
                str[3] = key;
                lcd.setCursor(4, 1);
                lcd.print(str[3]);
                delay(500);
                lcd.setCursor(4, 1);
                lcd.print("*");
                count = 1;
              }
              i = i + 1;
            }

            if (count == 1) {
              if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] && str[3] == STR[3]) {
                state = 2;
                lcd.clear();
              } else {
                lcd.clear();
                lcd.print(" Incorrect!");
                delay(1500);
                lcd.clear();
                lcd.print(" Try Again!");
                delay(1500);
                lcd.clear();
                lcd.print(" Enter Password");
                kt = false;
                break;
              }
            }
          }
        } else if (state == 2) {
          myServo.write(12);
          lcd.print(" New Password");
          i = 0;
          count = 0;
          while (count == 0) {
            char key = keypad.getKey();  // Ký tự nhập vào sẽ gán cho biến Key
            if (key)                     // Nhập mật khẩu
            {
              if (i == 0) {
                STR[0] = key;
                lcd.setCursor(1, 1);
                lcd.print(STR[0]);
                delay(500);  // Ký tự hiển thị trên màn hình LCD trong 1s
                lcd.setCursor(1, 1);
                lcd.print("*");  // Ký tự được che bởi dấu *
              }
              if (i == 1) {
                STR[1] = key;
                lcd.setCursor(2, 1);
                lcd.print(STR[1]);
                delay(500);
                lcd.setCursor(2, 1);
                lcd.print("*");
              }
              if (i == 2) {
                STR[2] = key;
                lcd.setCursor(3, 1);
                lcd.print(STR[2]);
                delay(500);
                lcd.setCursor(3, 1);
                lcd.print("*");
              }
              if (i == 3) {
                STR[3] = key;
                lcd.setCursor(4, 1);
                lcd.print(STR[3]);
                delay(500);
                lcd.setCursor(4, 1);
                lcd.print("*");
                count = 1;
              }
              i = i + 1;
            }
          }
          state = 3;
          lcd.clear();
          lcd.print(" Completed!");
          delay(1500);
          lcd.clear();
          lcd.print(" Enter Password");
        }
      }
      i = 0;
      count = 0;
      myServo.write(120);
      str[0] = ' ';
      str[1] = ' ';
      str[2] = ' ';
      str[3] = ' ';
      break;
  }
}
