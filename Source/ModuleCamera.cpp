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
	horizon_fov = 200.0f;

	LOG("Setting Frustum Type to PerspectiveFrustum");
	frustum.type = FrustumType::PerspectiveFrustum;
	
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;

	//Axis arrow -> (x, y, z) -> (red, green, blue)
	frustum.pos = float3(1.0f, 1.0f, 1.0f);
	float3 target = float3(0.0f, 0.0f, 0.0f);

	frustum.horizontalFov = DegToRad(horizon_fov);
	frustum.verticalFov = frustum.horizontalFov / ((float)FULL_SCREEN_WIDTH / (float)FULL_SCREEN_HEIGHT);

	float3 forward = target - frustum.pos;
	forward.Normalize();
	float3 up = float3::unitY;
	float3 right = Cross(forward, up);
	right.Normalize();
	up = Cross(right, forward);
	up.Normalize();

	frustum.front = forward;
	frustum.up = up;

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
	//return float4x4::LookAt(float3(0.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY, float3(0.0f, 0.0f, 0.0f));
	return float4x4(frustum.ViewMatrix());
}

bool ModuleCamera::CleanUp()
{
	return true;
}