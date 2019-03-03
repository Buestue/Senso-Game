#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 640
#define HEIGHT 480
#define XPOS 100
#define YPOS 50
#define MAX 5
#define ANGLE_DELTA 20
#define OFFSET 2/5
#define THICKNESS 3

void showMessage();
void gamepad(void);
void gameinit(void);
void gameplay(int);
int gamehuman(int);
int flash(int);
void lose (void);

void fillsector(int,int,int,int,int,int);

int col[] =  { MAGENTA, RED, BLUE, GREEN };
int lcol[] = { LIGHTMAGENTA, LIGHTRED, LIGHTBLUE, LIGHTGREEN };
int xmid, ymid, size;
int com[MAX];
int men[MAX];
char buffer[80];
int round;


int main(void)
{
  int i, failed = 0;
  int win, xsize = WIDTH, ysize = HEIGHT;
  char pkt[30];
               
  win = initwindow(xsize,ysize,"SNS STEP 3",XPOS,YPOS,0,1);

  gamepad();
  neu: 
  showMessage();
  delay(600);
  

  
  gameinit();

  for ( i = 0; i < MAX; i++ ){
    
      gameplay(i);
      gamehuman(i);
      printf("COMPUTER: %i\n %i\n %i\n %i\n %i\n",com[0],com[1],com[2],com[3],com[4]);;
      if(men[i]==com[i]){
      continue;
      }
      else if(men[i]!=com[i]){
      outtextxy((WIDTH/2)-40,(HEIGHT/2)-10,"You Lose");
      delay(1500);
      setcolor(BLACK);
      outtextxy((WIDTH/2)-40,(HEIGHT/2)-10,"You Lose");
      sprintf(pkt, "Punktzahl: %i",i); //PUNKTZAHL
      outtextxy(WIDTH/20,20,pkt);
      setcolor(RED);
      sprintf(pkt, "Punktzahl: %i",i); //PUNKTZAHL
      outtextxy((WIDTH/2)-60,(HEIGHT/2)-10,pkt);
      setcolor (WHITE);
      outtextxy((WIDTH/2)-100,HEIGHT-20,"Presse beliebige Taste");
      
      readkey();
      setcolor(BLACK);
      outtextxy((WIDTH/2)-60,(HEIGHT/2)-10,pkt);
      outtextxy((WIDTH/2)-100,HEIGHT-20,"beliebige Taste druecken");      
      goto neu;
      }
  }
  if(i=MAX){
  outtextxy((WIDTH/2)-40,(HEIGHT/2)-10,"You WIN");
  }
  
  readkey();
	closegraph(win);
	exit(EXIT_SUCCESS);
}

// Hier spielt der Rechner
void gameplay(int imax){

   int i,k=0;
   char pkt[20];


   
    for ( i = 0; i <= imax; i++ ){
      k = com[i];
      fillsector(xmid,ymid,ANGLE_DELTA+k*90,(k+1)*90-ANGLE_DELTA,size,lcol[k]);
      delay(200);//BLINKEN COMPUTER
      fillsector(xmid,ymid,ANGLE_DELTA+k*90,(k+1)*90-ANGLE_DELTA,size,col[k]);
      delay(800); // DELAY  ZWISCHEN DEN BLINKEN
      k++;
    }
    
    
    sprintf(pkt, "Punktzahl: %i",i-1); //PUNKTZAHL
    outtextxy(WIDTH/20,20,pkt);
}
// Hier wird das Spielfeld aufgebaut
void gamepad(){
 	int i;
 	setcolor(WHITE);
	settextstyle(SCRIPT_FONT,HORIZ_DIR,0);
  outtextxy((WIDTH/2)-60,20,"SENSO");

 

  xmid = getmaxx()/2;
  ymid = getmaxy()/2;
  size = (xmid<ymid)?xmid:ymid;
  size *= 0.75;
  for ( i = 0; i < 4; i++ ){
      fillsector(xmid,ymid,ANGLE_DELTA+i*90,(i+1)*90-ANGLE_DELTA,size,col[i]);
  }
}
// Hier werden die Spielfeldsektoren gezeichnet
void fillsector(int x,int y,int sangle,int eangle, int radius,  int color){
  setcolor(WHITE);
  setlinestyle(SOLID_LINE,1,THICKNESS);
  setfillstyle(SOLID_FILL,color);
  sector(x,y,sangle,eangle,radius,radius);
  setfillstyle(SOLID_FILL,BLACK);
  setcolor(BLACK);
  sector(x,y,sangle,eangle,radius*OFFSET,radius*OFFSET);
  fillellipse(xmid,ymid,radius*OFFSET-THICKNESS,radius*OFFSET-THICKNESS);
  setcolor(WHITE);
  setlinestyle(SOLID_LINE,1,THICKNESS);
  arc(xmid,ymid,sangle,eangle,radius*OFFSET);
}
// Hier wird das Spiel initiiert
void gameinit(void){
  int i;
  srand((int) time(NULL));
  for ( i = 0; i < MAX; i++ )
    com[i] = rand()%4;

}


void showMessage(){

  int i;
  int x,y;
  xmid = getmaxx()/2;
  ymid = getmaxy()/2;

  neu:
  setfillstyle(SOLID_FILL,WHITE);
  setcolor(WHITE);
  fillellipse(xmid,ymid,50,50);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
  outtextxy((WIDTH/2)-40,(HEIGHT/2)-10,"New Game");

        while(!ismouseclick(WM_LBUTTONDOWN)){
            }
            getmouseclick(WM_LBUTTONDOWN,&x,&y);
            if (x>(WIDTH/2)-50 && x<(WIDTH/2)+50 && y>(HEIGHT/2)-50 && y<(HEIGHT/2)+50){
            clearmouseclick(WM_LBUTTONDOWN);
            goto weiter;
            }
            else{
            goto neu;
            }
  weiter:
  setfillstyle(SOLID_FILL,BLACK);
  setcolor(BLACK);
  fillellipse(xmid,ymid,50,50);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
  outtextxy((WIDTH/2)-40,(HEIGHT/2)-10,"New Game");
  


}


int gamehuman (round){
int x,y;
int i;

for ( i = 0; i <= round; i++ ){

    while(!ismouseclick(WM_LBUTTONDOWN)){
    }

            getmouseclick(WM_LBUTTONDOWN,&x,&y);
            
            if(x>(WIDTH/2) && y>(HEIGHT/2)){
            men[i]=3;
            clearmouseclick(WM_LBUTTONDOWN);
            flash(3);
            }
            
            if(x>(WIDTH/2) && y<(HEIGHT/2)){
            men[i]=0;
            clearmouseclick(WM_LBUTTONDOWN);
            flash(0);
            }
            
            if(x<(WIDTH/2) && y<(HEIGHT/2)){
            men[i]=1;
            clearmouseclick(WM_LBUTTONDOWN);
            flash(1);
            }
          
            if(x<(WIDTH/2) && y>(HEIGHT/2)){
            men[i]=2;
            clearmouseclick(WM_LBUTTONDOWN);
            flash(2);
            }
            printf("MENSCH: %i\n %i\n %i\n %i\n %i\n",men[0],men[1],men[2],men[3],men[4]);    
    }
    delay(1000); //DELAY DES ERSTEN BLINKENS
    return round;     
}

int flash(k){

  fillsector(xmid,ymid,ANGLE_DELTA+k*90,(k+1)*90-ANGLE_DELTA,size,lcol[k]);
	delay(200);
	fillsector(xmid,ymid,ANGLE_DELTA+k*90,(k+1)*90-ANGLE_DELTA,size,col[k]);	
	return k;
}



