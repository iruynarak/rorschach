/*
Rorschach
Copyright (C) 2014  Yuri Karan Benevides Tomas

Rorschach is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Rorschach is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef _ListOfSubstrings
#include "ListOfSubstrings.h"
#endif

#ifndef _Reader
	#include "Reader.h"
#endif

#ifndef _RKRGST
	#include "RKRGST.h"
#endif

#include <iomanip>
#include<sys/time.h>


#define BASE 2


typedef char* string;
//	g++ -Wall -o teste *.cpp
//	./Rorschach ../testCases/04/resume.txt ../testCases/04/original.txt


using namespace std;

#include <sys/time.h>

/*
 * getTime: devolve o tempo atual em segundos.
 */
double getTime() {
	struct timeval tv;

	gettimeofday(&tv, 0);

	return tv.tv_sec + tv.tv_usec/1e6;
}

int main(int argc, char** argv)
{

	double resultTime;


	if(argc != 3)
	{
		cout << "Parameters: <patternFile> <textFile>\n";
		return 0;
	}

	resultTime = getTime();

	Reader<unsigned char>* reader = new Reader<unsigned char>(argv[1], argv[2]);



	Box<unsigned char>* box = reader->filesToBox();

	box->printBox();

	int initialSearchLength = 10;
	int minimumSearchLength = 7;
	RKRGST<unsigned char>* rkrgst = new RKRGST<unsigned char> (  box, initialSearchLength, minimumSearchLength,  BASE);
	rkrgst->execute();



	//resposta:
	cout << "\n\n\n\n___________________________________________\n\n";

	cout << "\nlengthOfTokensTiled: " << rkrgst->lengthOfTokensTiled << "\n\n";

	while(rkrgst->listOfFinalTiles->numberOfMatches != 0)
	{
		Match* match = rkrgst->listOfFinalTiles->remove();
		match->print();
		for(int i = 0; i < match->length; i++)
		{
			cout << (box->pattern)[match->patternIndex + i].content;
		}
		cout << "\n";
		for(int i = 0; i < match->length; i++)
		{
			cout << (box->text)[match->textIndex + i].content;
		}
		cout << "\n\n";
	}

	cout << "\nlengthOfTokensTiled: " << rkrgst->lengthOfTokensTiled << "\n\n";

	float similarity = ((2 * static_cast<float>(rkrgst->lengthOfTokensTiled)) / (static_cast<float>(box->patternSize) + static_cast<float>(box->textSize)))*100;

	cout << "Similaridade:" << setprecision (5)  << similarity << "%\n";


	resultTime = getTime() - resultTime;


	cout << "Tempo gasto: " << setprecision (5) << resultTime << " segundos\n";
	return 0;
}

