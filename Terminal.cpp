#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <ratio>
#include <string>
#include <chrono>
#include <windows.h>
#include <gdiplus.h>
#include <opencv2/opencv.hpp>


#define c_max 100//caracter do texto
#define t_max 15//tempo maximo
#define u_max 45//caracter do usuario

#define getch _getch
#define kbhit _kbhit
#define sleep Sleep

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS //temp
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "gdiplus.lib")


using namespace std;
using namespace Gdiplus;
using namespace cv;


void menu();
void titulo();
void login(char op, char usuario[]);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
int Screen(int argc, wchar_t** argv);
int Webcam();
int salvar(char op, char texto[], char usuario[]);

int main(){
	char op;
	char conta_usuario[u_max];

	do {
		system("cls");
		titulo();
		//usuario
		cout << "Usuario: ";
		//scanf("%44s", str);
		cin >> setw(44) >> conta_usuario;

		system("cls");
		titulo();
		menu();

		op = getch();

		switch (op) {
			case '1':
				login(op,conta_usuario);
			break;

			case '2':
				login(op, conta_usuario);
			break;

			case '3':
				login(op, conta_usuario);
			break;

			default:
				cout << "\a\aOpcao invalida";
				getch();
			break;


		}
	} while (1<3);
	
	
	getch();
	return 0;
}

void menu() {
	cout << "1- Patrulhamento\n";
	cout << "2- Almoco no refeitorio\n";
	cout << "3- Escolta de prisioneiro\n\n";
	cout << "Escolha um das opcoes: ";
}

void titulo() {
	char titulo[] = "TERMINAL ESTELAR\n";
	char linha_titulo[] = "==================";
	printf("%s\n%s%s\n\n", linha_titulo, titulo, linha_titulo);
}



