
anagrams.c : O anagrama a lui A este orice sir care contine exact aceleasi caractere ca A, cu acelasi numar de
aparitii, dar intr-o ordine diferita.In continuare, vom defini o marime cu ajutorul careia vom putea masura cat de
”puternica” este o anagrama. Gradul unei anagrame este un numar real cuprins
in intervalul [0, 1], care se refera la procentul de caractere care difera intre cele
doua cuvinte raportat la numarul total de caractere. In cazul in care doua cuvinte
nu sunt anagrame, le vom atribui gradul -1.

 Pentru anagrams.c am facut o functie pentru a verifica daca 2 cuvinte sunt anagrame astfel:
- Am initializat numarul de dati de care apare fiecare cifra in fiecare cuvant pentru a le putea compara ulterior.
- Daca cele 2 cuvinte au acelasi numar de litere este posibil sa fie anagrame.
- Ele sunt anagrame daca si numai daca fiecare litera apare de acelasi numar de ori si sunt construite cu aceleasi cifre

Odata ce am stabilit daca sunt anagrame, am facut o functie pentru a determina procentul am parcurs fiecare sir si am facut o comparatie 1-la-1

In rezolvarea propriu-zisa a problemei am ordonat cuvintele dupa grad, iar mai apoi am mai parcurs o data sirul pentru a le ordona alfabetic.



chess_checker.c :	1. O functie care afiseaza numarul de perechi de nebuni care se ataca
reciproc.
			2. Daca tabla de sah contine o singura pereche de nebuni care se ataca, atunci
sa se determine daca se poate muta unul dintre ei astfel incat sa nu mai existe
nicio pereche de nebuni care sa se atace. Daca nu exista nicio posibilitate de
mutare pentru niciunul dintre cei doi nebuni sau daca pe tabla nu exista doar
o singura pereche de astfel de nebuni, se va aflsa ”NU”. Altfel, se va afisa
”DA”.

Pentru chess_checker.c, inainte de rezolvare am creat cateva functii:
- creare_tabla_sah : care initializeaza o tabla goala de sah, fara nebuni
- numar_perechi_nebuni_pozitie_data  : - calculeaza cati oponenti are un nebun a carui pozitie (linie,coloana) o cunoastem
 				      - calculam de pe fiecare "jumatate de diagonala" - dreapta jos, dreapta sus, stanga jos, stanga sus
- numar_perechi: calculeaza suma de numar_perechi_nebuni_pozitie_data pentru fiecare nebun
- posibilitate: verifica daca exista posibilitatea de a muta unul dintre cei 2 nebuni care se ataca pentru a evita acest lucru
 
In functia propriu-zisa :
- am initializat tabla goala de sah
- am adaugat nebunii(am citit pozitiile acestora si le-am retinut in 2 vectori de coordonate)
- am calculat numarul total de nebuni care se ataca
* daca acesta era diferit de 1 atunci raspunsul este NU, din enuntul problemei
* daca acesta era egal cu 1 atunci cautam posibilitatea de a muta unul dintre cei 2 nebuni, folosind functia posibilitate


X & 0 : Se dau 8 numere de la tastatura care se scriu in baza 2 sub forma unei matrice de 8 x 8.
	  Se "sparge" matricea in 8 blocuri si se calculeaza scorul pe fiecare bloc.
	  Scorul pe fiecare bloc = linii_de_1 + coloane_de_1 + diagonale_de_1.
	  Scor total = suma scorurilor de pe fiecare bloc.
	  Se calculeaza scorurile pe matricele A, A*A si At si se afiseaza cel mai mare. 

 Pentru X & 0, inainte de rezolvare am creat cateva functii:
- dec_to_bin - transforma un numar in baza 2
- bin_to_dec - transforma un numar din baza 2 in baza 10
- inmultire_matrice - calculeaza produsul a 2 matrice, valorificam operatiile algebrei boolene
- transpusa_matrice - calculeaza transpusa unei matrice
- sum_X_0 : calculeaza scorul de X si 0 al unei matrice, calculand individual pentru fiecare bloc: A11(stanga sus), A12(dreapta sus), A21(stanga jos)
A22(dreapta jos)

In functia propriu-zisa:
- am realizat matricea conform enuntului, am trecut numarul in baza 2, iar mai apoi intr-o matrice
- am calculat A transpus, A^2, produsul matricelor A si A transpus 
- am comparat scorurie matricelor intre ele si am selectat-o pe cea cu scorul cel mai mare
- in cazul in care toate au acelasi scor am ales matricea A
- pentru matricea castigatoare am inversat  procedeul de la inceputul problemei, am trecut liniile acesteia inapoi in baza 10

 