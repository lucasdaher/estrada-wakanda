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

  if (T1)
  {
    printf("Comprimento total da estrada: %d\n", T1->T);
    if (T1->T == 10)
    {
      Soma++;
    }
    else
    {
      printf("Comprimento da estrada incorreto!\n");
    }
    NumTeste++;

    printf("Numero de cidades: %d\n", T1->N);
    if (T1->N == 2)
    {
      Soma++;
    }
    else
    {
      printf("Numero de cidades incorreto!\n");
    }
    NumTeste++;
  }
  else
  {
    printf("Estrutura da estrada nao inicializada corretamente!\n");
  }

  printf("Menor vizinhanca calculada: %.2f\n", D1);
  if (D1 == 3.5)
  {
    Soma++;
  }
  else
  {
    printf("A menor vizinhanca esta incorreta.\n");
  }
  NumTeste++;

  if (C1)
  {
    printf("Cidade com menor vizinhanca: %s\n", C1);
    if (strcmp(C1, "Birnin Zana") == 0)
    {
      Soma++;
    }
    else
    {
      printf("Cidade com menor vizinhanca incorreta!\n");
    }
    NumTeste++;
  }
  else
  {
    printf("Nome da cidade com menor vizinhanca nao inicializado corretamente!\n");
  }

  fprintf(Resposta, "\n\nATENCAO: Voce acertou %d de %d itens. Logo, em 2.00 pontos, sua nota foi %.2f.\n", Soma, NumTeste, 2.0 * (float)Soma / (float)NumTeste);

  fclose(Resposta);
  free(C1);
  if (T1)
  {
    free(T1->C);
    free(T1);
  }

  return 0;
}
