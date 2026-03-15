#ifndef BAOCAO_H
#define BAOCAO_H

#include "nhanvien.h"
#include "phongban.h"
#include "ungvien.h"

// Thong ke luong
void bangLuongThang(); // in bang luong tung NV va tong quy luong
void timLuongCaoNhat(); // top NV luong cao nhat va thap nhat

// Thong ke phong ban
void thongKeNhanVienTheoPB(); // so luong NV theo phong ban + bieu do text

// Hang doi ung vien
void lietKeHangDoi(); // liet ke UV dang cho trong Queue

// Thong ke luong theo thoi gian
void thongKeLuongTheoThoiGian(); // chon Thang/Quy/Nam/Khoang ngay

#endif