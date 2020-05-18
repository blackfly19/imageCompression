#include <bits/stdc++.h>
#include "kmeans.hpp"
#include <opencv2/opencv.hpp>
#define K 64
using namespace cv;
using namespace std;

void reshape_comp(Mat image,vector<float> img_res[])
{
	int cnt = 0;
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			Vec3b pixel = image.at<Vec3b>(i,j);
			img_res[cnt].push_back(pixel[0]);
			img_res[cnt].push_back(pixel[1]);
			img_res[cnt].push_back(pixel[2]);
			cnt++;
		}
	}
}
void reshape_decomp(Mat &image,vector<int>pred,int rows,int cols)
{
	int cnt = 0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			image.at<Vec3b>(i,j)[0] = pred[cnt];
			image.at<Vec3b>(i,j)[1] = pred[cnt];
			image.at<Vec3b>(i,j)[2] = pred[cnt];
			cnt++;
		}
	}
}
void compress(vector<float>img[],string name,int rows,int cols)
{
	string file = name+".txt";
	KMeans kmeans(K);
	fstream Compress;
	Mat compressed_img(rows,cols,CV_8UC(3),Scalar::all(0));

	Compress.open(file,ios::out);
	kmeans.fit(img,rows*cols);
	kmeans.predict(img);

	vector<float> *centroids = kmeans.getCentroids();
	vector<int> pred = kmeans.getPredictions();

	for(int i=0;i<K;i++)
	{
		for(int j=0;j<3;j++)
			Compress<<centroids[i].at(j)<<" ";
		Compress<<"\n";
	}
	reshape_decomp(compressed_img,pred,rows,cols);
	imwrite(name+"_compress.png",compressed_img);
	Compress.close();
}
void decompress(string file)
{
	vector<float> centroids[K];
	float word;
	string file_ext = file+".txt";
	fstream Decompress;
	Decompress.open(file_ext.c_str(),ios::in);

	Mat compressed_img = imread(file+"_compress.png",IMREAD_COLOR);
	Mat reconstruct(compressed_img.rows,compressed_img.cols,CV_8UC3,Scalar::all(0));
	for(int i=0;i<K;i++)
	{
		for(int j=0;j<3;j++)
		{
			Decompress >> word;
			centroids[i].push_back(word);
		}
	}
	for(int i=0;i<compressed_img.rows;i++)
	{
		for(int j=0;j<compressed_img.cols;j++)
		{
			int val = compressed_img.at<Vec3b>(i,j)[0];
			reconstruct.at<Vec3b>(i,j)[0] = centroids[val].at(0);
			reconstruct.at<Vec3b>(i,j)[1] = centroids[val].at(1);
			reconstruct.at<Vec3b>(i,j)[2] = centroids[val].at(2);
		}
	}
	imwrite(file+"_recovered.png",reconstruct);
	Decompress.close();
}
int main(int argc,char **argv)
{
	char *name = argv[2];
	char *function = argv[1];
	if(strcmp(function,"compress") == 0)
	{
		Mat original;
		string name_ren(name);
		original = imread(name,IMREAD_COLOR);
		int rows = original.rows;
		int cols = original.cols;
		vector<float>img_res[rows*cols];
		int dot = name_ren.find(".");
		name_ren.resize(dot);
		reshape_comp(original,img_res);
		compress(img_res,name_ren,rows,cols);
	}
	else
	if(strcmp(function,"decompress") == 0)
	{
		string name_ren(name);
		int dot = name_ren.find(".");
		name_ren.resize(dot);
		decompress(name_ren);
	}
}
