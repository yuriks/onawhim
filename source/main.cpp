#include <nds.h>
#include <algorithm>

#include "logo_tiles.h"

extern const u16 logo_map_bin_end[];
extern const u16 logo_map_bin[];
extern const u32 logo_map_bin_size;

static const int SPRITE_DMA_CHANNEL = 1;
static const int DATA_DMA_CHANNEL = 3;

const u16 logo_pal1[16] = {
	RGB15(9, 0, 0),    // 0
	RGB15(0, 21, 31),  // 1
	RGB15(0, 17, 31),  // 2
	RGB15(0, 13, 31),  // 3
	RGB15(2, 7, 29),   // 4
	RGB15(0, 3, 29),   // 5
	RGB15(8, 4, 21),   // 6
	RGB15(11, 6, 17),  // 7
	RGB15(14, 7, 13),  // 8
	RGB15(16, 8, 10),  // 9
	RGB15(19, 9, 6),   // 10
	RGB15(25, 15, 0),  // 11
	RGB15(29, 26, 0),  // 12
	RGB15(31, 31, 15), // 13
	RGB15(31, 31, 23), // 14
	RGB15(31, 31, 29)  // 15
};

const u16 logo_pal2[16] = {
	RGB15(9, 0, 0),    // 0
	RGB15(26, 26, 26), // 1
	RGB15(23, 23, 23), // 2
	RGB15(20, 20, 20), // 3
	RGB15(17, 17, 17), // 4
	RGB15(15, 15, 15), // 5
	RGB15(12, 12, 12), // 6
	RGB15(9, 9, 9),    // 7
	RGB15(6, 6, 6),    // 8
	RGB15(0, 0, 0),    // 9
	RGB15(0, 0, 0),    // 10
	RGB15(0, 0, 0),    // 11
	RGB15(0, 0, 0),    // 12
	RGB15(0, 0, 0),    // 13
	RGB15(0, 0, 0),    // 14
	RGB15(0, 0, 0),    // 15
};

const u16 fire_pal[16] = {
	RGB8(  0,   0,   0),
	RGB8( 14,   0,   0),
	RGB8( 27,   0,   0),
	RGB8( 41,   0,   0),
	RGB8( 54,   0,   0),
	RGB8( 68,   0,   0),
	RGB8( 81,   0,   0),
	RGB8( 98,   0,   0),
	RGB8(144,   0,   0),
	RGB8(188,   5,   2),
	RGB8(216,  60,  22),
	RGB8(235,  99,  36),
	RGB8(252, 134,  48),
	RGB8(250, 204,  30),
	RGB8(248, 242,  86),
	RGB8(249, 247, 212)
};

