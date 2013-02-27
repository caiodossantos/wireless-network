/**************************************************************************//**
  \file nwkTx.h

  \brief Interface of NWK transmission.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    2007-06-14 V. Panov - Created.
    2008-12-10 Max Gekk - Reduction of the used RAM.
    2009-10-16 Max Gekk - Redesign.
   Last change:
    $Id: nwkTx.h 20614 2012-03-23 09:37:37Z arazinkov $
 ******************************************************************************/
#if !defined _NWK_TX_H
#define _NWK_TX_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwkConfig.h>
#include <nldeData.h>
#include <nwkDbg.h>

/******************************************************************************
                               Definition section
 ******************************************************************************/
/** List of transmission parameters: delay type, prepare and confirm functions.
 * NOTE: Offset of tx parameters in this list must be equal tx id. */
#define NWK_TX_PARAMETERS \
{ \
  NWK_LINK_STATUS_TX_PARAMETERS,              /* NWK_LINK_STATUS_TX_ID */      \
  NWK_BROADCAST_STATUS_TX_PARAMETERS,         /* NWK_BROADCAST_STATUS_TX_ID */ \
  NWK_UNICAST_STATUS_TX_PARAMETERS,           /* NWK_UNICAST_STATUS_TX_ID */   \
  NWK_JOIN_REQ_TX_PARAMETERS,                 /* NWK_JOIN_REQ_TX_ID */         \
  NWK_ADDR_CONFLICT_JOIN_RESP_TX_PARAMETERS,  /* NWK_ADDR_CONFLICT_JOIN_RESP_TX_ID */ \
  NWK_JOIN_RESP_TX_PARAMETERS,                /* NWK_JOIN_RESP_TX_ID */        \
  NWK_LEAVE_ITSELF_TX_PARAMETERS,             /* NWK_LEAVE_ITSELF_TX_ID */     \
  NWK_LEAVE_CHILD_TX_PARAMETERS,              /* NWK_LEAVE_CHILD_TX_ID */      \
  NWK_REPORT_TX_PARAMETERS,                   /* NWK_REPORT_TX_ID */           \
  NWK_UPDATE_TX_PARAMETERS,                   /* NWK_UPDATE_TX_ID */           \
  NWK_ROUTE_REPLY_TX_PARAMETERS,              /* NWK_ROUTE_REPLY_TX_ID */      \
  NWK_INITIAL_ROUTE_REQ_TX_PARAMETERS,        /* NWK_INITIAL_ROUTE_REQ_TX_ID */\
  NWK_INITIAL_MANYTOONE_ROUTE_REQ_TX_PARAMETERS, /* NWK_INITIAL_MANYTOONE_ROUTE_REQ_TX_ID */\
  NWK_ROUTE_REQ_TX_PARAMETERS,                /* NWK_ROUTE_REQ_TX_ID */        \
  NWK_MANYTOONE_ROUTE_REQ_TX_PARAMETERS,      /* NWK_MANYTOONE_ROUTE_REQ_TX_ID */\
  NWK_ROUTE_RECORD_TX_PARAMETERS,             /* NWK_ROUTE_RECORD_TX_ID */     \
  NWK_MANY_TO_ONE_STATUS_TX_PARAMETERS,       /* NWK_MANY_TO_ONE_STATUS_TX_ID */\
  \
  NWK_UNICAST_COMMAND_TRANSIT_TX_PARAMETERS,  /* NWK_UNICAST_COMMAND_TRANSIT_TX_ID */ \
  NWK_UNICAST_DATA_TRANSIT_TX_PARAMETERS,     /* NWK_UNICAST_DATA_TRANSIT_TX_ID */    \
  NWK_BROADCAST_TRANSIT_TX_PARAMETERS,        /* NWK_BROADCAST_TRANSIT_TX_ID */       \
  NWK_MULTICAST_MEMBER_TRANSIT_TX_PARAMETERS, /* NWK_MULTICAST_MEMBER_TRANSIT_TX_ID */\
  NWK_SOURCE_ROUTE_TRANSIT_TX_PARAMETERS,     /* NWK_SOURCE_ROUTE_TRANSIT_TX_ID */    \
  NWK_ROUTE_RECORD_TRANSIT_TX_PARAMETERS,     /* NWK_ROUTE_RECORD_TRANSIT_TX_ID */    \
  NWK_MANY_TO_ONE_TRANSIT_STATUS_TX_PARAMETERS, /* NWK_MANY_TO_ONE_TRANSIT_STATUS_TX_ID */\
  \
  NWK_UNICAST_DATA_TX_PARAMETERS,             /* NWK_UNICAST_DATA_TX_ID */     \
  NWK_BROADCAST_DATA_TX_PARAMETERS,           /* NWK_BROADCAST_DATA_TX_ID */   \
  NWK_MULTICAST_MEMBER_TX_PARAMETERS,         /* NWK_MULTICAST_MEMBER_TX_ID */ \
  NWK_SOURCE_ROUTE_TX_PARAMETERS              /* NWK_SOURCE_ROUTE_TX_ID */     \
}

/******************************************************************************
                                 Types section
 ******************************************************************************/
