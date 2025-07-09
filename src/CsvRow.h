// Copyright 2025 Jakub Nowak

#ifndef CSVROW_H
#define CSVROW_H

#include <string>

template<typename... Types>
class CsvRow {
 private:
   std::tuple<Types...> data;

   template <std::size_t Index>
   void setValue(const std::string &s);

   template <typename T>
   T convert(const std::string &s);

   template <std::size_t I = 0>
   void setValueRuntime(std::size_t index, const std::string &value);
 public:
   CsvRow(std::string line, char delimiter);

   template <std::size_t I>
   decltype(auto) get() const;
};


#include "CsvRow.tpp"

#endif // CSVROW_H

