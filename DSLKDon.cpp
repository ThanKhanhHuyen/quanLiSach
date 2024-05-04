#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;
// GIẢM GIÁ TỪNG LOẠI
//  STRUCT THỂ LOẠI
struct TheLoai
{
    char maTheLoai[10];
    char tenTheLoai[50];
};

// STRUCT SÁCH
struct Date
{
    int ngay;
    int thang;
    int nam;
};

struct Sach
{
    char maSach[10];
    char tenSach[50];
    char tacGia[50];
    char NXB[50];
    Date ngayPhatHanh;
    float gia;
    int soLuong;
    TheLoai theLoai; // Thêm thông tin về thể loại sách
    float giamGia;
};

struct NodeSach
{
    Sach data;
    NodeSach *next;
};

struct ListSach
{
    NodeSach *Head;
    NodeSach *Tail;
};

void init_ListSach(ListSach &l)
{
    l.Head = NULL;
    l.Tail = NULL;
}

NodeSach *create_NodeSach(Sach sach)
{
    NodeSach *p = new NodeSach();
    if (p == NULL)
    {
        cout << "Khong du bo nho!";
        exit(1);
    }
    p->data = sach;
    p->next = NULL;
    return p;
}

void addFirst_Sach(ListSach &l, NodeSach *p)
{
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
    }
    else
    {
        p->next = l.Head;
        l.Head = p;
    }
}

void addLast_Sach(ListSach &l, NodeSach *p)
{
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
    }
    else
    {
        l.Tail->next = p;
        l.Tail = p;
    }
}

void nhapSach(Sach &sach)
{
    cout << "\nNhap ma sach:";
    cin >> sach.maSach;
    cout << "Nhap ten sach:";
    cin.ignore();
    cin.getline(sach.tenSach, 50);
    cout << "Nhap ten tac gia:";
    // cin.ignore();
    cin.getline(sach.tacGia, 50);
    cout << "Nhap nha xuat ban:";
    // cin.ignore();
    cin.getline(sach.NXB, 50);
    cout << "Nhap ngay phat hanh" << endl;
    cout << "Ngay: ";
    cin >> sach.ngayPhatHanh.ngay;
    cout << "Thang: ";
    cin >> sach.ngayPhatHanh.thang;
    cout << "Nam: ";
    cin >> sach.ngayPhatHanh.nam;
    cout << "Gia: ";
    cin >> sach.gia;
    cout << "So luong: ";
    cin >> sach.soLuong;
    cout << "Nhap ma the loai: ";
    cin >> sach.theLoai.maTheLoai;
    cout << "Nhap ten the loai: ";
    cin.ignore();
    cin.getline(sach.theLoai.tenTheLoai, 50);
    cout << "Nhap gia giam (%): ";
    cin >> sach.giamGia;
}

void nhapListSach(ListSach &l)
{
    Sach sach;
    nhapSach(sach);
    NodeSach *p = create_NodeSach(sach);
    int opt;
    cout << "\n1.Them vao dau danh sach:";
    cout << "\n2.Them vao cuoi danh sach:";
    cout << "\nNhap lua chon cua ban:";
    cin >> opt;
    if (opt == 1)
    {
        addFirst_Sach(l, p);
    }
    if (opt == 2)
    {
        addLast_Sach(l, p);
    }
    cout << "Thanh cong !" << endl;
}

void hienSach(Sach sach)
{
    sach.giamGia /= 100.0;
    cout << setw(10) << sach.maSach;
    cout << setw(15) << sach.tenSach;
    cout << setw(15) << sach.tacGia;
    cout << setw(10) << sach.NXB;
    cout << setw(15) << sach.ngayPhatHanh.ngay << "/" << sach.ngayPhatHanh.thang << "/" << sach.ngayPhatHanh.nam;
    cout << setw(10) << sach.gia;
    cout << setw(10) << sach.soLuong;
    cout << setw(10) << sach.theLoai.maTheLoai;
    cout << setw(15) << sach.theLoai.tenTheLoai;
    cout << setw(15) << sach.giamGia * 100;
    cout << setw(10) << sach.gia * (1 - sach.giamGia) << endl;
}

void hienListSach(ListSach l)
{
    cout << setw(100) << "--------------------THONG TIN SACH--------------------"
         << endl;
    cout << setw(10) << "Ma sach";
    cout << setw(15) << "Ten sach";
    cout << setw(15) << "Tac gia";
    cout << setw(10) << "NXB";
    cout << setw(22) << "Ngay phat hanh";
    cout << setw(10) << "Gia goc";
    cout << setw(10) << "SL";
    cout << setw(10) << "Ma TL";
    cout << setw(15) << "Ten TL";
    cout << setw(15) << "Giam gia(%)";
    cout << setw(10) << "Phai tra" << endl;
    NodeSach *p = l.Head;
    while (p != NULL)
    {
        hienSach(p->data);
        p = p->next;
    }
}

