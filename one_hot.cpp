/*  One_hot.cpp file contains drive function to do the one-hot encoding for categorical data often used in data mining/machin learning field*

Warning: I have tried my best to make the code error free. However, use the code at your own risk.

Prerequisites: Install armadillo, boost libraries before running the program.
What the function do?
Well, this function one_hot_encoding takes as input the file name and armadillo matrix.
Data file, which is a csv file infact, looks like this:

a, b, c, d, e ---> this is header line or column names
a1,,c1,d1,e1---> actual content starts here, note some missing values
a1,b1,,d1,e2
,,c1,d2,e3
a2,b2,c2,d1,e1

one hot encoded data matrix looks something  like this (note that columns have been permutated):
data:
   1.0000   1.0000   1.0000   1.0000        0        0        0        0        0        0        0
   1.0000        0   1.0000        0   1.0000   1.0000        0        0        0        0        0
        0   1.0000        0        0        0        0   1.0000   1.0000        0        0        0
        0        0   1.0000   1.0000        0        0        0        0   1.0000   1.0000   1.0000


Auther: Chandresh Maurya
Email: ckm.jnu@gmail.com

*/


#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>
#include <string.h>
#include<map>
#include<armadillo>
#include <boost/tokenizer.hpp>

/***************************Namespaces***********************************************/
using namespace std;
using namespace arma;


void one_hot_encoding(const char *filename, mat &edata)
{

// first read data from csv file, we assume that first line in the file is header line representing column names, we remove that

ifstream ifs;

ifs.open(filename,ios::in);
string line;

size_t lines_read = 0, element = 0;
using namespace boost;	//  boost tokenizer to split string
char_separator<char> sep(",");
map<string,int> category;
if(ifs.is_open())
    { //cout<<"reading...\n";
                while(ifs.good())
                {
                    getline(ifs,line);
					if(line.empty()) continue;
					lines_read += 1;
                    if(lines_read == 1) continue; // read first line, discard it because its a header line
                    else
                    {
                        tokenizer<char_separator<char> > tokens(line, sep);
    					tokenizer<char_separator<char> >::iterator iter = tokens.begin();
                        for(;iter != tokens.end();iter++)
                           {
                            if( category.find(*iter) == category.end())
                            {  category[*iter]= element;
                               element++;
                            }

                           }
                    }
              }
     ifs.close();
 }
else
 perror(" error opening file");


//for(map<string,int>::iterator it = category.begin();it!= category.end();it++)
 //  cout<<it->first<<"->"<<it->second<<endl;

//cout<<" MAP SIZE="<<category.size()<<endl;
edata.zeros(lines_read-1,category.size());
//edata.print();

// file the matrix with one hot
ifs.open(filename,ios::in);
lines_read = 0;
if(ifs.is_open()){
                while(ifs.good())
                {
                    getline(ifs,line);
					if(line.empty()) continue;
					lines_read += 1;
                    if(lines_read == 1) continue; // read first line, discard it because its a header line
                    else
                    {
                        tokenizer<char_separator<char> > tokens(line, sep);
    					tokenizer<char_separator<char> >::iterator iter = tokens.begin();
                        for(;iter != tokens.end();iter++)
                        {  // cout<<category[*iter]<<endl;
                                edata(lines_read-2,category[*iter]) = 1;

                        }
                    }
        }
  ifs.close();
}
else
 perror(" error opening file");

edata.print("data:");

}


int main(int argc, char**argv){

if(argc<2)
  {
	    cerr<<"Error in input format : 2 arguemnts required \n 1. executable filename";
        return( EXIT_FAILURE );

 }

    char trainfile[1024];
    strncpy(trainfile, argv[1], strlen(argv[1])+1);

    mat edata;
    one_hot_encoding(trainfile,edata);

    return 0;
}
