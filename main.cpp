#include <iostream>
#include <vector>

using namespace std;

typedef char Cell;
typedef vector<vector<Cell>> Board;
typedef vector<int> Gram;
typedef vector<Gram> Nonogram;

const char EMPTY = '.';
const char FILL = '#';
const char UNKNOWN = '?';

Nonogram __desolve(const Board &board) {
  Nonogram vertical;
  for (const auto &r : board) {
    Gram g;
    int cur_count = 0;
    for (const auto &c : r) {
      if (c == EMPTY) {
        if (cur_count) g.push_back(cur_count);
        cur_count = 0;
      } else {
        cur_count++;
      }
    }
    if (cur_count) g.push_back(cur_count);
    vertical.push_back(g);
  }
  return vertical;
}

pair<Nonogram, Nonogram> desolve(const Board &board) {
  const int dims = board.size();
  Board t_board(dims, vector<Cell>(dims, EMPTY));
  for (int i = 0; i < dims; i++)
    for (int j = 0; j < dims; j++) {
      t_board[j][i] = board[i][j];
    }
  return {__desolve(t_board), __desolve(board)};
}

Board random_board(int dims, double fill_rate) {
  Board b(dims, vector<Cell>(dims, EMPTY));
  if (fill_rate < 0.0) {
    fill_rate = 0.0;
    fprintf(stderr, "fill_rate is below zero");
  }
  if (fill_rate > 1.0) {
    fill_rate = 1.0;
    fprintf(stderr, "fill_rate is above one");
  }
  int fills = int(dims * dims * fill_rate);
  while (fills > 0) {
    int x = rand() % dims, y = rand() % dims;
    if (b[x][y] == FILL) continue;
    b[x][y] = FILL;
    fills--;
  }
  return b;
}

void print(const Board &board) {
  for (const auto &row : board) {
    for (const auto &c : row) {
      putchar(c);
    }
    putchar('\n');
  }
}

string encode_gram(const Nonogram &nonogram) {
  string encoded = "";
  for (const auto &gram : nonogram) {
    for (const auto &g : gram) {
      char code = 'A' + int(g - 1);
      encoded.push_back(code);
    }
    encoded.push_back(' ');
  }
  return encoded;
}

void print_gram(const Nonogram &nonogram) {
  printf("[");
  for (const auto &gram : nonogram) {
    printf("[");
    for (auto x : gram) printf("%d ", x);
    printf("]");
  }
  printf("]\n");
}

string encode_board(const Board &board) {
  string encoded = "";
  encoded += to_string(board.size()) + "\t";

  for (const auto &row : board) {
    string row_s(row.begin(), row.end());
    encoded += row_s + "\\n";
  }
  encoded += "\t";

  auto grams = desolve(board);
  encoded += encode_gram(grams.first) + "\t";
  encoded += encode_gram(grams.second) + "\t";
  return encoded;
}

void generate_all(Board &board, int dims, int i, int j, int prob) {
  if (prob != 0 && (i & 1) && (rand() % 100 < prob)) {
    return;
  }

  if (j == dims) {
    i++;
    j = 0;
  }
  if (i == dims) {
    string encoded = encode_board(board);
    cout << encoded << "\n";
    return;
  }
  board[i][j] = EMPTY;
  generate_all(board, dims, i, j + 1, prob);
  board[i][j] = FILL;
  generate_all(board, dims, i, j + 1, prob);
}

void generate_all(int dims, int prob) {
  Board board(dims, vector<Cell>(dims, UNKNOWN));
  generate_all(board, dims, 0, 0, prob);
}

void __test() {
  int dims = 10;
  float fill_rate = .5;
  // cin >> dims >> fill_rate;
  auto board = random_board(dims, fill_rate);
  print(board);
  auto d = desolve(board);
  cout << (encode_gram(d.first));
  print_gram(d.first);
  cout << (encode_gram(d.second));
  print_gram(d.second);
}

int main() {
  int dims = 1;
  int prob = 0;
  cin >> dims >> prob;
  generate_all(dims, prob);
}