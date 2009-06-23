/*
	for 	j <- 2 to length[A]
	    do 	key <- A[j]
		i <- j-1
		while	i > 0  and  A[i] > key
		    do	A[i+1] <- A[i]
		    	i <- i-1
		    done
		A[i+1] <- key
	    done
*/

        /* j -> $5
         * i -> $6
         * A -> $7 (but count from 1, that is , $7[1] is the first elem)
         * len(A) -> $8
         */
        /* TODO load $7 $8 */
        
        //for 	j <- 2 to length[A]
        addi $5,$0,2
FORBEG: 
        slt $1,$8,$5
        bne $1,$0,END
        //do 	key <- A[j]  
        add $2,$5,$7
        lw $1,0($2)//key->$1
	//i <- j-1
        subi $6,$5,1
	//while	i > 0  and  A[i] > key
WHILEBEG: 
        slt $2,0,$6
        beq $2,$0,WHILEEND
        add $3,$7,$6
        lw $4,0($3) //A[i] -> $4
        slt $2,$1,$4
        beq $2,$0,WHILEEND
	//do	A[i+1] <- A[i]
        addi $3,$3,1
        sw $4,0($3)
	//i <- i-1
        subi $6,$6,1
	//done
        beq $0,$0,WHILEBEG
WHILEEND: 
	//A[i+1] <- key
        addi $2,$6,1
        add $2,$2,$7
        sw $1,0($7)
	//done
        beq $0,$0,FORBEG
END: //END of for j <- 2 to lenth[A]
        swi 1