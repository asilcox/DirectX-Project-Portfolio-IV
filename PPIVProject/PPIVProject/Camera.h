#pragma once
#include "Graphics.h"

class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetMatrix();
	void Rotate(float dx, float dy);
	void Translate(DirectX::XMFLOAT3 translation);
	void Reset();
	DirectX::XMFLOAT3 GetPos();
private:
	float r = 20.0f;
	float z = 20.0f;
	float x = 0.0f;
	float theta = 0.0f;
	float phi = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
	DirectX::XMFLOAT3 pos;
	static constexpr float travelSpeed = 12.0f;
	static constexpr float rotationSpeed = 0.004f;
};