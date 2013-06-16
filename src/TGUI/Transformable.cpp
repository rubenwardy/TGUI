/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <TGUI/Defines.hpp>
#include <TGUI/Transformable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Transformable::Transformable() :
    m_Position(0, 0),
    m_TransformNeedUpdate(true),
    m_Transform()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Transformable::~Transformable()
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::setPosition(float x, float y)
    {
        m_Position.x = x;
        m_Position.y = y;

        m_TransformNeedUpdate = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::setPosition(const Vector2f& position)
    {
        setPosition(position.x, position.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Vector2f& Transformable::getPosition() const
    {
        return m_Position;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::move(float offsetX, float offsetY)
    {
        setPosition(m_Position.x + offsetX, m_Position.y + offsetY);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Transformable::move(const Vector2f& offset)
    {
        setPosition(m_Position.x + offset.x, m_Position.y + offset.y);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const sf::Transform& Transformable::getTransform() const
    {
        if (m_TransformNeedUpdate)
        {
            m_Transform = sf::Transform( 1, 0, m_Position.x,
                                         0, 1, m_Position.y,
                                         0.f, 0.f, 1.f);

            m_TransformNeedUpdate = false;
        }

        return m_Transform;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////