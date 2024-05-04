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
    NodeSach *left;
    NodeSach *right;
};
typedef NodeSach *Tree;

NodeSach *create_Node(Sach sach)
{
    NodeSach *p = new NodeSach();
    if (p == NULL)
    {
        cout << "Khong du bo nho!";
        exit(1);
    }
    p->data = sach;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void init_Tree(Tree &root)
{
    root = NULL;
}



void AddNode(Tree &root, Sach sach){
    if(root == NULL){
        NodeSach *p = create_Node(sach);
        root = p;
    }
    else
    {
        if (strcmp(root->data.maSach, sach.maSach) > 0)
        {
            AddNode(root->left, sach);
        }
        else if (strcmp(root->data.maSach, sach.maSach) < 0)
        {
            AddNode(root->right, sach);
        }
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

void hienSach(Tree root)
{
    cout << setw(20) << root->data.maSach;
    cout << setw(20) << root->data.tenSach;
    cout << setw(20) << root->data.tacGia;
    cout << setw(20) << root->data.NXB;
    cout << setw(20) << root->data.ngayPhatHanh.ngay << "/" << root->data.ngayPhatHanh.thang << "/" << root->data.ngayPhatHanh.nam;
    cout << setw(20) << root->data.gia;
    cout << setw(20) << root->data.soLuong << endl;
}

void hienListSach()
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
}

void write_NLR(char fileName[], Tree root)
{
    NodeSach *temp = new NodeSach();
    init_Tree(temp);
    NodeSach *p;
    while (root)
    {
        if (root->left == NULL)
        {
            AddNode(temp, root->data);
            root = root->right;
        }
        else
        {
            p = root->left;
            while (p->right && p->right != root)
            {
                p = p->right;
            }
            if (p->right == NULL)
            {
                p->right = root;
                AddNode(temp, root->data);
                root = root->left;
            }
            else
            {
                p->right = NULL;
                root = root->right;
            }
        }
    }
    FILE *of;
    of = fopen(fileName, "w");

    while (temp)
    {
        if (temp->left == NULL)
        {
            struct Sach inp2 = temp->data;
            fwrite(&inp2, sizeof(struct Sach), 1, of);
            temp = temp->right;
        }
        else
        {
            p = temp->left;
            while (p->right && p->right != temp)
            {
                p = p->right;
            }
            if (p->right == NULL)
            {
                p->right = temp;
                struct Sach inp2 = temp->data;
                fwrite(&inp2, sizeof(struct Sach), 1, of);
                temp = temp->left;
            }
            else
            {
                p->right = NULL;
                temp = temp->right;
            }
        }
    }
    fclose(of);
}