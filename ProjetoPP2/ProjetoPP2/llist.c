#include <stdio.h>
#include "llist.h"
#include <stdlib.h>
#include <string.h>

int count = 0;
//load para o 1º ficheiro
Pilot load(Pilot p, char txt[])
{
	FILE *file1; //apontador de ficheiro
	file1 = fopen(txt, "r");  //abertura de ficheiro
	H h = NULL;  // inicialização da lista h
	char x[100];
	int y = 0;
	float z = 0;

	//caso haja erro ao abrir , escreve mensagem
	if (file1 == NULL)
	{
		printf("Não foi possível abrir o ficheiro...");
	}
	else
	{//caso não haja le e grava os dados
		fscanf(file1, "%d", &count);
		while (fscanf(file1, "%s %d %f\n", &x, &y, &z) != EOF)
		{
			h = insertFileElemToH(h, x, y, z);
		}
		fclose(file1);
	}

	p = insertPilot(p, h);

	p = insertAllPilot(p, h);

	return p;
}
//load para o ficheiro da tabela
Pilot loadTable(Pilot p, char txt[])
{
	FILE *file2;
	file2 = fopen(txt, "r");
	int pn = 0, n = 1;
	char name[50], car[50], str[50];

	if (file2 == NULL)
	{
		printf("Não foi possível abrir o ficheiro...");
	}
	else
	{
		while (fgets(str, 50, file2) != NULL)
		{
			if (n == 1)
			{
				pn = (int)str[0] - 48;
				n++;
			}
			else if (n == 2)
			{
				strcpy(name, str);
				name[strlen(name) - 1] = '\0';

				n++;
			}
			else
			{
				strcpy(car, str);
				car[strlen(car) - 1] = '\0';
				p = insertNamePilot(p, name, car, pn);
				n = 1;
			}

		}
		fclose(file2);
	}
	return p;
}
//load para o ficheiro das distancias
Pilot loadDistance(Pilot p, char * txt[])
{
	FILE * file3;
	file3 = fopen(txt, "r");
	char etapa1[10], etapa2[10];
	float distance, dis1;

	if (file3 == NULL)
	{
		printf("Não foi possível abrir o ficheiro...");
	}
	else
	{
		while (fscanf(file3, "%s %s %f.%f", &etapa1, &etapa2, &distance, &dis1) != EOF)
		{
			distance += dis1;
			for (Pilot aux = p; aux != NULL; aux = aux->next)
			{
				aux->stages = insertDistance(aux->stages, distance, etapa2[0], atoi(etapa2 + 1));
			}
		}
	}
	return p;
}
//Inserir as distancias
EN insertDistance(EN stage, float di, char e1, int ei1)
{
	if (stage != NULL)
	{
		if (stage->nm == e1 && stage->n == ei1)
		{
			stage->distance = di;
		}
		else  stage->next = insertDistance(stage->next, di, e1, ei1);
	}
	return stage;
}
//Insere valores dentro da lista pilot
Pilot insertAllPilot(Pilot p, H h)
{
	Pilot aux = p;

	while (aux != NULL)
	{
		aux = pilotOrd(h, aux);

		aux = aux->next;
	}
	//Limpar os malloc do h
	do
	{
		h = removeH(h);

	} while (h != NULL);

	return p;
}
//Inserir Nomes no piloto
Pilot insertNamePilot(Pilot p, char n[], char c[], int num)
{
	Pilot aux;

	if (p == NULL || num < p->number)
	{
		aux = (Pilot)malloc(sizeof(struct pilot));
		strcpy(aux->name, n);
		strcpy(aux->car, c);
		aux->number = num;
		aux->stages = NULL;
		(*aux).next = p;
		return aux;
	}
	if (num == p->number)
	{
		strcpy(p->name, n);
		strcpy(p->car, c);
		return p;
	}
	else if (p->next != NULL && p->next->number > num)
	{
		aux = (Pilot)malloc(sizeof(struct pilot));
		aux->number = p->number;
		strcpy(aux->name, p->name);
		strcpy(aux->car, p->car);
		p->number = num;
		strcpy(p->name, n);
		strcpy(p->car, c);
		aux->stages = NULL;
		(*aux).next = p;
		return aux;
	}
	else
	{
		p->next = insertNamePilot(p->next, n, c, num);
		return p;
	}
}
//Inserir os elementos na lista H
H insertFileElemToH(H h, char x[], int y, float z)
{
	H aux;

	if (h == NULL)
	{
		aux = (H)malloc(sizeof(struct h));
		strcpy(aux->e, x);
		aux->p = y;
		aux->t = z;
		aux->next = NULL;
		return aux;
	}
	else
	{
		aux = (H)malloc(sizeof(struct h));
		aux->p = h->p;
		aux->t = h->t;
		strcpy(aux->e, h->e);
		h->p = y;
		h->t = z;
		strcpy(h->e, x);
		(*aux).next = h;
		return aux;
	}
	return h;
} //FEITO
// Ordenar os pilotos
Pilot pilotOrd(H h, Pilot p)
{
	H aux = h;

	if (h != NULL)
	{
		if (p->number == h->p)
		{
			p->stages = insertMiddleSteps(aux->e, p->stages, aux->t);
		}
		p = pilotOrd(h->next, p);
	}
	return p;
}
// Libertar memória usada pela lista H
H removeH(H listaH)
{
	H auxH;

	if (listaH == NULL)
	{
		return NULL;
	}
	else
	{
		auxH = listaH->next;
		free(listaH);
		return auxH;
	}
	return listaH;
}
//Mostra o numero de pilotos validos(1) ou invalidos(0)
int numberOfPilots(Pilot p, int b)
{
	int n = 0;
	Pilot aux = p;

	while (aux != NULL)
	{
		if (aux != NULL)
		{
			if (b == 1)
			{
				if (validateStage(aux->stages) == 1)
				{
					n++;
				}
			}
			else if (b == 0) { n++; }
		}
		else
		{
			return n;
		}

		aux = aux->next;
	}
	return n;
}
//Insere as etapas por ordem
EN insertMiddleSteps(char step[], EN e, float t)
{
	EN aux;

	if (e == NULL || compare(step, e->nm, e->n) < 0)
	{
		aux = (EN)malloc(sizeof(struct En));
		aux->E = t;
		aux->distance = 0;
		aux->nm = (char)step[0];
		aux->n = atoi(step + 1);
		aux->next = e;
		return aux;
	}

	e->next = insertMiddleSteps(step, e->next, t);
	return e;
}
//Funçao que compara as etapas
int compare(char step[], char nm, int n)
{
	int stNum = 0;

	if (step[0] == 'P' && nm == 'P' || step[0] == 'C' && nm == 'C')
		return 0;

	if (step[0] == 'P')
		return -1;

	if (step[0] == 'C')
		return 1;

	if (step[0] == 'E')
	{
		stNum = atoi(step + 1);

		if (nm == 'P')
		{
			return 0;
		}
		else if (nm == 'C')
		{
			return -1;
		}
		else if (stNum == n)
		{
			return 0;
		}
		else if (stNum < n)
		{
			return-1;
		}
		else return 1;
	}

	return 0;
}
// Validar se um piloto tem uma prova válida
int validateStage(EN aux)
{
	int b = 0;
	int z = 0;
	while (aux != NULL)
	{
		z++;

		if (aux->next == NULL && z == count + 1)
		{
			b = 1;
		}
		else if (aux->next == NULL && z != count + 1)
		{
			return 0;
		}

		if (aux->next != NULL)
		{
			if (aux->E < aux->next->E)
			{
				b = 1;
			}
			else return 0;
		}

		if (aux->next != NULL && aux->nm == 'E' && aux->next->nm == 'E')
		{
			if (aux->n < aux->next->n)
			{
				b = 1;
			}
			else return 0;

		}

		if (aux->nm == 'P')
		{
			b = 1;
		}
		else if (aux->nm == 'C' && aux->next == NULL)
		{
			b = 1;
		}

		aux = aux->next;
	}

	return b;
}
//Cria todos os pilotos
Pilot insertPilot(Pilot p, H h)
{
	NumPilot listNumPilots = NULL;
	//Lista com os numeros dos pilotos 
	while (h != NULL)
	{
		listNumPilots = insertNumPilot(h, listNumPilots);
		h = h->next;
	}
	//Lista nM para criar os pilotos
	while (listNumPilots != NULL)
	{
		p = insertNamePilot(p, "unknown", "unknown", listNumPilots->p);
		listNumPilots = removeNumPilot(listNumPilots);
	}

	return p;
}
//Liberta memória usada pela lista numPilot
NumPilot removeNumPilot(NumPilot np)
{
	NumPilot auxP;

	if (np == NULL)
	{
		return NULL;
	}
	else if (np)
	{
		auxP = np->next;

		free(np);
		return auxP;
	}
	else
	{
		np->next = removeNumPilot(np->next);
	}

	return np;

}
//Insere os dados na lista numPilot
NumPilot insertNumPilot(H h, NumPilot nP)
{
	NumPilot aux;

	if (nP == NULL || nP->p < h->p)
	{
		aux = (Pilot)malloc(sizeof(struct pilot));
		aux->p = h->p;
		aux->next = nP;
		return aux;
	}
	else if (nP->p > h->p)
	{
		aux = (Pilot)malloc(sizeof(struct pilot));
		aux->p = nP->p;
		nP->p = h->p;
		aux->next = nP;
		return aux;
	}
	else if (nP->p == h->p)
	{
		return nP;
	}
}
//Insere os dados para usar na tabela
Info lapTime(Info itb, float time, int num, char n[], char c[], int bool)
{
	Info aux;
	if (bool == 1)
	{
		if (itb == NULL || time < itb->time || itb->bool == 0)
		{
			{
				aux = (Info)malloc(sizeof(struct infoTable));
				strcpy(aux->namePilot, n);
				strcpy(aux->carPilot, c);
				aux->bool = bool;
				aux->numPilot = num;
				aux->time = time;
				(*aux).next = itb;
				return aux;
			}
			if (time == itb->time)
			{
				itb->next = lapTime(itb->next, time, num, n, c, bool);
				return itb;
			}
			else if (itb->next != NULL && itb->next->time > time)
			{
				aux = (Info)malloc(sizeof(struct infoTable));
				aux->numPilot = itb->numPilot;
				aux->time = itb->time;
				aux->bool = itb->bool;
				strcpy(aux->namePilot, itb->namePilot);
				strcpy(aux->carPilot, itb->carPilot);
				itb->numPilot = num;
				itb->time = time;
				itb->bool = bool;
				strcpy(itb->namePilot, n);
				strcpy(itb->carPilot, c);
				(*aux).next = itb;
				return aux;
			}
			else
			{
				itb->next = lapTime(itb->next, time, num, n, c, bool);
				return itb;
			}
		}
		else
		{
			if (itb == NULL)
			{
				aux = (Info)malloc(sizeof(struct infoTable));
				strcpy(aux->namePilot, n);
				strcpy(aux->carPilot, c);
				aux->numPilot = num;
				aux->bool = 0;
				aux->time = time;
				(*aux).next = itb;
				return aux;
			}
			else
			{
				itb->next = lapTime(itb->next, time, num, n, c, bool);
				return itb;
			}
		}
	}
	else
	{
		if (itb != NULL) {
			itb->next = lapTime(itb->next,time, num, n, c, bool);
		}
		else
		{
			itb->next = lapTime(itb->next, time, num, n, c, 1);
		}
	}
}

