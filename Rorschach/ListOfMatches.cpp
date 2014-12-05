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

#ifndef _ListOfMatches
	#include "ListOfMatches.h"
#endif




void ListOfMatches::insert(int length, int patternIndex, int textIndex)
{

	Match* temp = new Match(length, patternIndex, textIndex);
	numberOfMatches++;

	if(begin == 0)
	{
		begin = temp;
		return;
	}

	if(temp->length > begin->length)
	{
		temp->next = begin;
		begin->previous = temp;
		begin = temp;
		return;
	}

	Match* aux = begin;

	while(aux->next != 0)
	{
		if(temp->length > aux->length)
		{
			aux->previous->next = temp;
			temp->previous = aux->previous;
			temp->next = aux;
			aux->previous = temp;
			return;
		}

		aux = aux->next;
	}

	if(temp->length > aux->length)
	{
		aux->previous->next = temp;
		temp->previous = aux->previous;
		temp->next = aux;
		aux->previous = temp;
		return;
	}

	aux->next = temp;
	temp->previous = aux;
	return;


}

Match* ListOfMatches::remove()
{
	Match* match = begin;
	begin = begin->next;
	if(begin!= 0)
	{
		begin->previous = 0;
	}
	numberOfMatches--;


	return match;
}