const u16 rainbow[128] = {
	RGB8(255,   0,   0),
	RGB8(255,  12,   0),
	RGB8(255,  24,   0),
	RGB8(255,  36,   0),
	RGB8(255,  48,   0),
	RGB8(255,  60,   0),
	RGB8(255,  72,   0),
	RGB8(255,  84,   0),
	RGB8(255,  96,   0),
	RGB8(255, 108,   0),
	RGB8(255, 120,   0),
	RGB8(255, 133,   0),
	RGB8(255, 145,   0),
	RGB8(255, 157,   0),
	RGB8(255, 169,   0),
	RGB8(255, 181,   0),
	RGB8(255, 193,   0),
	RGB8(255, 205,   0),
	RGB8(255, 217,   0),
	RGB8(255, 229,   0),
	RGB8(255, 241,   0),
	RGB8(255, 253,   0),
	RGB8(245, 255,   0),
	RGB8(233, 255,   0),
	RGB8(221, 255,   0),
	RGB8(209, 255,   0),
	RGB8(197, 255,   0),
	RGB8(185, 255,   0),
	RGB8(173, 255,   0),
	RGB8(161, 255,   0),
	RGB8(149, 255,   0),
	RGB8(137, 255,   0),
	RGB8(124, 255,   0),
	RGB8(112, 255,   0),
	RGB8(100, 255,   0),
	RGB8( 88, 255,   0),
	RGB8( 76, 255,   0),
	RGB8( 64, 255,   0),
	RGB8( 52, 255,   0),
	RGB8( 40, 255,   0),
	RGB8( 28, 255,   0),
	RGB8( 16, 255,   0),
	RGB8(  4, 255,   0),
	RGB8(  0, 255,   8),
	RGB8(  0, 255,  20),
	RGB8(  0, 255,  32),
	RGB8(  0, 255,  44),
	RGB8(  0, 255,  56),
	RGB8(  0, 255,  68),
	RGB8(  0, 255,  80),
	RGB8(  0, 255,  92),
	RGB8(  0, 255, 104),
	RGB8(  0, 255, 116),
	RGB8(  0, 255, 129),
	RGB8(  0, 255, 141),
	RGB8(  0, 255, 153),
	RGB8(  0, 255, 165),
	RGB8(  0, 255, 177),
	RGB8(  0, 255, 189),
	RGB8(  0, 255, 201),
	RGB8(  0, 255, 213),
	RGB8(  0, 255, 225),
	RGB8(  0, 255, 237),
	RGB8(  0, 255, 249),
	RGB8(  0, 249, 255),
	RGB8(  0, 237, 255),
	RGB8(  0, 225, 255),
	RGB8(  0, 213, 255),
	RGB8(  0, 201, 255),
	RGB8(  0, 189, 255),
	RGB8(  0, 177, 255),
	RGB8(  0, 165, 255),
	RGB8(  0, 153, 255),
	RGB8(  0, 141, 255),
	RGB8(  0, 129, 255),
	RGB8(  0, 116, 255),
	RGB8(  0, 104, 255),
	RGB8(  0,  92, 255),
	RGB8(  0,  80, 255),
	RGB8(  0,  68, 255),
	RGB8(  0,  56, 255),
	RGB8(  0,  44, 255),
	RGB8(  0,  32, 255),
	RGB8(  0,  20, 255),
	RGB8(  0,   8, 255),
	RGB8(  4,   0, 255),
	RGB8( 16,   0, 255),
	RGB8( 28,   0, 255),
	RGB8( 40,   0, 255),
	RGB8( 52,   0, 255),
	RGB8( 64,   0, 255),
	RGB8( 76,   0, 255),
	RGB8( 88,   0, 255),
	RGB8(100,   0, 255),
	RGB8(112,   0, 255),
	RGB8(124,   0, 255),
	RGB8(137,   0, 255),
	RGB8(149,   0, 255),
	RGB8(161,   0, 255),
	RGB8(173,   0, 255),
	RGB8(185,   0, 255),
	RGB8(197,   0, 255),
	RGB8(209,   0, 255),
	RGB8(221,   0, 255),
	RGB8(233,   0, 255),
	RGB8(245,   0, 255),
	RGB8(255,   0, 253),
	RGB8(255,   0, 241),
	RGB8(255,   0, 229),
	RGB8(255,   0, 217),
	RGB8(255,   0, 205),
	RGB8(255,   0, 193),
	RGB8(255,   0, 181),
	RGB8(255,   0, 169),
	RGB8(255,   0, 157),
	RGB8(255,   0, 145),
	RGB8(255,   0, 133),
	RGB8(255,   0, 120),
	RGB8(255,   0, 108),
	RGB8(255,   0,  96),
	RGB8(255,   0,  84),
	RGB8(255,   0,  72),
	RGB8(255,   0,  60),
	RGB8(255,   0,  48),
	RGB8(255,   0,  36),
	RGB8(255,   0,  24),
	RGB8(255,   0,  12),
	RGB8(255,   0,   0)
};

struct LogoSprite
{
	u16 x:8;
	u16 y:8;
	ObjShape shape:2;
	ObjSize size:2;
	u16 gfxIndex:10;
};

static const int NUM_LOGO_SPRITES = 9;
const LogoSprite logo_sprites[NUM_LOGO_SPRITES] = {
	{80, 32, OBJSHAPE_SQUARE, OBJSIZE_64, 0}, // 0
	{16, 32, OBJSHAPE_TALL, OBJSIZE_64, 64}, // 1
	{16, 96, OBJSHAPE_TALL, OBJSIZE_64, 96}, // 2
	{48, 64, OBJSHAPE_TALL, OBJSIZE_64, 128}, // 3
	{144, 56, OBJSHAPE_WIDE, OBJSIZE_64, 160}, // 4
	{208, 56, OBJSHAPE_SQUARE, OBJSIZE_32, 192}, // 5
	{88, 96, OBJSHAPE_WIDE, OBJSIZE_64, 208},
	{152, 96, OBJSHAPE_WIDE, OBJSIZE_64, 240},
	{216, 96, OBJSHAPE_SQUARE, OBJSIZE_32, 272}
};

