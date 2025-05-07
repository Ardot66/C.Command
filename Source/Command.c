#include <string.h>
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
            if(*aliases == '\0')
            {
                if(allMatched)
                    return command;

                break;
            }
            
            if(*aliases == ' ')
            {
                if(allMatched)
                    return command;

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

char *GetArg(int argCount, char **args, char *flag)
{
    for(int x = 0; x < argCount; x++)
    {
        if(strcmp(flag, args[x]) == 0)
            return args[x];
    }
}