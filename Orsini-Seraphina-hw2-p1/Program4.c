//
//  Program4.c
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
    
    int pid;                //process id
    char * args[3];         //args to pass to execv
    char num = *argv[1];    //value at 2nd position: counter for program 3
    
    //Control is with parent, print name and ID
    printf("Control: Parent Process Before Fork\n");
    printf("Program Name: %s    PID: %d\n",argv[0],getpid());
    
    //fork
    pid = fork();
    
    //If child process, exec Program3.out
    if(pid == 0)
    {   printf("Control: Child Process\n");
        printf("Child Name: %s    Child PID: %d\n",argv[0],getpid());
        
        //build argv for execv
        args[0] = "Program2.out";
        args[1] = &num;
        args[2] = NULL;
        execv(args[0],args);
        
    }
    //else wait for exec, show control change
    else
    {   wait(&pid);
        printf("Control: Parent Process After Fork\n");
        
        
    }
    
    

    return 0;
}
