#define TF 79

struct listaCar
{
	struct listaCar *prox, *ant;
	char letra;
};
typedef struct listaCar ListaCar;

struct listaLin
{
	struct listaLin *top, *botton;
	int nro;
	struct listaCar *inicioL;
};
typedef struct listaLin ListaLin;

struct posicaoCur
{
	int lin,col;
};
typedef struct posicaoCur PosicaoCur;



void initL(ListaLin **L)
{
	*L = NULL;
}

void initCar(ListaCar **C)
{
	*C = NULL;
}

void createSent(ListaCar **C)
{
	ListaCar *aux, *sent = (ListaCar*)malloc(sizeof(ListaCar));
	sent -> prox = sent -> ant = NULL;
	sent -> letra = 0;
	if((*C)==NULL)
		*C = sent;
	else
	{
		aux = *C;
		while(aux->prox!=NULL)
			aux = aux -> prox;
		aux -> prox = sent;
		sent -> ant = aux;
	}
}

void insereFimL(ListaLin **Linha)
{
	ListaLin *aux,*novo = (ListaLin*)malloc(sizeof(ListaLin));
	novo -> top = novo -> botton = NULL;
	novo -> inicioL = NULL;
	novo -> nro = 0;
	if((*Linha)==NULL)
		(*Linha) = novo;
	else
	{
		aux = (*Linha);
		while(aux->botton!=NULL)
			aux = aux -> botton;
		novo -> top = aux;
		aux -> botton = novo;
	}
	createSent(&(novo->inicioL));
}

void insereProxL(ListaLin **Linha)
{
	ListaLin *novo = (ListaLin*)malloc(sizeof(ListaLin));
	novo -> top = novo -> botton = NULL;
	novo -> inicioL = NULL;
	novo -> nro = 0;
	if((*Linha)->botton==NULL)
	{
		(*Linha)->botton = novo;
		novo -> top = *Linha;
	}
	else
	{
		novo -> top = (*Linha);
		novo -> botton = (*Linha)->botton;
		(*Linha)->botton->top = novo;
		(*Linha)->botton = novo;
	}
	createSent(&(novo->inicioL));
}

void insereCar(ListaLin **Linha,ListaCar **cursor, char car, PosicaoCur *posCur)
{
	ListaCar *novo = (ListaCar*)malloc(sizeof(ListaCar));
	novo->ant = NULL;
	novo->letra = car;
	if((*Linha)->nro>=TF)
	{
		insereProxL(&(*Linha));
		*Linha = (*Linha)->botton;
		*cursor = (*Linha)->inicioL;
		(*posCur).col = 1;
		(*posCur).lin += 1;
	}
	if((*cursor)->ant==NULL)
	{
		novo->prox=(*cursor);
		(*cursor)->ant = novo;
		(*Linha)->inicioL = novo;
	}
	else
	{
		novo->prox = (*cursor);
		novo->ant = (*cursor)->ant;
		(*cursor)->ant->prox = novo;
		(*cursor)->ant = novo;
	}
	if(car!=27)
	{
		(*posCur).col += 1;
		(*Linha)->nro++;
	}	
}

void retiraL(ListaLin **Linha)
{
	if((*Linha)->botton==NULL)
	{
		(*Linha)->top->botton = NULL;
		free(*Linha);
	}
	else
	{
		(*Linha)->botton->top = (*Linha)->top;
		(*Linha)->top->botton = (*Linha)->botton;
		free(*Linha);
	}
}

void ApagaTodasL(ListaLin**Linhas,ListaLin**Linha,ListaCar**cursor)
{
	while((*Linha)->botton!=NULL)
		*Linha = (*Linha)-> botton;
	while(*Linha!=NULL)
	{
		*cursor = (*Linha)->inicioL;
		while((*cursor)->prox!=NULL)
			*cursor = (*cursor)->prox;
		while((*cursor!=NULL))
		{
			if((*cursor)->prox!=NULL)
				free((*cursor)->prox);
			*cursor = (*cursor)->ant;
		}
		free((*Linha)->inicioL);
		*Linha = (*Linha)->top;
		if(*Linha!=NULL)
			free((*Linha)->botton);
	}
}
void retiraCar(ListaLin **Linha, ListaCar *Caracter)
{
	if((Caracter)->ant==NULL)
	{
		(*Linha)->inicioL = (Caracter)->prox;
		(Caracter)->prox->ant = NULL;
		free(Caracter);
	}
	else
	{
		if((Caracter)->prox!=NULL)
		{
			(Caracter)->prox->ant = (Caracter)->ant;
			(Caracter)->ant->prox = (Caracter)->prox;
			free(Caracter); 
		}
	}
}

void deleteCar(ListaLin**Linha, ListaCar**cursor, PosicaoCur *posCur)
{
	ListaCar *aux;
	if((*cursor)->prox!=NULL)
	{
		if((*cursor)->prox->letra==27)
		{
			*cursor = (*cursor)->prox;
			retiraCar(&(*Linha),(*cursor)->ant);
			*cursor = (*cursor)->prox;
			retiraCar(&(*Linha),(*cursor)->ant);
		}
		else
		{
			*cursor = (*cursor)->prox;
			retiraCar(&(*Linha),(*cursor)->ant);
		}
		(*Linha)->nro--;
	}
}

void backSpc(ListaLin **Linha, ListaCar **cursor, PosicaoCur *posCur)
{
	if((*cursor)->ant!=NULL)
	{
		if((*cursor)->ant->letra!=27)
			retiraCar(&(*Linha),(*cursor)->ant);
		else
		{
			retiraCar(&(*Linha),(*cursor)->ant);
			if((*cursor)->ant!=NULL)
				retiraCar(&(*Linha),(*cursor)->ant);
		}
		(*posCur).col--;
		(*Linha)->nro--;
	}
	//else
}



