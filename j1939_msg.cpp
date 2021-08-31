#include "j1939_msg.h"

union J1939_MESSAGE_UNION
{
/** j1939 �� ID ��ɽṹ��
*
*/
    struct   j1939_PID
    {
        unsigned char	  DataPage			: 1;  /**< ����ҳ*/
        unsigned char	  Res				: 1;  /**< Resλ*/
        unsigned char	  Priority			: 3;  /**< ���ȼ�*/
        unsigned char	  Reserve			: 3;  /**< ����*/
        unsigned char	  PDUFormat;			      /**< PF*/
        unsigned char	  PDUSpecific; 			      /**< PS*/
        unsigned char	  SourceAddress;                      /**< SA*/
        unsigned char	  DataLength 			: 4;  /**< ���ݳ���*/
        unsigned char	  RTR			        : 4;  /**< RTRλ*/
        unsigned char	  Data[J1939_DATA_LENGTH];            /**< ����*/
        unsigned int      PGN			        :24;  /**< ����Ⱥ���*/
        unsigned int      ReservePGN			: 8;  /**< ����*/
    };
    struct j1939_PID Mxe;                                 /**< j1939 �� ID ��ɽṹ��*/
    unsigned char		Array[J1939_MSG_LENGTH + J1939_DATA_LENGTH]; /**< ���������飬������ٴ���ṹ�帳ֵ*/
};

typedef union J1939_MESSAGE_UNION J1939_MESSAGE;

J1939_MSG::J1939_MSG()
{

}
