#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"


int parseNextInstruction(int instructionReg[6], int memory[100][6], short int counter);

int translateOpcode(char tens, char ones);

int getMemoryContents(int index);

int executeInstruction(char memory[100][6], short int counter);

int getRegContents(int regId);

int getMemLocationFromPointer(int pointerId);

void displayVMStatus();


short int programCounter = 0;		//program counter
short int p0 = 0;					//pointer registers
short int p1 = 0;
short int p2 = 0;
short int p3 = 0;
short int stackPointer = 0;			//stack pointer
char processStatusWord [2];		//PSW
int acc = 0;						//accumulator
int r0 = 0;							//registers
int r1 = 0;
int r2 = 0;
int r3 = 0;
char memory [100][6];			//memory
char instructionReg[6];         //instruction register



int main(int argc, char *argv[]) {
    
    
    
    /*These variables are associated with the implementation of the VM*/
    int filePointer;
    int i;
    int curLineNumber = 0;
    char inputInstruction [7];
    int ret;
    
    int x;
    int y;
    for(x = 0; x < 100; x ++) 
	{for(y = 0; y < 6; y ++) 
	{	memory[x][y] = 'X';
	}
	}
    
    //Read file into VM memory. Assume the file name is program2.
    filePointer = open("fib.txt", O_RDONLY);
    printf("Open is %d\n", filePointer) ;
    
    
    
    //If error in read
    if (filePointer < 0)
    {   printf("Could not open file\n");
        exit(0);
    }
    
    
    //read in the first line of the program
    ret = read(filePointer, inputInstruction, 7);
    
    //infinite loop until file contents end
    while (1)
    {
        //end of file or error
        if (ret <= 0)
        {	break;
        }
        
        //copy input line to program memory
        for (i = 0; i < 6 ; i++)
        {	memory[curLineNumber][i] = inputInstruction[i];
        }
        
        //printing out program line for debugging purposes
//        printf("\nProgram Line %d:	", curLineNumber);
//        for(i = 0; i < 6; i++)
//        {	printf("%c", memory[curLineNumber][i]);
//        }
//        printf("\n") ;
        
        //read in next line of program input
        ret = read(filePointer, inputInstruction, 7);
        
        //if the first character is a 'Z' then you are reading data.
        //No more program code so break out of loop
        if(inputInstruction[0] == 'Z')
        {	break;
        }
        
        //increment line
        curLineNumber++;
        
    }
    
    
    
   
    programCounter = 0;
    int exitStatus = 0;
    while (exitStatus == 0)
    {
        
        exitStatus = executeInstruction(memory,programCounter);
        printf("\n");
        
        
    }
    printf("\nFinal VM State\n");
    displayVMStatus();
    
    
}


int translateOpcode(char tens, char ones)
{	int retVal = (tens - 48) * 10;
    retVal += (ones - 48);
    return retVal;
}


