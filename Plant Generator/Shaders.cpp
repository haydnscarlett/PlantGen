#include "Shaders.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), vertexShaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateVertexShader(vertexShaderBuffer.Get()->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}
	hr = device->CreateInputLayout(
		layoutDesc, numElements,
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
	return vertexShader.Get();
}

ID3D10Blob* VertexShader::GetBuffer()
{
	return vertexShaderBuffer.Get();
}
ID3D11InputLayout* VertexShader::GetInputLayout()
{
	return inputLayout.Get();
}


bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath)
{
	HRESULT hr = D3DReadFileToBlob(shaderpath.c_str(), pixelShaderBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreatePixelShader(pixelShaderBuffer.Get()->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

ID3D11PixelShader* PixelShader::GetShader()
{
	return pixelShader.Get();
}

ID3D10Blob* PixelShader::GetBuffer()
{
	return pixelShaderBuffer.Get();
}