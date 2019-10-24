# Omini_Chassis

## cubeMX pin configurations (Last update: 2019/10/24 sano)
* **System Core**
  * **RCC**
    > <dl>
    >  <dt>High Speed Clock (HSE): BYPASS Clock Source</dt>
    >  <dt>Low Speed Clock (LSE): Crystal/Ceramic Resonator</dt>
    > </dl>

* **Timers**
  * **TIM1**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>エンコーダカウンタ（左/正方向）</dd>
    > </dl>
      
  * **TIM2**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>モータドライバ信号（右前モータ/前進方向）</dd>
    >  <dd>周期：500Hz</dd>
    >  <dd>入力範囲：0-1000</dd>
    >
    >  <dt>Channel3: PWM Generation CH3</dt>
    >  <dd>モータドライバ信号（左前モータ/後進方向）</dd>
    >
    >  <dt>Channel4: PWM Generation CH4</dt>
    >  <dd>モータドライバ信号（左前モータ/前進方向）</dd>
    > </dl>
    
  * **TIM3**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>エンコーダカウンタ（前/負方向）</dd>
    > </dl>
    
  * **TIM4**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>エンコーダカウンタ（右/正方向）</dd>
    > </dl>
      
  * **TIM7**
    > <dl>
    >  <dt>Activated</dt>
    >  <dd>タイマ割込（Ticker管理用）</dd>
    > </dl>
      
  * **TIM8**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>モータドライバ信号（右後モータ/後進方向）</dd>
    >
    >  <dt>Channel2: PWM Generation CH2</dt>
    >  <dd>?</dd>
    >
    >  <dt>Channel3: PWM Generation CH3</dt>
    >  <dd>モータドライバ信号（右後モータ/前進方向）</dd>
    >
    >  <dt>Channel4: PWM Generation CH4</dt>
    >  <dd>モータドライバ信号（左後モータ/後進方向）</dd>
    > </dl>
      
  * **TIM9**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>モータドライバ信号（右前モータ/後進方向）</dd>
    >
    >  <dt>Channel2: PWM Generation CH2</dt>
    >  <dd>モータドライバ信号（左前モータ/前進方向）</dd>

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
    >  <dd>シリアル通信（stm-LinuxPC）</dd>
    > </dl>
    
  * **USART3**
    > <dl>
    >  <dt>Mode: Asynchronous</dt>
    >  <dd>シリアル通信（stm-デバッグPC）</dd>
    > </dl>
    
  * **USB_OTG_FS**
    > <dl>
    >  <dt>Mode: Device_Only</dt>
    >  <dt>Active_SOF</dt>
    >  <dt>Active_VBUS</dt>
    > </dl>
