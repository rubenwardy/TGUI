/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_LIST_BOX_HPP
#define TGUI_LIST_BOX_HPP


#include <TGUI/Widget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class Scrollbar;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ListBox : public Widget, public WidgetBorders
    {
      public:

        typedef SharedWidgetPtr<ListBox> Ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Copy constructor
        ///
        /// \param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox(const ListBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Overload of assignment operator
        ///
        /// \param right  Instance to assign
        ///
        /// \return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListBox& operator= (const ListBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget by calling the copy constructor.
        // This function calls new and if you use this function then you are responsible for calling delete.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ListBox* clone();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Loads the widget.
        ///
        /// \param configFileFilename  Filename of the config file.
        ///
        /// \throw Exception when the config file couldn't be opened.
        /// \throw Exception when the config file didn't contain a "ListBox" section with the needed information.
        /// \throw Exception when one of the images, described in the config file, couldn't be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::string& configFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the filename of the config file that was used to load the widget.
        ///
        /// \return Filename of loaded config file.
        ///         Empty string when no config file was loaded yet.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getLoadedConfigFile() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the list box.
        ///
        /// \param width   The new width of the list box
        /// \param height  The new height of the list box
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the size of the list box
        ///
        /// The size returned by this function does not include the borders.
        ///
        /// \return Size of the list box
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the full size of the list box
        ///
        /// The size returned by this function includes the borders.
        ///
        /// \return Full size of the list box
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the colors used in the list box.
        ///
        /// \param backgroundColor          The color of the background of the list box
        /// \param textColor                The color of the text
        /// \param selectedBackgroundColor  The color of the background of the selected item
        /// \param selectedTextColor        The color of the text when it is selected
        /// \param borderColor              The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& backgroundColor         = sf::Color::White,
                          const sf::Color& textColor               = sf::Color::Black,
                          const sf::Color& selectedBackgroundColor = sf::Color(50, 100, 200),
                          const sf::Color& selectedTextColor       = sf::Color::White,
                          const sf::Color& borderColor             = sf::Color::Black);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color that will be used inside the list box.
        ///
        /// \param backgroundColor  The color of the background of the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color that will be used inside the list box.
        ///
        /// \param textColor  The color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the background color of the selected text that will be used inside the list box.
        ///
        /// \param selectedBackgroundColor  The color of the background of the selected item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedBackgroundColor(const sf::Color& selectedBackgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the text color of the selected text that will be used inside the list box.
        ///
        /// \param selectedTextColor  The color of the text when it is selected
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedTextColor(const sf::Color& selectedTextColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Set the border color text that will be used inside the list box.
        ///
        /// \param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color that is currently being used inside the list box.
        ///
        /// \return The color of the background of the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color that is currently being used inside the list box.
        ///
        /// \return The color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the background color of the selected text that is currently being used inside the list box.
        ///
        /// \return The color of the background of the selected item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedBackgroundColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the text color of the selected text that is currently being used inside the list box.
        ///
        /// \return The color of the text when it is selected
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the border color that is currently being used inside the list box.
        ///
        /// \return The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBorderColor() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the font of the items.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// \param font  The new font.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the font of the items.
        ///
        /// \return  Pointer to the font that is currently being used.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font* getTextFont() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Adds an item to the list.
        ///
        /// \param itemName  The name of the item you want to add (this is the text that will be displayed inside the list box)
        ///
        /// \return
        ///         -  The index of the item when it was successfully added.
        ///         -  -1 when the list box is full (you have set a maximum item limit and you are trying to add more items)
        ///         -  -1 when there is no scrollbar and you try to have more items than fit inside the list box
        ///
        /// \warning The index returned by this function is no longer correct when an item is removed.
        ///
        /// \see setMaximumItems
        /// \see setScrollbar
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int addItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects an item in the list box.
        ///
        /// When adding items to the list box with the addItem function, none of them will be selected.
        /// If you want a default item selected then you can use this function to select it.
        /// The first item that matches the name will be selected.
        ///
        /// \param itemName  The item you want to select
        ///
        /// \return
        ///         - true on success
        ///         - false when none of the items matches the name
        ///
        /// \see setSelectedItem(unsigned int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Selects an item in the list box.
        ///
        /// When adding items to the list box with the addItem function, none of them will be selected.
        /// If you want a default item selected then you can use this function to select it.
        /// If the index is -1 then the \a deselectItem function will be called.
        ///
        /// \param index  The index of the item
        ///
        /// \return
        ///         - true on success
        ///         - false when the index was too high
        ///
        /// \see setSelectedItem(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Deselects the selected item.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectItem();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes an item from the list with a given index.
        ///
        /// \param index  The index of the item to remove
        ///
        /// \return
        ///        - true when the item was removed
        ///        - false when the index was too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItem(unsigned int index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the first item from the list with the given name.
        ///
        /// \param itemName  The item to remove
        ///
        /// \return
        ///        - true when the item was removed
        ///        - false when the name didn't match any item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes all items from the list.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the item name of the item with the given index.
        ///
        /// \param index  The index of the item
        ///
        /// \return The requested item.
        ///         The string will be empty when the index was too high.
        ///
        /// \see getItemIndex
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getItem(unsigned int index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the index of the first item with the given name.
        ///
        /// \param itemName  The name of the item
        ///
        /// \return The index of the item that matches the name.
        ///         If none of the items matches then the returned index will be -1.
        ///
        /// \warning This index may become wrong when an item is removed from the list.
        ///
        /// \see getItem
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getItemIndex(const sf::String& itemName) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the list of all the items.
        ///
        /// \return The vector of strings
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String>& getItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the currently selected item.
        ///
        /// \return The selected item.
        ///         When no item was selected then this function will return an empty string.
        ///
        /// \see getSelectedItemIndex
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelectedItem() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Get the index of the selected item.
        ///
        /// \return The index of the selected item
        ///         When no item was selected then this function returns -1.
        ///
        /// \warning This index may become wrong when an item is removed from the list.
        ///
        /// \see getSelectedItem
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedItemIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the scrollbar of the list box.
        ///
        /// \param scrollbarConfigFileFilename  Filename of the config file.
        ///                                     The config file must contain a Scrollbar section with the needed information.
        ///
        /// \return
        ///        - true when the scrollbar was successfully loaded
        ///        - false when the loading of the scrollbar failed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setScrollbar(const std::string& scrollbarConfigFileFilename);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Removes the scrollbar from the list box.
        ///
        /// When there are too many items to fit in the list box then the items will be removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the height of the items in the list box.
        ///
        /// \param itemHeight  The size of a single item in the list
        ///
        /// \remarks
        ///         - This size is always a little big greater than the text size.
        ///         - When there is no scrollbar then the items will be removed when they no longer fit inside the list box.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemHeight(unsigned int itemHeight);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the height of the items in the list box.
        ///
        /// \return The item height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the maximum items that the list box can contain.
        ///
        /// \param maximumItems  The maximum items inside the list box.
        ///                      When the maximum is set to 0 then the limit will be disabled.
        ///
        /// If no scrollbar was loaded then there is always a limitation because there will be a limited space for the items.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumItems(unsigned int maximumItems = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Returns the maximum items that the list box can contain.
        ///
        /// \return The maximum items inside the list box.
        ///         If the function returns 0 then there is no limit.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumItems() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the size of the borders.
        ///
        /// \param leftBorder    The width of the left border
        /// \param topBorder     The height of the top border
        /// \param rightBorder   The width of the right border
        /// \param bottomBorder  The height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(float leftBorder   = 0,
                                float topBorder    = 0,
                                float rightBorder  = 0,
                                float bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \brief Changes the transparency of the widget.
        ///
        /// \param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(float x, float y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNotOnWidget();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to set properties on the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // This function is a (slow) way to get properties of the widget, no matter what type it is.
        // When the requested property doesn't exist in the widget then the functions will return false.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void getProperty(std::string property, std::string& value) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \internal
        // Returns a list of all properties that can be used in setProperty and getProperty.
        // The second value in the pair is the type of the property (e.g. int, uint, string, ...).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::list< std::pair<std::string, std::string> > getPropertyList() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Defines specific triggers to ListBox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum ListBoxCallbacks
        {
            ItemSelected = WidgetCallbacksCount * 1,            ///< A new item was selected
            AllListBoxCallbacks = WidgetCallbacksCount * 2 - 1, ///< All triggers defined in ListBox and its base classes
            ListBoxCallbacksCount = WidgetCallbacksCount * 2
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        std::string m_loadedConfigFile;

        // This contains the different items in the list box
        std::vector<sf::String> m_items;

        // What is the index of the selected item?
        int m_selectedItem;

        // The size must be stored
        sf::Vector2u m_size;
        unsigned int m_itemHeight;
        unsigned int m_textSize;

        // This will store the maximum number of items in the list box (zero by default, meaning that there is no limit)
        unsigned int m_maxItems;

        // When there are too many items a scrollbar will be shown
        Scrollbar* m_scroll;

        // These colors are used to draw the list box
        sf::Color m_backgroundColor;
        sf::Color m_textColor;
        sf::Color m_selectedBackgroundColor;
        sf::Color m_selectedTextColor;
        sf::Color m_borderColor;

        // The font used to draw the text
        const sf::Font* m_textFont;

        // ComboBox contains a list box internally and it should be able to adjust it.
        friend class ComboBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_LIST_BOX_HPP
