/*
 *  GENE-SKU6 GPIO control
 *  Chipset: F81866
 */

#include "gene_gpio.hpp"


GeneGPIO::GeneGPIO()
{}

GeneGPIO::~GeneGPIO()
{}

void GeneGPIO::initGPIO()
{}

void GeneGPIO::closeGPIO()
{
  for (auto _pin : pin_array_)
  {
    // Make sure the pin direction is INPUT
    if (pin_direction_[_pin - 50] == PinDirection::OUTPUT)
    {
      setDirection(_pin, PinDirection::INPUT);
    }
    unexportPin(_pin);
  }
}

void GeneGPIO::exportPin(uint16_t pin_num)
{
  std::string _path = SYSFS_GPIO + EXPORT;

  if (pin_num == DIO_ALL)
  {
    for (auto _pin : pin_array_)
    {
      gpio_fstream_.open(_path, std::ios_base::out);
      if (gpio_fstream_.is_open())
      {
        gpio_fstream_ << _pin;
        gpio_fstream_.close();
        nanosleep(&ts_msec_100, NULL);
      }
      else
      {
        std::cerr << "[GPIO] Export failed: " << _path << " doesn't exist" << std::endl;
      }
    }
  }
  else if (pin_num >= DIO0 && pin_num <= DIO7)
  {
    gpio_fstream_.open(_path, std::ios_base::out);
    if (gpio_fstream_.is_open())
    {
      gpio_fstream_ << pin_num;
      gpio_fstream_.close();
      nanosleep(&ts_msec_100, NULL);
    }
    else
    {
      std::cerr << "[GPIO] Export failed: " << _path << " doesn't exist" << std::endl;
    }
  }
  else
  {
    std::cerr << "[GPIO] Export failed: Pin number " << pin_num << " doesn't exist" << std::endl;
  }
}

void GeneGPIO::unexportPin(uint16_t pin_num)
{
  std::string _path = SYSFS_GPIO + UNEXPORT;

  if (pin_num == DIO_ALL)
  {
    for (auto _pin : pin_array_)
    {
      gpio_fstream_.open(_path, std::ios_base::out);
      if (gpio_fstream_.is_open())
      {
        gpio_fstream_ << _pin;
        gpio_fstream_.close();
        nanosleep(&ts_msec_100, NULL);
      }
      else
      {
        std::cerr << "[GPIO] Unexport failed: " << _path << " doesn't exist" << std::endl;
      }
    }
  }
  else if (pin_num >= DIO0 && pin_num <= DIO7)
  {
    gpio_fstream_.open(_path, std::ios_base::out);
    if (gpio_fstream_.is_open())
    {
      gpio_fstream_ << pin_num;
      gpio_fstream_.close();
      nanosleep(&ts_msec_100, NULL);
    }
    else
    {
      std::cerr << "[GPIO] Unexport failed: " << _path << " doesn't exist" << std::endl;
    }
  }
  else
  {
    std::cerr << "[GPIO] Unexport failed: Pin number " << pin_num << " doesn't exist" << std::endl;
  }
}

void GeneGPIO::setDirection(uint16_t pin_num, uint16_t direction)
{
  if (pin_num == DIO_ALL)
  {
    for (auto _pin : pin_array_)
    {
      std::string _path = SYSFS_GPIO + GPIO_DIR + std::to_string(_pin) + DIRECTION;
      gpio_fstream_.open(_path, std::ios_base::out);
      if (gpio_fstream_.is_open())
      {
        switch (direction)
        {
        case INPUT:
          gpio_fstream_ << "in";
          gpio_fstream_.close();
          pin_direction_[_pin - 50] = PinDirection::INPUT;
          nanosleep(&ts_msec_100, NULL);
          break;

        case OUTPUT:
          gpio_fstream_ << "out";
          gpio_fstream_.close();
          pin_direction_[_pin - 50] = PinDirection::OUTPUT;
          nanosleep(&ts_msec_100, NULL);
          break;

        default:
          std::cerr << "[GPIO] Invalid direction: " << direction << std::endl;
          break;
        }
      }
      else
      {
        std::cerr << "[GPIO] Set direction failed: " << _path << " doesn't exist" << std::endl;
      }
    }
  }
  else if (pin_num >= DIO0 && pin_num <= DIO7)
  {
    std::string _path = SYSFS_GPIO + GPIO_DIR + std::to_string(pin_num) + DIRECTION;
    gpio_fstream_.open(_path, std::ios_base::out);
    if (gpio_fstream_.is_open())
    {
      switch (direction)
      {
      case INPUT:
        gpio_fstream_ << "in";
        gpio_fstream_.close();
        pin_direction_[pin_num - 50] = PinDirection::INPUT;
        nanosleep(&ts_msec_100, NULL);
        break;

      case OUTPUT:
        gpio_fstream_ << "out";
        gpio_fstream_.close();
        pin_direction_[pin_num - 50] = PinDirection::OUTPUT;
        nanosleep(&ts_msec_100, NULL);
        break;

      default:
        std::cerr << "[GPIO] Invalid direction: " << direction << std::endl;
        break;
      }
    }
    else
    {
      std::cerr << "[GPIO] Set direction failed: " << _path << " doesn't exist" << std::endl;
    }
  }
  else
  {
    std::cerr << "[GPIO] Pin number " << pin_num << " doesn't exist" << std::endl;
  }
}

int GeneGPIO::readValue(uint16_t pin_num)
{
  std::string _path = SYSFS_GPIO + GPIO_DIR + std::to_string(pin_num) + VALUE;
  gpio_fstream_.open(_path, std::ios_base::in);
  if (gpio_fstream_.is_open())
  {
    char _value;
    gpio_fstream_.get(_value);
    gpio_fstream_.close();

    if (_value == '0')
    {
      return LOW;
    }
    else
    {
      return HIGH;
    }
  }
  else
  {
    std::cerr << "[GPIO] Read value failed: " << _path << " doesn't exist" << std::endl;
    return -1;
  }
}

void GeneGPIO::writeValue(uint16_t pin_num, uint16_t value)
{
  if (pin_num >= DIO0 && pin_num <= DIO7)
  {
    if (value == LOW || value == HIGH)
    {
      std::string _path = SYSFS_GPIO + GPIO_DIR + std::to_string(pin_num) + VALUE;
      gpio_fstream_.open(_path, std::ios_base::out);
      if (gpio_fstream_.is_open())
      {
        gpio_fstream_ << value;
        gpio_fstream_.close();
      }
      else
      {
        std::cerr << "[GPIO] Write value failed: " << _path << " doesn't exist" << std::endl;
      }
    }
    else
    {
      std::cerr << "[GPIO] Write value failed: Invalid value " << value << std::endl;
    }
  }
  else
  {
    std::cerr << "[GPIO] Pin number " << pin_num << " doesn't exist" << std::endl;
  }
}