void init_video()
{
	lcdMainOnBottom();
	vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);
	videoSetMode(MODE_3_2D | DISPLAY_SPR_1D | DISPLAY_SPR_ACTIVE |
	             DISPLAY_BG3_ACTIVE | DISPLAY_BG1_ACTIVE |
	             DISPLAY_WIN0_ON | DISPLAY_SPR_WIN_ON);
	videoSetModeSub(MODE_0_2D | DISPLAY_SPR_1D | DISPLAY_BG0_ACTIVE);
}

OAMTable oam;
int sin_offset;
int cur_rainbow;
int screen_fade_black = 0;
// 22.10
int fade = 0;

u16 mix_colors(u16 x, u16 y, u16 mix /* 1.12 */)
{
	u32 mix32 = mix;
	u32 rmix = ((1<<12) - mix);

	u16 r = (((x>> 0) & 0x1F)*rmix + ((y>> 0) & 0x1F)*mix32) >> 12;
	u16 g = (((x>> 5) & 0x1F)*rmix + ((y>> 5) & 0x1F)*mix32) >> 12;
	u16 b = (((x>>10) & 0x1F)*rmix + ((y>>10) & 0x1F)*mix32) >> 12;

	return r | g << 5 | b << 10;
}

u16 get_rainbow_color(int vcount)
{
	int scroll = ((s32)cosLerp(sin_offset + (vcount << 6)) + (1 << 12)) / 148;
	int i = (vcount + cur_rainbow + scroll) % 128;
	return mix_colors(0, rainbow[i], screen_fade_black);
}


void on_hblank_irq()
{
	int vcount = REG_VCOUNT;

	if (vcount >= 192)
		return;

	BG_PALETTE[0] = get_rainbow_color(vcount);

	const int x0 = 32;
	const int x1 = 160;
	const int y0 = -4 << 10;
	const int y1 =  0 << 10;

	int alpha = y0 + ((int)vcount - x0)*((y1-y0)/(x1-x0));
	alpha = std::max(0, std::min(1 << 10, alpha+(fade*4)));

	// 1.4
	REG_BLDALPHA = (alpha >> 6) | (((1 << 10) - alpha) >> 6 << 8);
}

void cycle_palette(u16* pal, int first_index, int last_index)
{
	u16 tmp = BG_PALETTE[first_index];
	for (int i = first_index; i < last_index; ++i)
		BG_PALETTE[i] = BG_PALETTE[i+1];
	BG_PALETTE[last_index] = tmp;
}

