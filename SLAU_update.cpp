//HOWTO solve system of linear equations
//ax=b

#include <iostream>
#include <stdio.h>
#include <process.h>

using namespace std;




float **a, *b, *x;
int N;
char filename[256];
FILE* InFile=NULL;

void count_num_lines()
{
   //count number of lines in input file - number of equations
   int nelf=0;       //non empty line flag
   do{
       nelf = 0;
       while(fgetc(InFile)!='\n' && !feof(InFile)) nelf=1;
       if(nelf) N++;
   }while(!feof(InFile));
}

void freematrix()
{
   //free memory for matrixes
   int i;
   for(i=0; i<N; i++){
       delete [] a[i];
   }
   delete [] a;
   delete [] b;
   delete [] x;
}

void allocmatrix()
{
   //allocate memory for matrixes
   int i,j;
   x = new float[N];
   b = new float[N];
   a = new float*[N];
   if(x==NULL || b==NULL || a==NULL){
       printf("\nNot enough memory to allocate for %d equations.\n", N);
       exit(-1);
   }
   for(i=0; i<N; i++){
       a[i] = new float[N];
       if(a[i]==NULL){
	   printf("\nNot enough memory to allocate for %d equations.\n", N);
       }
   }
   for(i=0; i<N; i++){
       for(j=0; j<N; j++){
	   a[i][j]=0;
       }
       b[i]=0;
       x[i]=0;
   }
}

void readmatrix()
{
   int i=0,j=0;
   //read matrixes a and b from input file
   for(i=0; i<N; i++){
       for(j=0; j<N; j++){
	   fscanf(InFile, "%f", &a[i][j]);
       }
       fscanf(InFile, "%f", &b[i]);
   }
}


void display()
    {cout<<"Matrix:\n";
        for(int i=0;i<N;i++)
        {
            cout<<"\n";
            for(int j=0;j<N+1;j++)
            {
            	
                if(j==N)
                    cout<<" ";
                    cout<<a[i][j]<<"\t";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }


void printresult(){
   int i=0;
   printf("\n");
   printf("Result\n");
   for(i=0; i<N; i++){
   		cout<<scientific<<i<<" = "<<x[i]<<endl;
   }
}


void cls()
{
   for(int i=0; i<25; i++) printf("\n");
}


int main()
{ 
   int i=0,j=0, k=0;
   cls();
   do{
       printf("\nInput filename: ");
       scanf("%s", filename);
       InFile = fopen(filename, "rt");
   }while(InFile==NULL);
   count_num_lines();
   allocmatrix();
   rewind(InFile);
   //read data from file
   readmatrix();
   //check if there are 0 on main diagonal and exchange rows in that case
   //diagonal();
   fclose(InFile);
   display();
   //process rows
   for(k=0; k<N; k++){
       for(i=k+1; i<N; i++){
	   if(a[k][k]==0){
	       printf("\nSolution does not exist.\n");
	       return 0;
	   }
	   float M = a[i][k] / a[k][k];
	   for(j=k; j<N; j++){
	       a[i][j] -= M * a[k][j];
	   }
	   b[i] -= M*b[k];
       }
   }
   display();
   for(i=N-1; i>=0; i--){
       float s = 0;
       for(j = i; j<N; j++){
	   s = s+a[i][j]*x[j];
       }
       x[i] = (b[i] - s) / a[i][i];
   }

   InFile = fopen(filename, "rt");
   readmatrix();
   fclose(InFile);
   display();
   //testsolve();
   printresult();
   freematrix();
}
