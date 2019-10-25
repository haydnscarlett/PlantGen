#ifndef IndexBuffer_h__
#define IndexBuffer_h__
#include <d3d11.h>
#include <wrl/client.h>
#include <memory>

class IndexBuffer
{
private:
	IndexBuffer(const IndexBuffer& rhs);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;
	UINT bufferSize = 0;

public:
	IndexBuffer() {}

	ID3D11Buffer* Get()const
	{
		return indexBuffer.Get();
	}

	ID3D11Buffer* const* GetAddressOf()const
	{
		return indexBuffer.GetAddressOf();
	}

	UINT BufferSize() const
	{
		return this->bufferSize;
	}
	
	HRESULT Initialize(ID3D11Device* device, unsigned short* data, UINT numIndices)
	{
		this->bufferSize = numIndices;

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;;
		indexBufferDesc.ByteWidth = sizeof(unsigned short) * numIndices;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA indexBufferData;
		ZeroMemory(&indexBufferData, sizeof(indexBufferData));
		indexBufferData.pSysMem = data;

		HRESULT hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, this->indexBuffer.GetAddressOf());
		return hr;
	}
};

#endif // IndexBuffer_h__