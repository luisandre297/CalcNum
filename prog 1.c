#include <stdio.h>
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
        xaa = xa;
        xa = x;
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
    double r;
    functionType *g;
    r = BiPati(-1,0,pol,0.00001,100);
    printf("%f %c %d %f",r,ErrorHandler.type, ErrorHandler.Iter, ErrorHandler.tdesvio );
    return 0;
}
