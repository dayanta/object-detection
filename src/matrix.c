#include "definitions.h"

typedef struct _CvMat_RGB
{
	CvMat *b;
	CvMat *g;
	CvMat *r;
} CvMat_RGB;

typedef struct _CvMatk
void empirical_mean(double *src, int width, int height, int step, int channels)
{
	int i, j, k;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			for(k = 0; k < channels; k++)
			{
				src[i*step+j*channels+k] += (double)src[i*step+j*channels+k] / (double)width; 
			}
		}
	}
}

void deviation(unsigned char *src, double *u, int width, int height, int step, int channels)
{
	int i, j, k;

	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			for(k = 0; k < channels; k++)
			{			
				src[i*step+j*channels+k] = src[i*step+j*channels+k] -  (int)u[i*channels+k]; 
			}
		}
	}	
}

void covariance_matrix(CvMat *src, CvMat *dest, int height, int width, int channels)
{
	if(channels == 1)
	{
		cvMulTransposed(src, dest, NULL, 1.0/(double)width);	
	}
	else if(channels == 3)
	{
		CvMat_RGB src_rgb;
		CvMat_RGB dest_rgb;

		src_rgb.b = cvCreateMat(height, width, CV_8UC1);
		src_rgb.r = cvCreateMat(height, width, CV_8UC1);
		src_rgb.g = cvCreateMat(height, width, CV_8UC1);
		
		cvSplit(src, src_rgb.b, src_rgb.g, src_rgb.r, 0);

		dest_rgb.b = cvCreateMat(height, height, CV_32FC1);
		dest_rgb.g = cvCreateMat(height, height, CV_32FC1);
		dest_rgb.r = cvCreateMat(height, height, CV_32FC1);
		
		cvMulTransposed(src_rgb.b, dest_rgb.b, NULL, 1.0/(double)width);
		cvMulTransposed(src_rgb.g, dest_rgb.g, NULL, 1.0/(double)width);
		cvMulTransposed(src_rgb.r, dest_rgb.r, NULL, 1.0/(double)width);

		cvMerge(dest_rgb.b, dest_rgb.g, dest_rgb.r, 0, dest);
	}
	else
	{
		printf("Channel is not supported\n");
		exit(0);
	}	
}

void eigen_vv(CvMat *src, CvMat *eigen_vec, CvMat *eigen_val, int height, int channels)
{
	if(channels == 1)
	{
		cvSVD(src, eigen_vec, eigen_val, NULL, CV_SVD_U_T);
	}
	if(channels == 3)
	{
		CvMat_RGB src_rgb;
		CvMat_RGB eigen_vec_rgb;
		CvMat_RGB eigen_val_rgb:
	
		src_rgb.b = cvCreateMat(height, width, CV_8UC1);
		src_rgb.r = cvCreateMat(height, width, CV_8UC1);
		src_rgb.g = cvCreateMat(height, width, CV_8UC1);
					
		cvSplit(src, src_rgb.b, src_rgb.g, src_rgb.r, 0);

		eigen_vec_rgb.b = cvCreateMat(height, height, CV_32FC1);
		eigen_vec_rgb.g = cvCreateMat(height, height, CV_32FC1);
		eigen_vec_rgb.r = cvCreateMat(height, height, CV_32FC1);
							
		eigen_val_rgb.b = cvCreateMat(height, 1, CV_32FC1);
		eigen_val_rgb.g = cvCreateMat(height, 1, CV_32FC1);
		eigen_val_rgb.r = cvCreateMat(height, 1, CV_32FC1);
		
		cvSVD(src_rgb.b, eigen_vec_rgb.b, eigen_val_rgb.b, NULL, CV_SVD_U_T);
		cvSVD(src_rgb.r, eigen_vec_rgb.r, eigen_val_rgb.r, NULL, CV_SVD_U_T);
		cvSVD(src_rgb.g, eigen_vec_rgb.g, eigen_val_rgb.g, NULL, CV_SVD_U_T);
		
		cvMerge(eigen_vec_rgb.b, eigen_vec_rgb.r, eigen_vec_rgb.g, 0, eigen_vec);
		cvMerge(eigen_val_rgb.b, eigen_val_rgb.r, eigen_val_rgb.g, 0, eigen_val);	
	}
	else
	{
		printf("Number of channels not supported");
	}
}
