/**
  * @file Number.h
  * @author Chirag Solanki
  * @author Jon Price
  * The Number class represents an individual digit within the Sudoku game.
 */

# ifndef PROJECT1_NUMBER_H
# define PROJECT1_NUMBER_H

#include "Sparty.h"
#include "Board.h"
#include "Item.h"
#include <utility>


class Number : public Item
{
private:
    int mValue;                                   /// The actual digit mValue ranging from 0 to 8
    bool mIsGiven;                                /// Indicates if this number is a given
    bool mIsInSpartyStomach = false;              /// Indicates if this number is inside sparty's stomach
    bool mIsInContainer;                          /// Indicates if this number is inside a container

public:

    void XmlLoad(wxXmlNode *node) override;

    Number(Game * game, int number, bool given);

    /**
      * Marks the number as being inside Sparty's stomach.
     */
    void EatenBySparty();


    /**
      * Removes the number from Sparty's stomach.
     */
    void RegurgitatedBySparty();

    /**
      * Marks the number as being inside a container.
     */
    void PlaceInContainer();

    /**
      * Removes the number from the container.
     */
    void ReleaseFromContainer();
};

# endif //PROJECT1_NUMBER_H