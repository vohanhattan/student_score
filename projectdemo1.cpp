#include<stdio.h>
#include<conio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include"TextTable.h"
using namespace std;
struct DATE {
	int ngay;
	int thang;
	int nam;
};
struct LOP{
	char MaLop[30];
	char TenLop[50];
	char Khoa[50];
	char HeDaoTao[30];
};
struct HSSV {
	int MSSV;
	char hoten[30];
	char gtinh[5];
	DATE NgSinh;
	LOP Lophoc;
	int NamNhapHoc;
	float DiemTong = 0;
	char XepLoai[30] = "-";
};
struct Mon{
	int MaMon;
	char TenMon[100];
	int  TinChi;
	char LoaiMonHoc[50];
	char TenGiangVien[50];

};
struct Diem{
	int MSSV;
	int MaMon;
	int HocKi;
	int NamHoc;
	float DiemGiuaKi;
	float DiemCuoiki;
	float DiemTongMon = 0;
	char KetQuaMon[30]="-";
	char DiemChu[5]="-";
};
struct NodeSV {
	HSSV data;
	struct NodeSV* next;
};
struct NodeMon{
	Mon MonHoc;
	struct NodeMon* next;
};
struct NodeDiem{
	Diem DiemHoc;
	struct NodeDiem* next;
};
int keyPress(int i);
void addFirstSV(NodeSV*& head, HSSV x);
void addLastSV(NodeSV*& head, HSSV x);
void addItemSV(NodeSV*& head, NodeSV*& p, HSSV x);
bool isEmptySV(NodeSV*& head) {
	return head == NULL;
}
void deleteListSV(NodeSV*& head) {
	NodeSV* p = head;
	while (head != NULL) {
		head = head->next;
		delete p;
		p = head;
	}
}
bool isEmptyMH(NodeMon*& head) {
	return head == NULL;
}
void deleteListMH(NodeMon*& head) {
	NodeMon* p = head;
	while (head != NULL) {
		head = head->next;
		delete p;
		p = head;
	}
}
bool isEmptyDiem(NodeDiem*& head) {
	return head == NULL;
}
void deleteListDiem(NodeDiem*& head) {
	NodeDiem* p = head;
	while (head != NULL) {
		head = head->next;
		delete p;
		p = head;
	}
}
void printLine(int n);
void printListSV(NodeSV* n);
void tinhDTBMon(Diem& x);
void KetQuaMonHoc(Diem& x);
void TinhDiemChu(Diem& x);
void XepLoaiSinhVien(HSSV& x);
void nhapSV(NodeSV*& head);
void nhapvaodauDSSV(NodeSV *&head);
void capNhatSV(NodeSV*& head, int id);
int xoaTheoIDSV(NodeSV*& head, int id);
void timKiemTheoTenSV(NodeSV*& head, char ten[]);
void timKiemTheoMSSV(NodeSV *& head,int MSSV);
void sapxepTheoDTBSV(NodeSV*& head);
void sapXepTheoTenSV(NodeSV*& head);
void docFileSV(NodeSV*& head, char fileNameSV[]);
void ghiFileSV(NodeSV* head, char fileNameSV[]);
int ngayHopLe(int nDay, int nMonth, int nYear);
int tinhSoNgayTrongThang(int nMonth, int nYear);
bool laNamNhuan(int nYear);
void printMSSV(NodeSV* n);
string formatDate(int ngay, int thang, int nam);
void sapXepSinhVienKhoa(NodeSV*& head);
void addLastMH(NodeMon*& mh,Mon x);
void nhapMH(NodeMon*& mh) ;
void capNhatThongTinMH(NodeMon*& mh,Mon& x,int id);
void capNhatMH(NodeMon*& mh, int id);
int xoaTheoIDMH(NodeMon*& mh, int id);
void timKiemTheoTenMon(NodeMon*& head, char ten[]);
void timKiemTheoMaMon(NodeMon *& head,int mamon);
void sapxepTheoTC(NodeMon*& head);
void printListMH(NodeMon* n);
void addLastDiem(NodeDiem*& dm,Diem x);
void nhapDiem(NodeDiem*& dm, NodeSV*& sv, NodeMon*& mon); 
void capNhatThongTinDiem(NodeSV*& sv,NodeMon*& mon,NodeDiem*& dm,Diem& x);
void capNhatDiem(NodeSV*& sv,NodeMon*& mon,NodeDiem*& dm, int id, int mamon,int hocki, int namhoc);
int xoaTheoIDDiem(NodeDiem*& dm, int id);
void timKiemTheoMaSV(NodeDiem *& head,int mssv);
void sapxepTheoDiemTong(NodeDiem*& head);
void printListDiem(NodeDiem* n);
void docFileMon(NodeMon*& head, char fileNameMon[]);
void ghiFileMon(NodeMon* head, char fileNameMon[]);
int check_ID_MonHoc(NodeMon *& head,int mamon);
void timKiemTheoTenGiangVien(NodeMon*& head, char ten[]);
int check_MSSV_SinhVien(NodeSV *& head,int mssv);
void docFileDiem(NodeDiem*& head, char fileNameDiem[]);
void ghiFileDiem(NodeDiem*& head, char fileNameDiem[]);
int check_MSSV_Diem(NodeDiem *& head,int mssv);
int xoaTheoMaMonDiem(NodeDiem*& dm, int id);
int check_MaMon_Diem(NodeDiem *& head,int mamon);
int xoaTheoID_Diem(NodeDiem*& dm, int id, int mamon,int hocki, int namhoc);
int check_Hocki_NamHoc_Diem(NodeDiem *& head,int mssv,int mamon,int hocki,int namhoc);
void TraCuuDiem_Theo_MSSV(NodeDiem* n,NodeSV* sv,NodeMon* mon,int mssv);
void tinhDiemTong(NodeDiem* diem,NodeSV* sv);
int main()
{
	int key;
	char fileNameSV[] = "sinhvien.txt";
	char fileNameMon[]="monhoc.txt";
	char fileNameDiem[]="diem.txt";
	NodeSV* head = NULL;
	NodeMon* mh = NULL;
	NodeDiem* dm =NULL;
	docFileSV(head, fileNameSV);
	docFileMon(mh, fileNameMon);
	docFileDiem(dm,fileNameDiem);
	tinhDiemTong(dm,head);
	while (true) {
		cout << "\n";
		cout << " Chuc nang quan ly thong tin sinh vien \n";
		cout << "====================Student====================\n";
		cout << "|| 1. Doc File Sinh vien                     ||\n";
		cout << "|| 2. Them Sinh Vien                         ||\n";
		cout << "|| 3. Them Sinh Vien vao dau                 ||\n";
		cout << "|| 4. Cap Nhat Sinh Vien Theo MSSV           ||\n";
		cout << "|| 5. Xoa Sinh Vien Theo MSSV                ||\n";
		cout << "|| 6. Tim Sinh Vien Theo Ten                 ||\n";
		cout << "|| 7. Tim Sinh Vien Theo MSSV                ||\n";
		cout << "|| 8. Sap Xep DS Sinh Vien Theo Diem         ||\n";
		cout << "|| 9. Sap Xep Sinh Vien Theo He dao tao      ||\n";
		cout << "|| 10. In ra danh sach Sinh Vien             ||\n";
		cout << "|| 11. Xuat Danh Sach Sinh Vien Ra File      ||\n";
		cout << "|| 12. Kiem Tra Danh Sach sinh vien Trong    ||\n";
		cout << "|| 13. Sap xep SV theo nam nhap hoc          ||\n";
		cout << "===================Mon Hoc=====================\n";
		cout << "|| 14. Doc File cac Mon hoc                  ||\n";
		cout << "|| 15. Them Mon Hoc                          ||\n";
		cout << "|| 16. Cap Nhat Mon Hoc Theo Ma Mon hoc      ||\n";
		cout << "|| 17. Xoa Mon hoc Theo Ma so                ||\n";
		cout << "|| 18. Tim Mon hoc Theo Ten mon              ||\n";
		cout << "|| 19. Tim Mon hoc Theo ma so mon            ||\n";
		cout << "|| 20. Sap Xep Danh sach mon theo tin chi    ||\n";
		cout << "|| 21. In ra danh sach Mon Hoc               ||\n";
		cout << "|| 22. Kiem Tra Danh Sach mon hoc Trong      ||\n";
		cout << "|| 23. Xuat danh sach mon hoc ra file        ||\n";
		cout << "|| 24. Tim Mon hoc theo ten giang vien       ||\n";
		cout << "===================Diem========================\n";
		cout << "|| 25. Them Diem Sinh Vien                   ||\n";
		cout << "|| 26. Cap Nhat Diem cua sinh vien           ||\n";
		cout << "|| 27. Xoa Diem SV Theo cac tieu chi         ||\n";
		cout << "|| 28. Tim ket qua SV Theo MSSV              ||\n";
		cout << "|| 29. Sap Xep ket qua theo Diem Tong        ||\n";
		cout << "|| 30. In ra danh sach ket qua               ||\n";
		cout << "|| 31. Kiem Tra Danh Sach Ket Qua Trong      ||\n";
		cout << "|| 32. Save file diem                        ||\n";
		cout << "=================Tra Cuu ======================\n";
		cout << "|| 33. Tra cuu chi tiet diem theo MSSV       ||\n";
		cout << "|| 0. Thoat                                  ||\n";
		cout << "===================END========================\n";
		key = keyPress(1);
		switch (key) {
		case 1:
			docFileSV(head, fileNameSV);
			if (!isEmptySV(head)) {
				printf("\nDoc file %s thanh cong!", fileNameSV);
			}
			else {
				printf("\nDoc file %s khong thanh cong!", fileNameSV);
			}
			break;
		case 2:
			cout << "\nThem mot sinh vien.";
			nhapSV(head);
			printf("\nSuccessfuly!");
			break;
		case 3:
			cout << "\nNhap vao dau danh sach sinh vien.";
            nhapvaodauDSSV(head);
            printf("\nSuccessfuly!");
            break;
		case 4:
			if (!isEmptySV(head)) {
				int id;
				printMSSV(head);
				cout << "\nChinh sua thong tin sinh vien theo ID. ";
				cout << "\nNhap ID: "; cin >> id;
				capNhatSV(head, id);
			}
			else { cout << "\nDanh sach Student empty!"; }
			break;
		case 5:
			if (!isEmptySV(head)) {
				int id;
				cout << "\nXoa sinh vien theo ID .";
				cout << "\nNhap ID: "; cin >> id;
				if (xoaTheoIDSV(head, id) == 1) {
					printf("\nSinh vien co id = %d da bi xoa.", id);
					while(check_MSSV_Diem(dm,id))
						if(xoaTheoIDDiem(dm,id)==1);
				}
			}
			else { cout << "\nDanh sach Sinh Vien trong!"; }
			break;
		case 6:
			if (!isEmptySV(head)) {
				cout << "\nTim kiem Student theo ten.";
				char strTen[30];
				cout << "\nNhap ten de tim kiem: ";fflush(stdin); gets(strTen) ;
				timKiemTheoTenSV(head, strTen);
			}
			else { cout << "\nDanh sach Student empty!"; }
			break;
		case 7:
			if (!isEmptySV(head)) {
				cout << "\nTim kiem Student theo MSSV.";
				int mssv;
				cout << "\nNhap mssv de tim kiem: "; 
                scanf("%d",&mssv);
				timKiemTheoMSSV(head, mssv);
			}
			else { cout << "\nDanh sach Student empty!"; }
			break;
		case 8:
			if (!isEmptySV(head)) {
				cout << "\nSap xep Student theo diem trung binh (GPA).";
					sapxepTheoDTBSV(head);
				printListSV(head);
			}
			else {
				cout << "\nDanh sach Student empty!";
			}
			break;
		case 9:
			if (!isEmptySV(head)) {
				cout << "\nSap xep Student theo ten.";
				sapXepTheoTenSV(head);
				printListSV(head);
			}
			else {
				cout << "\nDanh sach Student empty!";
			}
			break;
		case 10:
			if (!isEmptySV(head)) {
				tinhDiemTong(dm,head);
				cout << "\nHien thi danh sach Student.\n";
				printListSV(head);
			}
			else {
				cout << "\nDanh sach Student empty!";
			}
			break;
		case 11:
			if (!isEmptySV(head)) {
				tinhDiemTong(dm,head);
				cout << "\nGhi danh sach Student vao file.";
				ghiFileSV(head, fileNameSV);
			}
			else {
				cout << "\nDanh sach Student empty!";
			}
			printf("\nGhi danh sach Student vao file %s thanh cong!", fileNameSV);
			break;
        case 12:
            if(isEmptySV(head)){
                cout << "\ndanh sach trong.";               
            }
            else cout << "\ndanh sach khong trong.";  
            break;

		case 13:
			if (!isEmptySV(head)) {
				cout << "\nSap xep danh sach sinh vien theo khoa";
				sapXepSinhVienKhoa(head);
				printListSV(head);
			}
			else {
				cout << "\nDanh sach Student empty!";
			}
			break;
		case 14:
			tinhDiemTong(dm,head);
			docFileMon(mh, fileNameMon);
			if (!isEmptyMH(mh)) {
				printf("\nDoc file %s thanh cong!", fileNameMon);
			}
			else {
				printf("\nDoc file %s khong thanh cong!", fileNameMon);
			}
			break;
		case 15:
			cout << "\nThem mot mon Hoc.";
			nhapMH(mh);
			printf("\nSuccessfuly!");
			break;
		case 16:
			if (!isEmptyMH(mh)) {
				int id;
				printListMH(mh);
				cout << "\nChinh sua thong tin sinh vien theo Ma Mon. ";
				cout << "\nNhap ID: "; cin >> id;
				capNhatMH(mh, id);
			}
			else { cout << "\nDanh sach Mon Hoc empty!"; }
			break;
		case 17:
			if (!isEmptyMH(mh)) {
				int id;
				cout << "\nXoa Mon Hoc theo Ma Mon .";
				cout << "\nNhap Ma Mon: "; cin >> id;
				if (xoaTheoIDMH(mh, id) == 1) {
					printf("\nMon Hoc Co Ma Mon = %d da bi xoa.", id);
					while(check_MaMon_Diem(dm,id))
					if(xoaTheoMaMonDiem(dm,id)==1);
				}
			}
			else { cout << "\nDanh sach Mon Hoc Trong!"; }
			break;
		case 18:
			if (!isEmptyMH(mh)) {
				cout << "\nTim kiem Mon Hoc theo ten.";
				char strTen[30];
				cout << "\nNhap ten mon de tim kiem: ";fflush(stdin); gets(strTen) ;
				timKiemTheoTenMon(mh, strTen);
			}
			else { cout << "\nDanh sach mon hoc empty!"; }
			break;
		case 19:
			if (!isEmptyMH(mh)) {
				cout << "\nTim kiem Mon Hoc theo Ma Mon.";
				int mamon;
				cout << "\nNhap ma mon de tim kiem: "; 
                scanf("%d",&mamon);
				timKiemTheoMaMon(mh, mamon);
			}
			else { cout << "\nDanh sach Mon empty!"; }
			break;
		case 20:
			if (!isEmptyMH(mh)) {
				cout << "\nSap xep Mon Hoc theo tin chi.";
				sapxepTheoTC(mh);
				printListMH(mh);
			}
			else {
				cout << "\nDanh sach Mon hoc empty!";
			}
			break;
		case 21:
			if (!isEmptyMH(mh)) {
				cout << "\nHien Thi danh sach mon Hoc";
				printListMH(mh);
			}
			else {
				cout << "\nDanh sach Mon hoc empty!";
			}
			break;
		case 22:
			if(isEmptyMH(mh)){
				cout << "\n danh sach trong";
			}
			else
				cout << "\n danh sach khong trong";
			break;
		case 23:
			if (!isEmptyMH(mh)) {
				cout << "\nGhi danh sach mon hoc vao file.";
				ghiFileMon(mh, fileNameMon);
			}
			else {
				cout << "\nDanh sach mon hoc empty!";
			}
			printf("\nGhi danh sach mon vao file %s thanh cong!", fileNameMon);
			break;
		case 24:
			if (!isEmptyMH(mh)) {
				cout << "\nTim kiem Mon Hoc theo ten giang vien.";
				char strTenGV[30];
				cout << "\nNhap ten giang vien de tim kiem: ";fflush(stdin); gets(strTenGV) ;
				timKiemTheoTenGiangVien(mh, strTenGV);
			}
			else { cout << "\nDanh sach mon hoc empty!"; }
			break;
		case 25:
			cout << "\nNhap diem sinh vien theo MSSV.";
			printListSV(head);
			printListMH(mh);
			nhapDiem(dm,head,mh);
			tinhDiemTong(dm,head);
			printf("\nSuccessfuly!");
			break;
		case 26:
			if (!isEmptyDiem(dm)) {
				int id26,mamon26,hocki26,namhoc26;
				printListDiem(dm);
				cout << "\nChinh sua Ket qua sinh vien theo MSSV. ";
				cout << "\nNhap MSSV: "; cin >> id26;
				cout << "\nNhap Ma Mon: "; cin >> mamon26;
				cout << "\nNhap Hoc ki: "; cin >> hocki26;
				cout << "\nNhap Nam Hoc: "; cin >> namhoc26;
				capNhatDiem(head,mh,dm, id26,mamon26,hocki26,namhoc26);
			}
			else { cout << "\nDanh sach Student empty!"; }
			break;
		case 27:
			if (!isEmptyDiem(dm)) {
				int id,mamon,hocki,namhoc;
				printListDiem(dm);
				cout << "\nXoa Ket Qua Sinh Vien.";
				cout << "\nNhap MSSV: "; cin >> id;
				cout << "\nNhap Ma Mon: "; cin >> mamon;
				cout << "\nNhap Hoc ki: "; cin >> hocki;
				cout << "\nNhap Nam Hoc: "; cin >> namhoc;
				if (xoaTheoID_Diem(dm, id,mamon,hocki,namhoc) == 1) {
					printf("\nKet Qua Sinh Vien co MSSV = %d da bi xoa.", id);
				}
				
			}
			else { cout << "\nDanh sach Ket Qua Trong!"; }
			break;
		case 28:
			if (!isEmptyDiem(dm)) {
				cout << "\nTim kiem ket qua SV theo MSSV.";
				int mssv;
				cout << "\nNhap mssv de tim kiem: "; 
                scanf("%d",&mssv);
				timKiemTheoMaSV(dm, mssv);
			}
			else { cout << "\nDanh sach Ket Qua empty!"; }
			break;
		case 29:
			if (!isEmptyDiem(dm)) {
				cout << "\nSap xep Ket Quan theo Diem Tong.";
				sapxepTheoDiemTong(dm);
				printListDiem(dm);
			}
			else {
				cout << "\nDanh sach ket qua SV empty!";
			}
			break;
		case 30:
			if (!isEmptyDiem(dm)) {
				tinhDiemTong(dm,head);
				cout << "\nHien Thi Ket Quan Sinh Vien";
				printListDiem(dm);
			}
			else {
				cout << "\nDanh sach Ket Qua empty!";
			}
			break;
		case 31:
			if(isEmptyDiem(dm)){
				cout << "\n danh sach trong";
			}
			else
				cout << "\n danh sach khong trong";
			break;
		case 32:
			if (!isEmptyDiem(dm)) {
				tinhDiemTong(dm,head);
				cout << "\nGhi danh sach mon hoc vao file.";
				ghiFileDiem(dm, fileNameDiem);
			}
			else {
				cout << "\nDanh sach diem empty!";
			}
			printf("\nGhi danh sach diem vao file %s thanh cong!", fileNameDiem);
			break;
		case 33:
			if (!isEmptyDiem(dm)) {
				int id33;
				tinhDiemTong(dm,head);
				printMSSV(head);
				cout << "\nTra cuu thong tin sinh vien theo MSSV. ";
				cout << "\nNhap MSSV: "; cin >> id33;
				if(check_MSSV_SinhVien(head,id33)==0)
				{
					cout << "\nKhong co sinh vien dat tieu chuan can tim";
					break;
				}
				TraCuuDiem_Theo_MSSV(dm,head,mh, id33);
			}
			else { cout << "\nDanh sach Diem empty!"; }
			break;
		case 0:
			cout << "\n Da thoat chuong trinh!";
			return 0;
		default:
			cout << "\nKhong co chuc nang nay!\nChon chuc nang trong menu.";
				break;
		}
		//keyPress(0);
	}
	deleteListSV(head);
	deleteListMH(mh);
	deleteListDiem(dm);
	return 0;
}
//===========================Sinh Vien===============================================//
void addFirstSV(NodeSV*& head, HSSV x) {
	NodeSV* p = new NodeSV();
	p->data = x;
	p->next = head;
	head = p;
}
void addLastSV(NodeSV*& head, HSSV x) {
	NodeSV* p = new NodeSV();
	p->data = x;
	p->next = NULL;
	if (head == NULL) {//Nếu rỗng=>khởi tạo danh sách
		head = p;
	}
	else {
		NodeSV* q = head;
		while (q->next != NULL) q = q->next;
		q->next = p;
	}
}
void addItemSV(NodeSV*& head, NodeSV*& p, HSSV x) {
	NodeSV* q = new NodeSV();
	q->data = x;
	if (p != NULL) {
		q->next = p->next;
		p->next = q;
	}
	else { //Thêm vào đầu danh sách
		q->next = head;
		head = q;
	}
}
void printLine(int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "=";
	}
	cout << endl;
}
void nhapSV(NodeSV*& head) 
{
	HSSV x;
	do{
		cout << "\nMSSV: "; cin >> x.MSSV;
	}while(check_MSSV_SinhVien(head,x.MSSV));
	cout << "\nHoTen: "; fflush(stdin); gets(x.hoten);
    cout << "\nGioiTinh: ";gets(x.gtinh);
    do{
        cout << "\nNgay thang nam sinh: ";
        cin >> x.NgSinh.ngay>> x.NgSinh.thang>> x.NgSinh.nam;
    }while(!ngayHopLe(x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam));
	cout << "\nMa lop: ";fflush(stdin);gets(x.Lophoc.MaLop);
	cout << "\nTen lop: ";gets(x.Lophoc.TenLop);
	cout << "\nKhoa: ";gets(x.Lophoc.Khoa);
	cout << "\nHe dao tao: ";gets(x.Lophoc.HeDaoTao);
	cout << "\nNam nhap hoc: ";cin >> x.NamNhapHoc;
	
	//tinhDTB(x);
	//xeploai(x);
	addLastSV(head, x);
}
void nhapvaodauDSSV(NodeSV *&head)
{
    HSSV x;

	do{
		cout << "\nMSSV: "; cin >> x.MSSV;
	}while(check_MSSV_SinhVien(head,x.MSSV));
	cout << "\nHoTen: "; fflush(stdin); gets(x.hoten);
    cout << "\nGioiTinh: ";gets(x.gtinh);
    do{
        cout << "\nNgay thang nam sinh: ";
        cin >> x.NgSinh.ngay>> x.NgSinh.thang>> x.NgSinh.nam;
    }while(!ngayHopLe(x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam));
	cout << "\nMa lop: ";fflush(stdin);gets(x.Lophoc.MaLop);
	cout << "\nTen lop: ";gets(x.Lophoc.TenLop);
	cout << "\nKhoa: ";gets(x.Lophoc.Khoa);
	cout << "\nHe dao tao: ";gets(x.Lophoc.HeDaoTao);
	cout << "\nNam nhap hoc: ";cin >> x.NamNhapHoc;
    addFirstSV(head, x);
}
void XepLoaiSinhVien(HSSV& x) {
	if(x.DiemTong<4&&x.DiemTong>=0) strcpy(x.XepLoai, "Kem");
	else if(x.DiemTong>=4&&x.DiemTong<5) strcpy(x.XepLoai,"Yeu");
	else if(x.DiemTong>=5&&x.DiemTong<7) strcpy(x.XepLoai,"Trung Binh");
	else if(x.DiemTong>=7&&x.DiemTong<8.5) strcpy(x.XepLoai,"Kha");
	else if(x.DiemTong==-1) strcpy(x.XepLoai,"Chua xep loai");
	else strcpy(x.XepLoai,"Gioi");
}
int keyPress(int Clear) {
	if (Clear == 0) {
		cout << "\n\nPress a key to continue....";
		getch();
		system("cls");
		return 0;
	}
	else {
		cout << "\n\nPress a key to do a function:";
		int keyp;
		cin >> keyp;
		return keyp;
	}
}
void capNhatThongTinSV(NodeSV *&head,HSSV& x,int id) {
	HSSV temp;
	cout << "\nMSSV: "; cin >> temp.MSSV;
	while(check_MSSV_SinhVien(head,temp.MSSV))
	{
		if(temp.MSSV==id)
		break;
		cout << "\nMa so sinh vien bi trung hay nhap lai: "; cin >> temp.MSSV;	
	}
	x.MSSV=temp.MSSV;
	cout << "\nHoTen: "; fflush(stdin); gets(x.hoten);
    cout << "\nGioiTinh: ";gets(x.gtinh);
    do{
        cout << "\nNgay thang nam sinh: ";
        cin >> x.NgSinh.ngay>> x.NgSinh.thang>> x.NgSinh.nam;
    }while(!ngayHopLe(x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam));
	cout << "\nMa lop: ";fflush(stdin);gets(x.Lophoc.MaLop);
	cout << "\nTen lop: ";gets(x.Lophoc.TenLop);
	cout << "\nKhoa: ";gets(x.Lophoc.Khoa);
	cout << "\nHe dao tao: ";gets(x.Lophoc.HeDaoTao);
	cout << "\nNam nhap hoc: ";cin >> x.NamNhapHoc;
}
void capNhatSV(NodeSV*& head, int id) {
	int found = 0;
	NodeSV* q = NULL, * p = head;
	while (p != NULL) {
		if (p->data.MSSV == id) {
			found = 1;
			printLine(40);
			cout << "\n Cap nhat thong tin Student co ID = " << id;
			capNhatThongTinSV(head,p->data,id);
			printLine(40);
			break;
		}
		p = p->next;
	}
	if (found == 0) {
		printf("\n Student co ID = %d khong ton tai.", id);
	}
}
int xoaTheoIDSV(NodeSV*& head, int id) {
	int found = 0;
	NodeSV* q = NULL, * p = head;
	while (p != NULL) {
		if (p->data.MSSV == id) {
			found = 1;
			printLine(40);
			if (p == head) {
				head = head->next;
			}
			else {
				q->next = p->next;
			}
			delete p;
			//cout << "\nDa xoa SV co ID = " << id;
			return 1;
		}
		q = p;
		p = p->next;
	}
	cout << "\nKhong ton tai SV co ID = " << id;
	return 0;
}
void timKiemTheoTenSV(NodeSV*& head, char ten[]) {
	NodeSV* head2 = NULL, * p;
	char tenSV[30];
	int found=0;
	p = head;
	while (p != NULL) {
		strcpy(tenSV, p->data.hoten);
		if (strstr(strupr(tenSV), strupr(ten))) {
			addLastSV(head2, p->data);
			found=1;
		}
		p = p->next;
	}
	if(found==0)
	{
		printf("\nKhong co sinh vien dat tieu chuan can tim\n");
    	
	}
	else printListSV(head2);
}
void timKiemTheoMSSV(NodeSV *& head,int mssv)
{
    NodeSV* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mssv == p->data.MSSV) {
			addLastSV(head2, p->data);
			found=1;
		}
        // else
        // {
		// 	if(found)
        //     printf("\nKhong co sinh vien dat tieu chuan can tim\n");
        // }
		p = p->next;
    }
	if(found==0)
	{
		printf("\nKhong co sinh vien dat tieu chuan can tim\n");
    	
	}
	else printListSV(head2);
}
void sapxepTheoDTBSV(NodeSV*& head) {
	HSSV tmp;
	NodeSV* p, * q, * min;
	p = head;
	while (p != NULL) {
		min = p;
		q = p->next;
		while (q != NULL) {
			if (min->data.DiemTong < q->data.DiemTong) {
				min = q;
			}
			q = q->next;
		}
		if (min != p) {
			tmp = p->data;
			p->data = min->data;
			min->data = tmp;
		}
		p = p->next;
	}
}
void sapXepTheoTenSV(NodeSV*& head) {
	char tenSV1[30];
	char tenSV2[30];
	HSSV tmp;
	NodeSV* p, * q, * min;
	p = head;
	while (p != NULL) {
		min = p;
		strcpy(tenSV1, min->data.Lophoc.HeDaoTao);
		q = p->next;
		while (q != NULL) {
			strcpy(tenSV2, q->data.Lophoc.HeDaoTao);
			if (strcmp(strupr(tenSV1), strupr(tenSV2)) > 0) {
				min = q;
			}
			q = q->next;
		}
		if (min != p) {
			tmp = p->data;
			p->data = min->data;
			min->data = tmp;
		}
		p = p->next;
	}
}
void sapXepSinhVienKhoa(NodeSV*& head){
	HSSV tmp;
	NodeSV* p, * q, * min;
	p = head;
	while (p != NULL) {
		min = p;
		q = p->next;
		while (q != NULL) {
			if (min->data.NamNhapHoc>q->data.NamNhapHoc) {
	 			min = q;
			}
			
			q = q->next;
		}
		if (min != p) {
			tmp = p->data;
			p->data = min->data;
			min->data = tmp;
		}
		p = p->next;
	}
}
void printListSV(NodeSV* n)
{
	HSSV x;
	string maso;
	string namnhaphoc;
	string diemso;
	string dateformat;
	printLine(110);
	TextTable t( '-', '|', '+' );
    t.add( "MSSV" );
    t.add( "Ten" );
	t.add( "Gioi Tinh" );
	t.add( "Ngay Sinh" );
	t.add( "Ma Lop" );
	t.add( "Lop" );
	t.add("Khoa");
	t.add( "He dao tao" );
	t.add( "Nam Nhap Hoc" );
	t.add( "Diem tong" );
	t.add( "Xep Loai" );
    t.endOfRow();
	
	int ind = 0;
		while (n != NULL) 
		{
			x = n->data;
			//tinhDTB(x);
			XepLoaiSinhVien(x);
			//cout << "--------------------------------------------------------------------------";
			maso = std::to_string(x.MSSV);
			namnhaphoc = std::to_string(x.NamNhapHoc);
			diemso = std::to_string(x.DiemTong);
			dateformat=formatDate(x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam);
			t.add(maso);
    		t.add(x.hoten);
			t.add(x.gtinh);
			t.add(dateformat);
			t.add(x.Lophoc.MaLop);
    		t.add(x.Lophoc.TenLop);
			t.add(x.Lophoc.Khoa);
			t.add(x.Lophoc.HeDaoTao);
			t.add(namnhaphoc);
			t.add(diemso);
			t.add(x.XepLoai);
			t.endOfRow();
			n = n->next;
		}
		t.setAlignment( 2, TextTable::Alignment::RIGHT );
		cout<<t;
    
}
void printMSSV(NodeSV* n){
	HSSV x;
	string maso;
	string namnhaphoc;
	printLine(110);
	TextTable t( '-', '|', '+' );
    t.add( "MSSV" );
    t.add( "Ten" );
	t.add( "Lop" );
	t.add("Khoa");
	t.add( "He dao tao" );
	t.add( "Nam Nhap Hoc" );
    t.endOfRow();
	int ind = 0;
		while (n != NULL) 
		{
			x = n->data;
			//tinhDTB(x);
			XepLoaiSinhVien(x);
			maso = std::to_string(x.MSSV);
			namnhaphoc = std::to_string(x.NamNhapHoc);
			t.add(maso);
    		t.add(x.hoten);
    		t.add(x.Lophoc.TenLop);
			t.add(x.Lophoc.Khoa);
			t.add(x.Lophoc.HeDaoTao);
			t.add(namnhaphoc);
			t.endOfRow();
			
			n = n->next;
		}
		
		t.setAlignment( 2, TextTable::Alignment::RIGHT );
		cout<<t;
}

