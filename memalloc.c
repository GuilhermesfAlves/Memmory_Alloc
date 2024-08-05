// implementa uma versão em C do programa em assembly

//Obtém o endereço de brk
void setup_brk(){
    // syscall rax 12 rdi 0
    // brk = sys brk;
}

//Restaura o endereço de brk
void dismiss_brk(){
    // syscall rax 12 rdi original_brk
}

// #define OVERHEAD 9
 //1. Procura bloco livre com tamanho igual ou maior que a requisição
 //2. Se encontrar, marca ocupação, utiliza os bytes necessários do bloco, retornando o endereço correspondente
 //3. Se não encontrar, abre espaço para um novo bloco
void* memory_alloc(unsigned long int bytes){
    
    // long long* dynamic_brk = syscall rax 12 rdi 0;
    // long long* original_brk = 0;
/*
    long long* greater_unused_brk = dynamic_brk;
    long long* iterator_brk = original_brk; 
    // procura por um lugar para alocar os bytes
    while (iterator_brk < dynamic_brk){
        if (*iterator_brk == 0){ // se não estiver sendo usado
            if (*(iterator_brk + 1) >= bytes + OVERHEAD){ // se couber o tamanho necessário + OVERHEAD
                if (*(greater_unused_brk + 1) <= *(iterator_brk + 1))
                    greater_unused_brk = iterator_brk;
                }
            }
        }
        iterator_brk += *(iterator_brk + 1) + 1; // itera para o proximo bloco
    }
    //se não tem lugar disponível, avança o brk
    if (greater_unused_brk == dynamic_brk){ // não há nenhum bloco desalocado que caiba
        dynamic_brk += bytes + OVERHEAD; //avança o brk em syscall
        *greater_unused_brk = 1;
        *(greater_unused_brk + 1) = bytes;
        return greater_unused_brk + OVERHEAD;
    }
    //quando vai se alocar em um espaço que ja existe
    *greater_unused_brk = 1;
    //se tal tamanho não puder ser fragmentado
    if (*(greater_unused_brk + 1) > bytes + OVERHEAD + 1){
        return greater_unused_brk + OVERHEAD;
    }
    *(greater_unused_brk + 1 + bytes + 1) = *(greater_unused_brk + 1) - (bytes + OVERHEAD); 
    *(greater_unused_brk + 1 + bytes) = 0;
    *(greater_unused_brk + 1) = bytes;
    return greater_unused_brk + OVERHEAD;
*/
}

//Marca um bloco ocupado como livre
int memory_free(void *pointer){
/*
    syscall rax 12 rdi 0
    if (pointer > brk)
        return 0
    *(pointer - OVERHEAD) = 0;
*/
}