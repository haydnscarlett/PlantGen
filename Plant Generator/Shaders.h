#pragma once

#pragma comment(lib,"D3DCompiler.lib")
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>

class VertexShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements);
	ID3D11VertexShader* GetShader();
	ID3D10Blob* GetBuffer();
	ID3D11InputLayout* GetInputLayout();
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr;
};


class PixelShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath);
	ID3D11PixelShader* GetShader();
	ID3D10Blob* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> pixelShaderBuffer = nullptr;
};