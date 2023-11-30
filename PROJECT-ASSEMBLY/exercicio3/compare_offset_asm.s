/*
int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue) {
	return k < values[i][j].len && values[i][j].offset[k] == avalue->offset[k];
}
*/

	.text
	.global	compare_offset
	
compare_offset:
	
    imul	$8, %rsi  
    add 	%rsi, %rdi  
    mov		(%rdi), %rdi
    imul	$16, %rdx  
    add 	%rdx, %rdi       
    
    mov 	(%rdi), %r9b 
    
    cmpb 	%r9b , %cl        
    jge 	return_zero_compare_offset 
    
	mov 	%rdi, %r10
	lea 	8(%r10), %r10
	mov 	(%r10), %r10
	lea 	(%r10, %rcx, 2), %r10
	mov 	$0, %r9
	movw 	(%r10), %r9w
	
	lea		8(%r8), %r8
	mov 	(%r8), %r8
	lea		(%r8, %rcx, 2), %r8
	mov 	$0, %r10
	movw	(%r8), %r10w
	
	cmp 	%r9, %r10
	je		return_one_compare_offset
	
return_zero_compare_offset:
	mov 	$0, %rax
	ret

return_one_compare_offset:
    mov 	$1, %rax
    ret
	
    .section .note.GNU-stack
    .end
