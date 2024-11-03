#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int main()
{
  int Soma = 0;
  int NumTeste = 0;

  FILE *Resposta = fopen("Resultado.txt", "w");

  Estrada *T1 = getEstrada("Teste01.txt");
  double D1 = calcularMenorVizinhanca("Teste01.txt");
  char *C1 = cidadeMenorVizinhanca("Teste01.txt");

  if (T1->T == 10)
    Soma++;

  NumTeste++;

  printf("T1->T == 10: O valor de T e %d\n", T1->T);

  if (T1->N == 2)
    Soma++;

  NumTeste++;

  printf("T1->N == 2: O valor de T e %d\n", T1->N);

  if (D1 == 3.5)
    Soma++;

  NumTeste++;

  printf("D == 3.5: O valor de D1 e %d\n", D1);

  if (strcmp(C1, "Birnin Zana") == 0)
    Soma++;

  NumTeste++;

  printf("Comparacao de C1 e Birnin Zana: O resultado foi: %d\n", strcmp(C1, "Birnin Zana"));

  fprintf(Resposta, "\n\nATENÇÃO: Você acertou %d de %d itens. Logo, em 2.00 pontos, sua nota foi %.2f.\n", Soma, NumTeste, 2.0 * (float)Soma / (float)NumTeste);
  printf("Avaliacao concluida.\n");
}