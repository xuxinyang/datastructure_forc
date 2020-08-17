#include <stdio.h>

int Fbinacci(int i)
{
    if (i < 2)
    {
        return (i == 0) ? 0 : 1;
    }
    else
    {
        return Fbinacci(i-1) + Fbinacci(i-2);
    }
}

int main(int argc, char const *argv[])
{
    int i;
    for(int i = 0; i < 40; i++)
    {
        printf("%d\n", Fbinacci(i));
    }
    return 0;
}