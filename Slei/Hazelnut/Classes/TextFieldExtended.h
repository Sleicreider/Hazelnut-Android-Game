#ifndef __TEXT_FIELD_EXTENDED_H__
#define __TEXT_FIELD_EXTENDED_H__

///include cocos to the new class
#include "cocos2d.h"
#include "ui/UILayout.h"
#include "ui/UITextField.h"

class TextFieldExtended : public cocos2d::Node
{
public:
	TextFieldExtended();
	~TextFieldExtended();

	static TextFieldExtended* create(const std::string &placeholder, const std::string &fontName, int fontSize, cocos2d::Vec2 position, float scaleFactor);

	virtual bool init();

	void setContainerPanel(cocos2d::ui::Layout* panel);
	void setTextField(cocos2d::ui::TextField* textField);

	std::string GetTextFieldValue();
protected:
	cocos2d::ui::Layout * _containerPanel;
	cocos2d::ui::TextField * _textField;

};


#endif // __TEXT_FIELD_EXTENDED_H__