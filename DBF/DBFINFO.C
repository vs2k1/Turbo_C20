#include <stdio.h>
#include <conio.h>
#include <alloc.h>

/*
   ┌───────────────────────── Заголовок файла
   │              ┌────────────────────────┬── Дескрипторы
   │              │                        │
   │              │                        │          ┌─── Терминальный
   │              │                        │          │   байт ASCII 10
   │              │                        │          │
┌────────────┐┌────────────┐┌───┐ ┌───┐┌────────────┐┌─┐┌────┐┌────┐
│            ││            ││   └┐└┐  ││            ││ ││    ││    │
└────────────┘└────────────┘└────┘ └──┘└────────────┘└─┘└────┘└────┘
   32 байта      32 байта                  32 байта
<───────────>  <──────────>             <──────────>      │      │
		Максимальное число дескрип. 255		  │      │
	       <───────────────────────────────────>      │      │
							  │      │
			      Записи			  │      │
			      ────────────────────────────┴──────┘
*/

#define 	MAX_DES		255
#define		SIZE_BLK	32

struct F_BUTE
{
 int version	: 3;			/* Номер версии */
 int f_dbt 	: 1;			/* Файл DBT в dBASE IV */
 int		: 1;			/* ??? */
 int f_sql 	: 2;			/* Флаг SQL */
 int memo	: 1;			/* Подключение MEMO файла */
};

struct DBF_HEADER
{
  struct F_BUTE		h_0;		/* 0 нулевой байт */
  unsigned char		date[3];	/* 1..3 дата последнего обновления */
  unsigned long int 	count;		/* 4..7 счетчик записей */
  unsigned int		hdr_lenth;	/* 8..9 длина заголовка и дискр.полей */
  unsigned int		rec_lenth;	/* 10..11 длина записи файла */
  unsigned char		reserved1[2];	/* 12..13 зарезервировано */
  unsigned char		tranz;          /* 14 задержка по транзакции */
  unsigned char		reserved2[13];	/* 15..27 зарезервировано */
  unsigned char		index_MDX;	/* 28 подключен MDX dBASE IV */
  unsigned char		reserved3[3];	/* 29..31 зарезервировано */
};

struct DBF_DESCRIPTOR
{
  char			fild_name[11];	/* 0..10 имя поля */
  char			fild_type;	/* 11 тип поля C,L,N,M,F */
  unsigned char		reserved1[4];	/* 12..15 зарезервировано */
  unsigned char		fild_lenth;	/* 16 длина поля */
  unsigned char		fild_point;	/* 17 число десятичных разрядов */
  unsigned char         reserved2[13];	/* 18..30 зарезервировано */
  unsigned char		teg;		/* флаг тега MDX в dBASE IV 0-1 */
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

    printf("\n\n  Версия - %u",header.ou.h_0.version);
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
      printf("\n  Число столбцов - %d  ",j_max);
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