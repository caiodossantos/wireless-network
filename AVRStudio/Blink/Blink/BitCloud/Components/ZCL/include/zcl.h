/************************************************************************//**
  \file zcl.h

  \brief
    The header file describes the public ZCL interface

    The file describes the public interface and types of ZCL

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    01.12.08 I. Fedina & A. Potashov - Created.
******************************************************************************/

#ifndef _ZCL_H
#define _ZCL_H

/******************************************************************************
                           Includes section
******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <aps.h>
#include <csDefaults.h>
#include <dbg.h>

/******************************************************************************
                           Definitions section
******************************************************************************/
#define PROFILE_ID_SMART_ENERGY  CCPU_TO_LE16(0x0109)
#define PROFILE_ID_CBA CCPU_TO_LE16(0x0105)
#define PROFILE_ID_HOME_AUTOMATION CCPU_TO_LE16(0x0104)
#define PROFILE_ID_LIGHT_LINK CCPU_TO_LE16(0xc05e)

// Macros defines the maximum size allocated for a value of type OCTET_STRING
#define OCTET_STRING_MAX_SIZE 255
/******************************************************************************
                           Types section
******************************************************************************/
typedef uint8_t  ZCL_ClusterType_t;
typedef uint16_t ZCL_AttributeId_t; //!< Describes type of attributes IDs
typedef uint8_t  ZCL_CommandId_t;
typedef uint32_t ZCL_UTCTime_t;
typedef uint32_t ZCL_Date_t;
typedef uint16_t ZCL_ReportTime_t; // time for reporting in seconds

/***************************************************************************//**
\brief Enumerated status values used in the ZCL
*******************************************************************************/
typedef enum
{
  //! Operation was successful.
  ZCL_SUCCESS_STATUS                      = 0x00,
  //!Operation was not successful
  ZCL_FAILURE_STATUS                      = 0x01,

  //0x02 - 0x7d - Reserved
  ZCL_INVALID_ATTRIBUTE_VALUE_STATUS      = 0x02,
  ZCL_TC_PERMISSION_TABLE_ERROR_STATUS    = 0x03,
  ZCL_APS_LINK_KEY_ERROR_STATUS           = 0x04,
  /*!Not all attributes were successfully written during write attribute request.*/
  ZCL_WRITE_ATTRIBUTES_FAILURE_STATUS     = 0x0f,

  //!The sender of the command does not have authorization to carry out this command.
  ZCL_NOT_AUTHORIZED_STATUS               = 0x7e,
  //!A reserved field/subfield/bit contains a nonzero value
  ZCL_RESERVED_FIELD_NOT_ZERO_STATUS      = 0x7f,
  /*!The command appears to contain the wrong fields, as detected either by the
  presence of one or more invalid field entries or by there being missing fields.
  Command not carried out. Implementer has discretion as to whether to return
  this error or ZCL_INVALID_FIELD_STATUS.*/
  ZCL_MALFORMED_COMMAND_STATUS            = 0x80,
  /*!The specified cluster command is not supported on the device.Command not
  carried out.*/
  ZCL_UNSUP_CLUSTER_COMMAND_STATUS        = 0x81,
  /*!The specified general ZCL command is not supported on the device.*/
  ZCL_UNSUP_GENERAL_COMMAND_STATUS        = 0x82,
  /*!A manufacturer specific unicast, cluster specific command was received
  with an unknown manufacturer code, or the manufacturer code was recognized but
  the command is not supported*/
  ZCL_UNSUP_MANUF_CLUSTER_COMMAND         = 0x83,
  /*!A manufacturer specific unicast, ZCL specific command was received with an
  unknown manufacturer code, or manufacturer code was recognized but the command
  is not supported*/
  ZCL_UNSUP_MANUF_GENERAL_COMMAND_STATUS  = 0x84,
  /*!At least one field of the command contains an incorrect value, according
  to the specification the device is implemented to.*/
  ZCL_INVALID_FIELD_STATUS                = 0x85,
  /*!The specified attribute does not exist on the device.*/
  ZCL_UNSUPPORTED_ATTRIBUTE_STATUS        = 0x86,
  /*!Out of range error, or set to a reserved value. Attribute keeps its old
  value.*/
  ZCL_INVALID_VALUE_STATUS                = 0x87,
  /*!Attempt to write a read only attribute.*/
  ZCL_READ_ONLY_STATUS                    = 0x88,
  /*!An operation (e.g. an attempt to create an entry in a table) failed due
  to an insufficient amount of free space available.*/
  ZCL_INSUFFICIENT_SPACE_STATUS           = 0x89,
  /*!An attempt to create an entry in a table failed due to a duplicate entry
  already being present in the table.*/
  ZCL_DUPLICATE_EXISTS_STATUS             = 0x8a,
  /*!The requested information (e.g. table entry) could not be found.*/
  ZCL_NOT_FOUND_STATUS                    = 0x8b,
  /*!Periodic reports cannot be issued for this attribute.*/
  ZCL_UNREPORTABLE_ATTRIBUTE_STATUS       = 0x8c,
  /*!The data type given for an attribute is incorrect. Command not carried out.*/
  ZCL_INVALID_DATA_TYPE_STATUS            = 0x8d,
  /*!The selector for an attribute is incorrect.*/
  ZCL_INVALID_SELECTOR_STATUS             = 0x8e,
  /*!A request has been made to read an attribute that the requester is not
  authorized to read. No action taken.*/
  ZCL_WRITE_ONLY_STATUS                   = 0x8f,
  /*!Setting the requested values would put the device in an inconsistent state
  on startup. No action taken.*/
  ZCL_INCONSISTENT_STARTUP_STATE_STATUS   = 0x90,
  /*!An attempt has been made to write an attribute that is present but is
  defined using an out-of-band method and not over the air.*/
  ZCL_DEFINED_OUT_OF_BAND_STATUS          = 0x91,
  /*!Failed case when a otau client or a otau server decides to abort the upgrade process. */
  ZCL_ABORT_STATUS                        = 0x95,
  /*!Invalid OTA upgrade image (ex. failed signature validation or signer information check or CRC check) */
  ZCL_INVALID_IMAGE_STATUS                = 0x96,
  /*!Server does not have data block available yet */
  ZCL_WAIT_FOR_DATA_STATUS                = 0x97,
  /*!No OTA upgrade image available for a particular client */
  ZCL_NO_IMAGE_AVAILABLE_STATUS           = 0x98,
  /*!The client still requires more OTA upgrade image files in order to successfully upgrade*/
  ZCL_REQUIRE_MORE_IMAGE_STATUS           = 0x99,

  //0x97 - 0xbf - Reserved
  /* Request was successfully processed, but application is forcing to reply with DefaultResponse */
  ZCL_SUCCESS_WITH_DEFAULT_RESPONSE_STATUS = 0xAA,

  /*!An operation was unsuccessful due to a hardware failure.*/
  ZCL_HARDWARE_FAILURE_STATUS             = 0xc0,
  /*!An operation was unsuccessful due to a software failure.*/
  ZCL_SOFTWARE_FAILURE_STATUS             = 0xc1,
  /*!An error occurred during calibration.*/
  ZCL_CALIBRATION_ERROR_STATUS            = 0xc2,

  //0xc3 - 0xff - Reserved

  ZCL_NO_RESPONSE_ERROR_STATUS            = 0xc3,
  //ZCL_ATTRIBUTE_NOT_FOUND_STATUS,
  ZCL_BAD_FRAME_STATUS                    = 0xc4,
  //ZCL_WRONG_ATTRIBUTE_TYPE_STATUS,
  ZCL_WRONG_RESPONSE_LENGTH_STATUS        = 0xc5,
  ZCL_END_PAYLOAD_REACHED_STATUS          = 0xfd,
  ZCL_MAX_PAYLOAD_REACHED_STATUS          = 0xfe,
  ZCL_INVALID_PARAMETER_STATUS            = 0xff,

} ZCL_Status_t;

