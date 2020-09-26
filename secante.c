#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define Secante(a,b,c,d,e,f)   Metodo2(a,b,c,secf,d,e,0,f)




typedef double functionType(double x);
typedef double functionType2(double xa, double xaa, functionType *u);

typedef struct HandleError{
    char type;
    int  Iter;
    char typeDev;
    double tdesvio;
} ErrorType;

ErrorType ErrorHandler;

double pol (double x)
{
    return 21*x*x*x*x-11*x*x*x+19*x*x-11*x-2;
}

double devpol (double x)
{
    return 21*x*x*x*4-11*x*x*3+19*x*2-11;
}

double modulo(double t)
{
    if (t < 0) return -t;
    else return t;
}

int testeErro(double v, double va, double erro)
{
    double desvio;
    if(v>1)
    {
        desvio = modulo(v-va)/v;
        ErrorHandler.typeDev = 'r';
        ErrorHandler.tdesvio = desvio;
    }else
    {
        desvio = modulo(v-va);
        ErrorHandler.typeDev = 'a';
        ErrorHandler.tdesvio = desvio;
    }
    if (desvio == 0) ErrorHandler.typeDev = 'n';
    if(desvio <= erro) return 0;
    else return 1;
}


double Metodo2(double xaa, double xa, functionType *f, functionType2 *g, double erro, int maxIter, int TypeSec, FILE *pont_arq)
{
    int i = 0;
    double x;
    if( (((*f)(xa)*( *f)(xaa)) >= 0)&&(TypeSec == 1) )
    {
        ErrorHandler.type = 'i';
        return 1;
    }
    printf("x = %lf  f(x)= %lf  erro = %lf  iteracao: 0\n",xa,(*f)(xa),ErrorHandler.tdesvio);
    fprintf(pont_arq,"x = %lf  f(x)= %lf  erro = %lf  iteracao: 0\n",xa,(*f)(xa),ErrorHandler.tdesvio);
    for(i=0 ; i<= maxIter ; i++)
    {
        x = (*g)(xa,xaa,f);
        if ( testeErro(x,xa,erro) == 0 )
        {
            ErrorHandler.type = 'n';
            ErrorHandler.Iter = i;
            return x;
        }
        printf("x = %lf  f(x)= %lf  erro = %lf  iteracao: %d\n",x,(*f)(x),ErrorHandler.tdesvio,i+1);
        fprintf(pont_arq,"x = %lf  f(x)= %lf  erro = %lf  iteracao: %d\n",x,(*f)(x),ErrorHandler.tdesvio,i+1);
        if(TypeSec == 1)
        {
            if(((*f)(xa)*(*f)(x))< 0) xaa = x;
            else xa = x;
        }
        else
        {
            xaa = xa;
            xa = x;
        }

    }
    ErrorHandler.type = 'a';
    ErrorHandler.Iter = i ;
    return 1;
}

double secf(double xa, double xaa, functionType *u)
{
    return ((*u)(xa)*xaa -(*u)(xaa)*xa)/((*u)(xa)-(*u)(xaa));
}



int main()
{
    FILE *pont_arq ;
    char frase_erro[20], frase_dsv[20],frase_metodo[20];
    double xa=0,xaa=0,erro,r;
    int ite;
    pont_arq = fopen("arquivo_res_Secante.txt", "w");

    printf("digite x0:");
    scanf("%lf",&xaa);
    printf("digite x1:");
    scanf("%lf",&xa);
    printf("digite erro desejado:");
    scanf("%lf",&erro);
    printf("digite limite iteracao:");
    scanf("%d",&ite);
    r = Secante(xaa,xa,pol,erro,ite,pont_arq);
    strcpy(frase_metodo,"Secante");
    switch (ErrorHandler.type)
    {
    case 'n':
        strcpy(frase_erro,"nenhum");
        break;
    case 'a':
        strcpy(frase_erro,"interacao");
        break;
    case 'i':
        strcpy(frase_erro,"intervalo");
        break;
    }

    switch (ErrorHandler.typeDev)
    {
    case 'n':
        strcpy(frase_dsv,"nenhum");
        break;
    case 'a':
        strcpy(frase_dsv,"absoluta");
        break;
    case 'r':
        strcpy(frase_dsv,"relativo");
        break;
    }

    printf( "%s a/x0 = %f , b/x1 = %f, resultado = %f, iteracao: %d erro: %s tipo desvio: %s\n",frase_metodo, xaa,xa,r,ErrorHandler.Iter, frase_erro,frase_dsv );
    fprintf(pont_arq,"%s a/x0 = %f , b/x1 = %f, resultado = %f, iteracao: %d erro: %s tipo desvio: %s\n",frase_metodo, xaa,xa,r,ErrorHandler.Iter, frase_erro,frase_dsv );
    fclose(pont_arq);
    return 0;
}


