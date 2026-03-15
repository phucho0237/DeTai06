#include "timkiem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Ham noi bo (static: chi dung trong file nay)
// In dong tieu de cot cua bang ket qua tim kiem
static void inHeader()
{
	printf("\n%-6s | %-30s | %-10s | %-4s | %-6s | %-20s | %-6s\n",
		"Ma NV", "Ho Ten", "Ngay Sinh", "GT", "HSL", "Chuc Vu", "Ma PB");
	printf("---------------------------------------------------------------------------------\n");
}

// Tim nhan vien theo ma NV (tim chinh xac, co phan biet hoa/thuong)
void timNhanVienTheoMa(char* maNV)
{
	// Dung ham findNodeNV co san trong nhanvien (tra ve NodeNV*)
	NodeNV* p = findNodeNV(dslkNV, maNV);
	if (p != NULL)
	{
		inHeader();
		showNodeNV(p); // goi ham de in
	}
	else
	{
		printf("Khong tim thay nhan vien voi ma '%s'\n", maNV);
	}
}

// Tim nhan vien theo ten (tim gan dung, khong phan biet hoa/thuong)
// Dung strstr de kiem tra chuoi con
void timNhanVienTheoTen(char* ten)
{
	int timThay = 0;

	// Chuyen chuoi can tim sang chu thuong de so sanh
	char tenLower[31];
	strncpy(tenLower, ten, 30);
	tenLower[30] = '\0';
	for (int i = 0; tenLower[i]; i++)
		if (tenLower[i] >= 'A' && tenLower[i] <= 'Z')
			tenLower[i] += 32; // chuyen ASCII hoa -> thuong (cach nhau 32)

	inHeader();

	// Duyet DSLK tu Head den Tail
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next)
	{
		// Chuyen ho ten NV sang chu thuong de so sanh
		char hoTenLower[31];
		strncpy(hoTenLower, p->Info.hoTenNV, 30);
		hoTenLower[30] = '\0';
		for (int i = 0; hoTenLower[i]; i++)
			if (hoTenLower[i] >= 'A' && hoTenLower[i] <= 'Z')
				hoTenLower[i] += 32;

		// strstr tra ve NULL neu khong tim thay chuoi con
		if (strstr(hoTenLower, tenLower) != NULL)
		{
			showNodeNV(p);
			timThay++;
		}
	}

	if (timThay == 0)
		printf("Khong tim thay nhan vien voi ten gan dung '%s'\n", ten);
	else
		printf("Tim thay %d ket qua.\n", timThay);
}

// Tim tat ca nhan vien thuoc mot phong ban cu the
void timNhanVienTheoPhongBan(char* maPB)
{
	// Kiem tra phong ban co ton tai khong truoc khi tim
	int tonTai = 0;
	for (int i = 0; i < soLuongPhongBan; i++)
		if (strcmp(dsPhongBan[i].maPB, maPB) == 0) { tonTai = 1; break; }

	if (!tonTai)
	{
		printf("Phong ban '%s' khong ton tai!\n", maPB);
		return;
	}

	int timThay = 0;
	inHeader();

	// Duyet DSLK, in ra cac NV co maPB trung khop
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next)
	{
		if (strcmp(p->Info.maPB, maPB) == 0)
		{
			showNodeNV(p);
			timThay++;
		}
	}

	if (timThay == 0)
		printf("Phong ban '%s' chua co nhan vien nao.\n", maPB);
	else
		printf("Tim thay %d nhan vien.\n", timThay);
}

// Sap xep danh sach nhan vien theo 2 tieu chi:
// 1. Giam dan theo he so luong
// 2. Neu he so luong bang nhau: tang dan theo nam sinh (nguoi lon tuoi hon xep truoc)
// Thuat toan: copy DSLK sang mang tam -> bubble sort -> ghi lai vao DSLK
void sapXepNhanVien()
{
	if (isEmptyDSNV(dslkNV) == 1) return;

	// Buoc 1: dem so nhan vien trong DSLK
	int n = 0;
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next) n++;

	// Buoc 2: copy du lieu tu DSLK sang mang tam
	NhanVien* arr = new NhanVien[n];
	NodeNV* p = dslkNV.Head;
	for (int i = 0; i < n; i++)
	{
		arr[i] = p->Info; // dung .Info thay vi .data
		p = p->Next;
	}

	// Buoc 3: Bubble sort tren mang tam
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			int canDoi = 0;

			if (arr[j].heSoLuong < arr[j + 1].heSoLuong)
				canDoi = 1; // hsl nho hon o truoc -> phai doi cho (giam dan)
			else if (arr[j].heSoLuong == arr[j + 1].heSoLuong)
			{
				// HSL bang nhau: so sanh nam sinh
				// ngaySinh % 10000 lay 4 chu so cuoi = nam sinh
				int namJ = arr[j].ngaySinh % 10000;
				int namJ1 = arr[j + 1].ngaySinh % 10000;
				if (namJ > namJ1) canDoi = 1; // nam sinh lon hon = tre hon -> xep sau
			}

			if (canDoi)
			{
				NhanVien temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	// Buoc 4: ghi lai ket qua sap xep vao DSLK
	p = dslkNV.Head;
	for (int i = 0; i < n; i++)
	{
		p->Info = arr[i]; // dung .Info
		p = p->Next;
	}

	delete[] arr; // giai phong mang tam
	printf("Sap xep nhan vien thanh cong!\n");
}

// Sap xep danh sach phong ban giam dan theo so nhan vien hien co
// Dung bubble sort truc tiep tren mang dsPhongBan
void sapXepPhongBan()
{
	for (int i = 0; i < soLuongPhongBan - 1; i++)
	{
		for (int j = 0; j < soLuongPhongBan - i - 1; j++)
		{
			// Neu phong j co it NV hon phong j+1 thi doi cho (giam dan)
			if (dsPhongBan[j].soNhanVienHienTai < dsPhongBan[j + 1].soNhanVienHienTai)
			{
				PhongBan temp = dsPhongBan[j];
				dsPhongBan[j] = dsPhongBan[j + 1];
				dsPhongBan[j + 1] = temp;
			}
		}
	}
	printf("Sap xep phong ban thanh cong!\n");
}