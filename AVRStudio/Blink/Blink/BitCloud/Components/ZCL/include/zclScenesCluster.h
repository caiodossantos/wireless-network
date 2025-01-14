/***************************************************************************//**
  \file zclScenesCluster.h

  \brief
    The header file describes the ZCL Scenes Cluster and its interface

    The file describes the types and interface of the ZCL Scenes Cluster

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008-2012, Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    12.02.09 D. Kasyanov - Created.
*******************************************************************************/

#ifndef _ZCLSCENESCLUSTER_H
#define _ZCLSCENESCLUSTER_H

/*!
Attributes and commands for determining basic information about a device,
setting user device information such as location, enabling a device and resetting it
to factory defaults.
*/

/*******************************************************************************
                   Includes section
*******************************************************************************/

#include <zcl.h>
#include <clusters.h>

/*******************************************************************************
                   Define(s) section
*******************************************************************************/

/**
 * \brief Scenes Cluster scene name support bit
*/

#define SCENE_NAME_SUPPORT_FLAG  0x80

/**
 * \brief Scenes Cluster server attributes amount
*/

#define ZCL_SCENES_CLUSTER_SERVER_ATTRIBUTES_AMOUNT 5

/**
 * \brief Scenes Cluster client attributes amount. Clinet doesn't have attributes.
*/

#define ZCL_SCENES_CLUSTER_CLIENT_ATTRIBTUES_AMOUNT 0

/**
 * \brief Scenes Cluster commands amount
*/

#define ZCL_SCENES_CLUSTER_COMMANDS_AMOUNT 13

/**
 * \brief Scenes Cluster server's attributes identifiers
*/

#define ZCL_SCENES_CLUSTER_SCENE_COUNT_SERVER_ATTRIBUTE_ID    CCPU_TO_LE16(0x0000)
#define ZCL_SCENES_CLUSTER_CURRENT_SCENE_SERVER_ATTRIBUTE_ID  CCPU_TO_LE16(0x0001)
#define ZCL_SCENES_CLUSTER_CURRENT_GROUP_SERVER_ATTRIBUTE_ID  CCPU_TO_LE16(0x0002)
#define ZCL_SCENES_CLUSTER_SCENE_VALID_SERVER_ATTRIBUTE_ID    CCPU_TO_LE16(0x0003)
#define ZCL_SCENES_CLUSTER_NAME_SUPPORT_SERVER_ATTRIBUTE_ID   CCPU_TO_LE16(0x0004)

/**
 * \brief Scenes Cluster client's command identifiers
*/

#define ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID            0x00
#define ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID           0x01
#define ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID         0x02
#define ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID    0x03
#define ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID          0x04
#define ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID         0x05
#define ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID 0x06

/**
 * \brief Scenes Cluster servers's command identifiers
*/

#define ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID         0x00
#define ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID        0x01
#define ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID      0x02
#define ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID 0x03
#define ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID       0x04
#define ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID 0x06


/**
 * \brief Scenes Cluster server define attributes macros
*/

#define ZCL_DEFINE_SCENES_CLUSTER_SERVER_ATTRIBUTES() \
    DEFINE_ATTRIBUTE(sceneCount, ZCL_READONLY_ATTRIBUTE, ZCL_SCENES_CLUSTER_SCENE_COUNT_SERVER_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID), \
    DEFINE_ATTRIBUTE(currentScene, ZCL_READONLY_ATTRIBUTE, ZCL_SCENES_CLUSTER_CURRENT_SCENE_SERVER_ATTRIBUTE_ID, ZCL_U8BIT_DATA_TYPE_ID), \
    DEFINE_ATTRIBUTE(currentGroup, ZCL_READONLY_ATTRIBUTE, ZCL_SCENES_CLUSTER_CURRENT_GROUP_SERVER_ATTRIBUTE_ID, ZCL_U16BIT_DATA_TYPE_ID), \
    DEFINE_ATTRIBUTE(sceneValid, ZCL_READONLY_ATTRIBUTE, ZCL_SCENES_CLUSTER_SCENE_VALID_SERVER_ATTRIBUTE_ID, ZCL_BOOLEAN_DATA_TYPE_ID), \
    DEFINE_ATTRIBUTE(nameSupport, ZCL_READONLY_ATTRIBUTE, ZCL_SCENES_CLUSTER_NAME_SUPPORT_SERVER_ATTRIBUTE_ID, ZCL_8BIT_BITMAP_DATA_TYPE_ID)


