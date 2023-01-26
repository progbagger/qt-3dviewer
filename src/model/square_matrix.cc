#include "square_matrix.h"

namespace model {

SquareMatrix::SquareMatrix(SizeType size)
    : size_(size), data_(size_ * size_, 0.0) {}

SquareMatrix::SizeType SquareMatrix::GetSize() const { return size_; }

const SquareMatrix::ValueType* SquareMatrix::GetRawData() const {
  return data_.data();
}

SquareMatrix::ValueType& SquareMatrix::operator()(SizeType row,
                                                  SizeType column) {
  if (row >= GetSize() || column >= GetSize()) throw std::exception();
  return data_[row * GetSize() + column];
}

const SquareMatrix::ValueType& SquareMatrix::operator()(SizeType row,
                                                        SizeType column) const {
  if (row >= GetSize() || column >= GetSize()) throw std::exception();
  return data_[row * GetSize() + column];
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix& other) const {
  if (GetSize() != other.GetSize()) throw std::exception();
  SquareMatrix result(GetSize());
  for (SizeType row = 0; row < GetSize(); ++row) {
    for (SizeType column = 0; column < GetSize(); ++column) {
      ValueType result_element = 0.0;
      for (SizeType current_element = 0; current_element < GetSize();
           ++current_element) {
        result_element +=
            (*this)(row, current_element) * other(current_element, column);
      }
      result(row, column) = result_element;
    }
  }
  return result;
}

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix& other) {
  *this = std::move(*this * other);
  return *this;
}

}  // namespace model
