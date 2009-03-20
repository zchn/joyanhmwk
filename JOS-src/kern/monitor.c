// Simple command-line kernel monitor useful for
// controlling the kernel and exploring the system interactively.

#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/memlayout.h>
#include <inc/assert.h>
#include <inc/x86.h>

#include <kern/console.h>
#include <kern/monitor.h>
#include <kern/kdebug.h>
#include <kern/pmap.h>

#define CMDBUF_SIZE	80	// enough for one VGA text line


struct Command {
	const char *name;
	const char *desc;
	// return -1 to force monitor to exit
	int (*func)(int argc, char** argv, struct Trapframe* tf);
};

static struct Command commands[] = {
	{ "help", "Display this list of commands", mon_help },
	{ "kerninfo", "Display information about the kernel", mon_kerninfo },
        { "backtrace", "Display the current backtrace",mon_backtrace },
        { "showmappings", "Display the mmu mappings",mon_showmappings },
};
#define NCOMMANDS (sizeof(commands)/sizeof(commands[0]))

unsigned read_eip();

/***** Implementations of basic kernel monitor commands *****/

int
mon_help(int argc, char **argv, struct Trapframe *tf)
{
	int i;

	for (i = 0; i < NCOMMANDS; i++)
		cprintf("%s - %s\n", commands[i].name, commands[i].desc);
	return 0;
}

int
mon_kerninfo(int argc, char **argv, struct Trapframe *tf)
{
	extern char _start[], etext[], edata[], end[];

	cprintf("Special kernel symbols:\n");
	cprintf("  _start %08x (virt)  %08x (phys)\n", _start, _start - KERNBASE);
	cprintf("  etext  %08x (virt)  %08x (phys)\n", etext, etext - KERNBASE);
	cprintf("  edata  %08x (virt)  %08x (phys)\n", edata, edata - KERNBASE);
	cprintf("  end    %08x (virt)  %08x (phys)\n", end, end - KERNBASE);
	cprintf("Kernel executable memory footprint: %dKB\n",
		(end-_start+1023)/1024);
	return 0;
}

int
mon_backtrace(int argc, char **argv, struct Trapframe *tf)
{
	// Your code here.
        uint32_t *fp = (uint32_t *)read_ebp();
	uint32_t eip = read_eip();
	char fn[50]; 
	int i;
	struct Eipdebuginfo info;
        cprintf("Stack backtrace:\n");
        while(fp != NULL){
		debuginfo_eip(eip,&info);
		strncpy(fn,info.eip_fn_name,info.eip_fn_namelen);
		fn[info.eip_fn_namelen] = 0;
		cprintf("%s:%d: %s+%d\n",info.eip_file,info.eip_line,fn,eip-info.eip_fn_addr);
                cprintf("  ebp %08x  eip %08x  args",
                        fp,fp[1],fp[2],fp[3],fp[4],fp[5],fp[6]);
		for(i = 2;i-2<info.eip_fn_narg;i++){
			cprintf(" %08x",fp[i]);
		}
		cprintf("\n");
		eip = fp[1];
                fp = (uint32_t *)(*fp);
        }
	return 0;
}


int
mon_showmappings(int argc, char **argv, struct Trapframe *tf)
{
	if(argc != 3) goto USAGE;
	uintptr_t beg_addr,end_addr,curr;
	beg_addr = (uintptr_t) strtol(argv[1],NULL,0);
	end_addr = (uintptr_t) strtol(argv[2],NULL,0);
	cprintf("Page mapping from %s to %s:\n",argv[1],argv[2]);
	for(curr = beg_addr; curr < end_addr+PGSIZE; curr += PGSIZE){
		pte_t *ppte = pgdir_walk((pde_t *)rcr3(), (const void *)curr, 0);
		if(ppte == NULL){
			cprintf("   V:%08x -> NOT MAPPED\n");
		}else{
			pte_t pte = *ppte;
			cprintf("   V:%08x -> P:%08x",curr-PGOFF(curr),PTE_ADDR(pte));
			if(pte & PTE_P) cprintf(" P");
			if(pte & PTE_W) cprintf(" W");
			if(pte & PTE_U) cprintf(" U");
			if(pte & PTE_PWT) cprintf(" PWT");
			if(pte & PTE_PCD) cprintf(" PCD");
			if(pte & PTE_A) cprintf(" A");
			if(pte & PTE_D) cprintf(" D");
			if(pte & PTE_PS) cprintf(" PS");
			if(pte & PTE_MBZ) cprintf(" MBZ");
			cprintf("\n");
		}
	}
	return 0;
USAGE:
	cprintf("USAGE: showmappings beg_addr end_addr\n");
	return 0;
}


/***** Kernel monitor command interpreter *****/

#define WHITESPACE "\t\r\n "
#define MAXARGS 16

static int
runcmd(char *buf, struct Trapframe *tf)
{
	int argc;
	char *argv[MAXARGS];
	int i;

	// Parse the command buffer into whitespace-separated arguments
	argc = 0;
	argv[argc] = 0;
	while (1) {
		// gobble whitespace
		while (*buf && strchr(WHITESPACE, *buf))
			*buf++ = 0;
		if (*buf == 0)
			break;

		// save and scan past next arg
		if (argc == MAXARGS-1) {
			cprintf("Too many arguments (max %d)\n", MAXARGS);
			return 0;
		}
		argv[argc++] = buf;
		while (*buf && !strchr(WHITESPACE, *buf))
			buf++;
	}
	argv[argc] = 0;

	// Lookup and invoke the command
	if (argc == 0)
		return 0;
	for (i = 0; i < NCOMMANDS; i++) {
		if (strcmp(argv[0], commands[i].name) == 0)
			return commands[i].func(argc, argv, tf);
	}
	cprintf("Unknown command '%s'\n", argv[0]);
	return 0;
}

void
monitor(struct Trapframe *tf)
{
	char *buf;

	cprintf("Welcome to the JOS kernel monitor!\n");
	cprintf("Type 'help' for a list of commands.\n");


	while (1) {
		buf = readline("K> ");
		if (buf != NULL)
			if (runcmd(buf, tf) < 0)
				break;
	}
}

// return EIP of caller.
// does not work if inlined.
// putting at the end of the file seems to prevent inlining.
unsigned
read_eip()
{
	uint32_t callerpc;
	__asm __volatile("movl 4(%%ebp), %0" : "=r" (callerpc));
	return callerpc;
}
