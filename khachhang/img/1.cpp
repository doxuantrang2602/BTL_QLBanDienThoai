#include <bits/stdc++.h>
#define se second
#define fi first
#define endl '\n'

using namespace std;

// Cap phat cho 1 node
// Kiem tra rong 
// Size
// insertFirst
// insertLast
// insertMiddle
// Xoa dau
// Xoa cuoi
// Xoa giua
// in 1 node
// in toan bo node
// Cac thuat toan sap xep, tim kiem,...

class KhachHang{
	private:	
		string name, sdt;
		int ma;
	public:
		friend istream &operator >> (istream& in,KhachHang& x){
			cout << "Nhap ma khach hang: "; in >> x.ma;
			cout << "Nhap ho ten: "; fflush(stdin); getline(in,x.name);
			cout << "Nhap sdt: "; fflush(stdin); getline(in, x.sdt);
			return in;
		}
		string getName(){
			return name;
		}
		string getSdt(){
			return sdt;
		}
		int getMa(){
			return ma;
		}	
		void nhapHoten(){
			cout << "Nhap ho ten: ";
			fflush(stdin); getline(cin,name);
		}
		void nhapSdt(){
			cout << "Nhap sdt: ";
			fflush(stdin); getline(cin,sdt);
		}
		

};

struct KH{
	KhachHang s;
	struct KH *prev;
	struct KH *next;
};

typedef struct KH* kh;

// cap phat dong cho 1 node
kh makeNode(KhachHang s){	
	kh tmp = new KH();
	tmp->s = s;
	tmp->prev = NULL;
	tmp->next = NULL;
	return tmp;
}

bool empty(kh a){
	return a == NULL;
}

int Size(kh a){
	int cnt =0;
	while(a != NULL){
		++cnt;
		a=a->next;
	}
	return cnt;
}


// Them 1 phan tu vao dau dslk
void insertFirst(kh *head,KhachHang s){
	kh tmp = makeNode(s);
	tmp->next =(*head);
	if(*head != NULL){
		(*head)->prev = tmp;
	}
	*head = tmp;
}
// Them phan tu vao cuoi dslk
void insertLast(kh *head,KhachHang s){
	kh newNode = makeNode(s); //cap phat cho newNode
	if(*head ==NULL){ // head tro den NULL thi newNode = head
		*head = newNode;
		return;
	}
	kh temp = *head;
	while(temp->next!=NULL){
		temp=temp->next;		
	}
	temp->next = newNode;
	newNode->prev = temp;
}
// Them phan tu vao giua dslk
void insertMiddle(kh *head, int k,KhachHang s){
	int n = Size(*head);
	if(k<0 || k >n+1){
		cout << "Vi tri chen khong hop le";
	}
	if(k == 1){
		insertFirst(head,s);
	}
	kh tmp = *head;
	for(int i=1;i<=k-1;i++){
		tmp= tmp->next;
	}
	kh newNode = makeNode(s);
	newNode->next=tmp;
	tmp->prev->next = newNode;
	tmp->prev = newNode->prev;
	newNode->prev = tmp->next;
}
void deleteFirst(kh &head)
{
	if(head == NULL) return;
	head = head->next;
	head->prev =NULL;
}
void deleteLast(kh &head){
	if(head == NULL) return;
	kh tmp;
	for(tmp=head; tmp!=NULL;tmp=tmp->next){
		if(tmp->next == NULL){
			kh tmp1 = tmp->prev;
			tmp1->next = NULL;
			tmp->prev = NULL;
		}
	}
}
void deleteMiddle(kh head,kh i)
{
	if(head == NULL && i == NULL) return;
	kh temp = i->prev;
	kh temp1 = i->next;
	temp->next = temp1;
	temp1->prev = temp;
	free(i);
}


void in(KhachHang s){
	cout << "-----------------------------\n";
	cout << "| Ma khach hang: " << s.getMa() <<endl;
	cout << "| Ho ten: " << s.getName() << endl;
	cout << "| So dien thoat: " << s.getSdt() << endl;
	cout << "-----------------------------\n";
}
void inds(kh a){
	cout << "Danh sach khach hang: \n";
	while(a != NULL){	
		in(a->s);
		a=a->next;		
	}
	cout << endl;
}

