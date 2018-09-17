#include "stdafx.h"
#include "CVVideo.h"

#include <opencv2/highgui.hpp> // highgui�̃w�b�_�[���C���N���[�h
#include <iostream>

#define VIDEO_SOURCE "C:\\Users\\ryo_g\\Videos\\GPS�ƃZ���T�[��AI.mp4"

CVVideo::CVVideo()
{
	cap = new cv::VideoCapture();
}


CVVideo::~CVVideo()
{
}

void CVVideo::Init(HWND hWnd) {
	// �I�[�v�����Ă��Ȃ�������I�[�v������
	if (!cap->isOpened())
		//cap->open(VIDEO_SOURCE);
		cap->open(0);// open the default camera
	cv::Mat frame;
	(*cap) >> frame;
	if (!frame.empty()) {
		HDC hdc;
		hdc = GetDC(hWnd);
		mat2memHdc(hdc, frame);
		memHDC2Mat(mat2memHdc.hbmp);
	}
}

void CVVideo::Capture(HWND hWnd)
{
	// �I�[�v�����Ă��Ȃ���ΏI��
	if (!cap->isOpened())
		return;

	cv::Mat frame;
	(*cap) >> frame;
	if (!frame.empty()) {
		// bitmap�ɕϊ�
		HDC hdc;
		hdc = GetDC(hWnd);
		mat2memHdc(hdc, frame);
		memHDC2Mat(mat2memHdc.hbmp);
		mat2memHdc.BitBlt(hdc, 0, 0, SRCCOPY);
	}
}

void CVVideo::Quit() 
{
	cap->release();
}