#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

struct GiaoDich
{
    int ma;
    string noiDung;
    double soTien;
    string loai;       // Thu / Chi
    string danhMuc;
    int ngay;
    int thang;
};

// ======================================================
// HÀM IN SỐ TIỀN
// ======================================================

void inTien(double soTien)
{
    cout << fixed << setprecision(0) << soTien << " VND";
}

// ======================================================
// HÀM TÌM GIAO DỊCH THEO MÃ
// ======================================================

int timTheoMa(GiaoDich ds[], int n, int ma)
{
    for (int i = 0; i < n; i++)
    {
        if (ds[i].ma == ma)
        {
            return i;
        }
    }

    return -1;
}

// ======================================================
// LƯU DỮ LIỆU VÀO FILE
// ======================================================

void luuFile(GiaoDich ds[], int n)
{
    ofstream file("thuchicanhan.txt");

    if (!file)
    {
        cout << "Khong mo duoc file de luu!\n";
        return;
    }

    file << fixed << setprecision(0);

    for (int i = 0; i < n; i++)
    {
        file << ds[i].ma << "|"
             << ds[i].noiDung << "|"
             << ds[i].soTien << "|"
             << ds[i].loai << "|"
             << ds[i].danhMuc << "|"
             << ds[i].ngay << "|"
             << ds[i].thang << endl;
    }

    file.close();
}

// ======================================================
// ĐỌC DỮ LIỆU TỪ FILE
// ======================================================

void docFile(GiaoDich ds[], int &n)
{
    ifstream file("thuchicanhan.txt");

    if (!file)
    {
        return;
    }

    n = 0;

    string dong;

    while (getline(file, dong) && n < 100)
    {
        stringstream ss(dong);

        string ma;
        string noiDung;
        string soTien;
        string loai;
        string danhMuc;
        string ngay;
        string thang;

        getline(ss, ma, '|');
        getline(ss, noiDung, '|');
        getline(ss, soTien, '|');
        getline(ss, loai, '|');
        getline(ss, danhMuc, '|');
        getline(ss, ngay, '|');
        getline(ss, thang, '|');

        if (ma == "" || noiDung == "")
        {
            continue;
        }

        ds[n].ma = stoi(ma);
        ds[n].noiDung = noiDung;
        ds[n].soTien = stod(soTien);
        ds[n].loai = loai;
        ds[n].danhMuc = danhMuc;
        ds[n].ngay = stoi(ngay);
        ds[n].thang = stoi(thang);

        n++;
    }

    file.close();
}

// ======================================================
// NHẬP GIAO DỊCH
// ======================================================

void nhapGiaoDich(GiaoDich &gd)
{
    cout << "Nhap ma giao dich: ";
    cin >> gd.ma;

    cin.ignore();

    cout << "Nhap noi dung: ";
    getline(cin, gd.noiDung);

    do
    {
        cout << "Nhap so tien (> 0): ";
        cin >> gd.soTien;

        if (gd.soTien <= 0)
        {
            cout << "So tien phai lon hon 0!\n";
        }

    } while (gd.soTien <= 0);

    do
    {
        cout << "Nhap loai (Thu/Chi): ";
        cin >> gd.loai;

        if (gd.loai != "Thu" && gd.loai != "Chi")
        {
            cout << "Chi duoc nhap Thu hoac Chi!\n";
        }

    } while (gd.loai != "Thu" && gd.loai != "Chi");

    cin.ignore();

    cout << "Nhap danh muc: ";
    getline(cin, gd.danhMuc);

    do
    {
        cout << "Nhap ngay (1-31): ";
        cin >> gd.ngay;

        if (gd.ngay < 1 || gd.ngay > 31)
        {
            cout << "Ngay khong hop le!\n";
        }

    } while (gd.ngay < 1 || gd.ngay > 31);

    do
    {
        cout << "Nhap thang (1-12): ";
        cin >> gd.thang;

        if (gd.thang < 1 || gd.thang > 12)
        {
            cout << "Thang khong hop le!\n";
        }

    } while (gd.thang < 1 || gd.thang > 12);
}

