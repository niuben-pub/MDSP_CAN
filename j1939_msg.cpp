#include "j1939_msg.h"

union J1939_MESSAGE_UNION
{
/** j1939 的 ID 组成结构体
*
*/
    struct   j1939_PID
    {
        unsigned char	  DataPage			: 1;  /**< 数据页*/
        unsigned char	  Res				: 1;  /**< Res位*/
        unsigned char	  Priority			: 3;  /**< 优先级*/
        unsigned char	  Reserve			: 3;  /**< 空闲*/
        unsigned char	  PDUFormat;			      /**< PF*/
        unsigned char	  PDUSpecific; 			      /**< PS*/
        unsigned char	  SourceAddress;                      /**< SA*/
        unsigned char	  DataLength 			: 4;  /**< 数据长度*/
        unsigned char	  RTR			        : 4;  /**< RTR位*/
        unsigned char	  Data[J1939_DATA_LENGTH];            /**< 数据*/
        unsigned int      PGN			        :24;  /**< 参数群编号*/
        unsigned int      ReservePGN			: 8;  /**< 空闲*/
    };
    struct j1939_PID Mxe;                                 /**< j1939 的 ID 组成结构体*/
    unsigned char		Array[J1939_MSG_LENGTH + J1939_DATA_LENGTH]; /**< 联合体数组，方便快速处理结构体赋值*/
};

typedef union J1939_MESSAGE_UNION J1939_MESSAGE;

J1939_MSG::J1939_MSG()
{

}
