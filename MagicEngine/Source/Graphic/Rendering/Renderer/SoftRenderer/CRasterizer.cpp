#include "CRasterizer.h"
#include "Foundation/Utils/Utils.hpp"
#include "Foundation/Memory/Memory.h"
#include <stdio.h>

namespace Magic
{
	CRasterizer::CRasterizer()
		: _pDrawBuffer(nullptr), _pDepthBuffer(nullptr), _pMinEdgeBuffer(nullptr), _pMaxEdgeBuffer(nullptr),
		   _bufferWidth(0), _bufferHeight(0), _OnFProgram(nullptr), _pGlobalUniforms(nullptr), _pUniforms(nullptr)
	{
	}

	CRasterizer::~CRasterizer()
	{
		SAFE_DELETE_ARRAY(_pMinEdgeBuffer);
		SAFE_DELETE_ARRAY(_pMaxEdgeBuffer);
	}

	void CRasterizer::DrawTriangle(Vector4f p0, Vector4f p1, Vector4f p2, Vector2f t0,
					  Vector2f t1, Vector2f t2, Color c0, Color c1, Color c2)
	{
		//三角形退化为线
		if ((FLOAT_EQUAL(p0.y, p1.y) && FLOAT_EQUAL(p0.y, p2.y)) ||
			(FLOAT_EQUAL(p0.x, p1.x) && FLOAT_EQUAL(p0.x, p2.x)))
			return;

		//按y从小到大排序
		if (p1.y < p0.y)
		{
			Utils::Swap(p0, p1);
			Utils::Swap(t0, t1);
			Utils::Swap(c0, c1);
		}

		if (p2.y < p1.y)
		{
			Utils::Swap(p2, p1);
			Utils::Swap(t2, t1);
			Utils::Swap(c2, c1);
		}

		if (p1.y < p0.y)
		{
			Utils::Swap(p0, p1);
			Utils::Swap(t0, t1);
			Utils::Swap(c0, c1);
		}

		if (FLOAT_EQUAL(p0.y, p1.y))
		{
			if (p1.x < p0.x)
				DrawBottomTriangle(p0, t0, c0, p1, t1, c1, p2, t2, c2);
			else
				DrawBottomTriangle(p1, t1, c1, p0, t0, c0, p2, t2, c2);
		}
		else if (FLOAT_EQUAL(p1.y, p2.y))
		{
			if (p1.x < p2.x)
				DrawTopTriangle(p0, t0, c0, p1, t1, c1, p2, t2, c2);
			else
				DrawTopTriangle(p0, t0, c0, p2, t2, c2, p1, t1, c1);
		}
		else
		{
			float newX = p0.x + (p2.x - p0.x) * (p1.y - p0.y) / (p2.y - p0.y);
			// float p02Rate = Vector2f(newX, p1.y).getDistanceFrom(Vector2f(p0.x, p0.y))
			//	/ Vector2f(p0.x, p0.y).getDistanceFrom(Vector2f(p2.x, p2.y));

			float p02Rate = (Vector2f(newX, p1.y) - (Vector2f(p0.x, p0.y))).Length() * (Vector2f(p0.x, p0.y) - (Vector2f(p2.x, p2.y))).InvLength();

			float invNewZ = p0.z * (1 - p02Rate) + p2.z * p02Rate;
			float newW = (1 / p0.w) * (1 - p02Rate) + (1 / p2.w) * p02Rate;

			Vector4f newPoint(newX, p1.y, invNewZ, 1 / newW);

			Vector2f newTexCoord = ((t0 / p0.w) * (1 - p02Rate) + (t2 / p2.w) * p02Rate) / newW;
			Color newColor = (((c0 / p0.w) * (1 - p02Rate)) + ((c2 / p2.w) * p02Rate)) / newW;
			if (p1.x < newPoint.x)
			{

				DrawTopTriangle(p0, t0, c0, p1, t1, c1, newPoint, newTexCoord, newColor);
				DrawBottomTriangle(newPoint, newTexCoord, newColor, p1, t1, c1, p2, t2, c2);
			}
			else
			{
				DrawTopTriangle(p0, t0, c0, newPoint, newTexCoord, newColor, p1, t1, c1);
				DrawBottomTriangle(p1, t1, c1, newPoint, newTexCoord, newColor, p2, t2, c2);
			}
		}
	}

