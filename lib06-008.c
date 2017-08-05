

///////////////////////////////////////////////////////////////
//
//
//   lib06.c   v008
//
//   high  school  physic text book  project
//   verify  Newtone law in real earth mass, R
//   2017-08-01
//
//     v007   2017-08-05
//  
//      david Tang Taiwan
//
//  Christmas meaning is not the exact day, 
//        but  his love .....
//
//  https://www.youtube.com/watch?v=SJeTGs92UKU
//  https://www.youtube.com/watch?v=RSJbYWPEaxw
//  https://www.youtube.com/watch?v=1H0ou7FvNJY
//
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// #include <tgmath.h>

#ifndef    PRJ_NTTEST
#define    PRJ_NTTEST  1

#define    FILE_NAME_OUT  " /tmp/tout.txt "


#define     DEBUG      1

#ifdef     DEBUG
#define    aprintf      printf
#else
#define    aprintf      {}
#endif



#ifdef     DEBUG3
#define    a3printf      printf
#else
#define    a3printf      {}
#endif


#define     TEST_OB_MASS    60

#define     G_CONST     (6.6525*pow(10,-11))    
#define     R_EARTH     (6378000.14)
#define     EARTH_R     (6378000.14)
#define     ZERO_CONST  (0.0000000001)
#define     MASS_EARTH  (5.9742*pow(10,24))
#define     VOL_EARTH   (1.0832*pow(10,12+9))
#define     DENSITY_EARTH		(5.515*1000)
                    //


/////////////////////////////////////////////////////////////////////////
int test_file_open()
{
FILE *fp;

fp = NULL;
fp = fopen(FILE_NAME_OUT,"w+");
if (fp ==NULL)
{
    printf("\n Error open file exit now !! \n");
   // flag_open_file = 0; // err
   exit(1);  
  return 1;
}else
{
    printf(" \n\n file test ok PASS !! \n\n");
}
  fclose(fp);
  return 0;
}




/////////////////////////////////////////////////////////////////////////   
int test_main_002()
{
  
 // printf(" %20.10lf \n",M_PI);


#ifdef   FILE_OK
  FILE* fp;
    fp = fopen("w+",FILE_NAME_OUT);
    
    if(fp ==NULL) 
    {
	printf("fp ==NULL \n");
	return 1;
    }
#endif  
  
  // M_PI = 3.14159
  // M_PI_2 = 1.570796
  double z  = 0.000000000001;
  double rzz = 0.00001 ;
  double thzz = 0.00001 ;

  /////////////////////////////////
  double R_earth = 10000;
  double h  = 100;
  double R_Max = 100;
  /////////////////////////////////
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  int i, j;
  double delta_area =   z;
  double area =  z;
  double r, th;

  double density = 200;  // metal

  double total_force =0;
  double force_delta ;

  double M1 =100;
  double delta_M2 = 0;
  double G= 6.67*(10^(-11)) ;
  
  area =  z;
   i =0;
   j =0;
  for(r =z ; r < R_Max ; r = r +delta_r)
  {
    delta_area =  z;
    for(th =  z ; th < 2*M_PI; th =th +delta_th )
    {
       	delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    } // end for th

    if( ((i++)%100)==0)
          putchar('.');  
                        

    area += delta_area;


    delta_M2 = delta_area * density ;

    double short_R =  sqrt( powl(R_earth,2)-powl(R_Max,2) ) ;
    
    double x = short_R + R_earth + h;

    force_delta = G*M1*delta_M2/(powl(x,2)) * ((short_R)/(r)) ;
    
    // force_delta = G*M1*delta_M2/pow(x,2) * ((short_R)/(R_earth)) ;

    total_force += force_delta;
    
  } // end for r
  
  printf("\n\n disk area   = %lf \n \n " , area) ;
  printf("\n\n disk force = %lf \n \n " , total_force ) ;
    
#ifdef FILE_OK    
    fclose(fp);
#endif

}// end test_main_002



