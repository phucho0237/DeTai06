#include <stdio.h>
#include <conio.h>
#include "phongban.h"
#include "nhanvien.h"
#include "ungvien.h"
#include "timkiem.h"
#include "baocao.h"  // thong ke, bao cao, bang luong
#include "tienich.h" // backup, restore, log

void main()
{
	docPhongBan(); // doc phongban.txt -> dsPhongBan[]
	docNhanVien(); // doc nhanvien.txt -> DSLK dslkNV (Head + Tail)
	initHangDoi(hangDoiTuyenDung); // khoi tao hang doi tuyen dung rong

	int chon;  // lua chon menu chinh
	int chon1; // lua chon submenu

	do {
		printf("\nDE TAI 05. QUAN LY NHAN SU CONG TY NHO BANG DSLK DON\n\n");
		printf("1. Quan ly phong ban\n");
		printf("2. Quan ly nhan vien\n");
		printf("3. Quan ly ung vien\n");
		printf("4. Xem danh sach phong ban\n");
		printf("5. Xem danh sach nhan vien\n");
		printf("6. Tim kiem & Sap xep\n");
		printf("7. Thong ke & Bao cao\n");
		printf("8. Tien ich he thong\n");
		printf("0. Thoat CT\n\n");

		printf("Nhap lua chon: ");
		scanf("%d", &chon);

		switch (chon)
		{
		case 0:
		{
			printf("Ban da chon thoat chuong trinh...");
			break;
		}

		// ===== QUAN LY PHONG BAN =====
		case 1:
		{
			do
			{
				printf("\n\nQUAN LY PHONG BAN\n");
				printf("1. Them phong ban\n");
				printf("2. Cap nhat phong ban\n");
				printf("3. Xoa phong ban\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1); // chon1 de khong anh huong toi chon cua menu chinh

				switch (chon1)
				{
				case 0: break;
				case 1: themPhongBan(); break;
				case 2:
				{
					char maPB[6];
					printf("Nhap ma phong ban can cap nhat: ");
					scanf(" %5s", maPB);
					capNhatPhongBan(maPB);
					break;
				}
				case 3:
				{
					char maPB[6];
					printf("Nhap ma phong ban can xoa: ");
					scanf(" %5s", maPB);
					xoaPhongBan(maPB);
					break;
				}
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		// ===== QUAN LY NHAN VIEN =====
		case 2:
		{
			do
			{
				printf("\n\nQUAN LY NHAN VIEN\n");
				printf("1. Them nhan vien\n");
				printf("2. Cap nhat nhan vien\n");
				printf("3. Xoa nhan vien\n");
				printf("4. Dieu chuyen nhan vien\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1);

				switch (chon1)
				{
				case 0: break;
				case 1: themNhanVien(); break;
				case 2: suaNhanVien(); break;
				case 3: xoaNhanVien(); break;
				case 4: dieuChuyenNhanVien(); break;
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		// ===== QUAN LY UNG VIEN (QUEUE TUYEN DUNG - FIFO) =====
		case 3:
		{
			do
			{
				printf("\n\nQUAN LY UNG VIEN\n");
				printf("1. Tiep nhan ho so\n");        // insert vao Queue
				printf("2. Phong van va tuyen dung\n"); // removeHangDoi tu Queue + xu ly
				printf("3. Xem hang doi\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1);

				switch (chon1)
				{
				case 0: break;
				case 1: tiepNhanHoSo(); break;
				case 2: phongVanTuyenDung(); break;
				case 3: xemHangDoi(); break;
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		// ===== XEM DANH SACH =====
		case 4: xemPhongBan(); break;
		case 5: xemNhanVien(); break;

			// ===== TIM KIEM VA SAP XEP =====
		case 6:
		{
			do
			{
				printf("\n\nTIM KIEM & SAP XEP\n");
				printf("1. Tim NV theo ma\n");
				printf("2. Tim NV theo ten\n");
				printf("3. Tim NV theo phong ban\n");
				printf("4. Sap xep nhan vien\n");
				printf("5. Sap xep phong ban\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1);

				switch (chon1)
				{
				case 0: break;
				case 1:
				{
					char ma[6];
					printf("Nhap ma NV: ");
					scanf(" %5s", ma);
					timNhanVienTheoMa(ma);
					break;
				}
				case 2:
				{
					char ten[31];
					printf("Nhap ten can tim: ");
					scanf(" %30[^\n]", ten);
					timNhanVienTheoTen(ten);
					break;
				}
				case 3:
				{
					char maPB[6];
					printf("Nhap ma phong ban: ");
					scanf(" %5s", maPB);
					timNhanVienTheoPhongBan(maPB);
					break;
				}
				case 4: sapXepNhanVien(); break;
				case 5: sapXepPhongBan(); break;
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		// ===== THONG KE & BAO CAO =====
		case 7:
		{
			do
			{
				printf("\n\nTHONG KE & BAO CAO\n");
				printf("1. Bang luong thang\n");
				printf("2. Top luong cao nhat / thap nhat\n");
				printf("3. Thong ke NV theo phong ban\n");
				printf("4. Liet ke hang doi ung vien\n");
				printf("5. Thong ke luong theo thoi gian\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1);

				switch (chon1)
				{
				case 0: break;
				case 1: bangLuongThang(); break;
				case 2: timLuongCaoNhat(); break;
				case 3: thongKeNhanVienTheoPB(); break;
				case 4: lietKeHangDoi(); break;
				case 5: thongKeLuongTheoThoiGian(); break;
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		// ===== TIEN ICH HE THONG =====
		case 8:
		{
			do
			{
				printf("\n\nTIEN ICH HE THONG\n");
				printf("1. Sao luu du lieu (Backup)\n");
				printf("2. Phuc hoi du lieu (Restore)\n");
				printf("3. Xem nhat ky he thong (Log)\n");
				printf("0. Quay lai\n");

				printf("Nhap lua chon: ");
				scanf("%d", &chon1);

				switch (chon1)
				{
				case 0: break;
				case 1: backupDuLieu(); break;
				case 2: restoreDuLieu(); break;
				case 3: xemLog(); break;
				default: printf("Lua chon khong hop le. Vui long thu lai."); break;
				}
			} while (chon1 != 0);
			break;
		}

		default:
		{
			printf("Lua chon khong hop le. Vui long thu lai.");
			break;
		}
		}
	} while (chon != 0);

	getch();
}