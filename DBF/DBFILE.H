
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
  unsigned char           inblock[SIZE_BLK];
  };
union DBF_DES_BUF
  {
  struct DBF_DESCRIPTOR 	        ou1;
  unsigned char           inblock[SIZE_BLK];
  };
