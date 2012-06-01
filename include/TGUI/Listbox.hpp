/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
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


#ifndef _TGUI_LISTBOX_INCLUDED_
#define _TGUI_LISTBOX_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API Listbox : public OBJECT, OBJECT_BORDERS
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Listbox();
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Listbox(const Listbox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Listbox();
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Listbox& operator= (const Listbox& right);

        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Creates the listbox.
        // The width and height parameters constain the size before scaling.
        // The ScrollbarPathname is the pathname needed to load the scrollbar. If not provided then there will be no possibility
        // to scroll, thus no items will be added when the listbox is full.
        // The ItemHeight parameter tells what the height of every item in the list will be. The text size will be based on this,
        // but will be a little smaller. If ItemHeight is 0 then it will become a tenth of the height of the listbox.
        //
        // The listbox may resize a little bit. It might be bigger or smaller than the size passed to this function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(unsigned int width,
                  unsigned int height,
                  const std::string scrollbarPathname = "",
                  unsigned int itemHeight = 0);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the size of the listbox. Note that this function will undo all scaling.
        // You are advised to use this function over the setScale function.
        // Note that the listbox has to be loaded correctly before calling this function.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the listbox, unaffected by scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2u getSize() const;
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the listbox, after the scaling transformation.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Vector2f getScaledSize() const;

        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the pathname that was used to load the scrollbar.
        // When no scrollbar was loaded then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedScrollbarPathname();
        

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the colors of the listbox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& backgroundColor         = sf::Color::White,
                          const sf::Color& textColor               = sf::Color::Black,
                          const sf::Color& selectedBackgroundColor = sf::Color(50, 100, 200),
                          const sf::Color& selectedTextColor       = sf::Color::White,
                          const sf::Color& borderColor             = sf::Color::Black);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get the colors that are currently used inside the listbox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor();
        const sf::Color& getTextColor();
        const sf::Color& getSelectedBackgroundColor();
        const sf::Color& getSelectedTextColor();
        const sf::Color& getBorderColor();


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the font of the items. When you don't call this function then the global font will be use.
        // This global font can be changed by calling the setGlobalFont function from Panel.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the font of the items.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getTextFont();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Adds an item to the list.
        //
        // When the text doesn't fit inside the listbox then the last characters are removed when cropText is true. Trying to
        // find the item with the full text later will of course fail. If the text may not be clipped for this reason then you
        // can set cropText to false, but this might cost some speed when drawing (it has to be clipped there every frame).
        // If you do decide to clip the text here than make sure that the scaling to the listbox is already done.
        //
        //
        // Return: - 0 when the listbox is full (m_MaxItems constains the maximum amount, zero means no limit). Note that the
        //           listbox can also be full when no scrollbar was loaded and the text no longer fits inside the listbox.
        //         - The id of the item otherwise (when it was successfully added). You will need this id when removing it from
        //           the listbox (when using a name to remove it you might remove other items that have the same name).
        //           Note that this id is no longer correct when an item is removed. Use it immediately or don't use it at all.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int addItem(const std::string itemName, bool cropText = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // None of the items is selected by default. If you want to select an item then call this function.
        // Note that if you select it by name, the first matching item will be selected.
        //
        // return: true on success
        //         false when the name was not found or the id was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(const std::string itemName);
        bool setSelectedItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes an item from the list with a given id.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes all items from the list with a given name.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeItem(const std::string itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes all items from the list.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the item name of the given id. The string will be empty when the id was too high or when it was 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the id of the first item with the given name. If none of the items matches then the id will be 0.
        // Note that this id is no longer correct when an item is removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemID(const std::string itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the list that constains all the items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<std::string>& getItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the currently selected item.
        // When no item was selected then this function will return an empty string.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getSelectedItem() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get the id of the selected item. Note that this id will become wrong when an item is removed from the listbox.
        // When no item was selected then this function returns 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getSelectedItemID();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the scrollbar of the listbox.
        // Only needed when this wasn't done when creating the listbox or if the scrollbar should be changed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setScrollbar(const std::string scrollbarPathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Removes the scrollbar from the listbox (if there is one). When there are too many items to fit in the listbox then
        // the items will be removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes/Returns the height of one item. This is always a little big greater than the text size.
        // Note that when changing the item height the scale will be taken into account during the calculations. When there is
        // no scrollbar this will be important because the items will be removed when they no longer fit inside the listbox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemHeight(unsigned int itemHeight);
        unsigned int getItemHeight();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes/Returns the height of the text. This is always a little big smaller than the item height.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);
        unsigned int getTextSize();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes/Returns the maximum items that the listbox can contain. If 0 then there is no limit.
        // If no scrollbar was loaded then there is always a limitation because the text can't go outside the listbox.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumItems(unsigned int maximumItems = 0);
        unsigned int getMaximumItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the size of the borders.
        // Note that these borders are scaled together with the listbox!
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(unsigned int leftBorder   = 0,
                        unsigned int topBorder    = 0,
                        unsigned int rightBorder  = 0,
                        unsigned int bottomBorder = 0);
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);
        void leftMousePressed(float x, float y);
        void leftMouseReleased(float x, float y);
        void mouseMoved(float x, float y);
        void mouseNotOnObject();
        void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the listbox on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        // This contains the different items in the listbox
        std::vector<std::string> m_Items;

        // What is the id of the selected item?
        unsigned int m_SelectedItem;

        // The size must be stored
        Vector2u m_Size;
        unsigned int m_ItemHeight;

        unsigned int m_TextSize;

        // This will store the maximum number of items in the listbox (zero by default, meaning that there is no limit)
        unsigned int m_MaxItems;

        // When there are too many items a scrollbar will be shown
        Scrollbar* m_Scroll;
        
        // The pathname of the loaded scrollbar (if there is one)
        std::string m_LoadedScrollbarPathname;

        // These colors are used to draw the listbox
        sf::Color m_BackgroundColor;
        sf::Color m_TextColor;
        sf::Color m_SelectedBackgroundColor;
        sf::Color m_SelectedTextColor;
        sf::Color m_BorderColor;

        // The font used to draw the text
        sf::Font m_TextFont;
        
        // The render texture, used to draw the text on (this allows to display only a part of the text)
        sf::RenderTexture* m_RenderTexture;

        // ComboBox contains a list box internally and it should be able to adjust it.
        friend struct ComboBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_LISTBOX_INCLUDED_
