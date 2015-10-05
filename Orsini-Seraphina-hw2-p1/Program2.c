//
//  program2.c
//  Homework2
//
//  Created by SRORS on 10/4/15.
//  Copyright (c) 2015 Seraphina Orsini. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, const char * argv[]) {
    
    
    int i = atoi(argv[1]);      //integer value of arg passed to program exec
    
    //print program name and ID, plus i print statements from arg 
    printf("Program Name: %s    PID: %d\n",argv[0],getpid());
    int j;
    for(j=0;j<i;j++)
    {   printf("Printing line %d of %d\n",j+1,i);
        
    }
    
    return 0;
}
