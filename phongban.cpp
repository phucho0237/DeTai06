#include "phongban.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dinh nghia bien toan cuc - cap phat bo nho thuc su o day
struct PhongBan dsPhongBan[MAX_PHONGBAN];
int soLuongPhongBan = 0;

// Doc du lieu phong ban tu file phongban.txt khi khoi dong chuong trinh
// Format moi dong: maPB|tenPB|heSoLuongCB|soNhanVienMax
void docPhongBan()
{
	FILE* f = fopen("phongban.txt", "r");
	if (f == NULL) return; // neu khong mo duoc file thi bo qua

	int ketQua;
	while (soLuongPhongBan < MAX_PHONGBAN)
	{
		// %[^|] doc chuoi den khi gap ky tu '|'
		ketQua = fscanf(f, " %[^|]|%[^|]|%f|%d",
			dsPhongBan[soLuongPhongBan].maPB,
			dsPhongBan[soLuongPhongBan].tenPB,
			&dsPhongBan[soLuongPhongBan].heSoLuongCB,
			&dsPhongBan[soLuongPhongBan].soNhanVienMax);

		if (ketQua != 4) break; // dung khi doc khong du 4 truong

		dsPhongBan[soLuongPhongBan].soNhanVienHienTai = 0; // se cap nhat sau khi doc NV
		soLuongPhongBan++;
	}

	fclose(f);
}

// Them phong ban moi vao mang dsPhongBan
void themPhongBan()
{
	if (soLuongPhongBan >= MAX_PHONGBAN)
	{
		printf("Khong the them phong ban moi. Da dat toi da so luong phong ban.\n");
		return;
	}

	struct PhongBan pb;

	printf("Nhap ma phong ban: ");
	scanf(" %5s", pb.maPB);

	// Kiem tra ma phong ban co bi trung khong
	for (int i = 0; i < soLuongPhongBan; i++)
	{
		if (strcmp(dsPhongBan[i].maPB, pb.maPB) == 0)
		{
			printf("Ma phong ban da ton tai!\n");
			return;
		}
	}

	printf("Nhap ten phong ban: ");
	scanf(" %30[^\n]", pb.tenPB); // doc ca chuoi co khoang trang
	printf("Nhap he so luong co ban: ");
	scanf("%f", &pb.heSoLuongCB);
	printf("Nhap so nhan vien toi da: ");
	scanf("%d", &pb.soNhanVienMax);

	pb.soNhanVienHienTai = 0; // phong ban moi chua co nhan vien

	dsPhongBan[soLuongPhongBan] = pb;
	soLuongPhongBan++;

	printf("Them phong ban thanh cong!\n");
}

// Cap nhat thong tin phong ban dua vao ma
void capNhatPhongBan(char* maPB)
{
	for (int i = 0; i < soLuongPhongBan; i++)
	{
		if (strcmp(dsPhongBan[i].maPB, maPB) == 0)
		{
			// Tim thay - sua truc tiep tren phan tu trong mang
			printf("Nhap ten phong ban moi: ");
			scanf(" %30[^\n]", dsPhongBan[i].tenPB);
			printf("Nhap he so luong co ban moi: ");
			scanf("%f", &dsPhongBan[i].heSoLuongCB);
			printf("Nhap so nhan vien toi da moi: ");
			scanf("%d", &dsPhongBan[i].soNhanVienMax);

			printf("Cap nhat phong ban thanh cong!\n");
			return;
		}
	}

	printf("Khong tim thay phong ban voi ma %s\n", maPB);
}

// Xoa phong ban khoi mang (chi xoa khi phong ban khong con nhan vien)
void xoaPhongBan(char* maPB)
{
	for (int i = 0; i < soLuongPhongBan; i++)
	{
		if (strcmp(dsPhongBan[i].maPB, maPB) == 0)
		{
			if (dsPhongBan[i].soNhanVienHienTai > 0)
			{
				printf("Khong the xoa phong ban. Vui long dieu chuyen nhan vien ra ngoai truoc.\n");
				return;
			}

			// Dich chuyen cac phan tu phia sau len 1 vi tri de ghi de phan tu can xoa
			for (int j = i; j < soLuongPhongBan - 1; j++)
				dsPhongBan[j] = dsPhongBan[j + 1];

			soLuongPhongBan--;
			printf("Xoa phong ban thanh cong!\n");
			return;
		}
	}

	printf("Khong tim thay phong ban voi ma %s\n", maPB);
}

// In danh sach tat ca phong ban ra man hinh dang bang
void xemPhongBan()
{
	if (soLuongPhongBan == 0)
	{
		printf("Danh sach phong ban trong!\n");
		return;
	}

	printf("\n%-6s | %-20s | %-10s | %-10s | %-10s\n",
		"Ma PB", "Ten PB", "He so CB", "NV toi da", "NV hien tai");
	printf("--------------------------------------------------------------\n");

	for (int i = 0; i < soLuongPhongBan; i++)
	{
		printf("%-6s | %-20s | %-10.2f | %-10d | %-10d\n",
			dsPhongBan[i].maPB,
			dsPhongBan[i].tenPB,
			dsPhongBan[i].heSoLuongCB,
			dsPhongBan[i].soNhanVienMax,
			dsPhongBan[i].soNhanVienHienTai);
	}
}