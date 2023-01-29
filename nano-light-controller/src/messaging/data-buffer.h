#ifndef _DATA_BUFFER_H_
#define _DATA_BUFFER_H_

class DataBuffer {
public:
    inline DataBuffer(int size) {
        _size = max(size, 4);
        _buffer = new byte[size];

        reset();
    }

    inline virtual ~DataBuffer() {
        delete[] _buffer;
    }

    inline void reset() {
        memset(_buffer, 0, _size);
        _pos = 0;
        _writePos = 0;
    }

    inline void write(byte data) {
        if (_writePos >= _size) {
            return;
        }
        _buffer[_writePos++] = data;
    }

    inline byte readByte() {
        if (_pos >= _size) {
            return 0;
        }

        byte data = _buffer[_pos];
        ++_pos;
        return data;
    }

    inline int readInt() {
        if (_pos + 4 > _size) {
            return 0;
        }

        //int32_t* pData = reinterpret_cast<int32_t*>(_buffer + _pos);

        int data = _buffer[_pos + 0] << 24 |
                   _buffer[_pos + 1] << 16 | 
                   _buffer[_pos + 2] << 8 |
                   _buffer[_pos + 3];

        _pos += 4;
        return data;
    }

    inline int availableData() const {
        return _writePos;
    }

    inline void seek(int pos) {
        if (pos >= _writePos || pos < 0) {
            _pos = 0;
        } else {
            _pos = pos;
        }
    }

private:
    byte* _buffer;
    int _size;
    int _pos;
    int _writePos;
};

#endif