typedef struct h
{
	char e[100];
	int p;
	float t;
	struct H *next;

}*H, SH;

typedef struct En
{
	char nm;
	int n;
	float E;
	int distance;
	struct En *next;

}*EN, en;

typedef struct pilot
{
	char name[50];
	char car[50];
	int number;
	EN stages;
	struct pilot *next;

}*Pilot, SPilot;

typedef struct numPilot
{
	int p;
	struct numPilot * next;

}*NumPilot;

typedef struct infoTable
{
	int pos, numPilot;
	char namePilot[50], carPilot[50];
	int bool;
	float time;
	float prevDif, ldDif;
	struct  infoTable * next;

}*Info, Sinfo;

typedef struct infoSpeed
{
	float avgSpeed;
	char n[100];
	struct infoSpeed * next;

}*InfoSpeed;

int numberOfPilots(Pilot p, int b);
int validateStage(EN e);
int compare(char step[], char nm, int n);
NumPilot insertNumPilot(H h, NumPilot nP);
NumPilot removeNumPilot(NumPilot np);
H insertFileElemToH(H h, char x[], int y, float z);
H removeH(H listaH);
Pilot load(Pilot p, char txt[]);
Pilot loadTable(Pilot p, char *txt[]);
Pilot loadDistance(Pilot p, char *txt[]);
Pilot pilotOrd(H h, Pilot p);
Pilot insertPilot(Pilot p, H h);
Pilot insertNamePilot(Pilot p, char n[], char c[], int num);
Pilot insertAllPilot(Pilot p, H h);
Pilot removePilot(Pilot lista, int num);
EN insertMiddleSteps(char step[], EN e, float t);
EN insertDistance(EN stage, float di, char e1, int ei1);
Info lapTime(Info itb, float time, int num, char n[], char c[],int bool);
Info removeLapTime(Info itb);
InfoSpeed insertAvgSpeedPilot(InfoSpeed avg, char n[], float avgSpeed);