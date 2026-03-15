#include "baocao.h"
#include <stdio.h>
#include <string.h>

// ============================================================
// HAM HO TRO
// ============================================================

// Tinh luong thuc te cua 1 nhan vien
// Luong = heSoLuong * heSoLuongCB cua phong ban
static float tinhLuong(NhanVien nv)
{
	for (int i = 0; i < soLuongPhongBan; i++)
		if (strcmp(dsPhongBan[i].maPB, nv.maPB) == 0)
			return nv.heSoLuong * dsPhongBan[i].heSoLuongCB;
	return 0;
}

// Lay ngay thang nam tu so nguyen ddmmyyyy
static void phanTachNgay(int ngay, int* d, int* m, int* y)
{
	*y = ngay % 10000;
	*m = (ngay / 10000) % 100;
	*d = ngay / 1000000;
}

// Lay quy (1-4) tu thang
static int layQuy(int thang)
{
	return (thang - 1) / 3 + 1;
}

// ============================================================
// 1. BANG LUONG THANG
// ============================================================
void bangLuongThang()
{
	if (isEmptyDSNV(dslkNV) == 1)
	{
		printf("Danh sach nhan vien trong!\n");
		return;
	}

	printf("\n========== BANG LUONG THANG ==========\n");
	printf("%-6s | %-30s | %-6s | %-10s | %-10s | %-10s\n",
		"Ma NV", "Ho Ten", "Ma PB", "He so NV", "He so PB", "Luong");
	printf("--------------------------------------------------------------------------\n");

	float tongQuyLuong = 0;

	// Duyet DSLK tu Head den Tail bang vong for
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next)
	{
		float luong = tinhLuong(p->Info); // dung .Info thay vi .data
		float hslPB = 0;

		for (int i = 0; i < soLuongPhongBan; i++)
			if (strcmp(dsPhongBan[i].maPB, p->Info.maPB) == 0)
			{
				hslPB = dsPhongBan[i].heSoLuongCB;
				break;
			}

		printf("%-6s | %-30s | %-6s | %-10.2f | %-10.2f | %-10.2f\n",
			p->Info.maNV,
			p->Info.hoTenNV,
			p->Info.maPB,
			p->Info.heSoLuong,
			hslPB,
			luong);

		tongQuyLuong += luong;
	}

	printf("--------------------------------------------------------------------------\n");
	printf("TONG QUY LUONG CONG TY: %.2f\n", tongQuyLuong);
}

// ============================================================
// 2. TOP LUONG CAO NHAT / THAP NHAT
// ============================================================
void timLuongCaoNhat()
{
	if (isEmptyDSNV(dslkNV) == 1)
	{
		printf("Danh sach nhan vien trong!\n");
		return;
	}

	NodeNV* nvCao = dslkNV.Head;
	NodeNV* nvThap = dslkNV.Head;
	float luongCao = tinhLuong(nvCao->Info);
	float luongThap = tinhLuong(nvThap->Info);

	// Duyet DSLK bang vong for
	for (NodeNV* p = dslkNV.Head->Next; p != NULL; p = p->Next)
	{
		float luong = tinhLuong(p->Info);
		if (luong > luongCao) { luongCao = luong; nvCao = p; }
		if (luong < luongThap) { luongThap = luong; nvThap = p; }
	}

	printf("\n===== TOP LUONG =====\n");
	printf("[CAO NHAT] %-6s | %-30s | Luong: %.2f\n",
		nvCao->Info.maNV, nvCao->Info.hoTenNV, luongCao);
	printf("[THAP NHAT] %-6s | %-30s | Luong: %.2f\n",
		nvThap->Info.maNV, nvThap->Info.hoTenNV, luongThap);
}

