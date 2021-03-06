#include "sudoku.h"
#include <vector>

Sudoku::Sudoku() {
    //initialization
    for (int i = 0; i < NUM_SUDOKU; ++i) {
        Sudoku::_sudoku[i] = 0;
        Sudoku::_temp_sudoku[i] = 0;
        for (int z = 0; z < 10; ++z)
            Sudoku::_3D_sudoku[i / 9][i % 9][z] = z;
        //for (int z = 0; z < 10; ++z)Sudoku::_trans_3D_sudoku[i / 9][i % 9][z] = z;
    }
}

void Sudoku::generate() {
    //generate
    int gen_sudoku[NUM_SUDOKU] = {
        0, 4, 0, 2, 1, 0, 0, 0, 0,
        8, 0, 7, 0, 0, 0, 0, 9, 0,
        2, 0, 0, 8, 0, 0, 4, 0, 1,
        3, 0, 0, 0, 0, 2, 9, 0, 5,
        0, 0, 5, 7, 0, 8, 6, 0, 0,
        7, 0, 6, 5, 0, 0, 0, 0, 4,
        5, 0, 1, 0, 0, 4, 0, 0, 9,
        0, 6, 0, 0, 0, 0, 7, 0, 8,
        0, 0, 0, 0, 2, 7, 0, 5, 0
    };
    for (int n = 0; n < NUM_SUDOKU; ++n) {
        printf("%d ", gen_sudoku[n]);
        if ((n + 1) % 9 == 0)
            printf("\n");
    }
}

void Sudoku::input_Sudoku_table() {
    //transform 存入一維陣列
    for (int i = 0; i < 9; ++i) {
        int k = i * 9;
        cin >> _sudoku[k] >> _sudoku[k + 1] >> _sudoku[k + 2] >> _sudoku[k + 3] >> _sudoku[k + 4] >> _sudoku[k + 5] >> _sudoku[k + 6] >> _sudoku[k + 7] >> _sudoku[k + 8];
    }
    move_to_temp();
    return;
}

void Sudoku::move_to_temp() {
    //transform 暫存
    for (int tem = 0; tem < NUM_SUDOKU; ++tem)
        _temp_sudoku[tem] = _sudoku[tem];
    return;
}

void Sudoku::transform() {
    //transform 主要function
    int judge[3];
    while (1) {
        cin >> judge[0];
        if (judge[0] == 0) {
            print_table();
            break;
        }
        switch (judge[0]) {
        case 1:
            cin >> judge[1] >> judge[2];
            Sudoku::swapNum(judge[1], judge[2]);
            break;
        case 2:
            cin >> judge[1] >> judge[2];
            Sudoku::swapRow(judge[1], judge[2]);
            break;
        case 3:
            cin >> judge[1] >> judge[2];
            Sudoku::swapCol(judge[1], judge[2]);
            break;
        case 4:
            cin >> judge[1];
            Sudoku::rotate(judge[1]);
            break;
        case 5:
            cin >> judge[1];
            Sudoku::flip(judge[1]);
            break;
        default:
            break;
        }
        move_from_temp();
    }
    return;
}

void Sudoku::move_from_temp() {
    //transform 自暫存輸入
    for (int tem = 0; tem < NUM_SUDOKU; tem++)
        _sudoku[tem] = _temp_sudoku[tem];
    return;
}

void Sudoku::print_table() {
    //transform 輸出陣列
    for (int n = 0; n < NUM_SUDOKU; ++n) {
        if ((n + 1) % 9 != 0)
            cout << _sudoku[n] << " ";
        if ((n + 1) % 9 == 0)
            cout << _sudoku[n] << endl;
    }
    return;
}

void Sudoku::swapNum(int x, int y) {
    //transform 換數字
    for (int sN = 0; sN < NUM_SUDOKU; sN++) {
        if (_sudoku[sN] == x)
            _temp_sudoku[sN] = y;
        if (_sudoku[sN] == y)
            _temp_sudoku[sN] = x;
    }
    return;
}

void Sudoku::swapRow(int x, int y) {
    //transform 換行
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
    for (int Row = 0; Row < 3; ++Row) {
        for (int sR = 0; sR < 9; ++sR) {
            _temp_sudoku[sR + 27 * x + 9 * Row] = _sudoku[sR + 27 * y + 9 * Row];
            _temp_sudoku[sR + 27 * y + 9 * Row] = _sudoku[sR + 27 * x + 9 * Row];
        }
    }
    int no_change = 3 - x - y;
    for (int noc = 0; noc < 27; ++noc)
        _temp_sudoku[noc + no_change * 27] = _sudoku[noc + no_change * 27];
}

