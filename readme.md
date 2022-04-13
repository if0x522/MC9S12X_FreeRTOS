# MC9S12X 飞思卡尔单片机FreeRTOS移植

## 基于FreeRTOSV10.4，以使其能在HC12X上运行

文件结构：

* CODE/文件夹中为硬件相关配置，包括初始化PLL，配置输出串口，设置中断，系统心跳

* RTOS/文件夹中为FreeRTOS内核相关文件，这里只是复制，除PORT部分。