#pragma once
#include "DisplayableObject.h"

class Ground :
	public DisplayableObject
{
public:
	Ground();
	~Ground();

	virtual void Display() override;
	void Update(const double& deltaTime);

private:

	float size = 1000.f;
};

