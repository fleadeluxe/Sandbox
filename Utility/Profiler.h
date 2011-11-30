/*
 *  Profiler.h
 *  Sandbox
 *
 *  Created by Jack Smith on 11/08/11.
 *  Copyright 2011 . All rights reserved.
 *
 */

#ifndef PROFILER_H_INCLUDED
#define PROFILER_H_INCLUDED

#define MAX_PROFILE_NODES 0xFF

typedef uint8_t TIndexType;

struct SProfileNode
{		
	TIndexType		m_nParent;
	TIndexType		m_nChild;
	TIndexType		m_nNextSibling;
	TIndexType		m_nPrevSibling;
	
	float			m_fTotalTime;
	int				m_nTotalCalls;
	const char*		m_szName;
	
	float			m_fStartTime;
	
	int				m_nRecursionCnt;
	
	int				m_nIndex;
};

class CProfiler;

class CProfileNodeIter
{
public:
	CProfileNodeIter(CProfiler* p_pProfiler);
	
	const SProfileNode* operator*() const;
	
	bool Next();
	bool Prev();
	bool Down();
	bool Up();
	
private:
	
	SProfileNode* GetCurrentNode() const;
	
	TIndexType	m_nCurrNode;
	
	CProfiler* m_pProfiler;
};

class CProfiler
{
public:
	
	CProfiler();
	
	void StartFrame();
	
	void StartProfile(const char* p_szName);
	void StopProfile();
	
	CProfileNodeIter*	GetIter();
	void				ReleaseIter(CProfileNodeIter* p_pIter);
	
private:
	
	void StartCurrentNode();
	bool EndCurrentNode();
	
	void ClearNodes();
	
	bool IsSameNode(SProfileNode* p_pNode,
					const char * p_szName);
	
	SProfileNode* GetSubNode(SProfileNode* p_pNode,
							 const char * p_szName);
	
	SProfileNode* CreateNewChild(const TIndexType& p_rnParent,
								 const char* p_szName);
	SProfileNode* CreateNewSibling(const TIndexType& p_rnSibling,
								   const char* p_szName);
	TIndexType CreateNewNode(const char * p_szName);
	
	friend class CProfileNodeIter;
	
	SProfileNode	m_aNodes[MAX_PROFILE_NODES];
	SProfileNode*	m_pCurrNode;
	TIndexType		m_nNextFreeNode;
};

#endif //PROFILER_H_INCLUDED