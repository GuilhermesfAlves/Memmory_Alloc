.section .bss
.global original_brk
original_brk:
    .skip 4

.section .text:
.global setup_brk
.global dismiss_brk
.global memory_alloc
.global memory_free


setup_brk:
    movl $60, %eax
    ret 

dismiss_brk:
    movl $60, %eax
    ret

memory_alloc:
    movl $60, %eax
    ret 

memory_free:
    movl $60, %eax
    ret 
