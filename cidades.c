#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL)
  {
    printf("Erro: não foi possível abrir o arquivo %s\n", nomeArquivo);
    return NULL;
  }

  Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
  if (estrada == NULL)
  {
    printf("Erro: falha na alocação de memória para Estrada\n");
    fclose(arquivo);
    return NULL;
  }

  if (fscanf(arquivo, "%d", &(estrada->T)) != 1)
  {
    printf("Erro: falha ao ler o comprimento da estrada\n");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }
  if (estrada->T < 3 || estrada->T > 1000000)
  {
    printf("Erro: comprimento da estrada fora dos limites permitidos (3 <= T <= 106)\n");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  if (fscanf(arquivo, "%d", &(estrada->N)) != 1)
  {
    printf("Erro: falha ao ler o número de cidades\n");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }
  if (estrada->N < 2 || estrada->N > 10000)
  {
    printf("Erro: numero de cidades fora dos limites permitidos (2 <= N <= 104)\n");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
  if (estrada->C == NULL)
  {
    printf("Erro: falha na alocação de memoria para as cidades\n");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  for (int i = 0; i < estrada->N; i++)
  {
    if (fscanf(arquivo, "%d %255s", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2)
    {
      printf("Erro: falha ao ler os dados da cidade %d\n", i + 1);
      free(estrada->C);
      free(estrada);
      fclose(arquivo);
      return NULL;
    }
    if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T)
    {
      printf("Erro: posicao da cidade %d fora dos limites permitidos (0 < Xi < T)\n", i + 1);
      free(estrada->C);
      free(estrada);
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
  {
    printf("Erro: nao foi possivel inicializar a estrada para calcular a menor vizinhanca\n");
    return -1;
  }

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
  {
    printf("Erro: nao foi possivel inicializar a estrada para determinar a cidade com menor vizinhanca\n");
    return NULL;
  }

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
  if (cidade == NULL)
  {
    printf("Erro: falha na alocação de memoria para o nome da cidade\n");
    free(estrada->C);
    free(estrada);
    return NULL;
  }

  strcpy(cidade, estrada->C[index].Nome);
  free(estrada->C);
  free(estrada);
  return cidade;
}