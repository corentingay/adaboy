/*
 * File : word_operations.hpp
 *
 * File created by : Corentin Gay
 * File was created at : 06/12/2017
 */

#pragma once

using uint16_t = unsigned short int;
using int16_t = signed short int;
using uint8_t = unsigned char;
using int8_t = signed char;
using size_t = unsigned long long;
using uint = unsigned int;

uint16_t make_word(uint8_t low, uint8_t high);
uint8_t get_high(uint16_t word);
uint8_t get_low(uint16_t word);