///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////   
int test_main_001()
{
  
  printf("\n start PI = %20.10lf \n",M_PI);  
  double x,y,z; // coordination
  
  
  double h = 100;
  
  // M_PI = 3.14159  
  // M_PI_2 = 1.570796  
  double zero  = 0.000000000001;
  double rzz = 0.001 ;
  double thzz = 0.001 ;
  
  double R_Max = 100000;
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  
  
  int i, j;
  double delta_area =   zero;
  double area =  zero;
  double r, th;
  double density = 1000000;
  double total_force =0;
  double force_delta ;
  double M1 = TEST_OB_MASS;
  double M2 = TEST_OB_MASS;

  double G= G_CONST;
  double R_real_earth = R_EARTH ;
  
  double M1_delta;
  double M1_real_earth =  MASS_EARTH   ;
  double dtocenter;
  
  char temp_c[100];
  int temp_int;
  
  
  i=0;  j=0;
  area =  zero;
  //total_force
  total_force =0;
  area =zero;
  for(r =zero ; r < R_Max; r = r +delta_r)
  {
    delta_area =  zero;
    force_delta = zero;
    for(th =  zero ; th < 2*M_PI; th =th +delta_th)
    {
    delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    }// end for
    
 
    area += delta_area;
    
    M1_delta = delta_area * density ;
    dtocenter =  pow(R_real_earth,2) - pow(r,2);
    
    dtocenter = sqrt(dtocenter);
    if(dtocenter < 0)
      {
          printf(" \n exit!!\n");
          return 1;
            scanf("%i\n",&temp_int);
      }
    //sqrt( (x^2)+(r^2) ) ;
    x = dtocenter +R_real_earth + h ; //  .....
    double factor = dtocenter/R_real_earth;
    double temp_gforce = (G*M1_delta*M2)/pow(x,2);
    aprintf("\n dbg %lf %lf %lf %lf %lf \n",x,pow(x,2),M1_delta,M2,G);
    force_delta = temp_gforce*factor ;
    total_force += force_delta; 
    aprintf("\n dbg =%lf %lf %lf %le \n", dtocenter,force_delta,factor,temp_gforce);
      // scanf("%i\n",&temp_int);
    
    
    i++;
    if((i%100)==0)
    {
      printf("\n start PI = %20.10lf <%010i> %20.10le %20.10le kg  "
      ,M_PI,i,force_delta,total_force/9.8);  
    
         // putchar('.');   
    }
  }// end for
  
  printf( "  \n\n area = %lf km*km    gforce= %le kg\n \n " 
  , (area/1000000.001),total_force/9.8) ;

    
   return 0;

}// end test_main_001


///////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//
//
////////////////////////////////////////////////////////////////

typedef struct  DISKreturnstruct
{
	double  volume;
	double  Gforce;
	double  area;
	double  mass;
	
	
} CLTDISKRETDEF;
//CLTDISKRETDEF


typedef  struct SPHEREreturnstruct
{
	//double  EARTH_VOLUEME;  // in cube meter
	//double  MAN_Gforce_KG;
	
	double earth_volume;  
	double earth_mass;
	double Gforce;
	
} CLTSPHERERETDEF;
//CLTDISKRETDEF
typedef struct aek34g56jli
{

double ManKGIN ;
double ManHigh ;
//double disk_x_from_center;  div_total_num
double div_total_num_spher_x ;
double div_total_num_disk_r ;
double div_total_num_disk_th ;


double density;
	
}  SPHEREINPUTDEF;
///////////////////////////////////////////////////////////////////////
//
//
//
//
//
///////////////////////////////////////////////////////////////////////   
int disk_volume_Gfouce( SPHEREINPUTDEF indata, double disk_x_from_center , CLTDISKRETDEF *ptr_out )

  // double ManKGIN, double ManHigh, 
