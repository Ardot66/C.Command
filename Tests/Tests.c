#include <stdio.h>
#include "Command.h"
#include "TestingUtilities.h"

int CommandBody(int argc, char **argv)
{
    printf("CommandRun\n");
}

const Command Commands[] = 
{
    CommandInit("mycommand 12", CommandBody, "This command is a test", 
        "\n"
        "Line one of help, this is normal text\n"
        "%i-h --help%pThis line is a test of the subcommand system\n"
        "%i--humungus%pThis line is a second test of the subcommand system\n"
    ),
    CommandInit("3 4 5", CommandBody, "This command is another test", 
        ""
    ),
};

const size_t CommandCount = sizeof(Commands) / sizeof(Command);

int main(int argc, char **argv)
{
    printf("Printing help\n\n");

    for(int x = 0; x < CommandCount; x++)
    {
        PrintCommandHelp(Commands + x, 3, 15);
    }

    TEST(FindCommand(Commands, CommandCount, "12"), ==, &Commands[0], p)
    TEST(FindArg(4, (char *[]){"-h", "amogus", "hehehe", "--help"}, "-f --help", NULL), ==, 1, d)
}