// ======================================================
// HIỂN THỊ 1 GIAO DỊCH
// ======================================================

void hienThiGiaoDich(GiaoDich gd)
{
    cout << "Ma giao dich: " << gd.ma << endl;
    cout << "Noi dung: " << gd.noiDung << endl;

    cout << "So tien: ";
    inTien(gd.soTien);
    cout << endl;

    cout << "Loai: " << gd.loai << endl;
    cout << "Danh muc: " << gd.danhMuc << endl;
    cout << "Ngay: " << gd.ngay << "/" << gd.thang << endl;

    cout << "-----------------------------\n";
}

// ======================================================
// HIỂN THỊ DANH SÁCH
// ======================================================

void hienThiDanhSach(GiaoDich ds[], int n)
{
    if (n == 0)
    {
        cout << "Danh sach dang rong!\n";
        return;
    }

    cout << "\n========== DANH SACH GIAO DICH ==========\n";

    for (int i = 0; i < n; i++)
    {
        hienThiGiaoDich(ds[i]);
    }
}

// ======================================================
// THÊM GIAO DỊCH
// ======================================================

void themGiaoDich(GiaoDich ds[], int &n)
{
    if (n >= 100)
    {
        cout << "Danh sach da day!\n";
        return;
    }

    GiaoDich gd;

    nhapGiaoDich(gd);

    if (timTheoMa(ds, n, gd.ma) != -1)
    {
        cout << "Ma giao dich da ton tai!\n";
        return;
    }

    ds[n] = gd;
    n++;

    luuFile(ds, n);

    cout << "Them giao dich thanh cong!\n";
}

// ======================================================
// SỬA GIAO DỊCH
// ======================================================

void suaGiaoDich(GiaoDich ds[], int n)
{
    int ma;

    cout << "Nhap ma giao dich can sua: ";
    cin >> ma;

    int viTri = timTheoMa(ds, n, ma);

    if (viTri == -1)
    {
        cout << "Khong tim thay giao dich!\n";
        return;
    }

    cout << "\nThong tin cu:\n";
    hienThiGiaoDich(ds[viTri]);

    GiaoDich gd;

    cout << "\nNhap thong tin moi:\n";

    gd.ma = ma;

    cin.ignore();

    cout << "Nhap noi dung: ";
    getline(cin, gd.noiDung);

    do
    {
        cout << "Nhap so tien (> 0): ";
        cin >> gd.soTien;

        if (gd.soTien <= 0)
        {
            cout << "So tien phai lon hon 0!\n";
        }

    } while (gd.soTien <= 0);

    do
    {
        cout << "Nhap loai (Thu/Chi): ";
        cin >> gd.loai;

        if (gd.loai != "Thu" && gd.loai != "Chi")
        {
            cout << "Chi duoc nhap Thu hoac Chi!\n";
        }

    } while (gd.loai != "Thu" && gd.loai != "Chi");

    cin.ignore();

    cout << "Nhap danh muc: ";
    getline(cin, gd.danhMuc);

    do
    {
        cout << "Nhap ngay (1-31): ";
        cin >> gd.ngay;

        if (gd.ngay < 1 || gd.ngay > 31)
        {
            cout << "Ngay khong hop le!\n";
        }

    } while (gd.ngay < 1 || gd.ngay > 31);

    do
    {
        cout << "Nhap thang (1-12): ";
        cin >> gd.thang;

        if (gd.thang < 1 || gd.thang > 12)
        {
            cout << "Thang khong hop le!\n";
        }

    } while (gd.thang < 1 || gd.thang > 12);

    ds[viTri] = gd;

    luuFile(ds, n);

    cout << "Sua giao dich thanh cong!\n";
}

// ======================================================
// XÓA GIAO DỊCH
// ======================================================

void xoaGiaoDich(GiaoDich ds[], int &n)
{
    int ma;

    cout << "Nhap ma giao dich can xoa: ";
    cin >> ma;

    int viTri = timTheoMa(ds, n, ma);

    if (viTri == -1)
    {
        cout << "Khong tim thay giao dich!\n";
        return;
    }

    for (int i = viTri; i < n - 1; i++)
    {
        ds[i] = ds[i + 1];
    }

    n--;

    luuFile(ds, n);

    cout << "Xoa giao dich thanh cong!\n";
}