/********************************************************************************//**
\brief ZigBee data types identifiers.

ZigBee devices, such as thermostats, lamps, etc., are defined in terms of the
attributes they contain, which can be written, read or reported using the
ZCL commands. The following list defines the data types and formats that
can be used for these attributes. Note that individual clusters, which may use
different or new types, show valid values, ranges, and units for the attributes they
represent.
Each data type is allocated an 8-bit data type ID. The most significant 5 bits of this
ID is used to divide the types into 32 type classes, and the least significant 3 bits
specify a specific data type within this class.
***********************************************************************************/
typedef enum
{
  //Null
  ZCL_NO_DATA_TYPE_ID                       = 0x00,

  //General data
  ZCL_8BIT_DATA_TYPE_ID                     = 0x08,
  ZCL_16BIT_DATA_TYPE_ID                    = 0x09,
  ZCL_24BIT_DATA_TYPE_ID                    = 0x0a,
  ZCL_32BIT_DATA_TYPE_ID                    = 0x0b,
  ZCL_40BIT_DATA_TYPE_ID                    = 0x0c,
  ZCL_48BIT_DATA_TYPE_ID                    = 0x0d,
  ZCL_56BIT_DATA_TYPE_ID                    = 0x0e,
  ZCL_64BIT_DATA_TYPE_ID                    = 0x0f,

  //Logical
  ZCL_BOOLEAN_DATA_TYPE_ID                  = 0x10,

  //Bitmap
  ZCL_8BIT_BITMAP_DATA_TYPE_ID              = 0x18,
  ZCL_16BIT_BITMAP_DATA_TYPE_ID             = 0x19,
  ZCL_24BIT_BITMAP_DATA_TYPE_ID             = 0x1a,
  ZCL_32BIT_BITMAP_DATA_TYPE_ID             = 0x1b,
  ZCL_40BIT_BITMAP_DATA_TYPE_ID             = 0x1c,
  ZCL_48BIT_BITMAP_DATA_TYPE_ID             = 0x1d,
  ZCL_56BIT_BITMAP_DATA_TYPE_ID             = 0x1e,
  ZCL_64BIT_BITMAP_DATA_TYPE_ID             = 0x1f,

  //Unsigned integer
  ZCL_U8BIT_DATA_TYPE_ID                    = 0x20,
  ZCL_U16BIT_DATA_TYPE_ID                   = 0x21,
  ZCL_U24BIT_DATA_TYPE_ID                   = 0x22,
  ZCL_U32BIT_DATA_TYPE_ID                   = 0x23,
  ZCL_U40BIT_DATA_TYPE_ID                   = 0x24,
  ZCL_U48BIT_DATA_TYPE_ID                   = 0x25,
  ZCL_U56BIT_DATA_TYPE_ID                   = 0x26,
  ZCL_U64BIT_DATA_TYPE_ID                   = 0x27,

  //Signed integer
  ZCL_S8BIT_DATA_TYPE_ID                    = 0x28,
  ZCL_S16BIT_DATA_TYPE_ID                   = 0x29,
  ZCL_S24BIT_DATA_TYPE_ID                   = 0x2a,
  ZCL_S32BIT_DATA_TYPE_ID                   = 0x2b,
  ZCL_S40BIT_DATA_TYPE_ID                   = 0x2c,
  ZCL_S48BIT_DATA_TYPE_ID                   = 0x2d,
  ZCL_S56BIT_DATA_TYPE_ID                   = 0x2e,
  ZCL_S64BIT_DATA_TYPE_ID                   = 0x2f,

  //Enumeration
  ZCL_8BIT_ENUM_DATA_TYPE_ID                = 0x30,
  ZCL_16BIT_ENUM_DATA_TYPE_ID               = 0x31,

  //Floating point
  ZCL_FSEMI_PRECISION_DATA_TYPE_ID          = 0x38,
  ZCL_FSINGLE_PRECISION_DATA_TYPE_ID        = 0x39,
  ZCL_FDOUBLE_PRECISION_DATA_TYPE_ID        = 0x3a,

  //String
  ZCL_OCTET_STRING_DATA_TYPE_ID             = 0x41,
  ZCL_CHARACTER_STRING_DATA_TYPE_ID         = 0x42,
  ZCL_LONG_OCTET_STRING_DATA_TYPE_ID        = 0x43,
  ZCL_LONG_CHARACTER_STRING_DATA_TYPE_ID    = 0x44,

  //Ordered sequence
  ZCL_ARRAY_DATA_TYPE_ID                    = 0x48,
  ZCL_STRUCTURE_DATA_TYPE_ID                = 0x4c,

  //Collection
  ZCL_SET_DATA_TYPE_ID                      = 0x50,
  ZCL_BAG_DATA_TYPE_ID                      = 0x51,

  //Time
  ZCL_TIME_OF_DAY_DATA_TYPE_ID              = 0xe0,
  ZCL_DATE_DATA_TYPE_ID                     = 0xe1,
  ZCL_UTC_TIME_DATA_TYPE_ID                 = 0xe2,

  //Identifier
  ZCL_CLUSTER_ID_DATA_TYPE_ID               = 0xe8,
  ZCL_ATTRIBUTE_ID_DATA_TYPE_ID             = 0xe9,
  ZCL_BACNET_OID_DATA_TYPE_ID               = 0xea,

  //Misscellaneous
  ZCL_IEEE_ADDRESS_DATA_TYPE_ID             = 0xf0,
  ZCL_128BIT_SECURITY_KEY_DATA_TYPE_ID      = 0xf1,
} ZCL_AttributeType_t;

