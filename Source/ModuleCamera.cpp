#include "ModuleCamera.h"


ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	LOG("Setting Frustum Type to PerspectiveFrustum");
	frustum.type = FrustumType::PerspectiveFrustum;
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

float4x4 ModuleCamera::getProjectionMatrix()
{
	/*frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * (16.0f / 9.0f)); //aspect;
	*/
	return frustum.ProjectionMatrix();
}

float4x4 ModuleCamera::getModelMatrix()
{
	return float4x4::identity;
	/*return float4x4::FromTRS(
		float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 0.0f)
	);*/
	//model.Transpose();
	//return model;
}

float4x4 ModuleCamera::getViewMatrix()
{
	//return float4x4::LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY, float3(0.0f, 0.0f, 0.0f));
	return float4x4(frustum.ViewMatrix());
}

bool ModuleCamera::CleanUp()
{
	return true;
}