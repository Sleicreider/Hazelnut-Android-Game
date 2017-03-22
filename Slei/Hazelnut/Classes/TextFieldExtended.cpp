#include "TextFieldExtended.h"
#include "DataHandler.h"
#include "FUtil.h"

USING_NS_CC;

TextFieldExtended::TextFieldExtended()
{
}


TextFieldExtended::~TextFieldExtended()
{
}

bool TextFieldExtended::init()
{
	// add the label as a child to this layer
	_containerPanel->addChild(_textField);
	this->addChild(_containerPanel);
	return true;
}

TextFieldExtended * TextFieldExtended::create(const std::string &placeholder, const std::string &fontName, int fontSize, Vec2 position, float scaleFactor)
{
	TextFieldExtended *pRet = new (std::nothrow) TextFieldExtended();
	ui::Layout *pRetLayout = ui::Layout::create();
	ui::TextField *pRetTextField = ui::TextField::create(placeholder, fontName, fontSize);

	pRetLayout->setPosition(position);
	pRetLayout->setAnchorPoint(Vec2(0.5, 0.5));
	pRetLayout->setBackGroundImage(DataHandler::TEXTURE_COLLECT_GAME_TEXT_FIELD);
	pRetLayout->setScale(scaleFactor);

	pRetTextField->ignoreContentAdaptWithSize(true);
	pRetTextField->setAnchorPoint(Vec2(0.5, 0.5));
	pRetTextField->setTextColor(Color4B::BLACK);
	pRetTextField->setPosition(Vec2(pRetLayout->getContentSize().width / 2.0f, pRetLayout->getContentSize().height / 2.0f));

	pRet->setContainerPanel(pRetLayout);
	pRet->setTextField(pRetTextField);

	if (pRet && pRet->init() && pRetLayout && pRetTextField)
	{
		
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet); 

	return nullptr;
}

void TextFieldExtended::setContainerPanel(cocos2d::ui::Layout* panel)
{
	_containerPanel = panel;
}

void TextFieldExtended::setTextField(cocos2d::ui::TextField* textField)
{
	_textField = textField;
}

std::string TextFieldExtended::GetTextFieldValue()
{
	return _textField->getString();
}