void Sudoku::swapCol(int x, int y) {
    //transform 換列
    if (x > y) {
        int temp = x;
        x = y;
        y = temp;
    }
    for (int Col = 0; Col < 3; ++Col) {
        for (int sC = 0; sC < 9; ++sC) {
            _temp_sudoku[9 * sC + Col + 3 * x] = _sudoku[9 * sC + Col + 3 * y];
            _temp_sudoku[9 * sC + Col + 3 * y] = _sudoku[9 * sC + Col + 3 * x];
        }
    }
    int no_change = 3 - x - y;
    for (int noc = 0; noc < 3; ++noc) {
        for (int sC = 0; sC < 9; ++sC)
            _temp_sudoku[9 * sC + noc + 3 * no_change] = _sudoku[9 * sC + noc + 3 * no_change];
    }
}

void Sudoku::rotate(int x) {
    //transform 旋轉
    for (int a = 0; a < x; ++a) {
        for (int ro = 0; ro < NUM_SUDOKU; ++ro) {
            int row = ro / 9;
            int col = ro % 9;
            _temp_sudoku[ro] = _sudoku[row + 9 * (9 - col - 1)];
        }
        move_from_temp();
    }
    return;
}

void Sudoku::flip(int x) {
    //transform 翻轉
    switch (x) {
    case 0: //up-down flip
        ud_flip();
        break;

    case 1: //left-right flip
        lr_flip();
        break;
    default:
        break;
    }
    return;
}

void Sudoku::ud_flip() {
    //transform 上下翻轉
    for (int udf = 0; udf < NUM_SUDOKU; ++udf) {
        int x = udf / 9;
        int y = udf % 9;
        _temp_sudoku[udf] = _sudoku[9 * (9 - 1 - x) + y];
    }
    return;
}

void Sudoku::lr_flip() {
    //transform 左右翻轉
    for (int udf = 0; udf < NUM_SUDOKU; ++udf) {
        int x = udf / 9;
        int y = udf % 9;
        _temp_sudoku[udf] = _sudoku[9 * x + (9 - 1 - y)];
    }
    return;
}
/**********************
*solve
***********************/

void Sudoku::s_input_Sudoku_2D() {
    //input by keyboard
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            cin >> _3D_sudoku[i][j][0];

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (_3D_sudoku[i][j][0] != 0)
                for (int k = 1; k < 10; ++k)
                    _3D_sudoku[i][j][k] = 0;
    return;
}

void Sudoku::s_output_Sudoku_2D() {
    //output to terminal
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 8; ++j)
            cout << _3D_sudoku[i][j][0] << " ";
        cout << _3D_sudoku[i][8][0] << endl;
    }
}

bool Sudoku::s_number_of_zero() {
    //how many spaces are zero.
    //空格大於65
    int zero = 0;
    for (int i = 0; i < NUM_SUDOKU; ++i)
        if (_3D_sudoku[i / 9][i % 9][0] == 0)
            zero++;
    if (zero >= 65)
        return false;
    return true;
}

int Sudoku::s_searchFirstZero() {
    //find first zero
    for (int a = 0; a < NUM_SUDOKU; ++a)
        if (_3D_sudoku[a / 9][a % 9][0] == 0)
            return a;
    return 81;
}

void Sudoku::s_human_solution() {
    //before recursive
    for (int i = 0; i < NUM_SUDOKU; ++i)
        if (_3D_sudoku[i / 9][i % 9][0] == 0)
            s_fill_in(i / 9, i % 9);
    s_while();
    return;
}

void Sudoku::s_fill_in(int x, int y) {
    //find which can be filled in
    //if I enter this function, _3D_sudoku[x][y][0]=0
    //row&column
    for (int a = 0; a < SUDOKU_9; ++a) {
        _3D_sudoku[x][y][_3D_sudoku[x][a][0]] = 0;
        _3D_sudoku[x][y][_3D_sudoku[a][y][0]] = 0;
    }
    //cube
    int xx = (x / 3) * 3, yy = (y / 3) * 3;
    for (int a = xx; a < xx + 3; ++a)
        for (int b = yy; b < yy + 3; ++b)
            _3D_sudoku[x][y][_3D_sudoku[a][b][0]] = 0;
    return;
}


