///*** Serkan Ertas ***///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SignRecords{ //structure def
        char full_name[20];
        int x_int;
        int x_fin;
        int y_int;
        int y_fin;
        int width;
        int height;
};
void Display_SignaturesTable(struct SignRecords *, int);

struct SignRecords * Load_SignaturesTable(char *fileName, int *lineNum){//file name is argv[1], and sending lineNum's address
    char Line[100]; //to pass the first line of the file  (fullname;xint;xfin...)
    int i;

    FILE *inFile; //opening the file
    inFile = fopen(fileName,"r");
    while(inFile==NULL){ //if file does not exist, it iterates until a valid file name is given
        printf("This file does not exist. Please enter again:");
        gets(fileName);
        fflush(stdin);
        inFile = fopen(fileName,"r");
    }
    printf("The signature records file (%s) has been successfully opened!\n",fileName);

    (*lineNum)=0;
    while(fscanf(inFile,"%[^\n]\n",Line)!=EOF){ //calculating the line number
        (*lineNum)++;
    }
    (*lineNum)--; //decrementing by 1 because of the first line (that is not included in data)
    rewind(inFile);

    struct SignRecords *temporaryTable;//creating an array of structures
    temporaryTable= (struct SignRecords *) malloc(sizeof(struct SignRecords)* (*lineNum));

    fscanf(inFile,"%[^\n]\n",Line); //passing the first line
    for(i=0; fscanf(inFile, "%[^;];%d;%d;%d;%d;\n", temporaryTable[i].full_name, &temporaryTable[i].x_int, &temporaryTable[i].x_fin, &temporaryTable[i].y_int, &temporaryTable[i].y_fin) != EOF ; i++){
        temporaryTable[i].width = temporaryTable[i].x_fin - temporaryTable[i].x_int; //calculating width for each structure
        temporaryTable[i].height = temporaryTable[i].y_fin - temporaryTable[i].y_int; //calculating height for each structure
    }
    fclose(inFile);
    printf("The following records have been loaded:\n");
    return temporaryTable; //returning the array of structures
}

void Display_SignaturesTable(struct SignRecords *SignatureTable, int lineNum){//displaying the table by using the array of structures
    int i;
    printf("full_name               x_initial  x_final   y_initial  y_final   width   height\n");
    for (i = 0; i < lineNum ; i++) {//displaying each structure line by line
        printf("%s      \t%d  \t   %d      %d       %d      %d\t  %d\n",SignatureTable[i].full_name,SignatureTable[i].x_int,SignatureTable[i].x_fin,SignatureTable[i].y_int,SignatureTable[i].y_fin,SignatureTable[i].width,SignatureTable[i].height);
    }
}

int Search(struct SignRecords *SignaturesTable, int lineNum, char *inputName){//to search if the given name/surname is in the table or not
    int i,length;

    char *name = strtok(inputName, " ");//parsing the given array until " " (space)
    char *surname = strtok(NULL, " ");//this variable can be NULL if inputName does not contain any space

    name[0] = toupper(name[0]);//making the string's first char upper, and others lower
    length = strlen(name);
    for(i = 1; i < length ; i++){
        name[i] = tolower(name[i]);
    }

    if(surname != NULL){//making the string's first char upper, and others lower
        surname[0] = toupper(surname[0]);
        length = strlen(surname);
        for(i = 1; i < length ; i++){
            surname[i] = tolower(surname[i]);
        }
    }

    for(i = 0 ; i < lineNum ; i++){ //to check each structure's .fullnames
        char arr[20];//arr is used because strtok function changes its source string
        strcpy(arr,SignaturesTable[i].full_name);
        char *nameData = strtok(arr, " ");
        char *surnameData  = strtok(NULL , " ");
        if(!strcmp(name,nameData) || !strcmp( (surname==NULL)?(" "):(surname) ,surnameData) || !strcmp(name,surnameData)){
            return i; //returns i (which is the place of structure in the array) if the given string's one part is in the table
        }
    }
    printf("That owner does not exist! Please try again!\n");
    return -1; //if the string is not in the table, it'll return -1
}

void Sort(struct SignRecords *SignaturesTable,int lineNum){
    int swapped,i;
    char w_h; //to check if it is according to width or height
    struct SignRecords tempStruct;
    do{ //user should enter inputs until its correct
        printf("Sort by (w: width, h: height) :");
        scanf(" %c",&w_h);
    } while (w_h!='w' && w_h!='h');

    if(w_h=='w') { //sorting the table by width
        do {//used bubble sort: iterate until the program does not enter the "if" section (completely sorted), so that the variable swapped cannot be 1, and loop will stop
            swapped = 0;
            for (i = 1; i < lineNum; i++) {
                if (SignaturesTable[i-1].width < SignaturesTable[i].width){
                    tempStruct = SignaturesTable[i-1];
                    SignaturesTable[i-1] = SignaturesTable[i];
                    SignaturesTable[i] = tempStruct;
                    swapped=1;
                }
            }
        } while (swapped);
    }else{//sorting the table by height
        do {//used bubble sort: iterate until the program does not enter the "if" section (completely sorted), so that the variable swapped cannot be 1, and loop will stop
            swapped = 0;
            for (i = 1; i < lineNum; i++) {
                if (SignaturesTable[i-1].height < SignaturesTable[i].height){
                    tempStruct = SignaturesTable[i-1];
                    SignaturesTable[i-1] = SignaturesTable[i];
                    SignaturesTable[i] = tempStruct;
                    swapped=1;
                }
            }
        } while (swapped);
    }
    Display_SignaturesTable(SignaturesTable,lineNum); //displays the table after it is sorted
}

int main(int argc, char *argv[]) {
    int lineNum,option,check;
    char fullName[20];
    struct SignRecords *SignatureTable = Load_SignaturesTable(argv[1],&lineNum); // SignatureTable is an array of structures
    Display_SignaturesTable(SignatureTable,lineNum);

    do{ //iterates until the user gives the value 3 to the "option" variable
        printf("\nTo search for a signature, please press 1\n" //all options here
               "To sort signatures based on width o height, please press 2\n"
               "To exit, please press 3\n"
               "Your Choice:");
        fflush(stdin);
        scanf("%d",&option);
        printf("\n");

        if(option == 1){ // SEARCH option
            do{ //iterates and wants user to enter input until the given input is in the table
                printf("Enter the name of the signature owner:");
                fflush(stdin);
                gets(fullName);
                check = Search(SignatureTable,lineNum, fullName);
            }while(check == -1);
            printf("%s start signing at x=%d and y=%d and finalized at x=%d and y=%d. Hence, %s has a signature of width %d and height %d.\n",SignatureTable[check].full_name,SignatureTable[check].x_int,SignatureTable[check].y_int,SignatureTable[check].x_fin,SignatureTable[check].y_fin,SignatureTable[check].full_name,SignatureTable[check].width,SignatureTable[check].height);
        }
        else if (option == 2){// SORT option
            Sort(SignatureTable,lineNum);
        }

        printf("\n");
    }while(option!=3);

    return 0;
}
