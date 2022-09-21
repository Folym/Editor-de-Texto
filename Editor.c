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
	char dig,negt=0;
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
						case 83:
							deleteCar(&(*Linha),&(*cursor),&posCur);	
							break;
					}
					break;
				case 0:
					dig = getch();
					switch(dig)
					{
						case 62:
							dig = 27;
						case 68:
							insereCar(&(*Linha),&(*cursor),27,&posCur);
						
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
