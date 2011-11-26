//
//  GraphicsTypes.h
//  Sandbox
//
//  Created by Jack Smith on 26/11/11.
//  Copyright (c) 2011. All rights reserved.
//

#ifndef Sandbox_GraphicsTypes_h
#define Sandbox_GraphicsTypes_h

#include "includes.h"
#include <vector>

struct SRenderBatch
{
    GLuint m_gluVertexBufferId;
    GLuint m_gluIndexBufferId;
    
    uint m_uElements;
};

typedef std::vector<float> TVertices;
typedef std::vector<uint> TIndices;

static void BindRenderData(const TVertices& p_rVerts,
                           const TIndices& p_rIndices,
                           SRenderBatch* p_pBatch)
{
    if (p_rVerts.empty() ||
        p_rIndices.empty() ||
        p_pBatch == NULL)
    {
        return;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, p_pBatch->m_gluVertexBufferId);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*p_rVerts.size(), &p_rVerts[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_pBatch->m_gluIndexBufferId);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)*p_rIndices.size(), &p_rIndices[0], GL_STATIC_DRAW);
    
    p_pBatch->m_uElements = p_rIndices.size();
}

#endif
