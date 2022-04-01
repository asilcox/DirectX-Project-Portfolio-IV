#include "Camera.h"

Camera::Camera()
{
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix()
{
	const DirectX::XMVECTOR forwardBaseVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const auto lookVector = DirectX::XMVector3Transform(forwardBaseVector,
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f)
	);
	const auto camPosition = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR camTarget = DirectX::XMVectorAdd(camPosition, lookVector);
	return DirectX::XMMatrixLookAtLH(camPosition, camTarget, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::Rotate(float dx, float dy)
{
	yaw = dx;
	pitch = dy;
}

void Camera::Translate(DirectX::XMFLOAT3 translation)
{
	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(
		DirectX::XMLoadFloat3(&translation),
		DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) *
		DirectX::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
	));
	pos = {
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z
	};
}

void Camera::Reset()
{
	pos = { 0.0, 0.0f, 0.0f };

	r = 20.0f;
	theta = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
}

DirectX::XMFLOAT3 Camera::GetPos()
{
	return pos;
}