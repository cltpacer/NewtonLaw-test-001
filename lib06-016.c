

///////////////////////////////////////////////////////////////
//
//
//   lib06.c   v016
//
//   high  school  physic text book  project
//   verify  Newtone law in real earth mass, R
//   2017-08-01
//
//     v007   2017-08-05
//     v016   2017-08-12
//  
//      david Tang Taiwan
//
//  Christmas meaning is not the exact day, 
//        but  his love .....
//
//  https://www.youtube.com/watch?v=SJeTGs92UKU
//  https://www.youtube.com/watch?v=RSJbYWPEaxw
//  std::numeric_limits 
//  So, include <math.h> (or in C++ maybe <cmath>), 
//  and test for __STDC_IEC_559__.

// If the macro is defined, not only are the types better specified 
// (float being 32bits and double being 64bits among others), 
// but also the behavior of builtin operators and standard-functions
// is more specified.
// Lack of the macro does not give any guarantees.
///////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <process.h>




#include "./datalib.h"

#ifndef    PRJ_NTTEST
#define    PRJ_NTTEST  1




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

//   fork();


/////////////////////////////////////////////////////////////////////////  
int double_check_Book_data()
{
double BookCalVol;
double temp, temp2;

BookCalVol = BOOK_CAL_VOL;
temp = BookCalVol - BOOK_EARTH_VOL;

temp2 = temp/BOOK_EARTH_VOL;

// temp2 = abs(temp);
printf("BOOK     VOL = %le \r\n",BOOK_EARTH_VOL);
printf("BOOK CAL VOL = %le \r\n", BookCalVol);
printf(" vol diff %le %lf  \r\n", temp,temp2);

temp = BOOK_MASS_EARTH / BookCalVol;

temp = temp- BOOK_DENSITY_EARTH; 
temp2 = temp/BOOK_DENSITY_EARTH;

printf(" den diff %le %lf  \r\n", temp,temp2);  


//int c = getchar();



}


 
/////////////////////////////////////////////////////////////////////////
//
//  cal  disk  volume
//  next step  used  x1,y1,z1    x2,y2,z2
//     line  vector
//   integral disk volume  to  9 planet 
//
//
//
//
//     data structure for in out
//
//
////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//
//
//   disk  volume cal
//   obj1  to obj2  can  integral any dir vector
//   
//   vector math would include  next  step
//
//
///////////////////////////////////////////////////////////////////////   
int disk_volume_Gfouce( CLTSPHEREINPUTDEF indata, double disk_x_from_center , CLTDISKRETDEF *ptr_out )

