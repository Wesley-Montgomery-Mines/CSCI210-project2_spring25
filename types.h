#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//This is the structure representing each node in the file system tree.
//A node can either represent a file or a directory.
struct NODE
{
    char name[64];           //This is the name of file or directory.
    char fileType;           //This is the filetype can be labeled either F for file or D for directory.
    struct NODE *childPtr;   //This is the pointer to first child node.
    struct NODE *siblingPtr; //This is the pointer to next sibling node.
    struct NODE *parentPtr;  //This is the pointer to parent node.
};

//These are the function declarations for all supported commands.
void mkdir(char temp[]);
void rmdir(char temp[]);
void ls(char temp[]);
void cd(char temp[]);
void pwd();
void touch(char temp[]);
void rm(char temp[]);
void menu();
void printTree();
void printHelper(struct NODE *directory, int depth);
int quit();

//This magically splits a path into dir and base name.
struct NODE *splitPath(char *pathName, char *baseName, char *dirName);
