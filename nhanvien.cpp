#include "nhanvien.h"
#include "tienich.h" // dung ghiLog khi them, xoa, dieu chuyen NV
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dinh nghia bien toan cuc - DSLK don quan ly nhan vien
DSNhanVien dslkNV;

// ============================================================
// CAC HAM XU LY NUT
// ============================================================

// Tao nut moi chua thong tin nhan vien nv
// Tra ve: con tro toi nut moi, hoac NULL neu that bai
NodeNV* createNodeNV(NhanVien nv)
{
	NodeNV* p = new NodeNV; // cap phat bo nho cho nut moi
	if (p == NULL)
	{
		printf("Khong du bo nho de cap phat nut moi!\n");
		return NULL;
	}
	p->Info = nv; // gan du lieu nhan vien vao nut
	p->Next = NULL; // chua co nut ke sau
	return p;
}

// Xuat noi dung cua 1 nut ra man hinh (1 dong thong tin NV)
void showNodeNV(NodeNV* p)
{
	printf("%-6s | %-30s | %-10d | %-4s | %-11.2f | %-20s | %-6s\n",
		p->Info.maNV,
		p->Info.hoTenNV,
		p->Info.ngaySinh,
		p->Info.gioiTinh,
		p->Info.heSoLuong,
		p->Info.chucVu,
		p->Info.maPB);
}

// Huy nut khoi bo nho (xoa nut don le)
void deleteNodeNV(NodeNV*& p)
{
	if (p == NULL) return;
	p->Next = NULL;
	delete p;
}

// ============================================================
// CAC HAM XU LY DSLK
// ============================================================

// Khoi tao DSLK rong: Head va Tail deu bang NULL
void initDSNV(DSNhanVien& ds)
{
	ds.Head = NULL; // lam rong con tro Head
	ds.Tail = NULL; // lam rong con tro Tail
}

// Kiem tra DSLK co rong hay khong
// Tra ve: 1 neu rong, 0 neu khong rong
int isEmptyDSNV(DSNhanVien ds)
{
	if (ds.Head == NULL)
		return 1; // danh sach rong
	else
		return 0; // danh sach co it nhat 1 nut
}

// Them nut p vao DAU DSLK
// Tra ve: 1 neu thanh cong, 0 neu that bai
int insertHeadNV(DSNhanVien& ds, NodeNV* p)
{
	if (p == NULL)
		return 0; // thuc hien khong thanh cong

	if (isEmptyDSNV(ds) == 1)
	{
		// Danh sach rong: ca Head va Tail deu tro vao nut moi
		ds.Head = p;
		ds.Tail = p;
	}
	else
	{
		p->Next = ds.Head; // nut moi tro toi nut dang o dau
		ds.Head = p; // cap nhat Head sang nut moi
	}
	return 1; // thuc hien thanh cong
}

// Them nut p vao CUOI DSLK
// Tra ve: 1 neu thanh cong, 0 neu that bai
int insertTailNV(DSNhanVien& ds, NodeNV* p)
{
	if (p == NULL)
		return 0; // thuc hien khong thanh cong

	if (isEmptyDSNV(ds) == 1)
	{
		// Danh sach rong: ca Head va Tail deu tro vao nut moi
		ds.Head = p;
		ds.Tail = p;
	}
	else
	{
		ds.Tail->Next = p; // noi nut cuoi hien tai vao nut moi
		ds.Tail = p; // cap nhat Tail sang nut moi
	}
	return 1; // thuc hien thanh cong
}

// Xoa nut dau DSLK, luu thong tin NV vao tham so nv
// Tra ve: 1 neu thanh cong, 0 neu that bai
int deleteHeadNV(DSNhanVien& ds, NhanVien& nv)
{
	if (isEmptyDSNV(ds) == 1)
		return 0; // thuc hien khong thanh cong

	NodeNV* p = ds.Head;
	ds.Head = ds.Head->Next;

	if (ds.Head == NULL) // neu danh sach rong sau khi xoa
		ds.Tail = NULL;

	nv = p->Info; // luu thong tin cua nut bi huy
	deleteNodeNV(p); // huy nut
	return 1; // thuc hien thanh cong
}

