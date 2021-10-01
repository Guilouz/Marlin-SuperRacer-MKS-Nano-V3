/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "../../inc/MarlinConfigPre.h"

#if ENABLED(EMERGENCY_PARSER)
  #include "../../feature/e_parser.h"
#endif

#include "../../core/serial_hook.h"

typedef void (*usart_rx_callback_t)(serial_t * obj);

struct MarlinSerial : public HardwareSerial {
  MarlinSerial(void* peripheral, usart_rx_callback_t rx_callback) :
      HardwareSerial(peripheral), _rx_callback(rx_callback)
  { }

  void begin(unsigned long baud, uint8_t config);
  inline void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }

  void _rx_complete_irq(serial_t* obj);

protected:
  usart_rx_callback_t _rx_callback;
};

typedef Serial0Type<MarlinSerial> MSerialT;
extern MSerialT MSerial1;
extern MSerialT MSerial2;
extern MSerialT MSerial3;
extern MSerialT MSerial4;
extern MSerialT MSerial5;
extern MSerialT MSerial6;
extern MSerialT MSerial7;
extern MSerialT MSerial8;
extern MSerialT MSerial9;
extern MSerialT MSerial10;
extern MSerialT MSerialLP1;
#define IDLE        0
#define WORKING     1
#define PAUSING     2
#define PAUSE       3
#define REPRINTING  4
#define REPRINTED   5
#define RESUMING    6
#define STOP        7
void change_button(int adress_high,int adress_low,int var);
void jump_to(int adress);
void get_serial1_commands(void);
void print_thr_count_page(int file_count,int page_flage);
void print_thr_adress_string(int high_adress,int low_adress,char *src);
void buf_clear(int high_adress,int low_adress,int num);
void printer_state_deal();
void pause_resume();
void change_en();
void change_zh_CN();
void change_zh_TW();
void change_ru();
void change_fr();
void change_es();
void change_de();
void change_jp();
void enable_buzzer();
void disable_buzzer();