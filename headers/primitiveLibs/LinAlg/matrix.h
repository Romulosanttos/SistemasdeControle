#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <iostream> 

#include "identifiers.h"

using namespace Identifiers;

namespace LinAlg {
    template<typename Type>
    class Matrix
    {
        public:
            Matrix (Type Number);
            Matrix (const char* Mat);
            Matrix (std::string Mat);
            Matrix (unsigned row, unsigned column);
            Matrix (): rows(0), columns(0), mat(NULL){}
            Matrix (const LinAlg::Matrix<Type>& otherMatrix);
            virtual ~Matrix ();

            unsigned getNumberOfRows () const;//OK
            unsigned getNumberOfColumns () const;//OK

            LinAlg::Matrix<Type> GetRow (unsigned number_of_the_row);//OK
            LinAlg::Matrix<Type> GetColumn (unsigned number_of_the_column);//OK

            void SwapRows (unsigned row_to_be_swapped, unsigned  row_to_take_place);
            void SwapColumns (unsigned column_to_be_swapped, unsigned column_to_take_place);

            unsigned Size ();

            bool isNull ();
            bool isSquare ();

            Type& operator() (unsigned row, unsigned column);
            Type  operator() (unsigned  row, unsigned column) const;

            LinAlg::Matrix<Type> operator() (unsigned* row_interval, unsigned column) const;
            LinAlg::Matrix<Type> operator() (unsigned  row, unsigned* column_interval) const;
            LinAlg::Matrix<Type> operator() (unsigned* row_interval, unsigned* column_interval) const;

            void operator= (const char* rhs);
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<Type>& otherMatrix);
            template<typename OtherMatrixType>
            LinAlg::Matrix<Type>& operator= (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);

            LinAlg::Matrix<Type>& operator+= (const Type& rhs /*scalar*/);//ok
            template<typename RightType>
            LinAlg::Matrix<Type>& operator+= (const LinAlg::Matrix<RightType>& rhs);//ok

            LinAlg::Matrix<Type>& operator-= (const Type& rhs /*scalar*/);//ok
            template<typename RightType>
            LinAlg::Matrix<Type>& operator-= (const LinAlg::Matrix<RightType>& rhs);//ok

            LinAlg::Matrix<Type>& operator*= (const Type& rhs /*scalar*/);//DEFEITO
            template<typename RightType>
            LinAlg::Matrix<Type>& operator*= (const LinAlg::Matrix<RightType>& rhs);


            LinAlg::Matrix<Type>& operator/= (const Type& rhs /*scalar*/);//dependente de *=
            template<typename RightType>
            LinAlg::Matrix<Type>& operator/= (const LinAlg::Matrix<RightType>& rhs);//dependente de *=

            LinAlg::Matrix<Type>& operator^= (double exp);//dependente de *=

            template<typename RightType>
            LinAlg::Matrix<Type> operator| (LinAlg::Matrix<RightType> rhs);//ok
            template<typename RightType>
            LinAlg::Matrix<Type> operator| (RightType rhs);
            template<typename RightType>
            LinAlg::Matrix<Type> operator|| (LinAlg::Matrix<RightType> rhs);//ok

            template<typename OtherMatrixType>
            void swap (const LinAlg::Matrix<OtherMatrixType>& otherMatrix);//falta

            //Should be declared as friend.
            template<typename OtherMatrixType>
            friend void swap (LinAlg::Matrix<Type>& lhs, LinAlg::Matrix<OtherMatrixType>& rhs) {lhs.swap(rhs);};//falta

        private:
            void Init (std::string Mat);
            void Init (unsigned row, unsigned column);

            void ReInit (unsigned row, unsigned column);

            void Add (unsigned row, unsigned column, Type number);

            template<typename OtherMatrixType>
            bool CheckDimensions(const LinAlg::Matrix<OtherMatrixType>& rhs, unsigned operation);//ok

            unsigned rows, columns;
            Type** mat;
    };

    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator+ (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs += rhs;}//OK
    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator+ (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return rhs += lhs;}//OK
    template<typename LeftType, typename RightType>
    LinAlg::Matrix<LeftType> operator+ (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs += rhs;}//OK

    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator- (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs -= rhs;}//OK
    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator- (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return -rhs -= -lhs;}//OK
    template<typename LeftType, typename RightType>
    LinAlg::Matrix<LeftType> operator- (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs -= rhs;}//OK

    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator* (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs *= rhs;}//OK
    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator* (const ScalarType& lhs, LinAlg::Matrix<MatrixType> rhs) {return rhs *= lhs;}//OK
    template<typename LeftType, typename RightType>
    LinAlg::Matrix<LeftType> operator* (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs *= rhs;}//OK

    template<typename MatrixType, typename ScalarType>
    LinAlg::Matrix<MatrixType> operator/ (LinAlg::Matrix<MatrixType> lhs, const ScalarType& rhs) {return lhs /= rhs;}//OK
    template<typename LeftType, typename RightType>
    LinAlg::Matrix<LeftType> operator/ (LinAlg::Matrix<LeftType> lhs, const LinAlg::Matrix<RightType>& rhs) {return lhs /= rhs;}//OK

    template<typename Type>
    LinAlg::Matrix<Type> operator- (const LinAlg::Matrix<Type>& mat);//OK

    template<typename Type>
    LinAlg::Matrix<Type> operator~ (LinAlg::Matrix<Type> mat);//OK

    template<typename Type>
    LinAlg::Matrix<Type> operator^ (LinAlg::Matrix<Type> lhs, int exp) {return lhs ^= exp;}//ok

    template<typename Type>
    std::ostream& operator<< (std::ostream& output, const LinAlg::Matrix<Type>& mat);//ok
    template<typename Type>
    std::istream& operator>> (std::istream& input, LinAlg::Matrix<Type>& mat);//ok

    template<typename Type>
    std::string& operator<< (std::string& output, const LinAlg::Matrix<Type>& mat);//ok

    template<typename Type>
    bool operator== (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs);//ok
    template<typename Type>
    bool operator!= (const LinAlg::Matrix<Type>& lhs, const LinAlg::Matrix<Type>& rhs) {return !(lhs == rhs);}//ok

    template<typename Type>
    void Zeros (LinAlg::Matrix<Type>& Mat);

    template<typename Type>
    LinAlg::Matrix<Type> Zeros (unsigned rows, unsigned columns);//ok

    template<typename Type>
    LinAlg::Matrix<Type> Eye (unsigned dimension);//ok

    template<typename Type>
    LinAlg::Matrix<Type> LineVector (unsigned from, unsigned to, unsigned step = 1);

    template<typename Type>
    void Ones (LinAlg::Matrix<Type> & mat);//ok

    template<typename Type>
    LinAlg::Matrix<Type> Ones (unsigned rows, unsigned columns);//ok

    template<typename Type>
    Type Determinant (const LinAlg::Matrix<Type>& mat);//ok

    template<typename Type>
    LinAlg::Matrix<Type> Cofactor(const LinAlg::Matrix<Type>& mat);//ok

    template<typename Type>
    LinAlg::Matrix<Type> Inverse(const LinAlg::Matrix<Type>& mat);//ok

    template<typename Type>
    void Print (const LinAlg::Matrix<Type>& mat);//ok
}

#include "SistemasdeControle/src/primitiveLibs/LinAlg/matrix.hpp"

#endif // MATRIX_H