// thêm 1 hoặc nhiều cuốn sách vào sau sách có tên nhập từ bàn phím(nhập rồi mới hiện thông báo không tìm thấy sách có tên x)
void addSachSauTen(ListSach &l, char tenSachNhap[50], NodeSach *sachMoi)
{
    NodeSach *p = l.Head; // nút hiện tại
    if (l.Head == NULL)
    {
        l.Head = l.Tail = sachMoi;
        cout << "Vi danh sach rong nen gia tri nhap vao se tu duoc them vao!";
    }
    while (p != NULL)
    {
        if (strcmp(tenSachNhap, p->data.tenSach) == 0)
        {
            sachMoi->next = p->next;
            p->next = sachMoi;
            return;
        }
        p = p->next;
    }
    cout << "Khong tim thay sach co ten " << tenSachNhap << endl;
}

// thêm 1 hoặc nhiều cuốn sách vào trước sách có tên nhập từ bàn phím(nhập rồi mới hiện thông báo không tìm thấy sách có tên x)
void addSachTruocTen(ListSach &l, char tenSachNhap[50], NodeSach *sachMoi)
{
    NodeSach *p = l.Head; // nút hiện tại
    NodeSach *q = NULL;   // nút trước
    if (l.Head == NULL)
    {
        l.Head = l.Tail = sachMoi;
        cout << "Vi danh sach rong nen gia tri nhap vao se tu duoc them vao!";
    }
    while (p != NULL)
    {
        if (strcmp(tenSachNhap, p->data.tenSach) == 0)
        {
            sachMoi->next = p;
            if (q == NULL)
            {
                l.Head = sachMoi;
            }
            else
            {
                q->next = sachMoi;
            }
            return;
        }
        q = p;
        p = p->next;
    }
    cout << "Khong tim thay sach co ten " << tenSachNhap << endl;
}

// thêm 1 cuốn sách vào vị trí bất kì
void addSachVaoViTriBatKy(ListSach &l, NodeSach *sachMoi, int vt)
{
    if (vt < 0)
    {
        cout << "Vi tri khong hop le !" << endl;
        return;
    }
    if (vt == 0)
    {
        // thêm vào đầu ds
        sachMoi->next = l.Head;
        l.Head = sachMoi;
        return;
    }

    NodeSach *p = NULL;   // nút trước
    NodeSach *q = l.Head; // nút hiện tại
    int vitrihientai = 0;
    while (q != NULL && vitrihientai < vt)
    {
        p = q;
        q = q->next;
        vitrihientai++;
    }

    if (vitrihientai == vt)
    {
        sachMoi->next = q;
        p->next = sachMoi;
    }
    else
    {
        cout << "Vi tri khong hop le !" << endl;
        delete sachMoi; // xoá sách mới vì vị trí không hợp lệ
    }
}

// Xoá sách ở đầu
void deleteFirst(ListSach &l)
{
    // nếu ds rỗng
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !" << endl;
        return;
    }
    NodeSach *p = l.Head;  // node p là node sẽ xoá
    l.Head = l.Head->next; // Cập nhật lại head là ptu kế tiếp
    delete p;
    cout << "Xoa thanh cong!" << endl;
}

// Xoá sách ở cuối
void deleteLast(ListSach &l)
{
    // nếu ds rỗng
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !" << endl;
        return;
    }
    if (l.Head->next == NULL)
    {
        // Ds chỉ chứa 1 phần tử
        delete l.Head;
        l.Head = NULL;
        cout << "Xoa thanh cong !";
        return;
    }
    NodeSach *p = l.Head;       // nút trước
    NodeSach *q = l.Head->next; // nút cuối

    while (q->next != NULL)
    {
        p = q;
        q = q->next;
    }
    p->next = NULL; // Cập nhật con trỏ của phần tử trước để không trỏ tới phần tử cuối cùng
    delete q;       // Giải phóng bộ nhớ của phần tử cuối cùng
    cout << "Xoa thanh cong!" << endl;
}

