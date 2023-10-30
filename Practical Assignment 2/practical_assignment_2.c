///*** Serkan Ertas ***///
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_a_dice(){//to roll a dice
    return rand() %6 + 1;
}

int play_computer(int turnCount, int totalScore) {  //it takes the turnCount to print which round it is, and totalScore to update it
    int dice1=1, dice2=1, dice3=1, dice4=1, dice5=1, noScore,myScore, i = 5;
    printf("Round %d -- My Turn\n", turnCount);
    printf("===========================================================\n");

    while (i) {// i=5 initially, when a dice is equal to 2 or 5, it decreases by 1, when i=0, it is Drop Dead
        myScore=0;
        noScore=0;
        printf("I got ->");

        /*dice variables are 1 initially, it enters the if and take a value from roll_a_dice function
         * if it is 2 or 5, the dice variable becomes 0 and noScore becomes 1 for this turn
         * and in the other turn it becomes -1 if it was 0 in the previous turn */
        if(dice1>0){
            dice1 = roll_a_dice();
            printf(" [Dice 1]: %d",dice1);
            if(dice1==2 || dice1==5){
                dice1=0;
                noScore=1;
                i--;}
        }else{dice1=-1;}

        if(dice2>0){
            dice2 = roll_a_dice();
            printf(" [Dice 2]: %d",dice2);
            if(dice2==2 || dice2==5){
                dice2=0;
                noScore=1;
                i--;}
        }else{dice2=-1;}

        if(dice3>0){
            dice3 = roll_a_dice();
            printf(" [Dice 3]: %d",dice3);
            if(dice3==2 || dice3==5){
                dice3=0;
                noScore=1;
                i--;}
        }else{dice3=-1;}

        if(dice4>0){
            dice4 = roll_a_dice();
            printf(" [Dice 4]: %d",dice4);
            if(dice4==2 || dice4==5){
                dice4=0;
                noScore=1;
                i--;}
        }else{dice4=-1;}

        if(dice5>0){
            dice5 = roll_a_dice();
            printf(" [Dice 5]: %d",dice5);
            if(dice5==2 || dice5==5){
                dice5=0;
                noScore=1;
                i--;}
        }else{dice5=-1;}
        printf("\n");

        if(!noScore){//if noScore is 0, it will calculate the score by adding each dice variable that is not excluded
            if (dice1 != -1) { myScore += dice1; }
            if (dice2 != -1) { myScore += dice2; }
            if (dice3 != -1) { myScore += dice3; }
            if (dice4 != -1) { myScore += dice4; }
            if (dice5 != -1) { myScore += dice5; }
        }
        totalScore+=myScore;
        if(i!=0){printf("My score: %d Total score: %d\n",myScore,totalScore);}

        if(noScore && (i)){//prints which dices are excluded each turn. when it is drop dead, i=0 so it'll not print "are excluded"
            if(dice1==0){ printf("Dice 1 ");}
            if(dice2==0){ printf("Dice 2 ");}
            if(dice3==0){ printf("Dice 3 ");}
            if(dice4==0){ printf("Dice 4 ");}
            if(dice5==0){ printf("Dice 5 ");}
            printf("are excluded!\n");
        }
        printf("\n");
    }
    printf("Drop Dead!\n");
    printf("My score: %d Total score: %d\n\n\n",myScore,totalScore);
    return totalScore;
}

