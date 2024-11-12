#include <bits/stdc++.h>
using namespace std;

class Student{
private:
    string MSV, Ten, Gioitinh, Hang; 
    int Tuoi;
    float Toan, Ly, Hoa, GPA;

public:
    // Ham tao
    Student() {}
    Student(string MSV = "", string Ten = "", string Gioitinh = "", int Tuoi = 0, float Toan = 0, float Ly = 0, float Hoa = 0) {
        this->MSV = MSV;
        this->Ten = Ten; 
        this->Gioitinh = Gioitinh;
        this->Tuoi = Tuoi;
        this->Toan = Toan;
        this->Ly = Ly;
        this->Hoa = Hoa;
        T_GPA();
        T_Hang();
    }

    // Tinh diem trung binh
    void T_GPA(){
        GPA = (Toan + Ly + Hoa) / 3.0;
    }

    // Xep loai hoc luc
    void T_Hang(){
        if (GPA >= 8.0) Hang = "Gioi";
        else if (GPA >= 7.0) Hang = "Kha"; 
        else if (GPA >= 5.0) Hang = "Trung Binh";
        else Hang = "Yeu";
    }

    // Lay thong tin
    string getMSV() const { return MSV; }
    string getTen() const { return Ten; }
    string getGioitinh() const { return Gioitinh; }
    int getTuoi() const { return Tuoi; }
    float getToan() const { return Toan; }
    float getLy() const { return Ly; }
    float getHoa() const { return Hoa; }
    float getGPA() const { return GPA; }
    string getHang() const { return Hang; }

    // Toan tu nap chong
    friend istream& operator>>(istream& is, Student& sv) {
        cout << "Nhap MSV: ";
        is >> sv.MSV;

        is.ignore();
        cout << "Nhap Ten: ";
        getline(is, sv.Ten);
        
        cout << "Nhap Gioi tinh: ";
        getline(is, sv.Gioitinh);
        
        cout << "Nhap Tuoi: ";
        is >> sv.Tuoi;
        
        cout << "Nhap diem Toan: ";
        is >> sv.Toan;
        
        cout << "Nhap diem Ly: ";
        is >> sv.Ly;
        
        cout << "Nhap diem Hoa: ";
        is >> sv.Hoa;

        sv.T_GPA();
        sv.T_Hang();
        return is;
    }

    friend ostream& operator<<(ostream& os, const Student& sv) {
        os << setw(10) << sv.MSV
           << setw(20) << sv.Ten
           << setw(10) << sv.Gioitinh  
           << setw(6) << sv.Tuoi
           << setw(6) << fixed << setprecision(1) << sv.Toan
           << setw(6) << sv.Ly
           << setw(6) << sv.Hoa
           << setw(6) << sv.GPA
           << setw(10) << sv.Hang;
        return os;
    }

    bool operator<(const Student& other) const {
        return this->GPA < other.GPA;
    }

    // Cap nhat thong tin sinh vien
    void updStudent(string MSV, string Ten, string Gioitinh, int Tuoi, float Toan, float Ly, float Hoa) {
        this->Ten = Ten;
        this->Gioitinh = Gioitinh;  
        this->Tuoi = Tuoi;
        this->Toan = Toan;
        this->Ly = Ly;
        this->Hoa = Hoa;
        T_GPA();
        T_Hang();
    }

    // Hien thi thong tin sinh vien
    void HienThi() const{
        cout << setw(10) << MSV
             << setw(20) << Ten
             << setw(10) << Gioitinh  
             << setw(6) << Tuoi
             << setw(6) << fixed << setprecision(1) << Toan
             << setw(6) << Ly
             << setw(6) << Hoa
             << setw(6) << GPA
             << setw(10) << Hang << endl;
    }
};

class QL_Student{
private:
    vector<Student> students;

public:
    // Doc du lieu tu file
    void readFile(const string& filename){
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Khong the mo file!!! " << filename << endl;
            return;
        }

        string MSV, Ten1, Ten2, Ten3, Gioitinh;
        int Tuoi;
        float Toan, Ly, Hoa;

        students.clear();
        while (file >> MSV >> Ten1 >> Ten2 >> Ten3 >> Gioitinh >> Tuoi >> Toan >> Ly >> Hoa) {
            string Ten = Ten1 + " " + Ten2 + " " + Ten3;
            Student student(MSV, Ten, Gioitinh, Tuoi, Toan, Ly, Hoa);
            students.push_back(student);
        }

