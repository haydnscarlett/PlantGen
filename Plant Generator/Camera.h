#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
	
	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	const DirectX::XMVECTOR& GetPositionVector() const;
	const DirectX::XMFLOAT3& GetPositionFloat3() const;
	const DirectX::XMVECTOR& GetRotationVector() const;
	const DirectX::XMFLOAT3& GetRotationFloat3() const;

	void SetPos(const DirectX::XMVECTOR& new_pos);
	void SetPos(float x, float y, float z);
	void AdjustPos(DirectX::XMVECTOR& adj_pos);
	void AdjustPos(float x, float y, float z);
	void SetRot(const DirectX::XMVECTOR& new_rot);
	void SetRot(float x, float y, float z);
	void AdjustRot(const DirectX::XMVECTOR& adj_rot);
	void AdjustRot(float x, float y, float z);
	void SetLookAtPos(DirectX::XMFLOAT3 lookAtPos);

	const DirectX::XMVECTOR& GetForwardVector();
	const DirectX::XMVECTOR& GetRightVector();
	const DirectX::XMVECTOR& GetBackwardVector();
	const DirectX::XMVECTOR& GetLeftVector();
private:
	void UpdateViewMatrix();
	DirectX::XMVECTOR posVector;
	DirectX::XMVECTOR rotVector;
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 rot;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	DirectX::XMVECTOR vecForward;
	DirectX::XMVECTOR vecLeft;
	DirectX::XMVECTOR vecRight;
	DirectX::XMVECTOR vecBackward;

};

