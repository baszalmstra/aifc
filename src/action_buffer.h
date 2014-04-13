#pragma once
#include <cstdint>
#include <vector>
#include <assert.h>
#include "ai_command.h"

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
	void BeginWrite(AICommandAction action);

	/// End the write event
	uint32_t EndWrite();

	/// Skip in the output stream by the specified number of bytes
	void SkipWrite(uint32_t count);

	/**
	* @brief Starts reading an event from the stream.
	* @returns The id of the event
	*/
	uint16_t BeginReadEvent();

	/**
	* @brief Ends reading the current event, skipping the read position to the next event.
	*/
	void EndReadEvent();

	/// EOF of the stream
	bool read_eof() const;


	/** Writing in the stream **/
public:
	/// Write a bool to the output stream
	void WriteBool(bool value);

	/// Write a byte to the output stream
	void WriteByte(uint8_t value);

	/// Write a string to the output stream
	void WriteString(const std::string& value);

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

	/** Reading in the stream **/
public:

	/// Read a bool from the stream
	const bool& ReadBool();

	/// Read a byte from the stream
	const uint8_t& ReadByte();

	/// Read a string from the stream
	const std::string& ReadString();
	
	/// Read a unsigned short from the stream
	const uint16_t& ReadUShort();

	/// Read a short from the string
	const int16_t& ReadShort();

	/// Read an usigned integer from the stream
	const uint32_t& ReadUInt();

	/// Read an integer from the stream
	const int32_t& ReadInt();

	/// Read a float from the stream
	const float& ReadFloat();

	/// Read a double from the stream
	const double& ReadDouble();

protected:
	/// Write to the output stream
	void Write(const uint8_t *bytes, uint32_t count);

	template<typename ReadType>
	const ReadType& Read()
	{                                                           
		assert(readPosition_ + sizeof(ReadType) <= writePosition_);
		const uint32_t pos = readPosition_;                       
		readPosition_ += sizeof(ReadType);
		return *reinterpret_cast<const ReadType*>(reinterpret_cast<const uint8_t*>(buffer_.at(pos)));
	}

private:
	uint32_t readPosition_;
	uint32_t writePosition_;

	uint32_t currentWriteEventPosition_;
	uint32_t nextReadEventPosition_;

	std::vector<uint8_t> buffer_;
};


//-------------------------------------------------------------------------------------------------
inline bool ActionBuffer::read_eof() const
{
	return readPosition_ == writePosition_;
}