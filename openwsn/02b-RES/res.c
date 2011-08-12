/*
 * Implementation of the IEEE802.15.4e RES layer
 *
 * Authors:
 * Thomas Watteyne <watteyne@eecs.berkeley.edu>, August 2010
 */

#include "openwsn.h"
#include "res.h"
#include "idmanager.h"
#include "openserial.h"
#include "IEEE802154.h"
#include "IEEE802154E.h"
#include "openqueue.h"
#include "neighbors.h"
#include "timers.h"
#include "IEEE802154E.h"
#include "iphc.h"
#include "leds.h"
#include "packetfunctions.h"

//===================================== variables ==============================

uint16_t res_periodMaintenance;
bool     res_busySending;

//===================================== prototypes =============================

//===================================== public =================================

void res_init() {
   res_periodMaintenance = 32768; // timer_res_fired() called every 1 sec 
   res_busySending       = FALSE;
   //poipoi disabling ADV timer_startPeriodic(TIMER_RES,res_periodMaintenance);
}

//===================================== public with upper ======================

error_t res_send(OpenQueueEntry_t *msg) {
   msg->owner        = COMPONENT_RES;
   msg->l2_frameType = IEEE154_TYPE_DATA;
   return mac_send(msg);
}

//===================================== public with lower ======================

void res_sendDone(OpenQueueEntry_t* msg, error_t error) {
   msg->owner = COMPONENT_RES;
   if (msg->creator == COMPONENT_RES) {
      // discard (ADV) packets this component has created
      openqueue_freePacketBuffer(msg);
      // I can send the next ADV
      res_busySending = FALSE;
   } else {
      // send the rest up the stack
      iphc_sendDone(msg,error);
   }
}

void res_receive(OpenQueueEntry_t* msg) {
   msg->owner = COMPONENT_RES;
   // send the rest up the stack
   switch (msg->l2_frameType) {
      case IEEE154_TYPE_DATA:
         iphc_receive(msg);
         break;
      default:
         openqueue_freePacketBuffer(msg);
         openserial_printError(COMPONENT_RES,ERR_MSG_UNKNOWN_TYPE,msg->l2_frameType,0);
         break;
   }
}

bool res_debugPrint() {
   uint16_t output=0;
   output = neighbors_getMyDAGrank();
   openserial_printStatus(STATUS_RES_DAGRANK,(uint8_t*)&output,1);
   return TRUE;
}

//===================================== timer ==================================

void timer_res_fired() {
   OpenQueueEntry_t* adv;
   
   // only send a packet if I received a sendDone for the previous.
   // the packet might be stuck in the queue for a long time for
   // example while the mote is synchronizing
   if (res_busySending==FALSE) {
      // get a free packet buffer
      adv = openqueue_getFreePacketBuffer();
      if (adv==NULL) {
         openserial_printError(ERR_NO_FREE_PACKET_BUFFER,
                               COMPONENT_RES,
                               0,
                               0);
         return;
      }
      
      // declare ownership over that packet
      adv->creator = COMPONENT_RES;
      adv->owner   = COMPONENT_RES;
      
      // add ADV-specific header
      packetfunctions_reserveHeaderSize(adv,sizeof(IEEE802154E_ADV_t));
      // the actual value of the current ASN will be written by the
      // IEEE802.15.4e when transmitting
      
      // some l2 information about this packet
      adv->l2_frameType = IEEE154_TYPE_BEACON;
      adv->l2_nextORpreviousHop.type = ADDR_16B;
      adv->l2_nextORpreviousHop.addr_16b[0] = 0xff;
      adv->l2_nextORpreviousHop.addr_16b[1] = 0xff;
      
      // send to MAC
      mac_send(adv);
      res_busySending = TRUE;
   }
}