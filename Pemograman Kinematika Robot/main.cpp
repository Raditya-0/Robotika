#include <iostream>
#include <fstream>
#include <cmath>

#define PI 3.14159265359
#define RAD PI / 180.0

using namespace std;

class Motor {
private:
    int id;
    float speed;

public:
    Motor(int motorId) : id(motorId), speed(0) {}

    void setSpeed(float spd) { speed = spd; }
    float getSpeed() const { return speed; }
    int getId() const { return id; }
};

class RobotBase {
protected:
    Motor motors[4] = { Motor(0), Motor(1), Motor(2), Motor(3) };
    float matrix[4][3] = {
        {cos(45.0 * RAD), sin(45.0 * RAD), 1},
        {cos(135.0 * RAD), sin(135.0 * RAD), 1},
        {cos(225.0 * RAD), sin(225.0 * RAD), 1},
        {cos(315.0 * RAD), sin(315.0 * RAD), 1}
    };

public:
    virtual void calculateSpeeds(int speedVector[3]) {
        for (int i = 0; i < 4; i++) {
            motors[i].setSpeed(
                matrix[i][0] * speedVector[0] +
                matrix[i][1] * speedVector[1] +
                matrix[i][2] * speedVector[2]
            );
        }
    }

    void displayMotorSpeeds() const {
        for (const Motor &motor : motors) {
            cout << "Motor " << motor.getId() << " Speed: " << motor.getSpeed() << endl;
        }
    }

    float getMotorSpeed(int motorId) const {
        return motors[motorId].getSpeed();
    }

    void logSpeedsToFile(const string &filename, int testCaseNumber) {
        ofstream file(filename, ios::out);  // Mode ios::out untuk menimpa file
        if (file.is_open()) {
            file << "\nTest Case " << testCaseNumber << ":\n";  // Tambahkan label Test Case
            for (const Motor &motor : motors) {
                file << "Motor " << motor.getId() << " Speed: " << motor.getSpeed() << endl;
            }
            file.close();
            cout << "Data awal kecepatan motor telah disimpan ke file." << endl;
        }
    }

    void appendSpeedsToFile(const string &filename, int testCaseNumber) {
        ofstream file(filename, ios::app);  // Mode ios::app untuk menambah data tanpa menimpa
        if (file.is_open()) {
            file << "\nTest Case " << testCaseNumber << ":\n";  // Tambahkan label Test Case
            for (const Motor &motor : motors) {
                file << "Motor " << motor.getId() << " Speed: " << motor.getSpeed() << endl;
            }
            file.close();
            cout << "Data tambahan kecepatan motor telah ditambahkan ke file (Test Case " << testCaseNumber << ")." << endl;
        }
    }

    void readSpeedsFromFile(const string &filename) {
        ifstream file(filename, ios::in);  // Mode ios::in untuk membaca file
        if (file.is_open()) {
            string line;
            cout << "\nIsi dari file " << filename << ":" << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Gagal membuka file untuk membaca." << endl;
        }
    }

    int getLastTestCaseNumber(const string &filename) {
        ifstream file(filename, ios::in);
        int lastTestCase = 0;
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                // Mencari baris yang dimulai dengan "Test Case"
                if (line.find("Test Case") != string::npos) {
                    // Menangkap nomor test case
                    size_t pos = line.find("Test Case") + 10; // Temukan posisi setelah "Test Case "
                    lastTestCase = stoi(line.substr(pos));  // Ubah string menjadi integer
                }
            }
            file.close();
        }
        return lastTestCase;
    }
};

class AdvancedRobotBase : public RobotBase {
public:
    void calculateSpeeds(int speedVector[3]) override {
        // Implementasi khusus untuk robot canggih
        for (int i = 0; i < 4; i++) {
            motors[i].setSpeed(
                (matrix[i][0] * speedVector[0] * 1.1) +
                (matrix[i][1] * speedVector[1] * 1.1) +
                (matrix[i][2] * speedVector[2] * 1.1)
            );
        }
    }

    void enhancedLogSpeeds(const string &filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            for (int i = 0; i < 4; i++) {
                file << "Motor " << i << " Enhanced Speed Log: " << getMotorSpeed(i) << endl;
            }
            file.close();
            cout << "Enhanced log saved to file." << endl;
        }
    }
};

int main() {
    AdvancedRobotBase robot;
    int speedVector[3];
    int check;

    // Mengambil nomor test case terakhir dari file
    int testCaseNumber = robot.getLastTestCaseNumber("movement_log.txt") + 1;  // Inisialisasi nomor test case

    cout << "Masukkan kecepatan X: ";
    cin >> speedVector[0];
    cout << "Masukkan kecepatan Y: ";
    cin >> speedVector[1];
    cout << "Masukkan kecepatan Z (rotasi): ";
    cin >> speedVector[2];

    robot.calculateSpeeds(speedVector);
    robot.displayMotorSpeeds();

    cout << "Apakah Print Hasil Sebelumnya (iya = 1): ";
    cin >> check;

    if (check != 1) {
        testCaseNumber = 1;
        // Menyimpan data awal ke file (menimpa isi file)
        robot.logSpeedsToFile("movement_log.txt", testCaseNumber);
    } else {
        // Menambah data baru ke file tanpa menimpa dan menambah label test case
        robot.appendSpeedsToFile("movement_log.txt", testCaseNumber);
    }

    // Membaca data dari file dan menampilkannya
    robot.readSpeedsFromFile("movement_log.txt");

    return 0;
}
