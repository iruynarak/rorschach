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

#ifndef _HashTable
#define _HashTable
#endif

#ifndef _ListOfSubstrings
#include "ListOfSubstrings.h"
#endif

#include <iostream>
using namespace std;

/**
 * \class HashTable
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos da pattern e da text
 * Classe que implementa uma tabela de valores de hash
 * \see RollingHash
 * \see ListOfSubstrings
 */
template <typename TypeOfContent>
class HashTable
{

	public:
		/// quantidade de valores diferentes possiveis para o valor da hash
		int hashTableSize;

		/// vetor de listas de substrings (uma para cada possivel valor de hash)
		ListOfSubstrings<TypeOfContent>* table;

		/**
		 * Construtor da classe HashTable
		 * \param primeNumber número primo que define o limite superior para o valor de hash
		 */
		HashTable(int primeNumber)
		{
			this->hashTableSize = primeNumber;
			table = new ListOfSubstrings<TypeOfContent>[hashTableSize];
		}

		/**
		 * Adiciona um novo termo na HashTable
		 * \param substring estrutura que contém o termo a ser adicionado e seu respectivo valor de hash
		 */
		void addHash(Substring<TypeOfContent>* substring)
		{
			(table[substring->rollingHash->hashValue]).addSubstring(substring);
		}

		/**
		 * Imprime o conteudo da tabela de hash
		 */
		void printHashTable()
		{

			Substring<TypeOfContent>* aux;

			for(int i = 0; i < hashTableSize; i++)
			{
				for(aux = table[i].begin; aux != 0; aux= aux->next)
				{
					aux->print();
				}

			}
		}
};

