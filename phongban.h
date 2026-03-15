#ifndef PHONGBAN_H
#define PHONGBAN_H

#define MAX_PHONGBAN 10 // so luong phong ban toi da

// Cau truc luu thong tin 1 phong ban (dung mang tinh - so luong co dinh)
struct PhongBan {
	char maPB[6]; // ma phong ban, toi da 5 ky tu
	char tenPB[31]; // ten phong ban, toi da 30 ky tu
	float heSoLuongCB; // he so luong co ban cua phong ban
	int soNhanVienMax; // so nhan vien toi da duoc phep
	int soNhanVienHienTai; // so nhan vien dang lam viec hien tai
};

// Bien toan cuc - dinh nghia trong phongban.cpp
// extern: bao cho cac file khac biet bien nay ton tai o phongban.cpp
extern struct PhongBan dsPhongBan[MAX_PHONGBAN];
extern int soLuongPhongBan;

// Prototype cac ham quan ly phong ban
void docPhongBan();
void themPhongBan();
void capNhatPhongBan(char* maPB);
void xoaPhongBan(char* maPB);
void xemPhongBan();

#endif