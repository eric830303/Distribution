//
//  main.cpp
//  RegionClassification
//
//  Created by TienHungTseng on 2017/7/3.
//  Copyright © 2017年 Eric Tseng. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#define n 100
using namespace std ;


bool comp( double a, double b)//Used in sort(),which is STL func.
{
    if ( a < b ) return true  ;
    else         return false ;
}

void mission( FILE *frange, FILE *fdistrib, vector<double> &vtr, double LB, double UB )
{
    unsigned long vsize = vtr.size()     ;
    cout << vsize << endl ;
    
    double range= ( UB - LB )/n        ;
   
    cout << range << endl ;
    int    *vctr= new int [ n ]          ;
    int ctr = 0;
    for( int i = 0 ; i < n ; i++ )
    {
        vctr[i] = 0 ;
        fprintf( frange, "%f\n", LB + i*range );
    }
    
    for( int i = 0 ; i < vsize ; i++  )
    {
        int index = (vtr[i]-LB)/range ;
        
        vctr[index] =vctr[index] + 1 ;
    }
    
    for( int i = 0 ; i < n ; i++ )
    {
        fprintf( fdistrib, "%d\n", vctr[i] );
        ctr += vctr[i] ;
    }
    cout << ctr << endl ;
}




int main(int argc, const char * argv[])
{
    if( argc < 4 )
    {
        printf("./dist file.txt L U\n") ;
        return -1 ;
    }
    
    ifstream        file  ;
    string          line  ;
    double  LB = atof( argv[2] ) ;
    double  UB = atof( argv[3] ) ;
    
    file.open( argv[1], ios::in ) ;
    
    if( !file )
    {
        printf("Can't Read file\n") ;
    }
    
    
    FILE *frangeL = fopen("./lower_range.txt","w+t") ;
    FILE *frangeU = fopen("./upper_range.txt","w+t") ;
    FILE *fdistrL = fopen("./lower_distri.txt","w+t") ;
    FILE *fdistrU = fopen("./upper_distri.txt","w+t") ;
    
    vector< double > vUpper ;
    vector< double > vLower ;
    
    //--------------- Read the file ------------------------------------------------
    while( getline( file, line ) )
    {
        double L = 0 ;
        double U = 0 ;
        istringstream   token( line )     ;
        token >> L >> U ;
        
        vUpper.push_back(U) ;
        vLower.push_back(L) ;
    }
    
    //--------------- Sort in increasing order -------------------------------------
    sort( vLower.begin(), vLower.end(), comp );
    sort( vUpper.begin(), vUpper.end(), comp );
    
    
    
    mission( frangeL, fdistrL, vLower, LB, UB ) ;
    mission( frangeU, fdistrU, vUpper, LB, UB ) ;
   
}
