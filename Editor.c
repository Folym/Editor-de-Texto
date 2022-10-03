#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "TADListaEncadeada.h"

void Aparencia(ListaLin **InicioPag ,PosicaoCur posCur)
{
	int i=1;
	gotoxy(2,2); printf("F2-Abrir");
	gotoxy(13,2); printf("F3-Salvar");
	gotoxy(24,2); printf("F4-Sair");
	gotoxy(34,2); printf("F5-Exibir");
	gotoxy(1,4);
	while(i<=81)
	{
		printf("-");
		i++;
	}
	exibLinhas(*InicioPag,posCur);
	gotoxy(1,29);
	i=1;
	while(i<=81)
	{
		printf("-");
		i++;
	}
	gotoxy(2,31); printf("COL=%d,",posCur.col);
	gotoxy(11,31); printf("LIN=%d,",posCur.lin);
	gotoxy(19,31); printf("||||");
	//PALAVRA LISTAGEN
}

void LerArquivo(ListaLin **Linha,ListaCar **cursor,PosicaoCur *posCur, char nom[15])
{
	FILE *arq;
	char car;
	strcat(nom,".txt");
	arq = fopen(nom,"r+");
	if(arq==NULL)
		printf("Arquivo não encontrado\n");
	else
	{
		while(!feof(arq))
		{
			car = fgetc(arq);
			if(car!='\n')
				insereCar(&(*Linha),&(*(cursor)),car,&(*posCur));
			else
			{
				insereProxL(&(*Linha));
				(*Linha) = (*Linha)->botton;
				*cursor = (*Linha)->inicioL;
				(*posCur).col = 1;
				(*posCur).lin++;
			}
		}
	}
	fclose(arq);
}

void SalvarArquivo(ListaLin *Linha,ListaCar **cursor,char nom[15])
{
	FILE *arq;
	char car;
	strcat(nom,".txt");
	arq = fopen(nom,"w+");
	while(Linha!=NULL)
	{
		(*cursor)= Linha->inicioL;
		while((*cursor)->prox!=NULL)
		{
			fputc((*cursor)->letra,arq);
			*cursor = (*cursor)->prox;
		}
		fputc('\n',arq);
		Linha = Linha->botton;
	}
	fclose(arq);
}

void ExibirEscrito(ListaLin *Linha, ListaCar *cursor, int PL, int RE, int RD)
{
	clrscr();
	char negt=0;
	PosicaoCur posCur;
	int count=0,i=0;
	while(i<120)
	{
		printf("|");	
		i++;
	}
	posCur.lin = 3;
	posCur.col = PL;
	while(Linha!=NULL)
	{
		cursor = Linha->inicioL;
		while(cursor->prox!=NULL)
		{
			if(negt==1)
				textcolor(RED);
			else
				textcolor(WHITE);
			if(cursor->letra==27)
				negt = !negt;
			else
			{
				if(cursor->letra==46 || cursor->letra==63 || cursor->letra==33 || count>RD)
				{
					gotoxy(posCur.col,posCur.lin); printf("%c",cursor->letra);
					posCur.col = PL;
					posCur.lin++;
					count=0;
				}
				else
				{
					gotoxy(posCur.col+RE,posCur.lin); printf("%c",cursor->letra);
					posCur.col++;
					count++;
				}
			}
			cursor = cursor->prox;
		}
		Linha = Linha->botton;
	}
}

void ConfParg(ListaLin *Linha, ListaCar *cursor)
{
	int PL,RE,RD;
	clrscr();
	gotoxy(2,2);	printf("Configuração dos parágrafos");
	gotoxy(1,3);	printf("----------------------------");
	gotoxy(2,6);	printf("Primeira Linha:");
	gotoxy(2,8); 	printf("Recuo Esquerdo:");
	gotoxy(2,10); 	printf("Recuo Direito:");
	gotoxy(18,6);	scanf("%d",&PL);
	gotoxy(18,8);	scanf("%d",&RE);
	gotoxy(17,10);	scanf("%d",&RD);
	ExibirEscrito(Linha,cursor,PL,RE,RD);
	getch();
}

void Menu(ListaLin **InicioPag ,PosicaoCur posCur)
{
	clrscr();
	Aparencia(&(*InicioPag), posCur);
	gotoxy(1+posCur.col,5+posCur.lin);
}

void Digitar(ListaLin **Linhas, ListaLin **Linha, ListaCar **cursor)
{
	PosicaoCur posCur;
	ListaLin *InicioPag = *Linhas;
	char dig,arq[15];
	posCur.lin = posCur.col = 1;
	Menu(&InicioPag, posCur);
	do
	{
		dig = getch();
		if(dig!=27)
		{
			
			switch(dig)
			{
				case -32:
					dig = getch();
					switch(dig)
					{
						case 'K':
							goLeft(&(*Linha),&(*cursor),&posCur);
							break;
						case 'H':
							goUp(&(*Linha),&(*cursor),&posCur);
							break;
						case 'P':
							goDown(&(*Linha),&(*cursor),&posCur);
							break;
						case 'M':
							goRight(&(*Linha),&(*cursor),&posCur);
							break;
						case 71:
							goHome(&(*Linha),&(*cursor),&posCur);
							break;
						case 73:
							pageUp(InicioPag,&(*Linha),&(*cursor),&posCur);
							break;
						case 79:
							goEnd(&(*Linha),&(*cursor),&posCur);
							break;
						case 81:
							pageDown(InicioPag,&(*Linha),&(*cursor),&posCur);
							break;
						case 83:
							deleteCar(&(*Linha),&(*cursor),&posCur);	
							break;
					}
					break;
				case 0:
					dig = getch();
					switch(dig)
					{
						case 60:
							clrscr();
							printf("Digite o nome do arquivo para abrir, sem o .txt\n");
							gets(arq);
							InicioPag = *Linhas;
							*Linha = *Linhas;
							clrscr();
							LerArquivo(&(*Linha),&(*cursor),&posCur,arq);
							break;
						case 61:
							clrscr();
							printf("Digite o nome do arquivo que deseja salvar, sem o .txt\n");
							gets(arq);
							InicioPag = *Linhas;
							*Linha = *Linhas;
							clrscr();
							SalvarArquivo(*Linha,&(*cursor),arq);
							break;
						case 62:
							dig = 27;
							break;
						case 63:
							*Linha = *Linhas;
							ConfParg(*Linha,*cursor);
						case 68:
							insereCar(&(*Linha),&(*cursor),27,&posCur);
							break;
						
					}
					break;
				case 8:
					backSpc(&(*Linha),&(*cursor),&posCur);
					break;
				case 13:
					if((*cursor)->prox==NULL)
					{
						insereProxL(&(*Linha));
						(*Linha) = (*Linha)->botton;
						*cursor = (*Linha)->inicioL;
						posCur.col = 1;
						posCur.lin++;
					}
					break;
				case 44:
					deleteCar(&(*Linha),&(*cursor),&posCur);
					break;
				default:
					insereCar(&(*Linha),&(*cursor),dig,&posCur);
					break;
			}
			Menu(&InicioPag, posCur);
		}
	}
	while(dig!=27);
}


int main(void)
{
	ListaLin *Linhas,*Linha;
	ListaCar *cursor;
	initL(&Linhas);
	insereFimL(&Linhas);
	Linha = Linhas;
	cursor = Linhas->inicioL;
	Digitar(&Linhas,&Linha,&cursor);	
}
