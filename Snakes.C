#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define INC 1
#define DEC 2
#define OUT 3
void playgame();
void navigate(char);
int decidestatus();
void randomboxes();
void decideposition();
void displayscreen();
void quitgame();
void disptime();
void save();
void openfile();
void splashscreen();
unsigned short int 	dtime=0,
			maxx=0,
			maxy=0,
			temptime=6,
			randx=0,
			randy=0,
			flag=INC;
unsigned int n=0, score=0;
int x1, y1, x2, y2;
int *P, *Q;
struct playerinfo
{
	char name[20];
	unsigned short int stime;
};
struct playerinfo player;
void main()
{
	int gdriver=DETECT, gmode;
	auto unsigned short char s=0;
	initgraph(&gdriver, &gmode, "");
	srand((unsigned)time(NULL));
	cleardevice();
	maxx=getmaxx();
	maxy=getmaxy();
	splashscreen();
	printf("Enter your name\n");
	scanf("%[^\n]s", &player.name);
menu:	cleardevice();
	settextstyle(0, 0, 4);
	outtextxy(maxx/3, 0, "MENU");
	printf("1-PLAY GAME\n");
	printf("2-RULES\n");
	printf("3-CONTROLS\n");
	printf("4-HIGH SCORES\n");
	printf("ANY OTHER KEY-EXIT");
	fflush(stdin);
	s=getche();
	cleardevice();
	switch(s)
	{
	case '1':
		playgame();
		getch();
		closegraph();
		break;
	case '2':
		clrscr();
		cleardevice();
		printf("\t\t\tSERPENT\n\
I suppose you've played the old snakes game which was\n\
quite popular on basic Nokia phones. This game is \n\
just a different version of that one.\n\
1) All you've to do is to make the snake survive as\n\
long as possible.\n\
2) The snake leaves a coloured trail behind as it traverses\n\
along the diffrent paths through which you guide.\n\
3) The snake can not traverse the path which it had been on.\n\
4) However, the trail isn't continuous. It fragments at certain\n\
places which is purely random.\n\
5) The snake may traverse through the space between\n\
these broken fragments.\n\
6) The snake is also faced with another challenge -\n\
random boxes flash on the screen every 5 seconds\n\
which serve as an obstruction and the serpent shouldn't\n\
try to traverse through them.\n\
7) The snake may move out of the screen and if it does so,\n\
it will appear at the side opposite to which it went earlier.\n");
		getch();
		clrscr();
		cleardevice();
		goto menu;
	case '3':
		settextstyle(0, 0, 4);
		outtextxy(maxx/3, 0, "CONTROLS");
		printf("\nW-UP\nS-DOWN\nA-LEFT\nD-RIGHT\nQ-QUIT\n");
		getch();
		clrscr();
		cleardevice();
		goto menu;
	case '4':
		clrscr();
		cleardevice();
		printf("\t\tHIGH SCORES\n\n\n");
		printf("PLAYER NAME\tTIME OF SURVIVAL\tPLAYED ON\n");
		openfile();
		getch();
		clrscr();
		cleardevice();
		goto menu;
	default:
		exit(0);
	}
}
void playgame()
{
	char c='\0';
	register unsigned short int setcolor=0;
	x1=y1=200;
	x2=y2=215;
	P=&x1;
	Q=&x2;
	line(0, maxy*9/10, maxx, maxy*9/10);
	while(1)
	{
		switch(flag)
		{
		case INC:
			(*P)++;
			(*Q)++;
			break;
		case DEC:
			(*P)--;
			(*Q)--;
			break;
		default:
			break;
		}
		decideposition();
		if(n%55==0)
			setcolor=rand()%16;
		setfillstyle(SOLID_FILL, setcolor);
		bar(x1, y1, x2, y2);
		randomboxes();
		if(decidestatus())
			quitgame();
		if(kbhit())
		{
			c=getche();
			c=tolower(c);
			if(c=='q')
				quitgame();
			navigate(c);
			while(kbhit()) getch();
		}
		disptime();
	}
}
void navigate(char c)
{
	switch(c)
	{
	case 'w':
		if(!(P==&y1 && Q==&y2))
		{
			P=&y1;
			Q=&y2;
			flag=DEC;
		}
		break;
	case 'd':
		if(!(P==&x1 && Q==&x2))
		{
			P=&x1;
			Q=&x2;
			flag=INC;
		}
		break;
	case 's':
		if(!(P==&y1 && Q==&y2))
		{
			P=&y1;
			Q=&y2;
			flag=INC;
		}
		break;
	case 'a':
		if(!(P==&x1 && Q==&x2))
		{
			P=&x1;
			Q=&x2;
			flag=DEC;
		}
		break;
	}
}
int decidestatus()
{
	register unsigned short int color1=0, color2=0;
	switch(flag)
	{
	case INC:
		if(P==&x1 && Q==&x2)
		{
			color1=getpixel(x1+16, y1);
			color2=getpixel(x2+1, y2);
		}
		if(P==&y1 && Q==&y2)
		{
			color1=getpixel(x1, y1+16);
			color2=getpixel(x2, y2+1);
		}
		break;
	case DEC:
		if(P==&x1 && Q==&x2)
		{
			color1=getpixel(x1-1, y1);
			color2=getpixel(x2-16, y2);
		}
		if(P==&y1 && Q==&y2)
		{
			color1=getpixel(x1, y1-1);
			color2=getpixel(x2, y2-16);
		}
		break;
	}
	if(color1!=0 || color2!=0)
		return OUT;
	else
		return 0;
}
void disptime()
{
	char stime[14];
	char stemptime[14];
	char ttime[]="Total time:";
	sprintf(stime, "%d", dtime);
	sprintf(stemptime, "Next:%d", temptime);
	setfillstyle(SOLID_FILL, BLACK);
	bar(0, maxy*10/11, maxx, maxy);
	setfillstyle(SOLID_FILL, WHITE);
	settextstyle(0, 0, 1);
	outtextxy(maxx*7/11, maxy*10/11, stemptime);
	strcat(ttime, stime);
	outtextxy(0, maxy*10/11, ttime);
	(n%55==0)?dtime++:0;
	(n%55==0)?temptime--:0;
	n++;
	delay(20);
}
void randomboxes()
{
	if(temptime==0)
	{
		register short unsigned int x=0;
		setfillstyle(SOLID_FILL, rand()%14+1);
		for(x=0; x<4; x++)
		{
			randx=rand()%maxx;
			randy=rand()%maxy;
			if(getpixel(randx, randy)==0 &&
			getpixel(randx+15, randy+15)==0 &&
			getpixel(randx+15, randy-15)==0 &&
			getpixel(randx-15, randy-15)==0)
				bar(randx, randy, randx+40, randy+40);
		}
		temptime=6;
	}
}
void decideposition()
{
	if(x1<=0)
	{
		x1=maxx-16;
		x2=maxx-1;
	}
	else if(x1==maxx)
	{
		x1=0;
		x2=15;
	}
	if(y1<=0)
	{
		y1=maxy*9/10-16;
		y2=maxy*9/10-1;
	}
	else if(y2==(maxy*9/10-1))
	{
		y1=0;
		y2=15;
	}
}
void displayscreen()
{
	register unsigned short int l=0;
	while(l<2000)
	{
		gotoxy(rand()%80, rand()%24);
		textcolor(rand()%14+1);
		cprintf("%c", 219);
		l++;
		delay(1);
	}
	l=0;
	while(l<5000)
	{
		gotoxy(rand()%80, rand()%24);
		textcolor(BLACK);
		cprintf("%c",219);
		l++;
		delay(1);
	}
	textcolor(WHITE);
	gotoxy(80/3,24/4);
	cprintf("Your score:%d", dtime*20);
	gotoxy(80/3,24/4+1);
	cprintf("You survived for:%d s", dtime);
	getch();
}
void quitgame()
{
	cleardevice();
	settextstyle(0, 0, 14);
	outtextxy(0, maxy/3, "HISS!");
	player.stime=dtime;
	save();
	getch();
	closegraph();
	displayscreen();
	exit(0);
}
void linkfloat()
{
	float a=0, *b;
	b=&a;
	a=*b;
}
void save()
{
	FILE *F;
	time_t t;
	F=fopen("SAVE.txt", "a");
	if(F==NULL)
	{
		printf("Can't open SAVE.txt\n");
		closegraph();
		exit(0);
	}
	time(&t);
	fprintf(F, "%s\t\t\t%d\t\t%s", player.name, player.stime, ctime(&t));
	fclose(F);
}
void openfile()
{
	FILE *F;
	char ch='\0';
	F=fopen("SAVE.txt", "r");
	if(F==NULL)
	{
		printf("Can't open SAVE.txt\n");
		closegraph();
		exit(0);
	}
	while(ch!=EOF)
	{
		ch=fgetc(F);
		printf("%c", ch);
	}
	fclose(F);
}
void splashscreen()
{
	char s[]="S";
	char n[]="N";
	char a[]="A";
	char k[]="K";
	char e[]="E";
	register unsigned short int m=0;
	clrscr();
	cleardevice();
	for(m=0; m<2; m++)
	{
		settextstyle(0, 0, 10);
		setcolor(rand()%14+1);
		outtextxy(0, maxy/3, s);
		settextstyle(0, 0, 9);
		setcolor(rand()%14+1);
		delay(200);
		outtextxy(75, maxy/3-1, n);
		settextstyle(0, 0, 8);
		setcolor(rand()%14+1);
		delay(150);
		outtextxy(150, maxy/3-2, a);
		settextstyle(0, 0, 7);
		setcolor(rand()%14+1);
		delay(100);
		outtextxy(225, maxy/3-3, k);
		settextstyle(0, 0, 6);
		setcolor(rand()%14+1);
		delay(50);
		outtextxy(300, maxy/3-4, e);
		settextstyle(0, 0, 5);
		setcolor(rand()%14+1);
		delay(10);
		outtextxy(375, maxy/3-5, s);
		delay(1000);
		clrscr();
		cleardevice();
	}
	setcolor(WHITE);
	settextstyle(0, 0, 2);
}