        file.close();
        cout << "Doc file thanh cong!" << endl;
    }

    // Them sinh vien moi
    void addStudent(){
        string MSV, Ten, Gioitinh;
        int Tuoi;
        float Toan, Ly, Hoa;

        cout << "Nhap MSV: ";
        cin >> MSV;

        // Kiem tra MSV trung
        for (const auto& student : students){
            if (student.getMSV() == MSV) {
                cout << "MSV " << MSV << " da ton tai. Vui long nhap lai!" << endl;
                return;
            }
        }

        cin.ignore();
        cout << "Nhap Ten: ";
        getline(cin, Ten);
        cout << "Nhap Gioi tinh: ";
        getline(cin, Gioitinh);
        cout << "Nhap Tuoi: ";
        cin >> Tuoi;
        cout << "Nhap diem Toan: ";
        cin >> Toan;
        cout << "Nhap diem Ly: ";
        cin >> Ly;
        cout << "Nhap diem Hoa: ";
        cin >> Hoa;

        // Kiem tra du lieu hop le
        if (Tuoi <= 0 || Toan < 0 || Toan > 10 || Ly < 0 || Ly > 10 || Hoa < 0 || Hoa > 10){
            cout << "Du lieu khong hop le. Vui long kiem tra lai!" << endl;
            return;
        }

        students.push_back(Student(MSV, Ten, Gioitinh, Tuoi, Toan, Ly, Hoa));
        cout << "Them sinh vien thanh cong!" << endl;
    }

    // Xoa sinh vien theo MSV
    void deleteStudent(const string& MSV){
        for (auto it = students.begin(); it != students.end(); ++it){
            if (it->getMSV() == MSV) {
                students.erase(it);
                cout << "Sinh vien voi MSV " << MSV << " da duoc xoa." << endl;
                return;
            }
        }
        cout << "Khong tim thay sinh vien voi MSV " << MSV << "." << endl;
    }

    // Hien thi tat ca sinh vien
    void displayAll(){
        if (students.empty()){
            cout << "Danh sach sinh vien trong!" << endl;
            return;
        }

        cout << setw(10) << "MSV"
             << setw(20) << "Ten" 
             << setw(10) << "Gioi tinh"
             << setw(6) << "Tuoi"
             << setw(6) << "Toan"
             << setw(6) << "Ly"
             << setw(6) << "Hoa"
             << setw(6) << "GPA"
             << setw(10) << "Hang" << endl;
        cout << string(80, '-') << endl;

        for (const auto& student : students) {
            student.HienThi();
        }
    }

    // Tim kiem sinh vien theo ten
    void searchByName(const string& searchName) {
        bool found = false;
        for (const auto& student : students) {
            if (student.getTen().find(searchName) != string::npos) {
                if (!found) {
                    cout << setw(10) << "MSV"
                         << setw(20) << "Ten"
                         << setw(10) << "Gioi tinh"
                         << setw(6) << "Tuoi" 
                         << setw(6) << "Toan"
                         << setw(6) << "Ly"
                         << setw(6) << "Hoa"
                         << setw(6) << "GPA"
                         << setw(10) << "Hang" << endl;
                    cout << string(80, '-') << endl;
                }
                student.HienThi();
                found = true;
            }
        }
        if (!found) {
            cout << "Khong tim thay sinh vien co ten \"" << searchName << "\"" << endl;
        }
    }

    // Sap xep theo GPA
    void sortGPA() {
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) {
                 return a.getGPA() > b.getGPA();
             });
    }

    // Sap xep theo ten
    void sortName() {
        sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) {
                 return a.getTen() < b.getTen();
             });
    }

    // Luu vao file
    void saveFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Khong the mo file de ghi!\n";
            return;
        }

        for (const auto& student : students) {
            file << student.getMSV() << " "
                 << student.getTen() << " "
                 << student.getGioitinh() << " "
                 << student.getTuoi() << " "
                 << fixed << setprecision(1)
                 << student.getToan() << " "
                 << student.getLy() << " " 
                 << student.getHoa() << endl;
        }

        cout << "Luu file thanh cong!\n";
    }
};

class App {
private:
    QL_Student qlsv;

    void clearScreen() {
        system("cls");
    }

    void pauseScreen() {
        cout << "\nNhan Enter de tiep tuc...";
        cin.get();
    }

    void displayMenu() {
        cout << "\n========== QUAN LY SINH VIEN ==========\n";
        cout << "1. Doc tu file\n";
        cout << "2. Them sinh vien\n";
        cout << "3. Xoa sinh vien\n";
        cout << "4. Tim kiem theo ten\n";
        cout << "5. Sap xep theo GPA\n";
        cout << "6. Sap xep theo ten\n";
        cout << "7. Hien thi danh sach\n";
        cout << "8. Luu vao file\n";
        cout << "0. Thoat\n";
        cout << "=====================================\n";
        cout << "Nhap lua chon: ";
    }

    void processChoice(int choice) {
        string searchName, MSV;
        
        switch (choice) {
            case 1:
                clearScreen();
                cout << "=== DOC TU FILE ===\n";
                qlsv.readFile("pupil.txt");
                break;
            case 2:
                clearScreen();
                cout << "=== THEM SINH VIEN ===\n";
                qlsv.addStudent();
                break;
            case 3:
                clearScreen();
                cout << "=== XOA SINH VIEN ===\n";
                cout << "Nhap MSV can xoa: ";
                getline(cin, MSV);
                qlsv.deleteStudent(MSV);
                break;
            case 4:
                clearScreen();
                cout << "=== TIM KIEM SINH VIEN ===\n";
                cout << "Nhap ten sinh vien can tim: ";
                getline(cin, searchName);
                qlsv.searchByName(searchName);
                break;
            case 5:
                clearScreen();
                cout << "=== SAP XEP THEO GPA ===\n";
                qlsv.sortGPA();
                qlsv.displayAll();
                break;
            case 6:
                clearScreen();
                cout << "=== SAP XEP THEO TEN ===\n";
                qlsv.sortName();
                qlsv.displayAll();
                break;
            case 7:
                clearScreen();
                cout << "=== DANH SACH SINH VIEN ===\n";
                qlsv.displayAll();
                break;
            case 8:
                clearScreen();
                cout << "=== LUU VAO FILE ===\n";
                qlsv.saveFile("pupil.txt");
                break;
            case 0:
                clearScreen();
                cout << "Cam on ban da su dung chuong trinh!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    }

public:
    void run() {
        int choice;
        do {
            clearScreen();
            displayMenu();
            cin >> choice;
            cin.ignore();

            processChoice(choice);

            if (choice != 0) {
                pauseScreen();
            }

        } while (choice != 0);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}