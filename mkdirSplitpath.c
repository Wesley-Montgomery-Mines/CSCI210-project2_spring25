#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern struct NODE *root;
extern struct NODE *cwd;

//This creates a new directory at the given path.
void mkdir(char pathName[])
{
    char dirName[64];
    char baseName[64];

    //This is where splitPath is used to get parent directory and parse path.
    struct NODE *dirToInsert = splitPath(pathName, baseName, dirName);
    if (dirToInsert == NULL)
    {
        return;
    }

    //This is the check if to see if no path was provided.
    if (strcmp(pathName, "/") == 0)
    {
        printf("MKDIR ERROR: no path provided\n");
        return;
    }

    //This is the check to see if a node with the same name already exists.
    struct NODE *currentChild = dirToInsert->childPtr;
    while (currentChild != NULL)
    {
        if (strcmp(currentChild->name, baseName) == 0)
        {
            printf("MKDIR ERROR: directory %s already exists\n", pathName);
            return;
        }
        currentChild = currentChild->siblingPtr;
    }

    //This will create and initialize a new directory node.
    struct NODE *newPath = (struct NODE *)malloc(sizeof(struct NODE));
    newPath->childPtr = NULL;
    newPath->fileType = 'D';
    newPath->siblingPtr = NULL;
    newPath->parentPtr = dirToInsert;
    strncpy(newPath->name, baseName, 64);

    //This will insert the node as a child or sibling.
    if (dirToInsert->childPtr == NULL)
    {
        dirToInsert->childPtr = newPath;
    }
    else
    {
        struct NODE *temp = dirToInsert->childPtr;
        while (temp->siblingPtr != NULL)
        {
            temp = temp->siblingPtr;
        }
        temp->siblingPtr = newPath;
    }

    //This is the success message. Yay it worked.
    printf("MKDIR SUCCESS: node %s successfully created\n", pathName);
}

//This will parse a given pathName into dirName and baseName.
//This will return the pointer to the parent node where the baseName would be located.
struct NODE *splitPath(char *pathName, char *baseName, char *dirName)
{
    struct NODE *currentNode = (pathName[0] == '/') ? root : cwd;

    //This will identify the position of the last slash.
    int lastSlash = -1;
    int currentIndex = 0;
    while (pathName[currentIndex] != '\0')
    {
        if (pathName[currentIndex] == '/')
        {
            lastSlash = currentIndex;
        }
        currentIndex++;
    }

    //This will split the path into baseName and dirName.
    if (lastSlash != -1)
    {
        strcpy(baseName, pathName + lastSlash + 1);
        strncpy(dirName, pathName, lastSlash);
        dirName[lastSlash] = '\0';
    }
    else
    {
        strcpy(dirName, "");
        strcpy(baseName, pathName);
    }

    //This will traverse directories from dirName.
    char *currentDirName = strtok(dirName, "/");
    while (currentDirName != NULL)
    {
        struct NODE *child = currentNode->childPtr;

        //This will search for currentDirName among currentNode's children.
        while (child != NULL && strcmp(child->name, currentDirName) != 0)
        {
            child = child->siblingPtr;
        }

        //This will pop up if a directory is not found.
        if (child == NULL)
        {
            printf("ERROR: directory %s does not exist\n", dirName);
            return NULL;
        }

        currentNode = child; //This will move down to the next level.
        currentDirName = strtok(NULL, "/");
    }

    return currentNode; //This is the parent of the baseName.
}