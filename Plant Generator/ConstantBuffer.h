#ifndef ConstantBuffer_h__
#define ConstantBuffer_h__

#include <d3d11.h>
#include "ConstantBufferTypes.h"
#include <wrl/client.h>


template<class T>
class ConstantBuffer
{
private:
	ConstantBuffer(const ConstantBuffer<T>& rhs);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;
	ID3D11DeviceContext* deviceContext = nullptr;

public:
	ConstantBuffer() {}

	T data;

	ID3D11Buffer* Get()const
	{
		return constantBuffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return constantBuffer.GetAddressOf();
	}

	HRESULT Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
	{
		deviceContext = context;

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - sizeof(T) % 16));
		cbd.StructureByteStride = 0u;


		HRESULT hr = device->CreateBuffer(&cbd, 0, constantBuffer.GetAddressOf());
		return hr;
	}

	bool ApplyChanges()
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		HRESULT hr = deviceContext->Map(constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(hr))
		{
			return false;
		}
		CopyMemory(mappedResource.pData, &data, sizeof(T));
		deviceContext->Unmap(constantBuffer.Get(), 0);
		return true;
	}
};
#endif // ConstantBuffer_h__