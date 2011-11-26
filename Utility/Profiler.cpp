/*
 *  Profiler.cpp
 *  Sandbox
 *
 *  Created by Jack Smith on 11/08/11.
 *  Copyright 2011 JackCorp. All rights reserved.
 *
 */

#include "Profiler.h"
#include "Utilities.h"

#define NodeHasChild(x)			(x != NULL && x->m_nChild		!= MAX_PROFILE_NODES)
#define NodeHasParent(x)		(x != NULL && x->m_nParent		!= MAX_PROFILE_NODES)
#define NodeHasNextSibling(x)	(x != NULL && x->m_nNextSibling != MAX_PROFILE_NODES)
#define NodeHasPrevSibling(x)	(x != NULL && x->m_nPrevSibling != MAX_PROFILE_NODES)

static const SProfileNode SDefaultNode = 
{
	MAX_PROFILE_NODES,
	MAX_PROFILE_NODES,
	MAX_PROFILE_NODES,
	MAX_PROFILE_NODES,
	0.0f,
	0,
	"",
	0.0f,
	0,
	MAX_PROFILE_NODES
};

CProfiler::CProfiler()
:	m_pCurrNode(NULL)
,	m_nNextFreeNode(0)
{
	ClearNodes();
}

void CProfiler::ClearNodes()
{
	for (int i = 0; i < MAX_PROFILE_NODES; ++i)
	{
		m_aNodes[i] = SDefaultNode;
		m_aNodes[i].m_nIndex = i;
	}	
}

void CProfiler::StartFrame()
{
	for (int i = 0; i < m_nNextFreeNode; ++i)
	{
		m_aNodes[i].m_fTotalTime	= 0.0f;
		m_aNodes[i].m_nTotalCalls	= 0;
		m_aNodes[i].m_nRecursionCnt	= 0;
		m_aNodes[i].m_fStartTime	= 0.0f;	
	}
}

void CProfiler::StartProfile(const char* p_szName)
{
	if (m_pCurrNode != NULL)
	{
		if (!IsSameNode(m_pCurrNode, p_szName))
		{
			m_pCurrNode = GetSubNode(m_pCurrNode, p_szName);
		}		
	}
	else 
	{
		//Root node
		m_pCurrNode = &m_aNodes[CreateNewNode(p_szName)];
	}
	
	StartCurrentNode();
}

void CProfiler::StopProfile()
{
	if (EndCurrentNode())
	{
		//Not a recursive function, return to parent (or just set to root if no parents)
		m_pCurrNode = NodeHasParent(m_pCurrNode) ? &m_aNodes[m_pCurrNode->m_nParent] : &m_aNodes[0];
	}
}

void CProfiler::StartCurrentNode()
{
	m_pCurrNode->m_nTotalCalls++;
	if (m_pCurrNode->m_nRecursionCnt++ == 0)
	{
		m_pCurrNode->m_fStartTime = GetTime();
	}
}

bool CProfiler::EndCurrentNode()
{
	if (--m_pCurrNode->m_nRecursionCnt == 0 && 
		m_pCurrNode->m_nTotalCalls != 0)
	{
		m_pCurrNode->m_fTotalTime = GetTime() - m_pCurrNode->m_fStartTime;
	}
	
	return (m_pCurrNode->m_nRecursionCnt == 0);	
}

bool CProfiler::IsSameNode(SProfileNode* p_pNode,
						   const char * p_szName)
{
	return (p_pNode != NULL && strcmp(p_pNode->m_szName, p_szName) == 0);
}

SProfileNode* CProfiler::GetSubNode(SProfileNode* p_pNode,
									const char * p_szName)
{
	//If this node has a child, check it
	if (NodeHasChild(p_pNode))
	{
		SProfileNode* pNextNode = &m_aNodes[p_pNode->m_nChild];
		if (IsSameNode(pNextNode, p_szName))
		{
			//The child node is the one we're looking for
			return pNextNode;
		}
		else
		{
			//Check the childs sibling chain for the node
			while (NodeHasNextSibling(pNextNode))
			{
				pNextNode = &m_aNodes[pNextNode->m_nNextSibling];
				if (IsSameNode(pNextNode, p_szName))
				{
					return pNextNode;
				}
			}
			
			//Not in the sibling chain, add another child
			return CreateNewSibling(pNextNode->m_nIndex, p_szName);
		}
	}
	else
	{
		return CreateNewChild(p_pNode->m_nIndex, p_szName);
	}
}

SProfileNode* CProfiler::CreateNewChild(const TIndexType& p_rnParent,
										const char* p_szName)
{
	SProfileNode* pChild = NULL;
	TIndexType nNewChild = CreateNewNode(p_szName);
	if (nNewChild < MAX_PROFILE_NODES)
	{
		SProfileNode* pParent = &m_aNodes[p_rnParent];
		pParent->m_nChild = nNewChild;
				
		pChild = &m_aNodes[nNewChild];
		pChild->m_nParent = p_rnParent;
	}
	
	return pChild;
}

SProfileNode* CProfiler::CreateNewSibling(const TIndexType& p_rnSibling,
										  const char* p_szName)
{
	SProfileNode* pSibling = NULL;
	TIndexType nNewSibling = CreateNewNode(p_szName);
	if (nNewSibling < MAX_PROFILE_NODES)
	{
		SProfileNode* pPrevSibling = &m_aNodes[p_rnSibling];
		pPrevSibling->m_nNextSibling = nNewSibling;
		
		pSibling = &m_aNodes[nNewSibling];
		pSibling->m_nParent = pPrevSibling->m_nParent;
		pSibling->m_nPrevSibling = p_rnSibling;
	}
	
	return pSibling;	
}

TIndexType CProfiler::CreateNewNode(const char * p_szName)
{
	if (m_nNextFreeNode >= MAX_PROFILE_NODES)
		return MAX_PROFILE_NODES;
	
	SProfileNode* pNewNode = &m_aNodes[m_nNextFreeNode];
	++m_nNextFreeNode;
	
	pNewNode->m_szName = p_szName;
	
	return m_nNextFreeNode-1;
}

//- CProfileNodeIter
CProfileNodeIter* CProfiler::GetIter()
{
	return new CProfileNodeIter(this);
}

void CProfiler::ReleaseIter(CProfileNodeIter* p_pIter)
{
	if (p_pIter != NULL)
	{
		delete p_pIter;
	}
}

CProfileNodeIter::CProfileNodeIter(CProfiler* p_pProfiler)
:	m_nCurrNode(0)
,	m_pProfiler(p_pProfiler)
{}

const SProfileNode* CProfileNodeIter::operator*() const
{
	return GetCurrentNode();
}

SProfileNode* CProfileNodeIter::GetCurrentNode() const
{
	return &(m_pProfiler->m_aNodes[m_nCurrNode]);
}

bool CProfileNodeIter::Next()
{
	SProfileNode* pNode = GetCurrentNode();
	m_nCurrNode = pNode->m_nNextSibling;
	return NodeHasNextSibling(pNode);
}

bool CProfileNodeIter::Prev()
{
	SProfileNode* pNode = GetCurrentNode();
	m_nCurrNode = pNode->m_nPrevSibling;
	return NodeHasPrevSibling(pNode);
}

bool CProfileNodeIter::Down()
{
	SProfileNode* pNode = GetCurrentNode();
	m_nCurrNode = pNode->m_nChild;
	return NodeHasChild(pNode);
}

bool CProfileNodeIter::Up()
{
	SProfileNode* pNode = GetCurrentNode();
	m_nCurrNode = pNode->m_nParent;
	return NodeHasParent(pNode);
}