// ======================================================
// TÌM THEO NỘI DUNG
// ======================================================

void timTheoNoiDung(GiaoDich ds[], int n)
{
    string tuKhoa;

    cin.ignore();

    cout << "Nhap tu khoa can tim: ";
    getline(cin, tuKhoa);

    bool timThay = false;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].noiDung.find(tuKhoa) != string::npos)
        {
            hienThiGiaoDich(ds[i]);
            timThay = true;
        }
    }

    if (!timThay)
    {
        cout << "Khong tim thay giao dich!\n";
    }
}

// ======================================================
// LỌC THEO DANH MỤC
// ======================================================

void locTheoDanhMuc(GiaoDich ds[], int n)
{
    string danhMuc;

    cin.ignore();

    cout << "Nhap danh muc can loc: ";
    getline(cin, danhMuc);

    bool timThay = false;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].danhMuc == danhMuc)
        {
            hienThiGiaoDich(ds[i]);
            timThay = true;
        }
    }

    if (!timThay)
    {
        cout << "Khong co giao dich trong danh muc nay!\n";
    }
}

// ======================================================
// LỌC THEO THÁNG
// ======================================================

void locTheoThang(GiaoDich ds[], int n)
{
    int thang;

    cout << "Nhap thang can loc: ";
    cin >> thang;

    if (thang < 1 || thang > 12)
    {
        cout << "Thang khong hop le!\n";
        return;
    }

    bool timThay = false;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].thang == thang)
        {
            hienThiGiaoDich(ds[i]);
            timThay = true;
        }
    }

    if (!timThay)
    {
        cout << "Khong co giao dich trong thang nay!\n";
    }
}

// ======================================================
// SẮP XẾP THEO SỐ TIỀN
// ======================================================

void sapXepTheoSoTien(GiaoDich ds[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ds[i].soTien > ds[j].soTien)
            {
                GiaoDich temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    luuFile(ds, n);

    cout << "Da sap xep theo so tien tang dan!\n";
}

// ======================================================
// SẮP XẾP THEO NGÀY
// ======================================================

void sapXepTheoNgay(GiaoDich ds[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ds[i].thang > ds[j].thang ||
                (ds[i].thang == ds[j].thang &&
                 ds[i].ngay > ds[j].ngay))
            {
                GiaoDich temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    luuFile(ds, n);

    cout << "Da sap xep theo ngay tang dan!\n";
}

// ======================================================
// TÍNH TỔNG THU
// ======================================================

double tongThu(GiaoDich ds[], int n)
{
    double tong = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].loai == "Thu")
        {
            tong += ds[i].soTien;
        }
    }

    return tong;
}

// ======================================================
// TÍNH TỔNG CHI
// ======================================================

double tongChi(GiaoDich ds[], int n)
{
    double tong = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].loai == "Chi")
        {
            tong += ds[i].soTien;
        }
    }

    return tong;
}

// ======================================================
// THỐNG KÊ THEO THÁNG
// ======================================================

void thongKeTheoThang(GiaoDich ds[], int n)
{
    int thang;

    cout << "Nhap thang can thong ke: ";
    cin >> thang;

    if (thang < 1 || thang > 12)
    {
        cout << "Thang khong hop le!\n";
        return;
    }

    double thu = 0;
    double chi = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].thang == thang)
        {
            if (ds[i].loai == "Thu")
            {
                thu += ds[i].soTien;
            }
            else
            {
                chi += ds[i].soTien;
            }
        }
    }

    cout << "\n========== THONG KE THANG " << thang << " ==========\n";

    cout << "Tong thu: ";
    inTien(thu);
    cout << endl;

    cout << "Tong chi: ";
    inTien(chi);
    cout << endl;

    cout << "So du: ";
    inTien(thu - chi);
    cout << endl;
}

// ======================================================
// TÌM KHOẢN CHI LỚN NHẤT
// ======================================================

