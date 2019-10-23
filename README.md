# Omini_Chassis

## cubeMX pin configuration
* Timers
  * TIM1  
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>Left enoder(plus direction)</dd>
    > </dl>
      
  * TIM2
    > * Channel1: PWM Generation CH1  
    >   `Front right motor(forward)`
    > * Channel3: PWM Generation CH3  
    >   `Front left motor(backward)`
    > * Chennel4: PWM Generation CH4  
    >   `Front left motor(forward)`
      
  * TIM7
    > * Activated  
        `Timer interrupt`
<details><summary>Timers</summary><div>
 
 <details><summary>TIM1</summary><div>
  <dl>
   <dt>Combined Channels: Encoder Mode</dt>
   <dd>Left enoder(plus direction)</dd>
  </dl>
 </div></details>
 
 <details><summary>TIM2</summary><div>
  <dl>
   <dt>Channel1: PWM Generation CH1</dt>
   <dd>Front right motor(forward)</dd>
   <dt>Channel3: PWM Generation CH3</dt>
   <dd>Front left motor(backward)</dd>
   <dt>Channel4: PWM Generation CH4</dt>
   <dd>Front left motor(forward)</dd>
  </dl>
 </div></details>
 
</div></details>
