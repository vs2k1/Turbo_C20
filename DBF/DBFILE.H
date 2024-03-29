
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
  unsigned char           inblock[SIZE_BLK];
  };
union DBF_DES_BUF
  {
  struct DBF_DESCRIPTOR 	        ou1;
  unsigned char           inblock[SIZE_BLK];
  };
