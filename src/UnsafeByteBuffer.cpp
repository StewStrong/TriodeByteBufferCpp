#include "UnsafeByteBuffer.hpp"

#ifdef BB_USE_NS
namespace bb {
#endif

/**
 * UnsafeByteBuffer constructor
 * Consume an entire uint8_t array of length len in the UnsafeByteBuffer
 *
 * @param arr uint8_t array of data (should be of length len)
 * @param size Size of space to allocate
 */
UnsafeByteBuffer::UnsafeByteBuffer(uint8_t* arr, uint32_t size) : buf(arr), size_internal(size), rpos(0), wpos(0) {
#ifdef BB_UTILITY
	name = "";
#endif
}

/**
 * Bytes Remaining
 * Returns the number of bytes from the current read position till the end of the buffer
 *
 * @return Number of bytes from rpos to the end (size())
 */
uint32_t UnsafeByteBuffer::bytesRemaining() const {
	return size() - rpos;
}

/**
 * Size
 * Returns the size of the internal buffer...not necessarily the length of bytes used as data!
 *
 * @return size of the internal buffer
 */
uint32_t UnsafeByteBuffer::size() const {
	return size_internal;
}

// Replacement

/**
 * Replace
 * Replace occurance of a particular uint8_t, key, with the uint8_t rep
 *
 * @param key uint8_t to find for replacement
 * @param rep uint8_t to replace the found key with
 * @param start Index to start from. By default, start is 0
 * @param firstOccuranceOnly If true, only replace the first occurance of the key. If false, replace all occurances. False by default
 */
void UnsafeByteBuffer::replace(uint8_t key, uint8_t rep, uint32_t start, bool firstOccuranceOnly) {
	uint32_t len = size();
	for (uint32_t i = start; i < len; i++) {
		uint8_t data = read<uint8_t>(i);
		// Wasn't actually found, bounds of buffer were exceeded
		if ((key != 0) && (data == 0))
			break;

		// Key was found in array, perform replacement
		if (data == key) {
			buf[i] = rep;
			if (firstOccuranceOnly)
				return;
		}
	}
}

// Read Functions

uint8_t UnsafeByteBuffer::peek() const {
	return read<uint8_t>(rpos);
}

uint8_t UnsafeByteBuffer::get() const {
	return read<uint8_t>();
}

uint8_t UnsafeByteBuffer::get(uint32_t index) const {
	return read<uint8_t>(index);
}

void UnsafeByteBuffer::getBytes(uint8_t* dest, uint32_t len) const {
	for (uint32_t i = 0; i < len; i++) {
        dest[i] = read<uint8_t>();
	}
}

char UnsafeByteBuffer::getChar() const {
	return read<char>();
}

char UnsafeByteBuffer::getChar(uint32_t index) const {
	return read<char>(index);
}

double UnsafeByteBuffer::getDouble() const {
	return read<double>();
}

double UnsafeByteBuffer::getDouble(uint32_t index) const {
	return read<double>(index);
}

float UnsafeByteBuffer::getFloat() const {
	return read<float>();
}

float UnsafeByteBuffer::getFloat(uint32_t index) const {
	return read<float>(index);
}

uint32_t UnsafeByteBuffer::getInt() const {
	return read<uint32_t>();
}

uint32_t UnsafeByteBuffer::getInt(uint32_t index) const {
	return read<uint32_t>(index);
}

uint64_t UnsafeByteBuffer::getLong() const {
	return read<uint64_t>();
}

uint64_t UnsafeByteBuffer::getLong(uint32_t index) const {
	return read<uint64_t>(index);
}

uint16_t UnsafeByteBuffer::getShort() const {
	return read<uint16_t>();
}

uint16_t UnsafeByteBuffer::getShort(uint32_t index) const {
	return read<uint16_t>(index);
}

// Write Functions

void UnsafeByteBuffer::put(UnsafeByteBuffer* src) {
	uint32_t len = src->size();
	for (uint32_t i = 0; i < len; i++)
		append<uint8_t>(src->get(i));
}

void UnsafeByteBuffer::put(uint8_t b) {
	append<uint8_t>(b);
}

void UnsafeByteBuffer::put(uint8_t b, uint32_t index) {
	insert<uint8_t>(b, index);
}

void UnsafeByteBuffer::putBytes(uint8_t* b, uint32_t len) {
	// Insert the data one byte at a time into the internal buffer at position i+starting index
	for (uint32_t i = 0; i < len; i++)
		append<uint8_t>(b[i]);
}

void UnsafeByteBuffer::putBytes(uint8_t* b, uint32_t len, uint32_t index) {
	wpos = index;

	// Insert the data one byte at a time into the internal buffer at position i+starting index
	for (uint32_t i = 0; i < len; i++)
		append<uint8_t>(b[i]);
}

void UnsafeByteBuffer::putChar(char value) {
	append<char>(value);
}

void UnsafeByteBuffer::putChar(char value, uint32_t index) {
	insert<char>(value, index);
}

void UnsafeByteBuffer::putDouble(double value) {
	append<double>(value);
}

void UnsafeByteBuffer::putDouble(double value, uint32_t index) {
	insert<double>(value, index);
}
void UnsafeByteBuffer::putFloat(float value) {
	append<float>(value);
}

void UnsafeByteBuffer::putFloat(float value, uint32_t index) {
	insert<float>(value, index);
}

void UnsafeByteBuffer::putInt(uint32_t value) {
	append<uint32_t>(value);
}

void UnsafeByteBuffer::putInt(uint32_t value, uint32_t index) {
	insert<uint32_t>(value, index);
}

void UnsafeByteBuffer::putLong(uint64_t value) {
	append<uint64_t>(value);
}

void UnsafeByteBuffer::putLong(uint64_t value, uint32_t index) {
	insert<uint64_t>(value, index);
}

void UnsafeByteBuffer::putShort(uint16_t value) {
	append<uint16_t>(value);
}

void UnsafeByteBuffer::putShort(uint16_t value, uint32_t index) {
	insert<uint16_t>(value, index);
}

// Utility Functions
#ifdef BB_UTILITY
void UnsafeByteBuffer::setName(std::string n) {
	name = n;
}

std::string UnsafeByteBuffer::getName() {
	return name;
}

void UnsafeByteBuffer::printInfo() {
	uint32_t length = size();
	std::cout << "UnsafeByteBuffer " << name.c_str() << " Length: " << length << ". Info Print" << std::endl;
}

void UnsafeByteBuffer::printAH() {
	uint32_t length = size();
	std::cout << "UnsafeByteBuffer " << name.c_str() << " Length: " << length << ". ASCII & Hex Print" << std::endl;

	for (uint32_t i = 0; i < length; i++) {
		std::printf("0x%02x ", buf[i]);
	}

	std::printf("\n");
	for (uint32_t i = 0; i < length; i++) {
		std::printf("%c ", buf[i]);
	}

	std::printf("\n");
}

void UnsafeByteBuffer::printAscii() {
	uint32_t length = size();
	std::cout << "UnsafeByteBuffer " << name.c_str() << " Length: " << length << ". ASCII Print" << std::endl;

	for (uint32_t i = 0; i < length; i++) {
		std::printf("%c ", buf[i]);
	}

	std::printf("\n");
}

void UnsafeByteBuffer::printHex() {
	uint32_t length = size();
	std::cout << "UnsafeByteBuffer " << name.c_str() << " Length: " << length << ". Hex Print" << std::endl;

	for (uint32_t i = 0; i < length; i++) {
		std::printf("0x%02x ", buf[i]);
	}

	std::printf("\n");
}

void UnsafeByteBuffer::printPosition() {
	uint32_t length = size();
	std::cout << "UnsafeByteBuffer " << name.c_str() << " Length: " << length << " Read Pos: " << rpos << ". Write Pos: "
	        << wpos << std::endl;
}

#ifdef BB_USE_NS
}
#endif

#endif
