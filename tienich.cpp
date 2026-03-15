#include "tienich.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILE_BACKUP_PB "backup_phongban.txt"
#define FILE_BACKUP_NV "backup_nhanvien.txt"
#define FILE_LOG "system.log"

// ============================================================
// HAM HO TRO: lay thoi gian hien tai thanh chuoi
// ============================================================
static void layThoiGian(char* buf, int size)
{
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);
	strftime(buf, size, "%d/%m/%Y %H:%M:%S", tm_info); // dinh dang dd/mm/yyyy hh:mm:ss
}

// ============================================================
// LOG HE THONG
// Ghi moi thao tac quan trong vao file system.log
// Format: [dd/mm/yyyy hh:mm:ss] HANH_DONG | chi tiet
// ============================================================
void ghiLog(const char* hanhDong, const char* chiTiet)
{
	FILE* f = fopen(FILE_LOG, "a"); // mo file o che do append
	if (f == NULL) return;

	char thoiGian[30];
	layThoiGian(thoiGian, sizeof(thoiGian));

	fprintf(f, "[%s] %-20s | %s\n", thoiGian, hanhDong, chiTiet);
	fclose(f);
}

// Xem toan bo noi dung file log
void xemLog()
{
	FILE* f = fopen(FILE_LOG, "r");
	if (f == NULL)
	{
		printf("Chua co file log hoac chua co thao tac nao duoc ghi.\n");
		return;
	}

	printf("\n===== NHAT KY HE THONG =====\n");
	char line[256];
	int count = 0;
	while (fgets(line, sizeof(line), f) != NULL)
	{
		printf("%s", line);
		count++;
	}
	printf("----------------------------\n");
	printf("Tong: %d dong log.\n", count);
	fclose(f);
}

// ============================================================
// BACKUP: ghi toan bo du lieu ra file
// Format giong file goc de co the doc lai
// ============================================================
void backupDuLieu()
{
	// --- Backup phong ban ---
	FILE* fPB = fopen(FILE_BACKUP_PB, "w");
	if (fPB == NULL)
	{
		printf("Khong the tao file backup phong ban!\n");
		return;
	}
	for (int i = 0; i < soLuongPhongBan; i++)
		fprintf(fPB, "%s|%s|%.2f|%d\n",
			dsPhongBan[i].maPB,
			dsPhongBan[i].tenPB,
			dsPhongBan[i].heSoLuongCB,
			dsPhongBan[i].soNhanVienMax);
	fclose(fPB);

	// --- Backup nhan vien ---
	FILE* fNV = fopen(FILE_BACKUP_NV, "w");
	if (fNV == NULL)
	{
		printf("Khong the tao file backup nhan vien!\n");
		return;
	}

	// Dem so node trong DSLK
	int n = 0;
	for (NodeNV* p = dslkNV.Head; p != NULL; p = p->Next) n++;

	// Dua vao mang tam de ghi dung thu tu (Head -> Tail)
	NhanVien* arr = new NhanVien[n];
	NodeNV* p = dslkNV.Head;
	for (int i = 0; i < n; i++)
	{
		arr[i] = p->Info; // dung .Info
		p = p->Next;
	}
	for (int i = 0; i < n; i++)
		fprintf(fNV, "%s|%s|%d|%s|%.2f|%s|%s\n",
			arr[i].maNV, arr[i].hoTenNV, arr[i].ngaySinh,
			arr[i].gioiTinh, arr[i].heSoLuong,
			arr[i].chucVu, arr[i].maPB);
	delete[] arr;
	fclose(fNV);

	printf("Backup thanh cong!\n");
	printf(" -> %s\n", FILE_BACKUP_PB);
	printf(" -> %s\n", FILE_BACKUP_NV);

	ghiLog("BACKUP", "Sao luu du lieu thanh cong");
}

// ============================================================
// RESTORE: doc lai du lieu tu file backup
// Xoa du lieu hien tai truoc khi doc lai
// ============================================================
void restoreDuLieu()
{
	printf("CANH BAO: Thao tac nay se ghi de toan bo du lieu hien tai!\n");
	printf("Ban co chac chan? (1 = Co / 0 = Khong): ");
	int xacNhan;
	scanf("%d", &xacNhan);
	if (!xacNhan) return;

	// --- Xoa du lieu phong ban hien tai ---
	soLuongPhongBan = 0;

	// --- Xoa toan bo DSLK nhan vien hien tai ---
	// Dung deleteHeadNV lap lai den khi het
	while (isEmptyDSNV(dslkNV) == 0)
	{
		NhanVien nv;
		deleteHeadNV(dslkNV, nv); // xoa nut dau, tu dong cap nhat Head va Tail
	}

	// --- Doc lai phong ban tu file backup ---
	FILE* fPB = fopen(FILE_BACKUP_PB, "r");
	if (fPB == NULL)
	{
		printf("Khong tim thay file backup phong ban '%s'!\n", FILE_BACKUP_PB);
		return;
	}
	int ketQua;
	while (soLuongPhongBan < MAX_PHONGBAN)
	{
		ketQua = fscanf(fPB, " %[^|]|%[^|]|%f|%d",
			dsPhongBan[soLuongPhongBan].maPB,
			dsPhongBan[soLuongPhongBan].tenPB,
			&dsPhongBan[soLuongPhongBan].heSoLuongCB,
			&dsPhongBan[soLuongPhongBan].soNhanVienMax);
		if (ketQua != 4) break;
		dsPhongBan[soLuongPhongBan].soNhanVienHienTai = 0;
		soLuongPhongBan++;
	}
	fclose(fPB);

	// --- Doc lai nhan vien tu file backup ---
	FILE* fNV = fopen(FILE_BACKUP_NV, "r");
	if (fNV == NULL)
	{
		printf("Khong tim thay file backup nhan vien '%s'!\n", FILE_BACKUP_NV);
		return;
	}
	NhanVien nv;
	while (1)
	{
		ketQua = fscanf(fNV, " %[^|]|%[^|]|%d|%[^|]|%f|%[^|]|%s",
			nv.maNV, nv.hoTenNV, &nv.ngaySinh,
			nv.gioiTinh, &nv.heSoLuong, nv.chucVu, nv.maPB);
		if (ketQua != 7) break;

		NodeNV* p = createNodeNV(nv); // tao nut moi
		insertTailNV(dslkNV, p); // them vao cuoi de giu thu tu

		for (int i = 0; i < soLuongPhongBan; i++)
			if (strcmp(dsPhongBan[i].maPB, nv.maPB) == 0)
			{
				dsPhongBan[i].soNhanVienHienTai++;
				break;
			}
	}
	fclose(fNV);

	printf("Restore thanh cong! Da tai lai %d phong ban.\n", soLuongPhongBan);
	ghiLog("RESTORE", "Phuc hoi du lieu tu file backup thanh cong");
}