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
/*
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
*/

void mission( FILE *foutput, vector<double> &vLower, vector<double> &vUpper, double LB, double UB )
{
    double range= ( UB - LB )/n        ;
    
    printf( "粒度＝%f\n", range );
    int    *vctr= new int [ n ]          ;
    
    
    
    //---- Initialization ----------------------------
    for( int i = 0 ; i < n ; i++ ){ vctr[i] = 0 ; }
    
    //---- Counting -----------------------------------
    int index = 0 ;
    for( int i = 0 ; i < vLower.size() ; i++  )
    {
        index = (vLower[i]-LB)/range ;
        vctr[index] =vctr[index] + 1 ;
        index = (vUpper[i]-LB)/range ;
        vctr[index] =vctr[index] + 1 ;
    }
    //---- Output -----------------------------------
    for( int i = 0 ; i < n ; i++ )
    {
        fprintf( foutput, "%f \t %d \n", LB + i*range, vctr[i] );
    }
}

int main(int argc, const char * argv[])
{
    if( argc < 4 )
    {
        printf("./dist input.txt L U\n") ;
        return -1 ;
    }
    
    ifstream        finput  ;
    string          line  ;
    double  LB = atof( argv[2] ) ;
    double  UB = atof( argv[3] ) ;
    
    finput.open( argv[1], ios::in ) ;
    
    if( !finput )
    {
        printf("Can't Read the input file 'input.txt'\n") ;
    }
    
    
    FILE *foutput = fopen("./output.txt","w+t") ;
    
    
    vector< double > vUpper ;
    vector< double > vLower ;
    
    //--------------- Read the file ------------------------------------------------
    getline( finput, line );
    while( getline( finput, line ) )
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
    
    mission( foutput, vLower, vUpper, LB, UB ) ;

}
