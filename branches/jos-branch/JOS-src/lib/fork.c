// implement fork from user space

#include <inc/string.h>
#include <inc/lib.h>

// PTE_COW marks copy-on-write page table entries.
// It is one of the bits explicitly allocated to user processes (PTE_AVAIL).
#define PTE_COW		0x800

//
// Custom page fault handler - if faulting page is copy-on-write,
// map in our own private writable copy.
//
static void
pgfault(struct UTrapframe *utf)
{
	void *addr = (void *) utf->utf_fault_va;
	uint32_t err = utf->utf_err;
	int r;

	// Check that the faulting access was (1) a write, and (2) to a
	// copy-on-write page.  If not, panic.
	// Hint:
	//   Use the read-only page table mappings at vpt
	//   (see <inc/memlayout.h>).

	// LAB 4: Your code here.
	pte_t pte = ((pte_t *)vpt)[PPN(addr)];
	if((err & FEC_WR) != 0 && (pte & PTE_COW) != 0){
		sys_page_alloc(0,PFTEMP,PTE_P|PTE_U|PTE_W);
		memmove(PFTEMP,ROUNDDOWN(addr,PGSIZE),PGSIZE);
		sys_page_map(0,PFTEMP,0,ROUNDDOWN(addr,PGSIZE),PTE_P|PTE_U|PTE_W);
		sys_page_unmap(0,PFTEMP);
	}else{
		panic("[%08x] Unknown page fault at %08x err: %x\n",env->env_id,addr,err);
	}

	// Allocate a new page, map it at a temporary location (PFTEMP),
	// copy the data from the old page to the new page, then move the new
	// page to the old page's address.
	// Hint:
	//   You should make three system calls.
	//   No need to explicitly delete the old page's mapping.
	
	// LAB 4: Your code here.
	
	//panic("pgfault not implemented");
}

//
// Map our virtual page pn (address pn*PGSIZE) into the target envid
// at the same virtual address.  If the page is writable or copy-on-write,
// the new mapping must be created copy-on-write, and then our mapping must be
// marked copy-on-write as well.  (Exercise: Why mark ours copy-on-write again
// if it was already copy-on-write?)
//
// Returns: 0 on success, < 0 on error.
// It is also OK to panic on error.
// 
static int
duppage(envid_t envid, unsigned pn)
{
	int r;
	void *addr;
	pte_t pte;

	// LAB 4: Your code here.
	//panic("duppage not implemented");
	int ret;
	pte_t p = ((pte_t *)vpt)[pn];
	if((p & PTE_P) == 0){
		panic("In duppage: p|PTE_P = 0\n");
	}
	if((p & PTE_U) == 0){
		panic("In duppage: p |PTE_U = 0\n");
	}
	if((p & PTE_W) == 0 && (p & PTE_COW) == 0){
		if((ret = sys_page_map(0, (void *)(pn*PGSIZE),
				 envid, (void *)(pn*PGSIZE), PTE_P | PTE_U )) < 0){
			return ret;
		}
	}else{
		if((ret = sys_page_map(0, (void *)(pn*PGSIZE), 
				envid, (void *)(pn*PGSIZE), PTE_P | PTE_U | PTE_COW)) < 0){
			return ret;
		}
		if((ret = sys_page_map(0, (void *)(pn*PGSIZE), 
				0, (void *)(pn*PGSIZE), PTE_P | PTE_U | PTE_COW)) < 0){
			return ret;
		}		
	}
	return 0;
}

//
// User-level fork with copy-on-write.
// Set up our page fault handler appropriately.
// Create a child.
// Copy our address space and page fault handler setup to the child.
// Then mark the child as runnable and return.
//
// Returns: child's envid to the parent, 0 to the child, < 0 on error.
// It is also OK to panic on error.
//
// Hint:
//   Use vpd, vpt, and duppage.
//   Remember to fix "env" and the user exception stack in the child process.
//   Neither user exception stack should ever be marked copy-on-write,
//   so you must allocate a new page for the child's user exception stack.
//
envid_t
fork(void)
{
	// LAB 4: Your code here.
	//panic("fork not implemented");
	envid_t envid;
	uint8_t *addr;
	int r;
	extern unsigned char end[];
	set_pgfault_handler(pgfault);
	envid = sys_exofork();
	if (envid < 0)
		panic("sys_exofork: %e", envid);
	if (envid == 0) {
		// We're the child.
		// The copied value of the global variable 'env'
		// is no longer valid (it refers to the parent!).
		// Fix it and return 0.
		env = &envs[ENVX(sys_getenvid())];
		return 0;
	}
	// We're the parent.
	int i,j;
	for(i=0; i*PTSIZE < UTOP; i++) {
		if(((pte_t *)vpd)[i] & PTE_P) {
			//cprintf("\n\nmapping %08x",i*PTSIZE);
			for(j=0; i*PTSIZE + j*PGSIZE < UTOP && j < NPTENTRIES; j++) {
				if(i*PTSIZE + j*PGSIZE == UXSTACKTOP-PGSIZE){
					continue;
				}
				//cprintf("mapping %08x",i*PTSIZE+ j*PGSIZE );
				// Copy mapping if necessary
				pte_t pte = ((pte_t *)vpt)[i*NPTENTRIES + j];
				if( (pte & PTE_P) && (pte & PTE_U)){
					duppage(envid, i*NPTENTRIES + j);
				}
			}
		}
	} 

	if((r = sys_page_alloc(envid, (void *)UXSTACKTOP-PGSIZE, PTE_P|PTE_U|PTE_W))< 0){
		panic("sys_page_alloc: %e", r);
	}

	// Also copy the stack we are currently running on.

	// Start the child environment running
	extern void _pgfault_upcall(void);//This is very important, you must dec it as a func pointer.
	sys_env_set_pgfault_upcall(envid,_pgfault_upcall);
	if ((r = sys_env_set_status(envid, ENV_RUNNABLE)) < 0)
		panic("sys_env_set_status: %e", r);

	return envid;
}

// Challenge!
int
sfork(void)
{
	panic("sfork not implemented");
	return -E_INVAL;
}