//double disk_x_from_center , double div_total_num )    
{
 
  
  a3printf("\n disk-in start disk_x_from_center=%20.10le \n", disk_x_from_center );
  double x,y,z; // coordination
  
  
  double h =  indata.ManHigh; //    ManHigh;
  
  // M_PI = 3.14159  
  // M_PI_2 = 1.570796  
  double zero  = 0.000000000001;
  
  
  double rzz = 1/indata.div_total_num_disk_r   ;  //0.001 ;
  double thzz = 1/ indata.div_total_num_disk_th ;
  
  double R_Max ;   //= 100000;
  
  R_Max =  pow(R_EARTH , 2) -  pow(    disk_x_from_center,2);
  R_Max =  sqrt(R_Max);  // ok
  
  
  
  double delta_th = 2*M_PI* thzz;
  double delta_r = R_Max * rzz;
  
  
  int i, j;
  double delta_area =   zero;
  double area =  zero;
  double volume =zero;
  double mass =zero;
  double r, th;
  
  double temp_gforce =0;
  
  double delta_disk_x = (R_EARTH*2)/indata.div_total_num_spher_x;  // 1000000;
  
  double density   =   indata.density;  //???;    // sity
  
  double total_force =0;
  double force_delta =0;
  //double M1 = TEST_OB_MASS;
  double M2 = indata.ManKGIN;    //TEST_OB_MASS;
  
  double G= G_CONST;
  double R_real_earth = R_EARTH ;
  
  
  double factor = 0;
  double M1_delta =0;
  double M1_real_earth =  MASS_EARTH   ;
  double dtocenter;
  
  int c;
  int temp_int;
  double temp_slop = zero ;
  
  i=0;  j=0;
  
  //total_force
  total_force =0;
  area =zero;
  volume = zero;
  mass = zero;
  i=0;
  for(r =zero ; r < R_Max  ; r = r +delta_r)
  {
    delta_area =  zero;
    force_delta = zero;
    for(th =  zero ; th < 2*M_PI; th =th +delta_th)
    {
        delta_area += (delta_th*(r))*(delta_r);  // arc*delta_r 
    
    }// end for
    
       // circle ring  mass gen Gforce ..
    area += delta_area;
    volume += area * delta_disk_x;
    
    M1_delta = delta_area * delta_disk_x *density ;
    mass +=  M1_delta;
    
    x = disk_x_from_center +R_real_earth + h ; //  man as  org point
    
    temp_slop = pow(r,2) + pow( x,2 );
    temp_slop = sqrt( temp_slop);
    
    if(abs(temp_slop ) < 0.001)
    {
    	printf("\n slop ERROR !! \n")  ; 
    	c = getchar();
    	if(c =='q') exit(1);
    } // end if
	
    factor = x/temp_slop   ;   //R_real_earth;
    
    temp_gforce = (G*M1_delta*M2)/pow(temp_slop , 2);  //  newton gforce
    
    a3printf("\n dbg001 %20.10le %20.10le %20.10le %20.10le %20.10le \n"
    ,x , pow(x,2) , M1_delta ,  M2,  G);
    
	force_delta = temp_gforce*factor ;
    total_force += force_delta; 
    
	a3printf("\n dbg002 =%20.10le %20.10le %20.10le %20.10le \n"
	,force_delta, factor,  temp_slop,  disk_x_from_center );
     // c = getchar();
     // if(c == 'q') exit(1);
    
    
    i++;
    if((i%1000)==0)
    {
      a3printf("\n disk-ring start PI = %20.10lf <%010i> %20.10le %20.10le kg  "
      ,M_PI,i,force_delta , total_force/9.8);  
    
          
    }
  }// end for
  
  a3printf( "  \n\n disk-exit area = %lf km*km    gforce= %le kg\n \n " 
  , (area/1000000.001),total_force/9.8) ;

    ptr_out->volume =    area ;   // m*m
    ptr_out->mass   =     area*density;
    ptr_out->Gforce = total_force/9.8;      // KG
    ptr_out->area   = area;
    
    
    
    
   return 0;

}   // end disk_volume_Gforce

