#ifndef TIENICH_H
#define TIENICH_H

#include "nhanvien.h"
#include "phongban.h"

// Backup / Restore toan bo du lieu ra file
void backupDuLieu(); // ghi dsPhongBan + DSLK NV ra file backup
void restoreDuLieu(); // doc lai du lieu tu file backup

// Log he thong
void ghiLog(const char* hanhDong, const char* chiTiet); // ghi 1 dong vao file log
void xemLog(); // in noi dung file log ra man hinh

#endif