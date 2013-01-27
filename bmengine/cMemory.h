
#ifndef _CMEMORY_H_
#define _CMEMORY_H_

#include "bmplatform.h"
#include "datatypes.h"

//	Utility MACROS
#define BMAlign(_v, _align)		(((size_t)(_v)+(_align)-1)&(~((_align)-1)))
#define BMAlignUp(_v,_align)	(BMAlign((_v),(_align))+(_align))
#define BMAlign16(_v)			BMAlign(_v,16)
#define BMAlign32(_v)			BMAlign(_v,32)
#define BMAlign64(_v)			BMAlign(_v,64)
#define BMAlign128(_v)			BMAlign(_v,128)

namespace bmcore
{
	//	Memory manipulation Utility Functions
	BM_INLINE void* BMMemmove (void* pDest, const void* pSrc, tMemSize iSize)
	{
		return memmove (pDest, pSrc, iSize);
	}

	BM_INLINE void* BMMemcpy (void* pDest, const void* pSrc, tMemSize iSize)
	{
		tByte* pbDest	= (tByte*)pDest;
		tByte* pbSrc	= (tByte*)pSrc;

		if ((pbSrc < pbDest && (pbSrc + iSize) > pbDest) ||
			(pbDest < pbSrc && (pbDest + iSize) > pbSrc))
		{
			//	Memory locations overlap, we should use memmove
			return BMMemmove(pDest, pSrc, iSize);
		}

		return memcpy(pDest, pSrc, iSize);
	}

	BM_INLINE void* BMMemset(void* pSrc, int iChar, tMemSize iNum)
	{
		return memset (pSrc, iChar, iNum);
	}

	BM_INLINE int BMMemcmp (const void* pSrc1, const void* pSrc2, tMemSize iNum)
	{
		return memcmp (pSrc1, pSrc2, iNum);
	}

	BM_INLINE void* BMMenchr (void* pSrc, int iChar, tMemSize iNum)
	{
		return memchr (pSrc, iChar, iNum);
	}

	/**
		\struct		cBlockHeader
		\brief		Represents the header for a memory block in the BME memory manager
	*/
	class BM_ALIGN_BEGIN(32) cBlockHeader
	{
	public:
		/**
			cMemory::calcDataOffset

			\brief Calculates the data offset for this header given the passed alignment

			The returned integer value represents the byte offset from the cBlockHeader pointer
			to the data pointer (which will be constructed and provided to the user.  This
			takes into account the header and footer along with the appropriate padding
			to ensure alignment.

			\return The byte offset between the memory manager's header pointer to the user's data pointer
		*/
		tuInt32 calcDataOffset(tuInt32 iAlignment);
	
		tByte			m_bFree;
		tByte			m_bLock;
		tuInt16			_pad16;

		tMemSize		m_size;
		tuInt32			m_dataOffset;
		cBlockHeader*	m_pNext;

	#ifdef BMDEBUG
		tuInt32			m_fileLine;
		tuChar8*		m_fileName;
	#endif

		tuInt32			m_CRC;
	}BM_ALIGN_END(32);

	/**
		\class	cMemory
		\brief	Abstracted Memory management class
	*/
	class BM_ALIGN_BEGIN(32) cMemory
	{
	public:
		cMemory(void* ptr, tMemSize size, tuInt32 align);
		virtual ~cMemory(void);

		void reinitialize(void);
		void createBlock (tBool bFree, cBlockHeader* pHeader, tMemSize total_size);

	protected:
		cMemory(void);

		
	
		//!	Pointer to the first header block within the pool
		cBlockHeader* m_pFirstBlock;

		//!	Alignment standard for this memory manager
		tuInt32		m_alignment;

		//!	Alignment standard for internal structures of the manager
		tMemSize	m_structAlign;

		//!	Resulting size of the block header after alignment with the previous standards
		tMemSize	m_paddedHeadSize;

		//!	Size of the allocation pool
		tMemSize	m_allocatedSize;

		//!	Pointer to the allocated block of memory
		void*		m_pAllocatedBlock;
	}BM_ALIGN_END(32);
}
#endif // _CMEMORY_H_
