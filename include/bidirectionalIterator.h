#ifndef BIDIRECTIONALITERATOR_H
#define BIDIRECTIONALITERATOR_H

#include <iterator>
#include <stdint.h>
#include <memory>
#include <stdexcept>

template <typename T>
class BidirectionalIterator {
public:
        typedef BidirectionalIterator<T> self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef int difference_type;

        BidirectionalIterator<T>(const pointer start, const int64_t length) : _dataPointer(start), _dataStart(start), _dataEnd(start + (length)) {}
        BidirectionalIterator<T>(const pointer position, const pointer start, const int64_t end) : _dataPointer(position), _dataStart(start), _dataEnd(end) {}
        
        bool canMove(int64_t amount){
                if (amount == 0){
                        isValid();
                }
                else{
                        return isValid() && ((_dataPointer+amount) >= _dataStart) && ((_dataPointer+amount) < _dataEnd);
                }
        }

        bool isValid() {
                return (_dataPointer >= _dataStart) && (_dataPointer < _dataEnd);
        }

        BidirectionalIterator<T> iteratorAtStart(){
                return BidirectionalIterator<T>(_dataStart, _dataStart, _dataEnd);
        }
        BidirectionalIterator<T> iteratorAtEnd(){
                return BidirectionalIterator<T>(_dataEnd, _dataStart, _dataEnd);
        }


        BidirectionalIterator<T> operator++() {
                //if(_dataPointer >= (_dataEnd - 1) || _dataPointer < (_dataStart-1)){
                //        throw std::range_error("Attempt to move BidirectionalIterator beyond the bounds of the data that it iterates over");
                //}
                ++_dataPointer;
                return *this;
        }
        BidirectionalIterator<T> operator++(int) {
                //if(_dataPointer >=_dataEnd || _dataPointer < (_dataStart)) {
                //        throw std::range_error("Attempt to move BidirectionalIterator beyond the bounds of the data that it iterates over");
                //}
                BidirectionalIterator<T> i = *this;
                _dataPointer++;
                return i;
        }

        BidirectionalIterator<T> operator--() {
                //if(_dataPointer > _dataEnd || _dataPointer <= _dataStart) {
                //        throw std::range_error("Attempt to move BidirectionalIterator beyond the bounds of the data that it iterates over");
                //}
                --_dataPointer;
                return *this;
        }
        BidirectionalIterator<T> operator--(int) {
                //if(_dataPointer > (_dataEnd - 1) || _dataPointer < _dataStart) {
                //        throw std::range_error("Attempt to move BidirectionalIterator beyond the bounds of the data that it iterates over");
                //}
                BidirectionalIterator<T> i = *this;
                _dataPointer--;
                return i;
        }

        reference operator*() const{
                if(_dataPointer >= _dataEnd || _dataPointer < _dataStart) {
                        throw std::range_error("Attempt to access BidirectionalIterator while it points outside the bounds of the data that it iterates over");
                }
                return *_dataPointer;
        }
        pointer operator->() const{
                if(_dataPointer >= _dataEnd || _dataPointer < _dataStart) {
                        throw std::range_error("Attempt to access BidirectionalIterator while it points outside the bounds of the data that it iterates over");
                }
                return _dataPointer;
        }

        bool operator==(const BidirectionalIterator<T>& ref) const {
                return _dataPointer == ref._dataPointer;
        }
        bool operator!=(const BidirectionalIterator<T>& ref) const {
                return _dataPointer != ref._dataPointer;
        }

private:
        pointer _dataPointer;
        pointer _dataStart;
        pointer _dataEnd;
};

#endif