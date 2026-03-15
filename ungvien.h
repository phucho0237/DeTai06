#ifndef UNGVIEN_H
#define UNGVIEN_H

#include "nhanvien.h"

// ============================================================
// KHAI BAO KIEU DU LIEU
// ============================================================

// Cau truc luu thong tin ung vien dang ky phong van
struct UngVien {
	char hoTenUV[31]; // ho ten ung vien
	int ngaySinh; // ngay sinh dinh dang ddmmyyyy
	char gioiTinh[4]; // "Nam" hoac "Nu"
};

// Node cua Queue
struct NodeUV {
	UngVien Info; // thanh phan du lieu (thong tin ung vien)
	NodeUV* Next; // thanh phan lien ket (dia chi nut ke sau)
};

// Queue tuyen dung (FIFO: ai nop truoc phong van truoc)
// - Head: dau hang - lay ra tai day (remove)
// - Tail: cuoi hang - them vao tai day (insert)
struct HangDoi {
	NodeUV* Head; // con tro dau hang doi (thay vi front)
	NodeUV* Tail; // con tro cuoi hang doi (thay vi rear)
	int size; // so luong ung vien dang trong hang
};

// Bien toan cuc hang doi tuyen dung - dinh nghia trong ungvien.cpp
extern HangDoi hangDoiTuyenDung;

// ============================================================
// PROTOTYPE CAC HAM XU LY NUT
// ============================================================
NodeUV* createNodeUV(UngVien uv); // tao nut moi chua thong tin uv
void showNodeUV(NodeUV* p); // xuat noi dung 1 nut ra man hinh

// ============================================================
// PROTOTYPE CAC HAM XU LY QUEUE
// ============================================================
void initHangDoi(HangDoi& q); // khoi tao hang doi rong
int isEmptyHangDoi(HangDoi q); // kiem tra hang doi rong (tra ve 1 neu rong)
int insert(HangDoi& q, NodeUV* p); // them nut vao CUOI hang doi
int removeHangDoi(HangDoi& q, UngVien& uv); // lay va huy nut o DAU hang doi
int getHead(HangDoi q, UngVien& uv); // xem nut o dau (khong huy)
void showHangDoi(HangDoi q); // xem toan bo hang doi

// ============================================================
// PROTOTYPE CAC HAM NGHIEP VU
// ============================================================
void tiepNhanHoSo(); // nhap thong tin va dua UV vao Queue
void phongVanTuyenDung(); // phong van UV dau hang, xu ly dau/rot
void xemHangDoi(); // in danh sach UV trong Queue

#endif