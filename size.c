#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){
	
	FILE *fp;
	
	fp=fopen("image.svg","w+");
	
	int arr1[10],i,x[10],y[10];
	float font[10];
		
	char **array=malloc(sizeof(char*)*10);
	
	
	for(i=0;i<10;i++)array[i]=malloc(sizeof(char)*256);/*define the 2D array for store a string*/ 
	 
	for(i=0;i<10;i++){
		scanf("%s %d",array[i],&arr1[i]);/*get the inputs*/
		
	}
	fprintf(fp,"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"768\" width=\"1028\">\n");
	fprintf(fp," <title>TAG CLOUD</title>\n");	
	for(i=0;i<10;i++){
		
		x[i]=rand()%1024;/*generate x and y cordinates*/
		y[i]=rand()%768;
		font[i]=(double)((40.0*(arr1[i]-arr1[0]))/(arr1[9]-arr1[0]))+10.0;/*calculate the font size*/
		
		fprintf(fp,"<text x=\"%d\" y=\"%d\" font-size=\"%f\" >%s</text>\n",x[i],y[i],font[i],array[i]);
		
			
		}	
		
	fprintf(fp,"<rect x=\"0\" y=\"0\" height=\"768\" width=\"1028\"\n"); 
	fprintf(fp,"fill=\"none\" stroke=\"blue\" stroke-width=\"3\" />\n");
	fprintf(fp,"</svg>\n");
	
	fclose(fp);		
	return 0;	
	}
