.global matMult
.text
.equ wordsize, 4


matMult:
    #prologue

    push %ebp #base pointer
    movl %esp, %ebp #set ebp to esp

    subl $5*wordsize, %esp #2*wordsize space for esp

           
#matA
    .equ A, (2 * wordsize)
    .equ num_row_a, (3 * wordsize) #num_row_a
    .equ num_column_a, (4 * wordsize) #num_column_a
#matB
	.equ B, (5 * wordsize)
 	.equ num_row_b, (6 * wordsize)  #num_row_b
	.equ num_column_b, (7 * wordsize)  #num_column_b

   	.equ i, (-1 * wordsize)   #%ebp
    .equ j, (-2 * wordsize) #%ebp
    .equ k, (-3 * wordsize) #%ebp
    .equ sum, (-4 * wordsize) #%ebp
	.equ final, (-5 * wordsize) #%ebp
	

	push %ebx  
	movl $0, %ebx   #ebx = 0
	push %edi
	push %esi
	
    movl $0, final(%ebp)   #final = 0

start:
    movl num_row_a(%ebp), %eax   #eax = num row a
    shll $2, %eax     #num row a * sizeof(int)
    push %eax      #set argument for malloc
    call malloc
    movl %eax, sum(%ebp)
    addl $1 * wordsize, %esp    #clear argument for malloc


first_for_loop: #++i
    movl num_column_b(%ebp), %eax
    shll $2, %eax  #num row b * sizeof(int)
    push %eax    #set argument for malloc
    call malloc

    addl $1 * wordsize, %esp   #clear argument
    movl sum(%ebp), %edi   #edi= sum
    movl %eax, (%edi,%ebx,wordsize)

    movl $0, %edx
	jmp first_for_loop_end


second_for_loop: #++j
    movl $0, %ecx
	jmp second_for_loop_end

third_for_loop: #++k
    #A[i][k]
    movl A(%ebp), %eax
    movl B(%ebp), %esi
	movl (%eax,%ebx,wordsize), %eax
    movl (%eax,%ecx,wordsize), %eax
    #B[k][j]
 	movl (%esi,%ecx,wordsize), %esi
    #A[i][k]*B[k][j] = eax
    imul (%esi,%edx,wordsize), %eax
    #final = eax =A[i][k]*B[k][j]
    addl %eax, final(%ebp)

	addl $1, %ecx
	cmpl num_row_b(%ebp), %ecx
	jl third_for_loop
		

third_for_loop_end:
	movl sum(%ebp), %edi
	movl (%edi,%ebx,wordsize), %edi
	movl final(%ebp), %eax
	                
	movl %eax, (%edi,%edx,wordsize)
           
	movl $0, final(%ebp)
            
	addl $1, %edx  #++j
	jmp second_for_loop

second_for_loop_end:
	cmpl num_column_b(%ebp), %edx
	jl third_for_loop

    addl $1, %ebx   #++i
	jmp first_for_loop     
       
first_for_loop_end:
	cmpl num_row_a(%ebp), %ebx
	jl second_for_loop

	movl sum(%ebp), %eax
	

#epilogue
end:
	pop %esi
	pop %edi
	pop %ebx

	movl %ebp, %esp
	pop %ebp
      
	ret

#add line

