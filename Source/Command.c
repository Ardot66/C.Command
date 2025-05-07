#include <string.h>
#include <stdio.h>
#include "Command.h"

const Command *FindCommand(const Command *commands, const size_t commandCount, const char *commandName)
{
    for(size_t x = 0; x < commandCount; x++)
    {
        const Command *command = commands + x;

        const char *aliases = command->Aliases;
        const char *commandCur = commandName;
        int allMatched = 1;
        while(1)
        {
            if((*aliases == ' ' || *aliases == '\0' && *commandCur == '\0') && allMatched)
                return command;
            
            if(*aliases == '\0')
                break;

            if(*aliases == ' ')
            {
                allMatched = 1;
                commandCur = commandName;
                aliases++;
                continue;
            }
                
            allMatched &= *aliases == *commandCur;

            if(*commandCur != '\0')
                commandCur++;
            aliases++;
        }
    }

    return NULL;
}

void PrintCommandSummary(const Command *command, const int padding)
{
    size_t commandNameLength = strlen(command->Aliases);
    int addedPadding = commandNameLength >= padding ? 1 : padding - commandNameLength;
    printf("%s%*c%s\n", command->Aliases, addedPadding, ' ', command->HelpSummary);
}

void PrintCommandHelp(const Command *command, const size_t indentation, const int padding)
{
    PrintCommandSummary(command, 0);
    const char *help = command->Help;

    const char *curSegment = help;
    int curSegmentLength = 0;

    while(1)
    {
        curSegmentLength++;

        if(*help == '%')
        {
            switch(*(help + 1))
            {
                case 'i':
                {
                    printf("%.*s%*c", curSegmentLength - 1, curSegment, indentation, ' ');
                    curSegment = help + 2;
                    curSegmentLength = -1;
                    break;
                }
                case 'p':
                {
                    int addedPadding = curSegmentLength > padding ? 0 : padding - curSegmentLength;
                    printf("%.*s%*c", curSegmentLength - 1, curSegment, addedPadding, ' ');
                    curSegment = help + 2;
                    curSegmentLength = -1;
                    break;
                }
            }
        }

        if(*help == '\0')
        {
            printf("%s", curSegment);
            break;
        }
        
        help++;
    }
}

int FindArg(int argCount, char **args, const char *flags, char **argDest)
{
    for(int x = 0; x < argCount; x++)
    {
        const char *curFlags = flags;
        char *curArg = args[x];
        int matching = 1;

        while(1)
        {            
            if(matching && (*curFlags == ' ' || *curFlags == '\0'))
            {
                if(argDest != NULL)
                    *argDest = argCount > x ? args[x + 1] : NULL;
                return 1;
            }
            
            if(*curFlags == '\0' || *curArg == '\0')
                break;
            if(*curFlags == ' ')
            {
                matching = 1;
                curArg = args[x];
                curFlags++;
                continue;
            }
            
            matching &= *curArg == *curFlags;

            curArg++;
            curFlags++;
        }
    }

    return 0;
}