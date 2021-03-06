/*
 * File : lcd.cpp
 *
 * File created by : Corentin Gay
 * File was created at : 01/12/2017
 */

#include <lcd.hpp>

LCD::LCD(Memory &mem) :
	_mem(mem),
	video(mem.get_video())
{
}


void LCD::step(int elapsed_time, unsigned char * s)
{
	update_variables(elapsed_time);

	if (clock >= current_mode.duration)
	{
		clock -= current_mode.duration;
		switch (current_mode.state)
		{
		case LCDState::Mode0 : //HBLANK
			video.set_ly(video.get_ly()+1);
			check_lyc();

			if (video.get_ly() >= 144) {
				current_mode = states[1]; //VBLANK
				_mem.set_interrupt_flag(Memory::Interrupt::VBLANK);
				check_interrupt_stat(4);
				draw(s);
			}
			else {
				current_mode = states[2]; //OAM
				check_interrupt_stat(5);
			}
			break;
		case LCDState::Mode1 : //VBLANK
			video.set_ly(video.get_ly()+1);
			check_lyc();

			if (video.get_ly() > 153) {
				video.set_ly(0);
				current_mode = states[2]; //OAM
				check_interrupt_stat(5);
			}
			break;
		case LCDState::Mode2 : //OAM
			current_mode = states[3]; //VRAM
			break;
		case LCDState::Mode3 : //VRAM
			current_mode = states[0]; //HBLANK
			check_interrupt_stat(3);
			draw_scanline();
			break;

		default :
			break;
		}

		//FIXME Permission bug
		video.set_OAM_accessible(/*current_mode.can_access_OAM()*/true);
		video.set_VRAM_accessible(/*current_mode.can_access_VRAM()*/true);
		video.set_lcd_status_mode((uint8_t)current_mode.state);
	}
}

void LCD::draw(unsigned char * s)
{
	// Each pixel is an unsigned char:
	// 0 -> white
	// 1 -> light gray
	// 2 -> dark gray
	// 3 -> black

	for (unsigned int i = 0; i < 160; i++)
	{
		for (unsigned int j = 0; j < 144; j++)
		{
			//Conversion to RGB format is done in the ADA world
			s[i+144*j] = pixels[i][j];

		/* We do it in a nicer way
			if (pixels[i][j] == 1) {
				p[0] = 150; p[1] = 150; p[2] = 150;
			}
			else if (pixels[i][j] == 2) {
				p[0] = 80; p[1] = 80; p[2] = 80;
			}
			else if (pixels[i][j] == 3) {
				p[0] = 0; p[1] = 0; p[2] = 0;
			}
			else {
				p[0] = 255; p[1] = 255; p[2] = 255;
			}
		*/
		}
	}
}

void LCD::draw_scanline()
{
	line = video.get_ly();
	//std::cout << "lcdc : " << CONTROL << std::endl;
	if (CONTROL[7] && CONTROL[0])
		render_tiles(line);
	if (CONTROL[7] && CONTROL[1])
		render_sprites(line);
}

void LCD::check_interrupt_stat(int num_bit)
{
	if (STATUS[num_bit])
		_mem.set_interrupt_flag(Memory::Interrupt::STAT);
}

void LCD::check_lyc()
{
	STATUS[2] = (video.get_ly() == video.get_lyc());
	video.set_lcd_status((uint8_t)STATUS.to_ulong());
	check_interrupt_stat(6);
}

bool State::can_access_VRAM() const
{
	return state != LCDState::Mode3;
}

bool State::can_access_OAM() const
{
	return (state != LCDState::Mode2 && state != LCDState::Mode3);
}


void LCD::update_variables(int elapsed_time)
{
	CONTROL = video.get_lcd_control();
	STATUS = video.get_lcd_status();

	current_mode = states[((uint8_t)(STATUS.to_ulong()) & 0x03)];

	clock += elapsed_time;
}

