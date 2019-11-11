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

void showHeaderInfo(unsigned char* input) {
	cout << "��� ���� :" << endl;
	cout << "filesize: " << *(int*)(input + 2) << endl;
	cout << "header_size: " << *(int*)(input + 14) << endl;
	cout << "��Ʈ�� ���� ��ġ: " << *(int*)(input + 10) << endl;
	cout << "Width: " << *(int*)(input + 18) << endl;
	cout << "height: " << *(int*)(input + 22) << endl;
	cout << "�ȼ��� ��Ʈ��: " << *(short*)(input + 28) << endl;
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
	FILE *inputFile, *outFile; //gray image
	unsigned char *header = new unsigned char[header_size];
	inputFile = fopen("Lena.bmp", "rb");
	if (inputFile == NULL) return 0;

	int size;
	fseek(inputFile, 0, SEEK_END);
	size = ftell(inputFile);
	rewind(inputFile);

	// ��� ���� �޾ƿ���
	unsigned char *input = new unsigned char[size]; //header + data
	unsigned char *output = new unsigned char[size];
	fread(input, 1, size, inputFile); //header + data;
	for (int i = 0; i < header_size; i++) { header[i] = input[i]; } 
	showHeaderInfo(header); // ��� ���� ���

	// data �޾ƿ���
	int imageStart = *(int*)(input + 10); //��Ʈ�� ���� ��ġ
	int image_size = size - imageStart; // �̹��� ������
	unsigned char *gray = new unsigned char[image_size]; // only data
	unsigned char *out_gray = new unsigned char[image_size];
	for (int i = imageStart,k=0; i < size;k++, i++) {gray[k] = input[i];}
	
	//showValue(gray,width,height);
	// DCT
	DCT(gray);







	 //����
	for (int i = 0; i < header_size; i++) { //Header
		output[i] = header[i];
	}
	for (int i = header_size; i < imageStart; i++) { //LUT
		output[i] = input[i];
	}
	for (int i = imageStart,k=0; i < size;k++, i++) { //data;
		output[i] = gray[k];
	}
	

	//write
	outFile = fopen("outLena.bmp", "wb");
	fwrite(output, 1, size, outFile);
	return 0;
}