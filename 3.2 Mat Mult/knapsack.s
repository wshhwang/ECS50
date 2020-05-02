/*

unsigned int max(unsigned int a, unsigned int b){
   //computes the max of a and b
  return a > b ? a : b;
}

unsigned int knapsack(int* weights, unsigned int* values, unsigned int num_items, 
              int capacity, unsigned int cur_value){
		  /
		  solves the knapsack problem
		  @weights: an array containing how much each item weighs
		  @values: an array containing the value of each item
		  @num_items: how many items that we have
		  @capacity: the maximum amount of weight that can be carried
		  @cur_weight: the current weight
		  @cur_value: the current value of the items in the pack
		  /
  unsigned int i;
  unsigned int best_value = cur_value;
  
  for(i = 0; i < num_items; i++){//for each remaining item
    if(capacity - weights[i] >= 0 ){//if we can fit this item into our pack
      //see if it will give us a better combination of items
      best_value = max(best_value, knapsack(weights + i + 1, values + i + 1, num_items - i - 1, 
                     capacity - weights[i], cur_value + values[i]));
    }				//if we can fit this item into our pack   
  }				//try to find the best combination of items among the remaining items
  return best_value;
}//knapsack
*/


.global knapsack
.equ ws, 4
.text

	/*
	unsigned int max(unsigned int a, unsigned int b){
	   //computes the max of a and b    
		// a=5  b=6   6-5=1      a<b 
		// a=5  b=5   5-5=0	 a=b	return movl %ebx, %eax
		// a=5  b=3   3-5=-2     a>b   return movl %eax
		
	  return a > b ? a : b;   // if a > b    =  0 > b - a   is 0 or bigger then return b
				 //   return a
				//  else
				//    return b
	}
	*/
	/*max:
		push %ebp
		movl %esp,%ebp
		#%eax is a
		#%ebx is b
		.equ a, 2*ws
		.equ b, 3*ws
		movl %edx,a(%ebp)
		movl %ebx,b(%ebp)
		movl a(%ebp), %eax
		cmpl %eax, b(%ebp) #b-a less than 0 a>b -> max is a   return epilogue
		jge a_greater  #a is greater
		movl b(%ebp), %eax   # b is max	
		
	a_greater:
		
		movl %esp, %ebp
		pop %ebp
		ret
	*/

/*
unsigned int knapsack(int* weights, unsigned int* values, unsigned int num_items, 
              int capacity, unsigned int cur_value){
  
  solves the knapsack problem
  @weights: an array containing how much each item weighs
  @values: an array containing the value of each item
  @num_items: how many items that we have
  @capacity: the maximum amount of weight that can be carried
  @cur_weight: the current weight
  @cur_value: the current value of the items in the pack
  
  unsigned int i;
  unsigned int best_value = cur_value;
  
  for(i = 0; i < num_items; i++){//for each remaining item
    if(capacity - weights[i] >= 0 ){//if we can fit this item into our pack
      //see if it will give us a better combination of items
      best_value = max(best_value, knapsack(weights + i + 1, values + i + 1, num_items - i - 1, 
                     capacity - weights[i], cur_value + values[i]));
    }//if we can fit this item into our pack   
  }//try to find the best combination of items among the remaining items
  return best_value;
}
*/

knapsack:
	#prologue:
		push %ebp
		movl %esp, %ebp
		subl $4*ws, %esp #make spaces
		#i is i(%ebp) = 0
		push %ebx
		push %edi   #i
		push %esi    
		

		.equ weights, 2*ws     	#weights: an array containing how much each item weighs
		.equ values, 3*ws  		#@values: an array containing the value of each item
		.equ num_items, 4*ws  	#@num_items: how many items that we have
		.equ capacity, 5*ws		#@capacity: the maximum amount of weight that can be carried
		#.equ cur_weight, 6*ws		#@cur_weight: the current weight
		.equ cur_value, 6*ws		#@cur_value: the current value of the items in the pack
		.equ max_value, -1*ws  #best_value
		.equ i, -2*ws   # unsigned int i;
		
		
			
				
		movl weights(%ebp), %ecx
		movl values(%ebp), %ebx
		movl num_items(%ebp), %esi
		movl capacity(%ebp), %eax
		movl cur_value(%ebp), %edx
		movl %edx, max_value(%ebp)  # unsigned int best_value = cur_value;
						#movl cur_value(%ebp), %eax
						#@@@@movl %eax, max_value(%ebp)
		movl $0,i(%ebp)   
		movl i(%ebp), %edi
		
		
		
		
		
		#jmp end_loop
			#i is i(%ebp) = 0
		
