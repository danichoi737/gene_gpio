# GENE-SKU6 GPIO

## INSTALL AAEON GPIO DRIVER
Check the GENE-SKU6 User's manual

## ADD GROUP 'GPIO'
```
$ sudo groupadd gpio
$ sudo adduser "$USER" gpio
```

## ADD GPIO RULES
```
$ cd scripts
$ chmod +x create_gpio_rules
$ ./create_gpio_rules
```

## RUN TEST CODE
```
$ mkdir build && cd build
$ cmake ..
$ ./gpio_test
```
