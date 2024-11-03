#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL)
  {
    perror("Nao foi possivel realizar a leitura do arquivo.");
    return NULL;
  }

  Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
  if (estrada == NULL)
  {
    perror("Nao foi possivel alocar a memoria para a estrada.");
    fclose(arquivo);
    return NULL;
  }

  if (fscanf(arquivo, "%d", &(estrada->T)) != 1)
  {
    perror("Falha ao ler o comprimento da estrada.");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  if (estrada->T < 3 || estrada->T > 1000000)
  {
    perror("Comprimento da estrada esta fora dos limites permitidos.");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  if (fscanf(arquivo, "%d", &(estrada->N)) != 1)
  {
    perror("Falha ao ler numero de cidades.");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  if (estrada->N < 2 || estrada->N > 10000)
  {
    perror("Numero de cidades esta fora dos limites permitidos.");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
  if (estrada->C == NULL)
  {
    perror("Falha na alocacao de memoria para as cidades.");
    free(estrada);
    fclose(arquivo);
    return NULL;
  }

  for (int i = 0; i < estrada->N; i++)
  {
    int posicao;
    char nome[256];
    if (fscanf(arquivo, "%d %[^\n]s", &posicao, nome) != 2)
    {
      printf("Falha ao ler os dados da cidade %d\n", i + 1);
      free(estrada->C);
      free(estrada);
      fclose(arquivo);
      return NULL;
    }
    if (posicao <= 0 || posicao >= estrada->T)
    {
      printf("Posicao da cidade %d fora dos limites permitidos.\n", i + 1);
      free(estrada->C);
      free(estrada);
      fclose(arquivo);
      return NULL;
    }

    estrada->C[i].Posicao = posicao;
    strncpy(estrada->C[i].Nome, nome, 255);
    estrada->C[i].Nome[255] = '\0';
  }
  fclose(arquivo);
  return estrada;
}

int compararCidades(const void *a, const void *b)
{
  Cidade *cidadeA = (Cidade *)a;
  Cidade *cidadeB = (Cidade *)b;
  return cidadeA->Posicao - cidadeB->Posicao;
}

double calcularMenorVizinhanca(const char *NomeArquivo)
{
  Estrada *estrada = getEstrada(NomeArquivo);
  if (!estrada)
    return -1;

  double menorVizinhanca = estrada->T;

  for (int i = 0; i < estrada->N - 1; i++)
  {
    int distanciaAtual = estrada->C[i + 1].Posicao - estrada->C[i].Posicao;
    double vizinhancaAtual = distanciaAtual / 2.0;

    if (vizinhancaAtual < menorVizinhanca)
    {
      menorVizinhanca = vizinhancaAtual;
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