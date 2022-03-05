#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int main()
{
	site* site_web;
	int nr_caractere, j, ok, copie_checksum, copie_indice, exista_site_input, nr_litere_input, aparitii[30], i, n;;
	long* checksum;
	char input_line[255], * site_name, input_vector[255], * word, * content, * copie_input, * input_vector_cuvinte;

	site_web = (struct site*)malloc(3 * sizeof(site)); // dynamically allocating memory for the database
	upload_database(site_web);
	n = number_of_sites();
	
	exista_site_input = 0;
	
	while (fgets(input_line, 100, stdin)) //cat timp exista sir input
	{
		if (input_line[0] == '\n') //cand sirul introdus este tasta ENTER, se va opri cautarea
			break;
		
		nr_litere_input = strlen(input_line);
		input_line[nr_litere_input - 1] = '\0';
		nr_litere_input--;
		//punem url-ul site-ului de analizat in input_line

		exista_site_input = 1;
		checksum = calloc((n + 1), sizeof(long)); //alocam dinamic checksum-ul siteului

		site_name = strtok(input_line, " ");
		while (site_name != NULL)
		{
			ok = 0; //nu am gasit site-ul in baza de date pana acum
			for (i = 0; i < n; i++)
				if (strcmp(site_name, (site_web + i)->url) == 0) // daca site-ul se gaseste in baza de date
				{
					ok = 1;
					copie_checksum = calculate_checksum(site_web, i);
					copie_indice = i;

				} //calculam checksum-ul site-ului 
			if (ok == 1) //pentru site-ul care trb analizat
			{
				if (copie_checksum == char_to_int((site_web + copie_indice)->checksum))
					printf("Website safe!\n");
				else
					printf("Malicious website! Official key: %s. Found key: %d\n", (site_web + copie_indice)->checksum, copie_checksum);
			}
			else
				printf("Website not found!\n"); //output-ul
			site_name = strtok(NULL, " ");
		}
		free(checksum);
		free(site_name);
	}
	free_database(site_web, n);
	
	return 0;
}