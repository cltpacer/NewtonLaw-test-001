


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

  typedef struct jhghgkj
{
    int ooo;
    void (*ptr) (double x, double y,  double *p);
    
} FPDEF002;

FPDEF002 ppp;


typedef struct doubleptr
{
   double *ptr;
} CLTDoublePTR ;

CLTDoublePTR dxx;


double g_double_do_not_used;




////////////////////////////////////////////////////////////////////////

//void (*foo)(int);

////////////////////////////////////////////////////////////////////////
void f_test_0099 (double x, double y, double *ptr ) 
{
    
// y= x^2
double ret;

 ret =   pow(x,2);

// ret = x;

*ptr = ret ;

//return ret;

}

////////////////////////////////////////////////////////////////////////
void integral_002( FPDEF002 ppp , 
double from, double to, double num, CLTDoublePTR ans)
{
    
    double ret002;
double x;
double z = 0.00000000001 ;
double delta_x = (to-from)/num ;     // 0.0001;

printf("\n\n  delta_x = %lf \n\n ", delta_x  );

double sum =0;
ret002 = 0;
for(x = z; x< to ; x = x + delta_x)
{
    (*(ppp.ptr))(  x ,8 , &ret002);   
    
    sum += ret002*delta_x;
    
}

(*(ans.ptr))  = sum; 
//*ret = ret002;

}
////////////////////////////////////////////////////////////////////////
int test_main_005()
{
    
dxx.ptr = &g_double_do_not_used;
ppp.ooo = 5;
ppp.ptr = &f_test_0099;

double in_001,in_002,in_003,in_004,in_005,temp;
double *ptr_double;
ptr_double = &temp;

in_001 = 0.0000000001;
in_002 = 10.00000001;
in_003 = 100000;

//class math_int 
//{
// int k,j,i;   
//}

int   flag ;


double ans;
ans =0;
                        //  copy from K&R BOOK example
                        //  K&R are two people who invent c language 
                        //  I saw this example before in text book 
    //void (*ptr_f)(double , double,  double *);   
    //ptr_f= &f_test;
    
   // FPDEF002  ptr_f ;
    //ptr_f.ptr = 
//int integral_002(double (*ptr)(double , double ),
//double from, double to, double num, double *ret)


double *p;
p = &ans;

dxx.ptr = p;


integral_002  ( ppp ,  in_001 , in_002  ,  in_003 ,  dxx )  ;

printf(" \n  ans = %lf \n ", ans);



}
/////////////////////////////////////////////////////////////////////////
