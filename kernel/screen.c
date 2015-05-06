#include <screen.h>
#include <io.h>

void move_cursor(void)
{
    uint16_t temp;

    temp = cy * WIDTH + cx;
    
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void clears()
{
  int i;
	uint16_t buf = 0;
	
	buf = 0x20 | (attribut << 8); 
	
	for(i=0;i<HEIGHT;i++) {
		memset16(videoptr + i * WIDTH, buf, WIDTH);
	}
	
	cx = cy = 0;
	move_cursor();
}

void init_video()
{
    videoptr = (uint16_t*) 0xB8000;
	attribut = 0xF1;
	clears();
}

static void itoa (char *buf, int base, int d)
{
	char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;
     
    /* If %d is specified and D is minus, put `-' in the head. */
    if (base == 'd' && d < 0)
    {
    	*p++ = '-';
         buf++;
         ud = -d;
    }
    else if (base == 'x')
    	divisor = 16;
     
    /* Divide UD by DIVISOR until UD == 0. */
    do
    {
    	int remainder = ud % divisor;
     
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
    while (ud /= divisor);
     
    /* Terminate BUF. */
    *p = 0;
     
    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2)
    {
    	char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

static void putchar (int c)
{
    if (c == '\n' )
    {
        newline:
        cx = 0;
        cy++;
        if (cy >= HEIGHT) {
            cy = 0;
            clears();
        }
        move_cursor();
        return;
    }
    if(c == '\r') {
        cx --;
        if(cx < 0) {
            cx = WIDTH-1;
            cy--;
            if(cy < 0) cy = 0;
        }
        move_cursor();
        videoptr[cx + cy*WIDTH] = (' ' & 0xFF) | (attribut << 8);  
        return;
    }
     
    videoptr[cx + cy*WIDTH] = (c & 0xFF) | (attribut << 8);  
         
    cx++;
    if (cx >= WIDTH)
        goto newline;
         
        move_cursor();
}

void printk (const char *format, ...)
{
    char **arg = (char **) &format;
   	int c;
    char buf[20];
     
    arg++;
     
    while ((c = *format++) != 0)
    {
    	if (c != '%')
             putchar (c);
        else
        {
            char *p;
     
            c = *format++;
            switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
                itoa (buf, c, *((int *) arg++));
                p = buf;
                goto string;
                break;
            case 'p':
                itoa(buf, 'x', *((int *) arg++));
                p = buf;
                putchar('0');
                putchar('x');
                goto string;
                break;
     
            case 's':
                p = *arg++;
                if (! p)
                    p = "(null)";
     
                string:
                while (*p)
                putchar (*p++);
                break;
     
            default:
                putchar (*((int *) arg++));
                break;
            }
        }
    }
}

void __pok()
{
    attribut = 0xF2;
    printk("ok.\n");
    attribut = 0xF1;
}
