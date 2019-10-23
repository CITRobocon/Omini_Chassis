# Omini_Chassis

## cubeMX pin configurations
* **System Core**
  * **RCC**
    > <dl>
    >  <dt>High Speed Clock (HSE): BYPASS Clock Source</dt>
    > </dl>
    >
    > <dl>
    >  <dt>Low Speed Clock (LSE): Crystal/Ceramic Resonator</dt>
    > </dl>

* **Timers**
  * **TIM1**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>Left enoder (plus direction)</dd>
    > </dl>
      
  * **TIM2**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>Front right motor (forward)</dd>
    >
    >  <dt>Channel3: PWM Generation CH3</dt>
    >  <dd>Front left motor (backward)</dd>
    >
    >  <dt>Channel4: PWM Generation CH4</dt>
    >  <dd>Front left motor (forward)</dd>
    > </dl>
    
  * **TIM3**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>Front enoder (minus direction)</dd>
    > </dl>
    
  * **TIM4**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>Right enoder (plus direction)</dd>
    > </dl>
      
  * **TIM7**
    > <dl>
    >  <dt>Activated</dt>
    >  <dd>Timer interrupt</dd>
    > </dl>
      
  * **TIM8**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>Rear right motor (backward)</dd>
    >
    >  <dt>Channel2: PWM Generation CH2</dt>
    >  <dd>?</dd>
    >
    >  <dt>Channel3: PWM Generation CH3</dt>
    >  <dd>Rear right motor (forward)</dd>
    >
    >  <dt>Channel4: PWM Generation CH4</dt>
    >  <dd>Rear left motor (backward)</dd>
    > </dl>
      
  * **TIM9**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>Front right motor (backward)</dd>
    >
    >  <dt>Channel2: PWM Generation CH2</dt>
    >  <dd>Front left motor (forward)</dd>

* **Conectivity**
  * **CAN**
    > <dl>
    >  <dt>Master Mode</dt>
    > </dl>
    
  * **ETH**
    > <dl>
    >  <dt>RMII</dt>
    > </dl>
    
  * **UART4**
    > <dl>
    >  <dt>Mode: Asynchronous</dt>
    >  <dd>Connection between Linux PC and stm32</dd>
    > </dl>
    
  * **USART3**
    > <dl>
    >  <dt>Mode: Asynchronous</dt>
    >  <dd>Connection between debugging PC and stm32</dd>
    > </dl>
    
  * **USB_OTG_FS**
    > <dl>
    >  <dt>Mode: Device_Only</dt>
    >  <dt>Active_SOF</dt>
    >  <dt>Active_VBUS</dt>
    > </dl>
