

/*----------------------------------------------------------------------/
  SPCOM_impression

  Program created to handle the impression data of SPCOM 111 students
  int their first impression exercise.
 
  Author:  Geoffrey Salisi
  Copyright (c) 2014 by Geoffrey Salisi.  All rights reserved.
 
-----------------------------------------------------------------------*/

//
// SPCOM 111 - Impression Assignment Automation
//	by Geoffrey Salisi
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>


using std::cin;
using std::cout;
using std::endl;
using std::string;

void intro(){
	cout <<	endl << "---------------------------------------------------------------" << endl;
	cout <<	"---        SPCOM 111 - Impression Exercise Program          ---" << endl;
	cout <<	"---------------------------------------------------------------" << endl;
	cout <<	"------  Extra Command                                     -----" << endl;
	cout <<	"------      - c = stops fetching input                   -----" << endl;
	cout <<	"---------------------------------------------------------------" << endl;
}
//returns the appropriate directory for each student name
string getdirstudent( string shortCLFN, string storedName){
		
		string newfilename;
		newfilename = storedName.append(".txt");

		string newfiledir = shortCLFN;
		newfiledir.append("folder");
		newfiledir.append("/");
		newfiledir.append(newfilename);

		return newfiledir;
}

//function that
string findclasslist(){

	string shortCLFN;
	bool classlistfound = false;

	while(!classlistfound){
		
		cout << endl << " - Input class file name here: ";
		getline(cin, shortCLFN);
		string tmpCLFN = shortCLFN;
		tmpCLFN.append(".txt");
		if(shortCLFN.empty()){
			cout << " ~ Error: File not found!" << endl;
		}else{
			cout << " ~ File found!" << endl;
			return shortCLFN;
		}
	}
	return shortCLFN;
}

bool addImpression( string shortCLFN, string currentlinestr ){

//readying the directory for the student files
	string storedName = currentlinestr;
	string newfiledir = getdirstudent(shortCLFN, storedName);
	
//check if there is an existing file	
	std::ifstream studentfile; 
	studentfile.open(newfiledir);

//copy the contents for editing later	
	string currimpression;
	getline(studentfile, currimpression);
	
	studentfile.close();

//now open file for editing

	std::ofstream studentfile2; 
	studentfile2.open(newfiledir);

	string newimpression; //fetch an impression
	
	cout << " - Add impression to "<< storedName << ": ";
	getline(cin, newimpression);

//exception to cancel current student impression update
	if( newimpression.empty() ){
		studentfile2 << currimpression;
		studentfile2.close();
		cout << " ~ * Skipped *" << endl;
		return false;

	}else if( newimpression.compare("c") != 0 ){

		currimpression.append(newimpression);
		studentfile2 << currimpression << "; ";
		cout << " ~ " <<currimpression << endl;
		studentfile2.close();
		return false;

	}else{
		studentfile2 << currimpression;
		studentfile2.close();
		return true;
	}
	
}

