#include "ModuleCamera.h"
#include "Application.h"


ModuleCamera::ModuleCamera()
{
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	horizon_fov = 150.0f;
	camera_speed = 1.0f;

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
	float3 up = float3::unitY;
	forward.Normalize();
	float3 right = Cross(forward, up);
	right.Normalize();
	up = Cross(right, forward);
	up.Normalize();

	frustum.front = forward;
	frustum.up = up;

	/*Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * 1.0f);*/

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
}

float4x4 ModuleCamera::getViewMatrix()
{
	//return float4x4::LookAt(float3(0.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 0.0f), float3::unitY, float3(0.0f, 0.0f, 0.0f));
	return float4x4(frustum.ViewMatrix());
}

void ModuleCamera::MoveUp(bool fast) {
	float3 translation;
	if (fast) translation = float3(0.0f, App->getDeltaTime() * camera_speed * 2, 0.0f);
	else translation = float3(0.0f, App->getDeltaTime() * camera_speed, 0.0f);
	CameraTranslation(translation);
}

void ModuleCamera::MoveDown(bool fast) {
	float3 translation;
	if (fast) translation = float3(0.0f, App->getDeltaTime() * -camera_speed * 2, 0.0f);
	else translation = float3(0.0f, App->getDeltaTime() * -camera_speed, 0.0f);
	CameraTranslation(translation);
}

void ModuleCamera::MoveRight(bool fast) {
	float3 translation;
	if (fast) translation = float3(App->getDeltaTime() * camera_speed * 2, 0.0f, 0.0f);
	else translation = float3(App->getDeltaTime() * camera_speed, 0.0f, 0.0f);
	CameraTranslation(translation);
}

void ModuleCamera::MoveLeft(bool fast) {
	float3 translation;
	if (fast) translation = float3(App->getDeltaTime() * -camera_speed * 2, 0.0f, 0.0f);
	else translation = float3(App->getDeltaTime() * -camera_speed, 0.0f, 0.0f);
	CameraTranslation(translation);
}

void ModuleCamera::MoveForward(bool fast) {
	float3 translation;
	if (fast) translation = float3(0.0f, 0.0f, App->getDeltaTime() * camera_speed * 2);
	else translation = float3(0.0f, 0.0f, App->getDeltaTime() * camera_speed);
	CameraTranslation(translation);
}

void ModuleCamera::MoveBackward(bool fast) {
	float3 translation;
	if (fast) translation = float3(0.0f, 0.0f, App->getDeltaTime() * -camera_speed * 2);
	else translation = float3(0.0f, 0.0f, App->getDeltaTime() * -camera_speed);
	CameraTranslation(translation);
}

void ModuleCamera::CameraTranslation(float3& translation) {
	frustum.pos += frustum.WorldRight() * translation.x;
	frustum.pos += float3(0.0f, 1.0f, 0.0f) * translation.y;
	frustum.pos += frustum.front * translation.z;
}

bool ModuleCamera::CleanUp()
{
	return true;
}