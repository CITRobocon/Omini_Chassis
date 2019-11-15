# Omini_Chassis
## Headers
* **physical**
  > <dl>
  >  <dt>physical.h</dt>
  >  <dd>物理定数定義ヘッダ</dd>
  > </dl>
  
* **ticker**
  > <dl>
  >  <dt>ticker/ticker.h</dt>
  >  <dd>タイマ割り込み管理プログラム</dd>
  > </dl>
  
* **scom**
  > <dl>
  >  <dt>scom/scom.h, src: scom/scom.c</dt>
  >  <dd>シリアル通信管理プログラム</dd>
  > </dl>
  
* **filters**
  > <dl>
  >  <dt>filters/filters.h</dt>
  >  <dd>フィルタリング処理プログラム</dd>
  > </dl>
  
* **odometry**
  > <dl>
  >  <dt>odometry/odometry.h</dt>
  >  <dd>オドメトリ計算プログラム</dd>
  > </dl>

<br>

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
    >  <dd>エンコーダカウンタ（左エンコーダ/正方向）</dd>
    > </dl>
      
  * **TIM2**
    > <dl>
    >  <dt>Channel1: PWM Generation CH1</dt>
    >  <dd>モータドライバ信号（右前モータ/前進方向）</dd>
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
    >  <dd>エンコーダカウンタ（前エンコーダ/負方向）</dd>
    > </dl>
    
  * **TIM4**
    > <dl>
    >  <dt>Combined Channels: Encoder Mode</dt>
    >  <dd>エンコーダカウンタ（右エンコーダ/正方向）</dd>
    > </dl>
      
  * **TIM7**
    > <dl>
    >  <dt>Activated</dt>
    >  <dd>タイマ割り込み（ticker管理）</dd>
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
