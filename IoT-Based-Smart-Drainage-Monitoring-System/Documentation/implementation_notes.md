# Implementation notes and verification checklist

## Confirmed from the supplied sketch
- NodeMCU ESP8266
- DHT11 on D3
- MQ-135 analog reading on A0
- Ultrasonic channel 1: TRIG D8, ECHO D7
- Ultrasonic channel 2: TRIG D6, ECHO D5
- 16x2 I2C LCD configured at address 0x27
- Buzzer/output on D0
- Blynk virtual pins V0–V4
- Blockage event names: `pipe_1_blocked`, `pipe_2_blocked`
- Blockage threshold: distance <= 3 cm

## Before final demonstration
- Confirm exact LCD SDA/SCL wiring and I2C address.
- Confirm the buzzer is electrically suitable for direct GPIO drive; use a transistor driver if required.
- Confirm ultrasonic ECHO voltage is reduced to a safe 3.3 V level.
- Confirm MQ-135 module output is within the ESP8266 A0 input range.
- Calibrate sensor readings and threshold using the actual pipe arrangement.
- Add DHT read-error handling and consider replacing blocking delays with a timer.
- Verify Blynk template, datastreams, event names and mobile notifications.

## Difference between supplied diagram, PDF and sketch
The block diagram depicts a gas sensor, ultrasonic water-level sensing, NodeMCU, Blynk, LCD, buzzer and mobile notifications. The sketch additionally specifies DHT11, MQ-135 and two ultrasonic channels. The uploaded PDF's circuit explanation contains different sensor/pin details in places. The repository README follows the supplied sketch for code pin mapping and flags the PDF for review rather than silently treating the descriptions as identical.
