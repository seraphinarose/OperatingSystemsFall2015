//
//  Program3.c
//  Homework2
//
//  Created by SRORS on 10/5/15.
//  Copyright (c) 2015 Seraphina Orsini. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>




int main(int argc, const char * argv[]) {
    
    int pid;                //holds process id
    char * args[2];         //holds args for exec command
    
    
    //Control is with parent process
    printf("Control: Parent Process Before Fork\n");
    printf("Program Name: %s    PID: %d\n",argv[0],getpid());
    
    //fork
    pid = fork();
    
    //If child process, exec Program1.out
    if(pid == 0)
    {   printf("Control: Child Process\n");
        printf("Child Name: %s    Child PID: %d\n",argv[0],getpid());
        
        //build argv for execv command
        args[0] = "Program1.out";
        args[1] = NULL;
        execv(args[0],args);
        
    }
    //if back at parent, show control by priting this statement
    else
    {   wait(&pid);
        printf("Control: Parent Process After Fork\n");
        
        
    }
    
    
    
    return 0;
}