/**
 * \brief On/Off Cluster define commands macros
*/

#define ZCL_DEFINE_SCENES_CLUSTER_COMMANDS(addSceneCommandInd, viewSceneCommandInd, removeSceneCommandInd, \
          removeAllScenesCommandInd, storeSceneCommandInd, recallSceneCommandInd, \
          getSceneMembershipCommandInd, addSceneResponseCommandInd, viewSceneResponseCommandInd, \
          removeSceneResponseCommandInd, removeAllScenesResponseCommandInd, storeSceneResponseCommandInd, \
          getSceneMembershipResponseInd) \
    DEFINE_COMMAND(addSceneCommand, ZCL_SCENES_CLUSTER_ADD_SCENE_COMMAND_ID,  \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     addSceneCommandInd), \
    DEFINE_COMMAND(viewSceneCommand, ZCL_SCENES_CLUSTER_VIEW_SCENE_COMMAND_ID, \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     viewSceneCommandInd), \
    DEFINE_COMMAND(removeSceneCommand, ZCL_SCENES_CLUSTER_REMOVE_SCENE_COMMAND_ID, \
                      COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     removeSceneCommandInd), \
    DEFINE_COMMAND(removeAllScenesCommand, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_COMMAND_ID,  \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     removeAllScenesCommandInd), \
    DEFINE_COMMAND(storeSceneCommand, ZCL_SCENES_CLUSTER_STORE_SCENE_COMMAND_ID, \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     storeSceneCommandInd), \
    DEFINE_COMMAND(recallSceneCommand, ZCL_SCENES_CLUSTER_RECALL_SCENE_COMMAND_ID, \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     recallSceneCommandInd), \
    DEFINE_COMMAND(getSceneMembershipCommand, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_COMMAND_ID, \
                     COMMAND_OPTIONS(CLIENT_TO_SERVER, ZCL_THERE_IS_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     getSceneMembershipCommandInd), \
    DEFINE_COMMAND(addSceneResponseCommand, ZCL_SCENES_CLUSTER_ADD_SCENE_RESPONSE_COMMAND_ID, \
                      COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     addSceneResponseCommandInd), \
    DEFINE_COMMAND(viewSceneResponseCommand, ZCL_SCENES_CLUSTER_VIEW_SCENE_RESPONSE_COMMAND_ID,  \
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     viewSceneResponseCommandInd), \
    DEFINE_COMMAND(removeSceneResponseCommand, ZCL_SCENES_CLUSTER_REMOVE_SCENE_RESPONSE_COMMAND_ID, \
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     removeSceneResponseCommandInd), \
    DEFINE_COMMAND(removeAllScenesResponseCommand, ZCL_SCENES_CLUSTER_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID, \
                      COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     removeAllScenesResponseCommandInd), \
    DEFINE_COMMAND(storeSceneResponseCommand, ZCL_SCENES_CLUSTER_STORE_SCENE_RESPONSE_COMMAND_ID,  \
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     storeSceneResponseCommandInd), \
    DEFINE_COMMAND(getSceneMembershipResponse, ZCL_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID, \
                     COMMAND_OPTIONS(SERVER_TO_CLIENT, ZCL_THERE_IS_NO_RELEVANT_RESPONSE, ZCL_COMMAND_ACK), \
                     getSceneMembershipResponseInd)


/**
 * \brief Scene Cluster definition macros
*/

#define SCENES_CLUSTER_ZCL_CLIENT_CLUSTER_TYPE(clattributes, clcommands) \
{ \
   .id = SCENES_CLUSTER_ID, \
   .options = { \
                .type = ZCL_CLIENT_CLUSTER_TYPE, \
                .security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY, \
              }, \
   .attributesAmount = ZCL_SCENES_CLUSTER_CLIENT_ATTRIBTUES_AMOUNT, \
   .attributes = (uint8_t *)clattributes, \
   .commandsAmount = ZCL_SCENES_CLUSTER_COMMANDS_AMOUNT, \
   .commands = (uint8_t *)clcommands \
}

#define SCENES_CLUSTER_ZCL_SERVER_CLUSTER_TYPE(clattributes, clcommands) \
{ \
   .id = SCENES_CLUSTER_ID, \
   .options = { \
                .type = ZCL_SERVER_CLUSTER_TYPE, \
                .security = ZCL_APPLICATION_LINK_KEY_CLUSTER_SECURITY, \
              }, \
   .attributesAmount = ZCL_SCENES_CLUSTER_SERVER_ATTRIBUTES_AMOUNT, \
   .attributes = (uint8_t *)clattributes, \
   .commandsAmount = ZCL_SCENES_CLUSTER_COMMANDS_AMOUNT, \
   .commands = (uint8_t *)clcommands \
}

#define DEFINE_SCENES_CLUSTER(cltype, clattributes, clcommands) \
    SCENES_CLUSTER_##cltype(clattributes, clcommands)

/******************************************************************************
                    Types section
******************************************************************************/
BEGIN_PACK

/**
 * \brief Add Scene Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
  uint16_t transitionTime;
  uint8_t sceneNameAndExtField[1];
} ZCL_AddScene_t;

/**
 * \brief View Scene Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_ViewScene_t;

/**
 * \brief Remove Scene Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_RemoveScene_t;

/**
 * \brief Remove All Scenes Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
} ZCL_RemoveAllScenes_t;

/**
 * \brief Store Scene Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_StoreScene_t;

/**
 * \brief Recall Scene Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_RecallScene_t;

/**
 * \brief Get Scene Membership Command Payload format.
 */

typedef struct PACK
{
  uint16_t groupId;
} ZCL_GetSceneMembership_t;

/**
 * \brief Add Scene Response Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_AddSceneResponse_t;

/**
 * \brief View Scene Response Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint16_t groupId;
  uint8_t sceneId;
  uint16_t transitionTime;
  uint8_t nameAndExtField[1]; // string sceneName, extension field.
} ZCL_ViewSceneResponse_t;

/**
 * \brief Remove Scene Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_RemoveSceneResponse_t;

/**
 * \brief Remove All Scenes Response Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint16_t groupId;
} ZCL_RemoveAllScenesResponse_t;

/**
 * \brief Store Scene Response Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint16_t groupId;
  uint8_t sceneId;
} ZCL_StoreSceneResponse_t;

/**
 * \brief Get Scene Membership Response Command Payload format.
 */

typedef struct PACK
{
  uint8_t status;
  uint8_t capacity;
  uint16_t groupId;
  uint8_t sceneCount;
  uint8_t sceneList[1];
} ZCL_GetSceneMembershipResponse_t;

/**
 * \brief Scene Cluster server's attributes
 */

typedef struct PACK
{
  struct PACK
  {
    ZCL_AttributeId_t id;
    uint8_t type;
    uint8_t properties;
    uint8_t value;
  } sceneCount;

  struct PACK
  {
    ZCL_AttributeId_t id;
    uint8_t type;
    uint8_t properties;
    uint8_t value;
  } currentScene;

  struct PACK
  {
    ZCL_AttributeId_t id;
    uint8_t type;
    uint8_t properties;
    uint16_t value;
  } currentGroup;

  struct PACK
  {
    ZCL_AttributeId_t id;
    uint8_t type;
    uint8_t properties;
    bool value;
  } sceneValid;

  struct PACK
  {
    ZCL_AttributeId_t id;
    uint8_t type;
    uint8_t properties;
    uint8_t value;
  } nameSupport;
} ZCL_SceneClusterServerAttributes_t;

END_PACK

/**
 * \brief Scene Cluster commands.
 */

typedef struct
{
  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*addSceneCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddScene_t * payload);
  } addSceneCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*viewSceneCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewScene_t * payload);
  } viewSceneCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*removeSceneCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveScene_t * payload);
  } removeSceneCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*removeAllScenesCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenes_t * payload);
  } removeAllScenesCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*storeSceneCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreScene_t * payload);
  } storeSceneCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*recallSceneCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RecallScene_t * payload);
  } recallSceneCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*getSceneMembershipCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembership_t * payload);
  } getSceneMembershipCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*addSceneResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_AddSceneResponse_t * payload);
  } addSceneResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*viewSceneResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_ViewSceneResponse_t * payload);
  } viewSceneResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*removeSceneResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveSceneResponse_t * payload);
  } removeSceneResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*removeAllScenesResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_RemoveAllScenesResponse_t * payload);
  } removeAllScenesResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*storeSceneResponseCommand)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_StoreSceneResponse_t * payload);
  } storeSceneResponseCommand;

  struct
  {
    ZCL_CommandId_t id;
    ZclCommandOptions_t options;
    ZCL_Status_t(*getSceneMembershipResponse)(ZCL_Addressing_t *addressing, uint8_t payloadLength, ZCL_GetSceneMembershipResponse_t * payload);
  } getSceneMembershipResponse;
} ZCL_ScenesClusterCommands_t;


#endif /* _ZCLSCENESCLUSTER_H */

