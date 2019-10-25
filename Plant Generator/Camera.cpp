#include "Camera.h"

Camera::Camera()
{
	pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	posVector = DirectX::XMLoadFloat3(&pos);
	rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotVector = DirectX::XMLoadFloat3(&rot);
	UpdateViewMatrix();
}
void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}
const DirectX::XMMATRIX& Camera::GetViewMatrix() const
{
	return viewMatrix;
}
const DirectX::XMMATRIX& Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

const DirectX::XMVECTOR& Camera::GetPositionVector() const
{
	return posVector;
}
const DirectX::XMFLOAT3& Camera::GetPositionFloat3() const
{
	return pos;
}
const DirectX::XMVECTOR& Camera::GetRotationVector() const
{
	return rotVector;
}
const DirectX::XMFLOAT3& Camera::GetRotationFloat3() const
{
	return rot;
}

void Camera::SetPos(const DirectX::XMVECTOR& new_pos)
{
	DirectX::XMStoreFloat3(&pos, new_pos);
	posVector = new_pos;
	UpdateViewMatrix();
}
void Camera::SetPos(float x, float y, float z)
{
	pos = DirectX::XMFLOAT3(x, y, z);
	posVector = DirectX::XMLoadFloat3(&pos);
	UpdateViewMatrix();
}
void Camera::AdjustPos(DirectX::XMVECTOR& adj_pos)
{
	posVector = DirectX::XMVectorAdd(posVector, adj_pos);
	DirectX::XMStoreFloat3(&pos, posVector);
	UpdateViewMatrix();
}
void Camera::AdjustPos(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
	posVector = XMLoadFloat3(&pos);
	UpdateViewMatrix();
}
void Camera::SetRot(const DirectX::XMVECTOR& new_rot)
{
	DirectX::XMStoreFloat3(&rot, new_rot);
	rotVector = new_rot;
	UpdateViewMatrix();
}
void Camera::SetRot(float x, float y, float z)
{
	rot = DirectX::XMFLOAT3(x, y, z);
	rotVector = DirectX::XMLoadFloat3(&rot);
	UpdateViewMatrix();
}
void Camera::AdjustRot(const DirectX::XMVECTOR& adj_rot)
{
	rotVector = DirectX::XMVectorAdd(rotVector, adj_rot);
	DirectX::XMStoreFloat3(&rot, rotVector);
	UpdateViewMatrix();
}
void Camera::AdjustRot(float x, float y, float z)
{
	rot.x = x;
	rot.y = y;
	rot.z = z;
	rotVector = XMLoadFloat3(&rot);
	UpdateViewMatrix();
}
void Camera::UpdateViewMatrix()
{
	DirectX::XMMATRIX camRotMatrix = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	DirectX::XMVECTOR camTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotMatrix);
	camTarget = DirectX::XMVectorAdd(camTarget, posVector);
	DirectX::XMVECTOR upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotMatrix);
	viewMatrix = DirectX::XMMatrixLookAtLH(posVector, camTarget, upDir);

	DirectX::XMMATRIX vecRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(0.0f, rot.y, 0.0f);
	vecForward = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	vecBackward = DirectX::XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	vecLeft = DirectX::XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	vecRight = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vecRotationMatrix);

}


void Camera::SetLookAtPos(DirectX::XMFLOAT3 lookAtPos)
{
	if (lookAtPos.x == pos.x && lookAtPos.y == pos.y && lookAtPos.z == pos.z)
		return;

	lookAtPos.x = pos.x - lookAtPos.x;
	lookAtPos.y = pos.y - lookAtPos.y;
	lookAtPos.z = pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);

	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0.0f)
	{
		yaw += DirectX::XM_PI;
	}
	SetRot(pitch, yaw, 0.0f);
}

const DirectX::XMVECTOR& Camera::GetForwardVector()
{
	return vecForward;
}
const DirectX::XMVECTOR& Camera::GetRightVector()
{
	return vecRight;
}
const DirectX::XMVECTOR& Camera::GetBackwardVector()
{
	return vecBackward;
}
const DirectX::XMVECTOR& Camera::GetLeftVector()
{
	return vecLeft;
}