// Tim nut co maNV trung voi tham so maNV
// Tra ve: con tro toi nut tim thay, hoac NULL neu khong co
NodeNV* findNodeNV(DSNhanVien ds, char* maNV)
{
	if (isEmptyDSNV(ds) == 1)
		return NULL; // danh sach rong

	NodeNV* p = ds.Head; // bat dau tu dau danh sach
	while (p != NULL)
	{
		if (strcmp(p->Info.maNV, maNV) == 0)
			return p; // tim thay
		p = p->Next; // xet nut ke sau
	}
	return NULL; // khong tim thay
}

// Xuat toan bo noi dung DSLK ra man hinh dang bang
void showDSNV(DSNhanVien ds)
{
	if (isEmptyDSNV(ds) == 1)
	{
		printf("Danh sach nhan vien trong!\n");
		return;
	}

	printf("\n%-6s | %-30s | %-10s | %-4s | %-10s | %-20s | %-6s\n",
		"Ma NV", "Ho Ten", "Ngay Sinh", "GT", "He so luong", "Chuc Vu", "Ma PB");
	printf("-------------------------------------------------------------------------------------------\n");

	// Duyet DSLK tu Head den Tail
	for (NodeNV* p = ds.Head; p != NULL; p = p->Next)
		showNodeNV(p);
}

// ============================================================
// CAC HAM NGHIEP VU
// ============================================================

// Doc du lieu nhan vien tu file nhanvien.txt khi khoi dong
// Format moi dong: maNV|hoTenNV|ngaySinh|gioiTinh|heSoLuong|chucVu|maPB
// Dung insertTailNV de giu dung thu tu trong file
void docNhanVien()
{
	FILE* f = fopen("nhanvien.txt", "r");
	if (f == NULL) return; // neu khong mo duoc file thi bo qua

	initDSNV(dslkNV); // khoi tao DSLK truoc khi doc

	NhanVien nv;
	int ketQua;

	while (1)
	{
		ketQua = fscanf(f, " %[^|]|%[^|]|%d|%[^|]|%f|%[^|]|%s",
			nv.maNV, nv.hoTenNV, &nv.ngaySinh,
			nv.gioiTinh, &nv.heSoLuong, nv.chucVu, nv.maPB);
		if (ketQua != 7) break; // dung khi doc khong du 7 truong

		NodeNV* p = createNodeNV(nv); // tao nut moi
		insertTailNV(dslkNV, p); // them vao cuoi de giu thu tu

		// Cap nhat si so phong ban tuong ung
		for (int i = 0; i < soLuongPhongBan; i++)
		{
			if (strcmp(nv.maPB, dsPhongBan[i].maPB) == 0)
			{
				dsPhongBan[i].soNhanVienHienTai++;
				break;
			}
		}
	}

	fclose(f);
}

// ============================================================
// VALIDATE DU LIEU
// ============================================================

// Kiem tra tuoi lao dong hop le (18-60 tuoi)
// Lay 4 chu so cuoi cua ngaySinh (ddmmyyyy) chinh la nam sinh
// Tra ve: 1 neu hop le, 0 neu khong hop le
int kiemTraTuoi(int ngaySinh)
{
	int nam = ngaySinh % 10000; // vi du: 19111995 % 10000 = 1995
	const int namHienTai = 2026;
	int tuoi = namHienTai - nam;
	if (tuoi < 18 || tuoi > 60)
	{
		printf("Tuoi khong hop le (18-60). Tuoi hien tai: %d\n", tuoi);
		return 0; // khong hop le
	}
	return 1; // hop le
}

