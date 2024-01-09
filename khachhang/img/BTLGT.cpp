#include<bits/stdc++.h>

using namespace std;


struct Khachhang{
    int mkh;
    char tenKH[25];
    char sdt[25];
    char chuyenNganh[30];
    float diemTK;
    
};
typedef struct Khachhang KH;
struct Node
{
    //khai bao thanh phan du lieu co kieu int
    KH data;
    //khai bao con tro next co kieu Node de chua dia chi phan tu sau
    Node *next;
    //khai bao con tro prev co kieu Node de chua dia chi phan tu truoc
    Node *prev;
};
typedef struct Node NODE;
struct doulist{
    //thanh phan dau danh sach
    NODE *pHead;
    //thanh phan cuoi danh sach
    NODE *pTail;
};
typedef struct doulist DLIST;
void KhoiTao(DLIST ds){
    //dat dia chi dau danh sach bang NULL
    ds.pHead = NULL;
    //dat dia chi cuoi danh sach bang NULL
    ds.pTail = NULL;
}


NODE* TaoNode(KH x) {
    //tao mot node p moi
    NODE *p;
    p = new NODE;
    //neu p==NULL thi khong du bo nho va ket thuc viec tao node
    if (p==NULL) {
        cout<<"KHONG DU BO NHO";
        return NULL;
    }
    //gan thanh phan data = x
    p->data=x;
    //gan con tro next = NULL
    p->next=NULL;
    //gan con tro prev = NULL
    p->prev = NULL;
    //tra ve node p da tao
    return p;
}
void ThemCuoi(DLIST &ds, NODE*p){
    //kiem tra danh sach rong neu rong thi them vao dau va cuoi
    if (ds.pHead == NULL){
        ds.pHead = ds.pTail = p;
    }else{
        //dat con tro next cua pTail hien tai vao p la node can them cuoi
        ds.pTail->next = p;
        //dat con tro prev cua node p ve phan tu cuoi danh sach
        p->prev = ds.pTail;
        //thay doi lai phan tu cuoi danh sach
        ds.pTail = p;
    }
}
void Nhap(DLIST &ds, int n){
    cout<<"NHAP VAO THONG TIN HOC VIEN\n";
    //duyet N lan
    for(int i = 0; i < n; i++){
        //nhap du lieu la cho hoc vien thu i
        KH x;
        cout<<"Nhap MaHV: ";
        cin>>x.mkh;
        cout<<"Nhap TenHV: ";
        fflush(stdin);
        cin>>x.tenKH;
        cout<<"Nhap lop: ";
        fflush(stdin);
        cin>>x.sdt;
        printf("Chuyen nganh: ");
        fflush(stdin);
        cin>>x.chuyenNganh;
        cout<<"Diem TK: ";
        cin>>x.diemTK;
        cout<<endl<<endl;
        //tao node p
        NODE *p = new NODE;
        //dua du lieu vua nhap vao node p
        p = TaoNode(x);
        //dua node p vao ham them cuoi va truyen vao node p vua tao
        ThemCuoi(ds,p);
    }
}
void Xuat(DLIST ds){
    //khoi tao mot node
    NODE *p = new NODE;
    //duyet tu dau danh sach den cuoi danh sach voi dieu kien p!=NULL
    for(p = ds.pHead; p!= NULL; p=p->next){
        //hien thi du lieu cua tung hoc vien
        cout<<" " <<p->data.mkh<<" " <<p->data.tenKH<<" " <<p->data.sdt<< " "<<p->data.chuyenNganh<< " "<<p->data.diemTK<<endl;
    }
}



NODE* TimKiem(DLIST ds, int mkh){
    //tao node p
    NODE *p;
    //gan p bang phan tu dau danh sach
    p = ds.pHead;
    //su dung vong lap
    while ((p!=NULL) && (p->data.mkh!=mkh)){
        p=p->next;
    }
    //tra ve ket qua, neu NULL thi khong tim thay
    return p;
}


void XoaDau(DLIST &ds){
    //gan p bang phan tu dau danh sach
    NODE *p = ds.pHead;
    //thuc hien gan lai phan tu dau danh sach
    ds.pHead = ds.pHead->next;
    ds.pHead->prev = NULL;
    //neu khong ton tai phan tu dau danh sach
    if (ds.pHead==NULL){
        ds.pTail = NULL;
    }
    //thay doi con tro next ve NULL
    p->next = NULL;
    //xoa node p duoc gan bang phan tu dau danh sach
    delete p;
}
void XoaCuoi (DLIST &ds){
    //tao node p va gan bang phan tu cuoi danh sach
    NODE *p = ds.pTail;
    //thuc hien gan lai phan tu cuoi danh sach
    ds.pTail = ds.pTail->prev;
    ds.pTail->next = NULL;
    //kiem tra phan tu cuoi neu rong
    if (ds.pTail==NULL){
        ds.pHead = NULL;
    }
    //thay doi con tro prev cua node p ve NULL
    p->prev = NULL;
    //xoa p duoc gan bang phan tu cuoi danh sach
    delete p;
}


void XoaTheoKhoaK(DLIST &ds, int mkh){
    //tim kiem theo du lieu x va gan vao node p
    NODE *p = TimKiem(ds, mkh);
    //neu tim thay ket qua
    if(p != NULL){
        //neu p->prev == NULL thuc hien xoa dau
        if (p->prev==NULL){
            XoaDau(ds);
            return;
        }
        //neu p->next == NULL thuc hien xoa cuoi
        if (p->next==NULL){
            XoaCuoi(ds);
            return;
        }
        //thay doi lai lien ket cua phan tu co khoa K can xoa
        p->prev->next = p->next;
        p->next->prev = p->prev;
        //gan con tro prev va next cua phan tu co khoa K can xoa ve null
        p->prev = NULL; 
        p->next = NULL;
        //xoa node p co phan tu la khoa k
        delete p;
    }
}



void Menu(DLIST &ds)
{
    int a;
    int Ma;
    KhoiTao(ds);
    do
    {
        cout<<"\n Ban chon 0,1,2";
        cout<<"\n\nNhap so can chon roi bam enter";
        cout<<"\n\n\n 0 - Thoat";
        cout<<"\n 1 - Xoa khach hang theo ma";
        cout<<"\n 2 - Sua thong tin";
       
        cin>>a;
        switch(a)
        {
            case 1:
                {
                     int mhv;
                    cout<<"\nNHAP MA HOC VIEN: "; 
                    cin>>mhv;
                    //goi ham xoa theo khoa k voi k = mhv
                    XoaTheoKhoaK(ds,mhv);
                    cout<<"\nDANH SACH  XOA THEO MA HOC VIEN %d\n"<<mhv;
                }
            case 2:
                {
                    Xuat(ds);
                    break;
                }
            
            case 0:
                {
                    break;
                }
            default: printf("\nBan chon sai vui long chon lai!");
        }
    }while(a != 0);
   
   
}

int main(){
    //khai bao mot danh sach lien ket doi
    DLIST ds;
    //nhap n phan tu 
    int n;
    cout<<"NHAP N: ";
    cin>>n;
    //khoi tao danh sach
    KhoiTao(ds);
    //goi ham nhap tryuyen vao danh sach va N phan tu
    Nhap(ds,n);
    //goi ham xuat cac du lieu co trong danh sach
    cout<<"DANH SACH HOC VIEN VUA NHAP\n";
    Xuat(ds);
    Menu(ds);
    //Xoa theo ma hoc vien
    Xuat(ds);
}
