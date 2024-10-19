#include <iostream>
#include <vector>

using namespace std;

struct Robot {
    int x, y;
    int speed;
    bool can_pass_walls;

    Robot(int startX, int startY) : x(startX), y(startY), speed(2), can_pass_walls(false) {}

    int get_travel_time() const {
        return speed;
    }

    bool move(char direction, int M, int N, const vector<vector<char>>& grid) {
        int newX = x, newY = y;
        if (direction == 'U') newX--;
        else if (direction == 'D') newX++;
        else if (direction == 'L') newY--;
        else if (direction == 'R') newY++;
        else return false;

        if (newX < 0 || newX >= M || newY < 0 || newY >= N) {
            return false;
        }

        if (grid[newX][newY] == 'x' && !can_pass_walls) {
            cout << "Robot nabrak, silahkan diperbaiki" << endl;
            return false;
        }

        x = newX;
        y = newY;
        return true;
    }
};

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<char>> grid(M, vector<char>(N));
    int startX, startY, goalX, goalY;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                startX = i;
                startY = j;
            }
            else if (grid[i][j] == 'F') {
                goalX = i;
                goalY = j;
            }
        }
    }

    int P;
    cin >> P;

    vector<char> moves(P);
    for (int i = 0; i < P; ++i) {
        cin >> moves[i];
    }

    Robot robot(startX, startY);
    int total_time = 0;
    bool met_official = false;

    for (char move : moves) {
        bool moved = robot.move(move, M, N, grid);
        if (!moved) {
            continue;
        }

        int x = robot.x;
        int y = robot.y;
        char current = grid[x][y];

        if (current == 'M') {
            cout << "Bertemu dengan mekanik, siap membasmi rintangan" << endl;
            robot.can_pass_walls = true;
            continue;
        }
        else if (current == 'E') {
            cout << "Bertemu dengan electrical, kecepatan roda naik menjadi 200%" << endl;
            robot.speed = 1;
        }
        else if (current == 'P') {
            cout << "Bertemu dengan Programming, diajak ikut KRI" << endl;
        }
        else if (current == 'O') {
            cout << "Bertemu dengan official, diajak ngonten bareng" << endl;
            met_official = true;
        }

        total_time += robot.get_travel_time();
    }

    if (met_official) {
        total_time *= 2;
    }

    if (robot.x == goalX && robot.y == goalY) {
        cout << "Robot berhasil mencapai tujuan" << endl;
    }
    else {
        cout << "Robot gagal dalam mencapai tujuan :(" << endl;
    }
    cout << "Robot telah berjalan selama " << total_time << " menit" << endl;

    return 0;
}

