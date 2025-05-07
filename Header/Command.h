#ifndef ___COMMAND___
#define ___COMMAND___

#include <stdint.h>

typedef struct Command
{
    char *Aliases;
    int (*Command)(int argCount, char **args);
    char *HelpSummary;
    char *Help;
} Command;

#define CommandInit(aliases, command, helpSummary, help) (Command){aliases, command, helpSummary, help}

const Command *FindCommand(const Command *commands, const size_t commandCount, const char *commandName);
char *GetArg(int argCount, char **args, char *flag);

#endif