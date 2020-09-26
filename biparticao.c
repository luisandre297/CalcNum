#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BiPati(a,b,c,d,e,f) Metodo1(a,b,c,d,e,f)




typedef double functionType(double x);
typedef double functionType2(double xa, double xaa, functionType *u);

typedef struct HandleError{
    char type;
    int  Iter;
    char typeDev;
    double tdesvio;
} ErrorType;

ErrorType ErrorHandler;


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

double Metodo1(double a, double b, functionType *f, double erro, int maxIter, FILE *pont_arq )
{
    int i = 0;
    double x,xa = 0;
    if(((*f)(a)*(*f)(b)) >= 0)
    {
        ErrorHandler.type = 'i';
        return 1;
    }
    if((*f)(a) == 0 )
    {
        ErrorHandler.type = 'n';
        ErrorHandler.Iter = i;
        ErrorHandler.typeDev = 'n';
        ErrorHandler.tdesvio = 0;
        return a;
    }
    if((*f)(b) == 0 )
    {
        ErrorHandler.type = 'n';
        ErrorHandler.Iter = i;
        ErrorHandler.typeDev = 'n';
        ErrorHandler.tdesvio = 0;
        return b;
    }
    for(i=0 ; i<= maxIter ; i++)
    {
        x = (a+b)/2;
        if((*f)(x) == 0 )
        {
            ErrorHandler.type = 'n';
            ErrorHandler.Iter = i;
            ErrorHandler.typeDev = 'n';
            ErrorHandler.tdesvio = 0;
            return x;
        }
        if ( testeErro(x,xa,erro) == 0 )
        {
            ErrorHandler.type = 'n';
            ErrorHandler.Iter = i;
            return x;
        }
        printf("a = %lf   b = %lf  x = %f f(x)= %lf  erro = %lf  iteracao: %d\n",a,b,x,(*f)(x),ErrorHandler.tdesvio,i+1);
        fprintf(pont_arq,"a = %lf    b = %lf   x = %lf   f(x)= %lf   erro = %lf   iteracao: %d\n",a,b,x,(*f)(x),ErrorHandler.tdesvio,i+1);
        if(((*f)(a)*(*f)(x))<0) b = x;
        else a = x;
        xa = x;
    }
    ErrorHandler.type = 'a';
    return 1;
}


double pol (double x)
{
    return 21*x*x*x*x-11*x*x*x+19*x*x-11*x-2;
}


int main()
{
    FILE *pont_arq ;
    char frase_erro[20], frase_dsv[20],frase_metodo[20];
    double xa=0,xaa=0,erro,r;
    int ite;
    pont_arq = fopen("arquivo_res_bi.txt", "w");

    printf("digite limite inferior intervalo:");
    scanf("%lf",&xaa);
    printf("digite limite superior intervalo:");
    scanf("%lf",&xa);
    printf("digite erro desejado:");
    scanf("%lf",&erro);
    printf("digite limite iteracao:");
    scanf("%d",&ite);
    r = BiPati(xaa,xa,pol,erro,ite,pont_arq);
    strcpy(frase_metodo,"Bissecao");


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


