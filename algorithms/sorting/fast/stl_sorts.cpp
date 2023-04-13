#include <iostream>
#include <algorithm>
#include <iterator> 
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>

using it = std::vector<int>::iterator;
using namespace std::chrono;
using nano = std::chrono::nanoseconds;  

namespace rost {
    template<typename iter, typename Tp>
        iter my_unguarded_partition(iter first, iter last, const Tp& pivot) {
            std::cout<<"my_unguarded_partition"<<std::endl;
            while (true) {
                while (*first < pivot)
                    ++first;
                --last;
                while (pivot < *last)
                    --last;
                if (!(first < last))
                    return first;
                std::swap(*first, *last);
                ++first;
            }
        }

    template<typename iter>
        void my_unguarded_linear_insert(iter last) {
            std::cout<<"my_unguarded_linear_insert"<<std::endl;
            typename std::iterator_traits<iter>::value_type val = std::move(*last);
            iter next = last;
            --next;
            while (val < *next) {
                *last = std::move(*next);
                last = next;
                --next;
            }
            *last = std::move(val);
        }

    template<typename iter>
        inline void my_unguarded_insertion_sort(iter first, iter last) {
            std::cout<<"my_unguarded_insertion_sort"<<std::endl;
            std::cout<<"my_unguarded_linear_insert in for loop"<<std::endl;
            for (iter i = first; i != last; ++i)
                my_unguarded_linear_insert(i);
        }

    /// Swaps the median value of *a, *b and *c to *a
    template<typename iter>
        void  my_move_median_first(iter a, iter b, iter c) {
            std::cout<<"my_move_median_first"<<std::endl;
            if (*a < *b) {
                if (*b < *c)
                    std::swap(*a, *b);
                else if (*a < *c)
                    std::swap(*a, *c);
            }
            else if (*a < *c)
                return;
            else if (*b < *c)
                std::swap(*a, *c);
            else
                std::swap(*a, *b);
        }  

    template<typename iter>
        inline iter my_unguarded_partition_pivot(iter first, iter last) {
            std::cout<<"my_unguarded_partition_pivot"<<std::endl;
            iter mid = first + (last - first) / 2;
            std::cout<<"my_move_median_first"<<std::endl;
            my_move_median_first(first, mid, (last - 1));
            std::cout<<"return my_unguarded_partition"<<std::endl;
            return my_unguarded_partition(first + 1, last, *first);
        }


    template<typename iter>
        void  my_heap_select(iter first, iter middle, iter last) {
            std::cout<<"my_heap_select"<<std::endl;
            std::cout<<"std::make_heap"<<std::endl;
            std::make_heap(first, middle);
            std::cout<<"std::__pop_heap in if of for loop"<<std::endl;
            for (iter i = middle; i < last; ++i)
                if (*i < *first)
                    std::__pop_heap(first, middle, i);
        }  

    template<typename iter>
        void my_insertion_sort(iter first, iter last) {
            std::cout<<"my_insertion_sort"<<std::endl;
            if (first == last)
                return;

            for (iter i = first + 1; i != last; ++i) {
                if (*i < *first) {
                    typename std::iterator_traits<iter>::value_type val = std::move(*i);
                    std::move_backward(first, i, i + 1);
                    *first = std::move(val);
                }
                else {
                    std::cout<<"my_unguarded_linear_insert"<<std::endl;
                    my_unguarded_linear_insert(i);
                }
            }
        }

    enum { _S_threshold = 16 };

    template<typename iter, typename _Size>
        void  my_introselect(iter first, iter nth,  iter last, _Size depth_limit) {
            std::cout<<"my_introselect"<<std::endl;
            while (last - first > 3) {
                if (depth_limit == 0) {
                    std::cout<<"my_heap_select"<<std::endl;

                    my_heap_select(first, nth + 1, last);

                    // Place the nth largest element in its final position.
                    std::swap(*first, *nth);
                    return;
                }

                --depth_limit;
                std::cout<<"my_unguarded_partition_pivot"<<std::endl;
                iter cut = my_unguarded_partition_pivot(first, last);
                if (cut <= nth)
                    first = cut;
                else
                    last = cut;
            }
            std::cout<<"my_insertion_sort"<<std::endl;
            my_insertion_sort(first, last);
        }

    template<typename iter>
        inline void my_partial_sort(iter first, iter middle, iter last) {
            std::cout<<"my_partial_sort"<<std::endl;
            std::cout<<"my_heap_select"<<std::endl;
            my_heap_select(first, middle, last);
            std::cout<<"std::sort_heap"<<std::endl;
            std::sort_heap(first, middle);

        }

