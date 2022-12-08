#include "ModuleTexture.h"
#include "DirectXTex.h"
using namespace DirectX;


ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{
	LoadTexture();
	return true;
}

update_status ModuleTexture::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void ModuleTexture::LoadTexture()
{
	HRESULT result = E_FAIL;

	result = LoadFromDDSFile(filename, DDS_FLAGS_NONE, &md, img);

	if (FAILED(result)) result = LoadFromTGAFile(filename, TGA_FLAGS_NONE, &md, img);

	if (FAILED(result)) result = LoadFromWICFile(filename, WIC_FLAGS_NONE, &md, img);
	
	if (FAILED(result)) 
	{
		LOG("Failed to load Texture");
		return;
	}

	result = FlipRotate(*(img.GetImage(0,0,0)), TEX_FR_FLIP_VERTICAL, img);
}

bool ModuleTexture::CleanUp()
{
	return true;
}