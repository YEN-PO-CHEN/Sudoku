#include "sudoku.h"

Sudoku::Sudoku()
{
    for (int i = 0; i < NUM_SUDOKU; i++)
    {
        Sudoku::_sudoku[i] = 0;
    }
}

void Sudoku::generate()
{
    int gen_sudoku[NUM_SUDOKU] = {
        0, 4, 0, 2, 1, 0, 0, 0, 0,
        8, 0, 7, 0, 0, 0, 0, 9, 0,
        2, 0, 0, 8, 0, 0, 4, 0, 1,
        3, 0, 0, 0, 0, 2, 9, 0, 5,
        0, 0, 5, 7, 0, 8, 6, 0, 0,
        7, 0, 6, 5, 0, 0, 0, 0, 4,
        5, 0, 1, 0, 0, 4, 0, 0, 9,
        0, 6, 0, 0, 0, 0, 7, 0, 8,
        0, 0, 0, 0, 2, 7, 0, 5, 0};
    for (int n = 0; n < NUM_SUDOKU; n++)
    {
        printf("%d ", gen_sudoku[n]);
        if ((n + 1) % 9 == 0)
            printf("\n");
    }
}

void Sudoku::input_Sudoku_table()
{
    for (int i = 0; i < 9; i++)
    {
        int k = i * 9;
        cin >> _sudoku[k] >> _sudoku[k + 1] >> _sudoku[k + 2] >> _sudoku[k + 3] >> _sudoku[k + 4] >> _sudoku[k + 5] >> _sudoku[k + 6] >> _sudoku[k + 7] >> _sudoku[k + 8];
    }
    move_to_temp();
    return;
}

void Sudoku::move_from_temp()
{
    for (int tem = 0; tem < NUM_SUDOKU; tem++)
    {
        _sudoku[tem] = _temp_sudoku[tem];
    }
    return;
}

void Sudoku::move_to_temp()
{
    for (int tem = 0; tem < NUM_SUDOKU; tem++)
    {
        _temp_sudoku[tem] = _sudoku[tem];
    }
    return;
}
void Sudoku::print_table()
{
    for (int n = 0; n < NUM_SUDOKU; n++)
    {
        cout<<_sudoku[n]<<" ";
        if ((n + 1) % 9 == 0)
            cout<<"endl";
    }
}
void Sudoku::transform()
{
    int judge[3];
    while (1)
    {
        cin >> judge[0];
        /* >> judge[1] >> judge[2];
        int x = judge[1];
        int y = judge[2];
        */
        if (judge[0] == 0)
        {
            print_table();
            break;
        }
        switch (judge[0])
        {
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

void Sudoku::swapNum(int x, int y)
{
    for (int sN = 0; sN < NUM_SUDOKU; sN++)
    {
        if (_sudoku[sN] == x)
            _temp_sudoku[sN] = y;
        if (_sudoku[sN] == y)
            _temp_sudoku[sN] = x;
    }
    return;
}

void Sudoku::swapRow(int x, int y)
{
    if (x > y)
    {
        int temp = x;
        x = y;
        y = temp;
    }
    for (int Row = 0; Row < 3; Row++)
    {
        for (int sR = 0; sR < 9; sR++)
        {
            _temp_sudoku[sR + 27 * x + 9 * Row] = _sudoku[sR + 27 * y + 9 * Row];
            _temp_sudoku[sR + 27 * y + 9 * Row] = _sudoku[sR + 27 * x + 9 * Row];
        }
    }
    int no_change = 3 - x - y;
    for (int noc = 0; noc < 27; noc++)
    {
        _temp_sudoku[noc + no_change * 27] = _sudoku[noc + no_change * 27];
    }
}
void Sudoku::swapCol(int x, int y)
{
    if (x > y)
    {
        int temp = x;
        x = y;
        y = temp;
    }
    for (int Col = 0; Col < 3; Col++)
    {
        for (int sC = 0; sC < 9; sC++)
        {
            _temp_sudoku[9 * sC + Col + 3 * x] = _sudoku[9 * sC + Col + 3 * y];
            _temp_sudoku[9 * sC + Col + 3 * y] = _sudoku[9 * sC + Col + 3 * x];
        }
    }
    int no_change = 3 - x - y;
    for (int noc = 0; noc < 3; noc++)
    {
        for (int sC = 0; sC < 9; sC++)
            _temp_sudoku[9 * sC + noc + 3 * no_change] = _sudoku[9 * sC + noc + 3 * no_change];
    }
}

void Sudoku::rotate(int x)
{
    for (int a = 0; a < x; a++)
    {
        for (int ro = 0; ro < NUM_SUDOKU; ro++)
        {
            int row = ro / 9;
            int col = ro % 9;
            _temp_sudoku[ro] = _sudoku[row + 9 * (9 - col - 1)];
        }
        move_from_temp();
    }
    return;
}

void Sudoku::flip(int x)
{
    switch (x)
    {
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

void Sudoku::ud_flip()
{
    for (int udf = 0; udf < NUM_SUDOKU; udf++)
    {
        int x = udf / 9;
        int y = udf % 9;
        _temp_sudoku[udf] = _sudoku[9 * (9 - 1 - x) + y];
    }
    return;
}

void Sudoku::lr_flip()
{
    for (int udf = 0; udf < NUM_SUDOKU; udf++)
    {
        int x = udf / 9;
        int y = udf % 9;
        _temp_sudoku[udf] = _sudoku[9 * x + (9 - 1 - y)];
    }
    return;
}

void Sudoku::before_recursive()
{
    //step 1:check number is more than 16.
    int count = 0;
    for (int solve = 0; solve < NUM_SUDOKU; solve++)
    {
        if (_sudoku[solve] != 0)
            count++;
    }
    if (count < 17)
    {
        cout << "2\n";
        return;
    }
    //step 2:unique solution.
    move_to_temp();
    unique_solution();
}

void Sudoku::unique_solution()
{
}

bool Sudoku::solve(Sudoku question, Sudoku &answer)
{
    int firstZero;
    firstZero = getFirstZeroIndex();
    if (firstZero == -1)
    { //end condition
    }
    else
    {
        for (int num = 1; num <= 9; num++)
        {
            question.setElement(firstZero, num);
            if (solve(question, answer))
                return true;
        }
        return false;
    }
}
void Sudoku::setElement(int index, int value)
{
    _sudoku[index] = value;
}
int Sudoku::getFirstZeroIndex()
{
    for (int i = 0; i < NUM_SUDOKU; i++)
        if (_sudoku[i] == 0)
            return i;
    return -1;
}