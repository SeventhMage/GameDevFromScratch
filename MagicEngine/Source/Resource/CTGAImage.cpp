#include "CTGAImage.h"
#include "Foundation/Memory/Memory.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

namespace Magic
{
	CTGAImage::CTGAImage()
		: _Width(0), _Height(0), _Format(RGBA), _ImageSize(0), _pData(nullptr)
	{
		
	}

	CTGAImage::~CTGAImage()
	{
		SAFE_DELETE(_pData);
	}

	bool CTGAImage::Load(const char *filename)
	{
		FILE *pFile;  // File pointer
		short sDepth; // Pixel depth;

		// Attempt to open the file
		pFile = fopen(filename, "rb");
		if (pFile == NULL)
		{
			printf("Openfile %s failed\n", filename);
			return false;
		}
		// Read in header (binary)
		fread(&_TgaHeader, 18 /* sizeof(TGAHEADER)*/, 1, pFile);

		// Get width, height, and depth of texture
		_Width = _TgaHeader.width;
		_Height = _TgaHeader.height;
		sDepth = _TgaHeader.bits / 8;

		// Put some validity checks here. Very simply, I only understand
		// or care about 8, 24, or 32 bit targa's.
		if (_TgaHeader.bits != 8 && _TgaHeader.bits != 24 && _TgaHeader.bits != 32)
		{
			return false;
		}
		// Calculate size of image buffer
		_ImageSize = _TgaHeader.width * _TgaHeader.height * sDepth;

		// Allocate memory and check for success
		_pData = (unsigned char *)malloc(_ImageSize * sizeof(unsigned char));
		if (_pData == NULL)
		{
			return false;
		}
		// Read in the bits
		// Check for read error. This should catch RLE or other
		// weird formats that I don't want to recognize
		if (fread(_pData, _ImageSize, 1, pFile) != 1)
		{
			free(_pData);
			_pData = NULL;
			return false;
		}

		// Set OpenGL format expected
		switch (sDepth)
		{
#ifndef OPENGL_ES
		case 3: // Most likely case
			_Format = BGR;
			break;
#endif
		case 4:
			_Format = BGRA;
			break;
		case 1:
			_Format = LUMINANCE;
			break;
		default: // RGB
				 // If on the iPhone, TGA's are BGR, and the iPhone does not
				 // support BGR without alpha, but it does support RGB,
				 // so a simple swizzle of the red and blue bytes will suffice.
				 // For faster iPhone loads however, save your TGA's with an Alpha!
#ifdef OPENGL_ES
			for (int i = 0; i < lImageSize; i += 3)
			{
				GLbyte temp = pBits[i];
				pBits[i] = pBits[i + 2];
				pBits[i + 2] = temp;
			}
#endif
			break;
		}

		// Done with File
		fclose(pFile);

		return true;
	}
}