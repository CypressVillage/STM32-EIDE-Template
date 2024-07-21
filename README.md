# STM32-EIDE-Template

基于 [EIDE](https://github.com/github0null/eide) 的 stm32 模板工程，开箱即用。

## 可选编译环境

- Keil MDK (AC5)
- armcc
- gcc

## 可选 STM32 型号

- STM32F103C8Tx
- STM32F103RCTx

## 预添加库/驱动

- Lua 语言支持
- TinyMaix 支持
- CMSIS DSP 库
- fft 库
- u8g2 SSD1306_128x64_I2C 图形库
- ADS1115
- I2C
- OLED
- PWM
- 按键
- 串口通信
- WT1-IMU 陀螺仪

## 食用方法

### EIDE

1. 双击 template.code-workspace 打开工作区
2. 信任工作区并安装推荐扩展 EIDE
3. F7 编译

### Keil MDK

1. 双击 template.uvprojx 打开 Keil 工程
2. F7 编译

## 注意事项

- 请确保你的 EIDE 扩展正确设置了编译器路径并勾选了 `AutoSearchIncludePath` 选项
- 高版本 Keil MDK 不附带 armcc 编译器（AC5），需自行安装
- 目前 armcc 编译器无法编译 TinyMaix、u8g2，需要使用 gcc 编译器