void LCD::render_tiles(int current_line)
{
	uint16_t tiles_address = 0;
	uint16_t tile_map_address = 0;
	bool is_signed = false;
	bool window_display = false;
	uint8_t scrollx = video.get_scrollx();
	uint8_t scrolly = video.get_scrolly();
	uint8_t wx = video.get_wx() - 7;
	uint8_t wy = video.get_wy();

	uint8_t lcd_control = video.get_lcd_control();

	if ((lcd_control >> 5) & 1)
		window_display = (current_line >= wy);
	if ((lcd_control >> 4) & 1) {
		tiles_address = 0x8000;
		is_signed = false;
	}
	else {
		tiles_address = 0x8800;
		is_signed = true;
	}

	if (!window_display) {
		if ((lcd_control >> 3) & 1)
			tile_map_address = 0x9c00;
		else
			tile_map_address = 0x9800;
	}
	else {
		if ((lcd_control >> 6) & 1)
			tile_map_address = 0x9c00;
		else
			tile_map_address = 0x9800;
	}


	uint8_t y = scrolly + current_line;
	if (window_display)
		y = current_line - wy;

	for (int i = 0; i < 160; i++) {
		uint8_t x = i + scrollx;
		if (window_display)
			x = i - wx;

		int16_t tile_num = get_tile_num(tile_map_address, x, y,
						is_signed);
		uint16_t tile_address = get_tile_address(tiles_address,
							 tile_num,
							 is_signed);

		uint8_t color_id = get_color_id(tile_address, 7-(x%8), y%8);

		pixels[i][current_line] = get_color(color_id, video.get_bgp());
	}

}

void LCD::render_sprites(int current_line)
{
	bool is_double = CONTROL[2];

	uint8_t height = (is_double) ? 16 : 8;

	// We fill sprites with the sprites to display
	size_t size = video.get_sprites(sprites);

	int index = 0;
	for (size_t i = 0; i < size; ++i) {
		if (sprites[i].get_x() == 0
		    || sprites[i].get_x() >= 168
		    || sprites[i].get_y() == 0
		    || sprites[i].get_y() >= 160
		    || sprites[i].get_y_pos() > current_line
		    || sprites[i].get_y_pos() + height <= current_line)
			continue;

		on_line[index] = (sprites[i]);
		++index;
	}

	int count = 0;

	// We iterate over each sprite that is on the current scan_line
	// TODO: actually implement iterators on our arrays
	for (unsigned int i = 0; i < index; ++i) {
		auto& it = on_line[i];
		if (count >= 10)
			break;
		uint16_t tile_num = it.get_tile();
		if (is_double)
			tile_num &= 0xfe;
		uint16_t tile_addr = get_tile_address(0x8000, tile_num, false);
		uint16_t y = current_line - it.get_y_pos();
		if (it.is_y_flipped())
			y = height - y - 1;

		uint8_t palette = video.get_obp0();
		if (it.is_obp1())
			palette = video.get_obp1();

		for (int i = 0; i < 8; ++i) {
			if (it.get_x_pos() + i < 0 || it.get_x_pos()+i >= 160)
				continue;

			uint8_t x = 7 - i;
			if (it.is_x_flipped())
				x = i;

			uint8_t color_id = get_color_id(tile_addr, x, y);
			uint8_t color = get_color(color_id, palette);
			if (it.is_above_bg() || color)
				pixels[it.get_x_pos()+i][current_line]=color;
		}
		count++;
	}
}

int16_t LCD::get_tile_num(uint16_t tilemap_addr, uint8_t x,
				  uint8_t y, bool is_signed)
{
	uint16_t addr = tilemap_addr + (y / 8) * 32 + (x / 8);
	if (is_signed)
		return (int8_t) video.simple_read(addr);
	else
		return video.simple_read(addr);
}

uint16_t LCD::get_tile_address(uint16_t tile_addr, int16_t tilenum,
				       bool is_signed)
{
	if (!is_signed)
		return tile_addr + (tilenum * 16);
	else
		return tile_addr + ((tilenum + 128) * 16);
}

uint8_t LCD::get_color_id(uint16_t tile_addr, uint8_t x, uint8_t y)
{
	uint8_t byte1 = video.simple_read(tile_addr + y * 2);
	uint8_t byte2 = video.simple_read(tile_addr + y * 2 + 1);

	uint8_t result = 0;

	uint8_t bit1 = (byte1 >> x) & 1;
	result+= (bit1) ? 2 : 0;
	uint8_t bit2 = (byte2 >> x) & 1;
	result+= (bit2) ? 1 : 0;

	return result;
}

int LCD::get_color(uint8_t id, uint8_t palette)
{
	return ((palette >> (id*2)) & 0x03);
}