void Sudoku::s_while() {
    while (1) {
        bool a, b;

        bool first_time_only = s_find_the_only();

        while (first_time_only == true) { // have modified
            a = s_find_the_only();
            if (a == false)
                break;
        }


        bool first_time_3_way = s_find_3_way();


        while (first_time_3_way == true) { // have modified
            b = s_find_3_way();
            if (b == false)
                break;
        }

        if (!first_time_only && !first_time_3_way)
            break;

    }
    return;
}

bool Sudoku::s_find_3_way() {
    //
    bool modified_c = false;
    bool modified_r = false;
    bool modified_cub = false;

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c) {
            if (_3D_sudoku[r][c][0] != 0)
                continue;

            if (s_find_row(r, c))
                modified_r = true;
            if (s_find_col(r, c))
                modified_c = true;
            if (s_find_cube(r, c))
                modified_cub = true;
        }
    return modified_r || modified_c || modified_cub;
}

bool Sudoku::s_find_col(int row, int col) {
    vector<int> cnt(10, 0);

    for (int r = 0; r < 9; ++r)
        if (_3D_sudoku[r][col][0] == 0)
            for (int k = 1; k < 10; ++k)
                if (_3D_sudoku[r][col][k] != 0)
                    cnt[k]++;

    for (int i = 1; i < 10; ++i) {
        if (cnt[i] == 1 && _3D_sudoku[row][col][i] != 0) {
            _3D_sudoku[row][col][0] = i;
            update(i, row, col);
            return true;
        }
    }

    return false;
}

bool Sudoku::s_find_row(int row, int col) {
    vector<int> cnt(10, 0);

    for (int c = 0; c < 9; ++c)
        if (_3D_sudoku[row][c][0] == 0)
            for (int k = 1; k < 10; ++k)
                if (_3D_sudoku[row][c][k] != 0)
                    cnt[k]++;

    for (int i = 1; i < 10; ++i) {
        if (cnt[i] == 1 && _3D_sudoku[row][col][i] != 0) {
            _3D_sudoku[row][col][0] = i;
            update(i, row, col);
            return true;
        }
    }
    return false;
}

bool Sudoku::s_find_cube(int row, int col) {
    vector<int> cnt(10, 0);
    int s_r = (row / 3) * 3;
    int s_c = (col / 3) * 3;
    for (int r = s_r; r < s_r + 3; ++r)
        for (int c = s_c; c < s_c + 3; ++c)
            if (_3D_sudoku[r][c][0] == 0)
                for (int num = 1; num < 10; ++num)
                    if (_3D_sudoku[r][c][num] != 0)
                        cnt[num]++;

    for (int i = 1; i < 10; ++i) {
        if (cnt[i] == 1 && _3D_sudoku[row][col][i] != 0) {
            _3D_sudoku[row][col][0] = i;
            update(i, row, col);
            return true;
        }
    }
    return false;
}

void Sudoku::update(int num, int row, int col) {
    for (int r = 0; r < 9; ++r)
        _3D_sudoku[r][col][num] = 0;
    for (int c = 0; c < 9; ++c)
        _3D_sudoku[row][c][num] = 0;

    int x = (row / 3) * 3, y = (col / 3) * 3;
    for (int a = x; a < x + 3; ++a)
        for (int b = y; b < y + 3; ++b)
            _3D_sudoku[a][b][num] = 0;

    for (int k = 1; k < 10; ++k)
        _3D_sudoku[row][col][k] = 0;

 
}

bool Sudoku::no_solution() {
    int count = 0;
    for (int i = 0; i < 81; ++i) {
        for (int j = 0; j < 10; j++)
            if (_3D_sudoku[i / 9][i % 9][j] == 0)
                ++count;
        if (count == 10)
            return true;
        else
            count = 0;
    }
    return false;
}

