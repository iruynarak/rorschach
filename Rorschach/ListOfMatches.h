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
	#define _ListOfMatches
#endif

#ifndef _Match
	#include "Match.h"
#endif

#include<iostream>

using namespace std;

/** \class ListOfMatches
 * Lista de casamentos (objetos da classe Match)
 */
class ListOfMatches
{
	public:
		/// Número de casamentos (objetos da classe Match) na lista
		int numberOfMatches;
		/// Ponteiro para o início da lista.
		Match* begin;
		/**
		 * Construtor de objeto da classe ListOfMatches
		 */
		ListOfMatches()
		{
			numberOfMatches = 0;
			begin = 0;
		}
		/**
		 * Insere casamento (objeto da classe Match)
		 * \param length Tamanho do casamento (objeto da classe Match) a ser inserido.
		 * \param patternIndex Índice em pattern do casamento (objeto da classe Match) a ser inserido.
		 * \param textIndex Índice em text do casamento (objeto da classe Match) a ser inserido.
		 */
		void insert(int length, int patternIndex, int textIndex);

		/**
		 * Remove um match da lista
		 */
		Match* remove();
};