	void CRasterizer::DrawTopTriangle(const Vector4f &p0, const Vector2f &t0,
									  const Color &c0, const Vector4f &p1, const Vector2f &t1,
									  const Color &c1, const Vector4f &p2, const Vector2f &t2, const Color &c2)
	{
		float dx01 = (p1.x - p0.x) / (p1.y - p0.y);
		float dx02 = (p2.x - p0.x) / (p2.y - p0.y);
		float x0 = p0.x;
		float x1 = p0.x;

		float ratel = sqrt(1 + dx01 * dx01);
		float rater = sqrt(1 + dx02 * dx02);

		// float dzl = (p1.z - p0.z) / (p0.getDistanceFrom(p1));
		// float dzr = (p2.z - p0.z) / (p0.getDistanceFrom(p2));

		float dzl = (p1.z - p0.z) * (p0.getInvDistanceFrom(p1));
		float dzr = (p2.z - p0.z) * (p0.getInvDistanceFrom(p2));

		dzl *= ratel;
		dzr *= rater;
		float zl = p0.z;
		float zr = p0.z;

		// float dwl = (1 / p1.w - 1 / p0.w) / (p0.getDistanceFrom(p1));
		// float dwr = (1 / p2.w - 1 / p0.w) / (p0.getDistanceFrom(p2));

		float dwl = (1 / p1.w - 1 / p0.w) * (p0.getInvDistanceFrom(p1));
		float dwr = (1 / p2.w - 1 / p0.w) * (p0.getInvDistanceFrom(p2));

		dwl *= ratel;
		dwr *= rater;
		float wl = 1 / p0.w;
		float wr = 1 / p0.w;

		// Color dcl = (c1 / p1.w - c0 / p0.w) / (p0.getDistanceFrom(p1));
		// Color dcr = (c2 / p2.w - c0 / p0.w) / (p0.getDistanceFrom(p2));

		Color dcl = (c1 / p1.w - c0 / p0.w) * (p0.getInvDistanceFrom(p1));
		Color dcr = (c2 / p2.w - c0 / p0.w) * (p0.getInvDistanceFrom(p2));

		dcl *= ratel;
		dcr *= rater;
		Color cl = c0 * wl;
		Color cr = c0 * wr;

		float dul = (t1.x / p1.w - t0.x / p0.w) / fabs(p1.x - p0.x);
		float dvl = (t1.y / p1.w - t0.y / p0.w) / fabs(p1.y - p0.y);
		float dur = (t2.x / p2.w - t0.x / p0.w) / fabs(p2.x - p0.x);
		float dvr = (t2.y / p2.w - t0.y / p0.w) / fabs(p2.y - p0.y);
		dul *= fabs(dx01);
		dur *= fabs(dx02);
		float ul = t0.x * wl;
		float vl = t0.y * wl;
		float ur = t0.x * wr;
		float vr = t0.y * wr;

		for (int i = (int)p0.y; i < (int)p2.y; ++i)
		{
			if (i >= _bufferHeight)
				break;

			if (i > 0 && x1 >= 0 && x0 < _bufferWidth && x1 >= x0)
			{
				unsigned int *addr = (unsigned int *)_pDrawBuffer + (unsigned int)(MAX(x0, 0) + (i - 1) * _bufferWidth);

				Vector2f tl(ul, vl);

				Vector2f tr(ur, vr);

				if (_pDepthBuffer)
				{
					float *zbuffer = _pDepthBuffer + int(MAX(x0, 0) + (i - 1) * _bufferWidth);
					if (_pSamplers)
					{
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr, tl, tr);
					}
					else
					{
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr);
					}
				}
				else
				{
					FillColor(addr, x1 - x0, cl, cr);
				}
			}

			zl += dzl;
			zr += dzr;

			wl += dwl;
			wr += dwr;

			x0 += dx01;
			x1 += dx02;

			ul += dul;
			vl += dvl;