bool getmode(){

	string ans;
	cout << " - Would you like to use auto mode? (y/n) : ";
	getline(cin, ans);

	return ans.compare("y") == 0;
}
void autoMode( string finalCLFN, string shortCLFN ){

	std::ifstream clfn;
	clfn.open(finalCLFN);
	string currStd;
	string tmp;
	cout << " ~ Auto-mode. Press enter to start... (TIP: press enter to skip a student)";
	getline(cin, tmp);

	while( getline(clfn, currStd) ){

		bool done;
		done = addImpression( shortCLFN, currStd );
		if( done ){
			break;
		}
		cout << " --- --- --- --- --- --- --- --- --- --- --- --- --- ---- ---" << endl;

	}

	clfn.close();
}
void manualMode( string finalCLFN, string shortCLFN ){
	// main loop to populate the impressions of students
	bool done = false; //just a dummy var
	int main_counter = 0;
	cout << " ~ Manual Mode : " << endl;

	while(!done){

		//ask for a name
		string inputName; 
		cout << " --- --- --- --- --- --- --- --- --- --- --- --- --- ---- ---" << endl;
		cout << " - Input student name: " ;
		getline(cin, inputName);


		//option to exit early
		if( inputName.compare( "c" ) == 0 ){
			cout << " - Cancelled impression input." << endl;
			cout << " --- --- --- --- --- --- --- --- --- --- --- --- --- ---- ---" << endl;
			break;
		}


		bool namefound = false;
		
		std::ifstream fileCL;
		fileCL.open(finalCLFN); //open classlist
		
		string currentlinestr; //stores the name on the current stream

		while(getline(fileCL, currentlinestr)){

			string currlinetmp = currentlinestr;
			std::transform(currlinetmp.begin(), 
							currlinetmp.end(), 
							currlinetmp.begin(), ::tolower); // converts string to all lower case
			//finds a match with the query
			if(currlinetmp.find(inputName) != string::npos){
				cout << "       ~~~~~~~~~~~~~       Okay!       ~~~~~~~~~~~~" << endl;
				namefound = true;
				break;
			}
		}
		
		fileCL.close();

		//edit the list of the student that was found
		if( namefound ){

			addImpression( shortCLFN, currentlinestr );

		}else{ // if no students were found prompt that it doesn't exist
			cout << " ~ Student '" << inputName << "' does not exist!" << endl;
		}

		++main_counter;
	}
}

void compileFiles( string finalCLFN, string shortCLFN ){

	cout << endl << " - Compile? (y/n) : ";
	string ans;
	getline(cin, ans);
	
	//compiles the all students' data to one text file	
	if(ans.compare("y") == 0){

	 	std::ifstream fileclasslist; //open classlist for counting
	 	fileclasslist.open(finalCLFN);
	 	string derp;
	 	int count = 0;

	 	while(getline(fileclasslist, derp)){
			++count;
		}
		cout << " ~ Appended " << count << " student data." << endl;
		
		fileclasslist.close();
	
	//reopen for actual rewriting
		std::ifstream reopenfile;
		reopenfile.open(finalCLFN);
		
	//create an output file	
		std::ofstream finaloutputfile;
		string finalname = shortCLFN;
		finalname.append("_final.txt");
		finaloutputfile.open(finalname);

		
	//iterates to all the names in class list
	 	for( int i = 0; i < count; ++i ){
	 		//get student name
	 		string name;
	 		getline(reopenfile, name);
	 		//get directory for read operation
	 		string tmpdir = getdirstudent(shortCLFN, name);
	 		std::ifstream impfile;
	 		impfile.open(tmpdir);

	 		string finalstudentline; //final output to write

	 		string impstrg;	//get impression line
	 		getline( impfile, impstrg );
	 		
	 		
			finalstudentline.append(name);
	 		finalstudentline.append(": ");
	 		finalstudentline.append(impstrg);
	 		finalstudentline.append("\n");
	 		

	 		finaloutputfile << finalstudentline << endl;
	 		

	 		impfile.close();
	 	}
	 	
	 	finaloutputfile.close();
	}

	cout << " ~ Exiting..." << endl;

}

int main(){

	intro();
//opens the classlist to find the student if it exists
// ---- "CLFN" stands for "Class list file name"

	string shortCLFN = findclasslist();
	string finalCLFN = shortCLFN;
	finalCLFN.append(".txt");

// Search for name in class list 

	bool automaticON = getmode();
	bool done = false;

	while(!done){
	
		if(automaticON){
			
			bool cont = true;
			while(cont){
				autoMode( finalCLFN, shortCLFN );

				cout << " - Continue? (y/n) : ";
				string contstr;
				getline( cin, contstr );
				if( contstr.compare("n") == 0 ){
					cont = false;
				}
			}

		}else{

			manualMode( finalCLFN, shortCLFN );
		}

		cout << " - * Want to switch modes? (y/n) : ";
		string str;
		getline(cin, str);

		if(str.compare("y") != 0){
			done = true;
		}else{
			automaticON = !automaticON;
		}
	}

	compileFiles( finalCLFN, shortCLFN );

	
return 0;

}