void khoanChiLonNhat(GiaoDich ds[], int n)
{
    int viTri = -1;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].loai == "Chi")
        {
            if (viTri == -1 ||
                ds[i].soTien > ds[viTri].soTien)
            {
                viTri = i;
            }
        }
    }

    if (viTri == -1)
    {
        cout << "Chua co khoan chi nao!\n";
        return;
    }

    cout << "\n========== KHOAN CHI LON NHAT ==========\n";
    hienThiGiaoDich(ds[viTri]);
}

// ======================================================
// DANH MỤC TIÊU NHIỀU NHẤT
// ======================================================

void danhMucTieuNhieuNhat(GiaoDich ds[], int n)
{
    string danhMuc[100];
    double tien[100] = {0};

    int soDanhMuc = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].loai != "Chi")
        {
            continue;
        }

        int viTri = -1;

        for (int j = 0; j < soDanhMuc; j++)
        {
            if (danhMuc[j] == ds[i].danhMuc)
            {
                viTri = j;
                break;
            }
        }

        if (viTri == -1)
        {
            danhMuc[soDanhMuc] = ds[i].danhMuc;
            tien[soDanhMuc] = ds[i].soTien;
            soDanhMuc++;
        }
        else
        {
            tien[viTri] += ds[i].soTien;
        }
    }

    if (soDanhMuc == 0)
    {
        cout << "Chua co khoan chi nao!\n";
        return;
    }

    int viTriMax = 0;

    for (int i = 1; i < soDanhMuc; i++)
    {
        if (tien[i] > tien[viTriMax])
        {
            viTriMax = i;
        }
    }

    cout << "\n========== DANH MUC CHI NHIEU NHAT ==========\n";

    cout << "Danh muc: " << danhMuc[viTriMax] << endl;

    cout << "So tien: ";
    inTien(tien[viTriMax]);
    cout << endl;
}

// ======================================================
// THỐNG KÊ CHUNG
// ======================================================

void thongKe(GiaoDich ds[], int n)
{
    double thu = tongThu(ds, n);
    double chi = tongChi(ds, n);
    double soDu = thu - chi;

    cout << "\n========== THONG KE ==========\n";

    cout << "Tong thu: ";
    inTien(thu);
    cout << endl;

    cout << "Tong chi: ";
    inTien(chi);
    cout << endl;

    cout << "So du hien tai: ";
    inTien(soDu);
    cout << endl;

    khoanChiLonNhat(ds, n);

    danhMucTieuNhieuNhat(ds, n);
}

// ======================================================
// ĐẶT NGÂN SÁCH
// ======================================================

void datNganSach(double nganSach[], int thang)
{
    if (thang < 1 || thang > 12)
    {
        cout << "Thang khong hop le!\n";
        return;
    }

    do
    {
        cout << "Nhap ngan sach thang " << thang << ": ";
        cin >> nganSach[thang];

        if (nganSach[thang] <= 0)
        {
            cout << "Ngan sach phai lon hon 0!\n";
        }

    } while (nganSach[thang] <= 0);

    cout << "Da dat ngan sach thanh cong!\n";
}

// ======================================================
// KIỂM TRA NGÂN SÁCH
// ======================================================

void kiemTraNganSach(GiaoDich ds[], int n, double nganSach[])
{
    int thang;

    cout << "Nhap thang can kiem tra: ";
    cin >> thang;

    if (thang < 1 || thang > 12)
    {
        cout << "Thang khong hop le!\n";
        return;
    }

    if (nganSach[thang] <= 0)
    {
        cout << "Thang nay chua dat ngan sach!\n";
        return;
    }

    double chi = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].thang == thang &&
            ds[i].loai == "Chi")
        {
            chi += ds[i].soTien;
        }
    }

    cout << "\n========== KIEM TRA NGAN SACH ==========\n";

    cout << "Ngan sach: ";
    inTien(nganSach[thang]);
    cout << endl;

    cout << "Da chi: ";
    inTien(chi);
    cout << endl;

    if (chi > nganSach[thang])
    {
        cout << "CANH BAO: DA VUOT NGAN SACH!\n";

        cout << "Vuot: ";
        inTien(chi - nganSach[thang]);
        cout << endl;
    }
    else
    {
        cout << "Chua vuot ngan sach.\n";

        cout << "Con lai: ";
        inTien(nganSach[thang] - chi);
        cout << endl;
    }
}

