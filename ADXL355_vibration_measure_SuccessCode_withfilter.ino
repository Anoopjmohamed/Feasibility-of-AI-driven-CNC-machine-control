#include <SPI.h>

// Memory register addresses:
const int XDATA3 = 0x08;
const int XDATA2 = 0x09;
const int XDATA1 = 0x0A;
const int YDATA3 = 0x0B;
const int YDATA2 = 0x0C;
const int YDATA1 = 0x0D;
const int ZDATA3 = 0x0E;
const int ZDATA2 = 0x0F;
const int ZDATA1 = 0x10;
const int RANGE = 0x2C;
const int POWER_CTL = 0x2D;

// Device values
const int RANGE_2G = 0x01;
const int RANGE_4G = 0x02;
const int RANGE_8G = 0x03;
const int MEASURE_MODE = 0x06; // Only accelerometer

// Operations
const int READ_BYTE = 0x01;
const int WRITE_BYTE = 0x00;

// Pins used for the connection with the sensor
const int CHIP_SELECT_PIN = 10;

// Filter parameters
const int FILTER_SIZE = 5;
float xDataFiltered = 0.0, yDataFiltered = 0.0, zDataFiltered = 0.0;
float xData[FILTER_SIZE], yData[FILTER_SIZE], zData[FILTER_SIZE];

void setup() {
  Serial.begin(115200);
  SPI.begin();

  // Initalize the  data ready and chip select pins:
  pinMode(CHIP_SELECT_PIN, OUTPUT);


  //Configure ADXL355:
  writeRegister(RANGE, RANGE_2G); // 2G
  writeRegister(POWER_CTL, MEASURE_MODE); // Enable measure mode

  // Give the sensor time to set up:
  delay(100);
}

void loop() {

  int axisAddresses[] = {XDATA1, XDATA2, XDATA3, YDATA1, YDATA2, YDATA3, ZDATA1, ZDATA2, ZDATA3};
  int axisMeasures[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int dataSize = 9;

  // Read accelerometer data
  readMultipleData(axisAddresses, dataSize, axisMeasures);

  // Split data
  int xdata = (axisMeasures[0] >> 4) + (axisMeasures[1] << 4) + (axisMeasures[2] << 12);
  int ydata = (axisMeasures[3] >> 4) + (axisMeasures[4] << 4) + (axisMeasures[5] << 12);
  int zdata = (axisMeasures[6] >> 4) + (axisMeasures[7] << 4) + (axisMeasures[8] << 12);
  
  // Apply two complement
  if (xdata >= 0x80000) {
    xdata = ~xdata + 1;
  }
  if (ydata >= 0x80000) {
    ydata = ~ydata + 1;
  }
  if (zdata >= 0x80000) {
    zdata = ~zdata + 1;
  }

  // Filter data
  filterData(xdata, ydata, zdata);

  // Print filtered axis values
  
  Serial.print(xDataFiltered);
  Serial.print("\t");
  Serial.print(yDataFiltered);
  Serial.print("\t");
  Serial.println(zDataFiltered);

  // Next data in 100 milliseconds
  // delay(25);
  delayMicroseconds(20000);
}

/* 
 * Write registry in specific device address
 */
void writeRegister(byte thisRegister, byte thisValue) {
  byte dataToSend = (thisRegister << 1) | WRITE_BYTE;
  digitalWrite(CHIP_SELECT_PIN, LOW);
  SPI.transfer(dataToSend);
  SPI.transfer(thisValue);
  digitalWrite(CHIP_SELECT_PIN, HIGH);
}

/* 
 * Read registry in specific device address
 */
unsigned int readRegistry(byte thisRegister) {
  unsigned int result = 0;
  byte dataToSend = (thisRegister << 1) | READ_BYTE;

  digitalWrite(CHIP_SELECT_PIN, LOW);
  SPI.transfer(dataToSend);
  result = SPI.transfer(0x00);
  digitalWrite(CHIP_SELECT_PIN, HIGH);
  return result;
}

/* 
 * Read multiple registries
 */
void readMultipleData(int *addresses, int dataSize, int *readedData) {
  digitalWrite(CHIP_SELECT_PIN, LOW);
  for(int i = 0; i < dataSize; i = i + 1) {
    byte dataToSend = (addresses[i] << 1) | READ_BYTE;
    SPI.transfer(dataToSend);
    readedData[i] = SPI.transfer(0x00);
  }
  digitalWrite(CHIP_SELECT_PIN, HIGH);
}

/*
 * Apply simple moving average filter to the data
 */
void filterData(int x, int y, int z) {
  static uint8_t dataIndex = 0;
  xData[dataIndex] = x;
  yData[dataIndex] = y;
  zData[dataIndex] = z;
  dataIndex = (dataIndex + 1) % FILTER_SIZE;

  float xSum = 0.0, ySum = 0.0, zSum = 0.0;
  for (uint8_t i = 0; i < FILTER_SIZE; i++) {
    xSum += xData[i];
    ySum += yData[i];
    zSum += zData[i];
  }
  xDataFiltered = xSum / FILTER_SIZE;
  yDataFiltered = ySum / FILTER_SIZE;
  zDataFiltered = zSum / FILTER_SIZE;
}
