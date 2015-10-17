//  programa para calcular a distancia entre matrizes de vizinhanca
// bem como outras grandezas metricas: norma, cosseno


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	FILE *arq1, *arq2, *saida;
	int nVertices,nArquivos;
	int i,j,k,primeiro;
	char nomeArquivo1[50], nomeArquivo2[50];
	int **mat1, **mat2;
	int cont=0;
	float distancia, normaA, normaB, produtoInterno, coxeno;

	if (argc != 5)
	{
		printf("Uso: ./distancia <nVertices> <nArquivos> <primeiro>\n\n\nnVertices = dimensao da matriz\nnArquivos = numero de matrizes\nprimeiro = primeiro numero das matrizes\nnomeArquivo = nome do radical do arquivo\n\n");
		exit(0);
	}
	nVertices = atoi(argv[1]);nArquivos = atoi(argv[2]);primeiro = atoi(argv[3]);

	/*ALOCAR MEMORIA*/
	mat1 = (int **)malloc(sizeof(int*) * nVertices);
	mat2 = (int **)malloc(sizeof(int*) * nVertices);
	for (i=0;i<nVertices;i++)
	{
		mat1[i] = (int *)malloc(sizeof(int) * nVertices);
		mat2[i] = (int *)malloc(sizeof(int) * nVertices);
	}

	
	for (k=0;k<nArquivos-1;k++)
	{
		if (k<10)
		{
	 		sprintf(nomeArquivo1,"%s00%d.net.mat",argv[4],k+primeiro);
		}
		else
		{
	 		sprintf(nomeArquivo1,"%s0%d.net.mat",argv[4],k+primeiro);
		}
		arq1 = fopen(nomeArquivo1,"r");
		if (arq1 == NULL){printf("Arquivo %s inexistente!\n",nomeArquivo1);exit(1);}
		i =0;
		j =0;
		for (i=0;i<nVertices;i++)
		{
			for (j=0;j<nVertices;j++)
			{
				fscanf(arq1,"%d",&mat1[i][j]);
			}
		}
		fclose(arq1);
		//
		if (k==99)
		{
			sprintf(nomeArquivo2,"%s%d.net.mat",argv[4],k+primeiro+1);
		}
		else if (k<9)
		{
			sprintf(nomeArquivo2,"%s00%d.net.mat",argv[4],k+primeiro+1);
		}
		else
		{
			sprintf(nomeArquivo2,"%s0%d.net.mat",argv[4],k+primeiro+1);
		}
		arq2 = fopen(nomeArquivo2,"r");
		if (arq2 == NULL){printf("Arquivo %s inexistente!\n",nomeArquivo2);exit(1);}
		i =0;
		j =0;
		for (i=0;i<nVertices;i++)
		{
			for (j=0;j<nVertices;j++)
			{
				fscanf(arq2,"%d",&mat2[i][j]);
			}
		}
		fclose(arq2);

		distancia = 0;
		normaA=0;
		normaB=0;
		produtoInterno=0;
		
		
		for (i=0;i<nVertices;i++)
		{
			for (j=0;j<nVertices;j++)
			{
				distancia += (float)( (mat1[i][j] - mat2[i][j])*(mat1[i][j] - mat2[i][j]) );
		                normaA += (float)( (mat1[i][j])*(mat1[i][j]) ); 
                		normaB += (float)( (mat2[i][j])*(mat2[i][j]) ); 
		                produtoInterno += (float)( (mat1[i][j])*(mat2[i][j]) ); 
			}
		}

		distancia = distancia/(float)(nVertices*nVertices);
	
		if ( (sqrt(normaA) != 0) && (sqrt(normaB) != 0) )
		{
			coxeno = (float) (produtoInterno/(sqrt(normaA)*sqrt(normaB)));
		}
		else
		{
			coxeno = 0;
		}
		saida = fopen("quasiDistancia.dat","a");
		fseek(saida,0,SEEK_END);
		fprintf (saida,"%d %d %f\n",k+primeiro,k+primeiro+1,sqrt(distancia));
		fclose(saida);
	}
	
	/*LIBERAR MEMORIA*/
	for (i=0;i<nVertices;i++)
	{
		free(mat1[i]);
		free(mat2[i]);
	}
	free(mat1);
	free(mat2);


}

