#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#define MASTER 0
double calcu(int i, long long N);
int main(int argc, char **argv) {
  int rank, size, rc;
  long long numParts;
  double result=0;
  double pisum, pi;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  
  //printf("[-]Rank id : %d , Processes size: %d", rank, size);

//   int N = (int)argv[1]; will crash
  numParts = atoll(argv[1]);
  //printf("\n[-]Number: %d\n", numParts);


  if(numParts <= 10000000000 && 1<= numParts){
     for(int i=rank;i<numParts;i+=size){
 	  result += calcu(i, numParts);
     }	
   //  printf("[-]Result: %lf",result);
     
  }else{
	exit(-1);
  }
  rc = MPI_Reduce(&result,&pi ,1,MPI_DOUBLE,MPI_SUM,MASTER,MPI_COMM_WORLD);
  //printf("\n[-]Return Code: %d , %.12lf\n",rc, pi);
  if(rank==MASTER){
 printf("%.12lf", pi);
  }
 // double width = radius / (double)rectangles;
 // for(int i=0;i<(argv[1]-1);i++){
 //	width * sqrt(1-(pow((width*(x*x)), 2)));
 // }
 // if(rank==MASTER){
 //	pi = pisum/size;
 //	printf("%f",pi);
 // }
  MPI_Finalize();
  
  return 0;
}
double calcu(int x,long long N){
	double pi = 4*(((double)1/N) * sqrt((double)1-pow((double)x/N,2)));
	return pi;
}
