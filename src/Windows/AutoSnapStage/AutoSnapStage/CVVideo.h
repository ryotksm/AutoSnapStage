#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp> // videoio�̃w�b�_�[���C���N���[�h

//      Mat�^���������f�o�C�X�R���e�L�X�g�ɕϊ�����N���X
struct Mat2MemHDC {
	BITMAPINFO bmi;
	HBITMAP hbmp;
	BYTE *pBits;
	HDC memHDC;

	Mat2MemHDC() {
		pBits = 0;
	}
	~Mat2MemHDC() {
		if (pBits) {
			DeleteObject(hbmp);
			DeleteDC(memHDC);
		}
	}
	//      Mat�^�̉摜�ƃ������f�o�C�X�R���e�L�X�g�ɕϊ�����
	bool operator()(HDC hdc, cv::Mat img) {
		//      ������4�̔{���ɍ��킹��
		int sx = img.cols;
		if (sx % 4) {
			sx = (sx + 4) & 0xfffffffc;
		}
		if (pBits == NULL || (pBits && (sx != bmi.bmiHeader.biWidth || img.rows != bmi.bmiHeader.biHeight))) {
			DeleteObject(hbmp);
			DeleteDC(memHDC);
			bmi.bmiHeader.biSize = sizeof(bmi);
			bmi.bmiHeader.biWidth = sx;
			bmi.bmiHeader.biHeight = -img.rows;     //      �㉺���]
			bmi.bmiHeader.biBitCount = img.channels() * 8;

			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biCompression = BI_RGB;
			bmi.bmiHeader.biSizeImage = 0;
			bmi.bmiHeader.biXPelsPerMeter = 0;
			bmi.bmiHeader.biYPelsPerMeter = 0;
			bmi.bmiHeader.biClrUsed = 0;
			bmi.bmiHeader.biClrImportant = 0;

			hbmp = CreateDIBSection(NULL, &bmi, 0, (void**)&pBits, NULL, 0);
			if (pBits == NULL) {     //      �������s��
				return false;
			}
			memHDC = CreateCompatibleDC(hdc);
			SelectObject(memHDC, hbmp);
		}

		//              img�̉�����4�̔{���łȂ��ꍇ������̂ŁA1���C�����R�s�[����
		for (int y = 0; y < height(); y++) {
			memcpy(pBits + y * width()*img.channels(), img.data + y * img.cols*img.channels(), img.cols*img.channels());
			//      �E���̗]���𔒂ɂ���
			BYTE* p = pBits + (y*width() + img.cols)*img.channels();
			for (int x = img.cols; x < width(); x++) {
				for (int n = 0; n < img.channels(); n++) {
					*p++ = 0xff;
				}
			}
		}
		return true;
	}
	int width(void) {
		return bmi.bmiHeader.biWidth;
	}
	int height(void) {
		return -bmi.bmiHeader.biHeight;
	}
	void BitBlt(HDC hdc, int dx, int dy, DWORD rop) {
		::BitBlt(hdc, 0, 0, width(), height(), memHDC, dx, dy, rop);
	}
};

//      �r�b�g�}�b�v��Mat�^�ɕϊ�����N���X
struct MemHDC2Mat {
	cv::Mat* mat;
	int width, height;
	MemHDC2Mat() {
		mat = 0;
	}
	void operator()(HBITMAP hbmp) {
		BITMAP bmp;
		GetObject(hbmp, sizeof(bmp), &bmp);
		if (mat == 0 || (mat && (bmp.bmHeight != height || bmp.bmWidth != width))) {
			delete mat;
			mat = new cv::Mat(bmp.bmHeight, bmp.bmWidth, CV_8UC(bmp.bmBitsPixel / 8));
		}
		width = bmp.bmWidth;
		height = bmp.bmHeight;
		size_t sz = bmp.bmWidth*bmp.bmHeight*(bmp.bmBitsPixel / 8);
		memcpy(mat->data, bmp.bmBits, sz);
	}
	~MemHDC2Mat() {
		if (mat)
			delete mat;
	}
};
class CVVideo
{
public:
	cv::VideoCapture* cap;


	CVVideo();
	~CVVideo();

	void Init(HWND hWnd);
	void Capture(HWND hWnd);
	void Quit();

private:
	Mat2MemHDC mat2memHdc;
	MemHDC2Mat memHDC2Mat;
};