/***************************************************************************//**
\brief The list of general ZCL commands.
*******************************************************************************/
typedef enum
{
  /*! Reading particular attributes' values from a remote device*/
  ZCL_READ_ATTRIBUTES_COMMAND_ID                            = 0x00,
  ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID                   = 0x01,

/*Write attributes*/
  /*! Modifying values of particular attributes on a remote device*/
  ZCL_WRITE_ATTRIBUTES_COMMAND_ID                           = 0x02,
  ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID                 = 0x03,
  ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID                  = 0x04,
  ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID               = 0x05,

/*Configure reporting*/
  ZCL_CONFIGURE_REPORTING_COMMAND_ID                        = 0x06,
  ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID               = 0x07,

/*Read reporting*/
  ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID               = 0x08,
  ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID      = 0x09,

/*Report attributes*/
  /*! Reporting particular attributes to a remote device; that is,
  sending current attributes' values*/
  ZCL_REPORT_ATTRIBUTES_COMMAND_ID                          = 0x0a,

/*Default response*/
  ZCL_DEFAULT_RESPONSE_COMMAND_ID                           = 0x0b,

/*Discover attributes*/
  /*! Obtaining information (IDs and types) of attributes supported
  by a particular cluster on a remote device*/
  ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID                        = 0x0c,
  ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID               = 0x0d,

/*Read attributes structured*/
  ZCL_READ_ATTRIBUTES_STRUCTURED_COMMAND_ID                 = 0x0e,

/*Write attributes structured*/
  ZCL_WRITE_ATTRIBUTES_STRUCTURED_COMMAND_ID                = 0x0f,
  ZCL_WRITE_ATTRIBUTES_STRUCTURED_RESPONSE_COMMAND_ID       = 0x10
} ZCL_GeneralCommandId_t;

/***************************************************************************//**
\brief Type describing possible ZSE Device IDs.
*******************************************************************************/
typedef enum
{
  /*! The Range Extender is a simple device that acts as a router for other devices. The
  Range Extender device shall not be a ZigBee end device. A product that
  implements the Range Extender device shall not implement any other devices
  defined in this profile. This device shall only be used if the product is not intended
  to have any other application, or if a private application is implemented that has
  not been addressed by this profile.*/
  ZSE_RANGE_EXTENDER_DEVICE_ID                          = 0x0008,
  /*! The Energy Service Portal connects the energy supply company communication
  network to the metering and energy management devices within the home. It
  routes messages to and from the relevant end points. It may be installed within a
  meter, thermostat, or In-Premise Display, or may be a standalone device, and it
  will contain another non-ZigBee communication module (e.g. power-line carrier,
  RF, GPRS, broadband Internet connection).*/
  ZSE_ENERGY_SERVICE_PORTAL_DEVICE_ID                   = 0x0500,
  /*!The Metering end device is a meter (electricity, gas, water, heat, etc.) that is fitted
  with a ZigBee device. Depending on what is being metered, the device may be
  capable of immediate (requested) reads or it will autonomously send readings
  periodically. A Metering end device may also be capable of communicating
  certain status indicators (e.g. battery low, tamper detected).*/
  ZSE_METERING_DEVICE_DEVICE_ID                         = 0x0501,
  /*! The In-Premise Display device will relay energy consumption data to the user by
  way of a graphical or text display. The display may or may not be an interactive
  device. At a minimum at least one of the following should be displayed: current
  energy usage, a history over selectable periods, pricing information, or text
  messages. As an interactive device, it can be used for returning simple messages
  for interpretation by the recipient.*/
  ZSE_IN_PREMISE_DISPLAY_DEVICE_ID                      = 0x0502,
  /*! The PCT device shall provide the capability to control the premise heating and
  cooling systems.*/
  ZSE_PROGRAMMABLE_COMMUNICATING_THERMOSTAT_DEVICE_ID   = 0x0503,
  /*! The Load Control device is capable of receiving Demand Response and Load
  Control events to manage consumption on a range of devices. Example devices
  are water heaters, exterior lighting, and pool pumps.*/
  ZSE_LOAD_CONTROL_DEVICE_DEVICE_ID                     = 0x0504,
  /*! Smart Appliance devices on the ZigBee network can participate in energy
  management activities. Examples of these are when Utilities initiate a demand
  response or pricing event, or the appliance actively informs customers via inhome
  displays of when or how energy is being used. In the latter case, scenarios
  include: Washer switching to cold water during periods of higher energy costs;
  Washer/Dryer/Oven/Hot Water Heater reporting cycle status;
  Over temperature conditions in Freezers and Refrigerators.*/
  ZSE_SMART_APPLIANCE_DEVICE_ID                         = 0x0505,
  /*! The Prepayment Terminal device will allow utility customers or other users (e.g.
  sub-metered tenants) to pay for consumption in discrete increments rather than
  establishing a traditional billing agreement. The Prepayment Terminal device will
  accept payment (e.g. credit card, code entry), display remaining balances, and
  alert the user of a balance approaching zero, and may perform some or all of the
  other functions described in In-Premise Display.*/
  ZSE_PREPAYMENT_TERMINAL_DEVICE_ID                     = 0x0506,
} ZSE_DeviceId_t;

/***************************************************************************//**
\brief Type describing possible HA Device Ids.
*******************************************************************************/
typedef enum
{
  /*! Home-Automation-Profile_r25 7.4.1 On/Off Light*/
  HA_ON_OFF_LIGHT_DEVICE_ID                             = 0x0100,
  /*! Home-Automation-Profile_r25 7.4.4 On/Off Light Switch*/
  HA_ON_OFF_LIGHT_SWITCH_DEVICE_ID                      = 0x0103,
  /*! Home-Automation-Profile_r25 7.4.5 Dimmer Switch*/
  HA_DIMMER_SWITCH_DEVICE_ID                            = 0x0104,
  /*! Home-Automation-Profile_r25 7.4.8 Occupancy Sensor*/
  HA_OCCUPANCY_SENSOR_DEVICE_ID                         = 0x0107,
  /*! Home-Automation-Profile_r25 7.3.7 Remote Control*/
  HA_REMOTE_CONTROL_DEVICE_ID                           = 0x0006,
  /*! Home-Automation-Profile_r25 7.4.2 Dimmable Light*/
  HA_DIMMABLE_LIGHT_DEVICE_ID                           = 0x0101,
    /*! Home-Automation-Profile_r25 7.6.2 Thermostat*/
  HA_THERMOSTAT_DEVICE_ID                               = 0x0301,
} HA_DeviceId_t;

