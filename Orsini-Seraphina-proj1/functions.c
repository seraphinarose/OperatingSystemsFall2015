//
//  functions.c
//  Project1
//
//  Created by SRORS on 9/24/15.
//  Copyright (c) 2015 Seraphina Orsini. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"



int convertTwoCharsToInt(char tens, char ones)
{	int retVal = (tens - 48) * 10;
    retVal += (ones - 48);
    return retVal;
    
}

int convertFourCharsToInt(char thou, char huns, char tens, char ones)
{	int retVal = (thou - 48) * 1000;
    retVal += (huns - 48) * 100;
    retVal += (tens - 48) * 10;
    retVal += (ones - 48);
    return retVal;
}


char * convertIntToFourChars(int input)
{
    char *retChar = malloc(sizeof(char)*4);
    if(retChar == NULL)
        return NULL;
    sprintf(retChar,"%04d",input);
    return retChar;
}

char * convertIntToMemory(int input)
{	char *tempChar = malloc(sizeof(char)*4);
    if(tempChar == NULL)
        return NULL;
    sprintf(tempChar,"%04d",input);
    
    char * retChar = malloc(sizeof(char)*6);
    retChar[0] = 'Z';
    retChar[1] = 'Z';
    retChar[2] = tempChar[0];
    retChar[3] = tempChar[1];
    retChar[4] = tempChar[2];
    retChar[5] = tempChar[3];
    free(tempChar);
    return retChar;
}



char * convertIntToTwoChars(int input)
{
    char *retChar = malloc(sizeof(char)*2);
    if(retChar == NULL)
        return NULL;
    sprintf(retChar,"%02d",input);
    return retChar;
}

