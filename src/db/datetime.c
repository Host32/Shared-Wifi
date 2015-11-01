#include "datetime.h"

//sprintf: dados numéricos para strings. 

char *format(int number){     
   char    *retorno, ret[100];
   int    i;

   if (number < 10){
      sprintf(ret,"0%d",number);
      retorno = ret;
      return retorno;
   }
   else{
      sprintf(ret,"%d",number);
      retorno = ret;
      return retorno;
   }
}  

char *timesist(void){

   int hora, seg, min;
   char   h[10], m[10], s[10], horas[10];
   char *tmp; 

   struct tm *local;
   time_t tsist;
	
   //deverá retornar um ponteiro, declaração disponível na documentação da Linguagem C.
   tsist = time(NULL);
   local = localtime(&tsist);   
   hora = local -> tm_hour;
   min = local -> tm_min;
   seg = local -> tm_sec;
    
   sprintf(h,"%s",format(hora));
   sprintf(m,"%s",format(min));
   sprintf(s,"%s",format(seg));
   sprintf(horas,"%s:%s:%s",h,m,s);

   tmp = horas;
   return tmp;
}

char *datesist(void){

   int dia,mes,ano;
   char   d[10], m[10], a[10], data[10];
   char *dtp; 

   struct tm *local;
   time_t tsist;
	
   //deverá retornar um ponteiro, declaração disponível na documentação da Linguagem C.
   tsist = time(NULL);
   local = localtime(&tsist);   
   dia = local -> tm_mday;
   mes = local -> tm_mon + 1;
   ano = local -> tm_year + 1900;
    
   sprintf(d,"%s",format(dia));
   sprintf(m,"%s",format(mes));
   sprintf(a,"%s",format(ano));
   sprintf(data,"%s/%s/%s",d,m,a);

   dtp = data;
   return dtp;
}

/* para fins de testes 
int main(){
	char date[50], time[50];
	
	sprintf(date,"%s",datesist());
	sprintf(time,"%s",timesist());
	printf("\n%s - %s\n\n",date, time);
}*/
