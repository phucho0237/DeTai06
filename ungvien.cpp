#include "ungvien.h"
#include "tienich.h" // dung ghiLog khi tuyen duoc NV chinh thuc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dinh nghia bien toan cuc hang doi tuyen dung
HangDoi hangDoiTuyenDung;

// ============================================================
// CAC HAM XU LY NUT
// ============================================================

// Tao nut moi chua thong tin ung vien uv
// Tra ve: con tro toi nut moi, hoac NULL neu that bai
NodeUV* createNodeUV(UngVien uv)
{
	NodeUV* p = new NodeUV; // cap phat bo nho cho nut moi
	if (p == NULL)
	{
		printf("Khong du bo nho de cap phat nut moi!\n");
		return NULL;
	}
	p->Info = uv; // gan du lieu ung vien vao nut
	p->Next = NULL; // chua co nut ke sau
	return p;
}

// Xuat noi dung 1 nut ra man hinh
void showNodeUV(NodeUV* p)
{
	printf("%-30s | %-10d | %-4s\n",
		p->Info.hoTenUV,
		p->Info.ngaySinh,
		p->Info.gioiTinh);
}

// ============================================================
// CAC HAM XU LY QUEUE
// ============================================================

// Khoi tao hang doi rong: Head va Tail deu NULL, size = 0
void initHangDoi(HangDoi& q)
{
	q.Head = NULL; // lam rong con tro dau
	q.Tail = NULL; // lam rong con tro cuoi
	q.size = 0;
}

// Kiem tra hang doi co rong hay khong
// Tra ve: 1 neu rong, 0 neu khong rong
int isEmptyHangDoi(HangDoi q)
{
	if (q.Head == NULL)
		return 1; // hang doi rong
	else
		return 0; // hang doi khong rong
}

// Them nut p vao CUOI hang doi (FIFO: ai nop truoc phong van truoc)
// Tra ve: 1 neu thanh cong, 0 neu that bai
int insert(HangDoi& q, NodeUV* p)
{
	if (p == NULL)
		return 0; // thuc hien khong thanh cong

	if (isEmptyHangDoi(q) == 1)
		q.Head = p; // hang doi rong: Head tro vao nut moi
	else
		q.Tail->Next = p; // noi nut cuoi hien tai vao nut moi

	q.Tail = p; // cap nhat Tail sang nut moi
	q.size++;
	return 1; // thuc hien thanh cong
}

// Lay va huy nut o DAU hang doi (FIFO), luu thong tin vao tham so uv
// Tra ve: 1 neu thanh cong, 0 neu that bai (hang doi rong)
int removeHangDoi(HangDoi& q, UngVien& uv)
{
	if (isEmptyHangDoi(q) == 1)
		return 0; // thuc hien khong thanh cong

	NodeUV* p = q.Head;
	q.Head = q.Head->Next; // di chuyen Head sang nut ke tiep

	if (q.Head == NULL) // neu hang rong sau khi lay
		q.Tail = NULL;

	uv = p->Info; // luu thong tin cua nut bi huy
	delete p; // giai phong bo nho
	q.size--;
	return 1; // thuc hien thanh cong
}

// Xem thong tin nut o DAU hang doi (khong huy)
// Tra ve: 1 neu thanh cong, 0 neu hang doi rong
int getHead(HangDoi q, UngVien& uv)
{
	if (isEmptyHangDoi(q) == 1)
		return 0; // khong thuc hien duoc

	uv = q.Head->Info; // lay thong tin cua nut dau hang
	return 1;
}

// Xuat noi dung toan bo hang doi (duyet ma khong lay ra)
void showHangDoi(HangDoi q)
{
	if (isEmptyHangDoi(q) == 1)
	{
		printf("Hang doi rong!\n");
		return;
	}

	printf("\nNoi dung hang doi: \n");
	printf("%-4s | %-30s | %-10s | %-4s\n", "STT", "Ho Ten", "Ngay Sinh", "GT");
	printf("----------------------------------------------------\n");

	// Duyet tu Head den Tail ma khong lay ra
	int stt = 1;
	for (NodeUV* p = q.Head; p != NULL; p = p->Next)
	{
		printf("%-4d | ", stt++);
		showNodeUV(p);
	}
}

// ============================================================
// CAC HAM NGHIEP VU
// ============================================================

