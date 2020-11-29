#include <iostream>
#include <ctime>
#include <omp.h>


int N = -1;//Размер массива A
int *A;//Динамический массив
int max_sum;//Максимальная сумма элементов знакочередующегося ряда
int l = 0, r = 1;//Левая и правая границы максимальной суммы

int main() {
    //ввод N
    while (N <= 10) {
        std::cout << "Entre length of array A, > 10\n";
        std::cin >> N;
    }

    //инициализация A
    A = new int[N];

    //ввод элементов A
    char c = '1';
    while (c != 'y' && c != 'n') {
        std::cout << "Do you want to enter A random it?\nEnter 'y' if you want to enter it, else enter 'n'.\n";
        std::cin >> c;
    }

    if (c == 'y')
        for (int i = 0; i < N; i++) {
            std::cin >> A[i];
        }
    else {
        srand(std::time(NULL));
        for (int i = 0; i < N; i++) {
            A[i] = rand();
            std::cout << A[i] << " ";
        }
        std::cout << '\n';

    }

    //начальное значение максимальной суммы
    max_sum = A[0] - A[1];

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            int sign = 1;
            int cur_sum = 0;
            for (int j = i; j < N; j++) {
                cur_sum += A[j] * sign;
                sign *= -1;
                #pragma omp critical
                {
                    if (cur_sum > max_sum) {
                        max_sum = cur_sum;
                        l = i;
                        r = j;
                    }
                }
            }
        }
    }

    //вывод результата
    std::cout << "Sum: " << max_sum << '\n';
    std::cout << "i: " << l << "; j: " << r << '\n';
}