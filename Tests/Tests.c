#include <stdio.h>
#include "Command.h"

int CommandBody(int argc, char **argv)
{
    printf("CommandRun\n");
}

const Command Commands[] = 
{
    CommandInit("mycommand 1 2", CommandBody, "", ""),
    //CommandInit("", CommandBody, "", "")
};

const size_t CommandCount = sizeof(Commands) / sizeof(Command);

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Please supply a command");
        return 0;
    }

    const Command *command = FindCommand(Commands, CommandCount, argv[1]);

    if(command == NULL)
        return 0;

    command->Command(argc, argv + 1);
}
