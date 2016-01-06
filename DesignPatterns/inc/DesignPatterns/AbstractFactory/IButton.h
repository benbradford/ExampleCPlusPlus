#pragma once

class IButton
{
public:
	virtual ~IButton(){}
	virtual void Click() = 0;
};