bool Sudoku::s_find_the_only() {
    //find the only one answer lattice
    int last_zero = s_LastZero();
    int a;
    int aaaaaa = 0;
    bool modify = false;
    for (a = 0; a < NUM_SUDOKU; ++a) {
        
        //find where is zero
        if (_3D_sudoku[a / 9][a % 9][0] != 0)
            continue;
        //where has the only one solution
        int temp = 0;
        for (int b = 1; b < 10 && temp <= 1; ++b)
            if (_3D_sudoku[a / 9][a % 9][b] != 0)
                ++temp;

        //找到該值且為最後一個0
        if (a == last_zero && temp > 1)
            return false;
        //有複數個解
        if (temp > 1)
            continue;
        //找到該值
        modify = true;
        int now = 0;
        if (no_solution()) {
            cout << "0" << endl;
            exit(0);
        }
        for (now = 1; now < 10; ++now)
            if (_3D_sudoku[a / 9][a % 9][now] != 0)
                break;
        //紀錄該值到now
        _3D_sudoku[a / 9][a % 9][0] = now;

        //把上下能去掉的數值歸零
        update(now, a / 9, a % 9);
        //no solution
        /*//row&column
        for (int a = 0; a < SUDOKU_9; ++a) {
            _3D_sudoku[a / 9][a % 9][now] = 0;
            _3D_sudoku[a / 9][a % 9][now] = 0;
        }
        //cube
        int x = ((a / 9) / 3) * 3;
        int y = ((a % 9) / 3) * 3;
        for (int c = x; c < x + 3; ++c)
            for (int d = y; d < y + 3; ++d)
                _3D_sudoku[c][d][now] = 0;*/
        
    }

    return modify;
}
int Sudoku::s_LastZero() {
    for (int a = 80; a >= 0; --a)
        if (_3D_sudoku[a / 9][a % 9][0] == 0)
            return a;
    return 81;
}
/****************
original * bool Sudoku::s_solve(int num){
    num = s_searchFirstZero();
    //printf("x=%d,y=%d\n",x,y);
    if (num == 81)
        return true;
    //pass the number is nonzero
    if (_3D_sudoku[num / 9][num % 9][0] != 0)
        s_solve(num + 1);
    //check this place
    for (int in = 1; in < 10; ++in){
        if (s_check(in, num / 9, num % 9)){
            //success
            _3D_sudoku[num / 9][num % 9][0] = in;
            s_solve(num + 1);
        }
        _3D_sudoku[num / 9][num % 9][0] = 0;
    }
    //failed
    return false;}
**************/

bool Sudoku::s_solve(int num) {
    //back tracing
    if (num == 81) {
        cout << "1" << endl;
        s_output_Sudoku_2D();
        exit(0);
        return true;
    }
    //pass the number is zero
    if (_3D_sudoku[num / 9][num % 9][0] == 0) {
        //check this place
        for (int in = 1; in < 10; ++in) {

            //if(_3D_sudoku[num / 9][num % 9][in]==0)continue;

            _3D_sudoku[num / 9][num % 9][0] = in;
            if (s_check(in, num / 9, num % 9))
                //success
                if (s_solve(num + 1) == true) return true;
        }
        _3D_sudoku[num / 9][num % 9][0] = 0;
    }
    else
        s_solve(num + 1);
    return false;
}

bool Sudoku::s_check(int num, int x, int y) {
    //check this place can put this number
    //x-axis
    for (int a = 0; a < SUDOKU_9; ++a)
        if (a != x)
            if (num == _3D_sudoku[a][y][0])
                return false;
    //y-axis
    for (int b = 0; b < SUDOKU_9; ++b)
        if (b != y)
            if (num == _3D_sudoku[x][b][0])
                return false;
    //cube
    int temp_x = (x / 3) * 3;
    int temp_y = (y / 3) * 3;
    for (int a = temp_x; a < temp_x + 3; ++a)
        for (int b = temp_y; b < temp_y + 3; ++b) {
            if (a == x && b == y);
            else if (num == _3D_sudoku[a][b][0])
                return false;
        }
    return true;
}



/*bool Sudoku::s_trans_s_solve(int num){
    if (num == 81){
        if(s_double_solution()){
                cout<<"1"<<endl;
                s_output_Sudoku_2D();
                exit(0);
            }
            cout<<"2"<<endl;
            exit(0);
    }
    //pass the number is zero
    if (_trans_3D_sudoku[num / 9][num % 9][0] == 0){
        //check this place
        for (int in = 10; in > 0; ++in){
            _trans_3D_sudoku[num / 9][num % 9][0] = in;
            if (s_check(in, num / 9, num % 9))
                s_solve(num-1);
        }
        _trans_3D_sudoku[num / 9][num % 9][0] = 0;
    }
    else
        s_solve(num-1);
}*/
/* bool Sudoku::s_double_solution(){
    for (int i = 0; i < NUM_SUDOKU; ++i)
        if(_3D_sudoku[i/9][i%9][0] != _trans_3D_sudoku[i/9][i%9][0])
            return false;
    return true;
}*/