InfoSpeed insertAvgSpeedPilot(InfoSpeed avg, char n[], float avgSpeed)
{
	InfoSpeed aux;

	if (avg == NULL || avg->avgSpeed > avgSpeed)
	{
		aux = (InfoSpeed)malloc(sizeof(struct infoSpeed));
		aux->avgSpeed = avgSpeed;
		strcpy(aux->n, n);
		aux->next = avg;
		return aux;
	}
	else if (avg->avgSpeed < avgSpeed)
	{
		aux = (InfoSpeed)malloc(sizeof(struct infoSpeed));
		aux->avgSpeed = avg->avgSpeed;
		strcpy(aux->n, avg->n);
		avg->avgSpeed = avgSpeed;
		strcpy(avg->n, n);
		aux->next = avg;
		return aux;
	}
	else if (avg->avgSpeed == avgSpeed)
	{
		return avg;
	}

}
//Liberta a memória usada pela lista Pilot
Pilot removePilot(Pilot lista, int num)
{
	Pilot aux1;

	if (lista == NULL)
	{
		return NULL;
	}
	else if (lista->number == num)
	{
		aux1 = lista->next;
		free(lista->stages);
		free(lista);
		return aux1;
	}
	else
	{
		lista->next = removePilot(lista->next, num);
	}

	return lista;

}
//Liberta a memoria usada pela lista Info
Info removeLapTime(Info itb)
{
	Info auxIT;

	if (itb == NULL)
	{
		return NULL;
	}
	else
	{
		auxIT = itb->next;
		free(itb);
		return auxIT;
	}

	return itb;

}