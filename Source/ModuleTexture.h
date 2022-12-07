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
	void LoadTexture();
	bool CleanUp();

private:
	const wchar_t* filename = L"C:/Users/usuario/source/repos/OpenGL - exercise/Source/assets/textures";
	TexMetadata md;
	ScratchImage img;

};
