// Copyright 2025 Jakub Nowak

#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <fstream>
#include <vector>
#include "CsvRow.h"

template<typename... Types>
class CsvReader {
 private:
    std::string filename;
    std::ifstream fileStream;
    bool hasHeader;
    std::vector<CsvRow<Types...>> rows;  
    char delimeter;
 public: 
    CsvReader(const std::string& filename, bool hasHeader = true, char delimeter = ',');
    const CsvRow<Types...>& operator[](std::size_t index) const;
    int rowCount() const;
};


#include "CsvReader.tpp"


#endif // CSVREADER_H 