/***************************************************************************//**
\brief Type describing possible ZLL Device Ids.
*******************************************************************************/
typedef enum
{
  /*! On/Off Light */
  ZLL_ON_OFF_LIGHT_DEVICE_ID                            = 0x0000,
  /*! On/off plug-in unit */
  ZLL_ON_OFF_PLUGIN_UNIT_DEVICE_ID                      = 0x0010,
  /*! Dimmable light */
  ZLL_DIMMABLE_LIGHT_DEVICE_ID                          = 0x0100,
  /*! Dimmable plug-in unit */
  ZLL_DIMMABLE_PLUGIN_UNIT_DEVICE_ID                    = 0x0110,
  /*! Color light */
  ZLL_COLOR_LIGHT_DEVICE_ID                             = 0x0200,
  /*! Color remote */
  ZLL_COLOR_REMOTE_DEVICE_ID                            = 0x0800,
  /*! Color scene remote */
  ZLL_COLOR_SCENE_REMOTE_DEVICE_ID                      = 0x0810,
  /*! Non-color remote */
  ZLL_NON_COLOR_REMOTE_DEVICE_ID                        = 0x0820,
  /*! Non-color scene remote */
  ZLL_NON_COLOR_SCENE_REMOTE_DEVICE_ID                  = 0x0830,
  /*! Control bridge */
  ZLL_CONTROL_BRIDGE_DEVICE_ID                          = 0x0840,
  /*! On/off sensor */
  ZLL_ON_OFF_SENSOR_DEVICE_ID                           = 0x0850,
} ZLL_DeviceId_t;

/*************************************************************************//**
  \brief ZCL event Ids
*****************************************************************************/
typedef enum
{
  ZCL_ATTRIBUTE_READ_EVENT_ID,      //!< attribute read event
  ZCL_ATTRIBUTE_WRITE_EVENT_ID,     //!< attribute written event
} ZCL_EventId_t;

/*************************************************************************//**
  \brief Reserved type to organize the queue of ZCL requests
*****************************************************************************/
typedef struct
{
  void    *next;
  uint8_t requestType;
} ZCL_Service_t;

/********************************************************************************//**
\brief Type describing address fields of some attributes in ZCL
***********************************************************************************/
typedef struct
{
  APS_AddrMode_t      addrMode;     //!< address mode indicates which address shall be used
  APS_Address_t       addr;         //!< address can be short, extended or group
  ProfileId_t         profileId;    //!< profile identifier
  Endpoint_t          endpointId;   //!< endpoint identifier
  ClusterId_t         clusterId;    //!< cluster identifier
  uint8_t             clusterSide;  //!< cluster side: server or client
  uint16_t            manufacturerSpecCode; //!< manufacturer specific code
#ifdef _LIGHT_LINK_PROFILE_
  bool                nonUnicast;
  uint8_t             sequenceNumber;
#endif /* _LIGHT_LINK_PROFILE_ */
} ZCL_Addressing_t;

/***************************************************************************//**
\brief Type describing ZCL Cluster options.
*******************************************************************************/
typedef struct
{
  uint8_t type        : 1;
  uint8_t security    : 1;
  uint8_t reserved    : 6;
} ZCL_ClusterOptions_t;

/***************************************************************************//**
\brief Type describing ZCL's events on cluster's attribute.
*******************************************************************************/
typedef enum
{
  ZCL_READ_ATTRIBUTE_EVENT,
  ZCL_WRITE_ATTRIBUTE_EVENT
} ZCL_AttributeEvent_t;

/***************************************************************************//**
\brief Type describing ZCL Cluster.
*******************************************************************************/
typedef struct
{
  ClusterId_t       id;                 //!< Cluster Id
  ZCL_ClusterOptions_t options;
  uint8_t           attributesAmount;   //!< Number of cluster attributes
  uint8_t           *attributes;        //!< Cluster attribute descriptors
  uint8_t           commandsAmount;     //!< Number of cluster-specific commands
  uint8_t           *commands;          //!< Cluster-specific command descriptors
  uint8_t           isReporting;        //!< Service field - if any automatic attribute reports are in progress
  void (*ZCL_ReportInd)(ZCL_Addressing_t *addressing, uint8_t reportLength, uint8_t *reportPayload); //!< Callback for reporting events
  void (*ZCL_AttributeEventInd)(ZCL_Addressing_t *addressing, ZCL_AttributeId_t attributeId, ZCL_AttributeEvent_t event); //!< Callback indicates action on cluster's attribute
} ZCL_Cluster_t;

/********************************************************************************//**
\brief Type describing information which is necessary for put/get element to/from payload
***********************************************************************************/
typedef struct
{
  uint8_t id; //!< element id. Can be either ::ZCL_GeneralCommandId_t value or special cluster command id
  uint8_t payloadLength; //!< payload length after adding a new element
  uint8_t *payload; //!< payload pointer where an element is added.
  void    *content; //!< pointer to content (memory) which shall be added/filled to/from payload
} ZCL_NextElement_t;

/********************************************************************************//**
\brief Type describing ZCL response
***********************************************************************************/
typedef struct
{
  ZCL_Status_t          status;          //!< status of command
  uint8_t               responseLength;  //!< length of response payload
  uint8_t              *responsePayload; //!< pointer to response payload. Response payload can be parsed by ZCL_GetNextElement() function
} ZCL_Response_t;

