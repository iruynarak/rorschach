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

#ifndef	_Letter
#define	_Letter
#endif

/**
 * \class Letter
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos da pattern e da text
 * Classe que armazena cada letra lida do alfabeto em questão
 */
template < typename TypeOfContent >
class Letter
{
	public:
		//------------------------------------------
		// Como estamos trabalhando um conjunto de Letter como array e não lista,
		//as posicoes estao marcadas pelos seus indices

		/// Índice da Letter não marcada posterior a esta
		int nextUnmarked ;
		/// Índice da Letter não marcada anterior a esta
		int previousUnmarked ;
		//------------------------------------------
		/// True caso esta Letter está marcada e false caso contrário
		bool marked ;
		//------------------------------------------
		/// Conteúdo da Letter
		TypeOfContent content ;

} ;
