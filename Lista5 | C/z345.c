#include <unistd.h> // chdir 
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> // strerror
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KRED  "\x1B[31m"
#define KWHT  "\x1B[37m"
#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);
void obslugaRury(char str[]);
void wykonajRure(char ***cmd);
//void obslugawyjbl(char str[]);
//void oblslugawyjscia(char str[]);
void obslugawejscia(char polecenie[]);
void zapiszDoPliku( char plik[], char tekst[]);
void czytajZPliku(char plikO[]);
int MAX=100;
char *plikowe[30];
char doZabicia[50];
bool wyjscie = false;
bool wejscie = false;
bool wyjbl = false;
bool amp = false;
int dl_pol=0; //dlugosc polecenia

int jobs[20];
int jobnumber=0;
    int jobDoZabicia = 0; 


int procesToKillId=NULL;
int main()
{
 pid_t pid;
 pid_t wpid;
char polecenie[100];
char katal[100];

char nowykatalog[20]; //katalog do ktorego wchodze
		char tmp[35];
char tmp2[35];
		int iter=0;
int tmpnum=0;
 int status;

bool potok= false;
bool czyStopped[20];
for(int i=0;i<20;i++) {czyStopped[i]=false;}	
bool CzyRowne(char zabijam[100],char proces[100])
{
int dl1=0;
int dl2=0;		
while(zabijam[dl1]!=NULL){dl1++;}
while(proces[dl2]!=NULL){dl2++;}
if(dl1 != dl2) return false;
else
{
	for(int i=0;i<dl1;i++)
	{
		if(zabijam[i] != proces[i]){ return false;    printf("nie ma takiego procesu");}
	}
	return true;	
}

}




void ls_f(char di[100])
{

char *argv[3];
argv[0] = "ls";
argv[1] = di;
argv[2] = NULL;

/*te if-y i else-y to sa bo program sie sam zamykal od rozu*/
 if (fork() == 0)
  {
   if (execvp(argv[0], argv) == -1)
    printf("%s\n", strerror(errno));
   exit(0);
  }
  else
  {
  	wait(&status);
  }

}



char c;

do
{
/*czyszcze tablice*/ for(int i=0;i<99;i++) {polecenie[i]=NULL;}	
potok=false;
wyjscie=false;
wejscie=false;
/* drukuje obecny katalog */
    printf("%s%s: %s",KRED,getcwd(katal, 100),KWHT); 
/* pobiera polecenie */
	gets(polecenie);
/*badam z czym mam do czynienia*/
		dl_pol=0;
		potok=false;
		/*licze ile ma znakow*/
		while(polecenie[dl_pol]!=NULL)
		{		
			dl_pol++;
			
		}
  if (dl_pol == 0)
  {
	c=getchar();
   if (c == EOF)  exit(0);
   continue;
  }
		/*sprawdzam czy ostatni znak to &*/
		if(polecenie[dl_pol-1]=='&')
		{
			   amp = true;
			printf("to zostalo w tle uruchamiane\n");
			polecenie[dl_pol-1]=NULL;
			dl_pol--;
		}

		/*sprawdzam czy to potok*/
		for(int i=0; i< (dl_pol-2); i++)
		{
			if(polecenie[i]=='|' && polecenie[i+1]==' ') {
				potok=true;
				   obslugaRury(polecenie);
			}
//--------------------------------------------------------------------------------
			if(polecenie[i]==' ' && polecenie[i+1]=='>') {
				wyjscie=true;
				  
		/*czyszcze tablice*/ for(int i=0;i<35;i++) {tmp[i]=NULL; tmp2[i]=NULL;}	
		char *argv[3];
		/*rozdzielam polecenia, tak aby dalo sie je wykonac*/
		iter=0;
			/*1-wszy arg*/
			while(polecenie[iter]!=' ')
			{
				tmp[iter]=polecenie[iter];
				iter++;
			}
		argv[0]=tmp;
		//printf("%s\n",argv[0]);
		iter++;
iter++;
iter++;
		tmpnum=0;
			/*2-gi arg*/
			while(iter<dl_pol)
			{
				tmp2[tmpnum]=polecenie[iter];
				tmpnum++;
				iter++;
			}
		argv[1]=tmp2;
		//printf("%s",argv[1]);
		argv[2] = NULL;
char *argc[3];
argc[0] = "ls";
argc[1] = katal;
argc[2] = NULL;


  int link[2];
  pid_t pidpok;
  char foo[4096];

  if (pipe(link)==-1)
    die("pipe");

  if ((pidpok = fork()) == -1)
    die("fork");

  if(pidpok == 0) {

    dup2 (link[1], STDOUT_FILENO);
    close(link[0]);
    close(link[1]);
    execl("/bin/ls", "ls", "-1", (char *)0);
    die("execl");

  } else {

    close(link[1]);
    int nbytes = read(link[0], foo, sizeof(foo));
    zapiszDoPliku(argv[1],foo);
    wait(NULL);

  }

			}	
//-----------------------------------------------------------------------------------	
			if(polecenie[i]=='<') {
				wejscie=true;

		/*czyszcze tablice*/ for(int i=0;i<35;i++) {tmp[i]=NULL; tmp2[i]=NULL;}	
		char *argv[3];
		/*rozdzielam polecenia, tak aby dalo sie je wykonac*/
		iter=0;
			/*1-wszy arg*/
			while(polecenie[iter]!=' ')
			{
				tmp[iter]=polecenie[iter];
				iter++;
			}
		argv[0]=tmp;
		printf("%s",argv[0]);
		iter++;
iter++;
iter++;
		tmpnum=0;
			/*2-gi arg*/
			while(iter<dl_pol)
			{
				tmp2[tmpnum]=polecenie[iter];
				tmpnum++;
				iter++;
			}
		argv[1]=tmp2;
		printf("%s",argv[1]);
		argv[2] = NULL;
				czytajZPliku(argv[1]);  
			}	
			if(polecenie[i]=='2' && polecenie[i+1]=='>') {
				wyjbl=true;
				  // obslugawyjbl(polecenie);
			}		
		}


if(!potok && !wyjscie && !wejscie && !wyjbl)
{

/* pomoc */
	if(strcmp(polecenie,"pomoc")==0)
	{
		printf("informacje\n");
		printf("jobs - pokazuje procesy \n");
		printf("start [pid] - wznawia proces \n");
		printf("zabij [pid] -zabija proces \n");
		printf("koniec - zamyka program\n");
	}
/* cd */
	if(polecenie[0]=='c' && polecenie[1]=='d')
	{
		if(polecenie[3]=='.' && polecenie[4]=='.')
		{
			// uzycie komendy cd ..
			chdir(".."); 
		}
		dl_pol=0;
		/*licze ile ma znakow nowy katalog*/
		while(polecenie[dl_pol]!=NULL)
		{	
			dl_pol++;
		}
		/*Czyszcze tablice*/
		for(int i=0;i<20;i++)
		{
			nowykatalog[i]=NULL;	
		}
		/*Odczytuje jak wyglada nazwa nowego katalogu*/
		for(int i=3;i<=(dl_pol-1);i++)
		{
			nowykatalog[i-3]=polecenie[i];
		}
				//execl("/bin/sh", "-c", "kat", (const char *)0);
			//execl("/bin/sh", "-c", "cd", (const char *)0);
			chdir(nowykatalog);
	}
/* ls */			
	if(strcmp(polecenie,"ls")==0)
	{
		ls_f(katal);
	}
/* startujj */
if(polecenie[0]=='s' && polecenie[1]=='t' && polecenie[2]=='a'&& polecenie[3]=='r' && polecenie[4]=='t')
{
		doZabicia[0]=polecenie[6];
		doZabicia[1]=polecenie[7];
		doZabicia[2]=polecenie[8];
		doZabicia[3]=polecenie[9];
	jobDoZabicia = atoi(doZabicia); 
    usleep(jobDoZabicia);
printf("%sstartuje numer PID:%d%s\n",KGRN,jobDoZabicia,KWHT);
for(int i=0;i<jobnumber;i++)
{
if(jobs[i]==jobDoZabicia) czyStopped[i]=false;
}

kill (jobDoZabicia,SIGCONT);
jobDoZabicia=0;
}
/* zatrzymaj */
if(polecenie[0]=='s' && polecenie[1]=='t' && polecenie[2]=='o'&& polecenie[3]=='p')
{
		doZabicia[0]=polecenie[5];
		doZabicia[1]=polecenie[6];
		doZabicia[2]=polecenie[7];
		doZabicia[3]=polecenie[8];
	jobDoZabicia = atoi(doZabicia); 
    usleep(jobDoZabicia);
printf("%szatrzymuje numer PID: %d%s\n",KYEL,jobDoZabicia,KWHT);
for(int i=0;i<jobnumber;i++)
{
if(jobs[i]==jobDoZabicia) czyStopped[i]=true;
}
kill (jobDoZabicia,SIGSTOP);
jobDoZabicia=0;
}


/* zabij */			
	if(polecenie[0]=='z' && polecenie[1]=='a' && polecenie[2]=='b'&& polecenie[3]=='i'&&polecenie[4]=='j' )
	{
		doZabicia[0]=polecenie[6];
		doZabicia[1]=polecenie[7];
		doZabicia[2]=polecenie[8];
		doZabicia[3]=polecenie[9];
	jobDoZabicia = atoi(doZabicia); 
    usleep(jobDoZabicia);
printf("zabijam numer PID:%d\n",jobDoZabicia);
kill(jobDoZabicia,SIGKILL);
for(int i=0;i<jobnumber;i++)
{
if(jobs[i]==jobDoZabicia) jobs[i]=0;
}
jobDoZabicia=0;
	}
/* jobs */
	if(polecenie[0]=='j' && polecenie[1]=='o' && polecenie[2]=='b'&& polecenie[3]=='s')
{
	for(int i=0;i<jobnumber;i++)
	{
		printf("PID: %d\n",jobs[i]);
		if(czyStopped[i]) printf("zatrzymany proces PID: %d\n",jobs[i]);
	}
}

/* inne */
	if(strcmp(polecenie,"ls")!=0 && !(polecenie[0]=='c' && polecenie[1]=='d')&& strcmp(polecenie,"pomoc")!=0 && !(polecenie[0]=='z' && polecenie[1]=='a' && polecenie[2]=='b'&& polecenie[3]=='i'&&polecenie[4]=='j' )&&!(polecenie[0]=='j' && polecenie[1]=='o' && polecenie[2]=='b'&& polecenie[3]=='s')&&!(polecenie[0]=='s' && polecenie[1]=='t' && polecenie[2]=='o'&& polecenie[3]=='p')&& !(polecenie[0]=='s' && polecenie[1]=='t' && polecenie[2]=='a'&& polecenie[3]=='r' && polecenie[4]=='t'))
	{


		/*czyszcze tablice*/ for(int i=0;i<35;i++) {tmp[i]=NULL; tmp2[i]=NULL;}	
		char *argv[3];
		/*rozdzielam polecenia, tak aby dalo sie je wykonac*/
		iter=0;
			/*1-wszy arg*/
			while(polecenie[iter]!=' ')
			{
				tmp[iter]=polecenie[iter];
				iter++;
			}
		argv[0]=tmp;
		iter++;
		tmpnum=0;
			/*2-gi arg*/
			while(iter<dl_pol)
			{
				tmp2[tmpnum]=polecenie[iter];
				tmpnum++;
				iter++;
			}
		argv[1]=tmp2;
		argv[2] = NULL;
		/*wykonuje polecenie*/
/* I sposob*/
pid = fork();
 if (fork() == 0)
  {
   if (execvp(argv[0], argv) == -1)
    printf("%s\n", strerror(errno));
   exit(0);
  }
  else
  {
  	 if (!amp) {
		wait(&status);
		setpgid(0,0);
		procesToKillId = pid;
		}
	else {
		setpgid(0,0);
		jobs[jobnumber] = pid;
		printf("numer PID:%d\n",jobs[jobnumber]);
		jobnumber++;
	}//setpgid(1,0);
  }
amp = false;
/*II sposob*//*
pid = fork();
if( pid==0)
    {
        //child code
        {
            perror("cos poszlo nie tak....");
        }
        exit(0);
    }
    else
    {
        if( pid < 0)
        {
            perror("cos poszlo nie tak....");
        }
        else
        {
              if(amp)
              {
                //przydzielamy dziecko do innego procesu niech on będzie musiał je zabić!
                setpgid(0,0);
              }
              else
              {
                procesToKillId = pid;
                wpid = waitpid(pid, &status, 0);
              }
              
        }
        
    }
/*Koniec 2 sposobu*/
		/*czyszcze tablice*/ for(int j=0;j<35;j++) {tmp2[j]=NULL;}	
					for(int j=0;j<35;j++) {tmp[j]=NULL;}	
	}



}


} while(strcmp(polecenie,"koniec"));


for(int i=0;i<jobnumber;i++)
{
kill(jobs[i],SIGKILL);
}
return 0;
}
//-------------------------------------------------
void czytajZPliku(char plikO[])
{
    int znak;
    FILE *plik = fopen( plikO, "r" );   // otwieramy plik do odczytu

    znak = getc( plik ); 
    while( znak != EOF )                  //pętla odczytująca po jednym znaku z pliku
    {
        printf( "%c", znak );             //do napotkania znaku końca pliku EOF
        znak = getc( plik );
    } 
    fclose( plik );                       //zamykamy plik

}

