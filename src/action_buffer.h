#pragma once

#include <cstdint>
#include <vector>
#include <assert.h>

#include "math_types.h"

enum AIAction
{
  kForce,
  kTorque,
  kFire
};

class ActionBuffer
{
public:
	ActionBuffer(uint32_t initialSizeBytes = 8 * 1024u);
	~ActionBuffer();

	ActionBuffer(const ActionBuffer& other) = delete;
	ActionBuffer(ActionBuffer&&) = delete;

	///Resize the buffer
	void Resize(uint32_t newSize);

	/// Begin the write event
	void BeginWrite(AIAction action);

	/// End the write event
	uint32_t EndWrite();

	/// Skip in the output stream by the specified number of bytes
	void SkipWrite(uint32_t count);

	/**
	* @brief Starts reading an event from the stream.
	* @returns The id of the event
	*/
	AIAction BeginReadEvent() const;

	/**
	* @brief Ends reading the current event, skipping the read position to the next event.
	*/
	void EndReadEvent() const;

	/// EOF of the stream
	bool read_eof() const;

	/// Reset read an write cursor to start of stream
	void reset();

	/** Writing in the stream **/
public:
	/// Write a bool to the output stream
	void WriteBool(bool value);

	/// Write a byte to the output stream
	void WriteByte(uint8_t value);

	/// Write an unsigned short to the output stream
	void WriteUShort(uint16_t value);

	/// Write a short to the output stream
	void WriteShort(int16_t value);

	/// Write an integer to the output stream
	void WriteInt(int32_t value);

	/// Write an unsigned integer to the output stream
	void WriteUInt(uint32_t value);

	/// Write a float to the output stream
	void WriteFloat(float value);

	/// Write a double to the output stream
	void WriteDouble(double value);

  /// Writes a 2d vector
  void WriteVec2(const Vec2f& vec);

	/** Reading in the stream **/
public:

	/// Read a bool from the stream
	const bool& ReadBool() const;

	/// Read a byte from the stream
	const uint8_t& ReadByte() const;
	
	/// Read a unsigned short from the stream
	const uint16_t& ReadUShort() const;

	/// Read a short from the string
	const int16_t& ReadShort() const;

	/// Read an usigned integer from the stream
	const uint32_t& ReadUInt() const;

	/// Read an integer from the stream
	const int32_t& ReadInt() const;

	/// Read a float from the stream
	const float& ReadFloat() const;

	/// Read a double from the stream
	const double& ReadDouble() const;

  /// Reads a vec2f 
  const Vec2f& ReadVec2f() const;

protected:
	/// Write to the output stream
	void Write(const uint8_t *bytes, uint32_t count);

	template<typename ReadType>
	const ReadType& Read() const
	{                                                           
		assert(readPosition_ + sizeof(ReadType) <= writePosition_);
		const uint32_t pos = readPosition_;                       
		readPosition_ += sizeof(ReadType);
		return *reinterpret_cast<const ReadType*>(&buffer_.at(pos));
	}

private:
	mutable uint32_t readPosition_;
	uint32_t writePosition_;

	uint32_t currentWriteEventPosition_;
	mutable uint32_t nextReadEventPosition_;

	std::vector<uint8_t> buffer_;
};


//-------------------------------------------------------------------------------------------------
inline bool ActionBuffer::read_eof() const
{
	return readPosition_ == writePosition_;
}

//-------------------------------------------------------------------------------------------------
inline void ActionBuffer::reset()
{
	writePosition_ = readPosition_ = 0;
}