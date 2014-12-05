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
#ifndef _Tile
#define _Tile
#endif
/*
template <typename TypeOfContent>
Nao precisarei do codigo acima ja que esta classe apenas
indica aonde esta o Tile. Ela nao cria um vector/lista de Letters
que representa um Tile
*/
/**
 * \class Tile
 * Classe referente a uma Tile.
 */
class Tile
{
	public:
		/// ponteiro para o próximo objeto da classe Tile contido na mesma lista que este
		Tile*	next;
		/// ponteiro para o prévio objeto da classe Tile contido na mesma lista que este
		Tile* previous;

		/// Índice para a letra inicial deste Tile na string
		int begin;

		/// Índice para a letra final deste Tile na string
		int end;

		/**
		 * Construtor de um objeto da classe Tile
		 * \param begin Índice da posição inicial do Tile na string
		 * \param end Índice da posição final do Tile na string
		 */
		Tile( int begin, int end)
		{
			this->begin = begin;
			this->end = end;
			/*
			OBS:
			nextTile e previousTile serao inicializados pela classe que criou o Tile
			*/
		}
};
