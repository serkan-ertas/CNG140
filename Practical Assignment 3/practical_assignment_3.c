///*** Serkan Ertas ***///

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int boardSize();
int initializeBoard(char**, int);
int getCoordinates(int,int,int,int,int,int**);
int checkCharacters(int,int,int,int,int,char**);
void displayBoard(int,int,int,int,int,int,char**,int**);
int checkAllOpened(int**,int);

int boardSize(){ //this function gets the size correctly
    int x,loopControl=1;

    do{
        printf("Please specify the board size:");
        scanf("%d",&x);
        fflush(stdin);
        if(x<2 || x>30){
            printf("Board size can only be between 2-30!\n");
            x=1;
        }else if(!(x%2)){ loopControl=0;
        }else{ printf("Board size can only be a multiple of two!\n");}
    }while(loopControl);
    printf("\n");
    return x;
}

int initializeBoard(char** arr,int n){ //this func does initialize a board
    int i,j,checkArr[n], selector;

    for(i=0;i<n;i++){ //this is for if a character is used n times or not
        checkArr[i]=n;
    }
    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            selector = rand()%n;
            while(checkArr[selector] == 0) //if the char is used n times, checkArr[selector] will be 0 and this will loop until finding a character not used n times
                selector = rand()%n;
            checkArr[selector]--;
            arr[i][j] = 33 + selector;
        }
    }
}

int getCoordinates(int row1,int row2,int column1,int column2,int n,int** checkArr){ //checks if the input is correct or not
    if(row1==row2 && column1==column2) { //two coordinates are same
        printf("Sorry, two door coordinates are same!\n");
        return 0;
    }
    else if(row1<0 || row1>=n || row2<0 || row2>=n || column1<0 || column1>=n || column2<0 || column2>=n){ //wrong coordinates
        printf("Sorry, wrong coordinates!\n");
        return 0;
    }
    if(checkArr[row1][column1] == 1 || checkArr[row2][column2] == 1){ //checks if its already opened
        if(checkArr[row1][column1] == 1){ printf("(%d,%d) already opened!\n",row1+1,column1+1);}
        if(checkArr[row2][column2] == 1){ printf("(%d,%d) already opened!\n",row2+1,column2+1);}
        return 0;
    }
    return 1;
}

int checkCharacters(int row1, int row2, int column1, int column2, int n, char** arr){ //checks if the 2 chars are the same or not
    if(arr[row1][column1] == arr[row2][column2]){
        return 1;
    }
    return 0;
}

void displayBoard(int openordisplay,int row1, int row2, int column1, int column2, int n, char** arr, int** checkArr){ //displays the board
    int i,j;
    printf("   ");
    for(i=0;i<n;i++){ //upper numbers of the board until n (( for example==> 1 2 3 4 ... n ))
        printf("%2.d ",i+1);
    }
    printf("\n");

    if(openordisplay) { //when a user enters an coordinates, their coordinates should be displayed regardless of whether they're the same or not
        checkArr[row1][column1] = 1; //when a player's turn starts, the variable "openordisplay" is 0 and nothing is changed
        checkArr[row2][column2] = 1;
    }

    for (i=0;i<n;i++){ //this part prints the board
        printf("%2.d ",i+1);
        for (j=0;j<n;j++){
            if(checkArr[i][j]==1){ //if its 1, it means it is opened
                printf(" %c ",arr[i][j]);
            }else{ printf(" @ ");} //prints @ if its closed

            if(j==n-1){ printf("\n");}
        }
    }
    if(openordisplay){ //after displaying, making coordinates closed again
        checkArr[row1][column1] = 0;
        checkArr[row2][column2] = 0;
    }
    printf("\n");
}

int checkAllOpened(int** checkArr,int n){ //if all chars are opened, the game has to end. this func checks it
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if (checkArr[i][j]==0) return 1; //if any one of the chars is not opened, it'll return 1, it means the game is not ended yet
        }
    }
    return 0; //the game is ended
}

int main() {
    srand(time(NULL));
    char** arr;
    int** checkArr;
    int n,i,j,score1,score2,player1or2,row1,row2,col1,col2;
    char loopControl;

    do { //main loop
        printf("Welcome to MemoME!\n");
        n = boardSize(); //gets the board size
        player1or2=1;
        score1=0;
        score2=0;

        arr = (int **) malloc(sizeof(int *) * n); //creates a dynamic array for the main board
        checkArr = (int **) malloc(sizeof(int *) * n); //creates a board that stores 0s and 1s
        for (int i = 0; i < n; i++) {
            arr[i] = (int *) malloc(sizeof(int) * n);
            checkArr[i] = (int *) malloc(sizeof(int) * n);
        }

        for (i = 0; i < n; i++) { //0 = closed ,,, 1 = opened
            for (j = 0; j < n; j++) {
                checkArr[i][j] = 0; //firstly, all of the chars are closed
            }
        }

        initializeBoard(arr,n); //creates the board
        printf("A Board is created for you with the size of %dx%d!\n\n",n,n);

        do{
            printf("--Player %d Turn:--\n", player1or2);
            displayBoard(0,0,0,0,0,n,arr,checkArr);//displays the board when the turn starts for a player
            do{
                printf("Enter the coordinates of doors to open:");
                scanf("(%d,%d) (%d,%d)",&row1,&col1,&row2,&col2);
                fflush(stdin);
                row1--;//all the coordinates are decremented by 1
                row2--;
                col1--;
                col2--;
            }while(!getCoordinates(row1,row2,col1,col2,n,checkArr)); //loops until the correct inputs are entered

            displayBoard(1,row1,row2,col1,col2,n,arr,checkArr); //displays the board, including the coordinates the player entered

            if(player1or2==1){//for player 1
                if(checkCharacters(row1,row2,col1,col2,n,arr)){ //checks if the chars are the same
                    score1+=2;
                    printf("Lucky you! Your Score: 2, total score:%d\n\n",score1);
                    checkArr[row1][col1]=1; //making those coordinates opened
                    checkArr[row2][col2]=1;
                }else{ //the chars are not the same
                    score1--;
                    printf("Unlucky! Your Score: -1, total score:%d\n\n",score1);
                }
                player1or2=2; //after player 1's turn, its now player 2's turn
            }else{//for player 2
                if(checkCharacters(row1,row2,col1,col2,n,arr)){ //checks if the chars are the same
                    score2+=2;
                    printf("Lucky you! Your Score: 2, total score:%d\n\n",score2);
                    checkArr[row1][col1]=1; //making those coordinates opened
                    checkArr[row2][col2]=1;
                }else{ //the chars are not the same
                    score2--;
                    printf("Unlucky! Your Score: -1, total score:%d\n\n",score2);
                }
                player1or2=1; //after player 2's turn, its now player 1's turn
            }

        } while (checkAllOpened(checkArr,n)); //if all coordinates are opened, checkAllOpened returns 0 and it stops

        if(score1>score2) { printf("\n**Winner is Player 1!**\n\n");} //winner is player 1
        else if(score2>score1){ printf("\n**Winner is Player 2!**\n\n");} //winner is player 2
        else{ printf("\n**It is a draw!**\n\n");} //the scores are the same at the end of the game

        printf("Would you like to play again (Y/N)?");
        scanf("%c",&loopControl);
        fflush(stdin);
    }while(loopControl=='Y' || loopControl=='y');

    printf("\nByee!");
    return 0;
}