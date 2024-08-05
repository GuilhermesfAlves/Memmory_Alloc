.section .data
.globl original_brk
original_brk: .quad 1
.section .text
.globl setup_brk
.globl dismiss_brk
.globl memory_alloc
.globl memory_free
setup_brk:
pushq %rbp
movq %rsp, %rbp
    movq $12, %rax
    movq $0, %rdi
    syscall
    movq %rax, original_brk
popq %rbp
ret 
dismiss_brk:
pushq %rbp
movq %rsp, %rbp
    movq $12, %rax
    movq original_brk, %rdi
    syscall
popq %rbp
ret
memory_alloc:
pushq %rbp
movq %rsp, %rbp
    pushq %rdi
    movq $12, %rax
    movq $0, %rdi
    syscall
    popq %rdi
    movq %rax, %r11 # dynamic_brk
    movq %r11, %r10 # greater_unused_brk
    movq original_brk, %r9 # iterator_brk
    while:
        cmpq %r11, %r9
        jge out_while
        cmpb $0, (%r9)
        jne endif1
            movq $9, %rdx
            addq %rdi, %rdx
            cmpq %rdx, 1(%r9)
            jl endif1
                movq 1(%r9), %rdx
                cmpq %rdx, 1(%r10)
                jg endif1
                    movq %r9, %r10
        endif1:
        movq 1(%r9), %rdx
        addq $9, %rdx
        addq %rdx, %r9
    jmp while
    out_while:
    cmpq original_brk, %r11
    cmpq %r11, %r10
    jne endif3
        movq $12, %rax
        movq %rdi, %r9
        addq %r10, %rdi
        addq $9, %rdi
        syscall
        movb $1, (%r10)
        movq %r9, 1(%r10)
        jmp end_malloc
    endif3:
    movb $1, (%r10)
    movq %rdi, %rdx
    addq $10, %rdx
    cmpq %rdx, 1(%r10)
    jge endif4
        jmp end_malloc
    endif4:
    movq %rdi, %rdx
    addq %r10, %rdx
    addq $9, %rdx
    movq 1(%r10), %rsi
    subq %rdi, %rsi
    subq $9, %rsi
    movq %rsi, 1(%rdx)
    movb $0, (%rdx)
    movq %rdi, 1(%r10)
end_malloc:
movq %r10, %rax 
addq $9, %rax
popq %rbp
ret
memory_free:
pushq %rbp
movq %rsp, %rbp
    movq %rdi, %r10
    movq $0, %rdi
    movq $12, %rax
    syscall
    cmpq %rax, %r10
    movq $0, %rax
    jge end_memory_free
    movb $0, -9(%r10) 
    movl $1, %eax
end_memory_free:
popq %rbp
ret 
