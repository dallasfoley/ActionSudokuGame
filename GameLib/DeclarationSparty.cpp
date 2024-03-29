/**
 * @file DeclarationSparty.cpp
 * @author Jon Price
 */

#include "pch.h"
#include "Declaration.h"
#include "Sparty.h"
#include "DeclarationSparty.h"

/**
 * Handle base sparty declarations
 * @param node wxXmlNode
 */
DeclarationSparty::DeclarationSparty(wxXmlNode * node) : Declaration(node,  L"images/" + node->GetAttribute(L"image1", L"sparty-1.png"))
{
    node->GetAttribute(L"head-pivot-angle", L"0").ToDouble(&mHeadPivotAngle);
    node->GetAttribute(L"head-pivot-x", "0").ToDouble(&mHeadPivotX);
    node->GetAttribute(L"head-pivot-y", "0").ToDouble(&mHeadPivotY);
    node->GetAttribute(L"mouth-pivot-angle", L"0").ToDouble(&mMouthPivotAngle);
    node->GetAttribute(L"mouth-pivot-x", L"0").ToDouble(&mMouthPivotX);
    node->GetAttribute(L"mouth-pivot-y", L"0").ToDouble(&mMouthPivotY);
    node->GetAttribute(L"target-x", L"0").ToDouble(&mTargetX);
    node->GetAttribute(L"target-y", L"0").ToDouble(&mTargetY);
    mHeadImage = L"images/" + node->GetAttribute(L"image1", L"sparty-1.png");
    mJawImage = L"images/" + node->GetAttribute(L"image2", L"sparty-2.png");
}

/**
 * Creates shared pointer for declaration
 * @param node wxXmlNode
 * @param game game construct
 * @return shared pointer to sparty
 */
std::shared_ptr<Item> DeclarationSparty::Create(wxXmlNode * node, Game * game)
{
    return std::make_shared<Sparty>(node, this);
}