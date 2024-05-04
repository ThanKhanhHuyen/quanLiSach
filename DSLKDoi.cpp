#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
struct date
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
    date ngayPhatHanh;
    float gia;
    int soLuong;
};

struct NodeSach
{
    Sach data;
    NodeSach *next;
    NodeSach *prev;
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
};

NodeSach *create_NodeSach(Sach sach)
{
    NodeSach *p = new NodeSach();
    if (p == NULL)
    {
        cout << "Khong du bo nho !";
        exit(1);
    }
    p->data = sach;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

// Thêm vào đầu ds
void insertFirst(ListSach &l, NodeSach *p)
{
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
    }
    else
    {
        p->next = l.Head;
        l.Head->prev = p;
        l.Head = p;
    }
}

// Thêm vào cuối ds
void insertLast(ListSach &l, NodeSach *p)
{
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
    }
    else
    {
        l.Tail->next = p;
        p->prev = l.Tail;
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
        insertFirst(l, p);
    }
    if (opt == 2)
    {
        insertLast(l, p);
    }
    cout << "Thanh cong !" << endl;
}

void hienSach(Sach sach)
{
    cout << setw(20) << sach.maSach;
    cout << setw(20) << sach.tenSach;
    cout << setw(20) << sach.tacGia;
    cout << setw(20) << sach.NXB;
    cout << setw(20) << sach.ngayPhatHanh.ngay << "/" << sach.ngayPhatHanh.thang << "/" << sach.ngayPhatHanh.nam;
    cout << setw(20) << sach.gia;
    cout << setw(20) << sach.soLuong << endl;
}

void hienListSach(ListSach l)
{
    cout << setw(100) << "--------------------THONG TIN SACH--------------------"
         << endl;
    cout << setw(20) << "Ma sach";
    cout << setw(20) << "Ten sach";
    cout << setw(20) << "Tac gia";
    cout << setw(20) << "Nha xuat ban";
    cout << setw(27) << "Ngay phat hanh";
    cout << setw(20) << "Gia";
    cout << setw(20) << "So luong" << endl;
    NodeSach *p = l.Head;
    while (p != NULL)
    {
        hienSach(p->data);
        p = p->next;
    }
}

// Thêm 1 phim sau phim có ngày phát hành nhập từ bàn phím
void themSachVaoSauNPH(ListSach &l, int ngayNhap, int thangNhap, int namNhap, Sach sach)
{
    NodeSach *p = l.Head;
    nhapSach(sach);
    NodeSach *q = create_NodeSach(sach);
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
        cout << "Vi danh sach rong nen gia tri nhap vao se tu duoc them vao!";
    }
    else
    {
        while (p != NULL && (p->data.ngayPhatHanh.ngay != ngayNhap || p->data.ngayPhatHanh.thang != thangNhap || p->data.ngayPhatHanh.nam != namNhap))
        {
            p = p->next;
        }
        if (p != NULL && p != l.Tail)
        {
            q->next = p->next;
            p->next->prev = q;
            p->next = q;
            q->prev = p;
        }
        else if (p != NULL && p == l.Tail)
        {
            insertLast(l, q);
        }
        else if (p == NULL)
        {
            cout << "Khong tim thay cuon sach co ngay phat hanh ban da nhap!" << endl;
            return;
        }
    }
    cout << "Them thanh cong! " << endl;
}
// Thêm n phim sau phim có mã nhập từ bàn phím
void insertAfterSachCode(ListSach &l, char maSachNhap[50], NodeSach *phimMoi)
{
    NodeSach *p = l.Head;
    // Nếu ds rỗng
    if (l.Head == NULL)
    {
        l.Head = l.Tail = phimMoi;
        cout << "Vi danh sach rong nen gia tri nhap vao se tu duoc them vao!";
    }
    else
    {
        while (p != NULL && strcmp(maSachNhap, p->data.maSach) != 0)
        {
            p = p->next;
        }
        if (p != NULL && p != l.Tail)
        {
            phimMoi->next = p->next;
            p->next->prev = phimMoi;
            p->next = phimMoi;
            phimMoi->prev = p;
        }
        // Trường hợp q là số đứng cuối
        else if (p != NULL && p == l.Tail)
        {
            insertLast(l, phimMoi);
        }
    }
}

// Thêm 1 phim sau phim có tên nhập từ bàn phím
void insertAfterSachName(ListSach &l, char tenSachNhap[50], Sach sach)
{
    NodeSach *p = l.Head;
    nhapSach(sach);
    NodeSach *q = create_NodeSach(sach);
    // Nếu ds rỗng
    if (l.Head == NULL)
    {
        l.Head = l.Tail = p;
        cout << "Vi danh sach rong nen gia tri nhap vao se tu duoc them vao!";
    }
    else
    {
        while (p != NULL && strcmp(tenSachNhap, p->data.tenSach) != 0)
        {
            p = p->next;
        }
        if (p != NULL && p != l.Tail)
        {

            q->next = p->next;
            p->next->prev = q;
            p->next = q;
            q->prev = p;
        }
        // Trường hợp q là số đứng cuối
        else if (p != NULL && p == l.Tail)
        {
            insertLast(l, q);
        }
    }
}

