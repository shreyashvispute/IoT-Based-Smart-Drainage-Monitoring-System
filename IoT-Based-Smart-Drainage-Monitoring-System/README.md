# IoT-Based Smart Drainage Monitoring System

An IoT prototype built around a NodeMCU ESP8266 to monitor drainage conditions using ultrasonic distance sensing, air-quality sensing and temperature/humidity sensing. Measurements are displayed locally and sent to the Blynk IoT platform.

## Project at a glance

- **Controller:** NodeMCU ESP8266
- **Water / blockage monitoring:** Two ultrasonic sensor channels
- **Air-quality monitoring:** MQ-135 analog output
- **Environmental monitoring:** DHT11 temperature and humidity sensor
- **Local interface:** 16×2 LCD with I²C backpack
- **Alert output:** Buzzer connected to D0 (as represented in the supplied sketch)
- **IoT platform:** Blynk

## Repository contents

| Folder | Contents |
|---|---|
| `Code/` | ESP8266 Arduino sketch |
| `Circuit_Diagram/` | Supplied system block diagram |
| `Images/` | Representative prototype and LCD stills extracted from the supplied demo video |
| `Research_Paper/` | Research paper PDF and paper metadata |
| `Documentation/` | Uploaded project document and implementation notes |
| `Results/` | Add serial monitor, LCD and Blynk screenshots |
| `Dashboard/` | Add Blynk dashboard screenshots or exports, if available |
| `Video/` | Original project demonstration video |

## Working principle

1. The NodeMCU reads the two ultrasonic sensor channels to estimate distance inside two monitored pipe locations.
2. The MQ-135 analog output is read through the ESP8266 analog input.
3. The DHT11 provides temperature and relative-humidity readings.
4. Readings are printed to the Serial Monitor and selected values are shown on the 16×2 I²C LCD.
5. The sketch sends readings to Blynk virtual pins V0–V4.
6. When either ultrasonic distance reading is at or below the configured 3 cm threshold, the sketch logs a Blynk event (`pipe_1_blocked` or `pipe_2_blocked`) and activates the buzzer output.

> The 3 cm threshold is the value in the supplied code. Calibrate it for the physical pipe geometry before relying on it.

## Pin mapping in the supplied sketch

| Module / signal | NodeMCU pin |
|---|---|
| DHT11 data | D3 |
| MQ-135 analog output | A0 |
| Ultrasonic 1 TRIG | D8 |
| Ultrasonic 1 ECHO | D7 |
| Ultrasonic 2 TRIG | D6 |
| Ultrasonic 2 ECHO | D5 |
| Buzzer output | D0 |
| I²C LCD | SDA/SCL according to your board wiring; LCD address configured as `0x27` |

Confirm the actual wiring against your built hardware before powering the circuit. The uploaded block diagram is a system-level diagram and does not show every pin-level connection.

## Software and libraries

- Arduino IDE
- ESP8266 board support package
- `ESP8266WiFi`
- `Blynk`
- `DHT sensor library`
- `LiquidCrystal_I2C`
- `Wire`

## Setup

1. Install the ESP8266 board package and the libraries listed above.
2. Open `Code/smart_drainage_monitoring.ino` in Arduino IDE.
3. Replace `YOUR_BLYNK_TEMPLATE_ID`, `YOUR_BLYNK_TEMPLATE_NAME`, `YOUR_BLYNK_AUTH_TOKEN`, `YOUR_WIFI_SSID` and `YOUR_WIFI_PASSWORD` with local values.
4. In Blynk, configure virtual pins V0 (temperature), V1 (humidity), V2 (MQ-135 analog reading), V3 (ultrasonic channel 1 distance) and V4 (ultrasonic channel 2 distance).
5. Configure Blynk event codes `pipe_1_blocked` and `pipe_2_blocked` if you want those event notifications.
6. Select the correct ESP8266 board and COM port, then upload and test.

## Important safety and validation notes

- **Credentials:** Never commit Wi-Fi passwords or Blynk authentication tokens to a public repository. The sketch in this repository uses placeholders. If real credentials were previously exposed, rotate the Blynk token and change the Wi-Fi password as appropriate.
- **Ultrasonic voltage:** Many HC-SR04 modules use a 5 V supply and can output a 5 V ECHO signal. ESP8266 GPIOs are 3.3 V logic and are not 5 V tolerant. Use a suitable voltage divider or level shifter on each ECHO line, and verify the sensor module's specifications.
- **MQ-135:** The sensor requires appropriate heater power and calibration. Its raw ADC value is not a calibrated ppm gas concentration. Check the exact MQ-135 module supply/output requirements and the NodeMCU A0 input range.
- **DHT11:** Handle failed readings; the DHT library can return `NaN`.
- **Blynk loop timing:** Blocking `delay()` calls and long sensor reads can affect cloud responsiveness. Consider a non-blocking `BlynkTimer` implementation for a later revision.
- **Physical testing:** Test with safe, controlled conditions. Do not enter drains or expose people to sewer gases as part of testing.

## Documentation note

The uploaded PDF has been placed in `Documentation/` as supplied. It contains some hardware-description differences from the provided sketch (for example, it mentions a single ultrasonic sensor and MQ-2 in one circuit-description section, while the sketch uses two ultrasonic channels and an MQ-135). Review and reconcile those sections before presenting the PDF as final project documentation.

## Research paper

The repository includes **“IoT Based Smart Drainage Monitoring System With Real Time Alert Messages”** in `Research_Paper/`. The paper lists Shreyash Vispute, Abhijit Bhgwat, Kiran Kasbe, Kiran Khairnar and Prof. S. A. Suryawanshi as authors, and identifies the *International Journal of Research Publication and Reviews* (ISSN 2582-7421). See [`Research_Paper/README.md`](Research_Paper/README.md) for the metadata visible in the supplied PDF. A DOI, volume, issue and publication year were not visible in the supplied copy.

## Author

Shreyash Vispute

## License

MIT License (add a `LICENSE` file if you choose to distribute the source under MIT terms).
