#include<stdio.h>
#include<stdlib.h>
#include"llist.h"
#include<string.h>
#include <locale.h>

char firstTxt[100] = "wrcpt.txt", secondTxt[100] = "table.txt", thirdTxt[100] = "etapas.txt";

void Problema1(Pilot p)
{
	printf("%d", numberOfPilots(p, 0));
}
void Problema2(Pilot p)
{
	printf("%d", numberOfPilots(p, 1));
}
void Problema3(Pilot p)
{
	if (p != NULL)
	{
		Problema3(p->next);

		if (validateStage(p->stages) == 1)
		{
			printf("%s-%d\n", p->name, p->number);
		}
	}
}
void Problema4(Pilot p)
{
	float soma;
	int quantPilot = 0;
	Pilot  pilot = NULL;
	Pilot  pe = NULL;
	EN e = p->stages;

	if (p != NULL)
	{
		//Cria um EN valido para ser usado como comparação das etapas
		if (validateStage(e) == 0)
		{
			for (pe = load(pe, firstTxt); pe != NULL;)
			{
				if (validateStage(e) == 0)
				{
					e = pe->next->stages;
				}
				else
				{
					break;
				}

				pe = removePilot(pe, pe->number);
			}
		}

		for (; e != NULL; e = e->next)
		{
			soma = 0;
			quantPilot = 0;
			//Cria um pilot para verificar os seus dados
			for (pilot = load(pilot, firstTxt); pilot != NULL; )
			{
				//Verifica os dados dos stages do pilot 
				for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
				{
					if (ep->next != NULL && e->nm == ep->nm && e->n == ep->n && ep->next->nm == e->next->nm && ep->next->n == e->next->n)
					{
						//soma o tempo que demorou entre as etapas
						soma += ep->next->E - ep->E;
						quantPilot++;
					}
				}
				pilot = removePilot(pilot, pilot->number);
			}

			if (e->next != NULL)
			{
				printf("%c%d - %c%d = %.1f\n", e->nm, e->n, e->next->nm, e->next->n, (float)(soma / quantPilot));
			}
		}
	}
}
void Problema5(Pilot p)
{
	float soma;
	int numPilot = 0;
	Pilot pilot = NULL;
	Pilot pe = NULL;
	EN e = p->stages;

	if (p != NULL)
	{
		if (validateStage(e) == 0)
		{
			for (pe = load(pe, firstTxt); pe != NULL;)
			{
				if (validateStage(e) == 0)
				{
					e = pe->next->stages;
				}
				else
				{
					break;
				}

				pe = removePilot(pe, pe->number);
			}
		}

		for (; e != NULL; e = e->next)
		{
			soma = 0;
			numPilot = 0;
			for (pilot = load(pilot, firstTxt); pilot != NULL; )
			{
				for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
				{
					//verifica apenas os dados de pilotos validos na corrida
					if (validateStage(pilot->stages) == 1)
					{
						if (ep->next != NULL && e->nm == ep->nm && e->n == ep->n && ep->next->nm == e->next->nm && ep->next->n == e->next->n)
						{
							soma += ep->next->E - ep->E;
							numPilot++;
						}
					}
				}
				pilot = removePilot(pilot, pilot->number);
			}

			if (e->next != NULL)
			{
				printf("%c%d - %c%d = %.1f\n", e->nm, e->n, e->next->nm, e->next->n, (float)(soma / numPilot));
			}

		}
	}
}
void Problema6(Pilot p)
{
	Pilot pilot = NULL;
	int numFaster = 0;
	char namePilot[100];
	int nPilot = 0;

	if (p != NULL)
	{
		for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt); pilot != NULL;)
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (validateStage(pilot->stages) == 1 && ep->nm == 'C')
				{
					//verifica os tempo de chegada do piloto valido e ve quem demorou menos
					if (numFaster == 0)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
					else if (numFaster > ep->E)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
				}
			}
			pilot = removePilot(pilot, pilot->number);
		}

		printf("%s - Carro %d", namePilot, nPilot);
	}
}
void Problema7(Pilot p)
{
	Pilot pilot = NULL;
	int numFaster = 0;
	char namePilot[100];
	int nPilot = 0;

	if (p != NULL)
	{
		for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt); pilot != NULL;)
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (validateStage(pilot->stages) && ep->nm == 'C')
				{
					//verifica os tempo de chegada do piloto valido e ve quem demorou mais
					if (numFaster == 0)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
					else if (numFaster < ep->E)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
				}

			}
			pilot = removePilot(pilot, pilot->number);
		}

		printf("%s - Carro %d", namePilot, nPilot);
	}
}
void Problema8(Pilot p)
{
	Pilot pilot = NULL;
	int numFaster = 0;
	char namePilot[100];
	int nPilot = 0, n1 = 0, n2 = 0;
	float stageTime = 0;
	char stage1 = ' ', stage2 = ' ';

	if (p != NULL)
	{
		//verifica quem o mais rapido
		for (pilot = load(pilot, firstTxt); pilot != NULL; )
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (validateStage(pilot->stages) == 1 && ep->nm == 'C')
				{
					if (numFaster == 0)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
					else if (numFaster > ep->E)
					{
						numFaster = ep->E;
						nPilot = pilot->number;
						strcpy(namePilot, pilot->name);
					}
				}
			}
			pilot = removePilot(pilot, pilot->number);
		}
		//verifica a etapa mais lenta
		for (pilot = load(pilot, firstTxt); pilot != NULL; )
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (pilot->number == nPilot)
				{
					if (stageTime == 0 && ep->next != NULL)
					{
						stageTime = ep->next->E - ep->E;
						stage1 = ep->next->nm;
						stage2 = ep->nm;
						n1 = ep->next->n;
						n2 = ep->n;
					}
					else if (ep->next != NULL && stageTime < ep->next->E - ep->E)
					{
						stageTime = ep->next->E - ep->E;
						stage1 = ep->next->nm;
						stage2 = ep->nm;
						n1 = ep->next->n;
						n2 = ep->n;
					}
				}
			}
			pilot = removePilot(pilot, pilot->number);
		}
	}
	printf("O Piloto %d teve a sua etapa mais lenta na  %c%d - %c%d com o valor de %.1f  ", nPilot, stage2, n2, stage1, n1, stageTime);
}
void Problema9(Pilot p)
{
	Pilot pilot = NULL;

	float soma = 0, stage = 0;

	for (EN e = p->stages; e != NULL; e = e->next)
	{
		stage = 0;

		for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt); pilot != NULL; )
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (ep->next != NULL && e->nm == ep->nm && e->n == ep->n)
				{
					if (stage == 0)
					{
						stage = ep->next->E - ep->E;

					}
					else if (stage > ep->next->E - ep->E)
					{
						stage = ep->next->E - ep->E;

					}
				}
			}
			pilot = removePilot(pilot, pilot->number);
		}
		soma += stage;
	}
	printf("O menor tempo possivel para efetuar a prova é %.1f", soma);
}
void Problema10(Pilot p)
{
	Pilot pilot = NULL;
	Info laptime = NULL;
	float prevTime = 0;
	float topTime = 0;

	if (p != NULL)
	{
		for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt); pilot != NULL; )
		{
			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (ep->nm == 'C')
				{
					laptime = lapTime(laptime, ep->E, pilot->number, pilot->name, pilot->car,1);
				}
			}
			pilot = removePilot(pilot, pilot->number);
		}
	}
	int pos = 1;

	printf("Pos.|No.|Driver|Car|Time|Dif. Prev.|Dif. Ldr. \n");

	for (; laptime != NULL;)
	{
		if (prevTime == 0)
		{
			topTime = laptime->time;
			prevTime = laptime->time;
			laptime->ldDif = 0;
			laptime->prevDif = 0;

		}
		else
		{
			laptime->ldDif = -topTime + laptime->time;
			laptime->prevDif = -prevTime + laptime->time;
			prevTime = laptime->time;
		}
		printf("   %d|  %d|%s|%s|%.1f|%.1f|%.1f\n", pos++, laptime->numPilot, laptime->namePilot, laptime->carPilot, laptime->time, laptime->prevDif, laptime->ldDif);

		laptime = removeLapTime(laptime);
	}
}
void Problema11(Pilot p) {

	Pilot pilot = NULL;
	float avgSpeed = 0; //distance / time
	float totalTime = 0;
	float totalDistance = 0;
	InfoSpeed is = NULL;
	//Pilot  pe = NULL;
	//EN e = p->stages;

	if (p != NULL)
	{
		for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt); pilot != NULL; )
		{


			if (validateStage(pilot->stages) == 1)
			{
				pilot = loadDistance(pilot, thirdTxt);
				totalDistance = 0; totalTime = 0;
			}

			for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
			{
				if (validateStage(pilot->stages) == 1 && ep->nm == 'C')
				{
					totalTime += ep->E;
				}
				totalDistance += ep->distance;
			}
			if (validateStage(pilot->stages) == 1)
			{
				avgSpeed = (totalDistance / totalTime); //tempo para definir 
				is = insertAvgSpeedPilot(is, pilot->name, avgSpeed);
			}
			pilot = removePilot(pilot, pilot->number);
		}
	}

	for (InfoSpeed aux = is; aux != NULL; aux = aux->next)
	{
		printf("A média das velocidades do piloto %s é %.4f \n", aux->n, aux->avgSpeed);
	}
}
void Problema12(Pilot p)
{
	Pilot pilot = NULL;
	float avgSpeed; //distance / time
	float totalTime;
	float totalDistance;
	float vel = 0;
	int numplayers = 0;
	Pilot  pe = NULL;
	EN e = p->stages;

	if (p != NULL) {

		if (validateStage(e) == 0)
		{
			for (pe = load(pe, firstTxt), pe = loadTable(pe, secondTxt), pe = loadDistance(pe, thirdTxt); pe != NULL;)
			{
				if (validateStage(e) == 0)
				{
					e = pe->next->stages;
				}
				else
				{
					break;
				}
				pe = removePilot(pe, pe->number);
			}
		}

		for (; e != NULL; e = e->next)
		{
			totalTime = 0;
			avgSpeed = 0;
			numplayers = 0;

			if (e->next != NULL)
			{
				totalDistance = e->next->distance;
			}
			for (pilot = load(pilot, firstTxt), pilot = loadTable(pilot, secondTxt), pilot = loadDistance(pilot, thirdTxt); pilot != NULL; )
			{
				vel = 0;
				for (EN ep = pilot->stages; ep != NULL; ep = ep->next)
				{
					if (ep->next != NULL)
					{
						totalTime = 0;
						if (ep->next != NULL && e->nm == ep->nm && e->n == ep->n && e->next->nm == ep->next->nm && e->next->n == ep->next->n)
						{
							totalTime = ep->next->E - ep->E;
							numplayers++;
						}
					}
					if (totalTime != 0)
					{
						vel = totalDistance / totalTime;
					}
				}
				pilot = removePilot(pilot, pilot->number);
				avgSpeed += vel;
			}
			avgSpeed = avgSpeed / numplayers;

			if (e->next != NULL)
			{
				printf("A média das velocidades na etapa: %c%d - %c%d é %.4f\n", e->nm, e->n, e->next->nm, e->next->n, avgSpeed);
			}
		}
	}
}

