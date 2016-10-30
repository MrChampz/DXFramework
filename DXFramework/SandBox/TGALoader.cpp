/////////////////////////////////////////////
//	Filename: TGALoader.cpp
/////////////////////////////////////////////
#include "TGALoader.h"

bool TGALoader::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename,
	ID3D11ShaderResourceView** textureView)
{
	bool result;
	HRESULT hResult;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ID3D11Texture2D* texture;
	unsigned int rowPitch;
	unsigned char* targaData;

	// Load the targa image data into memory
	targaData = LoadTarga(filename, height, width);
	if (!targaData)
	{
		return false;
	}

	// Setup the description of the texture
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture
	hResult = device->CreateTexture2D(&textureDesc, NULL, &texture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the targa image data into the texture
	deviceContext->UpdateSubresource(texture, 0, NULL, targaData, rowPitch, 0);

	// Setup the shader resource view description
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture
	hResult = device->CreateShaderResourceView(texture, &srvDesc, textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	// Generate mipmaps for this texture
	deviceContext->GenerateMips(*textureView);

	// Release the targa image data now that the image data has been loaded into the texture
	delete[] targaData;
	targaData = 0;

	return true;
}

bool TGALoader::LoadCubeMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename1, char* filename2,
	char* filename3, char* filename4, char* filename5, char* filename6, ID3D11ShaderResourceView** textureView)
{
	bool result;
	HRESULT hResult;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D11_SUBRESOURCE_DATA pData[6];
	ID3D11Texture2D* texture;
	unsigned int rowPitch;
	unsigned char* targaData;

	char* filenames[6];
	filenames[0] = filename1;
	filenames[1] = filename2;
	filenames[2] = filename3;
	filenames[3] = filename4;
	filenames[4] = filename5;
	filenames[5] = filename6;

	for (int i = 0; i < 6; i++)
	{
		// Load the targa image data into memory
		targaData = LoadTarga(filenames[i], height, width);
		if (!targaData)
		{
			return false;
		}

		// Set the row pitch of the targa image data
		rowPitch = (width * 4) * sizeof(unsigned char);

		// Pointer to the pixel data
		pData[i].pSysMem = targaData;
		// Line width in bytes
		pData[i].SysMemPitch = rowPitch;
		// This is only used for 3d textures.
		pData[i].SysMemSlicePitch = 0;
	}

	// Setup the description of the texture
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 6;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	// Create the empty texture
	hResult = device->CreateTexture2D(&textureDesc, &pData[0], &texture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Setup the shader resource view description
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = textureDesc.MipLevels;

	// Create the shader resource view for the texture
	hResult = device->CreateShaderResourceView(texture, &srvDesc, textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	// Release the targa image data now that the image data has been loaded into the texture
	delete[] targaData;
	targaData = 0;

	return true;
}

bool TGALoader::LoadTexture(ID3D10Device* device, char* filename, ID3D10ShaderResourceView** textureView)
{
	bool result;
	HRESULT hResult;
	int height, width;
	D3D10_TEXTURE2D_DESC textureDesc;
	D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ID3D10Texture2D* texture;
	unsigned int rowPitch;
	unsigned char* targaData;

	// Load the targa image data into memory
	targaData = LoadTarga(filename, height, width);
	if (!targaData)
	{
		return false;
	}

	// Setup the description of the texture
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D10_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE | D3D10_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D10_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture
	hResult = device->CreateTexture2D(&textureDesc, NULL, &texture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Set the row pitch of the targa image data
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the targa image data into the texture
	device->UpdateSubresource(texture, 0, NULL, targaData, rowPitch, 0);

	// Setup the shader resource view description
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture
	hResult = device->CreateShaderResourceView(texture, &srvDesc, textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	// Generate mipmaps for this texture
	device->GenerateMips(*textureView);

	// Release the targa image data now that the image data has been loaded into the texture
	delete[] targaData;
	targaData = 0;

	return true;
}

bool TGALoader::LoadCubeMap(ID3D10Device* device, char* filename1, char* filename2, char* filename3, char* filename4,
	char* filename5, char* filename6, ID3D10ShaderResourceView** textureView)
{
	bool result;
	HRESULT hResult;
	int height, width;
	D3D10_TEXTURE2D_DESC textureDesc;
	D3D10_SHADER_RESOURCE_VIEW_DESC srvDesc;
	D3D10_SUBRESOURCE_DATA pData[6];
	ID3D10Texture2D* texture;
	unsigned int rowPitch;
	unsigned char* targaData;

	char* filenames[6];
	filenames[0] = filename1;
	filenames[1] = filename2;
	filenames[2] = filename3;
	filenames[3] = filename4;
	filenames[4] = filename5;
	filenames[5] = filename6;

	for (int i = 0; i < 6; i++)
	{
		// Load the targa image data into memory
		targaData = LoadTarga(filenames[i], height, width);
		if (!targaData)
		{
			return false;
		}

		// Set the row pitch of the targa image data
		rowPitch = (width * 4) * sizeof(unsigned char);

		// Pointer to the pixel data
		pData[i].pSysMem = targaData;
		// Line width in bytes
		pData[i].SysMemPitch = rowPitch;
		// This is only used for 3d textures.
		pData[i].SysMemSlicePitch = 0;
	}

	// Setup the description of the texture
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 6;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D10_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D10_RESOURCE_MISC_TEXTURECUBE;

	// Create the empty texture
	hResult = device->CreateTexture2D(&textureDesc, &pData[0], &texture);
	if (FAILED(hResult))
	{
		return false;
	}

	// Setup the shader resource view description
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURECUBE;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = textureDesc.MipLevels;

	// Create the shader resource view for the texture
	hResult = device->CreateShaderResourceView(texture, &srvDesc, textureView);
	if (FAILED(hResult))
	{
		return false;
	}

	// Release the targa image data now that the image data has been loaded into the texture
	delete[] targaData;
	targaData = 0;

	return true;
}

unsigned char* TGALoader::LoadTarga(char* filename, int& height, int& width)
{
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char *targaImage, *targaData;

	// Open the targa file for reading in binary
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the file header
	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Get the important information from the header
	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	// Check that it is 32 bit and not 24 bit
	if (bpp != 32)
	{
		return false;
	}

	// Calculate the size of the 32 bit image data
	imageSize = width * height * 4;

	// Allocate memory for the targa image data
	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	// Read in the targa image data
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Allocate memory for the targa destination data
	targaData = new unsigned char[imageSize];
	if (!targaData)
	{
		return false;
	}

	// Initialize the index into the targa destination data array
	index = 0;

	// Initialize the index into the targa image data
	k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			targaData[index + 0] = targaImage[k + 2];  // Red.
			targaData[index + 1] = targaImage[k + 1];  // Green.
			targaData[index + 2] = targaImage[k + 0];  // Blue
			targaData[index + 3] = targaImage[k + 3];  // Alpha

														 // Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	return targaData;
}