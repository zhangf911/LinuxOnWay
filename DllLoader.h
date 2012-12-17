/*
 * DllLoader.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef DLLLOADER_H_
#define DLLLOADER_H_

#include "Common.h"

namespace LOW
{
	class DllLoader
	{
	private:
		/** ¶¯Ì¬¿âÃû³Æ **/
		std::string filename;
		/** ¶¯Ì¬¿âÈë¿ÚµØÖ· **/
		void *lptr;
		/** ×îºó´íÎó×´Ì¬ **/
		bool error;
	public:
		/**
		* @brief ¹¹Ôìº¯Êý
		* @param dllÎÄ¼þÂ·¾¶Ãû
		* @exception
		* @note
		*/
		DllLoader( const char *libfilename = "" );

		/**
		* @brief Îö¹¹º¯Êý
		* @exception
		* @note
		*/
		~DllLoader();

		/**
		* @brief ¼ÓÔØ¶¯Ì¬Á´½Ó¿â
		* @return true : ³É¹¦ false : Ê§°Ü
		* @exception
		* @note
		*/
		bool Load();

		/**
		* @brief Ð¶ÔØ¶¯Ì¬¿â
		* @exception
		* @note
		*/
		void Close();

		/**
		* @brief »ñÈ¡½Ó¿ÚµØÖ·
		* @param ½Ó¿ÚÃû³Æ
		* @return ½Ó¿ÚµØÖ·
		* @exception
		* @note
		*/
		void* GetAddressForSymbol( const char *symbol );

		/**
		* @brief »ñÈ¡×îºó´íÎó×´Ì¬
		* @return ×îºó´íÎó×´Ì¬
		* @exception
		* @note »ñÈ¡´íÎó×´Ì¬²¢ÖØÖÃÎªfalse
		*/
		bool Error()
		{
			bool lasterror = error;

			error = false;

			return lasterror;
		}

		/**
		* @brief »ñÈ¡¶¯Ì¬¿âÃû³Æ
		* @return ¶¯Ì¬¿âÃû³Æ
		* @exception
		* @note
		*/
		std::string GetName()
		{
			return filename;
		}

	};
}


#endif /* DLLLOADER_H_ */