typedef struct
{
  // Service structure
  ZCL_Service_t       service;
  ZCL_Response_t      response;         //!< Response structure
  void (*ZCL_Response)(ZCL_Response_t *resp); //!< callback for response
  void (*ZCL_DefaultResponse)(ZCL_Response_t *resp); //!< callback for default response
  ZCL_Addressing_t    dstAddressing;    //!< addressing of destination node
  Endpoint_t          endpointId;       //!< endpoint id who is request initiator
  uint8_t             id;               //!< command id
  uint8_t             requestLength;    //!< request payload length
  uint8_t             defaultResponse;  //!< default response bit state
  uint8_t             *requestPayload;  //!< request payload. It can be filled by ZCL_PutNextElement() function.
#ifdef _LIGHT_LINK_PROFILE_
  bool                seqNumberSpecified; //!< sequence number in ZCL header will be set according the value in dstAddressing
#endif /* _LIGHT_LINK_PROFILE_ */
} ZCL_Request_t;

BEGIN_PACK

/********************************************************************************//**
\brief Type describing payload element of read request command.

This type can be used to add one attribute entry to the read request payload.
***********************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id; //!< requested attribute id
} ZCL_ReadAttributeReq_t;

/********************************************************************************//**
\brief Types describing payload element of read attributes structured command.
***********************************************************************************/
typedef struct PACK
{
  uint8_t indicator;          //!< indicator field for obtaining required element
  uint16_t index[1];          //!< array of index fields (path to element)
} ZCL_Selector_t;

typedef struct PACK
{
  ZCL_AttributeId_t id;       //!< requested attribute id
  ZCL_Selector_t selector;    //!< attribute selector
} ZCL_ReadAttributesStructuredReq_t;

/********************************************************************************//**
\brief Type describing payload element of response to read request command.

This type can be used to get one attribute entry from the read response payload.
***********************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id;       //!< requested attribute id
  uint8_t           status;   //!< status of reading attribute operation
  uint8_t           type;     //!< requested attribute type
  uint8_t           value[1]; //!< requested attribute value
} ZCL_ReadAttributeResp_t;

/********************************************************************************//**
\brief Type describing payload element of write request command.

This type can be used to add one attribute entry to the write request payload.
***********************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id;       //!< requested attribute id
  uint8_t           type;     //!< requested attribute type
  uint8_t           value[1]; //!< requested attribute value
} ZCL_WriteAttributeReq_t;

/********************************************************************************//**
\brief Type describing payload element of response to write request command.

This type can be used to get next writing status from the write response payload.
***********************************************************************************/
typedef struct PACK
{
  uint8_t           status; //!< status of writing attribute operation
  ZCL_AttributeId_t id;     //!< requested attribute id
} ZCL_WriteAttributeResp_t;

/********************************************************************************//**
\brief Type describing payload element of configure report request command.

This type can be used to add one reporting record to the "configure report" request payload.
***********************************************************************************/
typedef struct PACK
{
  /*! The direction field specifies whether values of the attribute are be reported (0x00),
   * or whether reports of the attribute are to be received (0x01).*/
  uint8_t direction;
  /*! If the direction field is 0x00, this field contains the identifier of the attribute
   * that is to be reported. If instead the direction field is 0x01,
   * the device shall expect reports of values of this attribute.*/
  ZCL_AttributeId_t attributeId;
  union PACK
  {
    struct PACK
    {
      /*! The Attribute data type field contains the data type of the attribute
      * that is to be reported.*/
      uint8_t attributeType;
      /*! The minimum reporting interval field is 16-bits in length and shall contain
      * the minimum interval, in seconds, between issuing reports of the specified attribute.*/
      ZCL_ReportTime_t minReportingInterval;
      /*! The maximum reporting interval field is 16-bits in length and
      * shall contain the maximum interval, in seconds, between issuing reports
      * of the specified attribute.*/
      ZCL_ReportTime_t maxReportingInterval;
      /*! The reportable change field shall contain the minimum change to the attribute
      * that will result in a report being issued. This field is of variable length.
      * For attributes with 'analog' data type the field has the same data type
      * as the attribute.*/
      uint8_t reportableChange[1];
    };
    /*! The timeout period field is 16-bits in length and shall contain the maximum
      * expected time, in seconds, between received reports for the attribute specified
      * in the attribute identifier field. If more time than this elapses between reports,
      * this may be an indication that there is a problem with reporting.
      * If this value is set to 0x0000, reports of the attribute are not subject to timeout.*/
    ZCL_ReportTime_t timeoutPeriod;
  };
} ZCL_ConfigureReportingReq_t;

/********************************************************************************//**
\brief Type describing payload element of response to configure report request command.

This type can be used to get next status entry from the "configure report" response payload.
***********************************************************************************/
typedef struct PACK
{
  uint8_t           status;    //!< status of the configure reporting operation
  uint8_t           direction; //!< The direction field specifies whether values of the attribute are be reported (0x00), or whether reports of the attribute are to be received (0x01).
  ZCL_AttributeId_t attributeId;        //!< requested attribute identifier
} ZCL_ConfigureReportingResp_t;

/********************************************************************************//**
\brief Type describing payload element of ZCL Read Reporting Configuration command.
***********************************************************************************/
typedef struct PACK
{
  uint8_t           direction;    //!< The direction field specifies whether values of the attribute are be reported (0x00), or whether reports of the attribute are to be received (0x01).
  ZCL_AttributeId_t attributeId;  //!< requested attribute identifier
} ZCL_ReadReportingConfigurationReq_t;

/********************************************************************************//**
\brief Type describing payload element of ZCL Read Reporting Configuration Response command.
***********************************************************************************/
typedef struct PACK
{
  /*! If the attribute is not implemented on the sender or receiver of the command,
   * whichever is relevant (depending on direction), this field shall be set
   * to UNSUPPORTED_ATTRIBUTE. If the attribute is supported, but is not capable of
   * being reported, this field shall be set to UNREPORTABLE_ATTRIBUTE.
   * Otherwise, this field shall be set to SUCCESS.*/
  uint8_t             status;
  /*! The direction field specifies whether values of the attribute are reported (0x00),
   * or whether reports of the attribute are received (0x01).*/
  uint8_t             direction;
  /*! If the direction field is 0x00, this field contains the identifier of the attribute
   * that is to be reported. If instead the direction field is 0x01,
   * the device shall expect reports of values of this attribute.*/
  ZCL_AttributeId_t   attributeId;
  union PACK
  {
    struct PACK
    {
      /*! The Attribute data type field contains the data type of the attribute
      * that is to be reported.*/
      uint8_t          attributeType;
      /*! The minimum reporting interval field is 16-bits in length and shall contain
      * the minimum interval, in seconds, between issuing reports of the specified attribute.*/
      ZCL_ReportTime_t minReportingInterval;
      /*! The maximum reporting interval field is 16-bits in length and
      * shall contain the maximum interval, in seconds, between issuing reports
      * of the specified attribute.*/
      ZCL_ReportTime_t maxReportingInterval;
      /*! The reportable change field shall contain the minimum change to the attribute
      * that will result in a report being issued. This field is of variable length.
      * For attributes with 'analog' data type the field has the same data type
      * as the attribute.*/
      uint8_t          reportableChange[1];
    };
    /*! The timeout period field is 16-bits in length and shall contain the maximum
      * expected time, in seconds, between received reports for the attribute specified
      * in the attribute identifier field. If more time than this elapses between reports,
      * this may be an indication that there is a problem with reporting.
      * If this value is set to 0x0000, reports of the attribute are not subject to timeout.*/
    ZCL_ReportTime_t  timeoutPeriod;
  };
} ZCL_ReadReportingConfigurationResp_t;

