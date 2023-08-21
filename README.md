# ESP-IDF-ADXL345

This is an example of adxl345 accelerometer controlled by ESP32 under ESP-IDF

## How to start

Set up the environment variables.(if you followed the official [doc](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html))

```bash
. $HOME/esp/esp-idf/export.sh
```

Go to the _/example_ directory (/esp-idf-adxl345/example) and configure the project. My target is esp32

```bash
idf.py set-target esp32
idf.py menuconfig
```

Build

```bash
idf.py build
```

flash and monitor

```bash
idf.py -p PORT flash monitor
```

PORT is something like **/dev/ttyUSB0**, you can check it out by

```bash
ls /dev/tty*
```

## Expected output

```bash
I (339) SYSTEM: INTERFACE is i2c
I (339) SYSTEM: CONFIG_SDA_GPIO=21
I (349) SYSTEM: CONFIG_SCL_GPIO=22
I (349) ADXL345: devid=e5
I (349) ADXL345: ADXL345 set to measure mode
I (359) ADXL345: x=5, y=-14, z=244
I (459) ADXL345: x=5, y=-13, z=244
I (559) ADXL345: x=6, y=-13, z=244
I (659) ADXL345: x=5, y=-13, z=244
I (759) ADXL345: x=4, y=-13, z=245
I (859) ADXL345: x=5, y=-13, z=243
I (959) ADXL345: x=5, y=-13, z=244
I (1059) ADXL345: x=6, y=-13, z=245
```

## License

[MIT](https://choosealicense.com/licenses/mit/)
