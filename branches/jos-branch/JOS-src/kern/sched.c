#include <inc/assert.h>

#include <kern/env.h>
#include <kern/pmap.h>
#include <kern/monitor.h>


// Choose a user environment to run and run it.
void
sched_yield(void)
{
	// Implement simple round-robin scheduling.
	// Search through 'envs' for a runnable environment,
	// in circular fashion starting after the previously running env,
	// and switch to the first such environment found.
	// It's OK to choose the previously running env if no other env
	// is runnable.
	// But never choose envs[0], the idle environment,
	// unless NOTHING else is runnable.

	// LAB 4: Your code here.
	
	if(curenv == NULL){
		curenv = &envs[0];
	}
	int i;
	for(i = 1; i < NENV; i++){
		if((envs+1+(curenv+i-envs-1)%(NENV-1))->env_status == ENV_RUNNABLE){
                        //cprintf("[DEBUG] Env %08x chosen\n",(envs+1+(curenv+i-envs-1)%(NENV-1))->env_id);
			env_run(envs+1+(curenv+i-envs-1)%(NENV-1));
		}
	} 

	// Run the special idle environment when nothing else is runnable.
	if (envs[0].env_status == ENV_RUNNABLE)
		env_run(&envs[0]);
	else {
		cprintf("Destroyed all environments - nothing more to do!\n");
		while (1)
			monitor(NULL);
	}
}
