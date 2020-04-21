#include <iostream>
#include <iomanip>
#include <fstream>  
#include <cstdlib>
#include <cctype>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <Windows.h>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>


using namespace std;


int getMode();
string getSen();
string getAtt( string );
void countDown();
int getAccuracy( string, string );
char playAgain( int, double );
int getAvgAcc( int, int );


bool run = true;
int mode;
char again;


// game
int main()
{ 

	do {
		// run initial menu and select mode
		// 1 for casual, 2 for competitive
		mode = getMode();
		
		// casual  mode - 1 round, returns accuracy and time
		// TO-DO: 
		while ( mode == 1 ){
			
			int acc;
			string sen, att;
			
			sen = getSen();
			countDown();
			
			clock_t start, end;
			start = clock(); 
		  
		    att = getAtt( sen ); 
		   
		    end = clock(); 
		    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
		    
			acc = getAccuracy( sen, att );
			again = playAgain( acc, time_taken );
			
			if ( again == 'n' ){ // end program
				run = false;
				mode--;
			}
			else if ( again == 'c' ){ // return to menu
				mode--;
			}
			else if ( again == 'y' ){ // play mode 1 again
				true;
			}
		}
		
		// competitive mode - 3 (or more) rounds, returns average accuracy and total time
		// TO-DO:
		while ( mode == 2 ){
			
			int acc, avgAcc, totalAcc = 0;
			string sen, att;
			
			clock_t start, end;
			start = clock();
			
			// loop for each of 3 rounds
			for ( int round = 0; round < 3; round++ ){
				sen = getSen();
				countDown();
				att = getAtt( sen );
				acc = getAccuracy( sen, att );
				totalAcc += acc;
			}
			
			end = clock(); 
		    double time_taken = (double(end - start) / double(CLOCKS_PER_SEC)) - 9;
			
			avgAcc = getAvgAcc( totalAcc, 3 );
			again = playAgain( avgAcc, time_taken );
			
			if ( again == 'n' ){ // end program
				run = false;
				mode = 0;
			}
			else if ( again == 'c' ){ // return to menu
				mode = 0;
			}
			else if ( again == 'y' ){ // play mode 2 again
				true;
			}
		}
		
	} while ( run == true );
		
return 0;
}


// Functions
// intitialize and select mode
int getMode(){
	int mode;
	cout << "Welcome to Speed Typing" << endl << endl
	     << "Select mode:" << endl
	     << "Casual (1)" << endl
	     << "Competitive (2)" << endl << endl;
	cin >> mode;
	
	system("CLS");
	return mode;
}

// return random sentence as string
string getSen() 
	{		
		string sen;
		string line;
	    vector<string> lines;
	    
	    srand(time(0));
	    
	    ifstream file("sentences.txt");
	    
	    // count lines in the file, store lines in the string vector
	    int total_lines=0;
	    while ( getline(file,line) )
	    {
	        total_lines++; 
	    	lines.push_back(line);  
	    }
	    
	    int random_number=rand() % total_lines;
	    sen = lines[random_number];
	    cin.ignore();
	    
    	return sen;
}

// countdown
void countDown()
	{
		cout << "Ready...";
		Sleep(1000);
		system("CLS");
		cout << "3..";
		Sleep(1000);
		system("CLS");
		cout << "2..";
		Sleep(1000);
		system("CLS");
		cout << "1..";
		Sleep(1000);
		system("CLS");
	}

// display sentence, get and return attempt as string
string getAtt( string sen )
	{
		string att;
		cout << sen << "\n" << endl;
		getline(cin, att);
		return att;
	}

// convert both strings to arrays by words, compare and return rounded % accuracy
int getAccuracy ( string sen, string att )
	{
		system("CLS");
		
		string senAr[15] = { "" }, attAr[15] = { "" };
		string word = "";
		
		double acc;
		int correctWords = 0;

		string::iterator S, A;
		
		// pack sentence words into array by char iteration
		int wordCount = 0;
  		for ( S = sen.begin(); S < sen.end(); S++ ){
  			if ( *S != ' ' )
  				senAr[wordCount] += *S;
  			else 
  				wordCount++;
		}
		
		// pack attempt words into array by char iteration
		int t = 0;
  		for ( A = att.begin(); A < att.end(); A++ ){
  			if ( *A != ' ' )
  				attAr[t] += *A;
  			else 
  				t++;
		}
		
		// compare by array index (accuracy graded by full word)
		for ( int g = 0; g < wordCount + 1; g++ ){
			if ( senAr[g] == attAr[g] ){
				correctWords++;
			}
		}
		
		acc = ((double)correctWords / (double)(wordCount + 1)) * 100;
		return round(acc);
	}
	    
char playAgain( int acc, double time_taken )
	{
		char again;
		cout << "Accuracy: " << acc << " %"  << endl
			 << "Time: " << time_taken << " seconds" << endl
			 << "\nAgain? (y/n) or change mode (c): ";
		cin >> again;
		
		system("CLS");
		
		return again;
	}

int getAvgAcc( int totalAcc, int rounds )
	{
		double avg = (double) totalAcc / (double) rounds;
		return round(avg);
	}
