///*** Serkan Ertas ***///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct teamData{ //structure of teamData
    char teamName[20];
    int played;
    int point;
    char form[5];
};

void display_data(struct teamData *teamTable, int lineNum){ //displays the array of structures
    int i;
    printf("Team            Played  Points  Form\n");
    for(i=0; i<lineNum ; i++){ //displays each structure one by one
        printf("%s\t%d\t%d\t%s\n",teamTable[i].teamName,teamTable[i].played,teamTable[i].point,teamTable[i].form);
    }
    printf("\n");
}

struct teamData * load_data(char *filename, int *lineNum){//in general: opens the file, calculates the lineNum, dynamically creates the array of structures
    int i;
    char Line[100]; //it's for passing the first Line

    FILE *inFile;
    inFile = fopen(filename,"r");//trying to open the file in read mode
    while(inFile==NULL){ //filename does not exist, this part of code asks it again
        printf("Please enter file name again:");
        gets(filename);
        inFile = fopen(filename,"r");
    }

    while(fscanf(inFile,"%[^\n]\n",Line)!=EOF){ //calculating total rows in the file
        (*lineNum)++;
    }
    (*lineNum)--;//first line is not included
    rewind(inFile);

    struct teamData *temporaryTable = (struct teamData *) malloc(sizeof(struct teamData)*(*lineNum));//dynamically creating the array of structures
    if(temporaryTable == NULL){//memory allocation fail
        printf("Memory Allocation Is Failed!");
        exit(2584993);
    }

    fscanf(inFile,"%[^\n]\n",Line);//pass the first line
    for(i=0; fscanf(inFile,"%[^ ] %d %d %[^\n]\n",temporaryTable[i].teamName,&temporaryTable[i].played, &temporaryTable[i].point, temporaryTable[i].form)!=EOF ; i++){}
    // ^^^^^^^ initializes values for each structure, until its EOF
    printf("Your data is successfully processed and looks as follows:\n");
    display_data(temporaryTable,(*lineNum));

    return temporaryTable;
}

void process_data(struct teamData *teamTable, int lineNum, char * filename){//in general: calculate the avg, how many teams played 33/34 games, teams that have 3 consecutive wins, write those into a file
    FILE *outFile;
    outFile = fopen(filename,"w");//opens the file in writing mode

    char wwwTeams[lineNum][20];//array of teams that have 3 consecutive wins
    float avgPoints=0;
    int i, j, wwwCount=0, game33=0,game34=0;

    for(i=0; i<lineNum ; i++){//doing calculations for each structure in the array
        avgPoints += teamTable[i].point;//adding all the points, will be divided by the number of teams

        if(teamTable[i].played == 33){ game33++;}//33 or 34 games the team played
        else if(teamTable[i].played == 34){ game34++;}

        for(j=0; j<3 ; j++){//adds the team name to the array if the team has 3 consecutive wins
            if (teamTable[i].form[j] == 'W' && teamTable[i].form[j+1] == 'W' && teamTable[i].form[j+2] == 'W'){
                j=3;
                strcpy(wwwTeams[wwwCount], teamTable[i].teamName);
                wwwCount++;
            }
        }
    }
    avgPoints /= lineNum;

    //prints the statistics
    printf("Statistics are as follows:\nAverage points: %.1f\n%d teams played 34 games and %d teams played 33 games.\n",avgPoints,game34,game33);
    printf("These teams have three consecutive wins:\n");
    for(i = 0 ; i<wwwCount ; i++){
        puts(wwwTeams[i]);
    }

    //writes the calculation data into the file
    fprintf(outFile,"Statistics are as follows:\nAverage points: %.1f\n%d teams played 34 games and %d teams played 33 games.\n",avgPoints,game34,game33);
    fprintf(outFile, "These teams have three consecutive wins:\n");
    for(i = 0 ; i<wwwCount ; i++){
        fprintf(outFile,"%s\n",wwwTeams[i]);
    }

    printf("%s is also updated!\n",filename);
}

int main(int argc, char * argv[]) {
    if(argc<3){
        printf("Not enough arguments!");
        exit(2584993);
    }

    int lineNum=0;
    struct teamData *teamDataTable = load_data(argv[1],&lineNum);
    process_data(teamDataTable,lineNum,argv[2]);

    return 0;
}

/*  q1:
    q2: a) created the array and used malloc function(allocation, dynamically)
           lineNum is calculated in load_data function, its not assumed to be any number
        b) i would add a function for writing the calculations into the file, because "process" is not the appropriate name for updating a file
    q3: if two inputs are given, argc should be 3 (programName, firstInput, secondInput)
    q4:we can create the array of structures in main function and pass it as an argument to the load function
       however, if we do this, we should open the file in main, calculate lineNum in main, then create the array of structures
    q5:lineNum wont be changed so its passed by value, but the other two arguments, the array of structures and the filename are passed by reference
    q6:similarly, lineNum is passed by value, and the array of structures is passed by reference
*/