/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdEnable.h"
#include "Simd/SimdMemory.h"
#include "Simd/SimdInit.h"
#include "Simd/SimdBgrToBgra.h"

namespace Simd
{
    namespace Base
    {
        void BgrToBgra(const uchar *bgr, size_t size, uchar *bgra, bool fillAlpha, bool lastRow)
        {
            if(fillAlpha)
            {
                for(size_t i = (lastRow ? 1 : 0); i < size; ++i, bgr += 3, bgra += 4)
                {
                    *(int32_t*)bgra = (*(int32_t*)bgr) | 0xFF000000;
                }
                if(lastRow)
                {
                    bgra[0] = bgr[0];
                    bgra[1] = bgr[1];
                    bgra[2] = bgr[2];
                    bgra[3] = 0xFF;
                }
            }
            else
            {
                for(size_t i = (lastRow ? 1 : 0); i < size; ++i, bgr += 3, bgra += 4)
                {
                    *(int32_t*)bgra = (*(int32_t*)bgr);
                }
                if(lastRow)
                {
                    bgra[0] = bgr[0];
                    bgra[1] = bgr[1];
                    bgra[2] = bgr[2];
                }
            }
        }

        void BgrToBgra(const uchar *bgr, size_t width, size_t height, size_t bgrStride, uchar *bgra, size_t bgraStride)
        {
            for(size_t row = 1; row < height; ++row)
            {
                BgrToBgra(bgr, width, bgra, true, false);
                bgr += bgrStride;
                bgra += bgraStride;
            }
            BgrToBgra(bgr, width, bgra, true, true);
        }
    }

	void BgrToBgra(const View & bgr, View & bgra)
	{
		assert(bgra.width == bgr.width && bgra.height == bgr.height);
		assert(bgra.format == View::Bgra32 && bgr.format == View::Bgr24);

		BgrToBgra(bgr.data, bgr.width, bgr.height, bgr.stride, bgra.data, bgra.stride);
	}
}