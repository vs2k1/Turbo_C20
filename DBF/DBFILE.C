#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include "dbfile.h"

main( int narg, char *argv[] )
{
 FILE *fin;
 int i=1,
     j=0,
     j_max=0;
 unsigned int pocket;
 unsigned long	*addrdescriptor[MAX_DES];
 union DBF_HDR_BUF                header;
 union DBF_DES_BUF           *descriptor;

 if (narg > 1)
  {
  fin  = fopen (argv[1],"rb");
  if (fin != 0)
    {
    for (i=0; i < SIZE_BLK; i++)(fscanf(fin,"%c",&header.inblock[i]));
/*
    header.ou.h_0.version
    header.ou.h_0.f_dbt
    header.ou.h_0.f_sql
    header.ou.h_0.memo
    header.ou.date[2],header.ou.date[1],header.ou.date[0]
    header.ou.count
    header.ou.hdr_lenth
    header.ou.rec_lenth
    header.ou.tranz
    header.ou.index_MDX
*/
    while ( !feof(fin) )
      {
       j_max=j-1;		/* —¨α«® αβ®«΅ζ®Ά */
       pocket=fgetc(fin);
       ungetc(pocket,fin);
       if (pocket==13)
		break;
       descriptor = malloc(sizeof(char)*SIZE_BLK);
       (long*)addrdescriptor[j++] =(long*)descriptor;

       for (i=0; i < SIZE_BLK; i++)
		(fscanf(fin,"%c",&(descriptor->inblock[i])));
      } /*end while*/
/*
	 (long*)descriptor=(long*)addrdescriptor[j];
*/
    fcloseall ();

    }
  else
   printf("\nFile not found");
  }
}
