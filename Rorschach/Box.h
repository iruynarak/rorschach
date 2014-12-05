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

#ifndef	_Box
#define	_Box
#endif

#ifndef _Letter
#include "Letter.h"
#endif

#include<stdio.h>

/** \class Box
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos da pattern e da text
 * Classe criada para facilitar a administracao dos dados. Isto diminuira o tamanho do construtor do
 * RKRGST ao menos tempo que agrupara estes dados.
 */
template < typename TypeOfContent >
class Box
{
	public:
		/// Vetor de Letter alocada dinamicamente contendo pattern
		Letter<TypeOfContent>* pattern;

		/// Tamanho do vetor de Letter contendo o padrão
		int patternSize;

		/// Vetor contendo o texto onde será realizada a busca do padrão
		Letter<TypeOfContent>* text;

		/// Tamanho do vetor de Letter contendo o texto onde será realizada a busca do padrão
		int textSize;

		/**
		 * Construtor da classe Box
		 * \param pattern vetor de Letter contendo o padrão
		 * \param patternSize tamanho do vetor de Letter contendo o padrão
		 * \param text vetor contendo o texto onde será realizada a busca do padrão
		 * \param textSize tamanho do vetor de Letter contendo o texto onde será realizada a busca do padrão
		 */

		Box (Letter<TypeOfContent>* pattern, int patternSize, Letter<TypeOfContent>* text, int textSize)
		{
			this->text = text ;
			this->textSize = textSize;
			this->patternSize = patternSize;
			this->pattern = pattern ;
		}

		/**
		 * Destrutor da classe Box
		 */
		~Box()
		{
			delete pattern;
			delete text;
		}

		/**
		 * Método que imprime o conteúdo de pattern e text
		 * @return void
		 */
		void printBox()
		{
			for(int i = 0; i < patternSize; i++)
			{
				printf("%c", (pattern[i]).content);
			}

			printf("\n");

			for(int i = 0; i < textSize; i++)
			{
				printf("%c", (text[i]).content);
			}

			printf("\n");
		}
} ;
