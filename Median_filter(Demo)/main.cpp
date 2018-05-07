#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include<ctime> 

using namespace cv;

void cvMedianFilter(const Mat &src, Mat &dst, int n);
uchar  Median(uchar n1, uchar n2, uchar n3,
	uchar n4, uchar n5, uchar n6,
	uchar n7, uchar n8, uchar n9);
void salt(Mat &image, int num);


int main(int argc, char** argv)
{
	//声明IplImage指针
	IplImage* pImg = NULL;
	IplImage* pDealImg = NULL;
	IplImage* pSubImg = NULL;
	Mat mDealImg ;

	pImg = cvLoadImage("F:\\C++code\\OpenCV\\Median_filter(Demo)\\1.jpg", -1);
	int n = pImg->nChannels;
	pDealImg = cvCreateImage(
		cvGetSize(pImg),   //获得输入图片的大小，并进行创建，也可以使用cvSize（）  
		pImg->depth,
		pImg->nChannels
	);
	pSubImg = cvCreateImage(
		cvGetSize(pImg),
		pImg->depth,
		pImg->nChannels
		);

	//图像处理


	//撒盐处理
	Mat Salt_Image =cvarrToMat(pImg);
	salt(Salt_Image, 3000);
	*pImg = IplImage(Salt_Image);


	//滤波处理
	cvSmooth(pImg, pDealImg, CV_MEDIAN, 3);
// 	Mat mImg = cvarrToMat(pImg);
// 	cvMedianFilter(Salt_Image, mDealImg,n);//传递原图，目标图，通道数
// 	
// 	*pDealImg = IplImage(mDealImg);

	//图像做差
	cvSub(pImg,pDealImg,pSubImg);

	//创建窗口
	cvNamedWindow("src", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("deal", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Sub", CV_WINDOW_AUTOSIZE);


	//显示图像
	cvShowImage("src", pImg);
	cvShowImage("deal", pDealImg);
	cvShowImage("Sub", pSubImg);

	cvWaitKey(0); //等待按键

	//销毁窗口
	cvDestroyWindow("src");
	cvDestroyWindow("deal");
	cvDestroyWindow("Sub");

	//释放图像
	cvReleaseImage(&pImg);
	cvReleaseImage(&pDealImg);
	cvReleaseImage(&pSubImg);


	return 0;
}


void cvMedianFilter(const Mat &src, Mat &dst,int n)
{
	if (!src.data)return;
	Mat _dst(src.size(), src.type());
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {
				for (int k = 0; k < n; k++)//各通道滤波
				{
					_dst.at<Vec3b>(i, j)[k] = Median(src.at<Vec3b>(i, j)[k], src.at<Vec3b>(i + 1, j + 1)[k],
						src.at<Vec3b>(i + 1, j)[k], src.at<Vec3b>(i, j + 1)[k], src.at<Vec3b>(i + 1, j - 1)[k],
						src.at<Vec3b>(i - 1, j + 1)[k], src.at<Vec3b>(i - 1, j)[k], src.at<Vec3b>(i, j - 1)[k],
						src.at<Vec3b>(i - 1, j - 1)[k]);
				}
			}
			else
				_dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
		}
		_dst.copyTo(dst);
	}
}

unsigned char  Median(unsigned char n1, unsigned char n2, unsigned char n3,
		unsigned char n4, unsigned char n5, unsigned char n6,
		unsigned char n7, unsigned char n8, unsigned char n9) 
	{
	unsigned char arr[9] = {0};
	arr[0] = n1;
	arr[1] = n2;
	arr[2] = n3;
	arr[3] = n4;
	arr[4] = n5;
	arr[5] = n6;
	arr[6] = n7;
	arr[7] = n8;
	arr[8] = n9;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8 - i; j++)
			if (arr[j] > arr[j + 1])
			{
				unsigned char temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
	return arr[4];
	
}

void salt(Mat &image, int num) {  //撒盐算法
	if (!image.data) return;//防止传入空图  
	int i, j;
	srand(time(NULL));
	for (int x = 0; x < num; ++x) {
		i = rand() % image.rows;
		j = rand() % image.cols;
		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}
}

