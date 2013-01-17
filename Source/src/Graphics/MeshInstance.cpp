#include "Graphics/MeshInstance.hpp"

using namespace ic;
using gfx::CMeshInstance;

bool CMeshInstance::LoadMesh(asset::CMesh* pMesh)
{
    if(pMesh) mp_ActiveMesh = pMesh;
    return (pMesh != NULL);
}

bool CMeshInstance::LoadMesh(const std::string& filename)
{
    mp_ActiveMesh = asset::CAssetManager::Create<asset::CMesh>(filename);
    return (mp_ActiveMesh != NULL);
}

bool CMeshInstance::LoadIntoVBO(gfx::CVertexBuffer& VBO)
{
    if(!mp_ActiveMesh) return false;

    m_Dimensions.x = mp_ActiveMesh->GetMeshWidth();
    m_Dimensions.y = mp_ActiveMesh->GetMeshHeight();

    return mp_ActiveMesh->Offload(VBO.GetVertexBufferVec(),
                                  VBO.GetIndexBufferVec());    
}