/********************************************************************************//**
\brief Type describing payload element of report command.

This type can be used to get next reported attribute from the report payload.
***********************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t id;       //!< requested attribute id
  uint8_t           type;     //!< requested attribute type
  uint8_t           value[1]; //!< requested attribute value
} ZCL_Report_t;

/********************************************************************************//**
\brief Type describing payload of ZCL Default Response Command.
***********************************************************************************/
typedef struct PACK
{
  /*!The command identifier field is 8-bit in length and specifies the identifier
  of the received command to which this command is a response.*/
  uint8_t           commandId;
  /*!The status code field is 8-bit in length and specifies either SUCCESS or
  the nature of the error that was detected in the receive command.*/
  uint8_t           statusCode;
} ZCL_DefaultResp_t;

/********************************************************************************//**
\brief Type describing payload of ZCL Discovery Attributes Command.
***********************************************************************************/
typedef struct PACK
{
  /*!The start attribute identifier field is 16-bit in length and specifies
  the value of the identifier at which to begin the attribute discovery.*/
  ZCL_AttributeId_t startAttributeId;
  /*!The maximum attribute identifiers field is 8-bit in length and specifies
  the maximum number of attribute identifiers that are to be returned in the
  resulting discovery attributes response command.*/
  uint8_t           maxAttributeIds;
} ZCL_DiscoverAttributesReq_t;

/********************************************************************************//**
\brief Type describing payload the Attribute Report field of ZCL Discovery
       Attributes Response Command.
***********************************************************************************/
typedef struct PACK
{
  ZCL_AttributeId_t attributeId;  //!<Attribute identifier
  uint8_t           typeId;       //!<Attribute data type Id
} ZCL_DiscoverAttributesRespRec_t;

/********************************************************************************//**
\brief Type describing payload of ZCL Discovery Attributes Response Command.
***********************************************************************************/
typedef struct PACK
{
  /*!The discovery complete field is a boolean field. A value of 0 indicates
  that there are more attributes to be discovered. A value of 1 indicates that
  there are no more attributes to be discovered.*/
  uint8_t                           discoveryComplete;
  /*!Discovered attribute information*/
  ZCL_DiscoverAttributesRespRec_t   attributeInfo[1];
} ZCL_DiscoverAttributesResp_t;

END_PACK

/*************************************************************************//**
  \brief Type describing attribute events notification
*****************************************************************************/
typedef struct
{
  ZCL_Addressing_t   addressing;        //!< source addressing, source endpoint, destination cluster
  uint8_t            attributeId;       //!< attribute id
} ZCL_AttributeEventNtfy_t;

/*************************************************************************//**
  \brief Type describing parameter of ZCL_EventNtfy() function
*****************************************************************************/
typedef struct
{
  ZCL_EventId_t       eventId;         //!< event Id (e.g. ZCL_ATTRIBUTE_READ_EVENT_ID)
  union
  {
    ZCL_AttributeEventNtfy_t   attribute;  //!< attribute event
  } eventType;
} ZCL_EventNtfy_t;

/********************************************************************************//**
\brief Type describing parameter of ZCL_RegisterEndpoint() function
***********************************************************************************/
typedef struct
{
  // Service structure
  struct
  {
    APS_RegisterEndpointReq_t apsEndpoint;
    uint8_t seqNum;
  } service;

  SimpleDescriptor_t    simpleDescriptor;   //!< Device endpoint Simple Descriptor
  ZCL_Cluster_t         *serverCluster;     //!< Device server clusters
  ZCL_Cluster_t         *clientCluster;     //!< Device client clusters
} ZCL_DeviceEndpoint_t;

/*************************************************************************//**
 \brief ZCL Data Type Descriptor.
        Describes the Data Type length in bytes and Data Type kind (Analog or Descrete).
*****************************************************************************/
typedef struct
{
  uint16_t   length;                     //!<Length in bytes
  /*!Kind of Data Type. The #ZCL_DATA_TYPE_ANALOG_KIND, \n
   !#ZCL_DATA_TYPE_DISCRETE_KIND or \n
   !#ZCL_DATA_TYPE_COLLECTION_KIND should be used).*/
  uint8_t   kind;
} ZCL_DataTypeDescriptor_t;

/******************************************************************************
                           Inline functions section
******************************************************************************/
/********************************************************************************//**
  \brief Gets Cluster Side the Incoming command is intended to.

  \param[in] direction - incoming command direction
  \return cluster side detected
***********************************************************************************/
INLINE uint8_t getDstClusterSideByIncommingCommandDirection(uint8_t direction)
{
  return !direction;
}

/********************************************************************************//**
  \brief Gets source Cluster Side by destination Cluster side.

  \param[in] clusterSide - destination cluster's side
  \return cluster side detected
***********************************************************************************/
INLINE uint8_t getSrcClusterSideByDstClusterSide(uint8_t clusterSide)
{
  return !clusterSide;
}

/********************************************************************************//**
  \brief Gets destination Cluster Side by source Cluster side.

  \param[in] clusterSide - source cluster's side
  \return cluster side detected
***********************************************************************************/
INLINE uint8_t getDstClusterSideBySrcClusterSide(uint8_t clusterSide)
{
  return !clusterSide;
}

/********************************************************************************//**
  \brief Gets outgoing command direction by destination Cluster side.

  \param[in] clusterSide - destination cluster's side
  \return command direction detected
***********************************************************************************/
INLINE uint8_t getOutgoingCommandDirectionByDstClusterSide(uint8_t clusterSide)
{
  return clusterSide;
}

/********************************************************************************//**
  \brief Gets source Cluster side by direction of incoming command.

  \param[in] direction - incoming command direction.
  \return detected cluster side.
***********************************************************************************/
INLINE uint8_t getOwnClusterSideByIncomingCommandDirection(uint8_t direction)
{
  return direction;
}

