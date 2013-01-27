#include "cMemory.h"

namespace bmcore
{
	cMemory::cMemory(void)
	{
	}

	cMemory::cMemory(void* ptr, tMemSize size, tuInt32 align)
	{
		m_alignment			= align;
		m_structAlign		= sizeof(tMemSize);
		m_paddedHeadSize	= BMAlign(sizeof(cBlockHeader),sizeof(tMemSize));
		m_pAllocatedBlock	= ptr;
		m_allocatedSize		= size;

		reinitialize();
	}

	void cMemory::reinitialize()
	{
		//	Create a default block spanning the entire pool
		m_pFirstBlock = (cBlockHeader*)m_pAllocatedBlock;

		createBlock(TRUE, m_pFirstBlock, m_allocatedSize);
	}

	void cMemory::createBlock(tBool bFree, cBlockHeader* pHeader, tMemSize total_size)
	{
		pHeader->m_dataOffset = pHeader->calcDataOffset(m_alignment);
	}

	cMemory::~cMemory(void)
	{
	}

	tuInt32 cBlockHeader::calcDataOffset(tuInt32 iAlignment)
	{

	}
}