// Xoá 1 cuốn sách sau sách có tên nhập từ bàn phím
void deleteSachSauTen(ListSach &l, char tenSachNhap[50])
{
    if (l.Head == NULL)
    {
        cout << "\nKhong co gi de xoa !" << endl;
        return;
    }
    // trường hợp có 1 cuốn
    if (l.Head->next == NULL)
    {
        cout << "\nSau cuon sach nay khong co cuon sach nao !" << endl;
        return;
    }
    NodeSach *p = l.Head;       // nút trước
    NodeSach *q = l.Head->next; // nút hiện tại

    while (q != NULL)
    {
        // trường hợp có nhiều cuốn nhưng cuốn có tên nhập vào nằm cuối
        if (q->next == NULL)
        {
            if (strcmp(tenSachNhap, q->data.tenSach) == 0)
            {
                cout << "Sau cuon sach nay khong co cuon nao !" << endl;
                return;
            }
            // else{
            //     cout<<"Khong tim thay cuon sach co ten "<< tenSachNhap <<endl;
            //     return;
            // }
        }
        // trường hợp có nhiều cuốn và có sách sau cuốn nhập tên
        if (strcmp(tenSachNhap, p->data.tenSach) == 0)
        {
            NodeSach *k = q;   // nút xoá
            p->next = q->next; // cập nhật con trỏ của phần tử trước
            delete k;          // giải phóng bộ nhớ của phần tử xoá
            return;
        }
        p = q;
        q = q->next;
    }
    cout << "Khong tim thay sach co ten " << tenSachNhap << endl;
}
// xoá 1 cuốn sách ở vị trí bất kì
void deleteSachOViTriBatKy(ListSach &l, int vt)
{
    if (l.Head == NULL)
    {
        cout << "\nKhong co gi de xoa !" << endl;
        return;
    }

    if (vt < 0)
    {
        cout << "Vi tri khong hop le !" << endl;
        return;
    }
    if (vt == 0)
    {
        // xoá ở đầu ds
        NodeSach *k = l.Head; // nút xoá
        l.Head = l.Head->next;
        delete k;
        return;
    }

    NodeSach *p = NULL;   // nút trước
    NodeSach *q = l.Head; // nút hiện tại
    int vitrihientai = 0;
    while (q != NULL && vitrihientai < vt)
    {
        p = q;
        q = q->next;
        vitrihientai++;
    }

    if (q == NULL)
    {
        cout << "Vi tri khong hop le !" << endl;
        return;
    }
    // xoá ở vt bất kì
    p->next = q->next;
    delete q;
}

// xoá 1 cuốn sách có tên nhập từ bàn phím
void deleteSachTheoTen(ListSach &l, char tenSachXoa[50])
{
    if (l.Head == NULL)
    {
        cout << "\nKhong co gi de xoa !" << endl;
        return;
    }
    if (strcmp(tenSachXoa, l.Head->data.tenSach) == 0)
    {
        // xoá cuốn ở đầu ds
        NodeSach *k = l.Head; // nút xoá
        l.Head = l.Head->next;
        delete k;
        return;
    }
    NodeSach *p = l.Head;       // nút trước
    NodeSach *q = l.Head->next; // nút hiện tại

    while (q != NULL)
    {
        if (strcmp(tenSachXoa, q->data.tenSach) == 0)
        {
            NodeSach *k = q;
            p->next = q->next;
            delete k;
            return;
        }
        p = q;
        q = q->next;
    }
    cout << "Khong tim thay sach co ten " << tenSachXoa << endl;
}

// Đếm xem trong danh sách có bao nhiêu loại sách
int Size(ListSach l)
{
    int count = 0;
    NodeSach *p = l.Head;
    while (p != NULL)
    {
        p = p->next;
        count += 1;
    }

    return count;
}
// Đếm tổng số lượng sách hiện có
int tongSLSach(ListSach &l)
{
    int tong = 0;
    NodeSach *p = l.Head; // nút hiện tại
    while (p != NULL)
    {
        tong += p->data.soLuong;
        p = p->next;
    }
    return tong;
}

// Tính tổng tiền tất cả các cuốn sách
float tongTienCacLoaiSach(ListSach &l)
{
    int tongtien = 0;
    NodeSach *p = l.Head; // nút hiện tại
    while (p != NULL)
    {
        tongtien += p->data.soLuong * p->data.gia;
        p = p->next;
    }
    return tongtien;
}

// Tính tbc tổng tiền sách
double tbcTongTien(ListSach &l)
{
    double tbc;
    float tongtien = tongTienCacLoaiSach(l);
    int n = tongSLSach(l);
    return tbc = tongtien / n;
}

// tìm thông tin sách theo tên
// void timSachTheoTen(ListSach &l, char tenSachTim[50])
// {
//     if (l.Head == NULL)
//     {
//         cout << "\nDanh sach rong !" << endl;
//         return;
//     }
//     NodeSach *p = l.Head; // nút hiện tại

//     while (p != NULL && strcmp(tenSachTim, p->data.tenSach) != 0)
//     {
//         p=p->next;
//     }
//     if(p == NULL){
//         cout<<"Khong tim thay sach "<<tenSachTim<<endl;
//     }else{
//         NodeSach *k =l.Head;
//         while(k!=NULL){
//                 if(strcmp(k->data.tenSach, tenSachTim) == 0){
//                     cout<<setw(20)<< k->data.maSach<<setw(20)<<k->data.tenSach<<setw(20)<<k->data.tacGia
//                         <<setw(20)<<k->data.NXB<<setw(20)<<k->data.ngayPhatHanh.ngay<< "/" << k->data.ngayPhatHanh.thang << "/" << k->data.ngayPhatHanh.nam
//                         <<setw(20)<<k->data.gia<<setw(20)<<k->data.soLuong;
//                 }
//         }
//         p=p->next;
//     }
// }

