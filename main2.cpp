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

void mission( FILE *frange, FILE *fdistrib, FILE *fzero, vector<double> &vLower, vector<double> &vUpper, double LB, double UB )
{
    double range= ( UB - LB )/n        ;
   
    printf( "粒度＝%f\n", range );
    int    *vctr= new int [ n ]          ;
    for( int i = 0 ; i < n ; i++ )
    {
        vctr[i] = 0 ;
        fprintf( frange, "%f\n", LB + i*range );
    }
    
    int index = 0 ;
    for( int i = 0 ; i < vLower.size() ; i++  )
    {
        index = (vLower[i]-LB)/range ;
        vctr[index] =vctr[index] + 1 ;
        index = (vUpper[i]-LB)/range ;
        vctr[index] =vctr[index] + 1 ;
    }
    
    for( int i = 0 ; i < n ; i++ )
    {
        fprintf( fdistrib, "%d\n", vctr[i] );
        fprintf( fzero, "%d\n", 0 );
    }
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
    
    
    FILE *frangeL = fopen("./Range.txt","w+t") ;
    FILE *fdistrL = fopen("./distri.txt","w+t") ;
    FILE *fzero   = fopen("./zero.txt","w+t") ;
    
    vector< double > vUpper ;
    vector< double > vLower ;
    
    //--------------- Read the file ------------------------------------------------
    getline( file, line );
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
    
    mission( frangeL, fdistrL, fzero, vLower, vUpper, LB, UB ) ;

}
