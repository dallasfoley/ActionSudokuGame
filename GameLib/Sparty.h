/**
 * @file Sparty.h
 * @author rohch
 *
 * Class to describe the Sparty character
 */

#ifndef PROJECT1_GAMELIB_SPARTY_H
#define PROJECT1_GAMELIB_SPARTY_H

#include "Game.h"
#include "Item.h"
#include <wx/graphics.h>
#include <memory>

class DeclarationSparty;

/**
 * Class to describe the Sparty character
 */
class Sparty : public Item {
private:
    /// Character speed in pixels per second
    double mMaxSpeed = 400.00;

    /// The time for an eating cycles in seconds
    const double mEatingTime = 0.5;

    /// Current time remaining in headbutt
    double mHeadbuttCurrent = 0;

    /// The Sparty head image
    std::unique_ptr<wxImage> mHead;

    /// The Sparty head bitmap
    std::unique_ptr<wxBitmap> mHeadBitmap;

    /// The Sparty mouth image
    std::unique_ptr<wxImage> mMouth;

    /// The Sparty mouth bitmap (I couldnt make wxGraphicBitmap work, maybe try again later)
    std::unique_ptr<wxBitmap> mMouthBitmap;

    /// The destination X coordinate
    double mDestinationX;

    /// The destination Y coordinate
    double mDestinationY;

    /// Value to determine which image to draw first
    int front = 2;

    /// mouth pivot point
    wxPoint mMouthPivot;

    /// mouth pivot angle
    double mMouthAngle = 1;

    /// double to determine if Sparty is currently eating
    double mEating = 0;

    /// head pivot form XML
    wxPoint mHeadPivot = wxPoint(GetX(),GetY());

    ///Head angel member variable
    double mHeadAngle = 0;

    ///current game context
    Game * mGame;

    /// count of numbers in Sparty
    int mCount = 0;

public:
    /**
     * Constructor for Sparty
     * @param game Game object
     */
    explicit Sparty(Game *game);

    /**
     * Destructor for Sparty
     */
    ~Sparty();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the Sparty character
     * @param elapsed The time elapsed since the last update
     */
    void Update(double elapsed) override;

    void SetLandingPoint(double x, double y) override;
    /**
     * XML Node and declaration sparty
     * @param node The XML node
     * @param dec The sparty declaration
     */
    Sparty(wxXmlNode * node, DeclarationSparty * dec);

    /**
     * Implement the Sparty character's eating action
     */
    void Eat() override;

    /**
     * Implement the headbutt action
     */
    void Headbutt() override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSparty(this); }

    /**
     * Make hittest not work on sparty
     * @param x The x location
     * @param y The y location
     * @return false
     */
    bool HitTest(double x, double y) override { return false; }

    /**
     * Get the count of numbers in Sparty
     * @return int The count of numbers in Sparty
     */
    int GetCount() override {return mCount;}

    /**
     * Increment the count of numbers in Sparty
     */
    void IncrementCount() override {mCount++;}

    /**
     * Decrement the count of numbers in Sparty
     */
    void DecrementCount() override {mCount--;}

    void SetSpeed(double speedModifier);

    double GetSpeed() const override;

};

#endif //PROJECT1_GAMELIB_SPARTY_H
