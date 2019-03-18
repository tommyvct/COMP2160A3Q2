//--------------------------------------------------------------
// Name: Shang Wu
// Student Number: 7852291
// Course: COMP2160, Section A01
// Instructor: Mehdi Niknam
// Assignment 3, Question 2
// 
// Main driver program for set.o
// Implemented a simple shell to test set.o
// Can be used as both scripter and shell
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/set.h"

#define failed(x) printf("***FAILED*** %s\n", x) 
#define instructionIs(x) !strcmp(x, instruction)

const int MAX = 100;

int main(int argc, char const *argv[])
{
    FILE * instructionStream = stdin;
    Boolean readScript = false;

    // if a script file passed in
    if (argc > 1)
    {
        instructionStream = fopen(argv[1], "r");
        readScript = true;
        printf("Running script from \"%s\".\n", argv[1]);
    }
    else
    {
        fprintf(stdout,"Welcome to Set test shell!\n");
    }

    Set * setArray[MAX] = {NULL};
    int setSize;

    if (!validateMemUse())
    {
        failed("validateMemUse() is faulty.");
    }

    while (true)
    // interal exit
    // exit condition: EOF or "exit" as instrucion
    {
        char * buffer = malloc(sizeof(char) * MAX);
        char * instruction = NULL;
        char * paramString[MAX];
        int param[MAX];
        int paramSize = 0;


        printf("> ");
        fgets(buffer, MAX, instructionStream);

        // get instruction
        instruction = strtok(buffer, " ");
        // if pressed control-d or EOF
        if (instruction == NULL)
        {
            printf("\n");
            break;
        }
        // if pressed enter
        else if (!strcmp("\n", instruction))
        {
            if (readScript)
            {
                printf("\n");
            }

            continue;
        }

        // get parameter in string
        while(true)
        {
            paramString[paramSize] = strtok(NULL, " ");
            if (paramString[paramSize] == NULL)
            {
                break;
            }
            paramSize++;
        }

        // convert parameter string into int
        for(int i = 0; i < paramSize; i++)
        {
            int paramStatus = sscanf(paramString[i], "%d", &param[i]);
            if (paramStatus == EOF || paramStatus == 0)
            {
                paramSize = i;
                break;
            }
        }

        if (buffer[0] == '#')
        {
            continue;
        }
        else if (instructionIs("exit\n"))
        {
            break;
        }
        // operation with no parameter
        else if (paramSize == 0)
        {
            if (instructionIs("validate\n"))
            {
                Boolean result = validateMemUse();

                // result XOR setSize
                if (!result != !setSize)
                {
                    printf("Memory validated.\n");
                }
                else
                {
                    failed("Validation error");
                }
            }
            else
            {
                printf("Command not found.\n");
            }
        }
        // operation with 1 parameter
        else if (paramSize == 1)
        {
            if (instructionIs("new"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX)
                {
                    printf("Invalid Range. Valid range are from 0 to %d.\n", MAX - 1);
                }
                // prevent segmentation fault
                else if (setArray[param[0]] != NULL)
                {
                    printf("Set %d is not empty, delete it then try again.\n", param[0]);
                }
                else
                {
                    setArray[param[0]] = newSet();
                    if (setArray[param[0]] == NULL)
                    {
                        failed("Failed to construct a new Set.");
                    }
                    else
                    {
                        setSize++;
                        printf("Successfully constructed a new Set.\n");
                    }
                }
            }
            else if (instructionIs("delete"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX)
                {
                    printf("Invalid Range. Valid range are from 0 to %d.\n", MAX - 1);
                }
                // prevent segmentation fault
                else if (setArray[param[0]] == NULL)
                {
                    printf("No set to delete.\n");
                }
                else
                {
                    setArray[param[0]] = deleteSet(setArray[param[0]]);
                    if (setArray[param[0]] == NULL)
                    {
                        setSize--;
                        printf("Successfully deleted the Set.\n");
                    }
                    else
                    {
                        failed("Failed to delete the Set.");
                    }
                }
            }
            else
            {
                printf("Command not found.\n");
            }
        }
        // operation with 2 parameters
        else if (paramSize == 2)
        {
            if (instructionIs("insert"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL)
                    {
                        printf("Set %d is undefined, failed to insert %d.\n", param[0], param[1]);
                    }
                    else
                    {
                        if (insertItem(setArray[param[0]], param[1]))
                        {
                            printf("Successfuly inserted %d.\n", param[1]);
                        }
                        else
                        {
                            fprintf(stdout, "Failed to insert %d.\n", param[1]);
                        }
                    }
                }
            }
            else if (instructionIs("remove"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL)
                    {
                        printf("Set %d is undefined, failed to remove %d.\n", param[0], param[1]);
                    }
                    else
                    {
                        if (removeItem(setArray[param[0]], param[1]))
                        {
                            printf("Successfuly removed %d.\n", param[1]);
                        }
                        else
                        {
                            fprintf(stdout, "Failed to remove %d.\n", param[1]);
                        }
                    }
                }
            }
            else if (instructionIs("equal"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX || param[1] < 0 || param[1] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL || setArray[param[1]] == NULL)
                    {
                        printf("Attempting to compare Undefined Sets.\n");
                    }
                    else
                    {
                        if (areEqual(setArray[param[0]], setArray[param[1]]))
                        {
                            printf("Set %d and %d are equal.\n", param[0], param[1]);
                        }
                        else
                        {
                            printf("Set %d and %d are NOT equal.\n", param[0], param[1]);
                        }
                    }
                }
            }
            else if (instructionIs("disjoint"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX || param[1] < 0 || param[1] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL || setArray[param[1]] == NULL)
                    {
                        printf("Attempting to compare Undefined Sets.\n");
                    }
                    else
                    {
                        if (areDisjoint(setArray[param[0]], setArray[param[1]]))
                        {
                            printf("Set %d and %d have NO common items.\n", param[0], param[1]);
                        }
                        else
                        {
                            printf("Set %d and %d have common items.\n", param[0], param[1]);
                        }
                    }
                }
            }
            else
            {
                printf("Command not found.\n");
            }
        }
        // operation with 3 parameters
        else if (paramSize == 3)
        {
            if (instructionIs("union"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX || param[1] < 0 || param[1] >= MAX || param[2] < 0 || param[2] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL || setArray[param[1]] == NULL)
                    {
                        printf("Attempting to use Undefined Sets.\n");
                    }
                    else if (setArray[param[2]] != NULL)
                    {
                        printf("Set %d is not empty, delete it then try again.\n", param[2]);
                    }
                    else
                    {
                        setArray[param[2]] = unionOf(setArray[param[0]], setArray[param[1]]);
                        if (setArray[param[2]] == NULL)
                        {
                            failed("Failed to complete union operation.");
                        }
                        else
                        {
                            printf("Done.\n");
                        }
                    }
                }
            }
            else if (instructionIs("symdiff"))
            {
                // range check
                if (param[0] < 0 || param[0] >= MAX || param[1] < 0 || param[1] >= MAX || param[2] < 0 || param[2] >= MAX)
                {
                    printf("Invalid Range of Set. Valid range are from 0 to %d.\n", MAX - 1);
                }
                else
                {
                    // prevent segmentation fault
                    if (setArray[param[0]] == NULL || setArray[param[1]] == NULL)
                    {
                        printf("Attempting to use Undefined Sets.\n");
                    }
                    else if (setArray[param[2]] != NULL)
                    {
                        printf("Set %d is not empty, delete it then try again.\n", param[2]);
                    }
                    else
                    {
                        setArray[param[2]] = symmetricDifferenceOf(setArray[param[0]], setArray[param[1]]);
                        if (setArray[param[2]] == NULL)
                        {
                            failed("Failed to complete symmetric difference operation.");
                        }
                        else
                        {
                            printf("Done.\n");
                        }
                    }
                }
            }
            else
            {
                printf("Command not found.\n");
            }
        }
        else
        {
            printf("Command not found.\n");
        }
    }

    if (readScript)
    {
        printf("End of script.\n");
    }
    else
    {
        printf("bye!\n");
    }

    return 0;
}