void editKhachHang(kh &head){
	string edit_name;
	string edit_sdt;
	while(1){
		cout << "	----------------Edit_MENU---------------" << endl;
		cout << "		1. Sua ho ten Khach hang \n";
		cout << "		2. Sua so dien thoai khach hang \n";
		cout << "		3. Hoan thanh! \n";
		cout << "	Ban muon sua gi? Hay nhap lua chon nao: ";	
		int c;
		cin >> c;
		if(c==1){
			head->s.nhapHoten();
		}
		else if(c == 2){
			head->s.nhapSdt();
		}
		else if(c == 3){
			cout << "Da sua xong khach hang ma " << head->s.getMa();
			break;
		}
		else{
			cout << "Lua chon sai ! Hay nhap lai" << endl;
		}
	}
		
}

void TimKiem(kh &head){
	cout << "*Nhap ma khach hang can tim: ";
	int ma_nhap;
	cin >> ma_nhap;
	kh a;
	int k=0;
	for(a=head;a!=NULL;a=a->next){
		if(a->s.getMa() == ma_nhap){
			k++;			
			cout << "	Da tim thay khach hang ma " << a->s.getMa() <<" !" << endl;;
			cout << "	-------------Search_Menu------------" << endl;
			cout << "		1. Xoa khach hang vua nhap" << endl;
			cout << "		2. Sua thong tin ho ten, sdt khach hang" << endl;
			cout << "	Hay nhap lua chon cua ban: ";
			int b; cin >> b;
			cout << endl;
			if(b==1){
				if(a == head){
					deleteFirst(head);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;	
				}
				else if(a->prev!=NULL && a->next == NULL)
				{
					deleteLast(a);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;
				 } 
				else if(a!=head && a->next !=NULL)
				{
					deleteMiddle(head,a);
					cout << "Da xoa khach hang ma " << a->s.getMa() << " !"<< endl;									
				 }
			}			 	
			else if(b == 2){
				editKhachHang(a);
				break;
			}
		}		
	}
	cout << endl;
	if(k==0)	
		cout << "Khong tim thay khach hang can tim! " << endl;
}
int main(){
	kh head = NULL;
	while(1){
		cout << "----------------MENU--------------\n";
		cout << "1.Them khach hang vao dau danh sach  \n";
		cout << "2.Them khach hang vao cuoi danh sach \n";
		cout << "3.Them khach hang vao giua danh sach \n";
		cout << "4.Duyet danh sach khach hang         \n";
		cout << "5.Tim kiem khach hang theo ma        \n";
		cout << "0.Thoat!                             \n";
		cout << "----------------------------------\n";
		cout << "Nhap lua chon: ";
		int lc; cin >> lc;
		cout << endl;
		if(lc == 1){
			KhachHang x;
			cin >> x;
			insertFirst(&head,x);
			cout << "Ban co muon insertFirst (Y or N)? : ";
			string s; getline(cin,s);
			string s1 = "Y";
			string s2 = "N";
			cout << endl;
			while(s == s1){
				KhachHang x;
				cin >> x;
				insertFirst(&head,x);
				cout << "Ban van muon inserFirst(Y or N)? : "; getline(cin,s);
				cout << endl;
			}
			cout << endl;
			while(s == s2){
				cout << "Ket thuc !\n";
			    break;
			}
		}
		else if(lc == 2){
			KhachHang x;
			cin >> x;
			insertLast(&head,x);
			cout << "Ban co muon insertLast(Y or N): ";
			string s; getline(cin,s);
			cout << endl;
			string s1 = "Y";
			string s2 = "N";
			while(s == s1){
				KhachHang x;
				cin >> x;
				insertLast(&head,x);
				cout << "Ban van muon insertLast(Y or N)? : "; getline(cin,s);
				cout << endl;
			}
			while(s == s2){
				cout << "Ket thuc !\n";
			    break;
			}
		}
		else if(lc == 3){			
			int k; 
			cout << "Nhap vi tri can chen: ";
			cin >> k;
			KhachHang x;
			cin >> x;
			insertMiddle(&head,k,x);
			cout << "Ban co muon insertMiddle(Y or N): ";
			string s; getline(cin,s);
			string s1 = "Y";
			string s2 = "N";
			cout << endl;
			while(s == s1){				
				int k; 
				cout << "Nhap vi tri can chen: ";
				cin >> k;
				KhachHang x;
				cin >> x;
				insertMiddle(&head,k,x);
				cout << "Ban van muon insertMiddle(Y or N)?: "; getline(cin,s);
				cout << endl;
			}
			while(s == s2){
				cout << "Ket thuc !\n";
			    break;
			}
		}
		else if(lc == 4){
			inds(head);
		}
		else if(lc == 5){
			TimKiem(head);
		}
		else if(lc == 0){
			break;
		}
		else{
			cout << "Hay nhap lai lua chon !" << endl;
		}
	}
	return 0;
}