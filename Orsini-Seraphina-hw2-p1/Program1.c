//
//  program1.c
//  Homework2
//
//  Created by SRORS on 10/4/15.
//  Copyright (c) 2015 Seraphina Orsini. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, const char * argv[]) {
    
    //Print Statements with program name and ID
    printf("Program Name: %s    PID: %d\n",argv[0],getpid());
    printf(" /\\\n");
    printf("/__\\\n");
    
    return 0;
}
