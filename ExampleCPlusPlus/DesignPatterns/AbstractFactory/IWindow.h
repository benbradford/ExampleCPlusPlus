#pragma once

class IWindow
{
public:
	virtual ~IWindow(){}
	virtual void Maximise() = 0;
	virtual void Minimise() = 0;
};