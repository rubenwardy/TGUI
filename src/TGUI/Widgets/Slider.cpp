/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Widgets/Slider.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    static std::map<std::string, ObjectConverter> defaultRendererValues =
            {
                {"borders", Borders{2}},
                {"bordercolor", Color{60, 60, 60}},
                {"bordercolorhover", sf::Color::Black},
                {"trackcolor", Color{245, 245, 245}},
                {"trackcolorhover", Color{255, 255, 255}},
                {"thumbcolor", Color{245, 245, 245}},
                {"thumbcolorhover", Color{255, 255, 255}}
            };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Slider::Slider()
    {
        m_type = "Slider";

        m_draggableWidget = true;

        m_renderer = aurora::makeCopied<SliderRenderer>();
        setRenderer(RendererData::create(defaultRendererValues));

        setSize(200, 16);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Slider::Ptr Slider::create(int minimum, int maximum)
    {
        auto slider = std::make_shared<Slider>();

        slider->setMinimum(minimum);
        slider->setMaximum(maximum);

        return slider;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Slider::Ptr Slider::copy(Slider::ConstPtr slider)
    {
        if (slider)
            return std::static_pointer_cast<Slider>(slider->clone());
        else
            return nullptr;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::setSize(const Layout2d& size)
    {
        Widget::setSize(size);

        m_bordersCached.updateParentSize(getSize());

        if (getSize().x < getSize().y)
            m_verticalScroll = true;
        else
            m_verticalScroll = false;

        if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
        {
            float scaleFactor;
            if (m_verticalImage == m_verticalScroll)
            {
                m_spriteTrack.setSize(getInnerSize());
                m_spriteTrackHover.setSize(getInnerSize());

                if (m_verticalScroll)
                    scaleFactor = getInnerSize().x / m_spriteTrack.getTexture().getImageSize().x;
                else
                    scaleFactor = getInnerSize().y / m_spriteTrack.getTexture().getImageSize().y;
            }
            else // The image is rotated
            {
                m_spriteTrack.setSize({getInnerSize().y, getInnerSize().x});
                m_spriteTrackHover.setSize({getInnerSize().y, getInnerSize().x});

                if (m_verticalScroll)
                    scaleFactor = getInnerSize().x / m_spriteTrack.getTexture().getImageSize().y;
                else
                    scaleFactor = getInnerSize().y / m_spriteTrack.getTexture().getImageSize().x;
            }

            m_thumb.width = scaleFactor * m_spriteThumb.getTexture().getImageSize().x;
            m_thumb.height = scaleFactor * m_spriteThumb.getTexture().getImageSize().y;

            m_spriteThumb.setSize({m_thumb.width, m_thumb.height});
            m_spriteThumbHover.setSize({m_thumb.width, m_thumb.height});

            // Apply the rotation now that the size has been set
            if (m_verticalScroll != m_verticalImage)
            {
                m_spriteTrack.setRotation(-90);
                m_spriteTrackHover.setRotation(-90);
                m_spriteThumb.setRotation(-90);
                m_spriteThumbHover.setRotation(-90);
            }
            else
            {
                m_spriteTrack.setRotation(0);
                m_spriteTrackHover.setRotation(0);
                m_spriteThumb.setRotation(0);
                m_spriteThumbHover.setRotation(0);
            }
        }
        else // There are no textures
        {
            if (m_verticalScroll)
            {
                m_thumb.width = getSize().x * 1.6f;
                m_thumb.height = m_thumb.width / 2.0f;
            }
            else
            {
                m_thumb.height = getSize().y * 1.6f;
                m_thumb.width = m_thumb.height / 2.0f;
            }
        }

        updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f Slider::getFullSize() const
    {
        if (m_verticalScroll)
            return {std::max(getSize().x, m_thumb.width), getSize().y + m_thumb.height};
        else
            return {getSize().x + m_thumb.width, std::max(getSize().y, m_thumb.height)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f Slider::getWidgetOffset() const
    {
        if (m_verticalScroll)
            return {std::min(0.f, getSize().x - m_thumb.width), -m_thumb.height / 2.f};
        else
            return {-m_thumb.width / 2.f, std::min(0.f, getSize().y - m_thumb.height)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::setMinimum(int minimum)
    {
        // Set the new minimum
        m_minimum = minimum;

        // The maximum can't be below the minimum
        if (m_maximum < m_minimum)
            m_maximum = m_minimum;

        // When the value is below the minimum then adjust it
        if (m_value < m_minimum)
            setValue(m_minimum);

        updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Slider::getMinimum() const
    {
        return m_minimum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::setMaximum(int maximum)
    {
        // Set the new maximum
        m_maximum = maximum;

        // The minimum can't be below the maximum
        if (m_minimum > m_maximum)
            setMinimum(m_maximum);

        // When the value is above the maximum then adjust it
        if (m_value > m_maximum)
            setValue(m_maximum);

        updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Slider::getMaximum() const
    {
        return m_maximum;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::setValue(int value)
    {
        // When the value is below the minimum or above the maximum then adjust it
        if (value < m_minimum)
            value = m_minimum;
        else if (value > m_maximum)
            value = m_maximum;

        if (m_value != value)
        {
            m_value = value;

            onValueChange.emit(this, m_value);

            updateThumbPosition();
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int Slider::getValue() const
    {
        return m_value;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Slider::mouseOnWidget(sf::Vector2f pos) const
    {
        pos -= getPosition();

        // Check if the mouse is on top of the thumb
        if (sf::FloatRect(m_thumb.left, m_thumb.top, m_thumb.width, m_thumb.height).contains(pos))
            return true;

        // Check if the mouse is on top of the track
        if (sf::FloatRect{0, 0, getSize().x, getSize().y}.contains(pos))
            return true;

        return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::leftMousePressed(sf::Vector2f pos)
    {
        m_mouseDown = true;

        // Refresh the value
        mouseMoved(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::leftMouseReleased(sf::Vector2f)
    {
        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPosition();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::mouseMoved(sf::Vector2f pos)
    {
        pos -= getPosition();

        if (!m_mouseHover)
            mouseEnteredWidget();

        // Check if the mouse button is down
        if (m_mouseDown)
        {
            // Check in which direction the slider goes
            if (m_verticalScroll)
            {
                // Check if the click occurred on the track
                if (!m_mouseDownOnThumb)
                {
                    m_mouseDownOnThumb = true;
                    m_mouseDownOnThumbPos.x = pos.x - m_thumb.left;
                    m_mouseDownOnThumbPos.y = m_thumb.height / 2.0f;
                }

                // Set the new value
                if (pos.y - m_mouseDownOnThumbPos.y + (m_thumb.height / 2.0f) > 0)
                    setValue(static_cast<int>((((pos.y + (m_thumb.height / 2.0f) - m_mouseDownOnThumbPos.y) / getSize().y) * (m_maximum - m_minimum)) + m_minimum + 0.5f));
                else
                    setValue(m_minimum);

                // Set the thumb position for smooth scrolling
                float thumbTop = pos.y - m_mouseDownOnThumbPos.y;
                if ((thumbTop + (m_thumb.height / 2.0f) > 0) && (thumbTop + (m_thumb.height / 2.0f) < getSize().y))
                    m_thumb.top = thumbTop;
                else
                    m_thumb.top = (getSize().y / (m_maximum - m_minimum) * (m_value - m_minimum)) - (m_thumb.height / 2.0f);
            }
            else // the slider lies horizontal
            {
                // Check if the click occurred on the track
                if (!m_mouseDownOnThumb)
                {
                    m_mouseDownOnThumb = true;
                    m_mouseDownOnThumbPos.x = m_thumb.width / 2.0f;
                    m_mouseDownOnThumbPos.y = pos.y - m_thumb.top;
                }

                // Set the new value
                if (pos.x - m_mouseDownOnThumbPos.x + (m_thumb.width / 2.0f) > 0)
                    setValue(static_cast<int>((((pos.x + (m_thumb.width / 2.0f) - m_mouseDownOnThumbPos.x) / getSize().x) * (m_maximum - m_minimum)) + m_minimum + 0.5f));
                else
                    setValue(m_minimum);

                // Set the thumb position for smooth scrolling
                float thumbLeft = pos.x - m_mouseDownOnThumbPos.x;
                if ((thumbLeft + (m_thumb.width / 2.0f) > 0) && (thumbLeft + (m_thumb.width / 2.0f) < getSize().x))
                    m_thumb.left = thumbLeft;
                else
                    m_thumb.left = (getSize().x / (m_maximum - m_minimum) * (m_value - m_minimum)) - (m_thumb.width / 2.0f);
            }
        }
        else // Normal mouse move
        {
            // Set some variables so that when the mouse goes down we know whether it is on the track or not
            if (sf::FloatRect(m_thumb.left, m_thumb.top, m_thumb.width, m_thumb.height).contains(pos))
            {
                m_mouseDownOnThumb = true;
                m_mouseDownOnThumbPos.x = pos.x - m_thumb.left;
                m_mouseDownOnThumbPos.y = pos.y - m_thumb.top;
            }
            else // The mouse is not on top of the thumb
                m_mouseDownOnThumb = false;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::mouseWheelScrolled(float delta, sf::Vector2f)
    {
        if (m_value - delta < m_minimum)
            setValue(m_minimum);
        else
            setValue(static_cast<int>(m_value - delta));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::widgetFocused()
    {
        // A slider can't be focused (yet)
        unfocus();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::mouseNoLongerDown()
    {
        // The thumb might have been dragged between two values
        if (m_mouseDown)
            updateThumbPosition();

        Widget::mouseNoLongerDown();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Signal& Slider::getSignal(std::string&& signalName)
    {
        if (signalName == toLower(onValueChange.getName()))
            return onValueChange;
        else
            return Widget::getSignal(std::move(signalName));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::rendererChanged(const std::string& property)
    {
        if (property == "borders")
        {
            m_bordersCached = getRenderer()->getBorders();
            setSize(m_size);
        }
        else if (property == "texturetrack")
        {
            m_spriteTrack.setTexture(getRenderer()->getTextureTrack());

            if (m_spriteTrack.getTexture().getImageSize().x < m_spriteTrack.getTexture().getImageSize().y)
                m_verticalImage = true;
            else
                m_verticalImage = false;

            setSize(m_size);
        }
        else if (property == "texturetrackhover")
        {
            m_spriteTrackHover.setTexture(getRenderer()->getTextureTrackHover());
        }
        else if (property == "texturethumb")
        {
            m_spriteThumb.setTexture(getRenderer()->getTextureThumb());
            setSize(m_size);
        }
        else if (property == "texturethumbhover")
        {
            m_spriteThumbHover.setTexture(getRenderer()->getTextureThumbHover());
        }
        else if (property == "trackcolor")
        {
            m_trackColorCached = getRenderer()->getTrackColor();
        }
        else if (property == "trackcolorhover")
        {
            m_trackColorHoverCached = getRenderer()->getTrackColorHover();
        }
        else if (property == "thumbcolor")
        {
            m_thumbColorCached = getRenderer()->getThumbColor();
        }
        else if (property == "thumbcolorhover")
        {
            m_thumbColorHoverCached = getRenderer()->getThumbColorHover();
        }
        else if (property == "bordercolor")
        {
            m_borderColorCached = getRenderer()->getBorderColor();
        }
        else if (property == "bordercolorhover")
        {
            m_borderColorHoverCached = getRenderer()->getBorderColorHover();
        }
        else if (property == "opacity")
        {
            Widget::rendererChanged(property);

            m_spriteTrack.setOpacity(m_opacityCached);
            m_spriteTrackHover.setOpacity(m_opacityCached);
            m_spriteThumb.setOpacity(m_opacityCached);
            m_spriteThumbHover.setOpacity(m_opacityCached);
        }
        else
            Widget::rendererChanged(property);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f Slider::getInnerSize() const
    {
        return {getSize().x - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                getSize().y - m_bordersCached.getTop() - m_bordersCached.getBottom()};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::updateThumbPosition()
    {
        if (m_verticalScroll)
        {
            m_thumb.left = (getSize().x - m_thumb.width) / 2.0f;
            m_thumb.top = (getSize().y / (m_maximum - m_minimum) * (m_value - m_minimum)) - (m_thumb.height / 2.0f);
        }
        else
        {
            m_thumb.left = (getSize().x / (m_maximum - m_minimum) * (m_value - m_minimum)) - (m_thumb.width / 2.0f);
            m_thumb.top = (getSize().y - m_thumb.height) / 2.0f;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform.translate(getPosition());

        // Draw the borders around the track
        if (m_bordersCached != Borders{0})
        {
            if (m_mouseHover && m_borderColorHoverCached.isSet())
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorHoverCached);
            else
                drawBorders(target, states, m_bordersCached, getSize(), m_borderColorCached);

            states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
        }

        // Draw the track
        if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
        {
            if (m_mouseHover && m_spriteTrackHover.isSet())
                m_spriteTrackHover.draw(target, states);
            else
                m_spriteTrack.draw(target, states);
        }
        else // There are no textures
        {
            if (m_mouseHover && m_trackColorHoverCached.isSet())
                drawRectangleShape(target, states, getInnerSize(), m_trackColorHoverCached);
            else
                drawRectangleShape(target, states, getInnerSize(), m_trackColorCached);
        }

        states.transform.translate({-m_bordersCached.getLeft() + m_thumb.left, -m_bordersCached.getTop() + m_thumb.top});

        // Draw the borders around the thumb
        if (m_bordersCached != Borders{0})
        {
            if (m_mouseHover && m_borderColorHoverCached.isSet())
                drawBorders(target, states, m_bordersCached, {m_thumb.width, m_thumb.height}, m_borderColorHoverCached);
            else
                drawBorders(target, states, m_bordersCached, {m_thumb.width, m_thumb.height}, m_borderColorCached);

            states.transform.translate({m_bordersCached.getLeft(), m_bordersCached.getTop()});
        }

        // Draw the thumb
        if (m_spriteTrack.isSet() && m_spriteThumb.isSet())
        {
            if (m_mouseHover && m_spriteThumbHover.isSet())
                m_spriteThumbHover.draw(target, states);
            else
                m_spriteThumb.draw(target, states);
        }
        else // There are no textures
        {
            const sf::Vector2f thumbInnerSize = {m_thumb.width - m_bordersCached.getLeft() - m_bordersCached.getRight(),
                                                 m_thumb.height - m_bordersCached.getTop() - m_bordersCached.getBottom()};

            if (m_mouseHover && m_thumbColorHoverCached.isSet())
                drawRectangleShape(target, states, thumbInnerSize, m_thumbColorHoverCached);
            else
                drawRectangleShape(target, states, thumbInnerSize, m_thumbColorCached);
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
