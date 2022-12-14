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

bool ModuleTexture::LoadTexture(const wchar_t* filename, TexMetadata* md, ScratchImage& img)
{
	HRESULT result = E_FAIL;

	result = LoadFromDDSFile(filename, DDS_FLAGS_NONE, md, img);
	if (FAILED(result)) result = LoadFromTGAFile(filename, TGA_FLAGS_NONE, md, img);
	if (FAILED(result)) result = LoadFromWICFile(filename, WIC_FLAGS_NONE, md, img);
	return SUCCEEDED(result);
}

bool ModuleTexture::CleanUp()
{
	return true;
}