/********************************************************************************//**
  \brief Gets destination Cluster side by direction of outgoing command.

  \param[in] direction - outgoing command direction.
  \return detected cluster side.
***********************************************************************************/
INLINE uint8_t getDstClusterSideByOutgoingCommandDirection(uint8_t direction)
{
  return direction;
}

/********************************************************************************//**
  \brief Gets direction of incoming command by it's initiator cluster side.

  \param[in] clusterSide - command initiator cluster's side
  \return incoming command direction
***********************************************************************************/
INLINE uint8_t ZCL_GetIncomingCommandDirectionBySrcClusterSide(uint8_t clusterSide)
{
  return !clusterSide;
}

/***************************************************************************//**
\brief Calculates offset for zcl data in zcl buffer.

\return offset.
******************************************************************************/
INLINE uint8_t getZclAsduOffset(void)
{
  return APS_ASDU_OFFSET + GUARD_SIZE;
}

/******************************************************************************
                           Functions prototypes section
******************************************************************************/
/*********************************************************************************//**
\brief Registers an application endpoint

\ingroup zcl_common

This function registers an application endpoint to make ZCL know which devices types
are used by the application and which client and server clusters are supported.

\param[in] endpoint - contains device descriptor
************************************************************************************/
void ZCL_RegisterEndpoint(ZCL_DeviceEndpoint_t *endpoint);

/*************************************************************************//**
\brief Resets the ZCL component

\ingroup zcl_common

\param[in] none
*****************************************************************************/
void ZCL_ResetReq(void);

/*************************************************************************//**
 \brief Finds an attribute in ZCL and returns its value

 \ingroup zcl_common

 The function may be used to obtain only local attributes.
 To access an attribute on a remote device, send a read attributes
 general cluster command via the ZCL_AttributeReq() function.

 \param[in] endpointId - endpoint on which cluster is registered
 \param[in] clusterId - cluster unique identifier
 \param[in] direction - detects the cluster's side (client or server)
 \param[in] attrId - attribute unique identifier
 \param[out] attrType - pointer to attribute type determined and returned
 \param[out] attrValue - read out attribute value pointer

  Caller is responsible for providing big enough attrValue buffer.

 \return status of operation
*****************************************************************************/
ZCL_Status_t ZCL_ReadAttributeValue(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t direction,
                                    ZCL_AttributeId_t attrId, uint8_t *attrType, uint8_t *attrValue);

/*************************************************************************//**
 \brief Finds an attribute in ZCL and rewrites its value by the new one

 \ingroup zcl_common

 The function may be used to set or rewrite only local attributes.
 To set a new value to an attribute on a remote device, send a write attributes
 general cluster command via the ZCL_AttributeReq() function.

 \param[in] endpointId - endpoint on which cluster is registered
 \param[in] clusterId - cluster unique identifier
 \param[in] direction - detects the cluster's side (client or server)
 \param[in] attrId - attribute unique identifier
 \param[in] attrType - type of the attribute to be set
 \param[in] attrValue - pointer to attribute value to be set

 \return status of operation
*****************************************************************************/
ZCL_Status_t ZCL_WriteAttributeValue(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t direction,
                                     ZCL_AttributeId_t attrId, uint8_t attrType, uint8_t *attrValue);

/*************************************************************************//**
 \brief Finds an attribute in ZCL and rewrites its reportable change value by the new one

 \ingroup zcl_common

 If the reportable change value of an attribute is set to a non-zero value, using
 this function, the stack checks how much the attribute has changed each
 time a new value is set to it. The current (just set) value is compared with
 the last reported value, and if the absolute difference is greater than the
 reportable change value a new report is generated and sent to the air.

 \param[in] endpointId - endpoint on which cluster is registered
 \param[in] clusterId - cluster unique identifier
 \param[in] clusterSide - determs the cluster's side (client or server)
 \param[in] attrId - attribute unique identifier
 \param[in] attrType - type of the attribute to be set
 \param[in] repChange - pointer to reportable change value to be set

 \return status of operation.
*****************************************************************************/
ZCL_Status_t ZCL_SetReportableChange(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t clusterSide,
                                     ZCL_AttributeId_t attrId, uint8_t attrType, uint8_t *repChange);

/*************************************************************************//**
 \brief Finds attribute in ZCL and rewrites its value by the new one
 (to be used with remote write request).

 \param[in] endpointId - endpoint on which cluster is registered
 \param[in] clusterId - cluster unique identifier
 \param[in] direction - detects the cluster's side (client or server)
 \param[in] attrId - attribute unique identifier
 \param[in] attrType - type of the attribute to be set
 \param[in] attrValue - pointer to attribute value to be set
 \param[in] onlyCheck - not to write, but only check attribute existance.

 \return status of operation
*****************************************************************************/
ZCL_Status_t zclRemoteWriteAttributeValue(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t direction,
                                          ZCL_AttributeId_t attrId, uint8_t attrType, uint8_t *attrValue,
                                          bool onlyCheck);

/*************************************************************************//**
 \brief Sends a general ZCL command related to attributes to a remote device

 \ingroup zcl_common

 The function is used to read/write attributes from a remote device, to report
 local attributes, and to discover attributes supported by a particular cluster
 on a remote device.

 Command's parameters include addressing information, calback functions, command's
 ID, and the payload. The payload may be formed via the ZCL_PutNextElement() function
 and an instance of ZCL_NextElement_t type. The command may be used to perform
 actions on multiple attributes at a time; for example, to read several attributes
 from a remote device.

 Attribute related commands are usually send to specific short or extended addresses.
 Sending such commands to bound devices (employing ::APS_NO_ADDRESS mode) may not
 be as efficient, because in case of responses from more than one device the ZCL
 component will process only the first one.

 Upon receiving the response from the remote device, the callback function specified
 in the \c req->ZCL_Response field is called.

 Common uses of the function include sending the following commands (the command's
 ID listed below should be assigned to the \c req->id field):
 \li ::ZCL_READ_ATTRIBUTES_COMMAND_ID - reading remote attributes (obtaining values)
 \li ::ZCL_WRITE_ATTRIBUTES_COMMAND_ID - writing remote attributes (assigning new values)
 \li ::ZCL_REPORT_ATTRIBUTES_COMMAND_ID - reporting local attributes to remote devices
     (sending current attributes' values)
 \li ::ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID - discovering attributes of a remote device (obtaining
     data types and IDs of attributes supported by a particular cluster)

 \param[in] req - command parameters
*****************************************************************************/
void ZCL_AttributeReq(ZCL_Request_t *req);

