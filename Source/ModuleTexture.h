#pragma once
#include "Module.h"
#include "DirectXTex.h"

using namespace DirectX;

class ModuleTexture : public Module
{

public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool LoadTexture(const wchar_t* filename, TexMetadata *md, ScratchImage &img);
	bool CleanUp();

private:

};
