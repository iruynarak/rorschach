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
#ifndef _ListOfTiles
#define _ListOfTiles
#endif


#ifndef _Tile
#include "Tile.h"
#endif

#include<stdio.h>

/*
Nao precisarei do template "template <typename TypeOfContent>" do codigo acima ja que esta classe apenas
indica aonde esta o Tile. Ela nao cria um vector/lista de Letters
que representa um Tile
*/
/**
 * \class ListOfTiles
 * Classe que guarda objetos do tipo Tile
 * \see Tile
 */
class ListOfTiles
{

	public:

		/// Ponteiro para o primeiro objeto do tipo Tile na lista
		Tile* begin;

		/// Ponteiro para o último objeto do tipo Tile na lista
		Tile* end;

		/// Quantidade de objetos do tipo Tile na lista
		int numberOfTiles;

		/**
		 * Construtor de um objeto da classe ListOfTiles
		 */
		ListOfTiles()
		{
			begin = 0;
			numberOfTiles = 0;
			end = 0;
		}

		/**
		 * Destrutor de um objeto da classe ListOfTiles
		 */
		~ListOfTiles()
		{
			Tile* aux = begin;
			Tile* aux2;
			while(aux != NULL)
			{
				/*aux2 é utilizado já que se aux se tornar NULL após fazer
				"aux = aux->next; " e assim não conseguiriamos recuperar/deletar seu o termo
				anterior a ele
				*/
				aux2 = aux;

				aux = aux->next;

				delete aux2;
			}
		}

		/**
		 * Adiciona um novo objeto da classe Tile na lista
		 * \param tile Ponteiro para o objeto da classe Tile a ser adicionado
		 * \return Não há retorno
		 */
		void addTile(Tile* tile)
		{
			if(numberOfTiles == 0)
			{
				begin = tile;
				end = tile;
				begin->previous = NULL;
				begin->next = NULL;

			}

			numberOfTiles++;

			end->next = tile;
			tile->previous = end;
			tile->next = NULL;
			end = tile;

		}

		/**
		 * Imprime, para cada objeto da classe Tile na lista, o seu índice de início e de fim.
		 * \return Não há retorno
		 */
		void print()
		{
			Tile* aux = begin;

			while(aux != NULL)
			{
				printf("[%d | %d]\n", aux->begin, aux->end);
				aux = aux->next;
			}
		}

		/**
		 * Remove objeto da classe Tile
		 * \param tileBeginIndex Índice da primeira posição da tile a ser removida
		 * \param tileEndIndex Índice da última posição da tile a ser removida
		 * \return Não há retorno
		 */
		void removeTile(int tileBeginIndex, int tileEndIndex)
		{
			Tile* aux = begin;

			while(aux != NULL)
			{
				if(aux->begin == tileBeginIndex && aux->end== tileEndIndex)
				{
					if(aux != begin)
					{
						aux->previous->next = aux->next;
					}
					if(aux != end)
					{
						aux->next->previous = aux->previous;
					}
					if(aux == begin)
					{
						begin = aux->next;
					}
					if(aux == end)
					{
						end = aux->previous;
					}

					delete aux;

					break;
				}
				aux = aux->next;
			}
		}
};
