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
#define _ListOfSubstrings
#endif

#ifndef _Substring
#include "Substring.h"
#endif


/**
 *  \class ListOfSubstrings
 *  Lista de objetos da classe Substring
 *  \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos da pattern e da text
 *  \see Substring
 */
template <typename TypeOfContent>
class ListOfSubstrings
{
	public:

		/// Número de objetos da classe Substring na lista
		int numberOfSubstrings;

		/// Ponteiro para o início da lista
		Substring<TypeOfContent>* begin;

		/// Ponteiro para o fim da lista
		Substring<TypeOfContent>* end;

		/// Construtor de ListOfSubstrings.
		ListOfSubstrings()
		{
			numberOfSubstrings = 0;
			begin = 0;
			end = 0;
		}

		/**
		 * Destrutor de ListOfSubstrings.
		 * deletando cada um dos objetos da classe Substrings contidos
		 * na lista
		 */
		~ListOfSubstrings()
		{
			Substring<TypeOfContent>* aux;
			Substring<TypeOfContent>* aux2;

			while(aux != 0)
			{
				aux2 = aux;
				aux = aux->next;
				delete aux2;
			}

		}

		/**
		 * Adiciona uma nova substring a lista de substrings
		 * \param substring substring que será adicionada.
		 */
		void addSubstring(Substring<TypeOfContent>* substring)
		{
			if(!(numberOfSubstrings == 0))
			{
				end->next = substring;
				substring->previous = end;
				end = end->next;

			}
			else
			{
				begin = substring;
				begin->next = 0;
				begin->previous = 0;
				end = substring;
			}
			numberOfSubstrings++;
		}




};
