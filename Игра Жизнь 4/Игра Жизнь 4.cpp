// Игра Жизнь 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>

using namespace std;



// Состояния клетки
const int DEAD = 0;
const int ALIVE = 1;


/*
 * Количество живых клеток на игровом поле
*/
 int get_live_count(vector<vector<int>>& grid, int HEIGHT, int WIDTH)
{
    unsigned int count1 = 0;
    unsigned i, j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            if (grid[i][j] == 1) {
                count1++;
            }
        }
    }
  
    return count1;
}

// Функция, возвращающая количество живых соседей клетки
int countLiveNeighbors(vector<vector<int>>& grid, int x, int y, int WIDTH, int HEIGHT) 
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < WIDTH && j >= 0 && j < HEIGHT && (i != x || j != y) && grid[i][j] == ALIVE) {
                count++;
                
            }
        }
    }
   
    return count;
}


// Функция, обновляющая состояние клетки на следующем шаге
int updateCell(vector<vector<int>>& grid, int x, int y, int WIDTH, int HEIGHT)
{
    int liveNeighbors = countLiveNeighbors(grid, x, y, WIDTH, HEIGHT);
    if (grid[x][y] == ALIVE) {
        if (liveNeighbors < 2 || liveNeighbors > 3) {
            return DEAD; // Клетка умирает
        }
    }
    else {
        if (liveNeighbors == 3)
        {
            return ALIVE; // Клетка рождается
        }
    }
    return grid[x][y]; // Клетка остается в том же состоянии
}

int main() {
   // setlocale(LC_ALL, "Russian");
    unsigned rows1{20};       // количество строк
    unsigned columns1{30};  // количество столбцов
  
    std::ofstream fout("data.txt"); // открыли файл C:\data.txt на запись
    fout << rows1 << " " << columns1 << endl;
    fout << "2 3" << endl;// записали в файл C:\data.txt строку
    fout << "2 4" << endl;
    fout << "3 4" << endl;
    fout << "3 5" << endl;
    fout << "3 6" << endl;
    fout << "3 7" << endl;
    fout << "5 0" << endl;
    fout << "5 1" << endl;
    fout << "5 2" << endl;
    fout << "6 2" << endl;
    fout.close(); // закрыли файл

   // unsigned rows2{};       // количество строк
   // unsigned columns2{};  // количество столбцов
    int WIDTH{};//columns2
    int HEIGHT{};//

   
   


    std::ifstream f("data.txt");
    if (f.is_open())
    {
        f >> HEIGHT;
        std::cout << " HEIGHT" << " " << HEIGHT << "\t";
        f >> WIDTH;
        std::cout << " WIDTH" << " " << WIDTH << std::endl;
    }
  
    vector<vector<int>> grid(WIDTH, vector<int>(HEIGHT, DEAD));

   
    for (unsigned i{}; i < HEIGHT; i++) // заполняем  массив значениями из файла
       
    {

        for (unsigned j{}; j < WIDTH; j++)
        {

           // if (f.eof()) break;
            f >> i;
            f >> j;
            if (f.eof()) break;

            //std::cout << "i" << " " << i << "\t";
            grid[i][j] = 1;


        }
    }
    f.close();
   
    
  
    


    int x{};
    int y{};
    int Alive_cells{};
   
    bool is_optimal = false;
    unsigned int gen = 1;
  
    
    srand(time(NULL));
    /*
    * // Инициализируем поле случайными значениями
    for (int i = 0; i < WIDTH; i++) {
       for (int j = 0; j < HEIGHT; j++) {
            grid[i][j] = rand() % 2;
        }
    }
 */
    
    // Запускаем игру
 

        do{
       // int Alive_cells{};
         Alive_cells = get_live_count(grid, HEIGHT, WIDTH) ;

        // Выводим текущее состояние поля
        for (int i = 0; i < WIDTH; i++) 
        {
            for (int j = 0; j < HEIGHT; j++) 
            {
                cout << (grid[i][j] == ALIVE ? "*" : "-") << " ";
               
               
            }
            cout << endl;
         
        } cout << "Generated :" << gen++<<" " << " Alive cells : " << Alive_cells;
       
        cout << endl;

        // Обновляем состояние поля
        vector<vector<int>> newGrid(WIDTH, vector<int>(HEIGHT, DEAD));
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                newGrid[i][j] = updateCell(grid, i, j, WIDTH, HEIGHT);
            }
        }
        if (Alive_cells == 0) {
            std::cout << " Alive cells are dead. Game ower  " << std::endl;
            break;
        }
        if (grid == newGrid) {
            std::cout << "The world has stagnated. Game ower" << std::endl;
            break;
        }

        grid = newGrid;
       
       
        Sleep(1000);
        system("cls");
    } while (Alive_cells != 0 );

      

    return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
