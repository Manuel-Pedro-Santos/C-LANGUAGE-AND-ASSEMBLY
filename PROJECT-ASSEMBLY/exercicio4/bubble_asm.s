/*
static void memswap(void *one, void *other, size_t width){
	char tmp[width];
	memcpy(tmp, one, width);
	memcpy(one, other, width);
	memcpy(other, tmp, width);
}
*/
	.text
memswap:
    mov $1, %r8 #;R8 = i
    mov %rdi, %rcx
    mov %rsi, %r11

.for:
    cmp %r8, %rdx
    jle .end
    movb (%rdi), %r9b
    movb (%rsi), %r10b
    movb %r10b, (%rdi)
    movb %r9b, (%rsi)

    inc %rdi
    inc %rsi
    inc %r8b
    jmp .for
.end:
    mov %rcx,%rdi
    mov %r11,%rsi
    mov $0,%rax
    ret

/*
void bubble_sort(void *base, size_t nelements, size_t width,
			int (*compare)(const void *, const void *)) {
	int swap_flg = 0;
	if (nelements <= 1)
		return;
	char *limit = (char *)base + (nelements - 1) * width;
	for (char *ptr = base; ptr < limit; ptr += width)
		if (compare(ptr, ptr + width) > 0) {
			memswap(ptr, ptr + width, width);
			swap_flg = 1;
		}
	if (swap_flg == 0)
		return;
	bubble_sort(base, nelements - 1, width, compare);
}
*/


	.text
	.global	bubble_sort
bubble_sort:

	push	%rbx					# *base
	push	%rbp					# nelements
	push	%r12					# witdh
	push	%r13					# *limit
	push	%r14					# *ptr
	push	%r15					# swapflag
	
	mov 	%rdi, %rbx
	mov 	%rsi, %rbp
	mov 	%rdx, %r12
	mov 	%rcx, %r13
	xor		%r15d, %r15d			 # swap_flag = 0
	
	cmp 	$1, %rbp				 # nelements <= 1
	jle	 	ret_bubble_sort
	
	# LIMIT
	lea 	-1(%rbp), %r8   	 	# nelements -1
	mov		%r8, %rax
	mul 	%r12
	lea 	(%rbx,%rax), %r9 		#  limit = base + (nelems -1) * width
	
	mov     %rbx, %r14         		# ptr = base

for_bubble_sort:
	lea 	-1(%rbp), %r8   	 	# nelements -1
	mov		%r8, %rax
	mul 	%r12
	lea 	(%rbx,%rax), %r9 		#  limit = base + (nelems -1) * width
	
    cmp     %r14, %r9
    jle      end_bubble_sort  		# Jump if ptr is below limit
	
    mov     %r14, %rdi
    lea     (%r14,%r12), %rsi
    call    *%rcx
    mov		%r13, %rcx

    test    %eax, %eax
    js      for_inc_bubble_sort  	# Jump if result is negative (compare < 0)
	
	mov     %r14, %rdi
    lea     (%r14,%r12), %rsi
    mov     %r12, %rdx
    call    memswap
    mov		%r13, %rcx
    mov     $1, %r15d

for_inc_bubble_sort:
	lea		(%r14, %r12), %r14
    jmp     for_bubble_sort

end_bubble_sort:
	cmp		$0, %r15
	jz		ret_bubble_sort
	mov		%rbx, %rdi
	dec 	%rbp
	mov		%rbp, %rsi
	mov		%r12, %rdx
	mov		%r13, %rcx
	call 	bubble_sort

ret_bubble_sort: 
	pop		%r15
	pop		%r14
	pop		%r13
	pop		%r12
	pop		%rbp
	pop		%rbx
	ret

	.section .note.GNU-stack
	.end
