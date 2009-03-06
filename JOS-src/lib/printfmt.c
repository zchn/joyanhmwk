// Stripped-down primitive printf-style formatting routines,
// used in common by printf, sprintf, fprintf, etc.
// This code is also used by both the kernel and user programs.

#include <inc/types.h>
#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/stdarg.h>
#include <inc/error.h>

/*
 * Space or zero padding and a field width are supported for the numeric
 * formats only. 
 * 
 * The special format %e takes an integer error code
 * and prints a string describing the error.
 * The integer may be positive or negative,
 * so that -E_NO_MEM and E_NO_MEM are equivalent.
 */

#define ESC_COLOR_BLACK 0
#define ESC_COLOR_BLUE 1
#define ESC_COLOR_GREEN 2 
#define ESC_COLOR_CYAN 3
#define ESC_COLOR_RED 4
#define ESC_COLOR_PURPLE 5
#define ESC_COLOR_YELLOW 6
#define ESC_COLOR_WHITE 7

#define BACKG_SHIFT_CNT 12
#define FOREG_SHIFT_CNT 8          
          
          
static const char * const error_string[MAXERROR + 1] =
{
	NULL,
	"unspecified error",
	"bad environment",
	"invalid parameter",
	"out of memory",
	"out of environments",
	"segmentation fault",
};

/*
 * Print a number (base <= 16) in reverse order,
 * using specified putch function and associated pointer putdat.
 */
static void
printnum(void (*putch)(int, void*), void *putdat,
	 unsigned long long num, unsigned base, int width, int padc)
{
	// first recursively print all preceding (more significant) digits
	if (num >= base) {
		printnum(putch, putdat, num / base, base, width - 1, padc);
	} else {
		// print any needed pad characters before first digit
		while (--width > 0)
			putch(padc, putdat);
	}

	// then print this (the least significant) digit
	putch("0123456789abcdef"[num % base], putdat);
}

// Get an unsigned int of various possible sizes from a varargs list,
// depending on the lflag parameter.
static unsigned long long
getuint(va_list *ap, int lflag)
{
	if (lflag >= 2)
		return va_arg(*ap, unsigned long long);
	else if (lflag)
		return va_arg(*ap, unsigned long);
	else
		return va_arg(*ap, unsigned int);
}

// Same as getuint but signed - can't use getuint
// because of sign extension
static long long
getint(va_list *ap, int lflag)
{
	if (lflag >= 2)
		return va_arg(*ap, long long);
	else if (lflag)
		return va_arg(*ap, long);
	else
		return va_arg(*ap, int);
}


// Main function to format and print a string.
void printfmt(void (*putch)(int, void*), void *putdat, const char *fmt, ...);

