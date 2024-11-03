#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r+");
  if (arquivo == NULL)
  {
    perror("Nao foi possivel realizar a leitura do arquivo.\n");
    exit(EXIT_FAILURE);
  }

  // passou
  Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
  if (estrada == NULL)
  {
    perror("Nao foi possivel alocar a memoria para a estrada.\n");
    exit(EXIT_FAILURE);
  }

  // passou
  if (fscanf(arquivo, "%d", &(estrada->T)) != 1)
  {
    perror("Falha ao ler o comprimento da estrada.\n");
    free(estrada);
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  // passou
  if (estrada->T < 3 || estrada->T > 1000000)
  {
    perror("Comprimento da estrada esta fora dos limites permitidos.\n");
    free(estrada);
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  if (fscanf(arquivo, "%d", &(estrada->N)) != 1)
  {
    perror("Falha ao ler numero de cidades.\n");
    free(estrada);
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }
  if (estrada->N < 2 || estrada->N > 10000)
  {
    perror("Numero de cidades esta fora dos limites permitidos.\n");
    free(estrada);
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
  if (estrada->C == NULL)
  {
    perror("Falha na alocacao de memoria para as cidades.\n");
    free(estrada);
    fclose(arquivo);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < estrada->N; i++)
  {
    int posicao;
    char nome[256];
    if (fscanf(arquivo, "%d %255[^\n]", &posicao, nome) != 2)
    {
      printf("Falha ao ler os dados da cidade %d\n", i + 1);
      free(estrada->C);
      free(estrada);
      fclose(arquivo);
      exit(EXIT_FAILURE);
    }
    if (posicao <= 0 || posicao >= estrada->T)
    {
      perror("Posicao da cidade %d fora dos limites permitidos.\n");
      free(estrada->C);
      free(estrada);
      fclose(arquivo);
      exit(EXIT_FAILURE);
    }

    estrada->C[i].Posicao = posicao;
    strncpy(estrada->C[i].Nome, nome, 255);
    estrada->C[i].Nome[255] = '\0';
  }
  fclose(arquivo);
  return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo)
{
  Estrada *estrada = getEstrada(nomeArquivo);

  if (estrada == NULL)
  {
    perror("Nao foi possivel inicializar a estrada para calcular a menor vizinhanca.\n");
    exit(EXIT_FAILURE);
  }

  double menorVizinhanca = (double)(estrada->T);
  for (int i = 1; i < estrada->N; i++)
  {
    double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
    if (vizinhanca - menorVizinhanca)
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
    perror("Nao foi possivel inicializar a estrada para determinar a cidade com menor vizinhanca");
    exit(EXIT_FAILURE);
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
    perror("Falha na alocação de memoria para o nome da cidade.\n");
    free(estrada->C);
    free(estrada);
    exit(EXIT_FAILURE);
  }

  strcpy(cidade, estrada->C[index].Nome);
  free(estrada->C);
  free(estrada);
  return cidade;
}