/** Identifiers of transmission requests. */
typedef enum _NwkTxId_t
{
  NWK_LINK_STATUS_TX_ID = 0x00,
  NWK_BROADCAST_STATUS_TX_ID = 0x01,
  NWK_UNICAST_STATUS_TX_ID = 0x02,
  NWK_JOIN_REQ_TX_ID = 0x03,
  NWK_ADDR_CONFLICT_JOIN_RESP_TX_ID = 0x04,
  NWK_JOIN_RESP_TX_ID = 0x05,
  NWK_LEAVE_ITSELF_TX_ID = 0x06,
  NWK_LEAVE_CHILD_TX_ID = 0x07,
  NWK_REPORT_TX_ID = 0x08,
  NWK_UPDATE_TX_ID = 0x09,
  NWK_ROUTE_REPLY_TX_ID = 0x0A,
  NWK_INITIAL_ROUTE_REQ_TX_ID = 0x0B,
  NWK_INITIAL_MANYTOONE_ROUTE_REQ_TX_ID = 0x0C,
  NWK_ROUTE_REQ_TX_ID = 0x0D,
  NWK_MANYTOONE_ROUTE_REQ_TX_ID = 0x0E,
  NWK_ROUTE_RECORD_TX_ID = 0x0F,
  NWK_MANY_TO_ONE_STATUS_TX_ID = 0x10,
  NWK_MAX_COMMAND_TX_ID = NWK_MANY_TO_ONE_STATUS_TX_ID,

  NWK_UNICAST_COMMAND_TRANSIT_TX_ID = 0x11,
  NWK_UNICAST_DATA_TRANSIT_TX_ID = 0x12,
  NWK_MULTICAST_NON_MEMBER_TRANSIT_TX_ID = NWK_UNICAST_DATA_TRANSIT_TX_ID,
  NWK_BROADCAST_TRANSIT_TX_ID = 0x13,
  NWK_MULTICAST_MEMBER_TRANSIT_TX_ID = 0x14,
  NWK_SOURCE_ROUTE_TRANSIT_TX_ID = 0x15,
  NWK_ROUTE_RECORD_TRANSIT_TX_ID = 0x16,
  NWK_MANY_TO_ONE_TRANSIT_STATUS_TX_ID = 0x17,

  NWK_MIN_DATA_TX_ID = 0x18,
  NWK_UNICAST_DATA_TX_ID = NWK_MIN_DATA_TX_ID,
  NWK_MULTICAST_NON_MEMBER_TX_ID = NWK_UNICAST_DATA_TX_ID,
  NWK_BROADCAST_DATA_TX_ID = 0x19,
  NWK_MULTICAST_MEMBER_TX_ID = 0x1A,
  NWK_SOURCE_ROUTE_TX_ID = 0x1B,

  NWK_MAX_TX_ID
} NwkTxId_t;

/** Type of iterator for transmission identifiers. */
typedef uint8_t NwkTxIdIter_t;

/** Type of callback function for preparing an output packet. */
typedef void (* NwkPrepareTxFunc_t)(NwkOutputPacket_t *const);
/** Type of callback function for confirmation of packet transmission. */
typedef void (* NwkConfirmTxFunc_t)(NwkOutputPacket_t *const,
  const NWK_Status_t);

/** Internal variables of transmission component. */
typedef struct _NwkTx_t
{
  /** Queue of output packets */
  QueueDescriptor_t queue;
} NwkTx_t;

/** Internal states of output packet for debug. */
typedef enum _NwkOutPktState_t
{
  NWK_OUTPKT_IN_QUEUE_STATE = 0x00,
  NWK_OUTPKT_RDISCOVERY_STATE = 0x01,
  NWK_OUTPKT_MAC_STATE = 0x02,
  NWK_OUTPKT_DELAY_STATE = 0x03,
  NWK_OUTPKT_ENCRYPT_STATE = 0x04,
  NWK_OUTPKT_DECRYPT_STATE = 0x05,
  NWK_OUTPKT_ROUTE_RECORD_STATE = 0x06
} NwkOutPktState_t;

/******************************************************************************
                   Inline static functions prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Is this packet a network data?

  \param[in] outPkt - pointer to the output network packet.
  \return 'true' if this output packet is data packet otherwise return 'false'.
 ******************************************************************************/
INLINE bool nwkIsDataPacket(const NwkOutputPacket_t *const outPkt)
{
  assert(outPkt->txId < NWK_MAX_TX_ID, NWKTX_NWKISDATAPACKET0);
  return NWK_MIN_DATA_TX_ID <= outPkt->txId;
}

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Request to transmit the output packet.

  \param[in] outPkt - pointer to the output network packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkTxReq(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Main task handler of the packet transmission component
 ******************************************************************************/
NWK_PRIVATE void nwkTxTaskHandler(void);

/**************************************************************************//**
  \brief Reset the packet transmission component.
 ******************************************************************************/
NWK_PRIVATE void nwkResetTx(void);

/**************************************************************************//**
  \brief Confirmation of packet transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] status - network status of packet transmission.

  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkTxConf(NwkOutputPacket_t *const outPkt,
  const NWK_Status_t status);

/**************************************************************************//**
  \brief Write default values to parameters of MAC_DataReq request.

  \param[in] outPkt - pointer to an output packet.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkInitMacDataReq(NwkOutputPacket_t *const outPkt);

/**************************************************************************//**
  \brief Start packet transmission.

  \param[in] outPkt - pointer to output packet.
  \param[in] encrypt - if 'true' then packet encrypting is required.
  \return None.
 ******************************************************************************/
NWK_PRIVATE void nwkTransmitOutputPacket(NwkOutputPacket_t *const outPkt,
  const bool encrypt);

#endif /* _NWK_TX_H */
/** eof nwkTx.h */
