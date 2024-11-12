#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <algorithm>
using namespace std;

enum Otsinka { ZADOVILNO = 3, DOBRE, VIDMINNO };
enum Specialnist { KN, IT, ME, MF, FI };
string otsinkaStr[] = { "���������", "�����", "������" };
string specialnistStr[] = { "����'����� �����", "�������� ����������� ������������", "����������", "Գ����", "Գ������" };

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    int fizyka;
    int matematika;
    int informatika;
    int programming;       // Only for KN, IT
    int numericalMethods;  // Only for ME
    int pedagogy;          // Only for FI
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
double CalculateExcellentPercentage(const Student* students, const int N, int predmet);
void SortBySurname(Student* students, const int N);
int BinarySearchBySurname(const Student* students, const int N, const string& surname);
void PrintExcellentInPhysics(const Student* students, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� �������� N: "; cin >> N;

    Student* students = new Student[N];

    int menuItem;
    do {
        cout << "\n������� ��:\n";
        cout << " [1] - �������� ����� ��� ��������\n";
        cout << " [2] - ���� ����� ��� ��������\n";
        cout << " [3] - ���������� ������� �������� � ������, ���������� �� �����������\n";
        cout << " [4] - ���������� �������� �� ��������\n";
        cout << " [5] - ����� �������� �� ��������\n";
        cout << " [6] - ���� ������ ��������, �� ����� ������ '5' � ������\n";
        cout << " [0] - �����\n";
        cout << "������ ��������: "; cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(students, N);
            break;
        case 2:
            Print(students, N);
            break;
        case 3:
            cout << "³������ ��������, �� ����� '������' � ������: "
                << CalculateExcellentPercentage(students, N, 1) << "%" << endl;
            cout << "³������ ��������, �� ����� '������' � ����������: "
                << CalculateExcellentPercentage(students, N, 2) << "%" << endl;
            cout << "³������ ��������, �� ����� '������' � �����������: "
                << CalculateExcellentPercentage(students, N, 3) << "%" << endl;
            break;
        case 4:
            SortBySurname(students, N);
            cout << "�������� ����������� �� ��������.\n";
            Print(students, N);
            break;
        case 5:
        {
            SortBySurname(students, N);
            string surname;
            cin.ignore();
            cout << "������ ������� ��� ������: ";
            getline(cin, surname);
            int index = BinarySearchBySurname(students, N, surname);
            if (index != -1) {
                cout << "�������� ��������:\n";
                cout << "| " << setw(15) << left << students[index].prizv
                    << "| " << setw(8) << right << students[index].kurs << " ";
                cout << "| " << setw(20) << left << specialnistStr[students[index].specialnist] << " ";
                cout << "| " << setw(8) << students[index].fizyka << " ";
                cout << "| " << setw(10) << students[index].matematika << " ";
                cout << "| " << setw(11) << students[index].informatika << " |\n";
            }
            else {
                cout << "�������� � ����� �������� �� ��������.\n";
            }
        }
        break;
        case 6:
            PrintExcellentInPhysics(students, N);
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ����������� ��������! ��� ������ ����� ������ ����.\n";
        }
    } while (menuItem != 0);

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":\n";
        cin.ignore();
        cout << " �������: "; getline(cin, students[i].prizv);
        cout << " ����: "; cin >> students[i].kurs;
        cout << " ������������ (0 - ����'����� �����, 1 - �������� ����������� ������������, 2 - ����������, 3 - Գ����, 4 - Գ������): ";
        cin >> specialnist;
        students[i].specialnist = static_cast<Specialnist>(specialnist);

        cout << " ������ � ������: "; cin >> students[i].fizyka;
        cout << " ������ � ����������: "; cin >> students[i].matematika;
        cout << " ������ � �����������: "; cin >> students[i].informatika;

        if (students[i].specialnist == KN || students[i].specialnist == IT) {
            cout << " ������ � �������������: "; cin >> students[i].programming;
            students[i].numericalMethods = students[i].pedagogy = -1;
        }
        else if (students[i].specialnist == ME) {
            cout << " ������ � ��������� ������: "; cin >> students[i].numericalMethods;
            students[i].programming = students[i].pedagogy = -1;
        }
        else if (students[i].specialnist == FI) {
            cout << " ������ � ���������: "; cin >> students[i].pedagogy;
            students[i].programming = students[i].numericalMethods = -1;
        }
        else {
            students[i].programming = students[i].numericalMethods = students[i].pedagogy = -1;
        }

        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "=================================================================================================================================================\n";
    cout << "| �   | �������       | ���� | ������������             | Գ���� | ���������� | ����������� | ������������� | ������� ������| ��������� |\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << i + 1 << " ";
        cout << "| " << setw(15) << left << students[i].prizv
            << "| " << setw(4) << right << students[i].kurs << " ";
        cout << "| " << setw(25) << left << specialnistStr[students[i].specialnist] << " ";
        cout << "| " << setw(6) << right << students[i].fizyka << " ";
        cout << "| " << setw(10) << right << students[i].matematika << " ";
        cout << "| " << setw(11) << right << students[i].informatika << " ";

        cout << "| " << setw(13) << (students[i].programming != -1 ? to_string(students[i].programming) : "-") << " ";
        cout << "| " << setw(14) << (students[i].numericalMethods != -1 ? to_string(students[i].numericalMethods) : "-") << " ";
        cout << "| " << setw(10) << (students[i].pedagogy != -1 ? to_string(students[i].pedagogy) : "-") << " |\n";
    }
    cout << "=================================================================================================================================================\n";

}

double CalculateExcellentPercentage(const Student* students, const int N, int predmet) {
    int excellentCount = 0;

    for (int i = 0; i < N; i++) {
        int grade;
        switch (predmet) {
        case 1:
            grade = students[i].fizyka;
            break;
        case 2:
            grade = students[i].matematika;
            break;
        case 3:
            grade = students[i].informatika;
            break;
        default:
            return 0.0;
        }

        if (grade == VIDMINNO) {
            excellentCount++;
        }
    }

    return (static_cast<double>(excellentCount) / N) * 100;
}

void SortBySurname(Student* students, const int N) {
    sort(students, students + N, [](const Student& a, const Student& b) {
        return a.prizv < b.prizv;
        });
}

int BinarySearchBySurname(const Student* students, const int N, const string& surname) {
    int left = 0;
    int right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (students[mid].prizv == surname) {
            return mid;
        }
        else if (students[mid].prizv < surname) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void PrintExcellentInPhysics(const Student* students, const int N) {
    cout << "��������, �� ����� ������ '������' � ������:\n";
    for (int i = 0; i < N; i++) {
        if (students[i].fizyka == VIDMINNO) {
            cout << students[i].prizv << endl;
        }
    }
}