int play_user(int turnCount, int totalScore){
    int dice1=1, dice2=1, dice3=1, dice4=1, dice5=1, noScore,userScore, i = 5,rollTextControl=0;
    printf("Round %d -- Your Turn\n", turnCount);
    printf("===========================================================\n");

    while (i) {// i=5 initially, when a dice is equal to 2 or 5, it decreases by 1, when i=0, it is Drop Dead
        userScore=0;
        noScore=0;

        //when its the first turn, it enters the else part and make rollTextControl=1
        // in the other turns it always enters the if part
        if(rollTextControl!=0){
            printf("I rolled and you got\n");
        }else{
            printf("Are you ready to play!\nI rolled them for you and you got\n");
            rollTextControl=1;}

        printf("->");

        /*dice variables are 1 initially, it enters the if and take a value from roll_a_dice function
         * if it is 2 or 5, the dice variable becomes 0 and noScore becomes 1 for this turn
         * and in the other turn it becomes -1 if it was 0 in the previous turn */
        if(dice1>0){
            dice1 = roll_a_dice();
            printf(" [Dice 1]: %d",dice1);
            if(dice1==2 || dice1==5){
                dice1=0;
                noScore=1;
                i--;}
        }else{dice1=-1;}

        if(dice2>0){
            dice2 = roll_a_dice();
            printf(" [Dice 2]: %d",dice2);
            if(dice2==2 || dice2==5){
                dice2=0;
                noScore=1;
                i--;}
        }else{dice2=-1;}

        if(dice3>0){
            dice3 = roll_a_dice();
            printf(" [Dice 3]: %d",dice3);
            if(dice3==2 || dice3==5){
                dice3=0;
                noScore=1;
                i--;}
        }else{dice3=-1;}

        if(dice4>0){
            dice4 = roll_a_dice();
            printf(" [Dice 4]: %d",dice4);
            if(dice4==2 || dice4==5){
                dice4=0;
                noScore=1;
                i--;}
        }else{dice4=-1;}

        if(dice5>0){
            dice5 = roll_a_dice();
            printf(" [Dice 5]: %d",dice5);
            if(dice5==2 || dice5==5){
                dice5=0;
                noScore=1;
                i--;}
        }else{dice5=-1;}
        printf("\n");

        if(!noScore) {//if noScore is 0, it will calculate the score by adding each dice variable that is not excluded
            if (dice1 != -1) { userScore += dice1; }
            if (dice2 != -1) { userScore += dice2; }
            if (dice3 != -1) { userScore += dice3; }
            if (dice4 != -1) { userScore += dice4; }
            if (dice5 != -1) { userScore += dice5; }
        }
        totalScore+=userScore;
        if(i!=0){printf("Your score: %d Total score: %d\n", userScore, totalScore);}

        if(noScore && (i!=0)){//prints which dices are excluded each turn. when it is drop dead, i=0 so it'll not print "are excluded"
            if(dice1==0){ printf("Dice 1 ");}
            if(dice2==0){ printf("Dice 2 ");}
            if(dice3==0){ printf("Dice 3 ");}
            if(dice4==0){ printf("Dice 4 ");}
            if(dice5==0){ printf("Dice 5 ");}
            printf("are excluded!\n");
        }
        printf("\n");
    }
    printf("Drop Dead!\n");
    printf("Your score: %d Total score: %d\n\n\n", userScore, totalScore);
    return totalScore;
}

void scoresheet(int turnCount, int myScore, int yourScore){//prints the scoresheet
    printf("Our scoresheet after round %d:\n"
           "=============================\n"
           "My score    Your score\n"
           "%d%11.d\n\n",turnCount,myScore,yourScore);
}

int main(){
    int roundNum, turnCount=0, diceComp, diceUser, myScore=0, yourScore=0;
    srand(time(NULL));

    printf("Welcome to the Drop Dead game.\n"
           "Let's get started!\n\n"
           "How many rounds would you like to play?");
    scanf("%d",&roundNum);
    printf("\n");

    do{//iterates until the dices are different from each other
        diceComp=roll_a_dice();
        diceUser=roll_a_dice();
    }while(diceComp==diceUser);

    printf("I have rolled the dice and got %d!\n",diceComp);
    printf("I have rolled the dice for you and you got %d!\n\n",diceUser);

    if (diceComp>diceUser){//the computer rolled and got higher number than the user
        while(turnCount != roundNum){
            turnCount++;
            myScore = play_computer(turnCount,myScore);
            yourScore = play_user(turnCount,yourScore);
            scoresheet(turnCount,myScore,yourScore);
        }
    }
    else{//the user rolled and got higher number than the computer
        while(turnCount != roundNum){
            turnCount++;
            yourScore = play_user(turnCount,yourScore);
            myScore = play_computer(turnCount,myScore);
            scoresheet(turnCount,myScore,yourScore);
        }
    }

    if(myScore>yourScore){ printf("I AM THE WINNER!");}
    else{ printf("YOU ARE THE WINNER!");}
    return 0;
}
