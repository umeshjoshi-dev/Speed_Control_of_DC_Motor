# Results & Observations

## Experimental Setup

- **Location:** Silicon Control System, Dombivali (E), Maharashtra
- **Period:** January 2018 – March 2018
- **Supply Voltage:** 230V DC
- **Motor Rated Speed:** 2000 RPM

---

## Oscilloscope Observations (PWM Waveforms)

PWM waveforms were captured at different duty cycle settings using an oscilloscope.

| Test | Duty Cycle (%) | Average Voltage (V) | Observed Motor Speed |
|------|---------------|---------------------|----------------------|
| 1 | ~10% | ~23 V | Low (motor just starting) |
| 2 | ~25% | ~57.5 V | ~500 RPM |
| 3 | ~50% | ~115 V | ~1000 RPM |
| 4 | ~75% | ~172.5 V | ~1500 RPM |
| 5 | ~100% | ~230 V | ~2000 RPM (rated) |

> Actual waveform screenshots captured in Proteus simulation are included in the project report PDF.

---

## Key Observations

1. **Speed proportional to duty cycle:** Motor speed increased smoothly and proportionally as duty cycle increased — confirming the PWM control principle.

2. **Speed stability under load:** When load was applied within rated capacity, motor speed remained stable. The closed-loop nature of the IGBT chopper maintained consistent average voltage.

3. **Soft Start working correctly:** The motor ramped from 0 to operating speed over 20 seconds, preventing inrush current surge.

4. **Smooth Stop working correctly:** On pressing the stop button, the motor decelerated gradually over ~15 seconds, preventing sudden mechanical stress.

5. **LCD real-time display:** Duty cycle (%) and equivalent voltage (V) updated in real-time on the LCD at each potentiometer position change.

6. **Keypad control:** User could enter any speed percentage from 000 to 100. Motor responded correctly to each input.

---

## Simulation Results (Proteus ISIS)

The circuit was first simulated in Proteus ISIS before hardware implementation:
- PWM waveforms at various duty cycles matched theoretical values
- IGBT switching behavior verified
- Gate drive optocoupler isolation verified
- Motor response to duty cycle changes confirmed

---

## Conclusion

The project successfully demonstrated:
- Smooth, stepless speed control of a DC motor from 0 to 2000 RPM
- Reliable IGBT-based chopper operation at 230V DC
- Arduino-generated PWM as an effective, low-cost control solution
- Proper electrical isolation between control and power circuits
- Real-time monitoring via LCD display

The total project cost was **₹9,500**, making it a practical and cost-effective solution for industrial DC motor speed control applications.

---

## Future Scope

1. Adding a **speed feedback sensor** (tachometer/encoder) for true closed-loop PID speed control
2. Implementing **regenerative braking** to recover energy during motor deceleration
3. Extending to **AC motor control** using VFD (Variable Frequency Drive) principles
4. Adding **IoT connectivity** to monitor and control motor speed remotely
5. Scaling to higher power motors for industrial applications