void
vprintfmt(void (*putch)(int, void*), void *putdat, const char *fmt, va_list ap)
{
	register const char *p;
	register int ch, err;
	unsigned long long num;
	int base, lflag, width, precision, altflag;
        int color;
	char padc;

        color = 0;
        
	while (1) {
		while ((ch = *(unsigned char *) fmt++) != '%') {
			if (ch == '\0')
				return;
                        if (ch == 0x1b && (ch = *(unsigned char *) fmt++) == '[') {
                                color = 0;
                                while (ch != 'm') {
                                        ch = *(unsigned char *) fmt++;
                                        switch (ch) {
                                        case '3':
                                                ch = *(unsigned char *) fmt++;
                                                color &= 0xf << BACKG_SHIFT_CNT;
                                                switch (ch) {
                                                case '0':
                                                        color |= ESC_COLOR_BLACK << FOREG_SHIFT_CNT;
                                                        break;
                                                case '1':
                                                        color |= ESC_COLOR_RED << FOREG_SHIFT_CNT;
                                                        break;
                                                case '2':
                                                        color |= ESC_COLOR_GREEN << FOREG_SHIFT_CNT;
                                                        break;
                                                case '3':
                                                        color |= ESC_COLOR_YELLOW << FOREG_SHIFT_CNT;
                                                        break;
                                                case '4':
                                                        color |= ESC_COLOR_BLUE << FOREG_SHIFT_CNT;
                                                        break;
                                                case '5':
                                                        color |= ESC_COLOR_PURPLE << FOREG_SHIFT_CNT;
                                                        break;
                                                case '6':
                                                        color |= ESC_COLOR_CYAN << FOREG_SHIFT_CNT;
                                                        break;
                                                case '7':
                                                        color |= ESC_COLOR_WHITE << FOREG_SHIFT_CNT;
                                                        break;
                                                default:
                                                        color |= ESC_COLOR_WHITE << FOREG_SHIFT_CNT;
                                                }
                                                break;                                        
                                        case '4':
                                                ch = *(unsigned char *) fmt++;
                                                color &= 0xf << FOREG_SHIFT_CNT;
                                                switch (ch) {
                                                case '0':
                                                        color |= ESC_COLOR_BLACK << BACKG_SHIFT_CNT;
                                                        break;
                                                case '1':
                                                        color |= ESC_COLOR_RED << BACKG_SHIFT_CNT;
                                                        break;
                                                case '2':
                                                        color |= ESC_COLOR_GREEN << BACKG_SHIFT_CNT;
                                                        break;
                                                case '3':
                                                        color |= ESC_COLOR_YELLOW << BACKG_SHIFT_CNT;
                                                        break;
                                                case '4':
                                                        color |= ESC_COLOR_BLUE << BACKG_SHIFT_CNT;
                                                        break;
                                                case '5':
                                                        color |= ESC_COLOR_PURPLE << BACKG_SHIFT_CNT;
                                                        break;
                                                case '6':
                                                        color |= ESC_COLOR_CYAN << BACKG_SHIFT_CNT;
                                                        break;
                                                case '7':
                                                        color |= ESC_COLOR_WHITE << BACKG_SHIFT_CNT;
                                                        break;
                                                default:
                                                        color |= ESC_COLOR_BLACK << BACKG_SHIFT_CNT;
                                                }
                                                break;
                                        default:
                                                putch(ch|color,putdat);
                                                break;
                                        }
                                        ch = *(unsigned char *) fmt++;// ';'
                                }
                        }else{
                                putch(ch|color, putdat);
                        }
		}

		// Process a %-escape sequence
		padc = ' ';
		width = -1;
		precision = -1;
		lflag = 0;
		altflag = 0;
	reswitch:
		switch (ch = *(unsigned char *) fmt++) {

		// flag to pad on the right
		case '-':
			padc = '-';
			goto reswitch;
			
		// flag to pad with 0's instead of spaces
		case '0':
			padc = '0';
			goto reswitch;

		// width field
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			for (precision = 0; ; ++fmt) {
				precision = precision * 10 + ch - '0';
				ch = *fmt;
				if (ch < '0' || ch > '9')
					break;
			}
			goto process_precision;

		case '*':
			precision = va_arg(ap, int);
			goto process_precision;

		case '.':
			if (width < 0)
				width = 0;
			goto reswitch;

		case '#':
			altflag = 1;
			goto reswitch;

		process_precision:
			if (width < 0)
				width = precision, precision = -1;
			goto reswitch;

		// long flag (doubled for long long)
		case 'l':
			lflag++;
			goto reswitch;

		// character
		case 'c':
			putch(va_arg(ap, int)|color, putdat);
			break;

		// error message
		case 'e':
			err = va_arg(ap, int);
			if (err < 0)
				err = -err;
			if (err > MAXERROR || (p = error_string[err]) == NULL)
				printfmt(putch, putdat, "error %d", err);
			else
				printfmt(putch, putdat, "%s", p);
			break;

		// string
		case 's':
			if ((p = va_arg(ap, char *)) == NULL)
				p = "(null)";
			if (width > 0 && padc != '-')
				for (width -= strnlen(p, precision); width > 0; width--)
					putch(padc|color, putdat);
			for (; (ch = *p++) != '\0' && (precision < 0 || --precision >= 0); width--)
				if (altflag && (ch < ' ' || ch > '~'))
					putch('?'|color, putdat);
				else
					putch(ch|color, putdat);
			for (; width > 0; width--)
				putch(' '|color, putdat);
			break;

		// (signed) decimal
		case 'd':
			num = getint(&ap, lflag);
			if ((long long) num < 0) {
				putch('-'|color, putdat);
				num = -(long long) num;
			}
			base = 10;
			goto number;

		// unsigned decimal
		case 'u':
			num = getuint(&ap, lflag);
			base = 10;
			goto number;

		// (unsigned) octal
		case 'o':
			// Replace this with your code.
			num = getuint(&ap, lflag);
			base = 8;
                        goto number;
//			break;

		// pointer
		case 'p':
			putch('0', putdat);
			putch('x'|color, putdat);
			num = (unsigned long long)
				(uintptr_t) va_arg(ap, void *);
			base = 16;
			goto number;

		// (unsigned) hexadecimal
		case 'x':
			num = getuint(&ap, lflag);
			base = 16;
		number:
			printnum(putch, putdat, num, base, width, padc);
			break;

		// escaped '%' character
		case '%':
			putch(ch, putdat);
			break;
			
		// unrecognized escape sequence - just print it literally
		default:
			putch('%'|color, putdat);
			for (fmt--; fmt[-1] != '%'; fmt--)
				/* do nothing */;
			break;
		}
	}
}

void
printfmt(void (*putch)(int, void*), void *putdat, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprintfmt(putch, putdat, fmt, ap);
	va_end(ap);
}

struct sprintbuf {
	char *buf;
	char *ebuf;
	int cnt;
};

static void
sprintputch(int ch, struct sprintbuf *b)
{
	b->cnt++;
	if (b->buf < b->ebuf)
		*b->buf++ = ch;
}

int
vsnprintf(char *buf, int n, const char *fmt, va_list ap)
{
	struct sprintbuf b = {buf, buf+n-1, 0};

	if (buf == NULL || n < 1)
		return -E_INVAL;

	// print the string to the buffer
	vprintfmt((void*)sprintputch, &b, fmt, ap);

	// null terminate the buffer
	*b.buf = '\0';

	return b.cnt;
}

int
snprintf(char *buf, int n, const char *fmt, ...)
{
	va_list ap;
	int rc;

	va_start(ap, fmt);
	rc = vsnprintf(buf, n, fmt, ap);
	va_end(ap);

	return rc;
}


