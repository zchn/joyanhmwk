/* See COPYRIGHT for copyright information. */

#include <inc/mmu.h>
#include <inc/memlayout.h>
#include <inc/trap.h>

#include <kern/picirq.h>


###################################################################
# exceptions/interrupts
###################################################################

/* The TRAPHANDLER macro defines a globally-visible function for handling
 * a trap.  It pushes a trap number onto the stack, then jumps to _alltraps.
 * Use TRAPHANDLER for traps where the CPU automatically pushes an error code.
 */ 
#define TRAPHANDLER(name, num)						\
.text;									\
	.globl name;		/* define global symbol for 'name' */	\
	.type name, @function;	/* symbol type is function */		\
	.align 2;		/* align function definition */		\
	name:			/* function starts here */		\
	pushl $(num);							\
	jmp _alltraps;							\
.data;									\
	.long num;							\
	.long name

/* Use TRAPHANDLER_NOEC for traps where the CPU doesn't push an error code.
 * It pushes a 0 in place of the error code, so the trap frame has the same
 * format in either case.
 */
#define TRAPHANDLER_NOEC(name, num)					\
.text;									\
	.globl name;							\
	.type name, @function;						\
	.align 2;							\
	name:								\
	pushl $0;							\
	pushl $(num);							\
	jmp _alltraps;							\
.data;									\
	.long num;							\
	.long name


.data
.globl idttbl
idttbl:	.long	0xDEADBEEF


/*
 * Lab 3: Your code here for generating entry points for the different traps.
 */

TRAPHANDLER_NOEC(t_divide_lbl,T_DIVIDE)
TRAPHANDLER_NOEC(t_debug_lbl,T_DEBUG)
TRAPHANDLER_NOEC(t_nmi_lbl,T_NMI)
TRAPHANDLER_NOEC(t_brkpt_lbl,T_BRKPT)
TRAPHANDLER_NOEC(t_oflow_lbl,T_OFLOW)
TRAPHANDLER_NOEC(t_bound_lbl,T_BOUND)
TRAPHANDLER_NOEC(t_illop_lbl,T_ILLOP)
TRAPHANDLER_NOEC(t_device_lbl,T_DEVICE)
TRAPHANDLER(t_dblflt_lbl,T_DBLFLT)
TRAPHANDLER(t_tss_lbl,T_TSS)
TRAPHANDLER(t_segnp_lbl,T_SEGNP)
TRAPHANDLER(t_stack_lbl,T_STACK)
TRAPHANDLER(t_gpflt_lbl,T_GPFLT)
TRAPHANDLER(t_pgflt_lbl,T_PGFLT)
TRAPHANDLER_NOEC(t_fperr_lbl,T_FPERR)
TRAPHANDLER(t_align_lbl,T_ALIGN)
TRAPHANDLER_NOEC(t_mchk_lbl,T_MCHK)
TRAPHANDLER_NOEC(t_simderr_lbl,T_SIMDERR)
TRAPHANDLER_NOEC(t_syscall_lbl,T_SYSCALL)
/*
TRAPHANDLER_NOEC(t_default_lbl,T_DEFAULT)
*/

.data
	.long 0x0
	.long 0x0

/*
 * Lab 3: Your code here for _alltraps
 */
	
.text
	.globl _alltraps;
	.align 2
_alltraps:
	push %ds
	push %es
	pushal
	movw $GD_KD,%ax
	movw %ax,%ds
	movw %ax,%es
	push %esp
	call trap
	pop %esp
	popal
	pop %es
	pop %ds
	iret

