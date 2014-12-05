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
#ifndef _Substring
	#define _Substring
#endif

#ifndef _Letter
	#include "Letter.h"
#endif

#ifndef _RollingHash
	#include "RollingHash.h"
#endif

/**
 * \class Substring
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo do termo da substring.
 * Classe referente a um candidato a Tile.
 * além do seu ponteiro para a string que contém, índice de início e de fim, também possui uma RollingHash para o seu conteúdo
 */
template <typename TypeOfContent>
class Substring
{
	public:

		/// Ponteiro para a string que a contém
		Letter<TypeOfContent>* string;
		/// Ponteiro para a próxima substring na lista
		Substring<TypeOfContent>* next;
		/// Ponteiro para a substring anterior na lista
		Substring<TypeOfContent>* previous;

		/// ponteiro para a hash relativa ao seu conteúdo
		RollingHash<TypeOfContent>* rollingHash;

		///Índice inicial da substring na sua string de origem
		int begin;

		///Índice inicial da substring na sua string de origem
		int end;


		/**
		 * Construtor da classe Substring
		 * \param string ponteiro para a string que a contém
		 * \param begin índice para sua posição inicial na string que a contém
		 * \param end índice para sua posição final na string que a contém
		 * \param baseLength base do alfabeto ao qual pertence cada termo da string
		 * \param primeNumber número primo usado para evitar overflow do valor de hash
		 * \param begin Índice inicial da substring na sua string de origem
		 * \param end Índice inicial da substring na sua string de origem
		 */
		Substring(Letter<TypeOfContent>* string, int begin, int end, int baseLength, int primeNumber)
		{
			this->begin = begin;
			this->end = end;
			this->string = string;

			rollingHash = new RollingHash<TypeOfContent>(baseLength, primeNumber, string);

			for(int i = begin; i <= end; i++)
			{
				rollingHash->append(i);
			}
			next = 0;
			previous = 0;
		}


		/**
		 * Destrutor da classe Substring
		 */
		~Substring()
		{
			delete rollingHash;
		}


		/**
		 * Método que adiciona um novo termo a substring. Isto é feito através do ponteiro para
		 * a string que a contém. Adicionamos o termo posterior a substring.
		 * \see RollingHash
		 * \return void
		 */
		void append()
		{
			rollingHash->append(rollingHash->end +1);
			end++;
		}


		/**
		 * Método que remove um termo da substring.
		 * \see RollingHash
		 * \return void
		 */
		void skip()
		{
			rollingHash->skip();
			begin++;
		}


		/**
		 * Imprimindo indices e valor de hash da substring
		 * \see RollingHash
		 * \return void
		 */
		void print()
		{
			printf("begin: %d | end: %d | hash: %lld\n", rollingHash->begin, rollingHash->end, rollingHash->hashValue);
		}



};
