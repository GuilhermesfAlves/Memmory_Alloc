#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "memalloc.h"

#define CORRETO "\x1B[32m CORRETO!\x1B[0m"
#define INCORRETO "\x1B[31m INCORRETO\x1B[0m"

extern void *original_brk;	/* Você precisa ter a variável global que armazena o valor de brk como um extern aqui.
							No código de teste estou chamandando de original_brk, mas se utilizarem outro nome,
							substituir as ocorrências por ele aqui. */

int main() { 

	printf("============================== ROTINAS DE TESTE ==============================\n");
	
	setup_brk();
	void *initial_brk = original_brk;
	void *f_pnt, *s_pnt, *t_pnt, *n_pnt;
	// 50 41 90 1
	f_pnt = memory_alloc(100);
	printf("==>> ALOCANDO UM ESPAÇO DE 100 BYTES:\n");
	printf("\tLOCAL: %s\n", f_pnt-9 == initial_brk ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (f_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (f_pnt-8)) == 100 ? CORRETO : INCORRETO);
	printf("==>> DESALOCANDO UM ESPAÇO DE 100 BYTES:\n");
	memory_free(f_pnt);
	printf("\tIND. DE USO: %s\n", *((char*) (f_pnt-9)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (f_pnt-8)) == 100 ? CORRETO : INCORRETO);

	s_pnt = memory_alloc(50);
	t_pnt = memory_alloc(100);
	printf("==>> ALOCANDO UM ESPAÇO DE 50 BYTES:\n");
	printf("\tLOCAL: %s\n", s_pnt-9 == initial_brk ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt-8)) == 50 ? CORRETO : INCORRETO);
	printf("==>> ALOCANDO UM ESPAÇO DE 100 BYTES:\n");
	printf("\tLOCAL: %s\n", s_pnt+100 == t_pnt-9 ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (t_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (t_pnt-8)) == 100 ? CORRETO : INCORRETO);
	printf("==> VERIFICANDO A FRAGMENTAÇÃO DE MEMÓRIA:\n");
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt+50)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt+51)) == 41 ? CORRETO : INCORRETO);

	printf("==>> DESALOCANDO TUDO:\n");
	memory_free(s_pnt);
	memory_free(t_pnt);
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt-9)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt-8)) == 50 ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (t_pnt-9)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (t_pnt-8)) == 100 ? CORRETO : INCORRETO);

	n_pnt = memory_alloc(91);
	printf("==>> ALOCANDO UM ESPAÇO DE 91 BYTES:\n");
	printf("\tLOCAL: %s\n", n_pnt == t_pnt ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (n_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (n_pnt-8)) == 100 ? CORRETO : INCORRETO);

	memory_free(n_pnt);
	s_pnt = memory_alloc(90);
	printf("==>> ALOCANDO UM ESPAÇO DE 90 BYTES:\n");
	printf("\tLOCAL: %s\n", s_pnt == t_pnt ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt-8)) == 90 ? CORRETO : INCORRETO);
	printf("==> VERIFICANDO A FRAGMENTAÇÃO DE MEMÓRIA:\n");
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt+90)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt+91)) == 1 ? CORRETO : INCORRETO);
	memory_free(s_pnt);

	f_pnt = memory_alloc(1);
	printf("==>> ALOCANDO UM ESPAÇO DE 1 BYTE:\n");
	printf("\tLOCAL: %s\n", s_pnt == f_pnt ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (f_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (f_pnt-8)) == 1 ? CORRETO : INCORRETO);
	printf("==> VERIFICANDO A FRAGMENTAÇÃO DE MEMÓRIA:\n");
	printf("\tIND. DE USO: %s\n", *((char*) (f_pnt+1)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (f_pnt+2)) == 80 ? CORRETO : INCORRETO);

	printf("==>> DESALOCANDO A PILHA (ILEGAL):\n");
	unsigned long long stack_var = 0;
	unsigned int alloc_return = memory_free((void*) &stack_var);
	if (!alloc_return) printf("\tO RETORNO DA LIBERAÇÃO FOI NULL!\n");

	dismiss_brk();

	s_pnt = memory_alloc(50);

	printf("==>> ALOCANDO UM ESPAÇO DE 50 BYTES:\n");
	printf("\tLOCAL: %s\n", s_pnt-9 == initial_brk ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt-8)) == 50 ? CORRETO : INCORRETO);
	memory_free(s_pnt);
		
	printf("==>> DESALOCANDO UM ESPAÇO DE 50 BYTES:\n");
	printf("\tIND. DE USO: %s\n", *((char*) (s_pnt-9)) == 0 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (s_pnt-8)) == 50 ? CORRETO : INCORRETO);
	f_pnt = memory_alloc(100);

	printf("==>> ALOCANDO UM ESPAÇO DE 100 BYTES:\n");
	printf("\tLOCAL: %s\n", f_pnt-9 == s_pnt + 50 ? CORRETO : INCORRETO);
	printf("\tIND. DE USO: %s\n", *((char*) (f_pnt-9)) == 1 ? CORRETO : INCORRETO);
	printf("\tTAMANHO: %s\n", *((long long*) (f_pnt-8)) == 100 ? CORRETO : INCORRETO);
	memory_free(s_pnt);
	printf("==>> DESALOCANDO UM PONTEIRO JA DESALOCADO:\n");
	printf("\tRETORNO MEMORY_FREE(): %s\n", (memory_free(s_pnt) == -1)? CORRETO : INCORRETO);

	return 0;
}