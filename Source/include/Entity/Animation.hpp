/**
 * @file
 *	Animation.hpp - A basic abstraction of animation functions like loading
 *	a sprite sheet and switching sprites at certain rates.
 *
 * @author      George Kudrayvtsev (switch1440)
 * @version     1.0
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
 * @addtogroup Graphics
 * @{
 **/

#ifndef IRON_CLAD__ANIMATION_HPP
#define IRON_CLAD__ANIMATION_HPP

#include "Entity.hpp"

namespace ic
{
    /**
     * An animate-able extension of the CEntity class.
     *  This class acts exactly like an entity, but contains the ability
     *  to easily switch between sprites either automatically after a 
     *  certain period of time or manually.
     *  Currently, this is meant exclusively for simple, single-texture
     *  quad meshes, as that makes material binding much easier to 
     *  implement correctly.
     *  Another limitation is that all of the animations in the sprite
     *  sheet must be the exact same size.
     *  
     * @todo    Expand animation abilities to non-quad meshes.
     **/
    class CAnimation : public CEntity
    {
    public:
        CAnimation(){}
        ~CAnimation(){}

        /**
         * Load a custom animation file.
         *  This will load an .icanim file that specifies texture locations
         *  in a sprite sheet and various dimensions for all of them.
         * 
         * @param   std::string     Filename
         * 
         * @return  TRUE on success, FALSE on failure
         * 
         * @warning Loading animations is currently a relatively slow
         *          process that involves a lot of texture manipulation,
         *          so call this sparingly, preferably on load.
         **/
        bool LoadAnimationFromFile(const std::string& filename)
        { 
            asset::CTexture* pTexture = 
                asset::CAssetManager::Create<asset::CTexture>(filename);

            if(!pTexture) return false;
            
            mp_allTextures.push_back(pTexture);
            return true;
        }

        /**
         * Adds a sprite to the animation queue.
         *  This will load a sprite sheet and pull a texture out of the
         *  file at the specified dimensions.
         * 
         * @param   std::string     Sprite sheet filename
         * @param   math::rect_t    Dimenions of needed sprite
         * 
         * @return  TRUE on success, FALSE on failure.
         * 
         * @warning Loading animations is currently a relatively slow
         *          process that involves a lot of texture manipulation,
         *          so call this sparingly, preferably on load.
         **/
        bool AddSprite(const std::string& filename,
                       const math::rect_t& dimensions);
        bool AddSprite(const void* raw_pixels,
                       const math::rect_t& dimensions);

        /**
         * Toggles animation.
         *  A CAnimation with animation disabled acts exactly like a 
         *  CEntity for all intents and purposes. Disabling animation
         *  leaves the currently active texture as the one rendered,
         *  as opposed to the original texture.
         *
         * @param   bool    Enable / Disable animation
         **/
        void EnableAnimation(bool flag);

        /**
         * Sets the rate of animation.
         *  The internal sprites will iterate as this limit is reached.
         *  It is absolutely essential that you call Update() at the end
         *  of each frame in order to track this value properly.
         **/
        void SetAnimationRate(const float delta);

        /**
         * Iterates the current texture to the next one in the queue.
         * @return  TRUE if iterated to next one,
         *          FALSE if looping to beginning.
         **/
        bool NextSprite();

        /**
         * Iterates the current texture to the previous one in the queue.
         * @return  TRUE if iterated to previous one,
         *          FALSE if looping to end.
         **/
        bool PrevSprite();

        /**
         * Updates the current time delta value.
         *  This method will accurately measure time elapsed between 
         *  texture switches and will switch accordingly if necessary.
         **/
        void Update();

        inline asset::CTexture* GetTexture() const
        { return mp_ActiveTexture; }

    private:
        std::vector<asset::CTexture*>   mp_allTextures;
        asset::CTexture*                mp_ActiveTexture;
        float                           m_delay;
        bool                            m_enabled;
    };
}

#endif // IRON_CLAD__ANIMATION_HPP

/** @} **/