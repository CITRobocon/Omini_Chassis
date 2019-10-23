# Omini_Chassis

## cubeMX pin configuration
* Timers
  * TIM1  
    > * Combined Channels: Encoder Mode  
    >   `Left encoder(plus direction)`
      
  * TIM2
    > * Channel1: PWM Generation CH1
    >   > Front right motor(forward)
    > * Channel3: PWM Generation CH3
    >   > Front left motor(backward)
    > * Chennel4: PWM Generation CH4
    >   > Front left motor(forward)
      
  * TIM7
    * Activated
      > Timer interrupt
