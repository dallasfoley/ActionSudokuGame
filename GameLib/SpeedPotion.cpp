/**
 * @file SpeedPotion.cpp
 * @author Chirag Solanki
 */

#include "pch.h"
#include "SpeedPotion.h"
#include "Game.h"
#include "Sparty.h"
#include <iostream>
#include "wx/bitmap.h"

using namespace std;

/// The image for the speed potion
const wstring speedPotionImage = L"images/speedpotion.png";

/**
 * Constructor for SpeedPotion
 * @param declaration The declaration for the SpeedPotion
 * @param node The xml node for the SpeedPotion
 * @param game The game object
 */
SpeedPotion::SpeedPotion(DeclarationPotion * declaration, wxXmlNode * node, Game * game) : Item(declaration, node)
{
    mGame=game;
    mImage = make_unique<wxImage>(speedPotionImage, wxBITMAP_TYPE_ANY);
    mBitmap = make_unique<wxBitmap>(*mImage);
}


/**
 * Destructor for SpeedPotion
 */
SpeedPotion::~SpeedPotion()
{
}

/**
 * Draw the SpeedPotion
 * @param graphics The graphics context to draw on
 */
void SpeedPotion::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Item::Draw(graphics);
    double wid = mBitmap->GetWidth();
    double hit = mBitmap->GetHeight();
    graphics->DrawBitmap(*mBitmap,
                         (mX),
                         (mY),
                         wid,
                         hit);
}

/**
 * Update the SpeedPotion
 * @param elapsed The time elapsed since the last update
 */
void SpeedPotion::Update(double elapsed) {
    // Logic for updating the speed potion (dont know if needed)
    // For instance, movement, animation, disappearance after time, etc.
}


/**
 * Handle the interaction with Sparty
 */
void SpeedPotion::AffectSparty() {
    GenerateSpeedModifier(); // Generate a speed modifier
    auto sparty = mGame->GetSparty();
    if (sparty) {
       double newSpeed = sparty->GetSpeed() * mSpeedModifier; // Compute new speed
       sparty->SetSpeed(newSpeed); // Set new speed
    } else {
        std::cerr << "Error: Sparty object not found in game." << std::endl;
    }
}


/**
 * Generate a speed modifier
 */
void SpeedPotion::GenerateSpeedModifier() {
    // Randomly generates a speed modifier for Sparty
    mRNG = mGame->GetRandom();
    std::uniform_real_distribution<> distr(0.5, 3.0); // Range of speed modifier
    mSpeedModifier = distr(mRNG);
}


/**
 * Load the potion from xml file
 * @param node
 */
void SpeedPotion::XmlLoad(wxXmlNode *node)
{
    double x;
    node->GetAttribute(L"col").ToDouble(&x);
    double y;
    node->GetAttribute(L"row").ToDouble(&y);
    SetLocation(x, y);
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void SpeedPotion::Accept(ItemVisitor* visitor) {
    visitor->VisitPotion(this);
}

