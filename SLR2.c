/* 0. S->E   */
/* 1. E->E+T  */
/* 2. E->T     */
/* 3. T->T*P   */
/* 4. T->P  */
/* 5. P->i    */
/* 6. P->(E)  */

#include "stdio.h"
#include "conio.h"
#define MAX 20

typedef struct{
  char left;
  int  length;
} production;

void create_production(production p[7])
{
 p[0].left='S';   p[0].length=1;
 p[1].left='E';   p[1].length=3;
 p[2].left='E';   p[2].length=1;
 p[3].left='T';   p[3].length=3;
 p[4].left='T';   p[4].length=1;
 p[5].left='P';   p[5].length=1;
 p[6].left='P';   p[6].length=3;
}

typedef struct{
 short data[20];
 int top;
} state_stack;

typedef struct{
 char data[20];
 int  top;
} char_stack;

void init_state_stack(state_stack *st)
{
 st->top=0;
}

void init_char_stack(char_stack *st)
{
 st->top=0;
}

void state_push(state_stack *st,int s)
{
 if(st->top==MAX-1) { printf("\nstack is full!"); getch();exit(0); }
 st->data[st->top]=s;
 st->top++;
}

void char_push(char_stack *st,char ch)
{
 if(st->top==MAX-1) { printf("\nstack is full!"); getch();exit(0); }
 st->data[st->top]=ch;
 st->top++;
}

void state_pop(state_stack *st)
{
 if(st->top==0) { printf("\nstack is empty!"); getch();exit(0);}
  st->top--;
}

void char_pop(char_stack *st)
{
 if(st->top==0) { printf("\nstack is empty!"); getch();exit(0);}
  st->top--;
}

int read_state(state_stack *st)
{
  return st->data[st->top-1];
}

char read_char(char_stack *st)
{
  return st->data[st->top-1];
}

void error()
{
  printf("\nerror!");
  getch();
  exit(0);
}

int ch_to_int(char ch)
{
  int i;
  switch(ch)
  {
   case '+':i=0;break;
   case '*':i=1;break;
   case 'i':i=2;break;
   case '(':i=3;break;
   case ')':i=4;break;
   case '#':i=5;break;
   case 'E':i=6;break;
   case 'T':i=7;break;
   case 'P':i=8;break;
   default: printf("\ncharacter is false!");getch();exit(0);
  }
  return i;
}

void SLR_driver(state_stack *state,char_stack *input,char action[12][6],
                  int SLR_goto[12][9], production p[7] )
{
  int s,k,l,m;
  char c,ch;
  s=read_state(state);
  ch=read_char(input);
  printf("s=%d,ch=%c",s,ch);
  while(1)
  {  

     k=ch_to_int(ch);
     c=action[s][k];
    
     switch(c)
     {
     case 's': state_push(state,SLR_goto[s][k]); char_pop(input); break;
     case 'r': m=SLR_goto[s][k];
               for(l=p[m].length;l>0;l--)
                 state_pop(state);
               state_push(state,SLR_goto[read(state)][ch_to_int(p[m].left)]);
               break;
     case 'a': printf("\naccept!"); getch(); exit(0);
     default: error();
     }
   
     s=read_state(state);
     ch=read_char(input);
    printf("\ns=%d,ch=%c",s,ch);
 }
}
main()
{
  char c,ch[MAX];
  int i=0,j;
  state_stack state;
  char_stack input;
  char action[12][6]={
      {'0','0','s','s','0','0'},
      {'s','0','0','0','0','a'},
      {'0','0','s','s','0','0'},
      {'r','r','0','0','r','r'},
      {'r','r','0','0','r','r'},
      {'0','0','s','s','0','0'},
      {'r','s','0','0','r','r'},
      {'0','0','s','s','0','0'},
      {'r','r','0','0','r','r'},
      {'r','r','0','0','r','r'},
      {'r','s','0','0','r','r'},
      {'s','0','0','0','s','0'}};
  int SLR_goto[12][9]={
      {-1,-1,4,5,-1,-1,1,6,3},
      {2,-1,-1,-1,-1,-1,-1,-1,-1},
      {-1,-1,4,5,-1,-1,-1,10,3},
      {4,4,-1,-1,4,4,-1,-1,-1},
      {5,5,-1,-1,5,5,-1,-1,-1},
      {-1,-1,4,5,-1,-1,11,6,3},
      {2,7,-1,-1,2,2,-1,-1,-1},
      {-1,-1,4,5,-1,-1,-1,-1,8},
      {3,3,-1,-1,3,3,-1,-1,-1},
      {6,6,-1,-1,6,6,-1,-1,-1},
      {1,7,-1,-1,1,1,-1,-1,-1},
      {2,-1,-1,-1,9,-1,-1,-1,-1}};
   
  production p[7];

  create_production(p);
  init_char_stack(&input);
  init_state_stack(&state);

  printf("\ninput a string:");
  scanf("%c",&c);
  while(c!='#')
   {
    ch[i]=c;
    i++;
    scanf("%c",&c);
   }
  
  ch[i]='#';
  for(j=i;j>=0;j--) printf("%c",ch[j]);
  for(j=i;j>=0;j--)
    char_push(&input,ch[j]); 
  state_push(&state,0);
 
  SLR_driver(&state,&input,action,SLR_goto,p);
}
