// Chương trình Arduino để điều khiển 8 đèn LED
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Các chân kết nối 8 đèn LED
const int ledCount = 8;                         // Số lượng đèn LED
int value = 0;                                  // Giá trị dùng để điều khiển trạng thái đèn LED
void setup()
{
    for (int i = 0; i < ledCount; i++)
    {
        pinMode(ledPins[i], OUTPUT); // Thiết lập các chân của LED làm OUTPUT
    }
}

void showLeds(int value)
{
    for (int i = 0; i < ledCount; i++)
    {
        digitalWrite(ledPins[i], (value & (1 << i)) ? HIGH : LOW); // Hiển thị trạng thái từng đèn
    }
}

// Hiệu ứng 1: Đèn chạy từ trái sang phải
void singleL2R()
{
    value = 1; // 00000001
    while (value < (1 << ledCount))
    {
        showLeds(value);
        value <<= 1;
        delay(100);
    }
}

// Hiệu ứng 2: Đèn chạy từ phải sang trái
void singleR2L()
{
    value = 1 << (ledCount - 1); // 10000000
    while (value > 0)
    {
        showLeds(value);
        value >>= 1;
        delay(100);
    }
}

// Hiệu ứng 3: Bật dần từ trái sang phải
void turnOnL2R()
{
    value = 1; // 00000001
    while (value < (1 << ledCount))
    {
        showLeds(value);
        value = (value << 1) | 1;
        delay(100);
    }
}

// Hiệu ứng 4: Tắt dần từ phải sang trái
void turnOffR2L()
{
    value = (1 << ledCount) - 1; // 11111111
    while (value > 0)
    {
        showLeds(value);
        value >>= 1;
        delay(100);
    }
}

// Hiệu ứng 5: Bật dần từ ngoài vào trong
void turnIn()
{
    int left = 0, right = ledCount - 1;
    value = 0;
    while (left <= right)
    {
        value |= (1 << left) | (1 << right);
        showLeds(value);
        left++;
        right--;
        delay(100);
    }
}

// Hiệu ứng 6: Nhấp nháy toàn bộ đèn LED
void blink(int times)
{
    value = 0b10101010; // Khởi tạo giá trị nhấp nháy
    for (int i = 0; i < times; i++)
    {
        value = ~value;
        showLeds(value);
        delay(100);
    }
}

void loop()
{
    singleL2R();
    singleR2L();
    turnOnL2R();
    turnOffR2L();
    turnIn();
    blink(10); // Nhấp nháy 10 lần
}
