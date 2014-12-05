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
#ifndef _Reader
#define _Reader
#endif

#ifndef _Letter
#include "Letter.h"
#endif

#ifndef _Box
#include"Box.h"
#endif

#include <stdio.h>

#include <stdlib.h>
#include <fstream>
#include <stdexcept>
#include <fstream>

typedef char* string ;

/**
 * \class Reader
 * \tparam TypeOfContent tipo da letra do alfabeto utilizado. Tipo dos termos de text e pattern
 * tipo usado para a leitura dos arquivos que contem o texto
 */
template < typename TypeOfContent >
class Reader
{
	public:
		/// arquivo que contem o texto
		std::fstream textFile;

		/// arquivo que contem o pattern

		std::fstream patternFile;

		/**
		 * Construtor que, atraves dos nomes dos arquivos, os abre.
		 * \param patternFileName nome do arquivo contendo pattern
		 * \param textFileName nome do arquivo contendo text
		 */
		Reader ( string patternFileName , string textFileName )
		{
			/*
				http://www.cplusplus.com/reference/ios/skipws/
			*/

			if(! fileExist(patternFileName) || ! fileExist(textFileName))
			{
				throw std::invalid_argument( "file not exist" );
				exit (EXIT_FAILURE);
			}
			textFile.open ( textFileName , std::fstream::in );

			textFile.unsetf(std::ios::skipws);
			patternFile.open ( patternFileName , std::fstream::in );
			patternFile.unsetf(std::ios::skipws);
		}

		/**
		 * transforma os dados de um arquivo diretamente no tipo Box
		 * Usado quando o dado a ser trabalho eh char.
		 * Quando for token, apos a leitura do arquivo eh necessario realizar
		 * um passo a mais para a tokenização
		 * \return void
		 */
		void printFiles()
		{
			textFile.seekg (0, textFile.end);
			int textSize = textFile.tellg();
			textFile.seekg (0, textFile.beg);

			patternFile.seekg (0, patternFile.end);
			int patternSize = patternFile.tellg();
			patternFile.seekg (0, patternFile.beg);

			for(int i = 0; i < textSize; i++)
			{
				TypeOfContent aux;
				textFile >> aux;

				std::cout << aux;
			}

			printf("\n");

			for(int i = 0; i < patternSize; i++)
			{
				TypeOfContent aux;
				patternFile >> aux;

				std::cout << aux;
			}


			std::cout << "\n";
		}

		inline bool fileExist (const std::string& name)
		{
		    std::ifstream f(name.c_str());
		    if (f.good())
		    {
		        f.close();
		        return true;
		    }
		    else
		    {
		        f.close();
		        return false;
		    }
		}

		/**
		 * através dos arquivos encontrados no construtor,
		 * lê cada arquivo e para cada um adiciona seu respectivo conteúdo
		 * em um vetor de Letter<char> diferente. Por fim, agrupa-os, junto aos
		 * seus tamanhos em um objeto do tipo Box
		 * \return box contendo os vetores de Letter<char> criados e seus tamanhos
		 * \see Letter
		 * \see Box
		 */
		Box<TypeOfContent>* filesToBox ( )
		{
			/*
			 enviando o ponteiro textFile para o final do arquivo(fseek),
			 pegando o tamanho do arquivo(ftell) e voltando o ponteiro para
			 o inicio da arquivo(rewind)
			 */
			textFile.seekg (0, textFile.end);
			int textSize = textFile.tellg();
			textFile.seekg (0, textFile.beg);

			Letter<TypeOfContent>* text =  new Letter<TypeOfContent>[textSize];

			for ( int i = 0 ; i < textSize ; i++ )
			{
				TypeOfContent auxContent ;

				textFile >> auxContent;

				(text[i]).content = auxContent;

				//printf("%c %c\n", auxContent, (text[i]).content);
				(text[i]).marked = false;
				if(i != 0)
				{
					(text[i]).previousUnmarked = i-1;
					(text[i-1]).nextUnmarked = i;
				}
				else
				{
					(text[i]).previousUnmarked = -1;
				}
			}

			std::cout << "\n";

			/*
			enviando o ponteiro textFile para o final do arquivo(fseek),
			pegando o tamanho do arquivo(ftell) e voltando o ponteiro para
			o inicio da arquivo(rewind)
			*/

			patternFile.seekg (0, patternFile.end);
			int patternSize = patternFile.tellg();
			patternFile.seekg (0, patternFile.beg);

			Letter<TypeOfContent>* pattern = new Letter<TypeOfContent>[patternSize] ;

			for ( int i = 0 ; i < patternSize ; i++ )
			{
				TypeOfContent auxContent ;


				patternFile >> auxContent;

				(pattern[i]).content = auxContent;

				//printf("%c %c\n", auxContent, (pattern[i]).content);

				(pattern[i]).marked = false;
				if(i != 0)
				{
					(pattern[i]).previousUnmarked = i-1;
					(pattern[i-1]).nextUnmarked = i;
				}
				else
				{
					(pattern[i]).previousUnmarked = -1;
				}
			}


			Box<TypeOfContent>* box = new Box<TypeOfContent>(pattern, patternSize, text, textSize);

			return box;
		}

} ;
