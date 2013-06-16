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


#ifndef TGUI_GROUP_HPP
#define TGUI_GROUP_HPP

#include <list>

#include <TGUI/EventManager.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \brief Parent class for objects that store multiple objects.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Group
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group(const Group& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Group();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Group& operator= (const Group& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all objects that are created after calling this function.
        ///
        /// \param filename  Path of the font file to load
        ///
        /// \return True if loading succeeded, false if it failed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setGlobalFont(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the global font.
        ///
        /// This font will be used by all objects that are created after calling this function.
        ///
        /// \param font  Font to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setGlobalFont(const sf::Font& font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the global font.
        ///
        /// This is the font that is used for newly created object by default.
        ///
        /// \return global font
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getGlobalFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds an object to the group.
        ///
        /// \param objectPtr   Pointer to the object you would like to add
        /// \param objectName  If you want to access the object later then you must do this with this name
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(group); // Create a picture and add it to the group
        /// group.remove(pic);             // Remove the picture from the group
        /// group.add(pic);                // Add the picture to the group again
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void add(const SharedObjectPtr<Object>& objectPtr, const sf::String& objectName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a pointer to an earlier created object.
        ///
        /// \param objectName The name that was given to the object when it was added to the group.
        ///
        /// \return Pointer to the earlier created object
        ///
        /// \warning This function will return NULL when an unknown object name was passed.
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(group, "picName");
        /// tgui::Picture::Ptr pic2 = group.get("picName");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SharedObjectPtr<Object> get(const sf::String& objectName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Makes a copy of any existing object and returns the pointer to the new object.
        ///
        /// \param oldObject     A pointer to the old object.
        /// \param newObjectName If you want to access the object later then you must do this with this name
        ///
        /// \return Pointer to the new object
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(group, "picName");
        /// tgui::Picture::Ptr pic2 = group.copy(pic, "picName_2");
        /// tgui::Picture::Ptr pic3 = group.copy(group.get("picName"), "picName_3");
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SharedObjectPtr<Object> copy(const SharedObjectPtr<Object>& oldObject, const sf::String& newObjectName = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads a form from a file.
        ///
        /// The objects will be loaded and added to the group.
        /// Note that even when this function fails, some objects might have been loaded already.
        ///
        /// \param filename  Filename of the object file that is to be loaded
        ///
        /// \return
        ///        - true on success
        ///        - false when the file could not be opened
        ///        - false when the file contains a mistake
        ///        - false when one of the objects couldn't be loaded
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool loadObjectsFromFile(const std::string& filename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of all the objects.
        ///
        /// \return Vector of all object pointers
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector< SharedObjectPtr<Object> >& getObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns a list of the names of all the objects.
        ///
        /// \return Vector of all object names
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String>& getObjectNames();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single object that was added to the group.
        ///
        /// \param object  Pointer to the object to remove
        ///
        /// \see remove(sf::String)
        ///
        /// Usage example:
        /// \code
        /// tgui::Picture::Ptr pic(group, "picName");
        /// tgui::Picture::Ptr pic2(group, "picName2");
        /// group.remove(pic);
        /// group.remove(group.get("picName2"));
        /// \endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(const SharedObjectPtr<Object>& object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes a single object that was added to the group.
        ///
        /// \param object  Pointer to the object to remove
        ///
        /// This function is provided for internal use.
        /// The other remove function will probably be easier to use, but in the end they do exactly the same.
        ///
        /// \see remove(SharedObjectPtr<Object>)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void remove(Object* object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all objects that were added to the group.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void removeAllObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Focuses an object.
        ///
        /// The previously focused object will be unfocused.
        ///
        /// \param object  The object that has to be focused.
        ///
        /// \see unfocusObject
        /// \see unfocusAllObjects
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void focusObject(Object *const object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus an object.
        ///
        /// The next object will be focused.
        ///
        /// \param object  The object that has to be unfocused.
        ///
        /// \see focusObject
        /// \see unfocusAllObjects
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusObject(Object *const object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unfocus all the objects.
        ///
        /// \see focusObject
        /// \see unfocusObject
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unfocusAllObjects();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Uncheck all the radio buttons.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheckRadioButtons();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an object before all other objects.
        ///
        /// \param object  The object that should be moved to the front
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToFront(Object *const object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Places an object behind all other objects.
        ///
        /// \param object  The object that should be moved to the back
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void moveObjectToBack(Object *const object);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is used internally by child object to alert there parent about a callback.
        // If it reaches the window, then the callback can be obtained by calling the getCallback function of the window.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void addChildCallback(Callback& callback) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child objects.
        ///
        /// When a child object tells this object about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this object.
        ///
        /// \param func  Pointer to a free function with a reference to a Callback object as parameter.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void bindGlobalCallback(boost::function<void(const tgui::Callback&)> func);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Bind a function to the callbacks of all child objects.
        ///
        /// When a child object tells this object about the callback then the global callback function(s) will be called.
        /// If no global callback function has been bound then the callback is passed to the parent of this object.
        ///
        /// \param func      Pointer to a member function with a reference to a Callback object as parameter.
        /// \param classPtr  Pointer to the object of the class.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        void bindGlobalCallback(void (T::*func)(const tgui::Callback&), const T* const classPtr)
        {
            m_GlobalCallbackFunctions.push_back(boost::bind(func, classPtr, _1));
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the global callback function(s).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void unbindGlobalCallback();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Used internally to get the size of a group object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getDisplaySize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will call the draw function from all the objects.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void drawObjectGroup(sf::RenderTarget* target, const sf::RenderStates& states = sf::RenderStates::Default) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::vector<sf::String>  m_ObjName;

        sf::Font m_GlobalFont;

        // The internal event manager
        EventManager m_EventManager;

        // Is the group focused? If so, then one of the objects inside the group may be focused
        bool m_GroupFocused;

        // A list that stores all functions that receive callbacks triggered by child objects
        std::list< boost::function<void(const Callback&)> > m_GlobalCallbackFunctions;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_GROUP_HPP
