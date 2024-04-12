#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "qsort.h"


void merge(const std::string& file_name, const std::string& tmp_file_name1, const std::string& tmp_file_name2, int size, int series_step);


void multiphase_sort(const std::string& file_name, int size, int series_step = 1) {
    if (series_step > size) {
        remove("file.txt");
        rename("tmp.txt", "file.txt");
        return;
    }

    const std::string tmp_file_name1 = "tmp_file1.txt";
    const std::string tmp_file_name2 = "tmp_file2.txt";
    std::ifstream file(file_name);
    std::ofstream tmp_file1(tmp_file_name1);
    std::ofstream tmp_file2(tmp_file_name2);
    bool change_series = false;
    int number;

    for (int i = 0; file >> number; i++) {
        (change_series ? tmp_file1 : tmp_file2) << number << std::endl;
        if (i % series_step == 0) {
            change_series = !change_series;
        }
    }

    file.close();
    tmp_file1.close();
    tmp_file2.close();
    merge(file_name, tmp_file_name1, tmp_file_name2, size, series_step);
}


void merge(const std::string& file_name, const std::string& tmp_file_name1, const std::string& tmp_file_name2, int size, int series_step) {
    std::ofstream file("tmp.txt");
    std::ifstream tmp_file1(tmp_file_name1);
    std::ifstream tmp_file2(tmp_file_name2);
    int number1, number2;
    bool flag_of_tmp_file1 = bool(tmp_file1 >> number1);
    bool flag_of_tmp_file2 = bool(tmp_file2 >> number2);
    int help_index_for_loop = 0, help_index_for_arr_size;
    
    while (help_index_for_loop < size) {
        std::ofstream series_out("series.txt");
        help_index_for_arr_size = 0;
        
        for (int i = 0; i < series_step && flag_of_tmp_file1; i++) {
            series_out << number1 << std::endl;
            help_index_for_arr_size++;
            flag_of_tmp_file1 = bool(tmp_file1 >> number1);
        }
        for (int i = 0; i < series_step && flag_of_tmp_file2; i++) {
            series_out << number2 << std::endl;
            help_index_for_arr_size++;
            flag_of_tmp_file2 = bool(tmp_file2 >> number2);
        }
        
        series_out.close();
        std::ifstream series_in("series.txt");
        
        int* one_series = new int[help_index_for_arr_size];
        for (int i = 0; i < help_index_for_arr_size; i++) {
            series_in >> number1;
            one_series[i] = number1;
        }
        series_in.close();

        qsort(one_series, 0, help_index_for_arr_size- 1);

        for (int i = 0; i < help_index_for_arr_size; i++) {
            file << one_series[i] << std::endl;
            help_index_for_loop++;
        }

        delete[] one_series;
    }

    file.close();  
    
    tmp_file1.close();
    tmp_file2.close();
    remove("tmp_file1.txt");
    remove("tmp_file2.txt");
    remove("series.txt");

    multiphase_sort(file_name, size, series_step * 2);
}   