//-------------------------------------------

void obslugawejscia(char polecenie[])
{
 char **tabrura[MAX];
 char *tabtemp[MAX];
 int i = -1;
 char *s = strtok(polecenie, "<");
 char *s2;

 while (s != NULL)
 {
  i++;
  tabtemp[i] = s;
  s = strtok(NULL, "|");
 }
printf("%s",tabtemp);
}
//--------------------------------------------
void zapiszDoPliku( char plik[], char tekst[])
{
FILE *fp;
   if ((fp=fopen(plik, "w"))==NULL) {
     printf ("Nie mogę otworzyć pliku do zapisu!\n");
     exit(1);
     }
   fprintf (fp, "%s", tekst); /* zapisz nasz łańcuch w pliku */
   fclose (fp); /* zamknij plik */

}

//--------------------------------------------

void obslugaRury(char str[])
{
 char **tabrura[MAX];
 char *tabtemp[MAX];
 int i = -1;
 char *s = strtok(str, "|");
 char *s2;

 while (s != NULL)
 {
  i++;
  tabtemp[i] = s;
  s = strtok(NULL, "|");
 }

 for (int x=0; x<=i; x++)
 {
  char **ruraPart;
  ruraPart = malloc(sizeof(char *) * MAX);
  s2 = strtok(tabtemp[x], " ");
  int p = -1;

  while (s2 != NULL)
  {
   p++;
   ruraPart[p] = s2;
   s2 = strtok(NULL, " ");
  }

  p++;
  ruraPart[p] = NULL;
  tabrura[x] = ruraPart;

 }

tabrura[i+1] = NULL;
wykonajRure(tabrura);

for (int x=0; x<=i; x++)
 free(tabrura[x]);

}






void wykonajRure(char ***cmd)
{
 int tabp[2];
 pid_t pid;
 int fd_in =0;
 int status;

 while (*cmd != NULL)
 {
  pipe(tabp);

  if ((pid = fork()) == -1)  exit(1);

  else if (pid == 0)
  {
   dup2(fd_in, 0);
   if (*(cmd +1) != NULL)  dup2(tabp[1], 1);
 
   close(tabp[0]);
   execvp((*cmd)[0], *cmd);
   exit(0);
  }

  else
  {
   wait(&status);
   close(tabp[1]);
   fd_in = tabp[0];
   cmd++;
  }
 }

}

