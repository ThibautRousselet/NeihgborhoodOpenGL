#pragma once
#include "Model.h"

class SkyBox : public Model 
{
public:
	SkyBox(Shader shad, Texture text);
	SkyBox();
	void InitBuffer() override;
	void refresh() override;
};