// Tiep nhan ho so: nhap thong tin ung vien va dua vao Queue
void tiepNhanHoSo()
{
	UngVien uv;

	printf("Nhap ho ten ung vien: ");
	scanf("%s", uv.hoTenUV);

	printf("Nhap ngay sinh (ddmmyyyy): ");
	scanf("%d", &uv.ngaySinh);

	// Validate tuoi lao dong truoc khi cho vao Queue
	if (!kiemTraTuoi(uv.ngaySinh))
	{
		printf("Ho so bi tu choi do tuoi khong hop le.\n");
		return;
	}

	printf("Nhap gioi tinh (Nam/Nu): ");
	scanf(" %3s", uv.gioiTinh);

	NodeUV* p = createNodeUV(uv); // tao nut moi
	insert(hangDoiTuyenDung, p); // them vao cuoi hang doi
	printf("Da tiep nhan ho so. Vi tri trong hang doi: %d\n", hangDoiTuyenDung.size);
}

// Phong van ung vien dau hang va xu ly ket qua
// Dau: chuyen thanh NV chinh thuc, cap nhat DSLK va si so phong ban
// Rot: luu vao danhsachden.txt hoac xoa khoi he thong
void phongVanTuyenDung()
{
	if (isEmptyHangDoi(hangDoiTuyenDung) == 1)
	{
		printf("Hang doi trong, khong co ung vien nao!\n");
		return;
	}

	UngVien uv;
	removeHangDoi(hangDoiTuyenDung, uv); // lay ung vien dau hang ra de phong van

	printf("\n===== PHONG VAN =====\n");
	printf("Ho ten : %s\n", uv.hoTenUV);
	printf("Ngay sinh: %d\n", uv.ngaySinh);
	printf("Gioi tinh: %s\n", uv.gioiTinh);
	printf("Con lai trong hang doi: %d nguoi\n", hangDoiTuyenDung.size);

	int ketQua;
	printf("\nKet qua phong van (1 = Dau / 0 = Rot): ");
	scanf("%d", &ketQua);

	if (ketQua == 1)
	{
		// ===== DAU: Chuyen thanh Nhan vien chinh thuc =====
		NhanVien nv;

		printf("\n-- Nhap thong tin chinh thuc --\n");
		printf("Nhap ma nhan vien: ");
		scanf(" %5s", nv.maNV);
		if (!kiemTraMaNV(nv.maNV)) return; // kiem tra ma NV khong trung

		// Sao chep thong tin co san tu ung vien sang nhan vien
		strcpy(nv.hoTenNV, uv.hoTenUV);
		nv.ngaySinh = uv.ngaySinh;
		strcpy(nv.gioiTinh, uv.gioiTinh);

		printf("Nhap chuc vu: ");
		scanf(" %20[^\n]", nv.chucVu);
		printf("Nhap he so luong: ");
		scanf("%f", &nv.heSoLuong);
		printf("Nhap ma phong ban: ");
		scanf(" %5s", nv.maPB);

		int idx = kiemTraPhongBan(nv.maPB);
		if (idx == -1) return;

		NodeNV* p = createNodeNV(nv); // tao nut moi
		insertHeadNV(dslkNV, p); // them vao DSLK nhan vien
		dsPhongBan[idx].soNhanVienHienTai++; // cap nhat si so phong ban
		ghiLog("TUYEN_DUNG", nv.maNV); // ghi log

		printf("Ung vien '%s' da tro thanh nhan vien chinh thuc!\n", nv.hoTenNV);
	}
	else
	{
		// ===== ROT: Xoa hoac luu vao danh sach den =====
		int luuDSden;
		printf("Luu vao danh sach den? (1 = Co / 0 = Khong): ");
		scanf("%d", &luuDSden);

		if (luuDSden)
		{
			// Mo file o che do append ("a") de khong ghi de du lieu cu
			FILE* f = fopen("danhsachden.txt", "a");
			if (f != NULL)
			{
				fprintf(f, "%s|%d|%s\n", uv.hoTenUV, uv.ngaySinh, uv.gioiTinh);
				fclose(f);
				printf("Da luu '%s' vao danh sach den.\n", uv.hoTenUV);
			}
		}
		else
		{
			// UV da bi removeHangDoi roi nen chi can thong bao, bo nho da duoc delete trong removeHangDoi
			printf("Da xoa ho so '%s' khoi he thong.\n", uv.hoTenUV);
		}
	}
}

// In toan bo hang doi hien tai (goi ham showHangDoi)
void xemHangDoi()
{
	showHangDoi(hangDoiTuyenDung);
	if (!isEmptyHangDoi(hangDoiTuyenDung))
		printf("Tong: %d ung vien\n", hangDoiTuyenDung.size);
}