// Xoá ở đầu ds
void deleteFirstSach(ListSach &l)
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !";
    }
    else if (l.Head != NULL)
    {
        NodeSach *p = l.Head;
        // Nếu list có 1 phần tử
        if (p->next == NULL)
        {
            l.Tail = NULL;
            l.Head = NULL;
        }
        else if (p->next != NULL)
        {
            l.Head = p->next;
            p->next->prev = NULL;
            p->next = NULL;
        }
        else if (l.Head == NULL)
        {
            cout << "\nDanh sach rong !";
        }

        delete (p);
    }
}

// Xoá ở cuối ds
void deleteLast(ListSach &l)
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong !";
    }
    else if (l.Tail != NULL)
    {
        NodeSach *p = l.Tail;
        // Nếu list có 1 phần tử
        if (p->prev == NULL)
        {
            l.Tail = NULL;
            l.Head = NULL;
        }
        else if (p->prev != NULL)
        {
            l.Tail = p->prev;
            p->prev->next = NULL;
            p->prev = NULL;
        }
        else if (l.Tail == NULL)
        {
            cout << "\nDanh sach rong !";
        }

        delete (p);
    }
}

// sắp xếp tăng dần từ a->z theo tên sách
void sapxepTangDan_TenSach(ListSach &l)
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
            if (strcmp(p->data.tenSach, k->data.tenSach) > 0)
            {
                Sach tmp = p->data;
                p->data = k->data;
                k->data = tmp;
            }
        }
    }
    cout << "\nDa sap xep!" << endl;
}

void xoaTheoNamSX(ListSach &l)
{
    if (l.Head == NULL)
    {
        cout << "\nDanh sach rong!" << endl;
    }
    else
    {
        int nam;
        cin.ignore();
        cout << "\nNhap nam can xoa: ";
        cin >> nam;
        NodeSach *p = l.Head;
        while (p != NULL)
        {
            if (p->data.ngayPhatHanh.nam == nam)
            {
                if (p == l.Head)
                {
                    // neu node can xoa o dau danh sach
                    l.Head = l.Head->next;
                    if (l.Head != NULL)
                        l.Head->prev = NULL;
                    NodeSach *temp = p;
                    p = p->next;
                    delete temp;
                }
                else if (p == l.Tail)
                {
                    // neu node can xoa o cuoi danh sach
                    l.Tail = l.Tail->prev;
                    if (l.Tail != NULL)
                        l.Tail->next = NULL;
                    NodeSach *temp = p;
                    p = p->next;
                    delete temp;
                }
                else
                {
                    // neu node can xoa o giua danh sach
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    NodeSach *temp = p;
                    p = p->next;
                    delete temp;
                }

                cout << "\nDa xoa thanh cong!" << endl;
            }
            else
            {
                p = p->next;
            }
        }
    }
}

void menu(ListSach &l)
{
    while (1)
    {
        int opt;
        // system("cls");//Câu lệnh xoá màn hình
        cout << "\n============================MENU=============================" << endl;
        cout << "\n1. Them Node vao danh sach";
        cout << "\n2. Hien danh sach";
        cout << "\n3. Them 1 sach vao sau sach co ngay phat hanh vao tu ban phim";
        cout << "\n3. Them n sach vao sau sach co ngay phat hanh vao tu ban phim";
        cout << "\n4. Them n sach vao sau sach co ten nhap vao tu ban phim";
        cout << "\n5. Xoa sach o dau danh sach";
        cout << "\n6. Xoa sach o cuoi danh sach";
        cout << "\n7. Sap xep tu a -z theo ten sach";
        cout << "\n8. Xoa cac sach theo nam san xuat nhap tu ban phim";
        cout << "\n0. Thoat";
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
            int ngayNhap, thangNhap, namNhap;
            cout << "\nNhap ngay phat hanh cua cuon sach ma ban muon them vao sau:" << endl;
            cout << "Nhap ngay: ";
            cin >> ngayNhap;
            cout << "Nhap thang: ";
            cin >> thangNhap;
            cout << "Nhap nam: ";
            cin >> namNhap;
            Sach sach;
            cout << "\nNhap thong tin phim ma ban muon them vao ";

            themSachVaoSauNPH(l, ngayNhap, thangNhap, namNhap, sach);
            hienListSach(l);
        }
        else if(opt==4){
            
        }
        else if (opt == 4)
        {
            char maNhap[10];
            cout << "\nNhap ma phim ma ban muon them vao sau:";
            cin >> maNhap;
            int n;
            cout << "Nhap so luong phim can chen: ";
            cin >> n;
            Sach sach;
            NodeSach *sachMoi;
            for (int i = 0; i < n; i++)
            {
                nhapSach(sach);
                sachMoi = create_NodeSach(sach);
                insertAfterSachCode(l, maNhap, sachMoi);
            }
            hienListSach(l);
        }
        else if (opt == 5)
        {
            deleteFirstSach(l);
            hienListSach(l);
        }
        else if (opt == 6)
        {
            deleteLast(l);
            hienListSach(l);
        }
        else if (opt == 7)
        {
            sapxepTangDan_TenSach(l);
            hienListSach(l);
        }
        else if (opt == 8)
        {
            xoaTheoNamSX(l);
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