{  
  a3printf("\n disk-in start disk_x_from_center=%20.10le \n", disk_x_from_center );
  double x,y,z; // coordination
  
  
  double h =  indata.ManHigh; //    ManHigh;
  
  // M_PI = 3.14159  
  // M_PI_2 = 1.570796  
  double zero  = ZERO_CONST;
  
  
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
  
  double delta_disk_x = (2*R_EARTH)/indata.div_total_num_spher_x;  // 1000000;
  
  double density   =   indata.density;  //???;    // sity
  
  double total_force =0;
  double force_delta =0;
  //double M1 = TEST_OB_MASS;
  double M2 = indata.ManKGIN;    //TEST_OB_MASS;
  
  double G= G_CONST_NT;
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
    volume += delta_area * delta_disk_x;
    
    M1_delta = delta_area * delta_disk_x *density ;
    mass +=  M1_delta;
    
    x = disk_x_from_center +R_real_earth + h ; //  man as  org point
    
    temp_slop = pow(r,2) + pow( x,2 );
    temp_slop = sqrt( temp_slop);
    
    if(-0.00001< (temp_slop ) < 0.00000001)
    {//
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

    ptr_out->volume =    volume ;   // m*m
    ptr_out->mass   =     volume*density;
    ptr_out->Gforce = total_force;      // KG
    ptr_out->area   = area;
    
    
    
    
   return 0;

}   // end disk_volume_Gforce

///////////////////////////////////////////////////////////////////////////////////////////////
//
//   cal Gforce by integral vol 
//   next step used  x1,y1,z1  x2,y2,z2   cal
//    two obj Gforce
//    now only in x dir integral
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////
//SPHERERETDEF
 int  sphere_volume_Gforce( CLTSPHEREINPUTDEF  indata , CLTSPHERERETDEF  *ptr_out )
{

double R ;
CLTDISKRETDEF     ret_from_disk_delta;
double x;
double disk_x_from_center;

double delta_x ;  //= (2*R)/ indata.div_total_num_spher_x;
double temp_volume =0;
double temp_mass =0;
double temp_area =0;
double temp_Gforce =0;

R = EARTH_R;
delta_x = (2.0*R)/ indata.div_total_num_spher_x;  // 2R


    unsigned long  i =0;
	for(x=  -R; x < R; x = x + delta_x)
	{
	    disk_x_from_center = x;

        disk_volume_Gfouce (indata , disk_x_from_center , &ret_from_disk_delta  );	
		
		
		temp_volume += ret_from_disk_delta.volume;
		temp_mass   += ret_from_disk_delta.mass;
		temp_area   += ret_from_disk_delta.area;
		temp_Gforce += ret_from_disk_delta.Gforce;
		i++;
		if((i%200)==0)
		{
		   printf(" SH[%6li]] %18.10le %18.10le kg %18.10le %18.10le %18.10le \n",
		   i,x, temp_Gforce/BOOK_g ,temp_volume,temp_mass, temp_area) ;
		} // endif
	}  //end for

    
     printf("ret[%6li]] %18.10le %18.10le kg %18.10le %18.10le %18.10le \n",
		   i,x, temp_Gforce/BOOK_g ,temp_volume,temp_mass, temp_area) ;
		   
	ptr_out->earth_volume   = temp_volume  ;  // m*m*m
	ptr_out->earth_mass     = temp_mass ;     // kg
	ptr_out->Gforce         = temp_Gforce ;   //  nt
    
    
   return 0;




}  // end sphere






//////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////
int test_sphere(double high_input)
{
	
CLTSPHERERETDEF     ret;
CLTSPHEREINPUTDEF   indata;


indata.ManKGIN = TEST_MAN_MASS ;
indata.ManHigh = high_input ;

//indata.ManHigh = TEST_MAN_HIGH ;
//double disk_x_from_center;  div_total_num
indata.div_total_num_spher_x = 1000.00;   //5000 ;   //  60000/2/3.14 
indata.div_total_num_disk_r  = 1000.00;
indata.div_total_num_disk_th = 5000.00;  //  important

indata.density       =  DENSITY_EARTH ;  // kg/(m*m*m)    est

double R = EARTH_R;
double h =indata.ManHigh;
double G = G_CONST_EARTH;
double M2 = indata.ManKGIN;
double M1 = EARTH_MASS;
double NewtonLaw_Ans_Gforce ;
time_t timer1,timer2;
  
  double seconds;

  int ttt; 
 
 
FILE *fp;
char FileName[200];

sprintf(FileName,"out%0.0f.txt", high_input) ;
fp = NULL;
fp= fopen( FileName ,"w+");
if(fp==NULL)
{
    printf("\n file onpen err !!\n");
	return 1;    	
}

printf(" %s \n", FileName);
DBG_LOG_PRINT3(fp," %s \r\n", FileName);


//fclose(fp);
 //return  0;
  
 
NewtonLaw_Ans_Gforce = (G*M1*M2)/(pow(R_EARTH+h,2.0));


double math_formulation_volume = (4.00/3.00)*M_PI*powl(R,3.0);

time(&timer1);  /* get current time; same as: timer = time(NULL)  */
DBG_LOG_PRINT2(fp,"..........................START ....................................................\r\n" );

// fclose(fp);
// return 0;

//DBG_LOG_PRINT(fp"\n********************************\n");
sphere_volume_Gforce(indata, &ret);  // cal

time(&timer2); 
seconds = difftime(timer2 , timer1 ) ;

DBG_LOG_PRINT2(fp,".........................STOP ......................................................\r\n");

 ttt = (int) seconds;
DBG_LOG_PRINT4(fp,"Used time min= %i sec= %i \r\n", ttt/60, ttt%60);

DBG_LOG_PRINT4(fp,"input: h=%20.10le  %20.10le kg \r\n", indata.ManHigh, indata.ManKGIN);

DBG_LOG_PRINT4(fp,"Man Gforce  = %20.10le  %20.10le kg \r\n" , ret.Gforce , ret.Gforce/BOOK_g );
DBG_LOG_PRINT4(fp,"dir Gforce  = %20.10le  %20.10le kg \r\n" , NewtonLaw_Ans_Gforce ,NewtonLaw_Ans_Gforce /BOOK_g   );
      
DBG_LOG_PRINT2(fp,"PHY TEXT BOOK: used total earth mass as a small point, and Force = (G*M1*M2)/(R^2) is right !! \r\n")  ;    

double gdiff_temp, gdiff_per_temp;

gdiff_temp = NewtonLaw_Ans_Gforce-ret.Gforce ;
gdiff_per_temp =  gdiff_temp/   NewtonLaw_Ans_Gforce;  

DBG_LOG_PRINT3(fp,"Different direct used NTlaw - integral method = %lf \r\n" , gdiff_temp );      
DBG_LOG_PRINT3(fp," err percentage = %lf  \r\n", gdiff_per_temp);  
DBG_LOG_PRINT2(fp,"....................................................................................\r\n");

double vol_diff_temp, vol_diff_per_temp;

vol_diff_temp = BOOK_EARTH_VOL - ret.earth_volume;

vol_diff_per_temp = vol_diff_temp/ BOOK_EARTH_VOL;

DBG_LOG_PRINT3(fp,"VOL BOOK        =%20.10le \r\n", BOOK_EARTH_VOL);
DBG_LOG_PRINT3(fp,"VOL Formula     =%20.10le \r\n" ,math_formulation_volume);
DBG_LOG_PRINT3(fp,"VOL Cal         =%20.10le \r\n" ,ret.earth_volume);
DBG_LOG_PRINT4(fp,"Vol =%20.10le  percentage = %lf \r\n", vol_diff_temp, vol_diff_per_temp);
// CEO would be chinese ...
DBG_LOG_PRINT2(fp,"....................................................................................\r\n");
double CAL_Formula_g;
double reverse_g;
double F,M;

F = ret.Gforce;
//M = TEST_MAN_MASS;
reverse_g = F/M2;
CAL_Formula_g    =   ((G_CONST_NT*MASS_EARTH)/(powl(R_EARTH,2.0)) )   ;     //?????????       

DBG_LOG_PRINT3(fp,"g BOOK        = %20.10le \r\n" , BOOK_g);
DBG_LOG_PRINT3(fp,"g Formula     = %20.10le \r\n" , CAL_Formula_g);
DBG_LOG_PRINT3(fp,"g reverse_g   = %20.10le \r\n" , reverse_g);

DBG_LOG_PRINT4(fp,"g_diff For = %20.10le percentage= %lf \r\n",BOOK_g-CAL_Formula_g,(BOOK_g-CAL_Formula_g)/BOOK_g);
DBG_LOG_PRINT4(fp,"g_diff REV = %20.10le percentage= %lf \r\n",BOOK_g-reverse_g,(BOOK_g- reverse_g)/BOOK_g);

DBG_LOG_PRINT2(fp,"....................................................................................\r\n");

DBG_LOG_PRINT6(fp,"cal mass   = %20.10le  cal vol= %20.10le cal_d     = %lf  %lf \r\n",

ret.earth_mass, ret.earth_volume , ret.earth_mass/ret.earth_volume , indata.density);

DBG_LOG_PRINT6(fp,"BOOK mass  = %20.10le BOOK vol= %20.10le BOOK cal_d= %lf  %lf \r\n ",
MASS_EARTH,VOL_EARTH, MASS_EARTH/ VOL_EARTH , DENSITY_EARTH);

double temp = MASS_EARTH/VOL_EARTH;

DBG_LOG_PRINT5(fp,"Density BOOK = %lf  D from Bookmass/Bookvol =%lf percent=%lf \r\n", 
BOOK_DENSITY_EARTH,temp, (BOOK_DENSITY_EARTH-temp)/BOOK_DENSITY_EARTH );   

      
DBG_LOG_PRINT2( fp,".............................CLOSE..................................................\r\n");



fclose(fp);
 





}
/////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////
int cal_two_point_gravity( CLTPLANTE a1, CLTPLANTE a2)
{
	//  planet
	
	
	
	
	
}



////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
//
//
//   batch  test
//
//
//////////////////////////////////////////////////////////////////



//.......................................................................................//

/*

2017-08-05

Bug report:
    ret value   feel  unconfortable
    thinging  how to solve this problem
    
complain
(1)
    without  source level debuger
	
	difficult to find  the bug
(2)	
	sometimes ,  connection loss, 
	my code did not backup .....
(3)
    can not  draw  pic for math result in web environment	     
    
    
(4)
    creat file at remote computer
	but can not get this file to local !!
	can not download to local...  




*/


/*
//////////////////////////////////////////////////////////////////////////
//
//  PSALM 8
//
// majestic同義字
// KK[m?ˋd??st?k] DJ[m?ˋd?estik]
// a.形容詞
//
//    1. 雄偉的；威嚴的；崇高的
//    a majestic figure 一個有威嚴的人
//  In the distance we saw the majestic Rocky Mountains. 
//  我們望見了遠處巍峨的落基山脈。
//
//
//  https://en.wikisource.org/wiki/Bible_(King_James)/Psalms
//  (Best) https://www.youtube.com/watch?v=LxGdoW8hhOg
//  http://www.knowing-jesus.com/psalm-8-4/
//  http://bible.knowing-jesus.com/Psalm/8
//
//////////////////////////////////////////////////////////////////////////

Psalm 8

1 O LORD, our Lord, how excellent is thy name in all the earth! 

who hast set thy glory above the heavens.

2 Out of the mouth of babes and sucklings hast thou ordained strength 

because of thine enemies, that thou mightest still the enemy and the avenger.

3 When I consider thy heavens, the work of thy fingers, 

the moon and the stars, which thou hast ordained;

4 What is man, that thou art mindful of him? 

and the son of man, that thou visitest him?

5 For thou hast made him a little lower than the angels, 

and hast crowned him with glory and honour.

6 Thou madest him to have dominion over the works of thy hands; 

thou hast put all things under his feet:

7 All sheep and oxen, yea, and the beasts of the field;

8 The fowl of the air, and the fish of the sea, 

and whatsoever passeth through the paths of the seas.

9 O LORD our Lord, how excellent is thy name in all the earth!


.......................................................................
New American Std

PSALM 8

O LORD, our Lord, How majestic is Your name in all the earth,

  Who have displayed Your splendor above the heavens!

2 From the mouth of infants and nursing babes 

   You have established strength Because of Your adversaries,

 To make the enemy and the revengeful cease.

3 When I consider Your heavens, the work of Your fingers, 

   The moon and the stars, which You have ordained;

4 What is man that You take thought of him, 

  And the son of man that You care for him?

5 Yet You have made him a little lower than God, 

   And You crown him with glory and majesty!

6 You make him to rule over the works of Your hands; 

   You have put all things under his feet,

7 All sheep and oxen, And also the beasts of the field,

8 The birds of the heavens and the fish of the sea, 

   Whatever passes through the paths of the seas.

9 O LORD, our Lord, How majestic is Your name in all the earth! 












.......................................................................
about  King David

https://en.wikipedia.org/wiki/David

Beautiful Good song .... 

Pslam 8 by David King .... 

3000years ago...

1000 BC

https://www.youtube.com/watch?v=JZTx1vIpksc


大衛（希伯來語：???????，阿拉伯語：???? ??，其他音譯：達味／天主教，達烏德／伊斯蘭教，大闢／舊譯），

是公元前10世紀以色列聯合王國的第二任國王。大衛乃「被愛的」、

「蒙愛者」之意。他在位四十年；其中有七年六個月在希伯崙。

大部份關於大衛的記載都出自《希伯來聖經》中的《撒母耳記上》和《撒母耳記下》。

大衛在以色列歷代國王中，他是《聖經》描述為最正義的君主，並且是一位專心倚靠上帝的人，

是優秀的戰士、音樂家和詩人（在聖經中讚美上帝的詩篇絕大部分是他的著作）。根據《聖經》

，耶穌的父親約瑟是大衛的後裔。  
    
   



https://en.wikipedia.org/wiki/Solomon


Son of David

Solo  (single ???)

Solomon (/?s?l?m?n/; Hebrew: ????????, Modern Shlomo, 

Tiberian ??l?m? ISO 259-3 ?lomo; Syriac: ??????? Shlemun; 

Arabic: ????????? Sulaym?n, also colloquially: Silim?n or Slem?n; 

Greek: Σολομ?ν Solom?n; Latin: Salomon), 

also called Jedidiah (Hebrew ????????????), 

was, according to the Bible 

(Book of Kings: 1 Kings 1–11;

Book of Chronicles: 1 Chronicles 28–29, 2 Chronicles 1–9), 

Quran, hadith and Hidden Words[3] 

a fabulously wealthy and wise king of Israel and a son of David, 

the previous king of Israel.[4] 

The conventional dates of Solomon's reign are circa 970 to 931 BCE, 

normally given in alignment with the dates of David's reign.

 He is described as the third king of the United Monarchy, 

which would break apart into the northern Kingdom of Israel 

and the southern Kingdom of Judah shortly after his death. 

Following the split, his patrilineal descendants ruled over Judah alone.


所羅門（希伯來語：??????????），天主教漢譯為撒羅滿，阿拉伯語稱為蘇萊曼（??????）。

根據《希伯來聖經》的記載，他曾是以色列耶路撒冷的一代帝王，後來在《古蘭經》中，

他被稱為先知。據《希伯來聖經》的記載，所羅門王是大衛與拔示巴的兒子，

以色列王國的第三任君主，是北方的以色列王國和南方的猶大王國分裂前的最後一位君主。

據聖經記載，所羅門王是耶路撒冷第一聖殿的建造者，並有超人的智慧，

大量的財富和無上的權力。但最後由於所羅門王的罪過

（包括偶像崇拜和背棄神的旨意）導致在他的兒子羅波安執政時期王國發生了分裂。

所羅門王還是後世許多文獻和傳說的主角。







*/    
 
 
 
 ////////////////////////////////////////////////////////////////////////////////////////   
#endif