///////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
//SPHERERETDEF
 int  sphere_volume_Gforce( SPHEREINPUTDEF  indata , CLTSPHERERETDEF  *ptr_out )
{

double R ;
//SPHERERETDEF  ret_s;
CLTDISKRETDEF     ret_from_disk_delta;

R = EARTH_R;
double x;
double disk_x_from_center;

double delta_x = R/ indata.div_total_num_spher_x;
double temp_volume =0;
double temp_mass =0;
double temp_area =0;
double temp_Gforce =0;


    int i =0;
	for(x=  -R; x < R; x = x + delta_x)
	{
	    disk_x_from_center = x;

        disk_volume_Gfouce (indata , disk_x_from_center , &ret_from_disk_delta  );	
		
		
		temp_volume += ret_from_disk_delta.volume;
		temp_mass   += ret_from_disk_delta.mass;
		temp_area   += ret_from_disk_delta.area;
		temp_Gforce += ret_from_disk_delta.Gforce;
		i++;
		if((i%100)==0)
		{
		   printf("SHPER %20.10le %20.10le %20.10le %20.10le %20.10le \n",
		   x, temp_Gforce,temp_volume,temp_mass, temp_area) ;
		} // endif
	}  //end for



    //*ptr_out.
    
    //ptr_out->volume =    area ;   // m*m
    //ptr_out->mass   =     area*density;
    //ptr_out->Gforce = total_force/9.8;      // KG
    //ptr_out->area   = area;
    
    
	ptr_out->earth_volume   = temp_volume  ;  // m*m*m
	ptr_out->earth_mass     = temp_mass ;     // kg
	ptr_out->Gforce         = temp_Gforce ;  //  kg
    
    
   return 0;




}  // end sphere



//////////////////////////////////////////////////////////////////
int test_main_go()
{
	

//CLTSPHERERETDEF
CLTSPHERERETDEF  ret;
SPHEREINPUTDEF   indata;


indata.ManKGIN = 60 ;
indata.ManHigh = 100 ;
//double disk_x_from_center;  div_total_num
indata.div_total_num_spher_x = 1000;   //5000 ;   //  60000/2/3.14 
indata.div_total_num_disk_r = 1000;
indata.div_total_num_disk_th = 1000;



indata.density       =  DENSITY_EARTH ;  // kg/(m*m*m)    est


  //double seconds;

  time_t timer1,timer2;
  //struct tm y2k = {0};
  //y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
  double seconds;

 // y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

  time(&timer1);  /* get current time; same as: timer = time(NULL)  */


printf("\n********************************\n");
sphere_volume_Gforce(indata, &ret);  // cal

time(&timer2); 
seconds = difftime(timer2 , timer1 ) ;

printf("\nSTOP \n********************************\n");
printf("Used time sec= %20.10lf \n", seconds);

printf("STOP Man Gforce= %20.10le\n " , ret.Gforce);
printf("mass= %20.10le vol=%20.10le cal_d= %20.10le  %20.10le \n ",
      ret.earth_mass, ret.earth_volume , ret.earth_mass/ret.earth_volume , indata.density);

printf("\n\n..........................\n");
//printf(" Man Gforce= %20.10le  mass= %20.10le volume=%20.10le cal_d= %20.10le  %20.10le",
//ret.Gforce,  ret.earth_mass , ret.earth_volume , ret.earth_mass/ret.earth_volume , indata.density);


///////////////////////////////////////////////////////////////////////////////
FILE *fp;

fp = NULL;
fp= fopen("out.txt","w+");
if(fp==NULL)
{
    printf("\n file onpen err !!\n");
	return 1;    	
}

fprintf(fp,"\nSTOP \n********************************\n");
fprintf(fp,"Used time sec= %20.10lf \n", seconds);

fprintf(fp,"STOP Man Gforce= %20.10le\n " , ret.Gforce);
fprintf(fp,"mass= %20.10le vol=%20.10le cal_d= %20.10le  %20.10le \n ",
      ret.earth_mass, ret.earth_volume , ret.earth_mass/ret.earth_volume , indata.density);

fprintf(fp,"\n\n..........................\n");




 fclose(fp);
////////////////////////////////////////////////////////////////////////////////




}
//.....................................................................................................//

/*
typedef  struct SPHEREreturnstruct
{
	//double  EARTH_VOLUEME;  // in cube meter
	//double  MAN_Gforce_KG;
	
	
	
	double earth_volume;
	double earth_mass;
	double Gforce;
	
} CLTSPHERERETDEF;
//CLTDISKRETDEF
typedef struct aek34g56jli
{

double ManKGIN ;
double ManHigh ;
//double disk_x_from_center;  div_total_num
double div_total_num ;
double density;
	
}  SPHEREINPUTDEF;
*/
///////////////////////////////////////////////////////////////////










#endif






