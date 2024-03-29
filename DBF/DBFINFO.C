#include <stdio.h>
#include <conio.h>
#include <alloc.h>

/*
   旼컴컴컴컴컴컴컴컴컴컴컴컴 뇿．ギ¡� �젵쳽
   �              旼컴컴컴컴컴컴컴컴컴컴컴컫컴 꽖稅黍�獸贍
   �              �                        �
   �              �                        �          旼컴 뮙席Þ젷彛硫
   �              �                        �          �   줎⒱ ASCII 10
   �              �                        �          �
旼컴컴컴컴컴커旼컴컴컴컴컴커旼컴� 旼컴왯컴컴컴컴컴컴왯커旼컴커旼컴커
�            납            납   읏읏  납            납 납    납    �
읕컴컴컴컴컴켸읕컴컴컴컴컴켸읕컴켸 읕켸읕컴컴컴컴컴켸읕牡컴컴牡컴컴�
   32 줎⒱�      32 줎⒱�                  32 줎⒱�
<컴컴컴컴컴�>  <컴컴컴컴컴>             <컴컴컴컴컴>      �      �
		뙛めº젷彛�� 葉笹� ㄵ稅黍�. 255		  �      �
	       <컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�>      �      �
							  �      �
			      뇿�ⓤ�			  �      �
			      컴컴컴컴컴컴컴컴컴컴컴컴컴컴좔컴컴켸
*/

#define 	MAX_DES		255
#define		SIZE_BLK	32

struct F_BUTE
{
 int version	: 3;			/* 뜮Д� ´褻Ŀ */
 int f_dbt 	: 1;			/* 뵠œ DBT � dBASE IV */
 int		: 1;			/* ??? */
 int f_sql 	: 2;			/* 뵭젫 SQL */
 int memo	: 1;			/* 룼ㄺヮ曄��� MEMO �젵쳽 */
};

struct DBF_HEADER
{
  struct F_BUTE		h_0;		/* 0 �乘ⅱ�� 줎⒱ */
  unsigned char		date[3];	/* 1..3 쩆�� ��笹ⅳ�ⅲ� �∼�˙��⑨ */
  unsigned long int 	count;		/* 4..7 淞β葉� 쭬�ⓤⅸ */
  unsigned int		hdr_lenth;	/* 8..9 ㄻÞ� 쭬．ギ˚� � ㄸ稅�.��ゥ� */
  unsigned int		rec_lenth;	/* 10..11 ㄻÞ� 쭬�ⓤ� �젵쳽 */
  unsigned char		reserved1[2];	/* 12..13 쭬誓㎘舒ⓣ�쥯�� */
  unsigned char		tranz;          /* 14 쭬ㄵ逝첓 �� 循젺쭬ゆĿ */
  unsigned char		reserved2[13];	/* 15..27 쭬誓㎘舒ⓣ�쥯�� */
  unsigned char		index_MDX;	/* 28 ��ㄺヮ曄� MDX dBASE IV */
  unsigned char		reserved3[3];	/* 29..31 쭬誓㎘舒ⓣ�쥯�� */
};

struct DBF_DESCRIPTOR
{
  char			fild_name[11];	/* 0..10 º� ��ワ */
  char			fild_type;	/* 11 殊� ��ワ C,L,N,M,F */
  unsigned char		reserved1[4];	/* 12..15 쭬誓㎘舒ⓣ�쥯�� */
  unsigned char		fild_lenth;	/* 16 ㄻÞ� ��ワ */
  unsigned char		fild_point;	/* 17 葉笹� ㄵ碎殊嶺音 �젳涉ㄾ� */
  unsigned char         reserved2[13];	/* 18..30 쭬誓㎘舒ⓣ�쥯�� */
  unsigned char		teg;		/* 氏젫 收짛 MDX � dBASE IV 0-1 */
};
union DBF_HDR_BUF
  {
  struct DBF_HEADER                      ou;
  struct DBF_DESCRIPTOR                 ou1;
  unsigned char           inblock[SIZE_BLK];
  };
