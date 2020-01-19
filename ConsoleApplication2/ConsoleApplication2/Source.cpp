#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <conio.h>

using namespace cv;
using namespace std;

bool flagGunung = false, flagPantai = false, flagKota = false;

//histogram gunung
int histogramRGBmin[3][255]; //rgb total 6 gambar
int histogramRGBmax[3][255];

//histogram pantai
int histogramRGBPantaimin[3][255]; //rgb total 6 gambar
int histogramRGBPantaimax[3][255];

//histogram kota
int histogramRGBKotamin[3][255]; //rgb total 6 gambar
int histogramRGBKotamax[3][255];

int histogramRGBtampung[3][255]; //rgb 

void cekHistogram(){
	int x = 50;
	printf("Range untuk histogram gunung: \n");
	printf("max(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBmax[0][x], histogramRGBmax[1][x], histogramRGBmax[2][x]);
	printf("min(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBmin[0][x], histogramRGBmin[1][x], histogramRGBmin[2][x]);
	printf("Range untuk histogram pantai: \n");
	printf("max(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBPantaimax[0][x], histogramRGBPantaimax[1][x], histogramRGBPantaimax[2][x]);
	printf("min(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBPantaimin[0][x], histogramRGBPantaimin[1][x], histogramRGBPantaimin[2][x]);
	printf("Range untuk histogram kota : \n");
	printf("max(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBKotamax[0][x], histogramRGBKotamax[1][x], histogramRGBKotamax[2][x]);
	printf("min(r,g,b) indeks ke-%d saja : (%d,%d,%d)\n", x, histogramRGBKotamin[0][x], histogramRGBKotamin[1][x], histogramRGBKotamin[2][x]);
}

void clearHistogram(){
	int i=0;
	while(i<255){
		histogramRGBmin[0][i] = 0;
		histogramRGBmin[1][i] = 0;
		histogramRGBmin[2][i] = 0;
		histogramRGBmax[0][i] = 0;
		histogramRGBmax[1][i] = 0;
		histogramRGBmax[2][i] = 0;
		i++;
	}
	i=0;
	while(i<255){
		histogramRGBPantaimin[0][i] = 0;
		histogramRGBPantaimin[1][i] = 0;
		histogramRGBPantaimin[2][i] = 0;
		histogramRGBPantaimax[0][i] = 0;
		histogramRGBPantaimax[1][i] = 0;
		histogramRGBPantaimax[2][i] = 0;
		i++;
	}
	i=0;
	while(i<255){
		histogramRGBKotamin[0][i] = 0;
		histogramRGBKotamin[1][i] = 0;
		histogramRGBKotamin[2][i] = 0;
		histogramRGBKotamax[0][i] = 0;
		histogramRGBKotamax[1][i] = 0;
		histogramRGBKotamax[2][i] = 0;
		i++;
	}
}

void cariHistogramGunung(int maksi, int maksj, Mat pemandangan){
	int i=0,j=0;
	int r=0,g=0,b=0;
	while(i<255){
		histogramRGBtampung[0][i] = 0;
		histogramRGBtampung[1][i] = 0;
		histogramRGBtampung[2][i] = 0;
		i++;
	}
	i = j = 0;
	while(j<maksj){ //mencacah x
		while(i<maksi){ //mencacah y
			Vec3b cariWarna = pemandangan.at<Vec3b>(j, i);
			b = cariWarna.val[0];  //biru
			g = cariWarna.val[1]; //hijau
			r = cariWarna.val[2]; //merah
			//printf("(x,y) = (%d,%d) ",i,j);
			//printf("(r,g,b) = (%d,%d,%d)  \n",r,g,b);
			histogramRGBtampung[0][r]++;
			histogramRGBtampung[1][g]++;
			histogramRGBtampung[2][b]++;
			if(flagGunung == false){
				histogramRGBmax[0][r] = histogramRGBtampung[0][r]+1;
				histogramRGBmax[1][g] = histogramRGBtampung[1][g]+1;
				histogramRGBmax[2][b] = histogramRGBtampung[2][b]+1;
				histogramRGBmin[0][r] = histogramRGBtampung[0][r]-1;
				histogramRGBmin[1][g] = histogramRGBtampung[1][g]-1;
				histogramRGBmin[2][b] = histogramRGBtampung[2][b]-1;
			}
			//printf("histogramRGBtampung[0][%d] : %d \n",r,histogramRGBtampung[0][r]);
			//printf("histogramRGBtampung[1][%d] : %d \n",g,histogramRGBtampung[1][g]);
			//printf("histogramRGBtampung[2][%d] : %d \n\n",b,histogramRGBtampung[2][b]);
			i++;
		}
		i=0;
		j++;
	}
	//printf("\n");
	//printf("Size gambar (x,y) : (%d,%d)\n",maksi,maksj);
	i = j = 0;
	if(flagGunung == true){
		//tetap ulang max
		while(i<255){
			if(histogramRGBtampung[0][i] > histogramRGBmax[0][i]){
				histogramRGBmax[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] > histogramRGBmax[1][i]){
				histogramRGBmax[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] > histogramRGBmax[2][i]){
				histogramRGBmax[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		} 
		i = j = 0;
		//tetap ulang min
		while(i<255){
			if(histogramRGBtampung[0][i] < histogramRGBmin[0][i]){
				histogramRGBmin[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] < histogramRGBmin[1][i]){
				histogramRGBmin[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] < histogramRGBmin[2][i]){
				histogramRGBmin[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		}
		flagGunung = false;
	}
	flagGunung = true;
}

void cariHistogramPantai(int maksi, int maksj, Mat pemandangan){
	int i=0,j=0;
	int r=0,g=0,b=0;
	while(i<255){
		histogramRGBtampung[0][i] = 0;
		histogramRGBtampung[1][i] = 0;
		histogramRGBtampung[2][i] = 0;
		i++;
	}
	i = j = 0;
	while(j<maksj){ //mencacah x
		while(i<maksi){ //mencacah y
			Vec3b cariWarna = pemandangan.at<Vec3b>(j, i);
			b = cariWarna.val[0];
			g = cariWarna.val[1];
			r = cariWarna.val[2];
			histogramRGBtampung[0][r]++;
			histogramRGBtampung[1][g]++;
			histogramRGBtampung[2][b]++;
			if(flagPantai == false){
				histogramRGBPantaimax[0][r] = histogramRGBtampung[0][r]+1;
				histogramRGBPantaimax[1][g] = histogramRGBtampung[1][g]+1;
				histogramRGBPantaimax[2][b] = histogramRGBtampung[2][b]+1;
				histogramRGBPantaimin[0][r] = histogramRGBtampung[0][r]-1;
				histogramRGBPantaimin[1][g] = histogramRGBtampung[1][g]-1;
				histogramRGBPantaimin[2][b] = histogramRGBtampung[2][b]-1;
			}
			i++;
		}
		i=0;
		j++;
	}
	i = j = 0;
	if(flagPantai == true){
		//tetap ulang max
		while(i<255){
			if(histogramRGBtampung[0][i] > histogramRGBPantaimax[0][i]){
				histogramRGBPantaimax[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] > histogramRGBPantaimax[1][i]){
				histogramRGBPantaimax[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] > histogramRGBPantaimax[2][i]){
				histogramRGBPantaimax[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		} 
		i = j = 0;
		//tetap ulang min
		while(i<255){
			if(histogramRGBtampung[0][i] < histogramRGBPantaimin[0][i]){
				histogramRGBPantaimin[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] < histogramRGBPantaimin[1][i]){
				histogramRGBPantaimin[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] < histogramRGBPantaimin[2][i]){
				histogramRGBPantaimin[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		}
		flagPantai = false;
	}
	flagPantai = true;
}

void cariHistogramKota(int maksi, int maksj, Mat pemandangan){
	int i=0,j=0;
	int r=0,g=0,b=0;
	while(i<255){
		histogramRGBtampung[0][i] = 0;
		histogramRGBtampung[1][i] = 0;
		histogramRGBtampung[2][i] = 0;
		i++;
	}
	i = j = 0;
	while(j<maksj){ //mencacah x
		while(i<maksi){ //mencacah y
			Vec3b cariWarna = pemandangan.at<Vec3b>(j, i);
			b = cariWarna.val[0];
			g = cariWarna.val[1];
			r = cariWarna.val[2];
			histogramRGBtampung[0][r]++;
			histogramRGBtampung[1][g]++;
			histogramRGBtampung[2][b]++;
			if(flagKota == false){
				histogramRGBKotamax[0][r] = histogramRGBtampung[0][r]+1;
				histogramRGBKotamax[1][g] = histogramRGBtampung[1][g]+1;
				histogramRGBKotamax[2][b] = histogramRGBtampung[2][b]+1;
				histogramRGBKotamin[0][r] = histogramRGBtampung[0][r]-1;
				histogramRGBKotamin[1][g] = histogramRGBtampung[1][g]-1;
				histogramRGBKotamin[2][b] = histogramRGBtampung[2][b]-1;
			}
			i++;
		}
		i=0;
		j++;
	}
	i = j = 0;
	if(flagKota == true){
		//tetap ulang max
		while(i<255){
			if(histogramRGBtampung[0][i] > histogramRGBKotamax[0][i]){
				histogramRGBPantaimax[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] > histogramRGBKotamax[1][i]){
				histogramRGBKotamax[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] > histogramRGBKotamax[2][i]){
				histogramRGBKotamax[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		} 
		i = j = 0;
		//tetap ulang min
		while(i<255){
			if(histogramRGBtampung[0][i] < histogramRGBKotamin[0][i]){
				histogramRGBKotamin[0][i] = histogramRGBtampung[0][i]; 
			}
			if(histogramRGBtampung[1][i] < histogramRGBKotamin[1][i]){
				histogramRGBKotamin[1][i] = histogramRGBtampung[1][i]; 
			}
			if(histogramRGBtampung[2][i] < histogramRGBKotamin[2][i]){
				histogramRGBKotamin[2][i] = histogramRGBtampung[2][i]; 
			}
			i++;
		}
		flagKota = false;
	}
	flagKota = true;
}

void bacaGunung(){
	int x = 0,y = 0;
	Mat gunung[6];
	gunung[0] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\a.jpg");
	gunung[1] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\b.jpg");
	gunung[2] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\c.jpg");
	gunung[3] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\d.jpg");
	gunung[4] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\e.jpg");
	gunung[5] = imread("D:\\Computer Vision\\Praktikum 1\\gunung hijau\\f.jpg");
	int i=0;
	while(i<6){
		x = gunung[i].size().width;
		y = gunung[i].size().height;
		cariHistogramGunung(x,y,gunung[i]);
		//printf("Gunung ke-%d berhasil dibaca\n",i);
		//cekHistogram(); //cek histogram berbasis text
		//imshow("test",gunung[i]);
		//waitKey();
		i++;
	}
}

void bacaPantai(){
	int x = 0,y = 0;
	Mat pantai[6];
	pantai[0] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\a.jpg");
	pantai[1] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\b.jpg");
	pantai[2] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\c.jpg");
	pantai[3] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\d.jpg");
	pantai[4] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\e.jpg");
	pantai[5] = imread("D:\\Computer Vision\\Praktikum 1\\pantai\\f.jpg");
	int i=0;
	while(i<6){
		x = pantai[i].size().width;
		y = pantai[i].size().height;
		cariHistogramPantai(x,y,pantai[i]);
		i++;
	}
}

void bacaKota(){
	int x = 0,y = 0;
	Mat Kota[6];
	Kota[0] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\a.jpg");
	Kota[1] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\b.jpg");
	Kota[2] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\c.jpg");
	Kota[3] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\d.jpg");
	Kota[4] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\e.jpg");
	Kota[5] = imread("D:\\Computer Vision\\Praktikum 1\\kota\\f.jpg");
	int i=0;
	while(i<6){
		x = Kota[i].size().width;
		y = Kota[i].size().height;
		cariHistogramKota(x,y,Kota[i]);
		i++;
	}
}

void cekPemandangan(Mat pemandangan, int maksi, int maksj){
	int i = 0, j = 0;
	while(i<255){
		histogramRGBtampung[0][i] = 0;
		histogramRGBtampung[1][i] = 0;
		histogramRGBtampung[2][i] = 0;
		i++;
	}
	i = j = 0;
	int r = 0, g = 0, b = 0;
	while(j<maksj){ //mencacah x
		while(i<maksi){ //mencacah y
			Vec3b cariWarna = pemandangan.at<Vec3b>(j, i);
			b = cariWarna.val[0];  //biru
			g = cariWarna.val[1]; //hijau
			r = cariWarna.val[2]; //merah
			histogramRGBtampung[0][r]++;
			histogramRGBtampung[1][g]++;
			histogramRGBtampung[2][b]++;
			i++;
		}
		i=0;
		j++;
	}
	//cek gunung
	i = j = 0;
	int kecocokanHijau = 0, kecocokanMerah = 0, kecocokanBiru = 0;
	int hasil1 = 0, hasil2 = 0, hasil3 = 0;
	while(i<255){
		if(histogramRGBtampung[0][i] >= histogramRGBmin[0][i] && histogramRGBtampung[0][i] >= histogramRGBmin[0][i]){
			kecocokanMerah++;
		}
		if(histogramRGBtampung[1][i] <= histogramRGBmax[1][i] && histogramRGBtampung[1][i] >= histogramRGBmin[1][i]){
			kecocokanHijau++;
		}
		if(histogramRGBtampung[2][i] >= histogramRGBmin[2][i] && histogramRGBtampung[2][i] >= histogramRGBmin[2][i]){
			kecocokanBiru++;
		}
		i++;
	}
	hasil1 = kecocokanMerah + kecocokanHijau + kecocokanBiru;
	//cek pantai
	i = j = 0;
	kecocokanHijau = 0, kecocokanMerah = 0, kecocokanBiru = 0;
	while(i<255){
		if(histogramRGBtampung[0][i] >= histogramRGBPantaimin[0][i] && histogramRGBtampung[0][i] >= histogramRGBPantaimin[0][i]){
			kecocokanMerah++;
		}
		if(histogramRGBtampung[1][i] <= histogramRGBPantaimax[1][i] && histogramRGBtampung[1][i] >= histogramRGBPantaimin[1][i]){
			kecocokanHijau++;
		}
		if(histogramRGBtampung[2][i] >= histogramRGBPantaimin[2][i] && histogramRGBtampung[2][i] >= histogramRGBPantaimin[2][i]){
			kecocokanBiru++;
		}
		i++;
	}
	hasil2 = kecocokanMerah + kecocokanHijau + kecocokanBiru;
	//cek kota

	i = j = 0;
	kecocokanHijau = 0, kecocokanMerah = 0, kecocokanBiru = 0;
	while(i<255){
		if(histogramRGBtampung[0][i] >= histogramRGBKotamin[0][i] && histogramRGBtampung[0][i] >= histogramRGBKotamin[0][i]){
			kecocokanMerah++;
		}
		if(histogramRGBtampung[1][i] <= histogramRGBKotamax[1][i] && histogramRGBtampung[1][i] >= histogramRGBKotamin[1][i]){
			kecocokanHijau++;
		}
		if(histogramRGBtampung[2][i] >= histogramRGBKotamin[2][i] && histogramRGBtampung[2][i] >= histogramRGBKotamin[2][i]){
			kecocokanBiru++;
		}
		i++;
	}
	hasil3 = kecocokanMerah + kecocokanHijau + kecocokanBiru;
	i = j = 0;
	kecocokanHijau = 0, kecocokanMerah = 0, kecocokanBiru = 0;
	//membandingkan
	if(hasil1 >= hasil2 && hasil1 > hasil3){
		printf("Kecocokan mencapai %d (Gunung) \ndibanding dengan (Pantai) %d dan (Kota) %d\n", hasil1, hasil2, hasil3);
		printf("Gambar BISA dikategorikan sebagai 'Gunung' ");
	} else
	if(hasil2 > hasil1 && hasil2 >= hasil3){
		printf("Kecocokan mencapai %d (Pantai) \ndibanding dengan (Gunung) %d dan (Kota) %d\n", hasil2, hasil1, hasil3);
		printf("Gambar BISA dikategorikan sebagai 'Pantai' ");
	} else
	if(hasil3 >= hasil1 && hasil3 > hasil2){
		printf("Kecocokan mencapai %d (Kota) \ndibanding dengan (Gunung) %d dan (Pantai) %d\n", hasil3, hasil1, hasil2);
		printf("Gambar BISA dikategorikan sebagai 'Kota' ");
	}
	else
		printf("Gambar TIDAK BISA dikategorikan");
	//cek rgb gambar sekarang pada x
	int x = 255;
	//printf("nilai(r,g,b) ke-%d : (%d,%d,%d)\n", x, histogramRGBtampung[0][x], histogramRGBtampung[1][x], histogramRGBtampung[2][x]);
}

int main(int, char**){
	clearHistogram();
	Mat pemandangan[12];
	pemandangan[0] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 1.jpg");
	pemandangan[1] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 2.jpg");
	pemandangan[2] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 3.jpg");
	pemandangan[3] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 4.jpg");
	pemandangan[4] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 5.jpg");
	pemandangan[5] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 6.jpg");
	pemandangan[6] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 7.jpg");
	pemandangan[7] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 8.jpg");
	pemandangan[8] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 9.jpg");
	pemandangan[9] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 10.jpg");
	pemandangan[10] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 11.jpg");
	pemandangan[11] = imread("D:\\Computer Vision\\Praktikum 1\\apa ini 12.jpg");
	bacaGunung();
	bacaPantai();
	bacaKota();
	//cekHistogram();
	printf("===========================================================\n");
	int i = 0;
	while(i<12){
		printf("\nGambar ke-%d >> \n",i+1);
		cekPemandangan(pemandangan[i],pemandangan[i].size().width,pemandangan[i].size().height);
		printf("\n===========================================================\n");
		i++;
	}
	//imshow("test",pemandangan[0]);
	getch();
	waitKey();
    return 0;
}
