//////////////////////////////////////////////////////////////////////////////////////
//Задача 06-10: Гиперпростые числа
//
//Ограничение времени: 1 с
//Ограничение памяти: 64 M
//Простое натуральное число называется гиперпростым, если любое число, 
//получающееся из него откидыванием нескольких последних цифр, тоже является простым. 
//Например, число 7331 – гиперпростое, т.к. и оно само, и числа 733, 73, 7 
//являются простыми. Найдите все N-значные гиперпростые числа.
//
//Входные данные: единственное целое число N (1 ≤ N ≤ 9).
//
//Выходные данные: возрастающая последовательность целых чисел через пробел
//– ответ задачи.
//////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
//////////////////////////////////////////////////////////////////////////////////////
typedef long long                                   T_num;
typedef std::vector<T_num>                          T_hyper_prime_numbers_for_len;
typedef std::vector<T_hyper_prime_numbers_for_len>  T_hyper_prime_numbers;
//////////////////////////////////////////////////////////////////////////////////////
 
bool  is_prime_number(T_num  k)
{
    if(k < 2) return false;
    for(T_num  divisor_cur = 2; divisor_cur * divisor_cur <= k; ++divisor_cur)
    {
        if(k % divisor_cur == 0)
        {
            return  false;
        }
    }    
    return  true;
}
//////////////////////////////////////////////////////////////////////////////////////
int main()
{
    std::locale::global(std::locale(""));
    
    const int  NUM_LEN_MIN = 1;    
    const int  NUM_LEN_MAX = 9;    
    int        num_len = 0;
    do
    {
        std::cout << "Введите длину искомого гиперпростого числа от "
                  << NUM_LEN_MIN
                  << " до "
                  << NUM_LEN_MAX
                  <<": ";
        std::cin >> num_len;
    }while(num_len < NUM_LEN_MIN 
           || NUM_LEN_MAX < num_len);   
    
    T_hyper_prime_numbers  hyper_prime_numbers(num_len + 1);
    
    for(int num_len_cur = 0; num_len_cur <= num_len; ++num_len_cur)
    {
        if(num_len_cur == 0)
        {            
            hyper_prime_numbers[num_len_cur].push_back(0);                    
        }
        else
        {
            //Пробегаемся по гиперпростым числам предыдущей длины:
            for(T_hyper_prime_numbers_for_len::const_iterator  
                hyp_prim_num_prev_it = hyper_prime_numbers[num_len_cur - 1].begin();
                hyp_prim_num_prev_it != hyper_prime_numbers[num_len_cur - 1].end();
                ++hyp_prim_num_prev_it)
            {
                //Пробегаемся по всем хвостовым цифрам:
                for(int tail_dig_cur = 1; tail_dig_cur <= 9; ++tail_dig_cur)
                {
                    T_num  val = *hyp_prim_num_prev_it * 10 + tail_dig_cur;
                    if(is_prime_number(val))
                    {
                        hyper_prime_numbers[num_len_cur].push_back(val);
                    }
                }
            }
        }
    }
 
    if(hyper_prime_numbers[num_len].empty())
    {
        std::cout << "Не существует "
                  << num_len 
                  << "-значных гиперпростых чисел."
                  << std::endl;
    }
    else
    {
        int  counter = 0;
        for(T_hyper_prime_numbers_for_len::const_iterator  
            hyp_prim_num_it = hyper_prime_numbers[num_len].begin();
            hyp_prim_num_it != hyper_prime_numbers[num_len].end();
            ++hyp_prim_num_it)
        {
            std::cout << "#"
                      << ++counter
                      << ": "
                      << *hyp_prim_num_it
                      << std::endl;
        }    
    }
}
