//não funcionando
struct reg_lista
{
	struct listagen *cabeca;
	struct listagen *cauda;
};
union info_lista
{
	char info[8]; //se for 1
	struct reg_lista lista;//se for 0
};
struct listagen
{
	char terminal;
	union info_lista no;
};
typedef struct listagen ListaGen;

ListaGen* CriaT(char *info)
{
	ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
	L->terminal = 1;
	strcpy((L->no.info), info);
	return L;
}

char Nula(ListaGen* L)
{
	return L==NULL;
}

char Atomo(ListaGen *L)
{
	return !Nula(L) && L->terminal;
}

ListaGen* Cons(ListaGen *H, ListaGen *T)
{
	if(Atomo(T))
		return NULL;
	else
	{
		ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
		L->terminal = 0;
		L->no.lista.cabeca = H;
		L->no.lista.cauda = T;
		return L;
	}
}

ListaGen *Head(ListaGen *L)
{
	if(!Nula(L) || !Atomo(L))
		return NULL;
	else
		return L->no.lista.cabeca;
}

ListaGen *Tail(ListaGen *L)
{
	if(!Nula(L) || !Atomo(L))
		return NULL;
	else
		return L->no.lista.cauda;
}

void insereListaGen(ListaGen** Lpalavras, char palavra[])
{
	ListaGen *pai, *atual,*ant,*aux;
	int i;
	if(*Lpalavras==NULL)
		insereLetras(&(*Lpalavras),palavra[]);
	else
	{
		pai = atual = *Lpalavras;
		for(i=0;i<strlen(palavra)&&flag;i++)
		{
			busca = letra(atual,palavra[i],&ant,&aux);
			if(aux!=NULL && aux->letra==palavra[i])
			{
				pai = aux;
				atual = pai->prim
				if(atual==NULL)
				{
					insereLetras(&(pai->prim),palavras,i++);
					flag=0;
				}
				else if(i==strlen(palavra)-1)
					aux->final='T';
			}
			else 
			{
				novo = CriaNo(palavra[i],i,strlen(palavra));
				if(ant == aux)
				{
					if(aux==*Lpalavras)
					{
						novo -> prox = *Lpalavras;
						*Lpalavras = novo;
					}
					else
					{
						ant->prox = novo;
						novo->prox = aux;
					}
					insereLetras(&novo->prim,palavra,i++);
				}
			}
		}
	}
}


