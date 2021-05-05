#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma pack(1)

struct _Endereco{
  	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

typedef struct _Endereco* e;

int cmp(const void *a, const void *b){
  return (*(int *)a - *(int *)b);
}

void inter(char *x, char *y, char *z){
  FILE *a, *b, *s;
  a= fopen(x,"r");
  b= fopen(y,"r");
  s= fopen(z,"w");
  e c, d;
  fread(&c,sizeof(e),1,a);
  fread(&d,sizeof(e),1,b);

 while(!feof(a) && !feof(b)){
   if(cmp(&a,&b)<0){
    fwrite(&a,sizeof(e),1,s);
    fread(&a,sizeof(e),1,a);
   }else{
     fwrite(&b,sizeof(e),1,s);
     fread(&b,sizeof(e),1,b);
   }
 }
 while((!feof(a))){
   fwrite(&a,sizeof(e),1,s);
   fread(&a,sizeof(e),1,a);
 }
 while(!feof(b)){
   fwrite(&b,sizeof(e),1,s);
   fread(&b,sizeof(e),1,b);
 }
 fclose(a);
 fclose(b);
 fclose(s);
}

void cala(char v[31][15], e ab, int num){
  qsort(ab,num,sizeof(e), cmp);
  for(int j=0;j<17;j++){
    int v1=1,v2=2,v3=17;
    inter(v[v1],v[v2],v[v3]);
    v1=v1+2;
    v2=v2+2;
    v3++;
  }
}


int main(int argc, char *argv[]){
  FILE *a, *s;
  e *ed;
  a=fopen("cep.dat","r");
  fseek(a,0,SEEK_END);
  long x= ftell(a);
  long y=x/sizeof(e);
  int w=16;
  long z=y/w;
  ed=(e*) malloc(z*sizeof(e));
  fseek(a,0,SEEK_SET);
  int i=0;
  char c2[31][15];
  while(i<=15){
    char c[15];
    sprintf(c,"%d.dat",i);
    s=fopen(c,"w");
    c2[i][0]=c[i];
    fwrite(ed,sizeof(e),z,s);
    fclose(s);
    i++;
  }
  fclose(a);
  free(ed);
  cala(c2, *ed, z);
  return 0;
}
