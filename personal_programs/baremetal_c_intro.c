// BASIC BARE-METAL C PROGRAM
// https://youtu.be/mshVdGlGwBs
// andr-be 2023

#define BCM2837_GPSET0      0x3F20001C
#define BCM2837_GPFSEL0     0x3F200000
#define BCM2837_GPFSEL1     0x3F200004
#define BCM2837_GPFSEL2     0x3F200008
#define BCM2837_GPCLR0      0x3F200028


typedef unsigned int uint;

void write32(void *dst, uint val)
{
    uint* dst_u = (uint*)dst;
    *dst_u = val;

    return;
}

uint read32(void *src)
{
    uint* src_u = (uint*)src;
    return *src_u;
}

void main(void){
    // read an integer from GPFSEL2 register
    uint gpfsel2 = read32(BCM2837_GPFSEL2);
    // bitshift that register
    gpfsel2 |= (1<<3);
    // turn pin 21 into an output
    write32(BCM2837_GPFSEL2, gpfsel2);

    int i = 0;
    while(1) {
        // turn on pin 21
        write32(BCM2837_GPSET0, 1<<21);
        
        // lazy delay
        i = 0;
        while (i < 0x800000) i++;

        // turn off pin 231
        write32(BCM2837_GPCLR0, 1<<21);

        // lazy delay
        i = 0;
        while (i < 0x800000) i++;
    }
}
