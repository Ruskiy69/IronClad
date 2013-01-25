/**
 * @file
 *	Entity/RigidBody.hpp - The basic physics-controlled entity in the game world.
 *
 * @author      George Kudrayvtsev (switch1440)
 * @version     1.1.3
 * @copyright   Apache License v2.0
 *  Licensed under the Apache License, Version 2.0 (the "License").			\n
 *  You may not use this file except in compliance with the License.		\n
 *  You may obtain a copy of the License at:
 *  http://www.apache.org/licenses/LICENSE-2.0 								\n
 *  Unless required by applicable law or agreed to in writing, software		\n
 *  distributed under the License is distributed on an "AS IS" BASIS,		\n
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n
 *  See the License for the specific language governing permissions and		\n
 *  limitations under the License.
 *
 * @addtogroup Entity
 * @{
 **/

#ifndef IRON_CLAD__ENTITY__RIGID_BODY_HPP
#define IRON_CLAD__ENTITY__RIGID_BODY_HPP

#include "Entity.hpp"

namespace ic
{
    class IRONCLAD_API CRigidBody : public CEntity
    {
    public:
        CRigidBody() : m_vert(0.f), m_horz(0.f) {}
        ~CRigidBody(){}

        bool LoadFromFile(const char* pmesh_filename,
                          gfx::CVertexBuffer& VBO);

        bool LoadFromFile(const std::string& mesh_filename,
                          gfx::CVertexBuffer& VBO);

        bool LoadFromMesh(asset::CMesh* pMesh, gfx::CVertexBuffer& VBO);

        void Move(const math::vector2_t& Pos);
        void Move(const float x, const float y);

        void Adjust(const math::vector2_t& Rate);
        void Adjust(const float dx, const float dy);

        void AddVForce(const float dy);
        void AddHForce(const float dx);

        void Equalize();

        bool CheckCollision(const CEntity* Other) const;
        bool CheckCollision(const math::rect_t& Other) const;

        void Update();

    private:
        math::rect_t m_CollisionBox;
        float m_vert, m_horz;
    };
}

#endif // IRON_CLAD__ENTITY__RIGID_BODY_HPP

/** @} **/