pragma Warnings (Off);
pragma Ada_95;
pragma Restrictions (No_Exception_Propagation);
with System;
package ada_main is


   GNAT_Version : constant String :=
                    "GNAT Version: GPL 2017 (20170515-63)" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_draw" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure main;
   pragma Export (C, main, "main");

   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  interfaces%s
   --  system%s
   --  ada.exceptions%s
   --  ada.exceptions%b
   --  interfaces.stm32%s
   --  system.bb%s
   --  system.bb.board_parameters%s
   --  system.machine_code%s
   --  system.parameters%s
   --  system.parameters%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  system.task_info%s
   --  system.task_info%b
   --  system.unsigned_types%s
   --  interfaces.stm32.pwr%s
   --  interfaces.stm32.rcc%s
   --  system.bb.mcu_parameters%s
   --  system.bb.mcu_parameters%b
   --  system.stm32%s
   --  system.bb.parameters%s
   --  system.stm32%b
   --  system.assertions%s
   --  system.assertions%b
   --  system.secondary_stack%s
   --  system.secondary_stack%b
   --  ada.tags%s
   --  ada.tags%b
   --  system.multiprocessors%s
   --  system.bb.time%s
   --  system.bb.timing_events%s
   --  system.bb.interrupts%s
   --  system.bb.protection%s
   --  system.bb.cpu_primitives%s
   --  system.bb.board_support%s
   --  system.multiprocessors%b
   --  system.multiprocessors.spin_locks%s
   --  system.multiprocessors.spin_locks%b
   --  system.bb.board_support%b
   --  system.bb.cpu_primitives.multiprocessors%s
   --  system.multiprocessors.fair_locks%s
   --  system.bb.threads%s
   --  system.bb.threads.queues%s
   --  system.bb.threads.queues%b
   --  system.bb.protection%b
   --  system.bb.threads%b
   --  system.bb.cpu_primitives%b
   --  system.bb.cpu_primitives.multiprocessors%b
   --  system.os_interface%s
   --  system.multiprocessors.fair_locks%b
   --  system.bb.time%b
   --  system.bb.timing_events%b
   --  system.bb.interrupts%b
   --  system.task_primitives%s
   --  system.tasking%s
   --  system.tasking.debug%s
   --  system.tasking.debug%b
   --  system.task_primitives.operations%s
   --  system.tasking%b
   --  system.task_primitives.operations%b
   --  ada.real_time%s
   --  ada.real_time%b
   --  ada.real_time.delays%s
   --  ada.real_time.delays%b
   --  system.tasking.protected_objects%s
   --  system.tasking.protected_objects%b
   --  system.tasking.protected_objects.multiprocessors%s
   --  system.tasking.protected_objects.multiprocessors%b
   --  system.tasking.protected_objects.single_entry%s
   --  system.tasking.protected_objects.single_entry%b
   --  system.tasking.restricted%s
   --  system.tasking.restricted.stages%s
   --  system.tasking.restricted.stages%b
   --  ada.task_identification%s
   --  ada.task_identification%b
   --  system.interrupts%s
   --  system.interrupts%b
   --  ada.interrupts%s
   --  ada.interrupts%b
   --  ada.interrupts.names%s
   --  cortex_m%s
   --  cortex_m_svd%s
   --  hal%s
   --  cortex_m_svd.cache%s
   --  cortex_m_svd.pf%s
   --  cortex_m_svd.scb%s
   --  stm32%s
   --  stm32_svd%s
   --  stm32_svd.adc%s
   --  stm32_svd.dac%s
   --  stm32_svd.dma%s
   --  stm32_svd.dma2d%s
   --  stm32_svd.exti%s
   --  stm32_svd.fsmc%s
   --  stm32_svd.gpio%s
   --  stm32_svd.i2c%s
   --  stm32_svd.ltdc%s
   --  stm32_svd.pwr%s
   --  stm32_svd.rcc%s
   --  stm32_svd.rtc%s
   --  stm32_svd.sai%s
   --  stm32_svd.sdmmc%s
   --  sdmmc_svd%s
   --  stm32_svd.spi%s
   --  stm32_svd.syscfg%s
   --  bmp_fonts%s
   --  bmp_fonts%b
   --  cortex_m.cache%s
   --  cortex_m.cache%b
   --  hal.audio%s
   --  hal.bitmap%s
   --  bitmap_color_conversion%s
   --  bitmap_color_conversion%b
   --  hal.block_drivers%s
   --  hal.framebuffer%s
   --  hal.gpio%s
   --  hal.i2c%s
   --  hal.real_time_clock%s
   --  hal.sdmmc%s
   --  hal.sdmmc%b
   --  hal.spi%s
   --  hal.time%s
   --  hal.touch_panel%s
   --  ft5336%s
   --  ft5336%b
   --  hershey_fonts%s
   --  hershey_fonts%b
   --  bitmapped_drawing%s
   --  bitmapped_drawing%b
   --  ravenscar_time%s
   --  ravenscar_time%b
   --  sdmmc_init%s
   --  sdmmc_init%b
   --  sdmmc_svd_periph%s
   --  soft_drawing_bitmap%s
   --  soft_drawing_bitmap%b
   --  memory_mapped_bitmap%s
   --  memory_mapped_bitmap%b
   --  stm32.adc%s
   --  stm32.adc%b
   --  stm32.dac%s
   --  stm32.dac%b
   --  stm32.dma%s
   --  stm32.dma%b
   --  stm32.dma.interrupts%s
   --  stm32.dma.interrupts%b
   --  stm32.dma2d%s
   --  stm32.dma2d%b
   --  stm32.dma2d.interrupt%s
   --  stm32.dma2d.interrupt%b
   --  stm32.dma2d.polling%s
   --  stm32.dma2d.polling%b
   --  stm32.dma2d_bitmap%s
   --  stm32.dma2d_bitmap%b
   --  stm32.exti%s
   --  stm32.exti%b
   --  stm32.fmc%s
   --  stm32.fmc%b
   --  stm32.i2c%s
   --  stm32.i2c%b
   --  stm32.power_control%s
   --  stm32.power_control%b
   --  stm32.rcc%s
   --  stm32.rcc%b
   --  stm32.rtc%s
   --  stm32.rtc%b
   --  stm32.spi%s
   --  stm32.spi%b
   --  stm32.spi.dma%s
   --  stm32.spi.dma%b
   --  stm32.timers%s
   --  stm32.timers%b
   --  stm32.gpio%s
   --  stm32.sdmmc_interrupt%s
   --  stm32.i2s%s
   --  stm32.syscfg%s
   --  stm32.gpio%b
   --  stm32.sdmmc%s
   --  stm32.sdmmc_interrupt%b
   --  stm32.device%s
   --  stm32.device%b
   --  stm32.sdmmc%b
   --  stm32.i2s%b
   --  stm32.syscfg%b
   --  stm32.ltdc%s
   --  stm32.ltdc%b
   --  stm32.sai%s
   --  stm32.sai%b
   --  stm32.setup%s
   --  stm32.setup%b
   --  wm8994%s
   --  wm8994%b
   --  audio%s
   --  touch_panel_ft5336%s
   --  sdcard%s
   --  stm32.sdram%s
   --  framebuffer_ltdc%s
   --  framebuffer_rk043fn48h%s
   --  framebuffer_rk043fn48h%b
   --  stm32.board%s
   --  stm32.board%b
   --  sdcard%b
   --  stm32.sdram%b
   --  framebuffer_ltdc%b
   --  audio%b
   --  touch_panel_ft5336%b
   --  last_chance_handler%s
   --  last_chance_handler%b
   --  lcd_std_out%s
   --  lcd_std_out%b
   --  stm32.user_button%s
   --  stm32.user_button%b
   --  draw%b
   --  END ELABORATION ORDER

end ada_main;