void timSachTheoTen(ListSach &l, char tenSachTim[50])
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !" << endl;
        return;
    }
    NodeSach *p = l.Head; // nút hiện tại

    while (p != NULL)
    {
        if (strcmp(tenSachTim, p->data.tenSach) == 0)
        {
            cout << setw(100) << "--------------------THONG TIN SACH--------------------"
                 << endl;
            cout << setw(10) << "Ma sach" << setw(15) << "Ten Sach" << setw(15) << "Tac gia" << setw(10) << "NXB" << setw(22) << "Ngay phat hanh"
                 << setw(10) << "Gia" << setw(10) << "So luong" << setw(10) << "Ma TL" << setw(15) << "Ten TL"
                 << setw(15) << "Giam gia(%)" << setw(10) << "Phai tra" << endl;
            hienSach(p->data);
            return;
        }
        p = p->next;
    }
    if (p == NULL)
    {
        cout << "Khong tim thay sach " << tenSachTim << endl;
    }
}

// Trích lọc thuộc tính giảm giá y
//  Hàm hiển thị thông tin sách có giảm giá bằng y
void hienSachCoGiamGiaBangY(ListSach l, float y)
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !" << endl;
        return;
    }
    NodeSach *p = l.Head;
    bool check;
    while (p != NULL)
    {
        if (p->data.giamGia == y)
        {
            // cout << setw(100) << "--------------------THONG TIN SACH--------------------"
            //      << endl;
            cout << "\nDanh sach cuon sach co gia giam bang " << y << ":" << endl;
            cout << setw(10) << "Ma sach" << setw(15) << "Ten Sach" << setw(15) << "Tac gia" << setw(10) << "NXB" << setw(22) << "Ngay phat hanh"
                 << setw(10) << "Gia" << setw(10) << "So luong" << setw(10) << "Ma TL" << setw(15) << "Ten TL"
                 << setw(15) << "Giam gia(%)" << setw(10) << "Phai tra" << endl;
            hienSach(p->data);
            check = true;
        }
        p = p->next;
    }
    if (!check)
    {
        cout << "Khong tim thay cuon sach nao co gia giam bang " << y << endl;
    }
}

// Hàm lưu thông tin sách có giảm giá bằng y vào file
void luuSachCoGiamGiaBangYVaoFile(ListSach l, float y, const char *fileName)
{
    ofstream fileOut(fileName, ios::app);
    if (!fileOut.is_open())
    {
        cout << "Khong the mo tep " << fileName << " de ghi." << endl;
        return;
    }

    NodeSach *p = l.Head;
    while (p != NULL)
    {
        if (p->data.giamGia == y)
        {
            fileOut << p->data.maSach << ";" << p->data.tenSach << ";" << p->data.tacGia << ";" << p->data.NXB
                    << ";" << p->data.ngayPhatHanh.ngay << "/" << p->data.ngayPhatHanh.thang << "/" << p->data.ngayPhatHanh.nam
                    << ";" << p->data.gia << ";" << p->data.soLuong << ";" << p->data.theLoai.maTheLoai << ";"
                    << p->data.theLoai.tenTheLoai << ";" << p->data.giamGia << ";" << p->data.gia * (1 - p->data.giamGia / 100.0) << endl;
        }
        p = p->next;
    }

    fileOut.close();
    cout << "Thong tin cuon sach co gia giam bang " << y << " da duoc luu vao tep " << fileName << endl;
}

// Hàm đọc thông tin sách từ file giamgia.txt
void docThongTinSachTuFile(const char *fileName)
{
    ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        cout << "Khong the mo tep " << fileName << " de doc." << endl;
        return;
    }

    string line;
    while (getline(fileIn, line))
    {
        istringstream iss(line);
        string token;

        // Tách thông tin sách từ dòng
        // đọc dữ liệu từ chuỗi iss cho đến khi gặp ; và lưu vào biến token.
        getline(iss, token, ';'); // Mã sách
        string maSach = token;

        getline(iss, token, ';'); // Tên sách
        string tenSach = token;

        getline(iss, token, ';'); // Tác giả
        string tacGia = token;

        getline(iss, token, ';'); // NXB
        string NXB = token;

        getline(iss, token, '/'); // Ngay
        string Ngay = token;

        getline(iss, token, '/'); // Thang
        string Thang = token;

        getline(iss, token, ';'); // Nam
        string Nam = token;

        getline(iss, token, ';');
        string Gia = token;

        getline(iss, token, ';');
        string SL = token;

        getline(iss, token, ';');
        string MaTL = token;

        getline(iss, token, ';');
        string TenTL = token;

        getline(iss, token, ';');
        string Giam = token;

        getline(iss, token, ' ');
        string PhaiTra = token;

        // In thông tin sách
        cout << "Ma sach: " << maSach << ", Ten sach: " << tenSach << ", Tac gia: " << tacGia << ", NXB: " << NXB << ", Ngay phat hanh: " << Ngay << "/" << Thang << "/" << Nam << ", Gia: " << Gia << ", SL: " << SL << ", Ma TL: " << MaTL << ", Ten TL: " << TenTL << ", Giam(%): " << Giam << ", Phai tra: " << PhaiTra
             << endl;

        // In các trường khác của sách tương ứng
    }

    fileIn.close();
}

