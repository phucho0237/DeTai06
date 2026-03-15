#ifndef TIMKIEM_H
#define TIMKIEM_H

#include "nhanvien.h"
#include "phongban.h"

// Tim kiem nhan vien
void timNhanVienTheoMa(char* maNV); // tim chinh xac theo ma NV
void timNhanVienTheoTen(char* ten); // tim gan dung theo ten (dung strstr)
void timNhanVienTheoPhongBan(char* maPB); // tim tat ca NV thuoc 1 phong ban

// Sap xep
void sapXepNhanVien(); // giam dan theo HSL, neu bang nhau thi tang dan theo nam sinh
void sapXepPhongBan(); // giam dan theo so nhan vien hien co

#endif