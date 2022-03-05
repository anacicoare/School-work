#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void dec_to_bin(int n, char* s)
{
    int i;
    char* s1 = malloc(9 * sizeof(char));
    i = 0;
    for (i = 0; i <= 7; i++)
        s1[i] = '0';


    for (i = 0; i < 8; i++)
    {
        if (n % 2 == 0)
            s1[i] = '0';
        else
            s1[i] = '1';
        n = n / 2;
    } //in s1 stocam 8 resturi ale lui n la impartirea prin 2, in ordinea in care apar
    s1[8] = NULL;
    for (i = 7; i >= 0; i--)
        s[i] = s1[7 - i]; // oglindim sirul s1 pentru a rezulta reprezentarea binara
    free(s1);
    while (i >= 0)
    {
        s[i] = 0;
        i--;
    }
}
int bin_to_dec(char* s)
{
    int nr, i;
    nr = 0;
    for (i = 7; i >= 0; i--)
        nr = nr + (s[i] - '0') * pow(2, 7 - i);
    return nr;
}
void inmultire_matrice(int a[][8], int b[][8], int c[][8])
{
    int i, j, k;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            c[i][j] = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            for (k = 0; k < 8; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            for (k = 0; k < 8; k++)
                if (c[i][j] > 1)
                    c[i][j] = 1; // valorificam operatiile de 0 si 1 ale algebrei boolene
}
void transpusa_matrice(int a[][8], int t[][8])
{
    int i, j;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            t[i][j] = a[j][i];
}
int sum_X_0(int m[][8])
{
    int scor, ok1, ok2, ok3, ok4, i, j;
    scor = 0;
    ok3 = 1; //presupunem ca urmatoarea matrice are pe diagonala principala numai 1
    ok4 = 1; //presupunem ca urmatoarea matrice are pe diagonala secundara numai 1
    for (i = 0; i < 4; i++)
    {
        ok1 = 1; // presupunem ca avem pe linia i numai 1
        ok2 = 1; // presupunem ca avem pe linia i numai 1
        for (j = 0; j < 4; j++)
        {
            if (m[i][j] == 0)
                ok1 = 0; //am gasit un element egal cu 0 pe linia i
            if (m[j][i] == 0)
                ok2 = 0; //am gasit un element egal cu 0 pe coloana i
        }
        if (ok1 == 1)
            scor++;
        if (ok2 == 1)
            scor++;
        if (m[i][i] == 0)
            ok3 = 0; // am gasit un element egal cu 0 pe diagonala principala
        if (m[i][3 - i] == 0)
            ok4 = 0; // am gasit un element egal cu 0 pe diagonala secundara
    }
    if (ok3 == 1)
        scor++;
    if (ok4 == 1)
        scor++;


    //am facut verificarea pentru blocul de matrice A11


    ok3 = 1; //presupunem ca urmatoarea matrice are pe diagonala principala numai 1
    ok4 = 1; //presupunem ca urmatoarea matrice are pe diagonala secundara numai 1
    for (i = 0; i < 4; i++)
    {
        ok1 = 1; // presupunem ca urmatoarea matrice are pe linia i numai 1
        for (j = 4; j < 8; j++)
            if (m[i][j] == 0)
                ok1 = 0; // am gasit un element egal cu 0 pe linia i
        if (ok1 == 1)
            scor++;
        if (m[i][i + 4] == 0)
            ok3 = 0; //am gasit pe diagonala principala un element egal cu 0
        if (m[i][7 - i] == 0)
            ok4 = 0; //am gasit un element egal cu 0 pe diagonala secundara
    }
    for (i = 4; i < 8; i++)
    {
        ok2 = 1; // presupunem ca urmatoarea matrice are pe coloana i numai 1
        for (j = 0; j < 4; j++)
            if (m[j][i] == 0)
                ok2 = 0; //am gasit un element egal cu 0 pe coloana i
        if (ok2 == 1)
            scor++;
    }

    if (ok3 == 1)
        scor++;
    if (ok4 == 1)
        scor++;

    //am facut verificarea pentru blocul de matrice A12


    ok3 = 1; //presupunem ca urmatoarea matrice are pe diagonala principala numai 1
    ok4 = 1; //presupunem ca urmatoarea matrice are pe diagonala secundara numai 1
    for (i = 4; i < 8; i++)
    {
        ok1 = 1; //presupunem ca avem pe linia i numai 1
        for (j = 0; j < 4; j++)
            if (m[i][j] == 0)
                ok1 = 0; //am gasit un element egal cu 0 pe linia i
        if (ok1 == 1)
            scor++;
        if (m[i][i - 4] == 0)
            ok3 = 0; //am gasit un element egal cu 0 pe diagonala principala
        if (m[i][7 - i] == 0)
            ok4 = 0; //am gasit un element egal cu 0 pe diagonala secundara
    }
    for (i = 0; i < 4; i++)
    {
        ok2 = 1;// presupunem ca avem pe coloana i numai 1
        for (j = 4; j < 8; j++)
            if (m[j][i] == 0)
                ok2 = 0; //am gasit un element egal cu 0 pe coloana i
        if (ok2 == 1)
            scor++;
    }
    if (ok3 == 1)
        scor++;
    if (ok4 == 1)
        scor++;



    //am facut verificarea pentru blocul de matrice A21


    ok3 = 1; //presupunem ca urmatoarea matrice are pe diagonala principala numai 1
    ok4 = 1; //presupunem ca urmatoarea matrice are pe diagonala secundara numai 1
    for (i = 4; i < 8; i++)
    {
        ok1 = 1; // presupunem ca avem pe linia i numai 1
        ok2 = 1; // presupunem ca avem pe linia i numai 1
        for (j = 4; j < 8; j++)
        {
            if (m[i][j] == 0)
                ok1 = 0; //am gasit un element egal cu 0 pe linia i
            if (m[j][i] == 0)
                ok2 = 0; //am gasit un element egal cu 0 pe coloana i
        }
        if (ok1 == 1)
            scor++;
        if (ok2 == 1)
            scor++;
        if (m[i][i] == 0)
            ok3 = 0; // am gasit un element egal cu 0 pe diagonala principala
        if (m[i][11 - i] == 0)
            ok4 = 0; // am gasit un element egal cu 0 pe diagonala secundara
    }
    if (ok3 == 1)
        scor++;
    if (ok4 == 1)
        scor++;
    return scor;

    //am facut verificarea pentru blocul de matrice A22
}
int main()
{
    int a[8][8], i, j, v[8], k, a_transpus[8][8], a_patrat[8][8], produs_matrice_a_at[8][8], scor_a, scor_a_patrat, scor_produs_a_at, max1, matrice_castigatoare[8][8], nr;
    char s[9];
    for (i = 0; i < 8; i++)
        scanf("%d", &v[i]);
    for (i = 0; i < 8; i++)
    {
        k = v[i];
        dec_to_bin(k, s);
        for (j = 0; j < 8; j++)
            if (s[j] == '0')
                a[i][j] = 0;
            else
                a[i][j] = 1;

    } //am trecut inputurile pe 8 biti in matricea a


    transpusa_matrice(a, a_transpus); // am gasit transpusa matricei a
    inmultire_matrice(a, a, a_patrat); //am calculat matricea a^2
    inmultire_matrice(a, a_transpus, produs_matrice_a_at);


    scor_a = sum_X_0(a);
    scor_a_patrat = sum_X_0(a_patrat);
    scor_produs_a_at = sum_X_0(produs_matrice_a_at); //calculam scorurile fiecarei matrice
    max1 = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            matrice_castigatoare[i][j] = a[i][j];
    if (scor_a > max1)
    {
        max1 = scor_a;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++)
                matrice_castigatoare[i][j] = a[i][j];
    }
    if (scor_produs_a_at > max1)
    {
        max1 = scor_produs_a_at;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++)
                matrice_castigatoare[i][j] = produs_matrice_a_at[i][j];
    }
    if (scor_a_patrat > max1)
    {
        max1 = scor_a_patrat;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++)
                matrice_castigatoare[i][j] = a_patrat[i][j];
    }

    //am calculat scorul maxim in max1 si matricea cu scorul respectiv

    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
            if (matrice_castigatoare[j][i] == 1)
                s[i] = '1';
            else
                s[i] = '0';
        s[8] = NULL;
        nr = bin_to_dec(s);
        printf("%d\n", nr);
    } //am transformat in decimal

    return 0;
}