///*** Serkan Ertas ***///

#include <stdio.h>

int main() {
    int numGentle,numStrong,numStorm,numWrong,numCentre=1;
    float windSpeed = 1.0;
    char yes_no='y';

    while(yes_no=='y' || yes_no == 'Y'){
        numGentle=0;
        numStrong=0;
        numStorm=0;
        numWrong=0;
        printf("Enter the measurements:\n");
        printf("Please enter a measurement:");
        scanf("%f",&windSpeed);
        fflush(stdin);
        while(windSpeed>=0){

            if(windSpeed>=0 && windSpeed<=19.0){
                numGentle++;
            }
            else if (windSpeed<=49.0){
                numStrong++;
            }
            else if (windSpeed<=117.0){
                numStorm++;
            }
            else if (windSpeed>117){
                numWrong++;
            }
            printf("Please enter a measurement:");
            scanf("%f",&windSpeed);
            fflush(stdin);
        }
        printf("Statistics for centre %d: %d-gentle breeze days, %d-strong breeze days, %d-stormy days and %d-wrong recordings.",numCentre,numGentle,numStrong,numStorm,numWrong);
        printf("\nDo you want to continue?");
        scanf("%c",&yes_no);
        fflush(stdin);
        numCentre++;
    }
    return 0;
}