void goUp(ListaLin **Linha, ListaCar **cursor, PosicaoCur *posCur)
{
	int posCol;
	if((*Linha)->top!=NULL)
	{
		posCol = (*posCur).col;
		*Linha = (*Linha)->top;
		*cursor = (*Linha)->inicioL;
		(*posCur).col = 1;
		(*posCur).lin--;
		while((*cursor)->prox!=NULL && (*posCur).col<posCol)
		{
			*cursor = (*cursor)->prox;
			if((*cursor)->letra!=27)
				(*posCur).col++;
		}
		if((*cursor)->letra==27)
			*cursor = (*cursor)->prox;
	}
}

void goDown(ListaLin **Linha, ListaCar **cursor, PosicaoCur *posCur)
{
	int posCol;
	if((*Linha)->botton!=NULL)
	{
		posCol = (*posCur).col;
		*Linha = (*Linha)->botton;
		*cursor = (*Linha)->inicioL;
		(*posCur).col = 1;
		(*posCur).lin++;
		while((*cursor)->prox!=NULL && (*posCur).col<posCol)
		{
			*cursor = (*cursor)->prox;
			if((*cursor)->letra!=27)
				(*posCur).col++;
		}
		if((*cursor)->letra==27)
			*cursor = (*cursor)->prox;
	}
}

void goRight(ListaLin **Linha, ListaCar **cursor, PosicaoCur *posCur)
{
	if((*cursor)->prox!=NULL)
	{
		if((*cursor)->prox->letra!=27)
		{
			*cursor = (*cursor)->prox;
			(*posCur).col++;
		}
		else
		{
			*cursor = (*cursor)->prox;
			*cursor = (*cursor)->prox;
			(*posCur).col++;
		}
	}
	else
	{
		if((*Linha)->botton!=NULL)
		{
			*Linha = (*Linha)->botton;
			*cursor = (*Linha)->inicioL;
			(*posCur).col = 1;
			(*posCur).lin++;
		}
	}
}

void goLeft(ListaLin **Linha, ListaCar **cursor, PosicaoCur *posCur)
{
	if((*cursor)->ant!=NULL)
	{
		if((*cursor)->ant->letra!=27)
		{
			*cursor = (*cursor)->ant;
			(*posCur).col--;
		}
		else
		{
			*cursor = (*cursor)->ant;
			if((*cursor)->ant!=NULL)
			{
				*cursor = (*cursor)->ant;
				(*posCur).col--;
			}
			else
			{
				if((*Linha)->top!=NULL)
				{
					*Linha = (*Linha)->top;
					*cursor = (*Linha)->inicioL;
					while((*cursor)->prox!=NULL)
						*cursor = (*cursor)->prox;
					(*posCur).col = (*Linha)->nro+1;
					(*posCur).lin--;
				}
			}
		}
	}
	else
	{
		if((*Linha)->top!=NULL)
		{
			*Linha = (*Linha)->top;
			*cursor = (*Linha)->inicioL;
			while((*cursor)->prox!=NULL)
				*cursor = (*cursor)->prox;
			(*posCur).col = (*Linha)->nro+1;
			(*posCur).lin--;
		}
	}
}

void pageUp(ListaLin*InicioPag, ListaLin**Linha, ListaCar**cursor, PosicaoCur *posCur)
{
	int cont=0;
	while(*Linha!=InicioPag)
	{
		*Linha = (*Linha)->top;
		cont++;
	}
	*cursor = (*Linha)->inicioL;
	(*posCur).col=1;
	(*posCur).lin = (*posCur).lin-cont;
}

void pageDown(ListaLin*InicioPag,ListaLin**Linha , ListaCar**cursor, PosicaoCur *posCur)
{
	int cont=0;
	(*Linha) = InicioPag;
	while((*Linha)->botton!=NULL && cont<20)
	{
		*Linha = (*Linha)->botton;
		cont++;
	}
	*cursor = (*Linha)->inicioL;
	while((*cursor)->prox!=NULL)
		*cursor = (*cursor)->prox;
	(*posCur).lin = cont+1;
	(*posCur).col = (*Linha)->nro+1;
}

void goEnd(ListaLin**Linha, ListaCar**cursor, PosicaoCur *posCur)
{
	while((*cursor)->prox!=NULL)
		*cursor = (*cursor)->prox;
	(*posCur).col=(*Linha)->nro+1;
}

void goHome(ListaLin**Linha, ListaCar**cursor, PosicaoCur *posCur)
{
	*cursor = (*Linha)->inicioL;
	(*posCur).col=1;
}

void exibLinhas(ListaLin *inicioPag, PosicaoCur posCur)
{
	char negt=0;
	ListaCar *mostrar;
	(posCur).lin = (posCur).col = 1;
	while(inicioPag!=NULL && (posCur).lin<21)
	{
		mostrar = inicioPag->inicioL;
		while(mostrar!=NULL)
		{
			if(negt==1)
				textcolor(RED);
			else
				textcolor(WHITE);
			if(mostrar->letra==27)
			{
				negt = !negt;
				mostrar = mostrar -> prox;
			}
			else
			{
				gotoxy(1+(posCur).col,5+(posCur).lin);
				printf("%c",mostrar->letra);
				mostrar = mostrar->prox;
				(posCur).col++;
			}
		}
		inicioPag = inicioPag->botton;
		(posCur).lin++;
		(posCur).col=1;
	}
	textcolor(WHITE);
}