for_loop: #for(i = 0; i < num_items; i++)   
			

			jmp end_loop
			
			check:
			#cmpl %esi, %edi    #  i - num_items < 0 -> i-num_items >0
			#jae end_loop #if below 0
				#movl num_items(%ebp), %esi		# 0-4< 0	 
				#cmpl num_items(%ebp), %edi    #  i - num_items < 0 -> i-num_items >0
				#jbe end_loop
				#jg end_loop #greater 0
				
				
			#if(capacity - weights[i] >= 0 )  #%ecx , %edx available
				/*movl i(%ebp), %edi
				movl capacity(%ebp), %ecx   #capacity = %ecx
				movl weights(%ebp), %edx     #weight = %edx
				leal (%edx, %edi, ws), %edx  #weight[i] = %edx
				cmpl (%edx), %ecx  #capacity - weight[i] is below 0  ##seg error
				jl else  #less than 0*/
				

				movl weights(%ebp), %ecx
				leal (%ecx,%edi,ws), %edx
				cmpl (%edx), %eax
				jl else			


			
			/*
	    best_value = 
            max(best_value, knapsack(weights+i+1, values+i+1, num_items-i-1, capacity-weights[i], cur_value + values[i]));
			*/
			
				if:
	
				#cur_value +value[i]
					#movl i(%ebp), %edi
				#movl values(%ebp), %ebx  # %ebx = values
				movl cur_value(%ebp), %eax  # %eax = cur_values                 
 				
				leal (%ebx, %edi,ws),%edx #ebx = values[i]
				addl (%edx), %eax   #eax = cur_values +values [i]
						#addl (%ebx, %edi, ws),%esi #%esi = cur_values + value[i]    ###segment error
				push %eax


				#capacity - weight[i]
										#movl i(%ebp), %edi
										#movl weights(%ebp), %edx     #weight = %edx
										#leal (%edx, %edi, ws), %edx  #weight[i] = %edx
										#movl (%edx), %edx
				movl capacity(%ebp), %eax   #capacity = %ecx
				leal (%ecx, %edi, ws), %edx
				subl (%edx), %eax   # "if:" -> #capacity = %ecx #weight = %edx 		
				push %eax   

				#num_items - i - 1
				movl num_items(%ebp), %eax  #eax = num_items
				#movl i(%ebp), %edi				
				subl %edi, %eax  #esi - i

				subl $1, %eax    #(esi-i) - 1								
				push %eax   #num_items - i - 1

				#values +i +1
				#movl i(%ebp), %edi
				movl values(%ebp), %eax
				#addl $1, %edi
				leal 4(%eax, %edi, ws), %eax
				push %eax

				#weights +i +1
				#movl i(%ebp), %edi
				#addl $1, %edi
				movl weights(%ebp), %eax
				leal 4(%eax, %edi, ws), %eax
				push %eax   #weights +i +1

				#push %esi   #%esi = cur_values + value[i]  
				#push %eax   #num_items - i - 1
				#push %ebx   # values +i +1
				#push %ecx   #capacity - weight[i]
				

				
				#movl %edi, i(%ebp)
	
				call knapsack #knapsack ()
				addl $5 *ws, %esp #clear arguments


				#max value
				
								#movl weights(%ebp), %ecx
								#movl cur_value(%ebp), %edx
check_max:								
				cmpl %eax, max_value(%ebp)
							#jb max  #below or equal 0
							#cmpl %eax, max_value(%ebp)
				jae else  #above or equal
				movl %eax, max_value(%ebp)

				#movl %edi, %esi
				#movl max_value(%ebp), %eax
				#push %eax
				#movl %esi,%ebx  # [B] values+i+1 = num_items -1 -1
				#movl %eax,%edx  # [A] weight+i+1 = max_value

				#call max  #return eax is max value
				
				#movl %eax, max_value(%ebp)
				#movl i(%ebp), %edi
				#addl $4 *ws, %esp #clear arguments
								
			else:
				#addl $1,%edi
				incl %edi
				jmp for_loop
	end_loop:
				movl weights(%ebp), %ecx
				movl capacity(%ebp), %eax
				movl cur_value(%ebp), %edx
							
				cmpl %esi, %edi
				jb check				


				#movl max_value(%ebp), %eax
				#movl capacity(%ebp), %eax
				#movl weights(%ebp), %ecx
				#movl cur_value(%ebp), %edx

				#cmpl %esi, %edi    #  i - num_items < 0 -> i-num_items >0
				#jb for_loop #if below 0

	 			#jg end_loop #greater 0
				#movl max_value(%ebp), %eax
				movl max_value(%ebp), %eax
	#epilogue:
				pop %esi
				pop %edi
				pop %ebx
			
				pop %ecx
				pop %edx

				movl %ebp, %esp
				pop %ebp
				ret















