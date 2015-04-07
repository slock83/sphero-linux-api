Sync packet structure :
SOP1
SOP2
MRSP
SEQ
DLEN
<Data>
CHK

SOP1 :	
	FF
	
SOP2 :	
	FF
	
MRSP
	Contain error codes from the virtual device
	
SEQ
	00 si async
	SEQ from the original packet (If original packet needing aknowledgement had SEQ = 01 then this paxket SEQ is 01)
	
DLEN
	size of the datas (in bytes)
	
<Data>
	Optional datas
	
CHK
	Checksum
	
Async packet structure :
SOP1
SOP2
IDCODE
DLEN MSB
DLEN LSB
<Data>
CHK

SOP1:
	FF
	
SOP2:
	FE
	
IDCODE
  Depend on the async message type (more explaination after)

DLEN MSB & LSB
	size of data on 2 bytes

<Data>
	Datas of the message (more explaination after)
	
CHK
	Checksum
	
Datas from async messages :
IDCODE :
	01 Power notification
		length : 2 bytes
		datas : state
	02 Level 1 Diagnostic response
		datas : lots of informations in ASCII characters (more than 1k chars)
	03 Sensor data streaming
		datas : return the values asked by the command : Set Data Streaming
		returned value depend on the data source asked
	04 Config block contents
		data : the value of the requested configuration block from Get Configuration Block
	05 Pre-sleep warning
		no data, the sphero will got to sleep 10 seconds after this packet is sent
	06 Macro markers
		Depends on certains macros
	07 Collision detected
	08 orbBasic PRINT
	09 orbBasic error (ascii mode)
	0a orbBasic error (bin mode)
	0b self level result
		Sent only after a self level routine is completed
	0c Gyro axis limit exceeded
	
