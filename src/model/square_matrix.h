#ifndef MODEL_SQUARE_MATRIX_H_
#define MODEL_SQUARE_MATRIX_H_

#include <exception>
#include <vector>

namespace model {

class SquareMatrix {
 public:
  using ValueType = float;
  using SizeType = std::size_t;
  using MatrixType = std::vector<ValueType>;

  SquareMatrix() = delete;
  explicit SquareMatrix(SizeType size);

  SizeType GetSize() const;

  const ValueType* GetRawData() const;

  ValueType& operator()(SizeType row, SizeType column);
  const ValueType& operator()(SizeType row, SizeType column) const;

  SquareMatrix operator*(const SquareMatrix& other) const;
  SquareMatrix& operator*=(const SquareMatrix& other);

 private:
  SizeType size_;
  MatrixType data_;
};

}  // namespace model

#endif  // MODEL_SQUARE_MATRIX_H_
