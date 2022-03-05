#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_anagram(char* s1, char* s2)
{
    int n1, n2, i, j, fr1[123], fr2[123], k;
    n1 = strlen(s1); //lungimea primului sir
    n2 = strlen(s2); //lungimea celui de-al doilea sir
    for (i = 97; i <= 122; i++)
    {
        fr1[i] = 0; //nicio litera nu apare pana acum in primul sir
        fr2[i] = 0; //nicio litera nu apare pana acum in al doilea sir
    }

    if (n1 == n2) //daca au aceeasi lungime
    {
        for (i = 0; i < n1; i++)
        {
            fr1[s1[i]]++;
            fr2[s2[i]]++;

        }
        for (k = 0; k < n1; k++)
        {
            if (fr1[s2[k]] == 0)
                return 0; //daca o litera din cel de-al doilea sir nu apare in prima, atunci nu sunt anagrame
            if (fr2[s1[k]] == 0)
                return 0; //daca o litera din cel de-al doilea sir nu apare in prima, atunci nu sunt anagrame
        }
        for (i = 0; i < n1; i++)
            for (j = 0; j < n1; j++)
            {
                if (s1[i] == s2[j] && fr1[s1[i]] != fr2[s2[j]]) //daca aceeasi litera nu apare de tot atatea ori in cele 2 cuvinte

                    return 0;
            }
    }
    else
        return 0;
    return 1; //daca nu am primit return 0 pana acum inseamna ca totul a decurs corect, deci sunt anagrame
}
double compute_grade(char* s1, char* s2)
{
    int i;
    double p, nr, n1;
    if (is_anagram(s1, s2) == 1)
    {
        nr = 0; //numarul de litere diferite pe acelasi indice
        n1 = strlen(s1);
        for (i = 0; i < n1; i++)
            if (s1[i] != s2[i])
                nr++; //literele difera
        p = nr / n1; //calculam procentul
        return p;
    }
    else
        return -1;
}
int main()
{
    char s1[1000], s2[1000], cuv1[1000][50], cuv2[1000][50], aux1[50];
    int i, n, j, k, inceput_secventa, sfarsit_secventa;
    double grad[2];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%s", &cuv1[i]);
        scanf("%s", &cuv2[i]);
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (compute_grade(cuv1[i], cuv2[i]) > compute_grade(cuv1[j], cuv2[j]))
            {
                strcpy(aux1, cuv1[i]);
                strcpy(cuv1[i], cuv1[j]);
                strcpy(cuv1[j], aux1);
                strcpy(aux1, cuv2[i]);
                strcpy(cuv2[i], cuv2[j]);
                strcpy(cuv2[j], aux1);
            }                         //ordonam descrescator perechile dupa grad
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (compute_grade(cuv1[i], cuv2[i]) == compute_grade(cuv1[j], cuv2[j]))
                if (strcmp(cuv1[i], cuv1[j]) > 0)
                {
                    strcpy(aux1, cuv1[i]);
                    strcpy(cuv1[i], cuv1[j]);
                    strcpy(cuv1[j], aux1);
                    strcpy(aux1, cuv2[i]);
                    strcpy(cuv2[i], cuv2[j]);
                    strcpy(cuv2[j], aux1);
                }
    //ordonam lexico-gramatical cuvintele cu acelasi grad

    for (i = 0; i < n; i++)
        printf("%s %s\n", cuv1[i], cuv2[i]);
    return 0;
}