    template<typename iter, typename Size>
        void my_introsort_loop(iter first, iter last, Size depth_limit) {
            std::cout<<"my_introsort_loop"<<std::endl;
            while (last - first > int(_S_threshold)) {
                if (depth_limit == 0) {
                    std::cout<<"my_partial_sort"<<std::endl;
                    my_partial_sort(first, last, last);
                    return;
                }
                --depth_limit;
                std::cout<<"my_unguarded_partition_pivot"<<std::endl;
                iter cut = my_unguarded_partition_pivot(first, last);
                std::cout<<"my_introsort_loop"<<std::endl;
                my_introsort_loop(cut, last, depth_limit);
                last = cut;
            }
        }

    template<typename iter>
        void my_final_insertion_sort(iter first, iter last) {
            std::cout<<"my_final_insertion_sort"<<std::endl;
            if (last - first > int(_S_threshold)) {
                std::cout<<"my_insertion_sort"<<std::endl;
                my_insertion_sort(first, first + int(_S_threshold));
                std::cout<<"my_unguarded_insertion_sort"<<std::endl;
                my_unguarded_insertion_sort(first + int(_S_threshold), last);
            }
            else {
                std::cout<<"my_insertion_sort"<<std::endl;
                my_insertion_sort(first, last);
            }
        }

    template<typename iter>
        inline void sort(iter first, iter last) {
            std::cout<<"sort"<<std::endl;
            if (first != last) {
                std::cout<<"my_introsort_loop"<<std::endl;
                my_introsort_loop(first, last,	std::__lg(last - first) * 2);
                std::cout<<"my_final_insertion_sort"<<std::endl;
                my_final_insertion_sort(first, last);
            }
        }
} //namespace rost

void quickSort(it beg, it end) {
    if (beg + 1 > end)
        return;
    int pivot  = *(beg + (end - beg)/2);
    it i = beg, j = end-1;
    while(i <= j) {
        while(*i < pivot) ++i;
        while(*j > pivot) --j;
        if (i <= j)
            std::swap(*i++, *j--);
    }
    if (beg < j)
        quickSort(beg, j+1);
    if (i < end)
        quickSort(i, end);	
}

void quick(it left, it right) {
    it i = left, j = right - 1;        
    int tmp =  *(left + (right-left) / 2);
    while (i <= j) {
        while (*i < tmp) ++i;
        while (*j > tmp) --j;
        if (i <= j)
            std::swap(*i++,*j--);
    } 
    if (left < j)
        quick(left, j+1);
    if (i < right)
        quick(i, right);
}

it partition (it begin, it end) {
    int x= *(end-1);
    it i = begin-1;    
    for(it j = begin; j < end-1; ++j) {
        if(*j <= x)
            std::swap(*++i,*j);
    }
    std::swap(*++i,*(end-1));
    return i;
}

void quickSortIterative(it left, it right) {
    std::stack<it> stk;
    stk.push(left);
    stk.push(right);

    while (!stk.empty()) {
        right = stk.top();
        stk.pop();
        left = stk.top();
        stk.pop();

        it p = partition(left, right);

        if (p > left) {
            stk.push(left);
            stk.push(p);
        }

        if (p + 1 < right) {
            stk.push(p + 1);
            stk.push(right);
        }
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    using std::cout;
    using std::endl;

    int i = atoi(argv[1]);
    std::cout<<i<<std::endl;
    std::vector<int> vec1, vec2, vec3, vec4, vec5;
    for(int index = 0; index < i; ++index)
        vec1.push_back(rand() % 10000);
    vec2 = vec1;
    vec3 = vec1;
    vec4 = vec1;
    vec5 = vec1;

    high_resolution_clock::time_point t1, t2;
    nano timer;

    t1 = high_resolution_clock::now();
    std::sort(vec1.begin(), vec1.end());
    t2 = high_resolution_clock::now();
    timer = std::chrono::duration_cast<nano> (t2-t1);
    cout<<timer.count()<<"    standart"<<endl;

    t1 = high_resolution_clock::now();
    quickSort(vec2.begin(), vec2.end());
    t2 = high_resolution_clock::now();
    timer = std::chrono::duration_cast<nano> (t2-t1);
    cout<<timer.count()<<"    cormen"<<endl;

    t1 = high_resolution_clock::now();
    quick(vec3.begin(), vec3.end());
    t2 = high_resolution_clock::now();
    timer = std::chrono::duration_cast<nano> (t2-t1);
    cout<<timer.count()<<"    my simple"<<endl;

    t1 = high_resolution_clock::now();
    quickSortIterative(vec4.begin(), vec4.end());
    t2 = high_resolution_clock::now();
    timer = std::chrono::duration_cast<nano> (t2-t1);
    cout<<timer.count()<<"   iterative"<<endl;

    t1 = high_resolution_clock::now();
    rost::sort(vec5.begin(), vec5.end());
    t2 = high_resolution_clock::now();
    timer = std::chrono::duration_cast<nano> (t2-t1);
    cout<<timer.count()<<"    my standard"<<endl;

    return 0;
}
