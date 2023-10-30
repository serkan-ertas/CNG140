///*** Serkan Ertas ***///
////answers for paper is at the bottom

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3

int number_patients(int patients, int recovered, int admitted, int month){
    if (month==0){
        return patients;
    }
    else{
        return number_patients(patients,recovered,admitted,month-1)+admitted-recovered;
    }
}

void hospital_ranking(int beginning,int ending){
    if((ending-beginning) <= (beginning*0.3)){
        printf("blue");
    }
    else if((ending-beginning) <= (beginning*0.6)){
        printf("yellow");
    }
    else if ((ending-beginning)>(beginning*0.6)){
        printf("red");
    }
}

int main() {
    srand(time(NULL));
    int arr[N],i,months,admitted,recovered;
    char yes_no='Y';

    do{

    ///*** taking an array of 3 elements whose elements are not <1 and >50 ***///
    for(i=0;i<N;i++){
        printf("Enter the patients for hospital[%d]:",i+1);
        scanf("%d",&arr[i]);
        if (arr[i]<1 || arr[i]>50){
            printf("it is not allowed!\n");
            i--;
            fflush(stdin);
        }
    }

    ///*** month input ***///
    printf("How many months would you like to use in the calculation?");
    scanf("%d",&months);

    do{ ///*** randomly generating numbers ***///
        admitted= rand()%10+1;
        recovered= rand()%10+1;
    }while(admitted<=recovered);
    printf("Number of admitted patients per month: %d\n",admitted);
    printf("Number of recovered patients per month: %d\n",recovered);

    ///*** the last part ***///
    printf("After 5 months, hospitals are:");
    for(i=1;i<4;i++){
        printf("\nHospital[%d]:",i);
        hospital_ranking(arr[i-1], number_patients(arr[i-1],recovered,admitted,months));
    }

    printf("\n\nWould you like to try again?");
    fflush(stdin);
    scanf("%c",&yes_no);

    }while(yes_no=='Y');
    printf("Byee...");
    return 0;
}


/*
 * Those N elements will be stored consecutively, so the answer is YES
 *
 * For example N is a symbolic constant (line7) we can define it with #define N 3
 * and whenever the compiler does see N, it'll replace it with 3
 *
 *The datatype of the random number we generated is INTEGER
 *
 * Recursive functions calls itself again and again until the base condition is satisfied;
 * however, iterative functions have a loop (for,while,do-while) inside of it
 *
 * This function returns void because there is no need to return anything since we can just print the color of the hospitals.
 */