int main()
{
	powerOn(POWER_ALL_2D);
	init_video();

	dmaCopyHalfWords(DATA_DMA_CHANNEL, logo_tilesTiles, BG_TILE_RAM(0), logo_tilesTilesLen);
	dmaCopyHalfWords(DATA_DMA_CHANNEL, logo_tilesTiles, SPRITE_GFX,     logo_tilesTilesLen);
	dmaCopyHalfWords(DATA_DMA_CHANNEL, logo_map_bin, BG_MAP_RAM(8), logo_map_bin_size);
	dmaCopyHalfWords(DATA_DMA_CHANNEL, logo_pal1, &BG_PALETTE[16*0], 16*sizeof(u16));
	dmaCopyHalfWords(DATA_DMA_CHANNEL, logo_pal2, &BG_PALETTE[16*1], 16*sizeof(u16));
	dmaCopyHalfWords(DATA_DMA_CHANNEL, fire_pal,  &BG_PALETTE[16*2], 16*sizeof(u16));

	for (int i = 0; i < 48*1024/2; ++i)
	{
		u8 col = i % 16 + 16*2;
		BG_BMP_RAM(2)[i] = (col << 8) | col;
	}

	for (int i = 0; i < SPRITE_COUNT; ++i)
	{
		oam.oamBuffer[i].attribute[0] = ATTR0_DISABLED;
		oam.oamBuffer[i].attribute[1] = 0;
		oam.oamBuffer[i].attribute[2] = 0;
	}
	for (int i = 0; i < MATRIX_COUNT; ++i)
	{
		oam.matrixBuffer[i].hdx = 1 << 8;
		oam.matrixBuffer[i].hdy = 0;
		oam.matrixBuffer[i].vdx = 0;
		oam.matrixBuffer[i].vdy = 1 << 8;
	}

	BACKGROUND.control[3] = BG_BMP8_256x256 | BG_BMP_BASE(2) | BG_PRIORITY(3);
	BACKGROUND.control[1] = BG_32x32 | BG_COLOR_16 | BG_TILE_BASE(0) | BG_MAP_BASE(8) | BG_PRIORITY(1);
	BACKGROUND.scroll[1].x = 0;
	BACKGROUND.scroll[1].y = 0;
	
	REG_BG3PA = 1 << 8;
	REG_BG3PB = 0;
	REG_BG3PC = 0;
	REG_BG3PD = 1 << 8;

	WIN_IN = 0;
	WIN_OUT = (0 << 3) | (1 << 1) | (1 << 4) | (1 << 5) | (1 << 11) | (0 << 9) | (1 << 13);

	BG_PALETTE[0] = get_rainbow_color(0);

	int frame_counter = 0;

	bool do_screen_fadein = true;
	bool do_logo_alpha_fade = false;
	bool do_logo_fade_black = false;
	bool do_logo_fade_fire = false;

	sin_offset = 0;
	cur_rainbow = 0;
	int pal_delay = 0;

	irqSet(IRQ_HBLANK, on_hblank_irq);
	irqEnable(IRQ_HBLANK);

	REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG1 | BLEND_DST_BACKDROP;
	REG_BLDALPHA = 0 | (16 << 8);

	for (;;)
	{
		switch (frame_counter)
		{
			case 440:
				do_logo_alpha_fade = true; break;
			case 800:
				do_logo_fade_black = true;
				REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG1 | BLEND_SRC_BG3;
				fade = 0;
				break;
			case 1000:
				do_logo_fade_fire = true;
				for (int i = 0; i < NUM_LOGO_SPRITES; ++i)
				{
					SpriteEntry& spr = oam.oamBuffer[i];
					const LogoSprite& l = logo_sprites[i];

					spr.x = l.x;
					spr.y = l.y;
					spr.isHidden = false;
					spr.blendMode = OBJMODE_WINDOWED;
					spr.shape = l.shape;
					spr.size = l.size;
					spr.gfxIndex = l.gfxIndex;
				}
				break;
			default:
				break;
		}

		/*
		scanKeys();
		if (keysHeld() & KEY_LEFT)
			oam.oamBuffer[1].x -= 1;
		if (keysHeld() & KEY_RIGHT)
			oam.oamBuffer[1].x += 1;
		if (keysHeld() & KEY_UP)
			oam.oamBuffer[1].y -= 1;
		if (keysHeld() & KEY_DOWN)
			oam.oamBuffer[1].y += 1;
		*/


		swiWaitForVBlank();
		dmaCopyHalfWords(SPRITE_DMA_CHANNEL, &oam, OAM, sizeof(oam));

		if (do_screen_fadein)
		{
			screen_fade_black += 16;
			if (screen_fade_black == 1 << 12)
				do_screen_fadein = false;
		}

		if (do_logo_alpha_fade)
		{
			fade += 8;
			if (fade == 2 << 10)
				do_logo_alpha_fade = false;
		}

		if (do_logo_fade_black)
		{
			fade += 12;
			REG_BLDY = fade >> (10-4);
			if (fade >= 1 << 10)
				do_logo_fade_black = false;
		}

		if (do_logo_fade_fire)
		{
			fade -= 4;
			REG_BLDY = fade >> (10-4);
			if (fade <= 0)
				do_logo_fade_fire = false;
		}


		sin_offset += 192;
		cur_rainbow += 1;

		BG_PALETTE[0] = get_rainbow_color(0);

		if (pal_delay == 4)
		{
			pal_delay = 0;
			cycle_palette(&BG_PALETTE[0], 2, 14);
		}
		pal_delay += 1;


		frame_counter += 1;
	}

	return 0;
}
