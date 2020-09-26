#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BiPati(a,b,c,d,e) Metodo1(a,b,c,d,e)
#define Newton(a,b,c,d)   Metodo2(0,a,b,Newtonf,c,d,0)
#define Secante(a,b,c,d,e)   Metodo2(a,b,c,secf,d,e,0)
#define SecanteBi(a,b,c,d,e)   Metodo2(a,b,c,secf,d,e,1)


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

double Metodo1(double a, double b, functionType *f, double erro, int maxIter )
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
        if(((*f)(a)*(*f)(x))<0) b = x;
        else a = x;
        xa = x;
    }
    ErrorHandler.type = 'a';
    return 1;
}




double Metodo2(double xaa, double xa, functionType *f, functionType2 *g, double erro, int maxIter, int TypeSec)
{
    int i = 0;
    double x;
    if( (((*f)(xa)*( *f)(xaa)) >= 0)&&(TypeSec == 1) )
    {
        ErrorHandler.type = 'i';
        return 1;
    }
    for(i=0 ; i<= maxIter ; i++)
    {
        x = (*g)(xa,xaa,f);
        if ( testeErro(x,xa,erro) == 0 )
        {
            ErrorHandler.type = 'n';
            ErrorHandler.Iter = i;
            return x;
        }
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


double Newtonf(double xa, double xaa, functionType *u)
{
    return (*u)(xa);
}

double secf(double xa, double xaa, functionType *u)
{
    return ((*u)(xa)*xaa -(*u)(xaa)*xa)/((*u)(xa)-(*u)(xaa));
}














double polp (double x)
{
    return x-(21*x*x*x*x-11*x*x*x+19*x*x-11*x-2)/(21*x*x*x*4-11*x*x*3+19*x*2-11);
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
    int i,Metodo,ite;


    pont_arq = fopen("arquivo_res.txt", "w");

    printf("digite\n0-para sair \n1- bissecao\n2- newton\n3- secante\n4- secante e bissecao\n :");
    scanf("%d",&Metodo);


    while (Metodo !=0 )
    {
        switch (Metodo)
        {
        case 1:
            printf("digite limite inferior intervalo:");
            scanf("%lf",&xaa);
            printf("digite limite superior intervalo:");
            scanf("%lf",&xa);
            printf("digite erro desejado:");
            scanf("%lf",&erro);
            printf("digite limite iteracao:");
            scanf("%d",&ite);
            r = BiPati(xaa,xa,pol,erro,ite);
            strcpy(frase_metodo,"Bissecao");
            break;
        case 2:
            printf("digite x0:");
            scanf("%lf",&xaa);
            printf("digite erro desejado:");
            scanf("%lf",&erro);
            printf("digite limite iteracao:");
            scanf("%d",&ite);
            r = Newton(xaa,polp,erro,ite);
            strcpy(frase_metodo,"Newton");
            xa = xaa;
            break;
        case 3:
            printf("digite x0:");
            scanf("%lf",&xaa);
            printf("digite x1:");
            scanf("%lf",&xa);
            printf("digite erro desejado:");
            scanf("%lf",&erro);
            printf("digite limite iteracao:");
            scanf("%d",&ite);
            r = Secante(xaa,xa,pol,erro,ite);
            strcpy(frase_metodo,"Secante");
            break;
        case 4:
            printf("digite x0:");
            scanf("%lf",&xaa);
            printf("digite x1:");
            scanf("%lf",&xa);
            printf("digite erro desejado:");
            scanf("%lf",&erro);
            printf("digite limite iteracao:");
            scanf("%d",&ite);
            r = SecanteBi(xaa,xa,pol,erro,ite);
            strcpy(frase_metodo,"SecantBissecao");
            break;
        }

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
        printf("\ndigite\n0-para sair \n1- bissecao\n2- newton\n3- secante\n4- secante e bissecao\n :");
        scanf("%d",&Metodo);
    }




    fclose(pont_arq);
    return 0;
}
