/*******************************************************************************
CSCI 340 - Assignment 04 - Fall 2020

Programmer: Leonart Jaos
Z-ID: z1911688
Section: 0002
TA: Saiteja Alubelli
Date Due: October 1st, 2020

Purpose: The following program stores unique words from an input stream into a 
map container, and counts the frequency of which each word appears. The unique 
word is stored as the key and the frequency of which the word appears is stored
as the value. The map values are then printed with specific formatting.

********************************************************************************/

// Pre-processing directives
// The following allows input/output streams, the string class, file streams,
// the vector class, the map container, functions of algorithm, spacing options
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

//input file
#define FILE1 "./wordscanner.in"

// clean_entry  takes a string, reads values from 'a', and stores non-punctiati-
// on chars into string 'b'. These values are also converted to only lowercase.
// There were some addiotions to factor in words with punctuation at the begin-
// ning. The new string is stored into the address of string b.
void clean_entry(const string &a, string &b)
{
	string d ="";
	char n;
	for(auto it =a.begin(); it!=a.end(); ++it)
	{
		if((isalnum((*it))))
		{
			n = tolower(*it);
			d = d + n;
		}
		else if((it==a.begin())&&(isalnum((*(it+1)))))
		{
			continue;
		}
		else
		{
			break;
		}
	}
	b=d;
}
// get_words takes a map as parameter. First, this function takes all the chars
// from an input stream "FILE1" and stores them. Consecutive non-white space
// chars are not stored, including newlines.I needed to use the get() function
// from the string class so that I could still read the whitespace for word
// seperation purposes. 
// Consecutive characters stored 
// inbetween instances of white space are added into a string and stored into
// a vector of type string. The words stored in the string still contain non-
// alphanumeric characters. The words in the vector string are fed into the 
// clean_entry() that takes a copy of each string as one parameter and the address
// of the string as another parameter. After the string is cleaned, the cleaned 
// string is stored in place of the previous string.We don't want to store blank
// words, so after I clean each word, I only add the word into the map if it
// is not blank. 
void get_words(map<string, int> &m)
{
	vector<char> v;
	vector<string> x;
	char c;
	string s= "";
	ifstream is1;
	is1.open(FILE1);
	if(!is1)
	{
		cerr<<"Could not open input file: " << FILE1 << " Exiting program..." << endl;
		exit(1);
	}
	while(is1.get(c))
	{
		v.push_back(c);
		if((c==' ')||(c=='	')||(c=='\n'))
		{
			v.pop_back();
			if(s=="")
			{
			}
			else
			{
				//cout<<s<<endl;
				x.push_back(s);
				s = "";
			}
		}
		else
		{
			s=s+c;
		}
	} 
	for(auto it= x.begin();it!= x.end();++it)
	{
		s= *it;
		clean_entry(s,(*it));
		if((*it)!="")
		{
			s=(*it);
			m[s]++;
		}

	}
}
// The following function prints map values with left aligment and width requirements.
// To calculate the number of words in the stream, I just added the second member of 
// each string, which was the word frequency. The amount of unique words is simply the
// size of the map. I used another int to keep track of items per row 
void print_words(const map<string, int>&m)
{
	int icount=0;
	int scount=0;
	int wcount=m.size();
	for(auto it=m.begin();it!=m.end();++it)
	{
		scount = scount + (it->second);
		if(icount<2)
		{
			cout << setw(16) << left << it->first << " : " << setw(2) << it->second << "\t";
			icount++;
		}
		else
		{
			cout << setw(16) << left << it->first << " : " << setw(2) << it->second << "\t\n";
		       icount=0;	
		}
	}
	cout << "\n";
	cout << setw(28) << left << "no of words in input stream" << " : " << scount << endl;
	cout << setw(28) << left << "no of words in output stream" << " : " << wcount << endl;
}
// main function, declares map and invokes each of the functions
int main()
{
	map<string,int> m;
	get_words(m);
	print_words(m);
	return 0;
}


