# Circuit Description

## DC Chopper Circuit with IGBT and Arduino PWM

### Overall Block Diagram

```
[230V DC Supply]
      |
      v
[DC Chopper Stage]
  - IGBT (switching device)
  - Freewheeling Diode
  - Inductor (smoothing)
  - Capacitor (filtering)
      |
      v
[DC Motor Load]  <--- speed varies with average voltage
      |
      ^
[Gate Drive Circuit]
  - Optocoupler IC (isolation + amplification)
      |
      ^
[Arduino UNO]
  - Generates PWM signal (Pin 10)
  - Reads input from Potentiometer (A0) OR Keypad
  - Displays data on 20x4 LCD
```

---

## Components and Their Roles

### 1. Arduino UNO
- Acts as the **PWM signal generator** and controller
- Reads analog input from the potentiometer (or digital input from keypad)
- Sends PWM signal to the gate drive circuit
- Drives the 20x4 LCD for real-time display of duty cycle and voltage

### 2. IGBT (Insulated Gate Bipolar Transistor)
- Acts as the **main switching device** in the chopper circuit
- Turns ON and OFF at high frequency based on PWM signal
- Capable of handling the full 230V / high-current DC motor load
- Mounted on a heat sink to dissipate heat

### 3. Gate Drive Circuit (Optocoupler-based)
- **Two functions:**
  1. **Isolation:** Separates the low-voltage Arduino control circuit from the high-voltage power circuit (safety)
  2. **Amplification:** Boosts the Arduino's 5V PWM signal to the voltage level needed to drive the IGBT gate
- Prevents damage to the Arduino from power-side surges

### 4. Freewheeling Diode
- Connected in anti-parallel with the DC motor load
- Provides a path for the inductive motor current when the IGBT switches OFF
- Prevents destructive voltage spikes

### 5. Inductor
- Connected in series with the motor
- Smooths out the current waveform (reduces ripple)
- Helps maintain continuous motor current even during IGBT OFF periods

### 6. Capacitor
- Connected across the DC bus
- Filters voltage ripple
- Stabilizes the DC supply voltage

### 7. 20×4 LCD Display
- Connected to Arduino in 4-bit mode
- Displays:
  - Welcome message on startup
  - Soft start / smooth stop status
  - Real-time **Duty Cycle (%)** and **Voltage (V)** during operation

---

## Pin Connections (Arduino UNO)

| Arduino Pin | Connected To |
|-------------|-------------|
| Pin 10 (PWM) | Gate Drive Circuit Input |
| Pin A0 | Potentiometer (wiper terminal) |
| Pin 8 | LCD RS |
| Pin A1 | LCD EN |
| Pin A2 | LCD D4 |
| Pin A3 | LCD D5 |
| Pin A4 | LCD D6 |
| Pin A5 | LCD D7 |
| Pin 5 | Stop Button |
| Pin 4 | Start/Restart Button |
| Pin 11 | Motor Direction Control 1 |
| Pin 12 | Motor Direction Control 2 |

**For Keypad Control mode:**

| Arduino Pin | Keypad |
|-------------|--------|
| Pin 9 | Row 1 |
| Pin 8 | Row 2 |
| Pin 7 | Row 3 |
| Pin 6 | Row 4 |
| Pin 5 | Col 1 |
| Pin 4 | Col 2 |
| Pin 3 | Col 3 |

---

## Working Principle — PWM Speed Control

The average DC voltage delivered to the motor is controlled by the **duty cycle** of the PWM signal:

```
Average Voltage = Duty Cycle × Supply Voltage
                = (t_on / T) × 230V
```

Where:
- `t_on` = time IGBT is ON in one cycle
- `T` = total period of one PWM cycle

| Duty Cycle | Average Voltage | Approx. Motor Speed |
|------------|-----------------|---------------------|
| 0% | 0 V | 0 RPM |
| 25% | 57.5 V | ~500 RPM |
| 50% | 115 V | ~1000 RPM |
| 75% | 172.5 V | ~1500 RPM |
| 100% | 230 V | ~2000 RPM (rated) |

---

## Safety Notes

- The circuit operates at **230V DC** — appropriate precautions and insulation are required
- The IGBT must be properly mounted on its heat sink at all times during operation
- The gate drive optocoupler ensures the Arduino is fully isolated from the high-voltage side
- The soft-start function prevents motor inrush current at startup

---

*Circuit was designed, simulated in Proteus ISIS, and then implemented in hardware at Silicon Control System, Dombivali during January–March 2018.*
