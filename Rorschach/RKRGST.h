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
#ifndef _RKRGST
	#define _RKRGST
#endif

#ifndef _Box
	#include"Box.h"
#endif

#ifndef _listOfPatternTiles
	#include"ListOfTiles.h"
#endif

#ifndef _HashTable
	#include "HashTable.h"
#endif

#ifndef _ListOfMatches
	#include "ListOfMatches.h"
#endif

#define MAX_LENGTH 20

/** \class RKRGST
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos da pattern e da text
 * Classe contendo todos os algoritmos realizados pelo RKRGST
 */

#include<stdio.h>

template < typename TypeOfContent >
class RKRGST
{

	public:
		//-------------------------------------------------------------------------------------------------------------
		/// Tamanho inicial do padrão buscado
		int initialSearchLength;
		/// Tamanho mínimo a ser buscado
		int minimumSearchLength;

		/// Número primo utilizado na hash
		int primeNumber;

		/// Container de dados que guarda a palavra que compõe a Text, a palavra que contém a Pattern e seus respectivos tamanhos
		Box < TypeOfContent >* box ;

		/// Ponteiro para um objeto da classe ListOfTiles que contém uma lista de objetos da classe Tile relativos à Pattern
		ListOfTiles* listOfPatternTiles;

		/// Ponteiro para um objeto da classe ListOfTiles que contém uma lista de objetos da classe Tile relativos à Text
		ListOfTiles* listOfTextTiles;

		///Tamanho da base dos números gerados pela RollingHash.
		int baseLength;

		int lengthOfTokensTiled;