// ======================================================
// BIỂU ĐỒ CHI TIÊU THEO DANH MỤC
// ======================================================

void bieuDoDanhMuc(GiaoDich ds[], int n)
{
    string danhMuc[100];
    double tien[100] = {0};

    int soDanhMuc = 0;

    for (int i = 0; i < n; i++)
    {
        if (ds[i].loai != "Chi")
        {
            continue;
        }

        int viTri = -1;

        for (int j = 0; j < soDanhMuc; j++)
        {
            if (danhMuc[j] == ds[i].danhMuc)
            {
                viTri = j;
                break;
            }
        }

        if (viTri == -1)
        {
            danhMuc[soDanhMuc] = ds[i].danhMuc;
            tien[soDanhMuc] = ds[i].soTien;
            soDanhMuc++;
        }
        else
        {
            tien[viTri] += ds[i].soTien;
        }
    }

    cout << "\n========== BIEU DO CHI TIEU ==========\n";
    cout << "(1 * tuong ung 100.000 VND)\n\n";

    for (int i = 0; i < soDanhMuc; i++)
    {
        int soSao = (int)(tien[i] / 100000);

        cout << left << setw(15) << danhMuc[i];

        cout << " ";

        for (int j = 0; j < soSao; j++)
        {
            cout << "*";
        }

        cout << " ";

        inTien(tien[i]);

        cout << endl;
    }
}

// ======================================================
// MENU
// ======================================================

void menu()
{
    cout << "\n============================================\n";
    cout << "       QUAN LY CHI TIEU CA NHAN\n";
    cout << "============================================\n";

    cout << "1. Them giao dich\n";
    cout << "2. Sua giao dich\n";
    cout << "3. Xoa giao dich\n";
    cout << "4. Hien thi danh sach\n";
    cout << "5. Tim theo noi dung\n";
    cout << "6. Loc theo danh muc\n";
    cout << "7. Loc theo thang\n";
    cout << "8. Sap xep theo so tien\n";
    cout << "9. Sap xep theo ngay\n";
    cout << "10. Thong ke chung\n";
    cout << "11. Thong ke theo thang\n";
    cout << "12. Dat ngan sach\n";
    cout << "13. Kiem tra ngan sach\n";
    cout << "14. Bieu do chi tieu\n";
    cout << "0. Thoat\n";

    cout << "============================================\n";
}

// ======================================================
// HÀM MAIN
// ======================================================

int main()
{
    GiaoDich ds[100];

    int n = 0;

    double nganSach[13] = {0};

    // Đọc dữ liệu từ file khi chương trình bắt đầu
    docFile(ds, n);

    int luaChon;

    do
    {
        menu();

        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon)
        {
        case 1:
            themGiaoDich(ds, n);
            break;

        case 2:
            suaGiaoDich(ds, n);
            break;

        case 3:
            xoaGiaoDich(ds, n);
            break;

        case 4:
            hienThiDanhSach(ds, n);
            break;

        case 5:
            timTheoNoiDung(ds, n);
            break;

        case 6:
            locTheoDanhMuc(ds, n);
            break;

        case 7:
            locTheoThang(ds, n);
            break;

        case 8:
            sapXepTheoSoTien(ds, n);
            break;

        case 9:
            sapXepTheoNgay(ds, n);
            break;

        case 10:
            thongKe(ds, n);
            break;

        case 11:
            thongKeTheoThang(ds, n);
            break;

        case 12:
        {
            int thang;

            cout << "Nhap thang: ";
            cin >> thang;

            datNganSach(nganSach, thang);

            break;
        }

        case 13:
            kiemTraNganSach(ds, n, nganSach);
            break;

        case 14:
            bieuDoDanhMuc(ds, n);
            break;

        case 0:
            luuFile(ds, n);
            cout << "Da luu du lieu. Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (luaChon != 0);

    return 0;
}