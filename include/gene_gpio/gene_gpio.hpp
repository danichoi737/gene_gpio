/*
 *  GENE-SKU6 GPIO control
 *  Chipset: F81866
 */

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>


class GeneGPIO
{
private:
  std::fstream gpio_fstream_;
  const std::string SYSFS_GPIO = "/sys/class/gpio";
  const std::string EXPORT = "/export";
  const std::string UNEXPORT = "/unexport";
  const std::string GPIO_DIR = "/gpio";
  const std::string DIRECTION = "/direction";
  const std::string VALUE = "/value";

  uint16_t pin_array_[8] = {DIO0, DIO1, DIO2, DIO3, DIO4, DIO5, DIO6, DIO7};
  uint16_t pin_direction_[8] = {INPUT, };
  struct timespec ts_msec_100 = {.tv_sec = 0, .tv_nsec = 100000000};

public:
  enum PinNumber
  {
    DIO_ALL = 0,
    DIO0 = 50, DIO1 = 51, DIO2 = 52, DIO3 = 53,
    DIO4 = 54, DIO5 = 55, DIO6 = 56, DIO7 = 57
  };
  enum PinDirection
  {
    INPUT, OUTPUT
  };
  enum PinValue
  {
    LOW, HIGH
  };

  GeneGPIO();
  ~GeneGPIO();
  void initGPIO();
  void closeGPIO();
  void exportPin(uint16_t pin_num);
  void unexportPin(uint16_t pin_num);
  void setDirection(uint16_t pin_num, uint16_t direction);
  int readValue(uint16_t pin_num);
  void writeValue(uint16_t pin_num, uint16_t value);
};