// ============================================================
// 3. THONG KE NHAN VIEN THEO PHONG BAN + BIEU DO TEXT
// ============================================================
void thongKeNhanVienTheoPB()
{
	if (soLuongPhongBan == 0)
	{
		printf("Chua co phong ban nao!\n");
		return;
	}

	// Tim so NV lon nhat de tinh ty le bieu do
	int maxNV = 1;
	for (int i = 0; i < soLuongPhongBan; i++)
		if (dsPhongBan[i].soNhanVienHienTai > maxNV)
			maxNV = dsPhongBan[i].soNhanVienHienTai;

	printf("\n===== THONG KE NHAN VIEN THEO PHONG BAN =====\n");
	printf("%-6s | %-20s | %-5s | Bieu do\n", "Ma PB", "Ten PB", "SL NV");
	printf("------------------------------------------------------------\n");

	for (int i = 0; i < soLuongPhongBan; i++)
	{
		// Tinh do dai thanh bieu do (toi da 30 ky tu '#')
		int doDai = (maxNV > 0)
			? (dsPhongBan[i].soNhanVienHienTai * 30) / maxNV : 0;

		printf("%-6s | %-20s | %-5d | ",
			dsPhongBan[i].maPB,
			dsPhongBan[i].tenPB,
			dsPhongBan[i].soNhanVienHienTai);

		for (int j = 0; j < doDai; j++) printf("#");
		printf(" %d\n", dsPhongBan[i].soNhanVienHienTai);
	}
}

// ============================================================
// 4. LIET KE HANG DOI UNG VIEN
// ============================================================
void lietKeHangDoi()
{
	if (isEmptyHangDoi(hangDoiTuyenDung) == 1)
	{
		printf("Hang doi tuyen dung dang trong.\n");
		return;
	}

	printf("\n===== DANH SACH UNG VIEN DANG CHO PHONG VAN =====\n");
	printf("%-4s | %-30s | %-10s | %-4s\n", "STT", "Ho Ten", "Ngay Sinh", "GT");
	printf("----------------------------------------------------\n");

	// Duyet Queue tu Head den Tail ma khong lay ra (dung vong for)
	int stt = 1;
	for (NodeUV* p = hangDoiTuyenDung.Head; p != NULL; p = p->Next)
	{
		printf("%-4d | ", stt++);
		showNodeUV(p);
	}
	printf("Tong: %d ung vien dang cho.\n", hangDoiTuyenDung.size);
}

// ============================================================
// 5. THONG KE TONG LUONG THEO THOI GIAN
// ============================================================
void thongKeLuongTheoThoiGian()
{
	printf("\n===== THONG KE LUONG THEO THOI GIAN =====\n");
	printf("1. Theo thang\n");
	printf("2. Theo quy\n");
	printf("3. Theo nam\n");
	printf("4. Tu ngay den ngay\n");
	printf("Nhap lua chon: ");

	int chon;
	scanf("%d", &chon);

	int thang = 0, quy = 0, nam = 0, tuNgay = 0, denNgay = 0;

	if (chon == 1)
	{
		printf("Nhap thang (1-12): "); scanf("%d", &thang);
		printf("Nhap nam: "); scanf("%d", &nam);
	}
	else if (chon == 2)
	{
		printf("Nhap quy (1-4): "); scanf("%d", &quy);
		printf("Nhap nam: "); scanf("%d", &nam);
	}
	else if (chon == 3)
	{
		printf("Nhap nam: "); scanf("%d", &nam);
	}
	else if (chon == 4)
	{
		printf("Nhap ngay bat dau (ddmmyyyy): "); scanf("%d", &tuNgay);
		printf("Nhap ngay ket thuc (ddmmyyyy): "); scanf("%d", &denNgay);
	}
	else
	{
		printf("Lua chon khong hop le.\n");
		return;
	}

	int soThang = 0;
	if (chon == 1) soThang = 1;
	else if (chon == 2) soThang = 3;
	else if (chon == 3) soThang = 12;
	else soThang = 1;

	float tongLuong = 0;

	// Duyet DSLK bang vong for
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next)
	{
		int d, m, y;
		phanTachNgay(p->Info.ngaySinh, &d, &m, &y);

		int thoa = 0;
		if (chon == 1 && m == thang && y <= nam) thoa = 1;
		else if (chon == 2 && layQuy(m) == quy && y <= nam) thoa = 1;
		else if (chon == 3 && y <= nam) thoa = 1;
		else if (chon == 4 && p->Info.ngaySinh >= tuNgay
			&& p->Info.ngaySinh <= denNgay) thoa = 1;

		if (thoa) tongLuong += tinhLuong(p->Info) * soThang;
	}

	printf("Tong luong chi tra: %.2f\n", tongLuong);
}