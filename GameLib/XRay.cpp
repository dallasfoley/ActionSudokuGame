/**
 * @file XRay.cpp
 * @author Jon Price
 */


#include "pch.h"
#include "XRay.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/// The image for the XRay
const wstring xRayImage = L"images/xray.png";

/**
 * Constructor for XRay
 * @param declaration The declaration for the XRay
 * @param node The node for the XRay
 * @param mGame The game the XRay is in
 */
XRay::XRay(DeclarationXray *declaration, wxXmlNode *node, Game *mGame) : Item(declaration, node)
{
    mImage = make_unique<wxImage>(xRayImage, wxBITMAP_TYPE_ANY);
    mBitmap = make_unique<wxBitmap>(*mImage);
    auto child = node->GetChildren();
    mCapacity = declaration->GetCapacity();
    for (; child; child = child->GetNext())
    {
        auto i = mGame->XmlItem(child);
        mNumbers.push_back(i);
    }
}

/**
 * Destructor for XRay
 */
XRay::~XRay()
{
}

/**
 * Draw the XRay
 * @param graphics The graphics context to draw on
 */
void XRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);
    double wid = mBitmap->GetWidth();
    double hit = mBitmap->GetHeight();
    graphics->DrawBitmap(*mBitmap,
                         (mX),
                         (mY),
                         wid,
                         hit);
    double referenceX = GetX() + 10;
    double referenceY = GetY() + 20;
    for (int i = 0; i < mNumbers.size(); i++)
    {
        if (i % 3 == 0)
        {
            referenceX = GetX() + 10;
            referenceY -= 35;
        }
        // Place items in a grid pattern
        mNumbers[i]->SetLocation(referenceX, referenceY);
        mNumbers[i]->Draw(graphics);
        referenceX += 35;

    }
}


/**
 * Add an item to the XRay
 * @param item The item to add
 */
void XRay::AddItem(std::shared_ptr<Item> item)
{
    mNumbers.push_back(item);
}

/**
 * Remove an item from the XRay
 * @param item The item to remove
 * @return true if the item is removed
 */
bool XRay::RemoveItem(std::shared_ptr<Item> item)
{
    for (int i = 0; i < mNumbers.size(); i++)
    {
        if (mNumbers[i] == item)
        {
            mNumbers.erase(mNumbers.begin() + i);
            return true;
        }
    }
    return false;
}

/**
 * Clears the XRay of all items
 */
void XRay::Clear()
{
    mNumbers.clear();
}

/**
 * Regurgitate item back to the game
 * @param game The game the item is in
 * @param event The key event
 * @param x The x position of the item
 * @param y The y position of the item
 * @param board The board the item is on
 * @return true if the item is regurgitated
 */
bool XRay::Regurgitate(Game * game, wxKeyEvent & event, double x, double y, std::shared_ptr<Board> board)
{
    auto code = event.GetKeyCode();
    code -= 48;
    for(const auto& item : mNumbers)
    {
        if(item->GetValue() == code)
        {
            //Determine if Sparty is on the Board
            if(board->IsOnBoard(x,y, game))
            {

                // Set x and y to whole tile number
                x/= game->GetTileWidth();
                x = (int)x;
                x*= game->GetTileWidth();

                y/= game->GetTileWidth();
                y = (int)y;
                y++;
                y*= game->GetTileWidth();

                auto item2 = game->HitTest(x + game->GetTileWidth()/2, y -game->GetTileHit()/2);
                if(item2->GetValue() < 9)
                    return false;
                game->SetGameCount(game->GetGameCount() + 1);
            }
            item->SetLocation(x, y);
            game->AddItem(item);
            RemoveItem(item);
            return true;
        }
    }
    return false;
}