/*********************************************************************************//**
 \brief Sends a cluster-specific command

 \ingroup zcl_common

 The function sends a general cluster specific command. The command's type is
 recognized according to the \c req->id field. Commands' IDs are defined in clusters'
 definition files, which also contain all definition related to a particular cluster.

 In addition to addressing information and command's ID, eesential fields of
 the request parameters include the payload and the payload length. The payload
 for each command is defined as a structure in the cluster's definition file.
 The pointer to a properly configured instance of the command's payload shall be \
 assigned to the \c req->requestPayload field.

 The callback function specified in the \c req->ZCL_Response field is called to
 indicate the status of the command's delivery (not a specific response for the
 command). If acknowledgment of the command's delivery is received the success
 status is reported in the callback.

 A specific response to the command is processed by a special indication function
 registered for the command. If a command does not imply a specific response
 the default response may be requested (to indicate that the command has been
 executed). To request the default response set the \c req->defaultResponse field
 to ::ZCL_FRAME_CONTROL_ENABLE_DEFAULT_RESPONSE and assign the callback function
 that should be called upon default response reception to the \c req->ZCL_DefaultResponse
 field. To disable default response set \c req->defaultResponse to
 ::ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RESPONSE and \c req->ZCL_DefaultResponse to \c NULL.

 \param[in] req - contains request descriptor
************************************************************************************/
void ZCL_CommandReq(ZCL_Request_t *req);

/*********************************************************************************//**
\brief Specific command indication handler

\param[in] ind - contains indication descriptor
************************************************************************************/
//void ZCL_CommandInd(ZCL_CommandInd_t *ind);

/*************************************************************************//**
 \brief ZCL event notification handler

 \param[in] event - contains event descriptor
*****************************************************************************/
void ZCL_EventNtfy(ZCL_EventNtfy_t *event);

/*************************************************************************//**
 \brief This function returns bytes amount of a type by the type's ID

 \ingroup zcl_common

 \param[in] typeId - type's ID
 \param[in] value - pointer to variable of typeId, NULL means
            the maximum possible size
*****************************************************************************/
uint16_t ZCL_GetAttributeLength(uint8_t typeId, const uint8_t *value);

/*************************************************************************//**
 \brief Adds an element to the outgoing command payload

 \ingroup zcl_common

 This function is used to simplify forming a correst payload for general
 commands (read/write attributes etc.). A single command may involve actions on
 several attributes, and so the overall payload should contain pieces
 corresponding to each attribute.

 The general idea is to provide a buffer for the payload and some content. The
 function writes the content in a correct way to the buffer and calculate the
 overall payload length. The buffer and the payload length are then passed as
 parameters to the ZCL_AttributeReq() function.

 See the following example:

\code
ZCL_NextElement_t element;
ZCL_ReadAttributeReq_t readAttrReqElement;
ZCL_Request_t readAttrReq;
uint8_t buffer[BUFFER_SIZE];

element.payloadLength = 0;
element.payload = buffer;
element.id = ZCL_READ_ATTRIBUTES_COMMAND_ID;
element.content = &readAttrReqElement;

readAttrReqElement = ATTRIBUTE_ID1; //Set to the ID of the first attribute
ZCL_PutNextElement(&element);

readAttrReqElement = ATTRIBUTE_ID2; //Set to the ID of the second attribute
ZCL_PutNextElement(&element);

readAttrReq.requestLength = element.payloadLength;
readAttrReq.requestPayload = buffer;
...
\endcode

 Note, however, that the usage may differ depending on a command's type.

 \param[in] element - information about payload and element
 \param[out] status of the operation
*****************************************************************************/
ZCL_Status_t ZCL_PutNextElement(ZCL_NextElement_t *element);

/*************************************************************************//**
 \brief Gets an element from the incoming command's payload

 \ingroup zcl_common

 The function is used to simplify processing of responses fo general
 attributes related commands. Such command may return information concerning
 several attributes in a single frame. This function reads the next portion
 of information from the response payload.

 To use the function configure an instance of ZCL_NextElement type.
 The \c element->payload field should be set to the response payload,
 the \c element->payloadLength to the reponse payload's length, and
 the \c element->id field to the ID of the response. After calling this
 function, the \c element->content field may be casted to the appropriate
 response type (depending on the command's type); for example, for
 read attributes response it is ZCL_ReadAttributeResp_t.

 \param[in] element - information about payload and element
 \param[out] status of the operation
*****************************************************************************/
ZCL_Status_t ZCL_GetNextElement(ZCL_NextElement_t *element);

/***************************************************************************//**
\brief Checks whether ZCL is busy or not

\ingroup zcl_common

\return true - if ZCL is busy, false - otherwise
******************************************************************************/
bool ZCL_IsBusy(void);

/*************************************************************************//**
  \brief  ZCL data type descriptor get by the type ID function;
          fills the ZCL data type descriptor dased on the ZCL data type ID

  \param  Id - ZCL data type ID (unsigned 8-bit integer)
  \param  value - pointer to variable of typeId, NULL means maximum possible
          size
  \param  descriptor - ZCL Data Type Descriptor being filled
  \return None
  \sa     ZCL_DataTypeDescriptor_t
  \sa     ZCL_GetAttributeLength()
*****************************************************************************/
void ZCL_GetDataTypeDescriptor(uint8_t typeId, const uint8_t *value, ZCL_DataTypeDescriptor_t *descriptor);

/*************************************************************************//**
  \brief Find cluster descriptor by endpoint id, cluster id.

  \param[in] endpointId - endpoint unique identifier.
  \param[in] clusterId - cluster unique identifier.
  \param[in] clusterSide - cluster side (client or server).
  \return ZCL cluster descriptor if found, NULL otherwise.
*****************************************************************************/
ZCL_Cluster_t *ZCL_GetCluster(Endpoint_t endpointId, ClusterId_t clusterId, uint8_t clusterSide);

/**************************************************************************//**
  \brief Interface to pass ZCL request to APS

  APS_DataConf field in APS_DataReq must be an actual confirm handler pointer.

  \param[in] req The APS_DataReq_t primitive pointer.
  \param[in] apsSecurity If true APS security is switched on.
*****************************************************************************/
void zclApsDataReq(APS_DataReq_t *req, bool apsSecurity);

#endif //_ZCL_H

