#ifndef NHANVIEN_H
#define NHANVIEN_H

#include "phongban.h"

// ============================================================
// KHAI BAO KIEU DU LIEU
// ============================================================

// Cau truc luu thong tin 1 nhan vien
struct NhanVien {
	char maNV[6]; // ma nhan vien, toi da 5 ky tu, phai la duy nhat
	char hoTenNV[31]; // ho ten day du, toi da 30 ky tu
	int ngaySinh; // ngay sinh dinh dang ddmmyyyy (vi du: 19111995)
	char gioiTinh[4]; // "Nam" hoac "Nu"
	float heSoLuong; // he so luong ca nhan
	char chucVu[21]; // chuc vu trong cong ty, toi da 20 ky tu
	char maPB[6]; // ma phong ban nhan vien thuoc ve
};

// Node cua DSLK don
struct NodeNV {
	NhanVien Info; // thanh phan du lieu (thong tin nhan vien)
	NodeNV* Next; // thanh phan lien ket (dia chi nut ke sau)
};

// DSLK don quan ly nhan vien - co ca Head va Tail
struct DSNhanVien {
	NodeNV* Head; // con tro tro vao nut dau danh sach
	NodeNV* Tail; // con tro tro vao nut cuoi danh sach
};

// Bien toan cuc - dinh nghia trong nhanvien.cpp
extern DSNhanVien dslkNV;

// ============================================================
// PROTOTYPE CAC HAM XU LY NUT
// ============================================================
NodeNV* createNodeNV(NhanVien nv); // tao nut moi chua thong tin nv
void showNodeNV(NodeNV* p); // xuat noi dung 1 nut ra man hinh
void deleteNodeNV(NodeNV*& p); // huy nut khoi bo nho

// ============================================================
// PROTOTYPE CAC HAM XU LY DSLK
// ============================================================
void initDSNV(DSNhanVien& ds); // khoi tao danh sach rong
int isEmptyDSNV(DSNhanVien ds); // kiem tra danh sach rong
int insertHeadNV(DSNhanVien& ds, NodeNV* p); // them nut vao dau
int insertTailNV(DSNhanVien& ds, NodeNV* p); // them nut vao cuoi
int deleteHeadNV(DSNhanVien& ds, NhanVien& nv); // xoa nut dau
NodeNV* findNodeNV(DSNhanVien ds, char* maNV); // tim nut theo ma NV
void showDSNV(DSNhanVien ds); // xuat ca danh sach

// ============================================================
// PROTOTYPE CAC HAM NGHIEP VU
// ============================================================
void docNhanVien(); // doc du lieu tu file nhanvien.txt
void themNhanVien(); // nhap thong tin va them NV moi
void suaNhanVien(); // sua thong tin NV theo ma
void xoaNhanVien(); // xoa NV khoi DSLK theo ma
void dieuChuyenNhanVien(); // chuyen NV sang phong ban khac
void xemNhanVien(); // in danh sach NV ra man hinh

// Ham validate du lieu
int kiemTraTuoi(int ngaySinh); // kiem tra tuoi lao dong 18-60
int kiemTraMaNV(char* maNV); // kiem tra ma NV chua ton tai
int kiemTraPhongBan(char* maPB); // kiem tra phong ban ton tai va con cho

#endif