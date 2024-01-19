
/*
   �������������������������� ��������� 䠩��
   �              ���������������������������� ���ਯ���
   �              �                        �
   �              �                        �          ���� ��ନ�����
   �              �                        �          �   ���� ASCII 10
   �              �                        �          �
������������Ŀ������������Ŀ���Ŀ ���Ŀ������������Ŀ�Ŀ����Ŀ����Ŀ
�            ��            ��   ����  ��            �� ��    ��    �
���������������������������������� ���������������������������������
   32 ����      32 ����                  32 ����
<�����������>  <����������>             <����������>      �      �
		���ᨬ��쭮� �᫮ ���ਯ. 255		  �      �
	       <�����������������������������������>      �      �
							  �      �
			      �����			  �      �
			      ������������������������������������
*/

#define 	MAX_DES		255
#define		SIZE_BLK	32

struct F_BUTE
{
 int version	: 3;			/* ����� ���ᨨ */
 int f_dbt 	: 1;			/* ���� DBT � dBASE IV */
 int		: 1;			/* ??? */
 int f_sql 	: 2;			/* ���� SQL */
 int memo	: 1;			/* ������祭�� MEMO 䠩�� */
};

struct DBF_HEADER
{
  struct F_BUTE		h_0;		/* 0 �㫥��� ���� */
  unsigned char		date[3];	/* 1..3 ��� ��᫥����� ���������� */
  unsigned long int 	count;		/* 4..7 ���稪 ����ᥩ */
  unsigned int		hdr_lenth;	/* 8..9 ����� ��������� � ����.����� */
  unsigned int		rec_lenth;	/* 10..11 ����� ����� 䠩�� */
  unsigned char		reserved1[2];	/* 12..13 ��१�ࢨ஢��� */
  unsigned char		tranz;          /* 14 ����প� �� �࠭���樨 */
  unsigned char		reserved2[13];	/* 15..27 ��१�ࢨ஢��� */
  unsigned char		index_MDX;	/* 28 ������祭 MDX dBASE IV */
  unsigned char		reserved3[3];	/* 29..31 ��१�ࢨ஢��� */
};

struct DBF_DESCRIPTOR
{
  char			fild_name[11];	/* 0..10 ��� ���� */
  char			fild_type;	/* 11 ⨯ ���� C,L,N,M,F */
  unsigned char		reserved1[4];	/* 12..15 ��१�ࢨ஢��� */
  unsigned char		fild_lenth;	/* 16 ����� ���� */
  unsigned char		fild_point;	/* 17 �᫮ �������� ࠧ�冷� */
  unsigned char         reserved2[13];	/* 18..30 ��१�ࢨ஢��� */
  unsigned char		teg;		/* 䫠� ⥣� MDX � dBASE IV 0-1 */
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