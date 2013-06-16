/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2013 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_CLICKABLE_OBJECT_HPP
#define TGUI_CLICKABLE_OBJECT_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ClickableObject : public Object
    {
      public:

        typedef SharedObjectPtr<ClickableObject> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ClickableObject();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ClickableObject(const ClickableObject& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ClickableObject();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ClickableObject& operator= (const ClickableObject& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the object by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ClickableObject* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the object.
        ///
        /// \param width   The new width of the object
        /// \param height  The new height of the object
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(float width, float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the object.
        ///
        /// \return Size of the object
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Used to communicate with EventManager.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnObject(float x, float y);
        virtual void leftMousePressed(float x, float y);
        virtual void leftMouseReleased(float x, float y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function draws nothing.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        enum ClickableObjectCallbacks
        {
            LeftMousePressed              = ObjectCallbacksCount * 1,
            LeftMouseReleased             = ObjectCallbacksCount * 2,
            LeftMouseClicked              = ObjectCallbacksCount * 4,
            AllClickableObjectCallbacks   = ObjectCallbacksCount * 8 - 1,
            ClickableObjectCallbacksCount = ObjectCallbacksCount * 8
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        // The size of the object
        Vector2f  m_Size;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CLICKABLE_OBJECT_HPP