			ur += dur;
			vr += dvr;

			cl += dcl;
			cr += dcr;
		}
	}

	void CRasterizer::DrawBottomTriangle(const Vector4f &p0, const Vector2f &t0,
										 const Color &c0, const Vector4f &p1, const Vector2f &t1,
										 const Color &c1, const Vector4f &p2, const Vector2f &t2, const Color &c2)
	{
		float dx12 = (p1.x - p2.x) / (p1.y - p2.y);
		float dx02 = (p0.x - p2.x) / (p0.y - p2.y);
		float x0 = p1.x;
		float x1 = p0.x;

		float ratel = sqrt(1 + dx12 * dx12);
		float rater = sqrt(1 + dx02 * dx02);
		// float dzl = (p2.z - p1.z) / (p2.getDistanceFrom(p1));
		// float dzr = (p2.z - p0.z) / (p2.getDistanceFrom(p0));

		float dzl = (p2.z - p1.z) * (p2.getInvDistanceFrom(p1));
		float dzr = (p2.z - p0.z) * (p2.getInvDistanceFrom(p0));

		dzl *= ratel;
		dzr *= rater;

		float zl = p1.z;
		float zr = p0.z;

		// float dwl = (1 / p2.w - 1 / p1.w) / (p2.getDistanceFrom(p1));
		// float dwr = (1 / p2.w - 1 / p0.w) / (p2.getDistanceFrom(p0));

		float dwl = (1 / p2.w - 1 / p1.w) * (p2.getInvDistanceFrom(p1));
		float dwr = (1 / p2.w - 1 / p0.w) * (p2.getInvDistanceFrom(p0));

		dwl *= ratel;
		dwr *= rater;
		float wl = 1 / p1.w;
		float wr = 1 / p0.w;

		// Color dcl = (c2 / p2.w - c1 / p1.w) / (p2.getDistanceFrom(p1));
		// Color dcr = (c2 / p2.w - c0 / p0.w) / (p2.getDistanceFrom(p0));

		Color dcl = (c2 / p2.w - c1 / p1.w) * (p2.getInvDistanceFrom(p1));
		Color dcr = (c2 / p2.w - c0 / p0.w) * (p2.getInvDistanceFrom(p0));

		dcl *= ratel;
		dcr *= rater;
		Color cl = c1 * wl;
		Color cr = c0 * wr;

		float dul = (t2.x / p2.w - t1.x / p1.w) / fabs(p2.x - p1.x);
		float dvl = (t2.y / p2.w - t1.y / p1.w) / fabs(p2.y - p1.y);
		float dur = (t2.x / p2.w - t0.x / p0.w) / fabs(p2.x - p0.x);
		float dvr = (t2.y / p2.w - t0.y / p0.w) / fabs(p2.y - p0.y);
		dul *= fabs(dx12);
		dur *= fabs(dx02);
		float ul = t1.x * wl;
		float vl = t1.y * wl;
		float ur = t0.x * wr;
		float vr = t0.y * wr;

		for (int i = (int)p0.y; i < (int)p2.y; ++i)
		{
			if (i >= _bufferHeight)
				break;

			if (i > 0 && x1 >= 0 && x0 < _bufferWidth && x1 >= x0)
			{
				unsigned int *addr = (unsigned int *)_pDrawBuffer + (unsigned int)(MAX(x0, 0) + (i - 1) * _bufferWidth);

				Vector2f tl(ul, vl);
				Vector2f tr(ur, vr);

				if (_pDepthBuffer)
				{
					float *zbuffer = _pDepthBuffer + int(MAX(x0, 0) + (i - 1) * _bufferWidth);
					if (_pSamplers)
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr, tl, tr);
					else
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr);
				}
				else
					FillColor(addr, x1 - x0 + 1, cl, cr);
			}

			zl += dzl;
			zr += dzr;

			wl += dwl;
			wr += dwr;

			x0 += dx12;
			x1 += dx02;

			cl += dcl;
			cr += dcr;

			ul += dul;
			vl += dvl;
			ur += dur;
			vr += dvr;
		}
	}

	Color CRasterizer::GetInterpolation(const Color &c0, const Color &c1, float rate)
	{
		Color color(c0.a * (1 - rate) + c1.a * rate, c0.r * (1 - rate) + c1.r * rate,
					c0.g * (1 - rate) + c1.g * rate, c0.b * (1 - rate) + c1.b * rate);
		return color;
	}

	void CRasterizer::FillColor(unsigned int *addr, unsigned int count, const Color &c0, const Color &c1)
	{
		for (unsigned int i = 0; i < count; ++i)
		{
			float rate = 1.f * i / count;
			Color color = GetInterpolation(c0, c1, rate);
			auto result = _OnFProgram(_pGlobalUniforms, _pUniforms, nullptr, &color);
			*addr = result.Get32BitColor();
			++addr;
		}
	}

	void CRasterizer::FillColor(unsigned int *addr, float *zbuffer, unsigned int x0, float z0, float wl,
								unsigned int x1, float z1, float wr, const Color &c0, const Color &c1)
	{
		int count = x1 - x0;
		float invcount = 1.f / count;
		float dz = (z1 - z0) * invcount;
		float z = z0;
		//float dw = (wr - wl) * invcount;
		//float w = wl; 
		int x = x0; 
		Color dc = (c1 - c0) * invcount;
		Color c =  c0; 
		for (int i = 0; i < count; ++i)
		{
			if (x >= _bufferWidth)
				break;
			if ((z < *zbuffer) && (z >= -1 && z <= 1) && (x >= 0)) //这里的z实际为1/z
			{
				float invz = 1 / z;
				static Color color;
				color.a = c.a * invz;
				color.r = c.r * invz;
				color.g = c.g * invz;
				color.b = c.b * invz;

				auto result = _OnFProgram(_pGlobalUniforms, _pUniforms, _pSamplers, &color);

				*addr = result.Get32BitColor();
				*zbuffer = z;
			}

			x += 1;

			z += dz;
			//w += dw;
			c.a += dc.a;
			c.r += dc.r;
			c.g += dc.g;
			c.b += dc.b;

			if (x >= 0)
			{
				++zbuffer;
				++addr;
			}
		}
	}

	void CRasterizer::FillColor(unsigned int *addr, float *zbuffer, unsigned int x0, float z0, float wl,
								unsigned int x1, float z1, float wr, const Color &lc, const Color &rc, const Vector2f &lt, const Vector2f &rt)
	{
		int count = x1 - x0;
		int x = x0;
		float invcount = 1.f / count;
		float dz = (z1 - z0) * invcount;
		float z = z0;
		float dw = (wr - wl) * invcount;
		float w = wl;
		Color dc = (rc - lc) * invcount;
		Color c = lc;
		float du = (rt.x - lt.x) * invcount;
		float dv = (rt.y - lt.y) * invcount;

		float u = lt.x;
		float v = lt.y;
		for (int i = 0; i < count; ++i)
		{
			if (x >= _bufferWidth)
				break;
			if ((x >= 0) && (z < *zbuffer) && (z >= -1 && z <= 1)) // This z is 1/z in fact.
			{
				float invw = 1.f / w;
				float tx = u * invw;
				float ty = v * invw;
				// color + uv
				static float datas[4 + 2];
				Color &color = *((Color *)datas);
				color.a = c.a * invw;
				color.r = c.r * invw;
				color.g = c.g * invw;
				color.b = c.b * invw;

				Vector2f &texCoord = *(Vector2f *)(&color + 1);
				texCoord.x = tx;
				texCoord.y = ty;

				// fragment shader
				auto result = _OnFProgram(_pGlobalUniforms, _pUniforms, _pSamplers, datas);

				*addr = result.Get32BitColor();
				*zbuffer = z;
			}

			x += 1;

			z += dz;
			w += dw;
			c.a += dc.a;
			c.r += dc.r;
			c.g += dc.g;
			c.b += dc.b;
			u += du;
			v += dv;

			if (x >= 0)
			{
				++zbuffer;
				++addr;
			}
		}
	}

	void CRasterizer::FillColor(unsigned int *addr, float *zbuffer, const EdgeBuffer &minEdge, const EdgeBuffer &maxEdge)
	{
		int count = maxEdge.X - minEdge.X;
		if (count < 0)
			count = -count;
		int x = minEdge.X;
		float invcount = 1.f / count;
		float dz = (maxEdge.InvZ - minEdge.InvZ) * invcount;
		float invz = minEdge.InvZ;
		float dw = (maxEdge.InvW - minEdge.InvW) * invcount;
		float invw = minEdge.InvW;
		Color dc = (maxEdge.Color - minEdge.Color) * invcount;
		Color c = minEdge.Color;
		Vector2f dt = (maxEdge.TexCoords - minEdge.TexCoords) * invcount;
		Vector2f t = minEdge.TexCoords;


		float realz;

		for (int i = 0; i < count; ++i)
		{
			if ((x >= 0) && (invz < *zbuffer) && (invz >= -1 && invz <= 1))
			{
				realz = 1.f / invw;
				// color + uv
				static float datas[4 + 2];
				Color &color = *((Color *)datas);
				color.a = c.a * realz;
				color.r = c.r * realz;
				color.g = c.g * realz;
				color.b = c.b * realz;
				Vector2f &texCoord = *(Vector2f *)(&color + 1);
				texCoord.x = t.x * realz;
				texCoord.y = t.y * realz;
				// fragment shader
				auto result = _OnFProgram(_pGlobalUniforms, _pUniforms, _pSamplers, datas);
				*addr = result.Get32BitColor();
				*zbuffer = invz;
			}

			x += 1;

			if (x >= _bufferWidth)
				break;
				
			invz += dz;
			invw += dw;
			c.a += dc.a;
			c.r += dc.r;
			c.g += dc.g;
			c.b += dc.b;
			t.x = t.x + dt.x;
			t.y = t.y + dt.y;

			if (x >= 0)
			{
				++zbuffer;
				++addr;
			}
		}
	}

	void CRasterizer::SetFProgram(FProgram fProgram, UniformMap *globalUniforms, UniformMap *uniforms, ISampler **sampler)
	{
		_OnFProgram = fProgram;
		_pGlobalUniforms = globalUniforms;
		_pUniforms = uniforms;
		_pSamplers = sampler;
	}

	void CRasterizer::SetDrawBuffer(unsigned int *pDrawBuffer, int width, int height)
	{
		_pDrawBuffer = pDrawBuffer;
		if (_bufferHeight < height)
		{
			SAFE_DELETE(_pMinEdgeBuffer);
			SAFE_DELETE(_pMaxEdgeBuffer);
			_pMinEdgeBuffer = NEW EdgeBuffer[height];
			_pMaxEdgeBuffer = NEW EdgeBuffer[height];
		}

		_bufferWidth = width;
		_bufferHeight = height;
	}

	// Bresenham:See 3D Game Engine Design Second Edition, page 77
	void CRasterizer::DrawLine(int x0, int y0, int x1, int y1, const Color &c /* = Color(1, 0, 0, 0)*/)
	{
		// start point of the line
		int x = x0;
		int y = y0;

		// direction of line
		int dx = x1 - x0;
		int dy = y1 - y0;

		// Increment or decrement on direction of line
		int sx = 0;
		int sy = 0;
		if (dx > 0)
		{
			sx = 1;
		}
		else if (dx < 0)
		{
			sx = -1;
			dx = -dx;
		}

		if (dy > 0)
		{
			sy = 1;
		}
		else if (dy < 0)
		{
			sy = -1;
			dy = -dy;
		}

		int ax = 2 * dx;
		int ay = 2 * dy;

		if (dy <= dx)
		{
			// single step in x-direction
			for (int decy = ay - dx; x += sx; decy += ay)
			{
				DrawPixel(x, y, c);
				if (x == x1)
				{
					break;
				}
				if (decy >= 0)
				{
					decy -= ax;
					y += sy;
				}
			}
		}
		else
		{
			// single step in y-direction
			for (int decx = ax - dy; y += sy; decx += ax)
			{
				DrawPixel(x, y, c);
				if (y == y1)
				{
					break;
				}
				if (decx >= 0)
				{
					decx -= ay;
					x += sx;
				}
			}
		}
	}

	void CRasterizer::DrawPixel(int x, int y, const Color &c)
	{
		x = MIN(MAX(x, 0), _bufferWidth - 1);
		y = MIN(MAX(y, 0), _bufferHeight - 1);
		unsigned int *addr = (unsigned int *)_pDrawBuffer + (unsigned int)(x);
		if (y > 0)
			addr += (unsigned int)((y - 1) * _bufferWidth);
		*addr = c.Get32BitColor();
	}

	void CRasterizer::DrawEdgeBuffer(int i0, int i1, Vector4f p[3], Vector3f n[3], Color c[3], Vector2f t[3], EdgeBuffer *edgeBuffer)
	{
		int x0 = p[i0].x;
		int x1 = p[i1].x;
		int y0 = p[i0].y;
		int y1 = p[i1].y;
		float invz0 = p[i0].z;
		float invz1 = p[i1].z;
		float invw0 = 1.f / p[i0].w;
		float invw1 = 1.f / p[i1].w;

		// start point of the line
		int x = x0;
		int y = y0;

		// direction of line
		int dx = x1 - x0;
		int dy = y1 - y0;

		// Increment or decrement on direction of line
		int sx = 0;
		int sy = 0;
		if (dx > 0)
		{
			sx = 1;
		}
		else if (dx < 0)
		{
			sx = -1;
			dx = -dx;
		}

		if (dy > 0)
		{
			sy = 1;
		}
		else if (dy < 0)
		{
			sy = -1;
			dy = -dy;
		}

		int ax = 2 * dx;
		int ay = 2 * dy;
		

		float dx01 = (p[i1].x - p[i0].x) / (p[i1].y - p[i0].y);
		float rate = sqrt(1 + dx01 * dx01);
		
		float invDis = Utils::InvSqrt(dx * dx + dy * dy);
		float invdz = (invz1 - invz0) * invDis * rate;
		float invdw = (invw1 - invw0) * invDis * rate;
		float decz = invz0;
		float decw = invw0;

		Vector3f dn;
		Vector3f decn;
		Vector2f dt;
		Vector2f dect;
		Color dc;
		Color decc;

		if (n)
		{
			dn = (n[i1] * invw1 - n[i0] * invw0) * invDis * rate;
			decn  = n[i0] * invw0;
		}
		if (t)
		{
			dt.x = (t[i1].x * invw1 - t[i0].x * invw0) / dx;
			dt.y = (t[i1].y * invw1 - t[i0].y * invw0) / dy;
			dect = t[i0] * invw0;
		}

		if (c)
		{
			dc = (c[i1] * invw1 - c[i0] * invw0) * invDis * rate;
			decc =  c[i0] * invw0;
		}

		if (dy <= dx)
		{
			// single step in x-direction
			for (int decy = ay - dx; ;x += sx, decy += ay)
			{
				edgeBuffer[y].X = x;
				if (n)
				{
					edgeBuffer[y].Normal = decn;
				}

				if (t)
				{
					edgeBuffer[y].TexCoords = dect;
				}

				if (c)
				{
					edgeBuffer[y].Color = decc;
				}

				edgeBuffer[y].InvZ = decz;
				edgeBuffer[y].InvW = decw;

				if (x == x1)
				{
					break;
				}

				if (decy >= 0)
				{
					if (n)
					{
						decn = decn + dn;
					}

					if (t)
					{
						dect.x += dt.x;
						dect.y += dt.y;
					}

					if (c)
					{
						decc = decc + dc;
					}

					decz += invdz;
					decw += invdw;
					
					decy -= ax;
					y += sy;
				}
				else
				{
					if (t)
					{
						dect.x += dt.x;
					}
				}
			}
		}
		else
		{
			// single step in y-direction
			for (int decx = ax - dy; ;y += sy, decx += ax)
			{
				edgeBuffer[y].X = x;

				if (n)
				{
					edgeBuffer[y].Normal = decn;
				}

				if (t)
				{
					edgeBuffer[y].TexCoords = dect;
				}

				if (c)
				{
					edgeBuffer[y].Color = decc;
				}

				edgeBuffer[y].InvZ = decz;
				edgeBuffer[y].InvW = decw;

				if (y == y1)
				{
					break;
				}

				if (n)
				{
					decn = decn + dn;
				}

				if (t)
				{
					dect.y += dt.y;
				}

				if (c)
				{
					decc = decc + dc;
				}

				decz += invdz;
				decw += invdw;

				if (decx >= 0)
				{
					decx -= ay;
					x += sx;
					if (t)
					{
						dect.x += dt.x;
					}
				}
			}
		}
	}

	void CRasterizer::DrawTriangle(Vector4f p[3], Vector3f n[3], Color c[3], Vector2f t[3])
	{
		int i0 = 0;
		int i1 = 1;
		int i2 = 2;
		//三角形退化为线
		if ((FLOAT_EQUAL(p[i0].y, p[i1].y) && FLOAT_EQUAL(p[i0].y, p[i2].y)) ||
			(FLOAT_EQUAL(p[i0].x, p[i1].x) && FLOAT_EQUAL(p[i0].x, p[i2].x)))
			return;

		//按y从小到大排序
		if (p[i1].y < p[i0].y)
		{
			Utils::Swap(i0, i1);
		}

		if (p[i2].y < p[i1].y)
		{
			Utils::Swap(i2, i1);
		}

		if (p[i1].y < p[i0].y)
		{
			Utils::Swap(i0, i1);
		}

		if (FLOAT_EQUAL(p[i0].y, p[i1].y))//bottom triangle
		{
			if (p[i1].x < p[i0].x)
			{
				DrawEdgeBuffer(i1, i2, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i0, i2, p, n, c, t, _pMaxEdgeBuffer);
			}
			else
			{
				DrawEdgeBuffer(i0, i2, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i1, i2, p, n, c, t, _pMaxEdgeBuffer);
			}
		}
		else if (FLOAT_EQUAL(p[i1].y, p[i2].y)) //top triangle
		{
			if (p[i1].x < p[i2].x)
			{
				DrawEdgeBuffer(i1, i0, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i2, i0, p, n, c, t, _pMaxEdgeBuffer);
			}
			else
			{
				DrawEdgeBuffer(i0, i2, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i0, i1, p, n, c, t, _pMaxEdgeBuffer);
			}
		}
		else
		{
			//p1点在扫描线位置与p0p2的交点x
			float newX = p[i0].x + (p[i2].x - p[i0].x) * (p[i1].y - p[i0].y) / (p[i2].y - p[i0].y);

			if (p[i1].x < newX)
			{
				DrawEdgeBuffer(i0, i1, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i1, i2, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i0, i2, p, n, c, t, _pMaxEdgeBuffer);
			}
			else
			{
				DrawEdgeBuffer(i0, i2, p, n, c, t, _pMinEdgeBuffer);
				DrawEdgeBuffer(i0, i1, p, n, c, t, _pMaxEdgeBuffer);
				DrawEdgeBuffer(i1, i2, p, n, c, t, _pMaxEdgeBuffer);
			}
		}


		int yMin =  MAX((int)p[i0].y, 0);
		int yMax = MIN((int)p[i2].y, _bufferHeight - 1);
		for (int y = yMin; y <= yMax; ++y)
		{
			EdgeBuffer &minEdge = _pMinEdgeBuffer[y];
			EdgeBuffer &maxEdge = _pMaxEdgeBuffer[y];

			unsigned int offset = (unsigned int)(MAX(minEdge.X, 0) + (y - 1) * _bufferWidth);
			unsigned int *addr = (unsigned int *)_pDrawBuffer + offset;
			if (_pDepthBuffer)
			{
				float *zbuffer = _pDepthBuffer + offset;
				if (_pSamplers)
				{
					FillColor(addr, zbuffer, minEdge, maxEdge);
				}
				else
				{
					FillColor(addr, zbuffer, minEdge, maxEdge);
				}
			}
			else
			{
				FillColor(addr, nullptr, minEdge, maxEdge);
			}
		}
	}
}