//
//
int executeInstruction(char memory[100][6], short int counter)
{
    
    for(int i = 0; i < 6; i++)
    {	instructionReg[i] = memory[counter][i];
        
    }
    printf("PC = %02d; ",programCounter);
    printf("IR = ");
    for(int j = 0; j < 6; j++)
    {	printf("%c",instructionReg[j]);
        
    }
    printf("; ");
    
    
    int opcode = translateOpcode(instructionReg[0],instructionReg[1]);
    int retVal = 0;
    
    switch(opcode)
    {	case 0:
        {   printf("[Load Pointer Immediate]");
            
            int value = convertTwoCharsToInt(instructionReg[4],instructionReg[5]);
            int pointerNum = (instructionReg[3] - 48);
            
            
            if(pointerNum == 0)
            {	p0 = value;
            }
            else if(pointerNum == 1)
            {	p1 = value;
            }
            else if(pointerNum == 2)
            {	p2 = value;
                
            }
            else if(pointerNum == 3)
            {	p3 = value;
            }
            programCounter++;
            break;
        }
        case 1:
        {
            printf("[Add to Pointer Immediate]");
            int value = convertTwoCharsToInt(instructionReg[4],instructionReg[5]);
            int pointerNum = (instructionReg[3] - 48);
            
            
            if(pointerNum == 0)
            {	p0 += value;
                
            }
            else if(pointerNum == 1)
            {	p1 += value;
                
            }
            else if(pointerNum == 2)
            {	p2 += value;
                
            }
            else if(pointerNum == 3)
            {	p3 += value;
                
            }
            programCounter++;
            break;
        }
        case 2:
        {
            printf("[Subtract From Pointer Immediate]");
            int value = convertTwoCharsToInt(instructionReg[4],instructionReg[5]);
            int pointerNum = (instructionReg[3] - 48);
            
            
            if(pointerNum == 0)
            {	 p0 += value;
                
            }
            else if(pointerNum == 1)
            {	p1 += value;
                
            }
            else if(pointerNum == 2)
            {	p2 += value;
                
            }
            else if(pointerNum == 3)
            {	p3 += value;
                
            }
            programCounter++;
            break;
        }
        case 3:
        {
            printf("[Load Accumulator Immediate]");
            int value = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            
            acc = value;
            programCounter++;
            break;
        }
        case 4:
        {
            printf("[Load Accumulator Register Addressing]");
            int pointerNum = (instructionReg[3] - 48);
            int value;
            
            value = getMemoryContents(getMemLocationFromPointer(pointerNum));
            
            acc = value;
            programCounter++;
            break;
        }
        case 5:
        {
            printf("[Load Accumulator Direct Addressing]");
            int memAddress = convertTwoCharsToInt(instructionReg[2],instructionReg[3]);
            int value = getMemoryContents(memAddress);
            acc = value;
            programCounter++;
            break;
        }
        case 6:
        {
            printf("[Store Accumulator Register Addressing]");
            int pointerNum = (instructionReg[3] - 48);
            
            char * accVals = convertIntToMemory(acc);
            
            
            int memLoc = getMemLocationFromPointer(pointerNum);
            
            for(int i = 0;i<6;i++)
            {	memory[memLoc][i] = accVals[i];
                
            }
            
            programCounter++;
            break;
        }
        case 7:
        {
            printf("[Store Accumulator Direct Addressing]");
            int memLoc = convertTwoCharsToInt(instructionReg[3],instructionReg[3]);
            char * accVals = convertIntToMemory(acc);
            for(int i = 0;i<6;i++)
            {	memory[memLoc][i] = accVals[i];
                
            }
            programCounter++;
            
            break;
        }
        case 8:
        {   printf("[Store Register To Memory: Reg Addressing]");
            int regId = (instructionReg[3] - 48);
            int pointerId = (instructionReg[5] - 48);
            int memLoc;
            char * regVals = NULL;
            
            
            
            memLoc = getMemLocationFromPointer(pointerId);
            
            int regValue = getRegContents(regId);
            regVals = convertIntToMemory(regValue);
                
            
            for(int i = 0; i<6;i++)
            {
                memory[memLoc][i] = regVals[i];
                
            }
            programCounter++;
            break;
        }
        case 9:
        {
            printf("[Store Register To Memory: Direct Addressing]");
            int memLoc = convertTwoCharsToInt(instructionReg[4],instructionReg[5]);
    
            int regId = (instructionReg[3] - 48);
            char * regVals = NULL;
            
            int regValue = getRegContents(regId);
            regVals = convertIntToMemory(regValue);
                
                
            for(int i = 0;i<6;i++)
            {	memory[memLoc][i] = regVals[i];
                
            }
            programCounter++;
            
            break;
        }
        case 10:
        {   printf("[Load Register From Memory: Register Addressing]");
            int regId = (instructionReg[3] - 48);
            int pointerId = (instructionReg[5] - 48);
            int memLoc = -1;
            
            memLoc = getMemLocationFromPointer(pointerId);
            
            if(regId == 0)
            {	r0 = getMemoryContents(memLoc);
                
            }
            else if(regId == 1)
            {	r1 = getMemoryContents(memLoc);
                
            }
            else if(regId == 2)
            {	r2 = getMemoryContents(memLoc);
                
            }
            else if(regId == 3)
            {	r3 = getMemoryContents(memLoc);
                
            }
            
            programCounter++;
            break;
        }
        case 11:
        {   printf("[Load Register From Memory: Direct Addressing]");
            int regId = (instructionReg[3] - 48);
            int memLoc = convertTwoCharsToInt(instructionReg[4],instructionReg[5]);
            if(regId == 0)
            {	r0 = getMemoryContents(memLoc);
                
            }
            else if(regId == 1)
            {	r1 = getMemoryContents(memLoc);
                
            }
            else if(regId == 2)
            {	r2 = getMemoryContents(memLoc);
                
            }
            else if(regId == 3)
            {	r3 = getMemoryContents(memLoc);
                
            }
            programCounter++;
            break;
        }
        case 12:
        {
            printf("[Load Register R0 Immediate]");
            r0 = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            programCounter++;
            break;
        }
        case 13:
        {
            printf("[Register to Register Transer]");
            int contents = -1;
            int regId2 = (instructionReg[5] - 48);
            int regId1 = (instructionReg[3] - 48);
           
            contents = getRegContents(regId2);
            if(regId1 == 0)
            {	r0 = contents;
                
            }
            else if(regId1 == 1)
            {	r1 = contents;
                
            }
            else if(regId1 == 2)
            {	r2 = contents;
                
            }
            else if(regId1 == 3)
            {	r3 = contents;
                
            }
            programCounter++;
            break;
        }
        case 14:
        {
            printf("[Load Accumulator from Register]");
            int regId = (instructionReg[3] - 48);
            
            acc = getRegContents(regId);
            programCounter++;
            
            break;
        }
        case 15:
        {
            printf("[Load Register from Accumulator]");
            int regId = (instructionReg[3] - 48);
            
            
            if(regId == 0)
            {	r0 = acc;
                
            }
            else if(regId == 1)
            {	r1 = acc;
                
            }
            else if(regId == 2)
            {	r2 = acc;
                
            }
            else if(regId == 3)
            {	r3 = acc;
                
            }
            programCounter++;
            break;
        }
        case 16:
        {   printf("[Add Accumulator Immediate]");
            int addVal = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            acc += addVal;
            programCounter++;
            break;
        }
        case 17:
        {   printf("[Subtract Accumulator Immediate]");
            int subVal = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            acc -= subVal;
            programCounter++;
            break;
        }
        case 18:
        {
            printf("[Add Contents of Register to Accumulator]");
            int regId = (instructionReg[3] - 48);
            acc += getRegContents(regId);
            programCounter++;
            break;
        }
        case 19:
        {
            printf("[Subtract Contents of Register from Accumulator]");
            int regId = (instructionReg[3] - 48);
            acc -= getRegContents(regId);
            programCounter++;
            break;
            
        }
        case 20:
        {
            printf("[Add Accumulator Register Addressing]");
            int pointerId = (instructionReg[3] - 48);
            
            int value = getMemoryContents(getMemLocationFromPointer(pointerId));
            
            acc += value;
            programCounter++;
            break;
        }
        case 21:
        {
            printf("[Add Accumulator Direct Addressing]");
            int memLoc = convertTwoCharsToInt(instructionReg[2],instructionReg[3]);
            int value = getMemoryContents(memLoc);
            acc += value;
            programCounter++;
            break;
        }
        case 22:
        {
            printf("[Subtract from Accumulator Register Addressing]");
            int pointerId = (instructionReg[3] - 48);
            int value = getMemoryContents(getMemLocationFromPointer(pointerId));
            acc -= value;
            programCounter++;
            break;
        }
        case 23:
        {
            printf("[Subtract from Accumulator Direct Addressing]");
            int memLoc = convertTwoCharsToInt(instructionReg[2],instructionReg[3]);
            int value = getMemoryContents(memLoc);
            acc -= value;
            programCounter++;
            break;
        }
            
        case 24:
        {
            printf("[Compare Equal Register Addressing]");
            int pointerId = (instructionReg[3] - 48);
            int value = getMemoryContents(getMemLocationFromPointer(pointerId));
            if(acc == value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
            
        case 25:
        {
            printf("[Compare Less Register Addressing]");
            int pointerId = (instructionReg[3] - 48);
            int value = getMemoryContents(getMemLocationFromPointer(pointerId));
            if(acc < value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
        case 26:
        {
            printf("[Compare Greater Register Addressing]");
            int pointerId = (instructionReg[3] - 48);
            int value = getMemoryContents(getMemLocationFromPointer(pointerId));
            if(acc > value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
        case 27:
        {
            
            printf("[Compare Greater Immediate]");
            int value = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            if(acc > value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
            
        }
        case 28:
        {
            printf("[Compare Equal Immediate]");
            int value = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            if(acc == value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
            
        }
        case 29:
        {
            printf("[Compare Less Immediate]");
            int value = convertFourCharsToInt(instructionReg[2],instructionReg[3],instructionReg[4],instructionReg[5]);
            if(acc < value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
        case 30:
        {	printf("[Compare Register Equal]");
            int regId = (instructionReg[3] - 48);
            int value = getRegContents(regId);
            if(acc == value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            break;
        }
        case 31:
        {
            printf("[Compare Register Less]");
            int regId = (instructionReg[3] - 48);
            int value = getRegContents(regId);
            if(acc < value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
        case 32:
        {
            printf("[Compare Register Greater]");
            int regId = (instructionReg[3] - 48);
            int value = getRegContents(regId);
            if(acc > value)
            {	processStatusWord[0] = 'T';
                
            }
            else
            {	processStatusWord[0] = 'F';
                
            }
            programCounter++;
            break;
        }
        case 33:
        {
            printf("[Branch Conditional True]");
            int jumpCounter = convertTwoCharsToInt(instructionReg[2],instructionReg[3]);
            if(processStatusWord[0] =='T')
            {   programCounter = jumpCounter;
            }
            else {
                programCounter++;
            }
            break;
        }
        case 34:
        {
            printf("[Branch Conditional False]");
            int jumpCounter = convertTwoCharsToInt(instructionReg[2],instructionReg[3]);
            if(processStatusWord[0] =='F')
            {   programCounter = jumpCounter;
            }
            else {
                programCounter++;
            }
            break;
        }
        case 35:
        {   printf("[Branch Unconditional]");
            int jumpCounter = convertTwoCharsToInt(instructionReg[3],instructionReg[4]);
            programCounter = jumpCounter;
            break;
        }
        case 99:
        {
            printf("[HALT]");
            return -1;
            break;
        }
    }
    
    
    return retVal;
    
}

int getMemoryContents(int index)
{	
    int retVal = 0;

    retVal += (memory[index][2] - 48) * 1000;
    retVal += (memory[index][3] - 48) * 100;
    retVal += (memory[index][4] - 48) * 10;
    retVal += (memory[index][5] - 48);
    
    return retVal;
}


//Return contents of register
// 0 <= regID <= 3
int getRegContents(int regId)
{
    //select correct register to return by value
    if(regId == 0)
    {	return r0;
        
    }
    else if(regId == 1)
    {
        return r1;
    }
    else if(regId == 2)
    {
        return r2;
        
    }
    else if(regId == 3)
    {
        return r3;
        
    }
    //if not valid ID, return 0
    return 0;
}


//Return memory location pointer points to
// 0<= pointerID <= 3
int getMemLocationFromPointer(int pointerId)
{
    //select correct pointer to return value of memLoc it points to
    if(pointerId == 0)
    {
        return p0;
    }
    else if(pointerId == 1)
    {
        return p1;

    }
    else if(pointerId == 2)
    {
        return p2;
    }
    else if(pointerId == 3)
    {
        return p3;
    }
    
    //If not valid ID, return 0
    return 0;
}


//Function to display the status of the VM at any time.
void displayVMStatus()
{
    printf("CPU\n");
    printf("PC=%2d SP=%2d ACC=%4d PSW=%c IR=",programCounter,stackPointer,acc,processStatusWord[0]);
    
    for(int i=0;i<6;i++)
    {	printf("%c",instructionReg[i]);
        
    }
    printf("\n\n");
    printf("REGISTERS\n");
    printf("P0=%-4d P1=%-4d P2=%-4d P3=%-4d\n",p0,p1,p2,p3);
    printf("R0=%-4d R1=%-4d R2=%-4d R3=%-4d\n",r0,r1,r2,r3);
    printf("\n\n");
    printf("MEMORY\n");
    
    int m = 0;
    for (int i = 0; i < 100; i++)
    {   m++;
        for(int j = 0; j<6;j++)
        {
            printf("%c", memory[i][j]);
            
            
        }
        printf(" ");
        if(m%10 ==0)
        {
            printf("\n");
        }
    }
}