		ListOfMatches* listOfFinalTiles;


		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Construtor de objeto da classe RKRGST
		 * \param box Container de dados que guarda a palavra que compõe a Text, a palavra que contém a Pattern e seus respectivos tamanhos
		 * \param initialSearchLength Tamanho inicial do padrão buscado
		 * \param minimumSearchLength Tamanho mínimo a ser buscado
		 * \param baseLength Tamanho da base dos números gerados pela RollingHash.
		 */
		RKRGST ( Box<TypeOfContent>* box, int initialSearchLength, int minimumSearchLength, int baseLength)
		{
			RandomPrime randomPrime;
			this->box = box ;
			this->minimumSearchLength = minimumSearchLength;
			this->initialSearchLength = initialSearchLength;
			primeNumber = randomPrime.newRandomPrime((2*baseLength)+1, 10*baseLength);
			listOfPatternTiles = new ListOfTiles();
			listOfTextTiles = new ListOfTiles();
			this->baseLength = baseLength;
			lengthOfTokensTiled = 0;
			listOfFinalTiles = new ListOfMatches();

		}
		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Método que executa t odo o algoritmo RKRGST
		 */
		void execute ()
		{
			int searchLength = initialSearchLength ;
			ListOfMatches* listOfMatches = new ListOfMatches();

			int maxLength, first = 1;



			while ( 1 )
			{
				//print de verificacao:

				//cout << "------------------------------\n";
				//cout << "minimum: " << minimumSearchLength << " | searchLength: " << searchLength << "\n\n";
				maxLength = scanPattern ( searchLength, listOfMatches  ) ;
				if ( maxLength > 2 * searchLength && first)
				  {
				    searchLength = maxLength ;
				    if( maxLength > MAX_LENGTH){
				      searchLength = MAX_LENGTH;
				      first = 0;
				    }
				  }
				else
				  {
				    markArrays ( searchLength, listOfMatches ) ;
				    if ( searchLength > 2 * minimumSearchLength )
				      {
					searchLength = searchLength / 2 ;
				      }
				    else if ( searchLength > minimumSearchLength )
				      {
					searchLength = minimumSearchLength ;
				      }
				    else
				      {
					break ;
				      }
				  }
			}
			//cout << "------------------------------\n";

			//scanPattern(searchLength, listOfMatches);
			//markArrays(searchLength, listOfMatches);
			//delete listOfMatches;
		}
		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Método que marca as letras de um casamento
		 *\param searchLength Tamanho do casamento.
		 *\param listOfMatches Casamentos a serem marcados.
		 */
		void markArrays ( int searchLength, ListOfMatches* listOfMatches )
		{

			//print de verificacao:
			//cout << "Entrei na markArrays()\n";
			//cout << " numberOfMatches == " << listOfMatches->numberOfMatches << "\n";
			Match* match;
			while(listOfMatches->numberOfMatches != 0)
			{
				match = listOfMatches->remove();
				//verificar se ocorre oclusao
				if(!occluded(box, match))
				{
					listOfFinalTiles->insert(match->length, match->patternIndex, match->textIndex);
					//cout << "NOT OCCLUDED\n";
					markTokens(box, match);
					lengthOfTokensTiled += match->length;
				}
				else
				{
					//cout << "OCCLUDED\n";;
				}

				delete match;
			}
			return ;
		}
		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Buscando casamentos de tamanho searchLength
		 * \param searchLength Tamanho do casamento sendo buscado.
		 * \param listOfMatches Lista de casamentos encontrados na scanPattern.
		 */
		int scanPattern ( int searchLength, ListOfMatches* listOfMatches )
		{
			int j;
			int patternIndex;
			///Tabela de Hash contendo as substrings de Text
			HashTable<TypeOfContent>* textHashTable = new HashTable<TypeOfContent>(primeNumber);
			int returnLength = 0;

			//1. Starting at the first unmarked token of T, for each unmarked T t do
				//1.1. if distance to next tile ≤ s then advance t to first unmarked token after next tile
				//1.2. else create the KR hash-value for substring T t to T t+s−1 and add to hashtable
			fillTextHashTable(searchLength, textHashTable);

			//print de verificacao
			//textHashTable->printHashTable();

			//2. Starting at the first unmarked token of P, for each unmarked P p do
				//2.1. if distance to next tile ≤ s then advance p to first unmarked token after next tile
				//2.2. else

			int actualIndex = 0;
			while((patternIndex = findPatternSubstring(searchLength, textHashTable, actualIndex)) != -1)
			{
				actualIndex = patternIndex + 1;

				//print de verificacao:
				//cout << ">>>patternIndex: " << patternIndex << "\n";

				//create the KR hash-value for substring P p to P p+s−1
				Substring<TypeOfContent>* patternSubstring = new Substring<TypeOfContent>(box->pattern, patternIndex, patternIndex + searchLength -1, baseLength, primeNumber);

				int numberOfSubstringsWithSameHashValue = (textHashTable->table[patternSubstring->rollingHash->hashValue]).numberOfSubstrings;
				//check hashtable for hash of KR hash-value
				if(numberOfSubstringsWithSameHashValue != 0)
				{

					//for each hash-table entry with equal hashed KR hash-value do

					Substring<TypeOfContent>* textSubstring = (textHashTable->table[patternSubstring->rollingHash->hashValue]).begin;

					for(int i = 0; i <  numberOfSubstringsWithSameHashValue; i++, textSubstring = textSubstring->next)
					{

						//if for all j from 0 to s-1, P p+ j = T t+ j then /* IE match is not hash artifact */

						for(j = 0; j < searchLength; j++)
						{

							//print de verificacao
							//cout << "pattern: " << patternSubstring->string[(patternSubstring->begin + j)].content << "\n";
							//cout << "text: " << (textSubstring->string[textSubstring->begin + j]).content << "\n";

							if((patternSubstring->string[patternSubstring->begin + j]).content != (textSubstring->string[textSubstring->begin + j]).content)
							{
								break;
							}
							if((patternSubstring->string[patternSubstring->begin + j]).marked || (textSubstring->string[textSubstring->begin + j]).marked)
							{
							  break;
							}

						}
						//k: = s
						if(j == searchLength)
						{
							//print de verificacao:
							//cout << "Ocorreu match\n";

							//while P p+k = T t+k AND unmarked(P p+k ) AND unmarked(T t+k ) do
							//k := k + 1

							int k = 1;


							while
							(
									(box->patternSize > (patternSubstring->begin + searchLength + k -1))
									&&
									(box->textSize > (textSubstring->begin + searchLength + k -1))
									&&
									((patternSubstring->string[patternSubstring->begin + searchLength+ k-1 ]).content == (textSubstring->string[textSubstring->begin + searchLength + k -1]).content)
									&&
									!(patternSubstring->string[patternSubstring->begin + searchLength+ k-1]).marked
									&&
									!(textSubstring->string[textSubstring->begin + searchLength+ k-1]).marked
							)

							{
//
								k++;
							}

							//if k > 2 × s then return(k) /* and restart scanpattern with s = k */
							//print de verificacao
//							if(k -1 > 0)
//							{
//								cout << "\tfoi possivel aumentar o match de " << searchLength << " para " << searchLength + k -1  << "\n";
//							}

							if(j+k-1 > 2 * searchLength && j+k-1 <= MAX_LENGTH)
							{

								returnLength = searchLength + k -1;
								//listOfMatches->insert(searchLength + k -1, patternSubstring->begin, textSubstring->begin);
								return returnLength;
							}

							//else record new maximal-match
							else
							{
								returnLength = searchLength;
								//o "-1" abaixo é causado pois o k eh iterado uma vez a mais do que a ultima posicao correta
								listOfMatches->insert(searchLength + k -1, patternSubstring->begin, textSubstring->begin);
							}
						}

					}
				}
			}
			//Return(length of longest maximal-match)
			return returnLength ;
		}
		//-------------------------------------------------------------------------------------------------------------
		/** Encontra o índice do início de uma substring de tamanho searchLength. Nenhuma as suas letras podem estar marcadas.
		 * \param searchLength Tamanho das substrings buscadas.
		 * \param textHashTable Tabela de Hash das subcadeias de text.
		 * \param actualIndex indice da letra do pattern
		 * \return Retorna o índice inicial da substring ou -1 caso não haja substring de tamanho searchLength sem letras marcadas.
		 */
		int findPatternSubstring(int searchLength, HashTable<TypeOfContent>* textHashTable, int actualIndex)
		{
			//2. Starting at the first unmarked token of P, for each unmarked P p do
			Letter<TypeOfContent>* pattern = box->pattern;

			//indice da letra nao marcada em pattern
			int i = actualIndex;
			//caso a primeira letra nao seja a primeira nao marcada,
			//achar a primeira nao marcada
			if((pattern[i]).marked == true)
			{
				i = (pattern[i]).nextUnmarked;
			}
			//print de verificacao:
			//cout << "Indice da primeira string na findPatternString: " << i << "\n";

			//para isto devemos achar a primeira tile posicionada após i e calcular a distância a ela
			Tile* tile;
			while(true)
			{
				tile = listOfPatternTiles->begin;

				//print de verificacao:
				//cout << "Conteudo da listOfPatternTile: " << tile;

				//procurando a primeira Tile localizada após a letra de índice i em Pattern
				while(tile != 0 && i > tile->begin)
				{
					tile = tile->next;
				}


				//caso haja um objeto da classe Tile localizado após o Pattern de índice i.
				if(tile != 0)
				{
					//print de verificacao:
					//cout << "tile->begin: " << tile->begin << "\n";

					if(( tile->begin - i) > searchLength)
					{
						return i;
					}
					else
					{
						return (pattern[tile->end]).nextUnmarked;
					}

				}

				//caso  NÃO haja um objeto da classe Tile localizado após o Pattern de índice i.
				//if(tile == 0)
				else
				{

					//print de verificacao:
					//cout << " box->patternSize: " << box->patternSize << " i: " << i << " searchLength: " << searchLength << "\n";

					if(box->patternSize >= i + searchLength)
					{

						return i;
					}
					else
					{
						return -1;
					}
				}
			}

			return -1;
		}
		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Preenche a tabela de hash do texto com todas as substrings de tamanho searchLength não marcadas
		 * \param searchLength Tamanho das substrings buscadas.
		 * \param textHashTable Tabela de Hash das subcadeias de text.
		 * \see HashTable
		 */
		void fillTextHashTable(int searchLength, HashTable<TypeOfContent>* textHashTable)
		{
			bool reuse = false;

			Substring<TypeOfContent>* aux;

			Substring<TypeOfContent>* aux2;

			//print de verificacao:
			//cout << "Inicio da fillTextHashTable\n";

			//1. Starting at the first unmarked token of T, for each unmarked T t do

			//achando primeiro nao marcado
			int index = 0;

			if((box->text[0]).marked == true)
			{
				index = (box->text[0]).nextUnmarked;
			}

			while(index < box->textSize)
			{
				//print de verificacao:
				//cout << "Laco exterior da fillTextHashTable\n";


				//1.1. if distance to next tile ≤ s then advance t to first unmarked token after next tile
				//1.2. else create the KR hash-value for substring T t to T t+s−1 and add to hashtable

				//achando distancia para o tile que inicia em uma posicao posterior a index no texto
				Tile* tile = listOfTextTiles->begin;

				while(tile != 0 && tile->begin < index)
				{
					tile = tile->next;
				}

				//sao duas as possiveis causas do fim do laco anterior. acabaram-se os tiles ou index ficou para tras

				//caso tenham acabado os tiles sem acharmos um posterior a index.
				//devemos entao verificar se entre index e o fim do texto cabe uma substring de tamanho searchLength
				if(tile == 0)
				{
					//cabe
					if(box->textSize >= index + searchLength)
					{
						if(reuse)
						{
							aux2 = new Substring<TypeOfContent>(box->text,0, 0, baseLength, primeNumber);

							//print de verificacao:
							//cout << "REUSE\n";

							//todo: criar sobrecarga no operador = para RollingHash e Substring

							aux2->string = aux->string;

										aux2->next = aux->next;

										aux2->previous = aux->previous;

										aux2->rollingHash = new RollingHash<TypeOfContent>(aux->rollingHash->baseLength, aux->rollingHash->primeNumber, aux->rollingHash->string);

													aux2->rollingHash->hashValue = aux->rollingHash->hashValue;

													aux2->rollingHash->primeNumber = aux->rollingHash->primeNumber;

													aux2->rollingHash->length = aux->rollingHash->length;

													aux2->rollingHash->baseLength = aux->rollingHash->baseLength;

													aux2->rollingHash->string = aux->rollingHash->string;

													aux2->rollingHash->begin = aux->rollingHash->begin;

													aux2->rollingHash->end = aux->rollingHash->end;

										aux2->begin = aux->begin;

										aux2->end = aux->end;

							//print de verificacao:
							//aux->print();
							//aux2->print();

							aux2->skip();
							aux2->append();

							//print de verificacao:
							//aux->print();
							//aux2->print();

							//print de verificacao:
							//cout << aux << "\n";
							//cout << aux2 << "\n";
							//cout << aux->rollingHash << "\n";
							//cout << aux2->rollingHash << "\n";



							textHashTable->addHash(aux2);

							aux = aux2;
						}
						else
						{
							//cout << "NOT REUSE\n";
							aux = new Substring<TypeOfContent>(box->text, index, index + searchLength - 1, baseLength, primeNumber);
							textHashTable->addHash(aux);
						}

						//verificando a substring pode ser reaproveitada na proxima iteracao
						if(box->textSize >= index + searchLength + 1)
						{
							reuse = true;
						}
						else
						{
							reuse = false;
						}
					}
					//nao cabe
					else
					{
						break;
					}

				}

				//caso tenhamos achado tile posterior a index
				//devemos entao verificar se entre index e este tile cabe uma substring de tamanho searchLength
				else
				{
					//cabe
					if(tile->begin > index + searchLength - 1)
					{
						if(reuse)
						{
							aux2 = new Substring<TypeOfContent>(box->text,0, 0, baseLength, primeNumber);

							//print de verificacao:
							//cout << "REUSE\n";

							//todo: criar sobrecarga no operador = para RollingHash e Substring

							aux2->string = aux->string;

										aux2->next = aux->next;

										aux2->previous = aux->previous;

										aux2->rollingHash = new RollingHash<TypeOfContent>(aux->rollingHash->baseLength, aux->rollingHash->primeNumber, aux->rollingHash->string);

													aux2->rollingHash->hashValue = aux->rollingHash->hashValue;

													aux2->rollingHash->primeNumber = aux->rollingHash->primeNumber;

													aux2->rollingHash->length = aux->rollingHash->length;

													aux2->rollingHash->baseLength = aux->rollingHash->baseLength;

													aux2->rollingHash->string = aux->rollingHash->string;

													aux2->rollingHash->begin = aux->rollingHash->begin;

													aux2->rollingHash->end = aux->rollingHash->end;

										aux2->begin = aux->begin;

										aux2->end = aux->end;



							aux2->skip();
							aux2->append();

							textHashTable->addHash(aux2);

							aux = aux2;
						}
						else
						{
							aux = new Substring<TypeOfContent>(box->text, index, index + searchLength - 1, baseLength, primeNumber);
							textHashTable->addHash(aux);
						}

					}
					//nao cabe
					else
					{
						index = (box->text[tile->end]).nextUnmarked;
					}

					//verificando a substring pode ser reaproveitada na proxima iteracao
					if(tile->begin > index + searchLength)
					{
						reuse = true;
					}
					else
					{
						reuse = false;
					}

				}

				index++;
			}

			//print de verificacao:
			//cout << "Fim da fillTextHashTable\n";

		}
		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Verifica se o casamento é ocluso por algum tile.
		 * \param box Objeto contendo text, pattern e seus respectivos tamanhos.
		 * \param match Casamento a ser verificado
		 */
		bool occluded(Box<TypeOfContent>* box, Match* match)
		{
			for(int i = 0 ; i < match->length; i++)
			{
				if((box->text[match->textIndex + i]).marked || (box->pattern[match->patternIndex + i]).marked)
				{
					return true;
				}
			}

			return false;


		}

		//-------------------------------------------------------------------------------------------------------------
		/**
		 * Marca os tokens de um casamento
		 * \param box Objeto contendo text, pattern e seus respectivos tamanhos.
		 * \param match Casamento a ser marcado
		 */
		void markTokens(Box<TypeOfContent>*box, Match* match)
		{
			for(int i = 0 ; i < match->length ; i++)
			{
				(box->pattern[match->patternIndex + i]).marked = true;
				(box->text[match->textIndex + i]).marked = true;
			}
		}

		//-------------------------------------------------------------------------------------------------------------
} ;
