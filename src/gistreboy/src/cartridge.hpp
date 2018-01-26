#pragma once

#include <vector>
#include <array>
#include <string>
#include <fstream>

#include <memoryobject.hpp>

class Cartridge : public MemoryObject {

public :

	Cartridge(std::vector<std::pair<uint16_t, uint16_t>> range);
  
	// We use this method to change the currently running game.
	// The gameboy should not be running while calling it.
	// It initializes the rom and the ram to zero.
	void change_game(uint8_t *cart);

	uint8_t read(uint16_t address);
	void write(uint8_t byte, uint16_t address);  

	// FIXME: actually implement permissions
	bool can_read(uint16_t address);
	bool can_write(uint16_t address);

	bool ram_enable();
	bool has_boot();

	bool rom_ram_mode();
	bool has_ram();
	bool has_battery();
	bool has_timer();
	bool has_rumble();

private :

	//uint8_t get_current_rom_bank();
	//uint8_t get_current_ram_bank();

	/*the actual assembly of the cartridge separated in banks of 32kB */
	std::array<uint8_t, 2097152> rom;

  /* a program inside the gameboy that boots the machine
     and jumps to the location of the animated sequence
     inside the rom */

	//This array has been generated with the xd utility tool.
std::array<uint8_t,  256> boot_rom= { {
    0x31,0xFE,0xFF,0xAF,0x21,0xFF,0x9F,0x32,0xCB,0x7C,0x20,0xFB,0x21,0x26,
    0xFF,0x0E,0x11,0x3E,0x80,0x32,0xE2,0x0C,0x3E,0xF3,0xE2,0x32,0x3E,0x77,
    0x77,0x3E,0xFC,0xE0,0x47,0x11,0x04,0x01,0x21,0x10,0x80,0x1A,0xCD,0x95,
    0x00,0xCD,0x96,0x00,0x13,0x7B,0xFE,0x34,0x20,0xF3,0x11,0xD8,0x00,0x06,
    0x08,0x1A,0x13,0x22,0x23,0x05,0x20,0xF9,0x3E,0x19,0xEA,0x10,0x99,0x21,
    0x2F,0x99,0x0E,0x0C,0x3D,0x28,0x08,0x32,0x0D,0x20,0xF9,0x2E,0x0F,0x18,
    0xF3,0x67,0x3E,0x64,0x57,0xE0,0x42,0x3E,0x91,0xE0,0x40,0x04,0x1E,0x02,
    0x0E,0x0C,0xF0,0x44,0xFE,0x90,0x20,0xFA,0x0D,0x20,0xF7,0x1D,0x20,0xF2,
    0x0E,0x13,0x24,0x7C,0x1E,0x83,0xFE,0x62,0x28,0x06,0x1E,0xC1,0xFE,0x64,
    0x20,0x06,0x7B,0xE2,0x0C,0x3E,0x87,0xE2,0xF0,0x42,0x90,0xE0,0x42,0x15,
    0x20,0xD2,0x05,0x20,0x4F,0x16,0x20,0x18,0xCB,0x4F,0x06,0x04,0xC5,0xCB,
    0x11,0x17,0xC1,0xCB,0x11,0x17,0x05,0x20,0xF5,0x22,0x23,0x22,0x23,0xC9,
    0xCE,0xED,0x66,0x66,0xCC,0x0D,0x00,0x0B,0x03,0x73,0x00,0x83,0x00,0x0C,
    0x00,0x0D,0x00,0x08,0x11,0x1F,0x88,0x89,0x00,0x0E,0xDC,0xCC,0x6E,0xE6,
    0xDD,0xDD,0xD9,0x99,0xBB,0xBB,0x67,0x63,0x6E,0x0E,0xEC,0xCC,0xDD,0xDC,
    0x99,0x9F,0xBB,0xB9,0x33,0x3E,0x3C,0x42,0xB9,0xA5,0xB9,0xA5,0x42,0x3C,
    0x21,0x04,0x01,0x11,0xA8,0x00,0x1A,0x13,0xBE,0x20,0xFE,0x23,0x7D,0xFE,
    0x34,0x20,0xF5,0x06,0x19,0x78,0x86,0x23,0x05,0x20,0xFB,0x86,0x20,0xFE,
    0x3E,0x01,0xE0,0x50
} };

  /* the type of the cartidge see manual */
  uint8_t type = 0;

  /* the MBC of the cartridge, chip that will extend address space,
     no MBC is a simple 32kb cartidge like Tetris
     no MBC is 0, MM01 is 4 */
  int mbc = 0;

  /* the internal ram of the cartridge */
  std::array<uint8_t, 32768> ram;

  size_t rom_size = 0;
  size_t ram_size = 0;

  uint8_t current_rom_bank = 1;
  uint8_t current_ram_bank = 0; /* can be upper 2 bit of rom_bank_number */

  bool ram_enable_ = false;
  bool rom_ram_mode_ = false; /* false if rom mode, true if ram mode */

  bool has_ram_ = false;
  bool has_battery_ = false;
  bool has_timer_ = false;
  bool has_rumble_ = false;

  bool has_boot_ = false; /* true when boot rom is finished */

  std::string name;

  bool initialized = false;

};
