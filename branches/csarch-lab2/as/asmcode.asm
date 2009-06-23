DATA SEG    
        6
        6
        1
        3
        4
        2
        5
        DATA END        
        #A -> $7 (but count from 1, that is , $7[1] is the first elem)
        #len(A) -> $8

        addi $1 $0 512
        addi $2 $0 7
        swi 2
        
        addi $7 $0 512
        lw $8 0 $7
        
        #for 	j <- 2 to length[A]  j->$5
        addi $5 $0 2
FORBEG: 
        slt $1 $8 $5
        bne $1 $0 END
        #do 	key <- A[j]
        add $2 $5 $5
        add $2 $2 $2
        add $2 $2 $7
        lw $1 0 $2
        #key->$1
	#i <- j-1  i->$6
        addi $6 $5 -1
	#while	i > 0  and  A[i] > key
WHILEBEG: 
        slt $2 $0 $6
        beq $2 $0 WHILEEND
        add $3 $6 $6
        add $3 $3 $3
        add $3 $3 $7
        lw $4 0 $3
        #A[i] -> $4
        slt $2 $1 $4
        beq $2 $0 WHILEEND
	#do	A[i+1] <- A[i]
        addi $3 $3 4
        sw $4 0 $3
	#i <- i-1
        addi  $6 $6 -1
	#done
        beq $0 $0 WHILEBEG
WHILEEND: 
	#A[i+1] <- key
        addi $2 $6 1
        add $2 $2 $2
        add $2 $2 $2    
        add $2 $2 $7
        sw $1 0 $2 
	#done
        addi $5 $5 1
        beq $0 $0 FORBEG
END:
        #END of for j <- 2 to lenth[A]

        addi $1 $0 512
        addi $2 $0 7
        swi 2

        swi 1