/**
	\file	cDebugger_Win.h
	\brief	Contains windows specific debugging classes
*/
#ifndef _CDEBUGGER_WIN_H_
#define _CDEBUGGER_WIN_H_

#include "cDebugger.h"

namespace bmutil
{
	/**
		\class	cDebugger_Win
		\brief	Windows implementation of the debug module driver

		\see	cDebugger
	*/
	class cDebugger_Win : public cDebugger
	{
	public:
		/**
			cDebugger_Win::Get

			\brief	Obtains the singleton instance of cDebugger_Win

			This method should not be called directly from any of your code.
			it is designed to be used internally.

			\return		The pointer to the singleton instance of cDebugger_Win

			\see		cDebugger::Get
		*/
		static cDebugger_Win* Get();

		/**
			cDebugger::outputTrace

			\brief	Windows driver for trace output

			Uses the OutputDebugString method to write trace messages to the
			debug console.  Formatting matches the format used to provide 
			code navigation from specific trace message.

			\param	iLevel	The trave level for this message
			\param	iFile	The file that this message originates from
			\param	iLine	The line number of this trace meesage
			\param	iMsg	The actual message contents
			\param	...		Variable param list for value substitution within message
		*/
		virtual void outputTrace (tuInt16 iLevel, const tChar8* iFile, tMemSize iLine, const tChar8* iMsg, ...);
		
		virtual ~cDebugger_Win(void);

	protected:
		cDebugger_Win(void);
	private:
		//!	Singleton instance for the windows specific debugger module
		static cDebugger_Win* sm_pinstance;
	};
}
#endif	//_CDEBUGGER_WIN_H_