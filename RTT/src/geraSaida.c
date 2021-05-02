#include <stdio.h>
#include <stdlib.h>

#include "../headers/item.h"

void escreveArquivo(Item* rtt_inflado, int len, char* path_arquivo)
{
    qsort(rtt_inflado, len, sizeof(Item), &compare_item);
    FILE* fp = fopen(path_arquivo, "w");
    for(int i=0; i<len; i++)
    {
        fprintf(fp, "%d %d %.16lf\n", rtt_inflado[i].from, rtt_inflado[i].id, rtt_inflado[i].value);
    }
    fclose(fp);
}


/*
                                            .-.   _                __
                                                `  )`'-,`\        .-''``.-'
                                _.-''-.      _.'       `'--._.' ,-'  /
                                `\    _`'--'`                      .'
                                    '._ _`-       .--.   .--.      (`
                                        `.'       /    '.'    \      '.
                                    .'         \  0  |  0  /        '.
                                    /   _        '._.---._.'      _    \
                                    /    `'-.      (     )    .-'`     \
                                    / .---'_.   .   `-,-`  .  ._'---.  \
                                    |   -'`   .       |      .  `'-    |
                                    /_       .   '   /;\  '    .     ,_\
                                        '-.     '-..-`( ' )`-..-'     /
                                        '._         '-'         _.'
                                    jgs    '-..,__       __,..-'
                                                    `'---'`

*/