#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL)
    return NULL;

  Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
  if (estrada == NULL)
    return NULL;

  if (fscanf(arquivo, "%d", &(estrada->T)) != 1)
  {
    fclose(arquivo);
    return NULL;
  }
  if (estrada->T < 3 || estrada->T > 1000000)
  {
    fclose(arquivo);
    return NULL;
  }

  if (fscanf(arquivo, "%d", &(estrada->N)) != 1)
  {
    fclose(arquivo);
    return NULL;
  }
  if (estrada->N < 2 || estrada->N > 10000)
  {
    fclose(arquivo);
    return NULL;
  }

  estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
  if (estrada->C == NULL)
  {
    fclose(arquivo);
    return NULL;
  }

  for (int i = 0; i < estrada->N; i++)
  {
    if (fscanf(arquivo, "%d %s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2)
    {
      fclose(arquivo);
      return NULL;
    }
    if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T)
    {
      fclose(arquivo);
      return NULL;
    }
  }
  fclose(arquivo);
  return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo)
{
  Estrada *estrada = getEstrada(nomeArquivo);
  if (estrada == NULL)
    return -1;

  double menorVizinhanca = (double)(estrada->T);
  for (int i = 1; i < estrada->N; i++)
  {
    double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
    if (vizinhanca < menorVizinhanca)
    {
      menorVizinhanca = vizinhanca;
    }
  }

  free(estrada->C);
  free(estrada);
  return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo)
{
  Estrada *estrada = getEstrada(nomeArquivo);
  if (estrada == NULL)
    return NULL;

  int index = 0;
  double menorVizinhanca = (double)(estrada->T);
  for (int i = 1; i < estrada->N; i++)
  {
    double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
    if (vizinhanca < menorVizinhanca)
    {
      menorVizinhanca = vizinhanca;
      index = i;
    }
  }

  char *cidade = (char *)malloc((strlen(estrada->C[index].Nome) + 1) * sizeof(char));
  strcpy(cidade, estrada->C[index].Nome);

  free(estrada->C);
  free(estrada);
  return cidade;
}