//=================Mon Hoc==============================//

void addLastMH(NodeMon*& mh,Mon x)
{
	NodeMon* p = new NodeMon();
	p->MonHoc = x;
	p->next = NULL;
	if (mh == NULL) {//Nếu rỗng=>khởi tạo danh sách
		mh = p;
	}
	else {
		NodeMon* q = mh;
		while (q->next != NULL) q = q->next;
		q->next = p;
	}
}
void nhapMH(NodeMon*& mh) 
{
	Mon x;
	do{
		cout << "\nMa Mon: "; cin >> x.MaMon;
	}while(check_ID_MonHoc(mh,x.MaMon));
	
	cout << "\nTen Mon: "; fflush(stdin); gets(x.TenMon);
    cout << "\nTin Chi: "; cin >> x.TinChi;
	cout << "\nLoai Mon Hoc: "; fflush(stdin); gets(x.LoaiMonHoc);
	cout << "\nTen Giang Vien: "; fflush(stdin); gets(x.TenGiangVien);
	addLastMH(mh, x);
}
void capNhatThongTinMH(NodeMon*& mh,Mon& x,int id) {
	Mon temp;
	cout << "\nMa Mon: "; cin >> temp.MaMon;
	while(check_ID_MonHoc(mh,temp.MaMon))
	{
		if(temp.MaMon==id)
		break;
		cout << "\nMa Mon bi trung hay nhap lai: "; cin >> temp.MaMon;
		
	}
	x.MaMon=temp.MaMon;
	cout << "\nTen Mon: "; fflush(stdin); gets(x.TenMon);
    cout << "\nTin Chi: "; cin >> x.TinChi;
	cout << "\nLoai Mon Hoc: "; fflush(stdin); gets(x.LoaiMonHoc);
	cout << "\nTen Giang Vien: "; fflush(stdin); gets(x.TenGiangVien);

}
void capNhatMH(NodeMon*& mh, int id) {
	int found = 0;
	NodeMon* p = mh;
	while (p != NULL) {
		if (p->MonHoc.MaMon == id) {
			found = 1;
			printLine(40);
			cout << "\nCap nhat thong tin mon hoc co ID = " << id;
			capNhatThongTinMH(mh,p->MonHoc,id);	
			printLine(40);
			break;
		}
		p = p->next;
	}

	if (found == 0) {
		printf("\nMon Hoc co ma mon = %d khong ton tai.", id);
	}
}
int xoaTheoIDMH(NodeMon*& mh, int id) {
	int found = 0;
	NodeMon* q = NULL, * p = mh;
	while (p != NULL) {
		if (p->MonHoc.MaMon == id) {
			found = 1;
			printLine(40);
			if (p == mh) {
				mh = mh->next;
			}
			else {
				q->next = p->next;
			}
			delete p;
			return 1;
		}
		q = p;
		p = p->next;
	}
	cout << "\nKhong ton tai Mon co Ma Mon = " << id;
	return 0;
}
void timKiemTheoTenMon(NodeMon*& head, char ten[]) {
	NodeMon* head2 = NULL, * p;
	char tenMH[30];
	int found=0;
	p = head;
	while (p != NULL) {
		strcpy(tenMH, p->MonHoc.TenMon);
		if (strstr(strupr(tenMH), strupr(ten))) {
			addLastMH(head2, p->MonHoc);
			found=1;
		}
		p = p->next;
	}
	if(found==0)
	{
		printf("\nKhong co mon hoc dat tieu chuan can tim\n");
    	
	}
	else printListMH(head2);
}
void timKiemTheoTenGiangVien(NodeMon*& head, char ten[]) {
	NodeMon* head2 = NULL, * p;
	char tenGV[50];
	int found=0;
	p = head;
	while (p != NULL) {
		strcpy(tenGV, p->MonHoc.TenGiangVien);
		if (strstr(strupr(tenGV), strupr(ten))) {
			addLastMH(head2, p->MonHoc);
			found=1;
		}
		p = p->next;
	}
	if(found==0)
	{
		printf("\nKhong co mon hoc dat tieu chuan can tim\n");
    	
	}
	else printListMH(head2);
}
void timKiemTheoMaMon(NodeMon *& head,int mamon)
{
    NodeMon* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mamon == p->MonHoc.MaMon) {
			addLastMH(head2, p->MonHoc);
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		printf("\nKhong co mon hoc dat tieu chuan can tim\n");
    	
	}
	else printListMH(head2);
}
void sapxepTheoTC(NodeMon*& head) {
	Mon tmp;
	NodeMon* p, * q, * min;
	p = head;
	while (p != NULL) {
		min = p;
		q = p->next;
		while (q != NULL) {
			if (min->MonHoc.TinChi > q->MonHoc.TinChi) {
				min = q;
			}
			q = q->next;
		}
		if (min != p) {
			tmp = p->MonHoc;
			p->MonHoc = min->MonHoc;
			min->MonHoc = tmp;
		}
		p = p->next;
	}
}
void printListMH(NodeMon* n)
{
	Mon x;
	string mamon;
	string tinchi;
	printLine(110);
	TextTable t( '-', '|', '+' );
    t.add( "MaMon" );
    t.add( "TenMon" );
	t.add( "TinChi" );
	t.add( "LoaiMon" );
	t.add( "TenGiangVien" );
    t.endOfRow();
	int ind = 0;
		while (n != NULL) 
		{
			x = n->MonHoc;
			mamon = std::to_string(x.MaMon);
			tinchi = std::to_string(x.TinChi);
			t.add(mamon);
    		t.add(x.TenMon);
			t.add(tinchi);
			t.add(x.LoaiMonHoc);
			t.add(x.TenGiangVien);
			t.endOfRow();
			n = n->next;
		}
		t.setAlignment( 2, TextTable::Alignment::RIGHT );
		cout<<t;
    
}
//===========================================Diem=========================================================//
void tinhDTBMon(Diem& x) {
	x.DiemTongMon = (x.DiemGiuaKi + x.DiemCuoiki) / 2;
}
void KetQuaMonHoc(Diem& x) {
	if (x.DiemTongMon >= 5) strcpy(x.KetQuaMon, "Qua Mon");
	else strcpy(x.KetQuaMon, "Rot Mon");
}
void TinhDiemChu(Diem& x){
	if(x.DiemTongMon<4) strcpy(x.DiemChu,"F");
	else if(x.DiemTongMon>=4&&x.DiemTongMon<5.5) strcpy(x.DiemChu,"D");
	else if(x.DiemTongMon>=5.5&&x.DiemTongMon<7) strcpy(x.DiemChu,"C");
	else if(x.DiemTongMon>=7&&x.DiemTongMon<8.5) strcpy(x.DiemChu,"B");
	else strcpy(x.DiemChu,"A");
}
void addLastDiem(NodeDiem*& dm,Diem x)
{
	NodeDiem* p = new NodeDiem();
	p->DiemHoc = x;
	p->next = NULL;
	if (dm == NULL) {//Nếu rỗng=>khởi tạo danh sách
		dm = p;
	}
	else {
		NodeDiem* q = dm;
		while (q->next != NULL) q = q->next;
		q->next = p;
	}
}
void nhapDiem(NodeDiem*& dm, NodeSV*& sv, NodeMon*& mon) 
{
	int hockitemp,namhoctemp,mssvtemp,mamontemp;
	Diem x;
	do{
		cout << "\nMSSV: "; cin >> mssvtemp;
	}while(!check_MSSV_SinhVien(sv,mssvtemp));
	do{
		cout << "\nMa Mon: "; cin >> mamontemp;
	}while(!check_ID_MonHoc(mon,mamontemp));
	//cout << "\nHoc Ky: "; cin >> x.HocKi;
	cout << "\nHoc Ky: "; cin >> hockitemp;
	cout << "\nNam Hoc: "; cin >> namhoctemp;
	while(check_Hocki_NamHoc_Diem(dm,mssvtemp,mamontemp,hockitemp,namhoctemp))
	{
		cout<< "\nMot sinh vien khong the hoc 1 mon 2 lan trong mot hoc ki.";
		cout<< "\nHay nhap lai MSSV: "; cin >> mssvtemp;
		cout<< "\nHay nhap lai Ma Mon: "; cin >> mamontemp;
		cout<< "\nHay Nhap lai Hoc Ky:"; cin >> hockitemp;
		cout<< "\nHay Nhap lai Nam hoc:"; cin >> namhoctemp;
	}
	x.HocKi=hockitemp;
	x.NamHoc=namhoctemp;
	x.MSSV=mssvtemp;
	x.MaMon=mamontemp;
	//cout << "\nNam Hoc: "; cin >> x.NamHoc;
	cout << "\nDiem Giua ky: "; cin >> x.DiemGiuaKi;
	cout << "\nDiem Cuoi ky: "; cin >> x.DiemCuoiki;
	tinhDTBMon(x);
	TinhDiemChu(x);
	KetQuaMonHoc(x);
	addLastDiem(dm,x);
}
void capNhatThongTinDiem(NodeSV*& sv,NodeMon*& mon,NodeDiem*& dm,Diem& x) {
	int hockitemp,namhoctemp,mssvtemp,mamontemp;
	do{
		cout << "\nMSSV: "; cin >> mssvtemp;
	}while(!check_MSSV_SinhVien(sv,mssvtemp));
	do{
		cout << "\nMa Mon: "; cin >> mamontemp;
	}while(!check_ID_MonHoc(mon,mamontemp));
	cout << "\nHoc Ky: "; cin >> hockitemp;
	cout << "\nNam Hoc: "; cin >> namhoctemp;
	while(check_Hocki_NamHoc_Diem(dm,mssvtemp,mamontemp,hockitemp,namhoctemp))
	{
		cout<< "\nMot sinh vien khong the hoc 1 mon 2 lan trong mot hoc ki.";
		cout<< "\nHay nhap lai MSSV: "; cin >> mssvtemp;
		cout<< "\nHay nhap lai Ma Mon: "; cin >> mamontemp;
		cout<< "\nHay Nhap lai Hoc Ky:"; cin >> hockitemp;
		cout<< "\nHay Nhap lai Nam hoc:"; cin >> namhoctemp;
	}
	x.HocKi=hockitemp;
	x.NamHoc=namhoctemp;
	x.MSSV=mssvtemp;
	x.MaMon=mamontemp;
	cout << "\nDiem Giua ky: "; cin >> x.DiemGiuaKi;
	cout << "\nDiem Cuoi ky: "; cin >> x.DiemCuoiki;
	tinhDTBMon(x);
	TinhDiemChu(x);
	KetQuaMonHoc(x);
}
void capNhatDiem(NodeSV*& sv,NodeMon*& mon,NodeDiem*& dm, int id, int mamon,int hocki, int namhoc) {
	int found = 0;
	NodeDiem* q = NULL, * p = dm;
	while (p != NULL) {
		if (p->DiemHoc.MSSV == id&& p->DiemHoc.MaMon==mamon && p->DiemHoc.HocKi==hocki&&p->DiemHoc.NamHoc==namhoc) {
			found = 1;
			printLine(40);
			cout << "\n Cap nhat thong tin Student co MSSV = " << id;
			capNhatThongTinDiem(sv,mon,dm,p->DiemHoc);
			printLine(40);
			break;
		}
		p = p->next;
	}
	if (found == 0) {
		printf("\n Khong ton tai cac tieu chi can xoa");
	}
}