// Kiem tra ma nhan vien chua duoc dung (phai la duy nhat)
// Duyet toan bo DSLK de kiem tra
// Tra ve: 1 neu chua ton tai (hop le), 0 neu da ton tai
int kiemTraMaNV(char* maNV)
{
	NodeNV* p = findNodeNV(dslkNV, maNV); // tim nut co maNV
	if (p != NULL)
	{
		printf("Ma nhan vien da ton tai!\n");
		return 0; // da ton tai
	}
	return 1; // chua ton tai, hop le
}

// Kiem tra phong ban ton tai va con cho trong
// Tra ve: index cua phong ban neu hop le, -1 neu khong hop le
int kiemTraPhongBan(char* maPB)
{
	for (int i = 0; i < soLuongPhongBan; i++)
	{
		if (strcmp(dsPhongBan[i].maPB, maPB) == 0)
		{
			// Phong ban ton tai, kiem tra con cho khong
			if (dsPhongBan[i].soNhanVienHienTai >= dsPhongBan[i].soNhanVienMax)
			{
				printf("Phong ban da day nhan vien!\n");
				return -1;
			}
			return i; // tra ve index de cap nhat si so sau nay
		}
	}
	printf("Ma phong ban khong ton tai!\n");
	return -1;
}

// ============================================================
// NHAP THEM NHAN VIEN MOI TU BAN PHIM
// ============================================================

// Nhap thong tin nhan vien moi tu ban phim va them vao DSLK (vao dau)
void themNhanVien()
{
	NhanVien nv;

	printf("Nhap ma nhan vien: ");
	scanf(" %5s", nv.maNV);
	if (!kiemTraMaNV(nv.maNV)) return; // dung neu ma bi trung

	printf("Nhap ho ten: ");
	scanf("%s", nv.hoTenNV);

	printf("Nhap ngay sinh (ddmmyyyy): ");
	scanf("%d", &nv.ngaySinh);
	if (!kiemTraTuoi(nv.ngaySinh)) return; // dung neu tuoi khong hop le

	printf("Nhap gioi tinh (Nam/Nu): ");
	scanf(" %3s", nv.gioiTinh);

	printf("Nhap he so luong: ");
	scanf("%f", &nv.heSoLuong);

	printf("Nhap chuc vu: ");
	scanf(" %20[^\n]", nv.chucVu);

	printf("Nhap ma phong ban: ");
	scanf(" %5s", nv.maPB);
	int idx = kiemTraPhongBan(nv.maPB); // kiem tra phong ban va lay index
	if (idx == -1) return;

	NodeNV* p = createNodeNV(nv); // tao nut moi
	insertHeadNV(dslkNV, p); // them vao dau DSLK
	dsPhongBan[idx].soNhanVienHienTai++; // cap nhat si so phong ban
	ghiLog("THEM_NV", nv.maNV); // ghi log hanh dong them NV

	printf("Them nhan vien thanh cong!\n");
}

// Sua thong tin nhan vien (tru ma NV va phong ban)
// Tim nut trong DSLK va sua truc tiep tren nut do
void suaNhanVien()
{
	char maNV[6];
	printf("Nhap ma nhan vien can sua: ");
	scanf(" %5s", maNV);

	NodeNV* p = findNodeNV(dslkNV, maNV); // tim nut theo ma
	if (p == NULL)
	{
		printf("Khong tim thay nhan vien voi ma %s\n", maNV);
		return;
	}

	// Tim thay - sua truc tiep tren p->Info
	printf("Nhap ho ten moi: ");
	scanf(" %30[^\n]", p->Info.hoTenNV);

	printf("Nhap ngay sinh moi (ddmmyyyy): ");
	scanf("%d", &p->Info.ngaySinh);
	if (!kiemTraTuoi(p->Info.ngaySinh)) return;

	printf("Nhap gioi tinh moi (Nam/Nu): ");
	scanf(" %3s", p->Info.gioiTinh);

	printf("Nhap he so luong moi: ");
	scanf("%f", &p->Info.heSoLuong);

	printf("Nhap chuc vu moi: ");
	scanf(" %20[^\n]", p->Info.chucVu);

	printf("Cap nhat nhan vien thanh cong!\n");
}