int main(int agrc, char *agrv[])
{
	setlocale(LC_ALL, "portuguese");
	int ex = 0;
	Pilot p = NULL;

	p = load(p, agrv[1]);
	strcpy(firstTxt, agrv[1]);

	p = loadTable(p, agrv[3]);
	strcpy(secondTxt, agrv[3]);

	p = loadDistance(p, agrv[4]);
	strcpy(thirdTxt, agrv[4]);

	/*p = load(p, "wrcpt.txt");
	p = loadTable(p, "table.txt");
	p = loadDistance(p, "etapas.txt");
	*/

	ex = atoi(agrv[2]);

	switch (ex)
	{
	case 1:
		printf("Problema 1:\n");
		Problema1(p);
		break;
	case 2:
		printf("Problema 2:\n");
		Problema2(p);
		break;
	case 3:
		printf("Problema 3:\n");
		Problema3(p);
		break;
	case 4:
		printf("Problema 4:\n");
		Problema4(p);
		break;
	case 5:
		printf("Problema 5:\n");
		Problema5(p);
		break;
	case 6:
		printf("Problema 6:\n");
		Problema6(p);
		break;
	case 7:
		printf("Problema 7:\n");
		Problema7(p);
		break;
	case 8:
		printf("Problema 8:\n");
		Problema8(p);
		break;
	case 9:
		printf("Problema 9:\n");
		Problema9(p);
		break;
	case 10:
		printf("Problema 10:\n");
		Problema10(p);
		break;
	case 11:
		printf("Problema 11:\n");
		Problema11(p);
		break;
	case 12:
		printf("Problema 12:\n");
		Problema12(p);
		break;
	default:
		break;
	}

	if (agrc > 12)
	{
		printf("!!AGRC INVALIDO!!");
	}
}