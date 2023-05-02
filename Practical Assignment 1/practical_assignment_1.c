///*** kuroschin ***///
#include <stdio.h>
#define LF 10

int main()
{
    int option,baseOption,count,D,Bout,done,finish;
    char A,B,Bin,num16,lfCheck;

    printf("Welcome to Full Subtractor!\n   "
           "(1) Compute and Display the outputs\n   "
           "(2) Quit\n"
           "You choose:");
    scanf("%d",&option);
    printf("You have chosen option %d\n",option);

    while(option==1) {//program starts here if the user enter 1
        printf("\nWhich base will you use to enter input (base 2 or base 16)?");
        scanf(" %d", &baseOption);
        fflush(stdin);
        finish=1;
        while (finish) {// after selecting base, they both are in the loop
                        // because the program asks again and again
                        // until the user enters a valid num in base2/16

            if (baseOption == 2) {    /// BASE-2 OPTION SELECTED
                printf("Please enter your input:");
                count = 0;
                lfCheck = 0;
                done = 1;
                while (done) {
                    scanf("%c", &lfCheck);
                    if (lfCheck == 48 || lfCheck == 49)/// 0-1 CHECK
                    {
                        lfCheck -= 48;
                        count++;

                        if (count == 1) {
                            A = lfCheck;
                        } else if (count == 2) {
                            B = lfCheck;
                        } else if (count == 3) {
                            Bin = lfCheck;
                        }
                    }
                    else if (lfCheck != LF) ///if the num is not 0, 1 or 10, it is invalid
                    {                       ///the loop with "done" is broken here and,
                                            ///since count=-1, it wont execute any if at between the lines 59-67
                        printf("Invalid number in base 2! Please try again!\n");
                        fflush(stdin);
                        count = -1;
                        done = 0;
                    }
                    else { ///here executes if lfCheck=10
                        done = 0;
                    }
                }

                if (count == 3) { ///entered a valid num for our calculation
                    finish = 0;   ///stops while(finish) loop and goes to calculation
                }
                else if (count > 3) {
                    printf("You entered more than 3 bits! Please try again!\n");
                }
                else if (count > -1) {
                    printf("You entered less than 3 bits! Please try again!\n");
                }
                ///*** if the wrong number is entered, it will go to while(finish) and
                ///*** since baseOption is the same, the program will ask entering a num again
            }
            else if (baseOption==16) {    ///BASE-16 OPTION SELECTED
                printf("Please enter your input:");
                scanf("%c", &num16);
                fflush(stdin);

                if (num16 > 47 && num16 < 56) {///INPUTTED CORRECT NUMBER IN BASE-16
                    count=0;
                    num16 -= 48;
                    A = 0;      ///if num16 is 0, it wont enter the below loop
                    B = 0;      ///
                    Bin = 0;    ///so A,B,Bin need to be defined before
                    while(num16>0){ ///convert num16 to binary
                        count++;
                        if (count==1){
                            Bin = num16 % 2;
                        }
                        else if (count==2){
                            B = num16 % 2;
                        }
                        else {
                            A = num16 % 2;
                        }
                        num16 /= 2;
                    }
                    finish = 0; ///user entered correct input so it breaks while(finish)
                }
                else if ((num16 > 64 && num16 < 71) || (num16 == 56) || (num16 == 57)) {///entered A,B,C,D,E,F,8,9
                    printf("Not possible to convert it to 3-digit binary number. Please try again!\n");
                }
                else {///invalid num in base-16
                    printf("Invalid number in base 16! Please try again!\n");
                }
            }
        }

        ///correct input is entered and finish=0 now. here is the calculation:
        D = (((A == B) ? (0) : (1)) == Bin) ? (0) : (1);
        Bout = (((!A) && Bin) || ((!A) && B) || (B && Bin));
        printf("D is : %d\nBout is : %d\n\n", D, Bout);


        ///here is the start of our program
        printf("Welcome to Full Subtractor!\n   "
               "(1) Compute and Display the outputs\n   "
               "(2) Quit\n"
               "You choose:");
        fflush(stdin);
        scanf("%d", &option);
        printf("You have chosen option %d\n", option);
    }
    printf("BYEE!!");
    return 0;
}

///***011100110110010101110010011010110110000101101110001000000110010101110010011101000110000101110011***///