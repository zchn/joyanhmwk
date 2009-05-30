#include <inc/lib.h>

#define debug 0

static int pipeclose(struct Fd *fd);
static ssize_t piperead(struct Fd *fd, void *buf, size_t n, off_t offset);
static int pipestat(struct Fd *fd, struct Stat *stat);
static ssize_t pipewrite(struct Fd *fd, const void *buf, size_t n, off_t offset);

struct Dev devpipe =
{
	.dev_id=	'p',
	.dev_name=	"pipe",
	.dev_read=	piperead,
	.dev_write=	pipewrite,
	.dev_close=	pipeclose,
	.dev_stat=	pipestat,
};

#define PIPEBUFSIZ 32		// small to provoke races

struct Pipe {
	off_t p_rpos;		// read position
	off_t p_wpos;		// write position
	uint8_t p_buf[PIPEBUFSIZ];	// data buffer
};

int
pipe(int pfd[2])
{
	int r;
	struct Fd *fd0, *fd1;
	void *va;

	// allocate the file descriptor table entries
	if ((r = fd_alloc(&fd0)) < 0
	    || (r = sys_page_alloc(0, fd0, PTE_P|PTE_W|PTE_U|PTE_SHARE)) < 0)
		goto err;

	if ((r = fd_alloc(&fd1)) < 0
	    || (r = sys_page_alloc(0, fd1, PTE_P|PTE_W|PTE_U|PTE_SHARE)) < 0)
		goto err1;

	// allocate the pipe structure as first data page in both
	va = fd2data(fd0);
	if ((r = sys_page_alloc(0, va, PTE_P|PTE_W|PTE_U|PTE_SHARE)) < 0)
		goto err2;
	if ((r = sys_page_map(0, va, 0, fd2data(fd1), PTE_P|PTE_W|PTE_U|PTE_SHARE)) < 0)
		goto err3;

	// set up fd structures
	fd0->fd_dev_id = devpipe.dev_id;
	fd0->fd_omode = O_RDONLY;

	fd1->fd_dev_id = devpipe.dev_id;
	fd1->fd_omode = O_WRONLY;

	if (debug)
		cprintf("[%08x] pipecreate %08x\n", env->env_id, vpt[VPN(va)]);

	pfd[0] = fd2num(fd0);
	pfd[1] = fd2num(fd1);
	return 0;

    err3:
	sys_page_unmap(0, va);
    err2:
	sys_page_unmap(0, fd1);
    err1:
	sys_page_unmap(0, fd0);
    err:
	return r;
}

static int
_pipeisclosed(struct Fd *fd, struct Pipe *p)
{
	// Your code here.
	// 
	// Check pageref(fd) and pageref(p),
	// returning 1 if they're the same, 0 otherwise.
	// 
	// The logic here is that pageref(p) is the total
	// number of readers *and* writers, whereas pageref(fd)
	// is the number of file descriptors like fd (readers if fd is
	// a reader, writers if fd is a writer).
	// 
	// If the number of file descriptors like fd is equal
	// to the total number of readers and writers, then
	// everybody left is what fd is.  So the other end of
	// the pipe is closed.

	//panic("_pipeisclosed not implemented");
	int run_count1, run_count2;
	int fd_ref, pipe_ref;
	while (1) {
		run_count1 = env->env_runs;
		fd_ref = pageref(fd);
		pipe_ref = pageref(p);
		run_count2 = env->env_runs;

		if (run_count1 == run_count2) {
			if (fd_ref == pipe_ref)
				return 1;
			else
				return 0;
		}
	}
}

int
pipeisclosed(int fdnum)
{
	struct Fd *fd;
	struct Pipe *p;
	int r;

	if ((r = fd_lookup(fdnum, &fd)) < 0)
		return r;
	p = (struct Pipe*) fd2data(fd);
	return _pipeisclosed(fd, p);
}

static ssize_t
piperead(struct Fd *fd, void *vbuf, size_t n, off_t offset)
{
	// Your code here.  See the lab text for a description of
	// what piperead needs to do.  Write a loop that 
	// transfers one byte at a time.  If you decide you need
	// to yield (because the pipe is empty), only yield if
	// you have not yet copied any bytes.  (If you have copied
	// some bytes, return what you have instead of yielding.)
	// If the pipe is empty and closed and you didn't copy any data out,
	// return 0.
	// Use _pipeisclosed to check whether the pipe is closed.

	//panic("piperead not implemented");
	struct Pipe *p = (struct Pipe *) fd2data(fd);
	int read_count = 0;

	while (p->p_rpos >= p->p_wpos) {
		if (_pipeisclosed(fd, p))
			return 0;
		sys_yield();
	}

	while ((p->p_rpos < p->p_wpos) && (read_count < n)) {
		((char *)vbuf)[read_count++] = p->p_buf[(uint32_t)p->p_rpos % PIPEBUFSIZ];
		p->p_rpos++;
	}
	return read_count;
	/*return -E_INVAL;*/
}

static ssize_t
pipewrite(struct Fd *fd, const void *vbuf, size_t n, off_t offset)
{
	// Your code here.  See the lab text for a description of what 
	// pipewrite needs to do.  Write a loop that transfers one byte
	// at a time.  Unlike in read, it is not okay to write only some
	// of the data.  If the pipe fills and you've only copied some of
	// the data, wait for the pipe to empty and then keep copying.
	// If the pipe is full and closed, return 0.
	// Use _pipeisclosed to check whether the pipe is closed.

	//panic("pipewrite not implemented");
	struct Pipe *p = (struct Pipe *) fd2data(fd);
	int write_count = 0;

	while (write_count < n) {
		while ((p->p_wpos-p->p_rpos) >= PIPEBUFSIZ) {
			if (_pipeisclosed(fd, p))
				return 0;
			sys_yield();
		}

		p->p_buf[(uint32_t)p->p_wpos % PIPEBUFSIZ] = ((char *)vbuf)[write_count++];
		p->p_wpos++;
	}

	return write_count;
	/*return -E_INVAL;*/
}

static int
pipestat(struct Fd *fd, struct Stat *stat)
{
	struct Pipe *p = (struct Pipe*) fd2data(fd);
	strcpy(stat->st_name, "<pipe>");
	stat->st_size = p->p_wpos - p->p_rpos;
	stat->st_isdir = 0;
	stat->st_dev = &devpipe;
	return 0;
}

static int
pipeclose(struct Fd *fd)
{
	int r;

	if ((r=sys_page_unmap(0, (void *) fd)) < 0)
		return r;

	return sys_page_unmap(0, fd2data(fd));
}

