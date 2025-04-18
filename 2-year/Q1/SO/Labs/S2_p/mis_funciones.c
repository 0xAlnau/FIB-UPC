#include<stdbool.h>
#include<string.h>
int MAX_SIZE = 8;

bool Usage(const int argc)
{
    return argc >= 2;
}

int esNumero (char *str) {
    int tamanio = strlen (str);
    int resposta = 1;

    if ((str == NULL || tamanio > MAX_SIZE) && str[0] != '-')
        resposta = 0;
    else
    {
        if (str[0] == '-' || (str[0] >= '0' && str[0] <= '9'))
        {
            for (int i = 1; i < tamanio; ++i)
            {
                if ((str[i] < '0' || str[i] > '9'))
                    resposta = 0;
            }
        }
        else
            resposta = 0;
    }
    return resposta;
}

unsigned int char2int(char c) {
    unsigned int result = c - '0';
    return result;
}

int mi_atoi(char *s) {
    int resultat = 0, multiplicador = 1, tamanio = strlen(s);

    for (int i = tamanio-1; i >= 0; --i) {
        if (s[i] == '-') resultat = -1 * resultat;
        else resultat = resultat + char2int(s[i]) * multiplicador;
        multiplicador = multiplicador * 10;
    }
    return resultat;
}
