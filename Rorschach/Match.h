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
#ifndef _Match
	#define _Match
#endif

#include<iostream>

using namespace std;

/** \class Match
 * Classe que representa um casamento.
 */
class Match
{
	public:
		///tamanho do casamento
		int length;
		/// indice em pattern da primeira letra pertencente ao casamento
		int patternIndex;
		/// indice em text da primeira letra pertencente ao casamento
		int textIndex;

		/// Ponteiro para o proximo casamento em uma estrutura que engloba um objeto desta classe
		Match* next;
		/// Ponteiro para o casamento anterior em uma estrutura que engloba um objeto desta classe
		Match* previous;

		/**
		 * Construtor de um objeto da classe Match
		 * \param length Tamanho do casamento.
		 * \param patternIndex Indice em pattern da primeira letra pertencente ao casamento.
		 * \param textIndex Indice em pattern da primeira letra pertencente ao casamento.
		 */
		Match(int length, int patternIndex, int textIndex)
		{
			this->length = length;
			this->patternIndex = patternIndex;
			this->textIndex = textIndex;
			next = previous = 0;
		}

		/**
		 * Método que imprime o conteúdo do objeto da classe Match.
		 */
		void print()
		{
			cout << "length: " << length << " patternIndex: " << patternIndex << " textIndex: " << textIndex << "\n";
		}
};
