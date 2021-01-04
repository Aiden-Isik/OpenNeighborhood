#pragma once

#include <XBDM.h>

#include "Elements/Element.h"

class Drive : public Element
{
public:
	Drive(const XBDM::Drive& data);

	virtual void OnRender() override;
private:
	XBDM::Drive m_Data;
};
