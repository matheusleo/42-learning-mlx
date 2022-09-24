#include <stdio.h>

/*
	int = 4bytes = 4 * (8 bits)
	1bit = 0 <= x <= 255
	TRGB
	{
		T = 0 <= t <= 255
		R = 0 <= r <= 255
		G = 0 <= g <= 255
		B = 0 <= b <= 255
	}
	therefore, one int which is 4 bytes
	can store the four values related to the
	TRGB colors since each one of them has a range
	between 0 and 255
	int
	{
		00000000 - T
		00000000 - R
		00000000 - G
		00000000 - B
	}
*/

unsigned int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


unsigned int get_t(unsigned int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

unsigned int get_r(unsigned int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

unsigned int get_g(unsigned int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

unsigned int get_b(unsigned int trgb)
{
	return (trgb & 0xFF);
}

unsigned int get_complementary(unsigned int trgb)
{
	unsigned int comp_r;
	unsigned int comp_g;
	unsigned int comp_b;

	comp_r = ~get_r(trgb) & 0xFF;
	comp_g = ~get_g(trgb) & 0xFF;
	comp_b = ~get_b(trgb) & 0xFF;
	return (create_trgb(get_t(trgb), comp_r, comp_g, comp_b));
}
