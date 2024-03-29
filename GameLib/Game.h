/**
 * @file Game.h
 * @author Jon Price
 *
 * This class is responsible for loading the game, drawing the game, and updating the game
 * It also contains the game loop and keeps track of the game state and level
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "Item.h"
#include "Scoreboard.h"
#include "Declaration.h"
#include "FpsDisplay.h"
#include <Random>

class Sparty;

class XRay;

class Board;

class ItemVisitor;


/**
 * Class to represent the game
 * This class is responsible for loading the game, drawing the game, and updating the game
 * It also contains the game loop and keeps track of the game state and level
 */
class Game {
private:
    /// Enumerating class
    enum class Type {Start, Playing, Incorrect, Correct, Full};
    /// Member variable mType
    Type mType = Type::Start;
    /// Current level member variable
    int mLevel = 1;
    /// Count of numbers on the board
    int mCount = 0;
    /// Window scaling member variable
    double mScale;
    /// X offset member variable
    double mXOffset;
    /// Y offset member variable
    double mYOffset;
    /// Board tile width member variable
    double mTileWidth;
    /// Board tile height member variable
    double mTileHit;
    /// Pixel height member variable
    int mPixelHeight;
    /// Pixel width member variable
    int mPixelWidth;
    /// FPS display
    bool mDisplayFps = false;
    /// The scoreboard or timer
    Scoreboard mScoreboard;
    /// The playing board
    std::shared_ptr<Board> mBoard;
    /// Game items
    std::vector<std::shared_ptr<Item>> mItems;
    /// FPS display boolean
    FpsDisplay mFpsDisplay;
    /// Map for declarations
    std::unordered_map<wxString, std::shared_ptr<Declaration>> mDeclarations;
    /// Tracks game time
    double mGameTimer;
    /// Random number generator
    std::mt19937 mRandom;
    ///   Amount to change y coordinate of a message
    double mMessageAmount = 0;

public:
    /**
     * Sets the fps display to true or false
     */
    void SetDisplayFps() {mDisplayFps = !mDisplayFps;}
    Game();
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);
    void Update(double elapsed);
    void DrawMessage(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Sets the level of the game according to the parameter
     * @param level level to be set to
     */
    void SetLevel(int level) {mLevel = level;}
    std::shared_ptr<Item> XmlItem(wxXmlNode * node);
    void OnLeftDown(wxMouseEvent & event);
    void OnKeyDown(wxKeyEvent & event);
    std::shared_ptr<Item> HitTest(double x, double y);
    void Clear();
    void Restart();
    void NextLevel();
    bool CheckSolved();
    void Load(const wxString &filename);

    /**
     * Get number of declarations in the map
     * @return mDeclarations.size() size of the map
     */
    int GetMapLength() { return mDeclarations.size(); }

    /**
     * Gets the x value of a tile on the board
     * @return mTileWidth width of the tile
     */
    double GetTileWidth() const {return mTileWidth;}

    /**
     * Gets the y value of a tile on the board
     * @return mTileHit height of the tile
     */
    double GetTileHit() const {return mTileHit;}
    void AddItem(std::shared_ptr<Item> item);
    void Solve();
    /**
     * Set the game count
     * @param count numbers on board
     */
    void SetGameCount(int count) {mCount = count;}
    /**
     * Get the game count
     * @return mCount
     */
    int GetGameCount() const {return mCount;}
    /**
     * Get Sparty from the game
     * @return shared pointer to Sparty
     */
    std::shared_ptr<Item> GetSparty() {return mItems.back();}

    /**
     * Get teh random number generator
     * @return pointer to the random number generator
     */
     std::mt19937 &GetRandom() {return mRandom;}

    void DrawImFull(std::shared_ptr<wxGraphicsContext> graphics);
};


#endif //PROJECT1_GAME_H