int xoaTheoIDDiem(NodeDiem*& dm, int id) {
	int found = 0;
	NodeDiem* q = NULL, * p = dm;
	while (p != NULL) {
		if (p->DiemHoc.MSSV == id) {
			found = 1;
			//printLine(40);
			if (p == dm) {
				dm = dm->next;
			}
			else {
				q->next = p->next;
			}
			delete p;
			return 1;
		}
		q = p;
		p = p->next;
	}
	return 0;
}
int xoaTheoID_Diem(NodeDiem*& dm, int id, int mamon,int hocki, int namhoc) {
	int found = 0;
	NodeDiem* q = NULL, * p = dm;
	while (p != NULL) {
		if (p->DiemHoc.MSSV == id && p->DiemHoc.MaMon==mamon && p->DiemHoc.HocKi==hocki&&p->DiemHoc.NamHoc==namhoc) {
			found = 1;
			//printLine(40);
			if (p == dm) {
				dm = dm->next;
			}
			else {
				q->next = p->next;
			}
			delete p;
			return 1;
		}
		q = p;
		p = p->next;
	}
	cout << "\nKhong ton tai cac tieu chi can xoa";
	return 0;
}
int xoaTheoMaMonDiem(NodeDiem*& dm, int id) {
	int found = 0;
	NodeDiem* q = NULL, * p = dm;
	while (p != NULL) {
		if (p->DiemHoc.MaMon == id) {
			found = 1;
			//printLine(40);
			if (p == dm) {
				dm = dm->next;
			}
			else {
				q->next = p->next;
			}
			delete p;
			return 1;
		}
		q = p;
		p = p->next;
	}
	return 0;
}
void timKiemTheoMaSV(NodeDiem *& head,int mssv)
{
    NodeDiem* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mssv == p->DiemHoc.MSSV) {
			addLastDiem(head2, p->DiemHoc);
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		printf("\nKhong co sinh vien dat tieu chuan can tim\n");
    	
	}
	else printListDiem(head2);
}
void sapxepTheoDiemTong(NodeDiem*& head) {
	Diem tmp;
	NodeDiem* p, * q, * min;
	p = head;
	while (p != NULL) {
		min = p;
		q = p->next;
		while (q != NULL) {
			if (min->DiemHoc.DiemTongMon > q->DiemHoc.DiemTongMon) {
				min = q;
			}
			q = q->next;
		}
		if (min != p) {
			tmp = p->DiemHoc;
			p->DiemHoc = min->DiemHoc;
			min->DiemHoc = tmp;
		}
		p = p->next;
	}
}
void printListDiem(NodeDiem* n)
{
	Diem x;
	string mssv;
	string mamon;
	string hocki;
	string namhoc;
	string diemgiuaki;
	string diemcuoiki;
	string diemtong;
	printLine(110);
	TextTable t( '-', '|', '+' );
	t.add( "MSSV" );
    t.add( "Ma Mon" );
    t.add( "Hoc Ki" );
	t.add( "Nam Hoc" );
	t.add( "Diem Giua Ki" );
	t.add( "Diem Cuoi Ki" );
	t.add( "Diem Tong" );
	t.add( "Diem Chu" );
	t.add( "Ket Qua Mon" );
    t.endOfRow();
	int ind = 0;
		while (n != NULL) 
		{
			x = n->DiemHoc;
			mssv = std::to_string(x.MSSV);
			mamon = std::to_string(x.MaMon);
			hocki = std::to_string(x.HocKi);
			namhoc = std::to_string(x.NamHoc);
			diemgiuaki = std::to_string(x.DiemGiuaKi);
			diemcuoiki = std::to_string(x.DiemCuoiki);
			diemtong = std::to_string(x.DiemTongMon);
			t.add(mssv);
			t.add(mamon);
			t.add(hocki);
			t.add(namhoc);
			t.add(diemgiuaki);
			t.add(diemcuoiki);
			t.add(diemtong);
			t.add(x.DiemChu);
			t.add(x.KetQuaMon);
			t.endOfRow();
			n = n->next;
		}
		t.setAlignment( 2, TextTable::Alignment::RIGHT );
		cout<<t;
    
}
//======= Ham doc va ghi file cua chuong trinh
void ghiFileSV(NodeSV* head, char fileNameSV[]) {
	FILE * fp;
    fp = fopen (fileNameSV,"w");
    NodeSV *P;P=head;
    HSSV x;
    while (P!=NULL){
        x=P->data;
		//tinhDTB(x);
		//xeploai(x);
        //fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%s\n",P->data.MSSV,x.hoten,x.gtinh,x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam,x.dToan,x.dLy,x.dHoa,x.dTB,P->data.xLoai);
		fprintf(fp, "%d;%s;%s;%d;%d;%d;%s;%s;%s;%s;%d;%f;%s\n", P->data.MSSV, x.hoten,x.gtinh, x.NgSinh.ngay, x.NgSinh.thang, x.NgSinh.nam,x.Lophoc.MaLop, x.Lophoc.TenLop, x.Lophoc.Khoa,x.Lophoc.HeDaoTao, x.NamNhapHoc, x.DiemTong,x.XepLoai);
        P=P->next;
    }
    fclose (fp);
}
void docFileSV(NodeSV*& head, char fileNameSV[]) {
	FILE * fp;
    int i = 0;
    fp = fopen (fileNameSV, "r");
    cout << "Chuan bi doc file: "; puts(fileNameSV);
    HSSV x;
    while (fscanf(fp,"%d;%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%[^;];%[^;];%d;%f\n", &x.MSSV, &x.hoten,&x.gtinh, &x.NgSinh.ngay, &x.NgSinh.thang, &x.NgSinh.nam,&x.Lophoc.MaLop, &x.Lophoc.TenLop, &x.Lophoc.Khoa,&x.Lophoc.HeDaoTao, &x.NamNhapHoc, &x.DiemTong) != EOF) 
    {
		if(check_MSSV_SinhVien(head,x.MSSV))
		continue;
        addLastSV(head, x);
		i++;
    }
    cout << "So luong Student co san trong file la: " << i << endl;
    cout << endl;
    fclose (fp);
	return;
}
void docFileMon(NodeMon*& head, char fileNameMon[]) {
	FILE * fp;
    int i = 0;
    fp = fopen (fileNameMon, "r");
    cout << "Chuan bi doc file: "; puts(fileNameMon);
    Mon x;
    while (fscanf(fp,"%d;%[^;];%d;%[^;];%[^;];\n", &x.MaMon, &x.TenMon, &x.TinChi, &x.LoaiMonHoc, &x.TenGiangVien) != EOF) 
    {
		if(check_ID_MonHoc(head,x.MaMon))
		continue;
        addLastMH(head, x);
		i++;
    }
    cout << "So luong Mon co san trong file la: " << i << endl;
    cout << endl;
    fclose (fp);
	return;
}
void ghiFileMon(NodeMon* head, char fileNameMon[]) {
	FILE * fp;
    fp = fopen (fileNameMon,"w");
    NodeMon *P;P=head;
    Mon x;
    while (P!=NULL){
        x=P->MonHoc;
		//tinhDTB(x);
		//xeploai(x);
        //fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%d\t%f\t%f\t%f\t%f\t%s\n",P->data.MSSV,x.hoten,x.gtinh,x.NgSinh.ngay,x.NgSinh.thang,x.NgSinh.nam,x.dToan,x.dLy,x.dHoa,x.dTB,P->data.xLoai);
		fprintf(fp, "%d;%s;%d;%s;%s;\n", P->MonHoc.MaMon, x.TenMon,x.TinChi, x.LoaiMonHoc, x.TenGiangVien);
        P=P->next;
    }
    fclose (fp);
}

