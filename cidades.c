#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// Funcao auxiliar para comparar cidades pela posicao
int compararPosicoes(const void *a, const void *b)
{
  Cidade *cidadeA = (Cidade *)a;
  Cidade *cidadeB = (Cidade *)b;
  return cidadeA->Posicao - cidadeB->Posicao;
}

// Implementacao da funcao getEstrada
Estrada *getEstrada(const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (!arquivo)
    return NULL;

  Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
  if (!estrada)
    return NULL;

  fscanf(arquivo, "%d", &(estrada->T));
  fscanf(arquivo, "%d", &(estrada->N));

  // Verificacao de restricoes
  if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000)
  {
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
  if (!estrada->C)
  {
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  for (int i = 0; i < estrada->N; i++)
  {
    fscanf(arquivo, "%d", &(estrada->C[i].Posicao));
    fgetc(arquivo); // Ignora o espaco apos a posicao
    fgets(estrada->C[i].Nome, 256, arquivo);
    char *newline = strchr(estrada->C[i].Nome, '\n');
    if (newline)
      *newline = '\0';
  }

  fclose(arquivo);

  // Ordenar cidades por posicao
  qsort(estrada->C, estrada->N, sizeof(Cidade), compararPosicoes);

  return estrada;
}

// Funcao para calcular a menor vizinhanca
double calcularMenorVizinhanca(const char *nomeArquivo)
{
  Estrada *estrada = getEstrada(nomeArquivo);
  if (!estrada)
    return -1;

  double menorVizinhanca = estrada->T;

  // Calcular vizinhancas entre as cidades
  for (int i = 1; i < estrada->N; i++)
  {
    double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
    if (vizinhanca < menorVizinhanca)
    {
      menorVizinhanca = vizinhanca;
    }
  }

  // Considerar vizinhancas das extremidades
  double vizinhancaEsquerda = estrada->C[0].Posicao;
  double vizinhancaDireita = estrada->T - estrada->C[estrada->N - 1].Posicao;
  if (vizinhancaEsquerda < menorVizinhanca)
  {
    menorVizinhanca = vizinhancaEsquerda;
  }
  if (vizinhancaDireita < menorVizinhanca)
  {
    menorVizinhanca = vizinhancaDireita;
  }

  free(estrada->C);
  free(estrada);

  return menorVizinhanca;
}

// Funcao para retornar a cidade com a menor vizinhanca
char *cidadeMenorVizinhanca(const char *nomeArquivo)
{
  Estrada *estrada = getEstrada(nomeArquivo);
  if (!estrada)
    return NULL;

  double menorVizinhanca = estrada->T;
  int indiceCidade = 0;

  for (int i = 1; i < estrada->N; i++)
  {
    double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
    if (vizinhanca < menorVizinhanca)
    {
      menorVizinhanca = vizinhanca;
      indiceCidade = i - 1;
    }
  }

  // Verificar vizinhanca da cidade mais a esquerda
  double vizinhancaEsquerda = estrada->C[0].Posicao;
  if (vizinhancaEsquerda < menorVizinhanca)
  {
    menorVizinhanca = vizinhancaEsquerda;
    indiceCidade = 0;
  }

  // Verificar vizinhanca da cidade mais a direita
  double vizinhancaDireita = estrada->T - estrada->C[estrada->N - 1].Posicao;
  if (vizinhancaDireita < menorVizinhanca)
  {
    menorVizinhanca = vizinhancaDireita;
    indiceCidade = estrada->N - 1;
  }

  char *resultado = (char *)malloc(256 * sizeof(char));
  if (resultado)
  {
    strcpy(resultado, estrada->C[indiceCidade].Nome);
  }

  free(estrada->C);
  free(estrada);

  return resultado;
}
