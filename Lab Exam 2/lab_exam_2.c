///*** Serkan Ertas ***///

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void populateArray(int *array, int n);
void changes(int *array, int n);

int main() {
    srand(time(NULL));
    int *array;
    int n,i;

    printf("Enter the number of pen pressures:");
    scanf("%d",&n);

    array=(int *)malloc(sizeof(int)*n);

    populateArray(array,n);
    changes(array,n);

    return 0;
}

void populateArray(int *array, int n){
    int i;
    printf("Pen pressure values are: ");
    for (int i = 0; i < n; ++i) {
        array[i]=rand()%501; //assumed 0 and 500 are included
        printf("%d ",array[i]);
    }
    printf("\n");
}

void changes(int *array, int n){
    int i;
    printf("Pen pressure changes are: ");

    for (i = 0; i < n; ++i) {
        if(i==n-1){//if its the last element of our array
            if(!array[i]){// if it is 0, 0-0=0 then arr[i]=0
                array[i]=0;
            }else { //if its nonzero, it'll be 1
                array[i] = 1;
            }
        }
        else if(array[i]-array[i+1]){
            array[i]=1;
        }
        else{
            array[i]=0;
        }
        printf("%d",array[i]);
    }
    printf("\n");
}













