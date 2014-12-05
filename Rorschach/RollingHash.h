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
#ifndef _RollingHash
#define _RollingHash
#endif

#include<math.h>
#include<limits>
#include<stdlib.h>


#ifndef _RandomPrime
#include "RandomPrime.h"
#endif

#include<stdio.h>
#include<iostream>

/**
 * \class RollingHash
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo do termo adicionado a fila
 * classe que realiza a implementação da Rolling Hash
*/
template <typename TypeOfContent>
class RollingHash
{

	public:

		/// valor da hash referente ao conteudo da fila
		long long hashValue;

		/** numero primo utilizado para limitar
		*o valor da hash evitando overflow
		*/
		int primeNumber;

		/// quantidade de termos sendo usados para construir a hash
		int length;

		/// base do alfabeto utilizado na criação da hash
		int baseLength;

		/// ponteiro para a palavra que será usada na Rolling Hash
		Letter<TypeOfContent>* string;

		/// índice do início do trecho para o qual a Rolling Hash se refere
		int begin;

		/// índice do fim do trecho para o qual a Rolling Hash se refere
		int end;

		/**
		 * Construtor da Rolling Hash
		 * \param baseLength base do alfabeto utilizado na criação da hash
		 * \param randomPrime número primo utizado para limitar o valor da hash evitando overflow
		 * \param string ponteiro para a palavra que será usada na Rolling Hash
		 */
		RollingHash(int baseLength, int randomPrime, Letter<TypeOfContent>* string)
		{

			hashValue = 0;
			length = 0;

			this->baseLength = baseLength;

			/// primo escolhido deve ser maior ou igual que tamanho da string, ou seja, primeNumber >= length
			this->primeNumber = randomPrime;

			this->string = string;
			begin = -1;
			end = -1;
		}

		/**
		 *retorna o valor de hash atual
		 * @return void
		 */
		int getHashValue()
		{
			//printf("%d", hashValue);

			return hashValue;
		}

		/**
		 * adiciona uma nova letra a hash,
		 * atualizando o valor de hash, length e fila
		 * \param i Ponteiro para a localização da letra cujo tipo é TypeOfContent e que será adicionada
		 * \return void
		 */
		void append(int i)
		{

			// assumindo aqui que adicionamos sempre o termo uma unidade à direita do último termo da hash
			end = i;
			if(begin == -1)
			{
				begin = end;
			}
			int newT = (string[i]).content;
			length++;
			//hashValue = (hashValue * baseLength + newT) % primeNumber;
			hashValue = hashValue * baseLength; //shift
			hashValue = hashValue + newT; //acrescentando o novo termo
			//std::cout<< "newT=" << newT << "hashValue" << hashValue << "\n";
			hashValue = hashValue % primeNumber; //evitando overflow
		}

		/**
		 * retira a primeira letra da fila, ou seja,
		 * a mais antiga
		 * \return void
		 */
		void skip()
		{

			int oldT = (string[begin++]).content;

			if(std::numeric_limits<int>::max() <= pow(baseLength, length-1))
			{
				std::cout <<  "Estourou em pow(baseLength, length-1)\n";
				exit (EXIT_FAILURE);
			}

			if(std::numeric_limits<int>::max() <= (oldT*((unsigned long)pow(baseLength, length-1) % primeNumber)) % primeNumber)
			{
				std::cout <<  "Estourou em (oldT*((unsigned long)pow(baseLength, length-1) % primeNumber)) % primeNumber\n";
				exit (EXIT_FAILURE);
			}

			unsigned long aux =  (oldT*((unsigned long)pow(baseLength, length-1) % primeNumber)) % primeNumber;

			hashValue = hashValue - aux;

			length--;


			hashValue = hashValue<0? (primeNumber+hashValue) % primeNumber: hashValue % primeNumber;
		}

		/**
		 *imprime o valor da hash atual e os termos que serviram para a sua criação
		 * \return void
		 */
		void print()
		{
			printf("[%lld]\n", hashValue);


		}

		/**
		 * sobreescrevendo o operador == para que possamos comparar o conteúdo
		 * da RollingHash, ou seja, o conteúdo guardado na fila. Isto é útil
		 * durante a verificação de igualdade entre duas RollingHash cujos valores
		 * de hash delas são iguais.
		 * \param other a segunda RollingHash sendo comparada
		 * \return retorna true caso os conteúdos delas sejam iguais. Falso caso contrário
		 */
		inline bool operator ==(const RollingHash& other ) const
		{

			if( this->begin == other->begin && this->end == other->end && this->string == other->string)
			{
				return true;
			}

			return false;

		}





};
