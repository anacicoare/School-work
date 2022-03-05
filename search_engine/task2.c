#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int main()
{
	site* site_web;
	char  input_vector[255], * word, * content;
	int aparitii[30],i,n;

	site_web = (struct site*)malloc(3 * sizeof(site)); // dynamically allocating memory for the database
	upload_database(site_web);

	n = number_of_sites();
	gets(input_vector);
	
	word = strtok(input_vector, " ");
	int size_aparitii = 0; //nu avem niciun element in aparitii, unde vom stoca numarul site-urilor care contin cuvinte
	
	while (word != NULL) //cat timp nu am analizat toate cuvintele
	{
		for (i = 0; i < n; i++)
		{
			content = malloc(strlen((site_web + i)->content) * sizeof(char) + 1);
			
			strcpy(content, (site_web + i)->content); //facem o copie a continutului site-ului i

			if (check_word_in_string(content, word)) //verificam daca apare cuvantul in site
				if (!site_exists(site_web,i,aparitii,size_aparitii))
				{
					aparitii[size_aparitii] = i; //notam site-ul care contine cuvantul
					size_aparitii++;
				}
			
			free(content);
		}

		word = strtok(NULL, " "); //analizam urmatorul cuvant
	}

	int (*cmp[2])(char*, char*) = { cmp_crescator,cmp_descrescator }; //definim pointeri la functii
	ordonare(site_web, aparitii, size_aparitii, cmp[0]);

	for (i = 0; i < size_aparitii; i++)
		printf("%s\n", (site_web + aparitii[i])->url);

	free_database(site_web, n);
	free(word);
	
	return 0;
}