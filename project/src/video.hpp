#pragma once

#include <processor.hpp>
#include <sprite.hpp>
#include "array.hpp"

class Video {

public :

 	Video(Processor& proc);

	bool in_range(uint16_t address);

	uint8_t read(uint16_t address);
	void write(uint8_t byte, uint16_t address);

	uint8_t simple_read(uint16_t address);
	void simple_write(uint8_t byte, uint16_t address);

	void dma_transfer(uint16_t beg_src, uint16_t end_src);

	// NOTE: There is no difference between read/write for perms
	// If we try to read/write potentially protected memory,
	// we return _accessible otherwise we return true.
	bool is_accessible(uint16_t address);

	bool can_read(uint16_t address);
	bool can_write(uint16_t address);

	// Change permission on protected memory:
 	// VRAM (0x8000-0x9FFF) and OAM (0xFE00-0xFE9F)
	void set_VRAM_accessible(bool accessible);
	void set_OAM_accessible(bool accessible);

	size_t get_sprites(std::array<Sprite, 40>& sprites);

	uint8_t get_lcd_control();
	uint8_t get_lcd_status();
	uint8_t get_scrolly();
	uint8_t get_scrollx();
	uint8_t get_ly();
	uint8_t get_lyc();
	uint8_t get_wy();
	uint8_t get_wx(); /* actually wx - 7 */
	uint8_t get_bgp();
	uint8_t get_obp0();
	uint8_t get_obp1();

	void set_lcd_status(uint8_t status);
	void set_lcd_status_mode(uint8_t mode);
	void set_ly(uint8_t ly);

private:
	bool is_OAM(uint16_t address);
	bool is_VRAM(uint16_t address);
private :

	Processor &_proc;
	uint8_t video_memory[0x10000];
	bool _OAM_accessible = false;
	bool _VRAM_accessible = true;
};
