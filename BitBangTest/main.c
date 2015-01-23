#include <stdio.h>
#include <math.h>
 
  
void show_binary(char *msg, unsigned int u, unsigned char length) 
{ 
    
  int t; int i;
  printf(msg);
  printf(" " );
  unsigned int top=pow(2,length-1);
  for(t=top, i=0; t>0; t = t/2,i++) 
  {
    if(u & t) printf("1"); 
    else printf("0"); 
    if(i==7){
        printf(" ");
        i=-1;
    }
  }
 
  printf( "\n");
}

unsigned char getDateTime_FAT(void)
{
    unsigned short dateFAT, timeFAT;
	//Date Bits 0–4: Day of month, valid value range 1-31 inclusive.
	//Date Bits 5–8: Month of year, 1 = January, valid value range 1–12 inclusive.
	//Date Bits 9–15: Count of years from 1980, valid value range 0–127 inclusive (1980–2107).
   
   unsigned char year=15;
   unsigned char month=1;
   unsigned char day=23;
   unsigned char hour=20;
   unsigned char minute=55;
   unsigned char second=26;
   show_binary("year=",year,8);
   dateFAT=(year+20) & 0x7F; //FAT year is the number of years after 1980 (valid values 0 - 127). datetime.date.year is stored 00 to 99, 00 means year 2000, 99 means year 2099
   show_binary("dateFAT=year+20=",dateFAT,16);
   dateFAT=dateFAT<<9;
   dateFAT|= (month & 0x0F)<<5;
   dateFAT|= (day & 0x1F);
   //Time Bits 0–4: 2-second count, valid value range 0–29 inclusive (0 – 58 seconds).
   //Time Bits 5–10: Minutes, valid value range 0–59 inclusive.
   //Time Bits 11–15: Hours, valid value range 0–23 inclusive.
   timeFAT=hour & 0x1F; //5 bits
   timeFAT=timeFAT<<11; //16-5
   timeFAT|= (minute & 0x3F)<<5;  //6 bits, 11-6
   timeFAT|= ((second/2) & 0x3F);  //6 bits, 11-6
   
   show_binary("dateFAT",dateFAT,16);
   show_binary("timeFAT",timeFAT,16);
    
   return 0;
}

int main()
{
     
    getDateTime_FAT();
    return 0;
}

