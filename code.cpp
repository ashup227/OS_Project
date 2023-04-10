#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
int nRes,nproc;
int *resources;
int **allocated;
int **maxreq;
int **need;
int *safeSeq;

int main(int argc, char** argv) {
	
 printf("\nNumber of Processes? ");
	scanf("%d", &nproc);

 printf("\nNumber of Resources? ");
	scanf("%d", &nRes);

 resources = (int *)malloc(nRes * sizeof(*resources));
 printf("\nCurrently Available resources (R1 R2 ...)? ");
 for(int i=0; i<nRes; i++)
 scanf("%d", &resources[i]);

 allocated = (int **)malloc(nproc * sizeof(*allocated));
 for(int i=0; i<nproc; i++)
 allocated[i] = (int *)malloc(nRes * sizeof(**allocated));

 maxreq = (int **)malloc(nproc * sizeof(*maxreq));
 for(int i=0; i<nproc; i++)
 maxreq[i] = (int *)malloc(nRes * sizeof(**maxreq));

 printf("\n");
 for(int i=0; i<nproc; i++) {
 printf("\nResource allocated to process %d (R1 R2 ...)? ", i+1);
 for(int j=0; j<nRes; j++)
 scanf("%d", &allocated[i][j]);
 }
 printf("\n");
 for(int i=0; i<nproc; i++) {
 printf("\nMaximum resource required by process %d (R1 R2 ...)? ", i+1);
 for(int j=0; j<nRes; j++)
 scanf("%d", &maxreq[i][j]);
 }
 printf("\n");

 need = (int **)malloc(nproc * sizeof(*need));
 for(int i=0; i<nproc; i++)
 need[i] = (int *)malloc(nRes * sizeof(**need));

 for(int i=0; i<nproc; i++)
 for(int j=0; j<nRes; j++)
 need[i][j] = maxreq[i][j] - allocated[i][j];

	safeSeq = (int *)malloc(nproc * sizeof(*safeSeq));

}

bool getSafeSeq() {
 int tempRes[nRes];
 for(int i=0; i<nRes; i++) tempRes[i] = resources[i];

 bool finished[nproc];
 for(int i=0; i<nproc; i++) finished[i] = false;
 int nfinished=0;
 while(nfinished < nproc) {
 bool safe = false;

 for(int i=0; i<nproc; i++) {
 if(!finished[i]) {
 bool possible = true;

 for(int j=0; j<nRes; j++)
 if(need[i][j] > tempRes[j]) {
 possible = false;
 break;
 }

 if(possible) {
 for(int j=0; j<nRes; j++)
 tempRes[j] += allocated[i][j];
 safeSeq[nfinished] = i;
 finished[i] = true;
 ++nfinished;
 safe = true;
 }
 }
 }

 if(!safe) {
 for(int k=0; k<nproc; k++) safeSeq[k] = -1;
 return false; 
 }
 }
 return true; 
}