// Xoa nhan vien khoi DSLK theo ma
// Dung bien prev de luu nut truoc cur, xu ly ca 3 truong hop:
// xoa dau / xoa giua / xoa cuoi danh sach
void xoaNhanVien()
{
	char maNV[6];
	printf("Nhap ma nhan vien can xoa: ");
	scanf(" %5s", maNV);

	NodeNV* cur = dslkNV.Head;
	NodeNV* prev = NULL; // luu nut phia truoc cur

	while (cur != NULL)
	{
		if (strcmp(cur->Info.maNV, maNV) == 0)
		{
			// Cap nhat si so phong ban truoc khi xoa
			for (int i = 0; i < soLuongPhongBan; i++)
			{
				if (strcmp(dsPhongBan[i].maPB, cur->Info.maPB) == 0)
				{
					dsPhongBan[i].soNhanVienHienTai--;
					break;
				}
			}

			// Noi lai lien ket, bo qua nut can xoa
			if (prev == NULL)
				dslkNV.Head = cur->Next; // xoa nut dau: Head tro sang nut ke tiep
			else
				prev->Next = cur->Next; // xoa nut giua/cuoi

			if (cur == dslkNV.Tail) // neu xoa nut cuoi: cap nhat Tail
				dslkNV.Tail = prev;

			ghiLog("XOA_NV", cur->Info.maNV); // ghi log truoc khi xoa
			deleteNodeNV(cur); // huy nut
			printf("Xoa nhan vien thanh cong!\n");
			return;
		}
		prev = cur; // luu lai nut hien tai truoc khi di tiep
		cur = cur->Next;
	}

	printf("Khong tim thay nhan vien voi ma %s\n", maNV);
}

// Dieu chuyen nhan vien sang phong ban khac
// Cap nhat maPB cua NV, giam si so phong cu, tang si so phong moi
void dieuChuyenNhanVien()
{
	char maNV[6];
	printf("Nhap ma nhan vien can dieu chuyen: ");
	scanf(" %5s", maNV);

	NodeNV* p = findNodeNV(dslkNV, maNV); // tim nut theo ma
	if (p == NULL)
	{
		printf("Khong tim thay nhan vien voi ma %s\n", maNV);
		return;
	}

	char maPBMoi[6];
	printf("Phong ban hien tai: %s\n", p->Info.maPB);
	printf("Nhap ma phong ban moi: ");
	scanf(" %5s", maPBMoi);

	// Khong cho dieu chuyen sang chinh phong ban hien tai
	if (strcmp(maPBMoi, p->Info.maPB) == 0)
	{
		printf("Nhan vien da thuoc phong ban nay roi!\n");
		return;
	}

	// Kiem tra phong ban moi ton tai va con cho
	int idxMoi = kiemTraPhongBan(maPBMoi);
	if (idxMoi == -1) return;

	// Giam si so phong ban cu
	for (int i = 0; i < soLuongPhongBan; i++)
	{
		if (strcmp(dsPhongBan[i].maPB, p->Info.maPB) == 0)
		{
			dsPhongBan[i].soNhanVienHienTai--;
			break;
		}
	}

	// Cap nhat ma phong ban moi va tang si so phong moi
	strcpy(p->Info.maPB, maPBMoi);
	dsPhongBan[idxMoi].soNhanVienHienTai++;
	ghiLog("DIEU_CHUYEN_NV", p->Info.maNV); // ghi log

	printf("Dieu chuyen nhan vien thanh cong!\n");
}

// In danh sach tat ca nhan vien trong DSLK ra man hinh
void xemNhanVien()
{
	showDSNV(dslkNV); // goi ham
}