/**
 * @file DeclarationNumber.h
 * @author Jon Price
 */

#ifndef PROJECT1_DECLARATIONNUMBER_H
#define PROJECT1_DECLARATIONNUMBER_H

#include "Declaration.h"

/**
 * Base class for number declarations
 */
class DeclarationNumber : public Declaration{
private:
    bool mGiven; ///< whether this declaration is for a given or for a digit
    int mValue; ///< the value corresponding to this digit
public:
    DeclarationNumber(wxXmlNode * node, bool given);
    bool GetGiven() { return mGiven; } ///< @returns mGiven
    int GetValue() { return mValue; } ///< @returns mValue
};


#endif //PROJECT1_DECLARATIONNUMBER_H