void docFileDiem(NodeDiem*& head, char fileNameDiem[]) {
	FILE * fp;
    int i = 0;
    fp = fopen (fileNameDiem, "r");
    cout << "Chuan bi doc file: "; puts(fileNameDiem);
    Diem x;
    while (fscanf(fp,"%d;%d;%d;%d;%f;%f;%f;%[^;];%[^;];\n", &x.MSSV, &x.MaMon, &x.HocKi, &x.NamHoc, &x.DiemGiuaKi,&x.DiemCuoiki,&x.DiemTongMon,&x.KetQuaMon,&x.DiemChu) != EOF) 
    {
        addLastDiem(head, x);
		i++;
    }
    cout << "So luong Mon co san trong file la: " << i << endl;
    cout << endl;
    fclose (fp);
	return;
}
void ghiFileDiem(NodeDiem*& head, char fileNameDiem[]) {
	FILE * fp;
    fp = fopen (fileNameDiem,"w");
    NodeDiem *P;P=head;
    Diem x;
    while (P!=NULL){
        x=P->DiemHoc;
		fprintf(fp, "%d;%d;%d;%d;%f;%f;%f;%s;%s\n", P->DiemHoc.MSSV, x.MaMon, x.HocKi, x.NamHoc, x.DiemGiuaKi,x.DiemCuoiki,x.DiemTongMon,x.KetQuaMon,x.DiemChu);
        P=P->next;
    }
    fclose (fp);
}