// Ghi DS sách vào file dạng nhị phân
void ghiFile_Sach1(ListSach &l)
{
    FILE *f;
    char fileName[20];
    cin.ignore();
    cout << "\nNhap ten file: ";
    cin >> fileName;

    ofstream fileOut(fileName, ios::app);
    if (!fileOut.is_open())
    {
        cout << "Khong the mo tep " << fileName << " de ghi." << endl;
        return;
    }

    f = fopen(fileName, "wb");
    if (f == NULL)
    {
        cout << "\nKhong mo duoc file!" << endl;
        return;
    }
    else
    {
        int n = Size(l);
        fwrite(&n, sizeof(int), 1, f);
        NodeSach *p = l.Head;
        while (p != NULL)
        {
            fwrite(&p->data, sizeof(Sach), 1, f);
            p = p->next;
        }
        fclose(f);
    }
    cout << "\nDa ghi file dạng nhị phân!" << endl;
}

// Đọc DS sách từ file dạng nhị phân
void docFile_Sach1(ListSach &l)
{
    FILE *f;
    char fileName[20];
    cin.ignore();
    cout << "\nNhap ten file: ";
    cin >> fileName;

    ifstream fileIn(fileName);
    if (!fileIn.is_open())
    {
        cout << "Khong the mo tep " << fileName << " de doc." << endl;
        return;
    }

    f = fopen(fileName, "rb");
    if (f == NULL)
    {
        cout << "\nKhong ton tai file";
        return;
    }
    else
    {
        Sach sach;
        NodeSach *p;
        int n;
        init_ListSach(l);
        fread(&n, sizeof(int), 1, f);
        for (int i = 0; i < n; i++)
        {
            fread(&sach, sizeof(Sach), 1, f);
            p = create_NodeSach(sach);
            hienSach(p->data);
            addLast_Sach(l, p);
        }
        fclose(f);
        cout << "\nDa doc file !" << endl;
    }
}

// XOÁ SÁCH THEO NGÀY PHÁT HÀNH
void deleteSachTheoNPH(ListSach &l, int ngay, int thang, int nam)
{
    if (l.Head == NULL)
    {
        cout << "\nKhong co gi de xoa !" << endl;
        return;
    }

    // Xử lý trường hợp xóa ở đầu danh sách
    while (l.Head != NULL && l.Head->data.ngayPhatHanh.ngay == ngay && l.Head->data.ngayPhatHanh.thang == thang && l.Head->data.ngayPhatHanh.nam == nam)
    {
        NodeSach *k = l.Head;
        l.Head = l.Head->next;
        delete k;
    }

    NodeSach *p = l.Head; // nút trước
    NodeSach *q = l.Head; // nút hiện tại

    bool found = false; // Biến kiểm tra xem có cuốn sách nào bị xóa hay không

    while (q != NULL)
    {
        if (q->data.ngayPhatHanh.ngay == ngay && q->data.ngayPhatHanh.thang == thang && q->data.ngayPhatHanh.nam == nam)
        {
            NodeSach *k = q;
            p->next = q->next;
            delete k;
            found = true;
        }
        else
        {
            p = q;
        }

        q = p->next;
    }

    if (!found)
    {
        cout << "Khong tim thay sach co ngay phat hanh " << ngay << "/" << thang << "/" << nam << endl;
    }
}

// sắp xếp giảm dần từ a->z theo tên sách
void sapxepGiamDan_TenSach(ListSach &l)
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong!" << endl;
        return;
    }
    for (NodeSach *p = l.Head; p != NULL; p = p->next)
    {
        for (NodeSach *k = p->next; k != NULL; k = k->next)
        {
            if (strcmp(p->data.tenSach, k->data.tenSach) < 0)
            {
                Sach tmp = p->data;
                p->data = k->data;
                k->data = tmp;
            }
        }
    }
    cout << "\nDa sap xep!" << endl;
}

// Hàm hiển thị sách theo thể loại
void hienThiTheoTheLoai(ListSach &l, char theLoaiCanHien[50])
{
    NodeSach *p = l.Head;
    bool coSachTheoTheLoai = false;

    cout << "\nDanh sach cac sach thuoc the loai '" << theLoaiCanHien << "':" << endl;
    while (p != NULL)
    {
        if (strcmp(theLoaiCanHien, p->data.theLoai.tenTheLoai) == 0)
        {
            hienSach(p->data);
            coSachTheoTheLoai = true;
        }
        p = p->next;
    }

    if (!coSachTheoTheLoai)
    {
        cout << "Khong co sach thuoc the loai '" << theLoaiCanHien << "'." << endl;
    }
}

