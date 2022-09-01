#ifndef _MAGIC_C_TGAIMAGE_H_
#define _MAGIC_C_TGAIMAGE_H_

#include "Resource/IImage.h"

#include <string>

namespace Magic
{
#pragma pack(push)
#pragma pack(1)
	typedef struct
	{
		char identsize;				   // Size of ID field that follows header (0)
		char colorMapType;			   // 0 = None, 1 = paletted
		char imageType;				   // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
		unsigned short colorMapStart;  // First colour map entry
		unsigned short colorMapLength; // Number of colors
		unsigned char colorMapBits;	   // bits per palette entry
		unsigned short xstart;		   // image x origin
		unsigned short ystart;		   // image y origin
		unsigned short width;		   // width in pixels
		unsigned short height;		   // height in pixels
		char bits;					   // bits per pixel (8 16, 24, 32)
		char descriptor;			   // image descriptor
	} TGAHEADER;
#pragma pack(pop)

	class CTGAImage : public IImage
	{
	public:
		CTGAImage();
		~CTGAImage();

		virtual bool Load(const char *fullPath);
		virtual unsigned char *GetData() const { return _pData; }
		virtual Format GetFormat() const { return _Format; }
		virtual unsigned long GetImageSize() const { return _ImageSize; }
		virtual int GetWidth() const { return _Width; }
		virtual int GetHeight() const { return _Height; }

	private:
		std::string _Filename;
		int _Width;
		int _Height;
		Format _Format;
		unsigned long _ImageSize;
		unsigned char *_pData;
		TGAHEADER _TgaHeader;
	};
}

#endif