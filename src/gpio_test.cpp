/*
 *  GENE-SKU6 GPIO Test code
 */

#include <csignal>
#include "gene_gpio.hpp"

/* GPIO class */
GeneGPIO gene_gpio;

/* Time */
static struct timespec ts_sec_1 = {.tv_sec = 1, .tv_nsec = 0};


void signal_handler(int signal)
{
  std::cout << std::endl;

  gene_gpio.closeGPIO();
  exit(signal);
}

int main(int argc, char **argv)
{
  // Install a signal handler
  signal(SIGINT, signal_handler);

  // Use all pin
  gene_gpio.exportPin(GeneGPIO::PinNumber::DIO_ALL);

  // OUTPUT Test
  gene_gpio.setDirection(GeneGPIO::PinNumber::DIO_ALL, GeneGPIO::PinDirection::OUTPUT);
  // Value: HIGH
  for (uint16_t pin = GeneGPIO::PinNumber::DIO0; pin < GeneGPIO::PinNumber::DIO3; pin++)
  {
    gene_gpio.writeValue(pin, GeneGPIO::PinValue::HIGH);
    std::cout << "[TEST] " << pin << ": HIGH" << std::endl;
    nanosleep(&ts_sec_1, NULL);
  }
  // Value: LOW
  for (uint16_t pin = GeneGPIO::PinNumber::DIO0; pin < GeneGPIO::PinNumber::DIO3; pin++)
  {
    gene_gpio.writeValue(pin, GeneGPIO::PinValue::LOW);
    std::cout << "[TEST] " << pin << ": LOW" << std::endl;
    nanosleep(&ts_sec_1, NULL);
  }

  // INPUT Test
  gene_gpio.setDirection(GeneGPIO::PinNumber::DIO_ALL, GeneGPIO::PinDirection::INPUT);
  // Read value
  uint16_t _count = 1;
  while (_count <= 10)
  {
    std::cout << "[TEST] READ " << _count << "\t";
    for (uint16_t pin = GeneGPIO::PinNumber::DIO0; pin < GeneGPIO::PinNumber::DIO7 + 1; pin++)
    {
      std::cout << pin << ": " << gene_gpio.readValue(pin) << "\t";
    }
    std::cout << std::endl;

    nanosleep(&ts_sec_1, NULL);
    _count++;
  }

  // Close all pin
  gene_gpio.closeGPIO();

  return 0;
}