union DBF_DES_BUF
  {
  struct DBF_DESCRIPTOR 	        ou1;
  unsigned char           inblock[SIZE_BLK];
  };

main( int narg, char *argv[] )
{
 FILE *fin;
 int x=0,
     y=0,
     i=1,
     j=0,
     j_max;
 unsigned int pocket;
 unsigned long	*addrdescriptor[MAX_DES];
 union DBF_HDR_BUF                header;
 union DBF_DES_BUF           *descriptor;

 clrscr();
 if (narg > 1)
  {
  fin  = fopen (argv[1],"rb");
  if (fin != 0)
    {
    for (i=0; i < SIZE_BLK; i++)(fscanf(fin,"%c",&header.inblock[i]));

    printf("\n\n  궏褻⑨ - %u",header.ou.h_0.version);
    printf("\n  DBT    - %u",header.ou.h_0.f_dbt);
    printf("\n  SQL    - %u",header.ou.h_0.f_sql);
    printf("\n  Memo   - %u",header.ou.h_0.memo);
    printf("\n  Data   - %d-%d-%d",header.ou.date[2],header.ou.date[1],header.ou.date[0]);
    printf("\n  Count  - %ld",header.ou.count);
    printf("\n  HdrLn  - %u",header.ou.hdr_lenth);
    printf("\n  ReLn   - %u",header.ou.rec_lenth);
    printf("\n  Tranz  - %u",header.ou.tranz);
    printf("\n  MDX    - %u",header.ou.index_MDX);

    while ( !feof(fin) )
      {
       j_max=j-1;
       pocket=fgetc(fin);
       ungetc(pocket,fin);
       if (pocket==13)
		break;
       descriptor = malloc(sizeof(char)*SIZE_BLK);
       (long*)addrdescriptor[j++] =(long*)descriptor;

       for (i=0; i < SIZE_BLK; i++)
		(fscanf(fin,"%c",&(descriptor->inblock[i])));

/*     printf("\na      - %d",  a);
       printf("\naddr   - %u",  addrdescriptor[j]);
       printf("\nFldNm  - %s",  descriptor->ou1.fild_name);
       printf("\nType   - .%c.",descriptor->ou1.fild_type);
       printf("\nFldLn  - %u",  descriptor->ou1.fild_lenth);
       printf("\nFldPo  - %u",  descriptor->ou1.fild_point);
       printf("\nTeg    - %u",  descriptor->ou1.teg);
*/
      } /*end while*/
/*    getch();
      for (j=0; j <= j_max; j++)(printf("\nj = %u",addrdescriptor[j]));
      getch();
*/
      printf("\n\n\n***********************");
      printf("\n  뿨笹� 飡�ァ餘� - %d  ",j_max);
      printf("\n***********************");
      gotoxy(32,1);
      printf("N  Field Name      Type  Width  Dec    Teg");
      gotoxy(32,2);
      printf("==========================================");
      window(32,3,79,25);
      clrscr();
      for (j=0,x=1,y=1; j <= j_max; j++)
       {
	 (long*)descriptor=(long*)addrdescriptor[j];
	 gotoxy(x,y); cprintf("%d", j);
	 gotoxy(x+4,y);cprintf("%s",descriptor->ou1.fild_name);
	 gotoxy(x+20,y);cprintf(".%c.",descriptor->ou1.fild_type);
	 gotoxy(x+26,y);cprintf("%u",descriptor->ou1.fild_lenth);
	 gotoxy(x+33,y);cprintf("%u",descriptor->ou1.fild_point);
	 gotoxy(x+40,y);cprintf("%u",descriptor->ou1.teg);
	 y++;
	 if ((y%22)==0)
	  {
	   gotoxy(x,y);
	   cprintf("\nPress any key to continue");
	   y=1;
	   getch();
	   clrscr();
	  }
       }
    fcloseall ();
    getch();

    }
  else
   printf("\nFile not found");
  }
}
