#include "types.h"

struct NODE *root; //This is the pointer to root of the simulated file system
struct NODE *cwd;  //This is the pointer to the current working directory

//This is the list of valid commands for the shell
char *cmd[] = {
    "mkdir", "rmdir", "ls", "cd", "pwd", "touch", "rm",
    "menu", "tree", "quit", NULL};

/*The function findCMD does the following three things.
* Find the index of a command string in the cmd[] array.
* Take the command string entered by the user.
* And finally return the index of the command in cmd[] or -1 if not found.*/
int findCMD(char *command)
{
    int i = 0;
    while (cmd[i])
    {
        if (!strcmp(command, cmd[i]))
        {
            return i;
        }
        i++;
    }
    return -1;
}

/*The function initialize does the following.
* First it initializes the root of the file system tree.
* Then sets the root directory name to "/", the type to 'D', and the current working directory to the root.*/
void initialize()
{
    root = (struct NODE *)malloc(sizeof(struct NODE));
    root->parentPtr = NULL;
    root->siblingPtr = NULL;
    strcpy(root->name, "/");
    root->fileType = 'D';
    root->childPtr = NULL;

    cwd = root;
}

int main()
{
    initialize(); //This sets up the root directory.

    int index;
    char line[128], command[64], temp[64];

    while (1)
    {
        fprintf(stderr, "Input command > "); //This will prompt to stderr.
        fgets(line, 128, stdin);             //This will read input line.
        line[strcspn(line, "\n")] = 0;       //This will remove newline.

        command[0] = temp[0] = 0;             //This will reset the strings.
        sscanf(line, "%s %s", command, temp); //This will extract the command and optional path.

        index = findCMD(command); //This will identify the command.

        switch (index)
        {
        case 0:
            mkdir(temp);
            break;
        case 1:
            rmdir(temp);
            break;
        case 2:
            ls(temp);
            break;
        case 3:
            cd(temp);
            break;
        case 4:
            pwd();
            break;
        case 5:
            touch(temp);
            break;
        case 6:
            rm(temp);
            break;
        case 7:
            menu();
            break;
        case 8:
            printTree();
            break;
        case 9:
            return quit(); //This quits program.
        default:
            printf("Invalid command\n");
        }
    }
}
