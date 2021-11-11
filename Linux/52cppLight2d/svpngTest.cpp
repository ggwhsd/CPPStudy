#include "svpng.inc"
#include <iostream>
using namespace std;
void test_rgb(void)
{
	unsigned char rgb[256*256*3], *p = rgb;
	unsigned x,y;
	FILE *fp = fopen("rgb.png","wb");
    for(y=0;y<256;y++)
	{
		for(x=0;x<256;x++)
		{
			*p++ = (unsigned char )x;
			*p++ = (unsigned char )y;
			*p++ = 128;
		}
	}
	svpng(fp,256,256,rgb,0);
	fclose(fp);
}

int main(void)
{
	test_rgb();
	return 0;
}