// Hàm tìm cuốn sách có giá cao nhất
Sach timSachGiaCaoNhat(ListSach &l)
{
    Sach sachGiaCaoNhat;
    sachGiaCaoNhat.gia = INT_MIN; // Giá trị khởi tạo là giá trị nhỏ nhất cho kiểu int

    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong!" << endl;
        return sachGiaCaoNhat; // Trả về cuốn sách có giá trị khởi tạo
    }

    NodeSach *p = l.Head;
    while (p != NULL)
    {
        if (p->data.gia > sachGiaCaoNhat.gia)
        {
            sachGiaCaoNhat = p->data;
        }
        p = p->next;
    }

    return sachGiaCaoNhat;
}



// Hàm trích lọc và lưu sách có giảm giá từ mức x đến mức y vào file
void trichLocVaLuuSachTheoGia(ListSach l, float x, float y, const char *fileName)
{
    ofstream fileOut(fileName);

    if (!fileOut.is_open())
    {
        cout << "Khong the mo tep " << fileName << " de ghi." << endl;
        return;
    }

    NodeSach *p = l.Head;
    bool check = false;

    while (p != NULL)
    {
        if (p->data.giamGia >= x && p->data.giamGia <= y)
        {
            // Ghi thông tin sách vào tệp tin
            fileOut << p->data.maSach << ";" << p->data.tenSach << ";" << p->data.tacGia << ";" << p->data.NXB
                    << ";" << p->data.ngayPhatHanh.ngay << "/" << p->data.ngayPhatHanh.thang << "/" << p->data.ngayPhatHanh.nam
                    << ";" << p->data.gia << ";" << p->data.soLuong << ";" << p->data.theLoai.maTheLoai << ";"
                    << p->data.theLoai.tenTheLoai << ";" << p->data.giamGia << ";" << p->data.gia * (1 - p->data.giamGia / 100.0) << endl;

            check = true;
        }
        p = p->next;
    }

    fileOut.close();

    if (check)
    {
        cout << "Da trich loc va luu sach co gia giam tu " << x << " den " << y << " vao tep " << fileName << endl;
    }
    else
    {
        cout << "Khong tim thay cuon sach nao co gia giam trong khoang tu " << x << " den " << y << endl;
    }
}

// Hàm để đếm số lượng sách có năm xuất bản nhất định
int demSachTheoNamXuatBan(ListSach &l, int namXuatBan)
{
    int count = 0;
    NodeSach *p = l.Head;

    // Duyệt qua danh sách sách
    while (p != nullptr)
    {
        // Kiểm tra xem năm xuất bản của cuốn sách có bằng với năm cần tìm hay không
        if (p->data.ngayPhatHanh.nam == namXuatBan)
        {
            count++;
            hienSach(p->data);
        }
        p = p->next;
    }

    return count;
}

// Hàm xuất danh sách các sách có thể loại là "Truyen tranh"
void xuatSachTheoLoai(ListSach &l, const char loaiCanTim[])
{
    NodeSach *p = l.Head;

    // Duyệt qua danh sách sách
    while (p != nullptr)
    {
        // Kiểm tra xem cuốn sách có loại sách là "Truyen tranh" hay không
        if (strcmp(p->data.theLoai.tenTheLoai, loaiCanTim) == 0)
        {
            hienSach(p->data);
        }
        p = p->next;
    }
}


// SAP XEP TANG DAN THEO MUC GIAM GIA (bubble sort-sap xep noi bot)
void sapXepTangDan_GiamGia(ListSach& l) {
    if (l.Head == NULL || l.Head->next == NULL) {
        cout << "\nDanh sach khong can sap xep!" << endl;
        return;
    }

    for (NodeSach* p = l.Head; p != NULL; p = p->next) {
        for (NodeSach* k = p->next; k != NULL; k = k->next) {
            if (p->data.giamGia > k->data.giamGia) {
                Sach tmp = p->data;
                p->data = k->data;
                k->data = tmp;
            }
        }
    }

    cout << "\nDa sap xep tang dan theo giam gia!" << std::endl;
}

// SỬA THÔNG TIN GIAM GIA CUA SÁCH CÓ MÃ NHẬP TỪ BÀN PHÍM
void suaThongTinSach(ListSach &l, char maSach[10])
{
    if (l.Head == NULL)
    {
        cout << "Danh sach rong. Khong the sua thong tin." << endl;
        return;
    }

    NodeSach *p = l.Head;
    while (p != NULL)
    {
        if (strcmp(p->data.maSach, maSach) == 0)
        {
            cout << "Nhap gia giam (%): ";
            cin >> p->data.giamGia;

            cout << "Da sua thong tin sach co ma " << maSach << " thanh cong." << endl;
            return;
        }
        p = p->next;
    }
    cout << "Khong tim thay sach co ma la: " << maSach << endl;
}

