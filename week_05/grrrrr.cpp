#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAP_SIZE = 10;
const int OBSTACLE_NUM = 3;

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

// 이동 가능한 방향
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

// 맵 상태 (0: 빈칸, 1: 장애물, 2: 아군, 3: 적군)
int map[MAP_SIZE][MAP_SIZE];

// 장애물 생성
void generateObstacles() {
    int cnt = 0;
    while (cnt < OBSTACLE_NUM) {
        int x = rand() % MAP_SIZE;
        int y = rand() % MAP_SIZE;
        if (map[x][y] == 0) {
            map[x][y] = 1;
            cnt++;
        }
    }
}

// 초기 맵 생성
void initMap() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            map[i][j] = 0;
        }
    }
    map[rand() % MAP_SIZE][rand() % MAP_SIZE] = 2; // 아군 생성
    map[rand() % MAP_SIZE][rand() % MAP_SIZE] = 3; // 적군 생성
    generateObstacles(); // 장애물 생성
}

// 현재 맵 출력
void printMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == 0) {
                cout << ".";
            }
            else if (map[i][j] == 1) {
                cout << "#";
            }
            else if (map[i][j] == 2) {
                cout << "O";
            }
            else if (map[i][j] == 3) {
                cout << "X";
            }
        }
        cout << endl;
    }
}

// 현재 위치에서 이동 가능한 모든 위치 탐색
vector<Point> getAdjacentPoints(int x, int y) {
    vector<Point> adjPoints;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < MAP_SIZE && ny >= 0 && ny < MAP_SIZE &&
            (map[nx][ny] == 0 || map[nx][ny] == 2)) { // 이동 가능한 위치
            adjPoints.push_back(Point(nx, ny));
        }
    }
    return adjPoints;
}

// bfs를 이용한 최단 경로 탐색
vector<Point> findShortestPath(Point start, Point end) {
    vector<Point> shortestPath;
    queue<vector<Point>> q;
    vector<Point> startPath;
    startPath.push_back(start);
    q.push(startPath);

    while (!q.empty()) {
        vector<Point> currPath = q.front();
        q.pop();
        Point currPos = currPath.back();

        if (currPos.x == end.x && currPos.y == end.y) { // 도착지 도달
            shortestPath = currPath;
            break;
        }

        vector<Point> adjPoints = getAdjacentPoints(currPos.x, currPos.y);
        for (int i = 0; i < adjPoints.size(); i++) {
            Point adjPos = adjPoints[i];
            bool visited = false;
            for (int j = 0; j < currPath.size(); j++) {
                if (currPath[j].x == adjPos.x && currPath[j].y == adjPos.y) {
                    visited = true;
                    break;
                }
            }
            if (!visited) {
                vector<Point> newPath = currPath;
                newPath.push_back(adjPos);
                q.push(newPath);
            }
        }
    }

    return shortestPath;
}

// 최단 경로 출력
void printShortestPath(const vector<Point>& shortestPath) {
    cout << "Shortest Path: ";
    for (int i = 0; i < shortestPath.size() - 1; i++) {
        int dx = shortestPath[i + 1].x - shortestPath[i].x;
        int dy = shortestPath[i + 1].y - shortestPath[i].y;
        if (dx == 1) {
            cout << "Right ";
        }
        else if (dx == -1) {
            cout << "Left ";
        }
        else if (dy == 1) {
            cout << "Down ";
        }
        else if (dy == -1) {
            cout << "Up ";
        }
    }
    cout << endl;
}

void printPath(vector<Point> path) {
    string pathStr = "";
    for (int i = 1; i < path.size(); i++) {
        int dx = path[i].x - path[i - 1].x;
        int dy = path[i].y - path[i - 1].y;
        if (dx == 1 && dy == 0) {
            pathStr += "D";
        }
        else if (dx == -1 && dy == 0) {
            pathStr += "U";
        }
        else if (dx == 0 && dy == 1) {
            pathStr += "R";
        }
        else if (dx == 0 && dy == -1) {
            pathStr += "L";
        }
    }
    cout << "X's shortest path: " << pathStr << endl;
}


int main() {
    initMap();
    printMap();

    Point start(-1, -1), end(-1, -1);
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == 2) { // 아군의 위치
                start = Point(i, j);
            }
            else if (map[i][j] == 3) { // 적군의 위치
                end = Point(i, j);
            }
        }
    }

    vector<Point> shortestPath = findShortestPath(start, end);

    cout << "최단 경로: ";
    for (int i = 0; i < shortestPath.size(); i++) {
        cout << "(" << shortestPath[i].x << ", " << shortestPath[i].y << ")";
        if (i != shortestPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}