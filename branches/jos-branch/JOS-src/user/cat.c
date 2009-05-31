#include <inc/lib.h>

char buf[8192];

void
cat(int f, char *s)
{
	long n;
	int r;
        /* /\**\/ */
        /* struct Fd *fds; */
        /* fd_lookup(f, &fds); */
        /* cprintf("DEBUG cat Size: %d\n",fds->fd_file.file.f_size); */
        /* /\**\/ */
	while ((n = read(f, buf, (long)sizeof(buf))) > 0)
		if ((r = write(1, buf, n)) != n)
			panic("write error copying %s: %e", s, r);
	if (n < 0)
		panic("error reading %s: %e", s, n);
}

void
umain(int argc, char **argv)
{
	int f, i;

	argv0 = "cat";
	if (argc == 1)
		cat(0, "<stdin>");
	else
		for (i = 1; i < argc; i++) {
			f = open(argv[i], O_RDONLY);
			if (f < 0)
				cprintf("can't open %s: %e", argv[i], f);
			else {
				cat(f, argv[i]);
				close(f);
			}
		}
}