void menu(ListSach &l)
{
    while (1)
    {
        int opt;
        // system("cls");//Câu lệnh xoá màn hình
        cout << "\n============================MENU=============================";
        cout << "\n1. Them Node vao danh sach";
        cout << "\n2. Hien danh sach";
        cout << "\n3. Them 1 sach vao sau sach co ten nhap vao tu ban phim";
        cout << "\n4. Them n sach vao sau sach co ten nhap vao tu ban phim";
        cout << "\n5. Them 1 sach vao truoc sach co ten nhap vao tu ban phim";
        cout << "\n6. Them n sach vao truoc sach co ten nhap vao tu ban phim";
        cout << "\n7. Them 1 cuon sach vao vi tri bat ki";
        cout << "\n8. Xoa sach o dau";
        cout << "\n9. Xoa sach o cuoi";
        cout << "\n10. Xoa 1 cuon sach sau sach co ten nhap tu ban phim";
        cout << "\n11. Xoa 1 cuon sach o vi tri bat ki";
        cout << "\n12. Xoa 1 cuon sach co ten nhap tu ban phim";
        // cout << "\n13. Dem so loai sach dang co";
        // cout << "\n14. Tinh tong so luong cac loai sach";
        // cout << "\n15. Tim kiem thong tin sach theo ten";
        // cout << "\n16. Hien thong tin sach co % giam gia bang y va ghi vao file giamgia.txt";
        // cout << "\n17. Doc thong tin trong file giam gia";
        cout << "\n18. Ghi DS sach vao file";
        cout << "\n19. Doc file DS sach ";
        cout << "\n20. Xoa sach theo ngay phat hanh";
        // cout << "\n22. Sap xep ten sach giam dan(z-a)";
        // cout << "\n23. Tim kiem cac sach co the loai x";
        // cout << "\n24. Tim kiem cuon sach co gia cao nhat";
        // cout << "\n25. Tinh tong tien tat ca cac sach";
        // cout << "\n26. Tinh TBC tien cac cuon sach";
        cout << "\n21. Sap xep sach theo gia giam tang dan";
        cout << "\n22. Sua thong tin sach theo ma";
        // cout << "\n28. Trich loc sach co gia giam tu muc x den y va luu vao file trichloc.txt";
        // cout << "\n29. Doc thong tin sach tu file trichloc.txt";
        // cout << "\n30. Dem so luong sach theo nam xuat ban";
        // cout << "\n31. Hien cac sach co the loai la truyen tranh";
        cout << "\n0.  Thoat";
        cout << "\nNhap lua chon cua ban:";
        cin >> opt;
        if (opt == 1)
        {
            nhapListSach(l);
        }
        else if (opt == 2)
        {
            hienListSach(l);
        }
        else if (opt == 3)
        {
            char tenSachNhap[50];
            cout << "Nhap ten sach ma ban muon them vao sau: ";
            cin >> tenSachNhap;
            Sach sach;
            cout << "\nNhap thong tin sach ma ban muon them";
            nhapSach(sach);
            NodeSach *sachMoi = create_NodeSach(sach);

            addSachSauTen(l, tenSachNhap, sachMoi);
            hienListSach(l);
        }
        else if (opt == 4)
        {
            char tenSachNhap[50];
            cout << "Nhap ten sach ma ban muon them vao sau: ";
            cin >> tenSachNhap;
            int n;
            cout << "Nhap so luong sach can them: ";
            cin >> n;
            Sach sach;
            NodeSach *sachMoi;
            for (int i = 0; i < n; i++)
            {
                nhapSach(sach);
                sachMoi = create_NodeSach(sach);
                addSachSauTen(l, tenSachNhap, sachMoi);
            }

            hienListSach(l);
        }
        else if (opt == 5)
        {
            char tenSachNhap[50];
            cout << "Nhap ten sach ma ban muon them vao truoc: ";
            cin >> tenSachNhap;
            Sach sach;
            cout << "\nNhap thong tin sach ma ban muon them";
            nhapSach(sach);
            NodeSach *sachMoi = create_NodeSach(sach);

            addSachTruocTen(l, tenSachNhap, sachMoi);
            hienListSach(l);
        }
        else if (opt == 6)
        {
            char tenSachNhap[50];
            cout << "Nhap ten sach ma ban muon them vao truoc: ";
            cin >> tenSachNhap;
            int n;
            cout << "Nhap so luong sach can them: ";
            cin >> n;
            Sach sach;
            NodeSach *sachMoi;
            for (int i = 0; i < n; i++)
            {
                nhapSach(sach);
                sachMoi = create_NodeSach(sach);
                addSachTruocTen(l, tenSachNhap, sachMoi);
            }

            hienListSach(l);
        }
        else if (opt == 7)
        {
            int vt;
            cout << "Nhap vi tri ma ban muon them vao(0 la dau danh sach): ";
            cin >> vt;
            Sach sach;
            cout << "\nNhap thong tin sach ma ban muon them";
            nhapSach(sach);
            NodeSach *sachMoi = create_NodeSach(sach);

            addSachVaoViTriBatKy(l, sachMoi, vt);
            hienListSach(l);
        }
        else if (opt == 8)
        {
            deleteFirst(l);
            hienListSach(l);
        }
        else if (opt == 9)
        {
            deleteLast(l);
            hienListSach(l);
        }
        else if (opt == 10)
        {
            char tenSachNhap[50];
            cout << "\nNhap ten sach can xoa sau: ";
            cin >> tenSachNhap;
            deleteSachSauTen(l, tenSachNhap);
            hienListSach(l);
        }
        else if (opt == 11)
        {
            int vt;
            cout << "Nhap vi tri ma ban muon xoa(0 la dau danh sach): ";
            cin >> vt;
            deleteSachOViTriBatKy(l, vt);
            hienListSach(l);
        }
        else if (opt == 12)
        {
            char tenSachXoa[50];
            cout << "Nhap ten cuon sach ma ban muon xoa: ";
            cin >> tenSachXoa;
            deleteSachTheoTen(l, tenSachXoa);
            hienListSach(l);
        }
        else if (opt == 13)
        {
            cout << "Hien dang co " << Size(l) << " loai sach";
        }
        else if (opt == 14)
        {
            cout << "Tong so cuon sach hien co la " << tongSLSach(l);
        }
        else if (opt == 15)
        {
            char tenSachTim[50];
            cout << "Nhap ten sach muon tim kiem thong tin: ";
            cin >> tenSachTim;
            timSachTheoTen(l, tenSachTim);
        }
        else if (opt == 16)
        {
            float y;
            cout << "Nhap gia tri giam gia (y): ";
            cin >> y;
            hienSachCoGiamGiaBangY(l, y);
            luuSachCoGiamGiaBangYVaoFile(l, y, "giamgia.txt");
        }
        else if (opt == 17)
        {
            docThongTinSachTuFile("giamgia.txt");
        }
        else if (opt == 18)
        {
            ghiFile_Sach1(l);
        }
        else if (opt == 19)
        {
            docFile_Sach1(l);
        }
        else if (opt == 20)
        {
            int ngay, thang, nam;
            cout << "\n Nhap sach co ngay phat hanh ban muon xoa: " << endl;
            cout << " Ngay: ";
            cin >> ngay;
            cout << "Thang: ";
            cin >> thang;
            cout << "Nam: ";
            cin >> nam;
            deleteSachTheoNPH(l, ngay, thang, nam);
            hienListSach(l);
        }
        else if (opt == 30)
        {
            sapxepGiamDan_TenSach(l);
            hienListSach(l);
        }
        else if (opt == 23)
        {
            char theLoaiCanHien[50];
            cout << "\nNhap ten the loai can tim: ";
            cin >> theLoaiCanHien;
            hienThiTheoTheLoai(l, theLoaiCanHien);
        }
        else if (opt == 24)
        {
            Sach sachGiaCaoNhat = timSachGiaCaoNhat(l);
            cout << "\nCuon sach co gia cao nhat la: " << sachGiaCaoNhat.tenSach << ", Gia: " << sachGiaCaoNhat.gia << endl;
        }
        else if (opt == 25)
        {
            cout << "Tong tien tat ca cac cuon sach la: " << tongTienCacLoaiSach(l);
        }
        else if (opt == 26)
        {
            cout << "TBC tien cac cuon sach la: " << tbcTongTien(l);
        }
        else if (opt == 28)
        {
            float x, y;
            cout << "Nhap muc x: ";
            cin >> x;
            cout << "Nhap muc y: ";
            cin >> y;
            trichLocVaLuuSachTheoGia(l, x, y, "trichloc.txt");
        }
        else if (opt == 29)
        {
            docThongTinSachTuFile("trichloc.txt");
        }
        else if (opt == 30)
        {
            int namXuatBanCanTim;
            cout << "Nhap nam xuat ban can tim: ";
            cin >> namXuatBanCanTim;
            int soLuongSach = demSachTheoNamXuatBan(l, namXuatBanCanTim);

            // In kết quả
            if (soLuongSach > 0)
            {
                cout << "So luong sach co nam xuat ban " << namXuatBanCanTim << " la: " << soLuongSach << endl;
            }
            else
            {
                cout << "Khong co sach nao voi nam xuat ban " << namXuatBanCanTim << endl;
            }
        }
        else if(opt == 31){
            xuatSachTheoLoai(l, "truyen tranh");
        }
        else if (opt == 21)
        {
            sapXepTangDan_GiamGia(l);
            hienListSach(l);
        }
        else if (opt == 22)
        {
            char maSach[10];
            cout << "Nhap ma cua cuon sach can sua thong tin: ";
            cin >> maSach;
            suaThongTinSach(l, maSach);
            hienListSach(l);
        }
        else
        {
            break;
        }
    }
}
int main()
{
    ListSach l;
    init_ListSach(l);
    menu(l);

    system("pause");
    return 0;
}
