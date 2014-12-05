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
#ifndef _RandomNumber
#define _RandomNumber
#endif

#include<stdlib.h> //rand
#include<time.h>//time
#include<stdio.h>//printf

/**
 * \class RandomNumber
 * Cria um número inteiro aleatório entre dois inteiros,min e max.
 */
class RandomNumber
{
	public:
		/// Construtor que inicializa a semente da função que gera o número aleatório
		RandomNumber()
		{
			srand (time(NULL));
		}

		/**
		 * Gera um número aleatório x, sendo min <= x <= max
		 * \param min Valor mínimo possível de ser atribuído ao número criado
		 * \param max Valor máximo possível de ser atribuído ao número criado
		 */
		int newRandomNumber(int min, int max)
		{
			int prime;
			int length = max - min;
			prime = (rand()%length)+ min;

			return prime;
		}

};