void login(char op, char usuario[]) {
	using namespace chrono;
	
	int c_i = 0;
	char c;
	double num = 0;

	char esgotado = '4';

	char esc = 27;
	char enter = 13;
	char backspace = 8;
	char space = 32;
	
	char texto[c_max];
	
	char s_end[]="db";

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	num = time_span.count();

	texto[0] = '\0';
	system("cls");
	titulo();
	
	switch (op) {
		case '1'://patrulhamento
			cout << "Justificativa: ";
			while (num<t_max) {//update*
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
				num = time_span.count();
				if (kbhit()) {

					c = getch();// ler o caracter
								//apagar
					if ((c == backspace) && (c_i>0)) {

						putchar(c);
						putchar(space);
						putchar(backspace);
						texto[c_i--];
					}
					else if (c == enter) {//inseriu a tempo
						salvar(op,texto,usuario);
						break;
					}
					//entrada do valor
					else if ((c_i < c_max - 1) && (c_i >= 0) && (c != backspace)) {
						putchar(c);
						texto[c_i++] = c;
						texto[c_i] = '\0';


					}
					//sinal sonoro de limite maximo de caracter
					else if (c_i >= c_max - 1) {
						printf("\a");
					}


					if ((c == esc) && (c_i<c_max)) {//
						printf("\n Processo interrompido");
						Sleep(1000);
						break;
					}
				}
			}
			if (num >= t_max) {
				texto[0] = '\0';
				salvar(esgotado, texto,usuario);
			}
		break;
		
		case '2'://Almoco
			salvar(op,texto,usuario);
		break;

		case '3'://Escolta
			salvar(op, texto,usuario);
		break;

		default:
			return;
		break;
	}

	
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid){
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

int Screen(int argc, wchar_t** argv){
	
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	HWND desktop = GetDesktopWindow();
	HDC desktopdc = GetDC(desktop);
	HDC mydc = CreateCompatibleDC(desktopdc);
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	HBITMAP mybmp = CreateCompatibleBitmap(desktopdc, width, height);
	HBITMAP oldbmp = (HBITMAP)SelectObject(mydc, mybmp);
	BitBlt(mydc, 0, 0, width, height, desktopdc, 0, 0, SRCCOPY | CAPTUREBLT);
	SelectObject(mydc, oldbmp);

	const wchar_t* filename = (argc > 1) ? argv[1] : L"screen.png";
	Bitmap* b = Bitmap::FromHBITMAP(mybmp, NULL);
	CLSID  encoderClsid;
	Status stat = GenericError;
	if (b && GetEncoderClsid(L"image/png", &encoderClsid) != -1) {
		stat = b->Save(filename, &encoderClsid, NULL);
	}
	if (b)
		delete b;

	// cleanup
	GdiplusShutdown(gdiplusToken);
	ReleaseDC(desktop, desktopdc);
	DeleteObject(mybmp);
	DeleteDC(mydc);

	system("move /Y screen.png db\\img");
	return stat == Ok;
}

int Webcam(){
	int ct = 0;
	char tipka;
	char filename[100]; // For filename
	int  c = 1; // For filename
	
	Mat frame;
	//--- INICIO CAPTURA VIDEO
	VideoCapture cap;
	// ABRE A CAMER PADRÃO USANDO API PADRÃO
	cap.open(0);
	// OU AVANÇADO: SELECIONANDO ALGUMA API BACKEND
	int deviceID = 0;             // 0 = CAMERA PADRÃO
	int apiID = cv::CAP_ANY;      // 0 = API PADRÃO
								  // ABRE A CAMERA USANDO API SELECIONADA
	cap.open(deviceID + apiID);
	// CHECANDO 
	if (!cap.isOpened()) {
		cerr << "\a\aERRO! Nao foi possivel abrir a camera\n";
		//return -1;
		return 0;
	}
	
	
	for (;;){
		cap.read(frame);

		if (frame.empty()) {
			cerr << "ERRO! Quadro em branco\n";
			//return -1;
			return 0;
			break;
		}

		Sleep(5);
		//aguarda uma entrada com tempo limite suficiente para mostrar imagens
		//imshow("CAMERA 1", frame);  // Janela com a webcam

		//tipka = cv::waitKey(30); //uso manual
		tipka = 'q';//caputar
		if (tipka == 'q') {

			sprintf_s(filename, "Webcam_%d.jpg", c); // selecione a sua pasta
			cv::waitKey(10);

			//imshow("CAMERA 1", frame);
			imwrite(filename, frame);
			//cout << "Webcam_" << c << endl;
			//c++; //não é necessário agora
			tipka = 'a';
		}


		if (tipka == 'a') {
			system("move /Y Webcam_1.jpg db/img");
			
			Sleep(1500);
			break;
		}


	}
	return 1;
}

int salvar(char op, char texto[], char usuario[]){
	int w_save;
	int s_save;

	char name_file[40];
	char num_char[20];

	FILE *arq;

	//ac_master
	char op_aux[3];
	op_aux[0] = op;
	op_aux[1] = '\0';

	//ac
	char nome_arquivo[] = "db\\db.txt";
	char criar_pasta_db[] = "mkdir db";
	char abrir_pasta_db[] = "cd db";
	char voltar_pasta[] = "cd ..";
	char criar_pasta_img[] = "mkdir db\\img";
	char abrir_pasta_img[] = "cd img";
	char comando[75];

	system(criar_pasta_db);
	//system(abrir_pasta_db);
	system(criar_pasta_img);
	//system(voltar_pasta);
	system("cls");

	char Linha[100];
	char *result;
	int i = 0;
	

	//[estrutura usuario - opcao - justificativa - end/webcam - end/screen
	if ((arq = fopen(nome_arquivo, "a")) == NULL) {//read - adapt
		printf("\a\aErro no arquivo!!!!! Chame logo o Almirante.");
		sleep(2000);
		exit(1);
	}
	fclose(arq);
	
	arq = fopen(nome_arquivo, "rt");
	while (!feof(arq)) {
		result = fgets(Linha, 100, arq);
		i++;
	}
	sprintf(num_char, "%d", i);//convert
	fclose(arq);//close

				//[estrutura usuario - opcao - justificativa - end/webcam - end/screen
	if ((arq = fopen(nome_arquivo, "a")) == NULL) {//read - adapt
		printf("\a\aErro no arquivo!!!!! Chame logo o Almirante.");
		sleep(2000);
		exit(1);
	}
	

	//name file
	strcpy_s(name_file, op_aux);
	strcat_s(name_file, "_");
	strcat_s(name_file, usuario);
	strcat_s(name_file, "_");
	strcat_s(name_file, num_char);
	
	//system(abrir_pasta_db);
	//system(abrir_pasta_img);
	//cout << "parou";  getch();

	switch (op) {

		case '1'://usuario + op + justificativa
			fprintf(arq, "%s\t%c\t%s\tNULL\tNULL\n", usuario, op, texto);
		break;

		case '2'://usuario + op
			fprintf(arq, "%s\t%c\tNULL\tNULL\tNULL\n", usuario,op);
		break;

		case '3'://usuario + op
			fprintf(arq, "%s\t%c\tNULL\tNULL\tNULL\n", usuario, op);
		break;

		case '4'://usuario + op + justificativa(t) = webcam || screen

			if (w_save = Webcam()) {//webcam
									//ren file webcam 
									//num_char
				strcpy_s(comando, "ren db\\img\\Webcam_1.jpg ");
				strcat_s(name_file, ".jpg");
				strcat_s(comando, name_file);
				//chamar o system
				system(comando);
				getch();
				//save
				fprintf(arq, "%s\t%c\tNULL\t%s\tNULL\n", usuario, op, name_file);
			}
			else if (s_save = Screen(0, 0)) {
				//ren file screen
				strcpy_s(comando, "ren db\\img\\screen.png ");
				strcat_s(name_file, ".png");
				strcat_s(comando, name_file);
				system(comando);
				fprintf(arq, "%s\t%c\tNULL\tNULL\t%s\n", usuario, op, name_file);
			}
			else {
				cout << "\a\a Erro! Por favor, chame o Almirante" << endl;
				Sleep(2000);
				return 0;
			}

			break;

		default:
			cout << "ERRO!!!\a\a Chame o Almirante, rápido!!\a\a";
			sleep(2000);
		break;
	}




	//db file
	//folder db
	//folder image
	fclose(arq);
	return 1;
}
