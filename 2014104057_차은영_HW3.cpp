#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
using namespace std;

#define header_size 54
#define width 256
#define height 256

int Qtable[8 * 8] = { 16, 11, 10, 16, 24, 40, 51, 61,
					12, 12, 14, 19, 26, 58, 60, 55,
					14, 13, 16, 24, 40, 57, 69, 56,
					14, 17, 22, 29, 51, 87, 80, 63,
					18, 22, 37, 56, 68, 109, 103, 77,
					24, 35, 55, 64, 81, 104, 113, 92,
					49, 64, 78, 87, 103, 121, 120, 101,
					72, 92, 95, 98, 112, 100, 103, 99 };

void showHeaderInfo(char* input) {
	cout << "헤더 정보 :" << endl;
	cout << "filesize: " << *(int*)(input + 2) << endl;
	cout << "비트맵 시작 위치: " << *(int*)(input + 10) << endl;
	cout << "header_size: " << *(int*)(input + 14) << endl;
	cout << "Width: " << *(int*)(input + 18) << endl;
	cout << "height: " << *(int*)(input + 22) << endl;
	cout << "픽셀당 비트수: " << *(short*)(input + 28) << endl;
}

void showValue(unsigned char* input, int w, int h) {
	cout << endl;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << setw(5) << (int)input[i*w + j];
		}
		cout << endl;
	}
}

void DCT(unsigned char* input) {

}


int main()
{
	/*
	FILE *inputFile, *outFile; //gray image
	inputFile = fopen("Lena.bmp", "rb");
	if (inputFile == NULL) return 0;
	int size;
	fseek(inputFile, 0, SEEK_END);
	size = ftell(inputFile);
	rewind(inputFile);
	fread(input, 1, size, inputFile); //header
	for (int i = 0; i < header_size; i++) { header[i] = input[i]; }
	*/
	ifstream inputFile;
	inputFile.open("Lena.bmp", ios::binary);
	
	// 헤더 정보 받아오기
	char* header = new char[header_size];
	inputFile.read((char*)header, header_size);
	 
	showHeaderInfo(header); // 헤더 정보 출력
	
	// LUT 받아오기
	int imageStart = *(int*)(header + 10); //비트맵 시작 위치
	int image_size = width *height; // 이미지 사이즈
	int RGB_size = image_size * 3;
	int LUT_size = imageStart - header_size;
	char* LUT = new char[LUT_size];
	inputFile.read((char*)LUT, LUT_size);

	// data 받아오기
	unsigned char** RGB;
	unsigned char** RGB_out;
	unsigned char** R;
	unsigned char** out_gray;

	RGB = new unsigned char* [height];
	RGB_out = new unsigned char* [height];
	R = new unsigned char* [height]; // only data
	out_gray = new unsigned char* [height];

	for (int i = 0; i < height; i++) {
		RGB[i] = new unsigned char[width*3];
		RGB_out[i] = new unsigned char[width * 3];
		R[i] = new unsigned char[width];
		out_gray[i] = new unsigned char[width];
	}

	for (int i = 0; i < height; i++) {
		inputFile.read((char*)RGB[i], width*3);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0, jj = 0; j < width*3; jj++, j += 3) {
			R[i][jj] = RGB[i][j];
			//G[i][jj] = RGB[i][j+1];
			//B[i][jj] = RGB[i][j+2];
		}
	}

	


	
	//showValue(gray,width,height);
	// DCT
	//DCT(gray);





	 //저장
	for (int i = 0; i < height; i++) {
		for (int j = 0, jj = 0; j < width*3; jj++, j += 3) {
			RGB_out[i][j] = R[i][jj];
			RGB_out[i][j+1] = R[i][jj];
			RGB_out[i][j+2] = R[i][jj];
		}
	}
	
	

	//write
	//outFile = fopen("outLena.bmp", "wb");
	//fwrite(output, 1, size, outFile);
	ofstream outFile;
	outFile.open("out.bmp", ios::binary);
	outFile.write((char*)header, header_size);
	outFile.write((char*)LUT, LUT_size);
	for (int i = 0; i < height; i++) {
		outFile.write((char*)RGB_out[i], width*3);
	}
	
	cout << "complete!!" << endl;
	
	return 0;
}