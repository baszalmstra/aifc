#include "action_buffer.h"
#include <assert.h>

const uint32_t kInvalidPosition = ~(uint32_t) 0;

//-------------------------------------------------------------------------------------------------
ActionBuffer::ActionBuffer(uint32_t initialSizeBytes) 
: writePosition_(0), readPosition_(0), 
currentWriteEventPosition_(kInvalidPosition),
nextReadEventPosition_(kInvalidPosition)
{
	buffer_.resize(initialSizeBytes);
}
//-------------------------------------------------------------------------------------------------
ActionBuffer::~ActionBuffer() { }

//-------------------------------------------------------------------------------------------------
void ActionBuffer::Write(const uint8_t* bytes, uint32_t count)
{
	// Grow the stream if required
	if (writePosition_ + count >= buffer_.size())
		Resize(writePosition_ + count);

	// Move the cursor
	uint8_t *data = reinterpret_cast<uint8_t*>(&buffer_.at(writePosition_));
	writePosition_ += count;

	// Copy over the data
	for (uint32_t i = 0; i < count; ++i)
		data[i] = bytes[i];
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::Resize(uint32_t newSize)
{
	buffer_.resize(newSize);
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::BeginWrite(AIAction action)
{
	assert(currentWriteEventPosition_ == kInvalidPosition);

	// Store the start of the event
	currentWriteEventPosition_ = writePosition_;

	// Write the event header
	SkipWrite(sizeof(uint32_t));
	WriteUShort(action);
}

//-------------------------------------------------------------------------------------------------
uint32_t ActionBuffer::EndWrite()
{
	assert(currentWriteEventPosition_ != kInvalidPosition);

	// Determine the actual size of the event
	uint32_t actualSize = writePosition_ - currentWriteEventPosition_;
	
	//Assign in stream the event size
	*reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(&buffer_.at(currentWriteEventPosition_))) = actualSize;

	// End of the event
	currentWriteEventPosition_ = kInvalidPosition;

	return actualSize;
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::SkipWrite(uint32_t count)
{
	// Grow the stream if required
	if (writePosition_ + count >= buffer_.size())
		Resize(writePosition_ + count);

	// Move the cursor
	writePosition_ += count;
}

//-------------------------------------------------------------------------------------------------
uint16_t ActionBuffer::BeginReadEvent() const
{
	assert(nextReadEventPosition_ == kInvalidPosition);

	// Read the size of the event
	uint32_t size = ReadUInt();
	uint16_t id = ReadUShort();

	// Determine next event position
	nextReadEventPosition_ = readPosition_ - sizeof(size) - sizeof(id) + size;

	return id;
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::EndReadEvent() const
{
	assert(nextReadEventPosition_ != kInvalidPosition);

	// Simply move the cursor and reset it
	readPosition_ = nextReadEventPosition_;
	nextReadEventPosition_ = kInvalidPosition;
}


//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteBool(bool value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(bool));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteByte(uint8_t value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(uint8_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteString(const std::string& value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(uint8_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteUShort(uint16_t value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(uint16_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteShort(int16_t value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(int16_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteInt(int32_t value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(int32_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteUInt(uint32_t value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(uint32_t));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteFloat(float value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(float));
}

//-------------------------------------------------------------------------------------------------
void ActionBuffer::WriteDouble(double value)
{
	Write(reinterpret_cast<const uint8_t*>(&value), sizeof(double));
}

//-------------------------------------------------------------------------------------------------
const bool& ActionBuffer::ReadBool() const
{
	return Read<bool>();
}

//-------------------------------------------------------------------------------------------------
const uint8_t& ActionBuffer::ReadByte() const
{
	return Read<uint8_t>();
}

//-------------------------------------------------------------------------------------------------
const std::string& ActionBuffer::ReadString() const
{
	return Read<std::string>();
}

//-------------------------------------------------------------------------------------------------
const uint16_t& ActionBuffer::ReadUShort() const
{
	return Read<uint16_t>();
}

//-------------------------------------------------------------------------------------------------
const int16_t& ActionBuffer::ReadShort() const
{
	return Read<int16_t>();
}

//-------------------------------------------------------------------------------------------------
const uint32_t& ActionBuffer::ReadUInt() const
{
	return Read<uint32_t>();
}

//-------------------------------------------------------------------------------------------------
const int32_t& ActionBuffer::ReadInt() const
{
	return Read<int32_t>();
}

//-------------------------------------------------------------------------------------------------
const float& ActionBuffer::ReadFloat() const
{
	return Read<float>();
}

//-------------------------------------------------------------------------------------------------
const double& ActionBuffer::ReadDouble() const
{
	return Read<double>();
}
