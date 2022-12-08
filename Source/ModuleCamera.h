#pragma once
#include "Module.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{

public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	float4x4 getProjectionMatrix();
	float4x4 getModelMatrix();
	float4x4 getViewMatrix();
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void MoveForward();
	void MoveBackward();
	void CameraTranslation(float3& translation);
	bool CleanUp();

private:
	Frustum frustum;
	float horizon_fov;
	float camera_speed;
};