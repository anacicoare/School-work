#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void creare_tabla_sah(int a[][100], int N, int M, int x[], int y[])
{
    int i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < M; j++)
            a[i][j] = 0;
    for (i = 0; i < N; i++)
        a[x[i]][y[i]] = 1;
}
int numar_perechi_nebun_pozitie_data(int a[][100], int M, int i, int j)
{
    int nr, copie_linie, copie_coloana, linie, coloana, ok;
    nr = 0;
    copie_linie = i;
    copie_coloana = j;
    linie = copie_linie + 1;
    coloana = copie_coloana + 1;
    ok = 0; //presupunem ca nebunul nu are pereche
    while (linie >= 0 && linie < M && coloana >= 0 && coloana < M)
    {
        if (a[linie][coloana] == 1)
        {
            ok = 1;
            nr++;
        } //cautam nebun pe partea dreapta jos de diagonala
        linie++;
        coloana++;
    }
    copie_linie = i;
    copie_coloana = j;
    linie = copie_linie - 1;
    coloana = copie_coloana + 1;
    while (linie >= 0 && linie < M && coloana >= 0 && coloana < M)
    {
        if (a[linie][coloana] == 1)
        {
            ok = 1;
            nr++;
        } //cautam nebun pe partea de dreapta sus de diagonala
        linie--;
        coloana++;
    }
    copie_linie = i;
    copie_coloana = j;
    linie = copie_linie + 1;
    coloana = copie_coloana - 1;
    while (linie >= 0 && linie < M && coloana >= 0 && coloana < M)
    {
        if (a[linie][coloana] == 1)
        {
            ok = 1;
            nr++;
        } //cautam nebun pe partea de stanga jos de diagonala
        linie++;
        coloana--;
    }
    copie_linie = i;
    copie_coloana = j;
    linie = copie_linie - 1;
    coloana = copie_coloana - 1;
    while (linie >= 0 && linie < M && coloana >= 0 && coloana < M)
    {
        if (a[linie][coloana] == 1)
        {
            ok = 1;
            nr++;
        } //cautam nebun pe partea de stanga sus de diagonala
        linie--;
        coloana--;
    }
    return nr;
}
int numar_perechi(int a[][100], int M, int N, int x[], int y[])
{
    int i, j, nr, linie, coloana, ok, k;
    nr = 0; //numarul de perechi de nebuni
    for (i = 0; i < N; i++) //vom cauta numarul de perechi pe care il are nebunul de pe pozitia (x[i],y[i])
    {
        k = numar_perechi_nebun_pozitie_data(a, M, x[i], y[i]);
        nr = nr + k;
        a[x[i]][y[i]] = 0;
    }
    creare_tabla_sah(a, N, M, x, y); //refacem tabla de sah
    return nr;
}
int posibilitate(int a[][100], int M, int N, int x[], int y[])
{
    int ok, i, j, copie_linie, copie_coloana, t, nr;
    ok = 0; //presupunem ca nu exista nicio posibilitate de a muta nebunul
    for (t = 0; t < N; t++) //pentru toate pozitiile pe care se afla un nebun
    {
        copie_linie = x[t];
        copie_coloana = y[t]; //linia si coloana pe care se afla nebunul pe care il analizam
        if (numar_perechi_nebun_pozitie_data(a, M, x[t], y[t]) == 1) // daca analizam nebunul care se ataca cu un singur alt nebun
        {
            a[x[t]][y[t]] = 0; //luam nebunul de pe tabla de sah pentru a-i cauta pozitia necesara
            for (i = 0; i < M; i++)
                for (j = 0; j < M; j++)
                {
                    if (a[i][j] != 1 && x[t] != i && y[t] != j) //daca ne aflam pe o pozitie pe care nu este un nebun, pe pozitia pe care nu era nebunul inainte de a-l ridica
                    {
                        a[i][j] = 1; //asezam nebunul in pozitia respectiva
                        nr = numar_perechi_nebun_pozitie_data(a, M, i, j);
                        if (nr == 0)
                        {
                            ok = 1; //am gasit o posibilitate de a muta nebunul
                            return 1;
                        }
                    }
                }
            a[copie_linie][copie_coloana] = 1; //nu am gasit o pozitie in care sa nu se atace cu alti nebuni, deci l-am pus la loc
        }
    }
    return 0;

}
int main()

{
    int M, x[100], y[100], i, j, a[100][100], N, nr, t;
    scanf("%d", &M);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &x[i]);
        scanf("%d", &y[i]);
    } // perechea (x[i],y[i]) va reprezenta perechea (linie,coloana) pe care se afla un nebun
    creare_tabla_sah(a, N, M, x, y);
    nr = numar_perechi(a, M, N, x, y);
    printf("%d\n", nr);
    creare_tabla_sah(a, N, M, x, y);

    if (nr == 1)
    {
        t = posibilitate(a, M, N, x, y);
        if (t == 0)
            printf("NU\n");
        else
            printf("DA\n");
    }
    else
        printf("NU\n");
    return 0;
}