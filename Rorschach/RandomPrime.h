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
#ifndef _RandomPrime
#define _RandomPrime
#endif

#ifndef _RandomNumber
#include "RandomNumber.h"
#endif

/**
 * \class RandomPrime
 * Classe que cria um número primo aleatório
 */
class RandomPrime
{

	public:
		/// Ponteiro para a classe que cria um número aleatório, primo ou não
		RandomNumber* randomNumber;

		/**
		 *Construtor da classe RandomPrime
		 */
		RandomPrime()
		{
			randomNumber = new RandomNumber();
		}

		/**
		 * Destrutor da classe RandomPrime
		 */
		~RandomPrime()
		{
			delete randomNumber;
		}

		/**
		 * Verifica se um certo número é primo ou não
		 * \param number - número que será verificado
		 * \return bool - true caso seja primo e false caso contrário
		 */
		bool isPrime(int number)
		{
			for(int i = 2; i < number/2; i++)
			{
				if(number % i == 0)
				{
					return false;
				}
			}
			return true;
		}

		/**
		 * Gera um número primo aleatório
		 * \param min - menor número possível de ser retornado
		 * \param max - maior número possível de ser retornado
		 * \return número primo gerado
		 */
		int newRandomPrime(int min, int max)
		{
			int randomPrime;

			while(true)
			{
				randomPrime = randomNumber->newRandomNumber(min, max);
				if(isPrime(randomPrime))
				{
					break;
				}
			}


			return randomPrime;
		}
};