string formatDate(int ngay, int thang, int nam)
{
	string date="";
	date =date + std::to_string(ngay);
	date=date+"/";
	date =date + std::to_string(thang);
	date=date+"/";
	date =date + std::to_string(nam);
	return date;
}

//===============Mot so ham kiem tra rang buoc=======================

bool laNamNhuan(int nYear)
{
	if ((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
	{
		return true;
	}
	return false;

	// <=> return ((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0);
}

// Hàm trả về số ngày trong tháng thuộc năm cho trước
int tinhSoNgayTrongThang(int nMonth, int nYear)
{
	int nNumOfDays;

	switch (nMonth)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: 
		nNumOfDays = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11: 
		nNumOfDays = 30;
		break;
	case 2:
		if (laNamNhuan(nYear))
		{
			nNumOfDays = 29;
		}
		else
		{
			nNumOfDays = 28;
		}
		break;
	}

	return nNumOfDays;
}

int ngayHopLe(int nDay, int nMonth, int nYear)
{
	// Kiểm tra năm
	if (nYear < 0)
	{
		return 0; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra tháng
	if (nMonth < 1 || nMonth > 12)
	{
		return 0; // Ngày không còn hợp lệ nữa!
	}

	// Kiểm tra ngày
	if (nDay < 1 || nDay > tinhSoNgayTrongThang(nMonth, nYear))
	{
		return 0; // Ngày không còn hợp lệ nữa!
	}

	return 1; // Trả về trạng thái cuối cùng...
}


int check_ID_MonHoc(NodeMon *& head,int mamon)
{
    NodeMon* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		//cout << p->MonHoc.MaMon;
		if (mamon == p->MonHoc.MaMon) {
			//addLastMH(head2, p->MonHoc);
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		return 0;
    	
	}
	else return 1;
}
int check_MSSV_SinhVien(NodeSV *& head,int mssv)
{
    NodeSV* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mssv == p->data.MSSV) {
			//addLastSV(head2, p->data);
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		return 0;
    	
	}
	else return 1;
}

int check_MSSV_Diem(NodeDiem *& head,int mssv)
{
    NodeDiem* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mssv == p->DiemHoc.MSSV) {
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		return 0;
    	
	}
	else return 1;
}
int check_MaMon_Diem(NodeDiem *& head,int mamon)
{
    NodeDiem* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (mamon == p->DiemHoc.MaMon) {
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		return 0;
    	
	}
	else return 1;
}
int check_Hocki_NamHoc_Diem(NodeDiem *& head,int mssv,int mamon,int hocki,int namhoc)
{
    NodeDiem* head2=NULL,* p;
    p=head;
	int found=0;
    while (p != NULL)
    {
		if (namhoc == p->DiemHoc.NamHoc&&hocki==p->DiemHoc.HocKi&&mssv==p->DiemHoc.MSSV&&mamon==p->DiemHoc.MaMon) {
			found=1;
		}
		p = p->next;
    }
	if(found==0)
	{
		return 0;
    	
	}
	else return 1;
}
//===============================================Phan Tra cuu Diem =======================================================
void TraCuuDiem_Theo_MSSV(NodeDiem* n,NodeSV* sv,NodeMon* mon,int mssv)
{
	timKiemTheoMSSV(sv,mssv);
	NodeMon* nodemon_temp;
	Diem res_diem;
	Mon res_mon;
	int dem=0;
	string mssv_str;
	string mamon_str;
	string hocki_str;
	string namhoc_str;
	string diemgiuaki_str;
	string diemcuoiki_str;
	string diemtong_str,tinchi_str;
	printLine(110);
	TextTable t( '-', '|', '+' );
	t.add( "Ma Mon" );
	t.add("Ten Mon");
	t.add("Ten giang vien");
	t.add("Tin chi");
    t.add( "Nam hoc" );
	t.add("Hoc ki");
	t.add("Loai mon hoc");
	t.add( "Diem Giua Ki" );
	t.add( "Diem Cuoi Ki" );
	t.add( "Diem Tong" );
	t.add( "Diem Chu" );
	t.add( "Ket Qua Mon" );
    t.endOfRow();
	NodeDiem* n2=NULL;
	int found=0;
    while (n != NULL)
    {
		if (mssv == n->DiemHoc.MSSV) {
			addLastDiem(n2, n->DiemHoc);
			found=1;
		}
		n = n->next;
    }
	if(found==0)
	{
		printf("\nSinh vien nay chua duoc nhap diem\n");
    	return;
	}
	while (n2!=NULL)
	{
		//dem++;
		nodemon_temp=mon;
		while(nodemon_temp!=NULL)
		{
			res_diem=n2->DiemHoc;
			res_mon=nodemon_temp->MonHoc;
			if(res_diem.MaMon==res_mon.MaMon)
			{
				
		 		mamon_str = std::to_string(res_mon.MaMon);
		 		hocki_str = std::to_string(res_diem.HocKi);
		 		namhoc_str = std::to_string(res_diem.NamHoc);
		 		diemgiuaki_str = std::to_string(res_diem.DiemGiuaKi);
				diemcuoiki_str = std::to_string(res_diem.DiemCuoiki);
		 		diemtong_str = std::to_string(res_diem.DiemTongMon);
				tinchi_str = std::to_string(res_mon.TinChi);
				 t.add(mamon_str);
				 t.add(res_mon.TenMon);
				 t.add(res_mon.TenGiangVien);
				 t.add(tinchi_str);
				 t.add(namhoc_str);
				 t.add(hocki_str);
				 t.add(res_mon.LoaiMonHoc);
				 t.add(diemgiuaki_str);
				 t.add(diemcuoiki_str);
				 t.add(diemtong_str);
				 t.add(res_diem.DiemChu);
				 t.add(res_diem.KetQuaMon);
				 t.endOfRow();
				 break;
			
			}
			nodemon_temp=nodemon_temp->next;
		}
		n2 = n2->next;
	}
	//cout <<dem;
	t.setAlignment( 2, TextTable::Alignment::RIGHT );
 	cout<<t;
}
void tinhDiemTong(NodeDiem* diem,NodeSV* sv) {
	int dem=0,found=0;
	NodeDiem* diem_temp;
	//NodeSV* sv_temp;
	float tong=0,test;
	diem_temp=diem;
	//sv_temp=sv;
	while (sv!=NULL)
	{
		diem_temp=diem;
		while(diem_temp!=NULL)
		{
			
			if(diem_temp->DiemHoc.MSSV==sv->data.MSSV)
			{
				tong=tong+diem_temp->DiemHoc.DiemTongMon;
				dem++;
				found=1;
			}
			diem_temp=diem_temp->next;
		}
		if(found==1)
		{
			test=float(tong)/dem;
			dem=0;
			tong=0;
			found=0;
		}
		else test=-1;
		sv->data.DiemTong=test;
		//cout<<test;
		//cout<<"\n";
		sv=sv->next;
	}
	
}	
