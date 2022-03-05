#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int main()
{
	FILE* f;
	int i, n, nr_litere;
	char file_name[30][30], s[80], * p, * cod_html1, * cod_html2;
	site* site_web;

	site_web = (struct site*)malloc(3 * sizeof(site)); // dynamically allocating memory for the database
	allocate_memory_for_sites(site_web,file_name);
	
	n = number_of_sites();

	for (i = 0; i < n; i++)
		upload_site_to_database(site_web, file_name, i);	

	for (i = 0; i < n; i++)
		printf("%s %s %s\n", (site_web + i)->url, (site_web + i)->nr_access, (site_web + i)->title);

	for (i = 0; i < n; i++) 
		upload_colors_to_sites(site_web, i);

	free_database(site_web, n);
	
	return 0;
}